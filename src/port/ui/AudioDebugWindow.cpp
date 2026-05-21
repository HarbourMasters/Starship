#include "AudioDebugWindow.h"
#include "port/audio/AudioDebug.h"
#include <imgui.h>
#include <string>

// CODEC_* constants
extern "C" {
#include <sf64audio_provisional.h>
}

namespace SF64 {

static const char* CodecName(int codec) {
    switch (codec) {
        case CODEC_ADPCM:         return "ADPCM";
        case CODEC_S8:            return "S8";
        case CODEC_S16_INMEMORY:  return "S16_INMEMORY";
        case CODEC_SMALL_ADPCM:   return "SMALL_ADPCM";
        case CODEC_REVERB:        return "REVERB";
        case CODEC_S16:           return "S16";
        default:                  return "UNKNOWN";
    }
}

static void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(desc);
        ImGui::EndTooltip();
    }
}

void AudioDebugWindow::DrawElement() {
    if (!gSnapshotReady.load(std::memory_order_acquire)) {
        ImGui::TextDisabled("No sample has played yet.");
        return;
    }

    AudioDebugSnapshot s = AudioDebug_GetSnapshot();
    const std::string& path = AudioDebug_GetSamplePath(s.sample);

    // ── Current sample ───────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Current Sample", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2, "sample_cols", false);
        ImGui::SetColumnWidth(0, 160.0f);

        ImGui::TextDisabled("Path");        ImGui::NextColumn();
        ImGui::TextUnformatted(path.empty() ? "(unknown)" : path.c_str());
        ImGui::NextColumn();

        ImGui::TextDisabled("Ptr");         ImGui::NextColumn();
        ImGui::Text("%p", static_cast<void*>(s.sample));
        ImGui::NextColumn();

        ImGui::TextDisabled("Codec");       ImGui::NextColumn();
        ImGui::Text("%s (%d)", CodecName(s.codec), s.codec);
        ImGui::NextColumn();

        ImGui::TextDisabled("Size (bytes)"); ImGui::NextColumn();
        ImGui::Text("%u  (%.1f KB)", s.sampleSize, s.sampleSize / 1024.0f);
        ImGui::NextColumn();

        // Playback position progress bar
        ImGui::TextDisabled("Position");    ImGui::NextColumn();
        {
            float frac = (s.endPos > 0) ? (float)s.samplePos / (float)s.endPos : 0.0f;
            frac = (frac < 0.0f) ? 0.0f : (frac > 1.0f) ? 1.0f : frac;
            char overlay[64];
            snprintf(overlay, sizeof(overlay), "%d / %u", s.samplePos, s.endPos);
            ImGui::ProgressBar(frac, ImVec2(-1.0f, 0.0f), overlay);
        }
        ImGui::NextColumn();

        // Resample rate: fixed-point 16.16 → frequency ratio
        ImGui::TextDisabled("Resample Rate"); ImGui::NextColumn();
        float pitchRatio = (float)s.resampleRate / 32768.0f;   // Q15 fixed-point
        ImGui::Text("0x%04X  (%.4fx pitch)", (unsigned)s.resampleRate, pitchRatio);
        ImGui::SameLine(); HelpMarker("Fixed-point Q15: 0x8000 = 1.0 (no pitch shift)");
        ImGui::NextColumn();

        ImGui::Columns(1);
    }

    // ── Loop info ────────────────────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Loop Info", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::Columns(2, "loop_cols", false);
        ImGui::SetColumnWidth(0, 160.0f);

        bool hasLoop = (s.loopCount != 0);

        ImGui::TextDisabled("Has Loop");    ImGui::NextColumn();
        if (hasLoop)
            ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "Yes");
        else
            ImGui::TextDisabled("No");
        ImGui::NextColumn();

        ImGui::TextDisabled("Loop Start");  ImGui::NextColumn();
        ImGui::Text("%u", s.loopStart);
        ImGui::NextColumn();

        ImGui::TextDisabled("Loop End");    ImGui::NextColumn();
        ImGui::Text("%u", s.loopEnd);
        ImGui::NextColumn();

        ImGui::TextDisabled("Loop Length"); ImGui::NextColumn();
        ImGui::Text("%u samples", (s.loopEnd > s.loopStart) ? s.loopEnd - s.loopStart : 0);
        ImGui::NextColumn();

        ImGui::TextDisabled("Loop Count");  ImGui::NextColumn();
        if (s.loopCount == 0xFFFFFFFF)
            ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "Infinite (0xFFFFFFFF)");
        else
            ImGui::Text("%u", s.loopCount);
        ImGui::NextColumn();

        // Show where in the loop we are
        if (hasLoop && s.loopEnd > s.loopStart) {
            ImGui::TextDisabled("Loop Progress"); ImGui::NextColumn();
            uint32_t len = s.loopEnd - s.loopStart;
            int posInLoop = s.samplePos - (int)s.loopStart;
            float frac = (posInLoop >= 0) ? (float)posInLoop / (float)len : 0.0f;
            frac = (frac < 0.0f) ? 0.0f : (frac > 1.0f) ? 1.0f : frac;
            char overlay[64];
            snprintf(overlay, sizeof(overlay), "%d / %u", posInLoop, len);
            ImGui::ProgressBar(frac, ImVec2(-1.0f, 0.0f), overlay);
            ImGui::NextColumn();
        }

        ImGui::Columns(1);
    }

    // ── All registered samples ───────────────────────────────────────────────
    if (ImGui::CollapsingHeader("Registered Samples")) {
        std::lock_guard<std::mutex> lk(gSamplePathMapMutex);
        ImGui::Text("%zu sample(s) registered", gSamplePathMap.size());
        ImGui::Separator();

        if (ImGui::BeginTable("##samples", 2,
                              ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                              ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingStretchProp,
                              ImVec2(0.0f, 300.0f))) {
            ImGui::TableSetupScrollFreeze(0, 1);
            ImGui::TableSetupColumn("Path",    ImGuiTableColumnFlags_WidthStretch);
            ImGui::TableSetupColumn("Ptr",     ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableHeadersRow();

            for (auto& [ptr, p] : gSamplePathMap) {
                ImGui::TableNextRow();
                ImGui::TableSetColumnIndex(0);
                bool isActive = (ptr == s.sample);
                if (isActive) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.4f, 1.0f));
                ImGui::TextUnformatted(p.c_str());
                if (isActive) ImGui::PopStyleColor();

                ImGui::TableSetColumnIndex(1);
                ImGui::Text("%p", static_cast<void*>(ptr));
            }
            ImGui::EndTable();
        }
    }
}

} // namespace SF64
