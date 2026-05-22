#include "AudioDebugWindow.h"
#include "port/audio/AudioDebug.h"
#include <imgui.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <cinttypes>
#include <cstdio>
#include <cstring>

extern "C" {
#include <sf64audio_provisional.h>
#include <sf64audio_external.h>
#include <audioseq_cmd.h>
#include <audiothread_cmd.h>
#include <bgm.h>
}

namespace SF64 {

// ── Name tables ──────────────────────────────────────────────────────────────

static const char* CodecName(int codec) {
    switch (codec) {
        case CODEC_ADPCM:        return "ADPCM";
        case CODEC_S8:           return "S8";
        case CODEC_S16_INMEMORY: return "S16_INMEMORY";
        case CODEC_SMALL_ADPCM:  return "SMALL_ADPCM";
        case CODEC_REVERB:       return "REVERB";
        case CODEC_S16:          return "S16";
        default:                 return "UNKNOWN";
    }
}

static const char* SeqIdName(int id) {
    switch (id) {
        case SEQ_ID_SFX:          return "SFX";
        case SEQ_ID_VOICE:        return "VOICE";
        case SEQ_ID_CORNERIA:     return "CORNERIA";
        case SEQ_ID_METEO:        return "METEO";
        case SEQ_ID_TITANIA:      return "TITANIA";
        case SEQ_ID_SECTOR_X:     return "SECTOR X";
        case SEQ_ID_ZONESS:       return "ZONESS";
        case SEQ_ID_AREA_6:       return "AREA 6";
        case SEQ_ID_VENOM_1:      return "VENOM 1";
        case SEQ_ID_SECTOR_Y:     return "SECTOR Y";
        case SEQ_ID_FORTUNA:      return "FORTUNA";
        case SEQ_ID_SOLAR:        return "SOLAR";
        case SEQ_ID_BOLSE:        return "BOLSE";
        case SEQ_ID_KATINA:       return "KATINA";
        case SEQ_ID_AQUAS:        return "AQUAS";
        case SEQ_ID_SECTOR_Z:     return "SECTOR Z";
        case SEQ_ID_MACBETH:      return "MACBETH";
        case SEQ_ID_ANDROSS:      return "ANDROSS";
        case SEQ_ID_BOSS_CO_1:    return "BOSS CO 1";
        case SEQ_ID_BOSS_ME:      return "BOSS ME";
        case SEQ_ID_BOSS_TI:      return "BOSS TI";
        case SEQ_ID_BOSS_SX:      return "BOSS SX";
        case SEQ_ID_BOSS_ZO:      return "BOSS ZO";
        case SEQ_ID_BOSS_A6:      return "BOSS A6";
        case SEQ_ID_BOSS_VE:      return "BOSS VE";
        case SEQ_ID_BOSS_SY:      return "BOSS SY";
        case SEQ_ID_UNK_26:       return "UNK_26";
        case SEQ_ID_BOSS_SO:      return "BOSS SO";
        case SEQ_ID_BOSS_BO:      return "BOSS BO";
        case SEQ_ID_BOSS_KA:      return "BOSS KA";
        case SEQ_ID_BOSS_AQ:      return "BOSS AQ";
        case SEQ_ID_BOSS_SZ:      return "BOSS SZ";
        case SEQ_ID_BOSS_MA:      return "BOSS MA";
        case SEQ_ID_BOSS_ANDROSS: return "BOSS ANDROSS";
        case SEQ_ID_TITLE:        return "TITLE";
        case SEQ_ID_OPENING:      return "OPENING";
        case SEQ_ID_MENU:         return "MENU";
        case SEQ_ID_CO_INTRO:     return "CO_INTRO";
        case SEQ_ID_GOOD_END:     return "GOOD END";
        case SEQ_ID_DEATH:        return "DEATH";
        case SEQ_ID_GAME_OVER:    return "GAME OVER";
        case SEQ_ID_UNK_41:       return "UNK_41";
        case SEQ_ID_STAFF_ROLL:   return "STAFF ROLL";
        case SEQ_ID_STAR_WOLF:    return "STAR WOLF";
        case SEQ_ID_INTRO_S:      return "INTRO S";
        case SEQ_ID_INTRO_M:      return "INTRO M";
        case SEQ_ID_VERSUS:       return "VERSUS";
        case SEQ_ID_VS_HURRY:     return "VS HURRY";
        case SEQ_ID_BOSS_CO_2:    return "BOSS CO 2";
        case SEQ_ID_BAD_END:      return "BAD END";
        case SEQ_ID_ME_INTRO:     return "ME_INTRO";
        case SEQ_ID_INTRO_51:     return "INTRO_51";
        case SEQ_ID_UNK_52:       return "UNK_52";
        case SEQ_ID_UNK_53:       return "UNK_53";
        case SEQ_ID_KATT:         return "KATT";
        case SEQ_ID_BILL:         return "BILL";
        case SEQ_ID_VS_MENU:      return "VS_MENU";
        case SEQ_ID_UNK_57:       return "UNK_57";
        case SEQ_ID_WARP_ZONE:    return "WARP ZONE";
        case SEQ_ID_UNK_59:       return "UNK_59";
        case SEQ_ID_WORLD_MAP:    return "WORLD MAP";
        case SEQ_ID_AND_BRAIN:    return "AND BRAIN";
        case SEQ_ID_TO_ANDROSS:   return "TO ANDROSS";
        case SEQ_ID_TRAINING:     return "TRAINING";
        case SEQ_ID_VE_CLEAR:     return "VE CLEAR";
        case SEQ_ID_BOSS_RESUME:  return "BOSS RESUME";
        case SEQ_ID_VOICE_LYLAT:  return "VOICE LYLAT";
        case 0xFFFF:              return "NONE";
        default:                  return "?";
    }
}

static const char* SeqPlayerName(int idx) {
    switch (idx) {
        case SEQ_PLAYER_BGM:     return "BGM";
        case SEQ_PLAYER_FANFARE: return "FANFARE";
        case SEQ_PLAYER_SFX:     return "SFX";
        case SEQ_PLAYER_VOICE:   return "VOICE";
        default:                 return "?";
    }
}

static const char* SoundModeName(int m) {
    switch (m) {
        case SOUNDMODE_STEREO:  return "Stereo";
        case SOUNDMODE_HEADSET: return "Headset";
        case SOUNDMODE_SURROUND:return "Surround";
        case SOUNDMODE_MONO:    return "Mono";
        default:                return "?";
    }
}

static const char* AudioSpecName(int id) {
    switch (id) {
        case AUDIOSPEC_CO:  return "CO (Corneria)";
        case AUDIOSPEC_ME:  return "ME (Meteo)";
        case AUDIOSPEC_TI:  return "TI (Titania)";
        case AUDIOSPEC_SX:  return "SX (Sector X)";
        case AUDIOSPEC_ZO:  return "ZO (Zoness)";
        case AUDIOSPEC_A6:  return "A6 (Area 6)";
        case AUDIOSPEC_SY:  return "SY (Sector Y)";
        case AUDIOSPEC_FO:  return "FO (Fortuna)";
        case AUDIOSPEC_SO:  return "SO (Solar)";
        case AUDIOSPEC_BO:  return "BO (Bolse)";
        case AUDIOSPEC_KA:  return "KA (Katina)";
        case AUDIOSPEC_AQ:  return "AQ (Aquas)";
        case AUDIOSPEC_SZ:  return "SZ (Sector Z)";
        case AUDIOSPEC_MA:  return "MA (Macbeth)";
        default: {
            static char buf[16];
            snprintf(buf, sizeof(buf), "%d", id);
            return buf;
        }
    }
}

// ── Helpers ──────────────────────────────────────────────────────────────────

static void HelpMarker(const char* desc) {
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered()) {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted(desc);
        ImGui::EndTooltip();
    }
}

static s32 DrawPoolBar(const char* label, const AudioAllocPool& pool) {
    if (pool.size <= 0) return 0;
    s32 used = (s32)(pool.curRamAddr - pool.startRamAddr);
    if (used < 0) used = 0;
    float frac = (float)used / (float)pool.size;
    char overlay[64];
    snprintf(overlay, sizeof(overlay), "%d / %d KB", used / 1024, pool.size / 1024);
    ImVec4 col = (frac < 0.6f) ? ImVec4(0.2f, 0.8f, 0.2f, 1.f)
               : (frac < 0.85f)? ImVec4(0.9f, 0.75f, 0.1f, 1.f)
               :                  ImVec4(0.9f, 0.2f, 0.2f, 1.f);
    ImGui::PushStyleColor(ImGuiCol_PlotHistogram, col);
    ImGui::ProgressBar(frac, ImVec2(-1.f, 0.f), overlay);
    ImGui::PopStyleColor();
    return used;
}

// ── Module toggle button (coloured by visibility state) ──────────────────────
static void ModuleToggle(const char* label, bool* pVisible) {
    if (*pVisible)
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.2f, 0.5f, 0.2f, 1.f));
    else
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.25f, 0.25f, 0.25f, 1.f));
    if (ImGui::Button(label, ImVec2(120.f, 0.f)))
        *pVisible = !*pVisible;
    ImGui::PopStyleColor();
}

// ── Main draw ────────────────────────────────────────────────────────────────

void AudioDebugWindow::DrawElement() {

    // Persistent visibility flags for each detachable module
    static bool sShow_PCMCapture   = false;
    static bool sShow_ChanMute     = false;
    static bool sShow_SeqPlayers   = false;
    static bool sShow_Sequences    = false;
    static bool sShow_ActiveNotes  = false;
    static bool sShow_ChanStats    = false;
    static bool sShow_Polyphony    = false;
    static bool sShow_Reverb       = false;
    static bool sShow_AudioHeap    = false;
    static bool sShow_System       = false;
    static bool sShow_SampleInfo   = false;

    // ── Frame Step (always in main window) ───────────────────────────────────
    {
        bool stepping = SF64::gAudioStepMode.load(std::memory_order_acquire);
        uint64_t frameCount = SF64::gAudioFrameCount.load(std::memory_order_relaxed);

        {
            bool wasStepping = stepping;
            if (wasStepping)
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.2f, 0.2f, 1.f));
            if (ImGui::Button(wasStepping ? "Resume Audio" : "Pause Audio")) {
                stepping = !stepping;
                SF64::gAudioStepMode.store(stepping, std::memory_order_release);
                if (!stepping)
                    SF64::gAudioStepOnce.store(false, std::memory_order_release);
            }
            if (wasStepping) ImGui::PopStyleColor();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip(stepping
                ? "Audio synthesis is PAUSED — game keeps running, silence output.\nClick to resume."
                : "Click to pause audio synthesis for frame-by-frame stepping.\nGame keeps running.");

        ImGui::SameLine();
        {
            if (!stepping) ImGui::BeginDisabled();
            if (ImGui::Button("Step Frame"))
                SF64::gAudioStepOnce.store(true, std::memory_order_release);
            if (!stepping) ImGui::EndDisabled();
        }
        if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
            ImGui::SetTooltip("Run audio synthesis for exactly one frame.\nPause the driver first.");

        ImGui::SameLine();
        static int sStepN = 10;
        ImGui::SetNextItemWidth(52.f);
        ImGui::InputInt("##stepN", &sStepN, 1, 10);
        if (sStepN < 1) sStepN = 1;
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Number of frames to advance.\nUse +/- or type a value.");
        ImGui::SameLine();
        {
            if (!stepping) ImGui::BeginDisabled();
            char stepLabel[32];
            snprintf(stepLabel, sizeof(stepLabel), "Step %d", sStepN);
            if (ImGui::Button(stepLabel))
                SF64::gAudioStepN.fetch_add(sStepN, std::memory_order_release);
            if (!stepping) ImGui::EndDisabled();
        }

        int remaining = SF64::gAudioStepN.load(std::memory_order_relaxed);
        if (remaining > 0) {
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(1.f, 0.8f, 0.2f, 1.f), "%d left", remaining);
        }

        ImGui::SameLine();
        ImGui::Spacing(); ImGui::SameLine();
        if (stepping) {
            ImGui::TextColored(ImVec4(1.f, 0.4f, 0.4f, 1.f),
                               "[PAUSED]  frame %" PRIu64, frameCount);
        } else {
            ImGui::TextDisabled("frame %" PRIu64, frameCount);
        }
    }
    ImGui::Separator();

    // ── Module toggle grid ───────────────────────────────────────────────────
    ImGui::TextDisabled("Modules:");
    ModuleToggle("PCM Capture",   &sShow_PCMCapture);  ImGui::SameLine();
    ModuleToggle("Chan Mute",     &sShow_ChanMute);    ImGui::SameLine();
    ModuleToggle("Seq Players",   &sShow_SeqPlayers);  ImGui::SameLine();
    ModuleToggle("Sequences",     &sShow_Sequences);
    ModuleToggle("Active Notes",  &sShow_ActiveNotes); ImGui::SameLine();
    ModuleToggle("Chan Stats",    &sShow_ChanStats);   ImGui::SameLine();
    ModuleToggle("Polyphony",     &sShow_Polyphony);   ImGui::SameLine();
    ModuleToggle("Reverb",        &sShow_Reverb);
    ModuleToggle("Audio Heap",    &sShow_AudioHeap);   ImGui::SameLine();
    ModuleToggle("System",        &sShow_System);      ImGui::SameLine();
    ModuleToggle("Sample Info",   &sShow_SampleInfo);

    // ── PCM Capture ──────────────────────────────────────────────────────────
    if (sShow_PCMCapture) {
        ImGui::SetNextWindowSize(ImVec2(450, 175), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("PCM Capture##sf64ad", &sShow_PCMCapture)) {
            static char sRecPathBuf[512] = "audio_capture.raw";
            ImGui::SetNextItemWidth(340.f);
            ImGui::InputText("Output file##recpath", sRecPathBuf, sizeof(sRecPathBuf));
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Raw signed 16-bit little-endian PCM.\n"
                                  "Import in Audacity with:\n"
                                  "  File > Import > Raw Data\n"
                                  "  Encoding: Signed 16-bit PCM\n"
                                  "  Byte order: Little-endian\n"
                                  "  Channels: 2 (stereo)");

            ImGui::Spacing();

            bool isRecording = SF64::gAudioRecording.load(std::memory_order_acquire);
            bool isPaused    = SF64::gAudioRecordPaused.load(std::memory_order_acquire);
            uint64_t bytes   = SF64::gAudioRecordBytes.load(std::memory_order_relaxed);

            if (!isRecording) {
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.55f, 0.15f, 1.f));
                if (ImGui::Button("Record")) {
                    {
                        std::lock_guard<std::mutex> lk(SF64::gAudioRecordMutex);
                        SF64::gAudioRecordPath = sRecPathBuf;
                    }
                    SF64::gAudioRecordPaused.store(false, std::memory_order_release);
                    SF64::gAudioSaveAndStop.store(false, std::memory_order_release);
                    SF64::gAudioRecording.store(true, std::memory_order_release);
                }
                ImGui::PopStyleColor();
            } else {
                {
                    bool wasPaused = isPaused;
                    if (wasPaused)
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.45f, 0.1f, 1.f));
                    if (ImGui::Button(wasPaused ? "Resume" : "Pause")) {
                        SF64::gAudioRecordPaused.store(!isPaused, std::memory_order_release);
                    }
                    if (wasPaused) ImGui::PopStyleColor();
                }
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip(isPaused ? "Resume writing PCM to file."
                                               : "Pause writing — keeps file open, no data lost.");

                ImGui::SameLine();
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.6f, 0.1f, 0.1f, 1.f));
                if (ImGui::Button("Save & Stop")) {
                    SF64::gAudioSaveAndStop.store(true, std::memory_order_release);
                }
                ImGui::PopStyleColor();
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("Flush and close the output file, then stop recording.");
            }

            ImGui::SameLine();
            ImGui::Spacing(); ImGui::SameLine();
            if (isRecording) {
                double mb = bytes / (1024.0 * 1024.0);
                if (isPaused)
                    ImGui::TextColored(ImVec4(1.f, 0.7f, 0.1f, 1.f),
                                       "[PAUSED]  %.2f MB captured", mb);
                else
                    ImGui::TextColored(ImVec4(0.3f, 1.f, 0.3f, 1.f),
                                       "[REC]  %.2f MB", mb);
            } else {
                ImGui::TextDisabled("idle");
            }
        }
        ImGui::End();
    }

    // ── Channel Mute ─────────────────────────────────────────────────────────
    if (sShow_ChanMute) {
        ImGui::SetNextWindowSize(ImVec2(460, 130), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Channel Mute##sf64ad", &sShow_ChanMute)) {
            if (ImGui::Button("Mute All")) {
                for (int i = 0; i < SF64::kNumSeqChannels; i++)
                    SF64::gMutedChannels[i].store(true, std::memory_order_relaxed);
            }
            ImGui::SameLine();
            if (ImGui::Button("Unmute All")) {
                for (int i = 0; i < SF64::kNumSeqChannels; i++)
                    SF64::gMutedChannels[i].store(false, std::memory_order_relaxed);
            }
            ImGui::Spacing();

            for (int i = 0; i < SF64::kNumSeqChannels; i++) {
                if (i > 0 && i % 8 == 0) ImGui::NewLine();
                else if (i > 0)          ImGui::SameLine();

                bool muted = SF64::gMutedChannels[i].load(std::memory_order_relaxed);
                if (muted) ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.15f, 0.15f, 1.f));
                char label[8];
                snprintf(label, sizeof(label), "Ch %d", i);
                if (ImGui::Button(label, ImVec2(52.f, 0.f)))
                    SF64::gMutedChannels[i].store(!muted, std::memory_order_relaxed);
                if (muted) ImGui::PopStyleColor();
                if (ImGui::IsItemHovered()) {
                    ImGui::BeginTooltip();
                    ImGui::Text("Channel %d — %s\nClick to %s", i,
                                muted ? "MUTED" : "active",
                                muted ? "unmute" : "mute");
                    ImGui::EndTooltip();
                }
            }
            ImGui::NewLine();
        }
        ImGui::End();
    }

    // ── Sequence Players ─────────────────────────────────────────────────────
    if (sShow_SeqPlayers) {
        static float  sVolScale[SEQ_PLAYER_MAX]   = {1.f, 1.f, 1.f, 1.f};
        static int    sTempoDelta[SEQ_PLAYER_MAX] = {0, 0, 0, 0};
        static int    sTranspose[SEQ_PLAYER_MAX]  = {0, 0, 0, 0};

        ImGui::SetNextWindowSize(ImVec2(480, 520), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Sequence Players##sf64ad", &sShow_SeqPlayers)) {
            for (int pi = 0; pi < SEQ_PLAYER_MAX; pi++) {
                const SequencePlayer& p = gSeqPlayers[pi];

                ImVec4 nameCol = p.enabled
                    ? ImVec4(0.4f, 1.f, 0.4f, 1.f)
                    : ImVec4(0.5f, 0.5f, 0.5f, 1.f);
                ImGui::TextColored(nameCol, "[%d] %s", pi, SeqPlayerName(pi));
                ImGui::SameLine();
                ImGui::TextDisabled("state=%d", p.state);

                if (!p.enabled) { ImGui::Separator(); continue; }

                ImGui::Columns(2, nullptr, false);
                ImGui::SetColumnWidth(0, 160.f);

#define ROW(lbl, ...) do { ImGui::TextDisabled(lbl); ImGui::NextColumn(); ImGui::Text(__VA_ARGS__); ImGui::NextColumn(); } while(0)
                ROW("Sequence",   "%s  (id %u)", SeqIdName(p.seqId), (unsigned)p.seqId);
                ROW("Volume",     "%.3f  (fade %.3f  applied %.3f)",
                                  p.volume, p.fadeVolume, p.appliedFadeVolume);
                ROW("Tempo",      "%u ticks/min  (change %+d)", (unsigned)p.tempo, (int)p.tempoChange);
                ROW("Transpose",  "%+d semitones", (int)p.transposition);
                ROW("Fade Timer", "%u ticks", (unsigned)p.fadeTimer);
                ROW("Muted",      "%s", p.muted ? "YES" : "no");
#undef ROW
                ImGui::Columns(1);

                ImGui::Spacing();
                ImGui::PushID(pi);

                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.15f, 0.15f, 1.f));
                if (ImGui::Button("Stop")) {
                    AUDIOCMD_GLOBAL_DISABLE_SEQPLAYER(pi, 20);
                }
                ImGui::PopStyleColor();
                ImGui::SameLine(); HelpMarker("Fade out and disable this sequence player (20 tick fade).");

                ImGui::SameLine();
                if (ImGui::Button("Silence")) {
                    AUDIOCMD_SEQPLAYER_FADE_TO_SET_VOLUME(pi, 0, 0);
                }
                ImGui::SameLine(); HelpMarker("Instantly set volume to 0 (player stays running).");

                ImGui::SameLine();
                if (ImGui::Button("Restore Vol")) {
                    sVolScale[pi] = 1.f;
                    AUDIOCMD_SEQPLAYER_FADE_VOLUME_SCALE(pi, 1.f);
                }
                ImGui::SameLine(); HelpMarker("Reset volume scale to 1.0.");

                ImGui::SetNextItemWidth(200.f);
                if (ImGui::SliderFloat("Vol Scale", &sVolScale[pi], 0.f, 2.f, "%.2f")) {
                    AUDIOCMD_SEQPLAYER_FADE_VOLUME_SCALE(pi, sVolScale[pi]);
                }
                ImGui::SameLine(); HelpMarker("Multiplicative volume scale (1.0 = normal).");

                ImGui::SetNextItemWidth(200.f);
                if (ImGui::SliderInt("Tempo +/-", &sTempoDelta[pi], -300, 300)) {
                    AUDIOCMD_SEQPLAYER_CHANGE_TEMPO(pi, sTempoDelta[pi]);
                }
                ImGui::SameLine();
                if (ImGui::Button("Reset##tempo")) {
                    AUDIOCMD_SEQPLAYER_CHANGE_TEMPO(pi, -sTempoDelta[pi]);
                    sTempoDelta[pi] = 0;
                }
                ImGui::SameLine(); HelpMarker("Add a BPM delta on top of the sequence's native tempo.");

                ImGui::SetNextItemWidth(200.f);
                if (ImGui::SliderInt("Transpose", &sTranspose[pi], -24, 24)) {
                    AUDIOCMD_SEQPLAYER_SET_TRANSPOSITION(pi, (s8)sTranspose[pi]);
                }
                ImGui::SameLine();
                if (ImGui::Button("Reset##tr")) {
                    sTranspose[pi] = 0;
                    AUDIOCMD_SEQPLAYER_SET_TRANSPOSITION(pi, 0);
                }
                ImGui::SameLine(); HelpMarker("Shift all notes on this player up/down by semitones.");

                ImGui::PopID();
                ImGui::Separator();
            }
        }
        ImGui::End();
    }

    // ── Sequences ────────────────────────────────────────────────────────────
    if (sShow_Sequences) {
        static int  sSeqSelPlayer  = 0;
        static int  sSeqSelId      = 2;
        static bool sSeqDisasmDirty = true;
        static std::string sSeqDisasm;

        ImGui::SetNextWindowSize(ImVec2(620, 560), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Sequences##sf64ad", &sShow_Sequences)) {
            // Player picker
            ImGui::AlignTextToFramePadding();
            ImGui::TextDisabled("Player:"); ImGui::SameLine();
            for (int pi = 0; pi < SEQ_PLAYER_MAX; pi++) {
                if (pi > 0) ImGui::SameLine();
                char plabel[32];
                snprintf(plabel, sizeof(plabel), "%s##seqpl%d", SeqPlayerName(pi), pi);
                if (ImGui::RadioButton(plabel, &sSeqSelPlayer, pi)) {}
            }

            ImGui::Spacing();

            static ImGuiTextFilter sSeqFilter;
            sSeqFilter.Draw("Filter##seqfilter", 200.f);
            ImGui::SameLine(); HelpMarker("Filter sequence list by name, id, or path.");

            if (ImGui::BeginTable("##seqlist", 4,
                    ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                    ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingFixedFit,
                    ImVec2(0.f, 220.f))) {
                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("ID",   ImGuiTableColumnFlags_WidthFixed,  36.f);
                ImGui::TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed, 120.f);
                ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("",     ImGuiTableColumnFlags_WidthFixed,  80.f);
                ImGui::TableHeadersRow();

                for (int id = 0; id < SEQ_ID_MAX; id++) {
                    const char* name = SeqIdName(id);
                    const std::string& seqPath = AudioDebug_GetSeqPath((uint8_t)id);
                    char idstr[8];
                    snprintf(idstr, sizeof(idstr), "%d", id);
                    if (!sSeqFilter.PassFilter(name) &&
                        !sSeqFilter.PassFilter(idstr) &&
                        !sSeqFilter.PassFilter(seqPath.c_str()))
                        continue;

                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    bool sel = (sSeqSelId == id);
                    if (sel) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.f, 0.4f, 1.f));
                    if (ImGui::Selectable(idstr, sel,
                            ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowOverlap,
                            ImVec2(0.f, 0.f))) {
                        if (sSeqSelId != id) { sSeqSelId = id; sSeqDisasmDirty = true; }
                    }
                    if (sel) ImGui::PopStyleColor();

                    ImGui::TableSetColumnIndex(1);
                    ImGui::TextUnformatted(name);

                    ImGui::TableSetColumnIndex(2);
                    if (seqPath.empty()) {
                        ImGui::TextDisabled("—");
                    } else {
                        const char* slash = strrchr(seqPath.c_str(), '/');
                        ImGui::TextUnformatted(slash ? slash + 1 : seqPath.c_str());
                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::TextUnformatted(seqPath.c_str());
                            ImGui::EndTooltip();
                        }
                    }

                    ImGui::TableSetColumnIndex(3);
                    ImGui::PushID(id);
                    const SequencePlayer& liveP = gSeqPlayers[sSeqSelPlayer];
                    bool isPlaying = liveP.enabled && ((int)liveP.seqId == id);
                    if (isPlaying)
                        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.15f, 0.55f, 0.15f, 1.f));
                    if (ImGui::SmallButton(isPlaying ? "■ Stop" : "▶ Play")) {
                        if (isPlaying) {
                            AUDIOCMD_GLOBAL_DISABLE_SEQPLAYER(sSeqSelPlayer, 10);
                        } else {
                            AUDIOCMD_GLOBAL_INIT_SEQPLAYER(sSeqSelPlayer, id, 0, 0);
                        }
                        sSeqDisasmDirty = true;
                    }
                    if (isPlaying) ImGui::PopStyleColor();
                    ImGui::PopID();
                }
                ImGui::EndTable();
            }

            ImGui::Spacing();
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.55f, 0.1f, 0.1f, 1.f));
            if (ImGui::Button("Stop Player")) {
                AUDIOCMD_GLOBAL_DISABLE_SEQPLAYER(sSeqSelPlayer, 10);
            }
            ImGui::PopStyleColor();
            ImGui::SameLine(); HelpMarker("Stop the selected sequence player with a short fade-out.");

            ImGui::Separator();

            ImGui::TextDisabled("Bytecode disassembly");
            ImGui::SameLine();
            if (ImGui::SmallButton("Refresh##seqdis")) sSeqDisasmDirty = true;
            ImGui::SameLine(); HelpMarker(
                "Disassembles the raw N64 sequence bytecode for the selected sequence ID.\n"
                "The disassembly follows audio_seqplayer.c opcode dispatch tables.\n"
                "Click Refresh after changing the selected sequence.");

            if (sSeqDisasmDirty) {
                sSeqDisasm.clear();
                sSeqDisasmDirty = false;

                const SequencePlayer* src = nullptr;
                for (int pi = 0; pi < SEQ_PLAYER_MAX; pi++) {
                    if (gSeqPlayers[pi].enabled && (int)gSeqPlayers[pi].seqId == sSeqSelId) {
                        src = &gSeqPlayers[pi];
                        break;
                    }
                }
                if (!src && gSeqPlayers[sSeqSelPlayer].enabled)
                    src = &gSeqPlayers[sSeqSelPlayer];

                if (src && src->seqData != nullptr) {
                    const uint8_t* d = reinterpret_cast<const uint8_t*>(src->seqData);
                    size_t sz = 65536;
                    char linebuf[256];

                    snprintf(linebuf, sizeof(linebuf),
                             "seqId: %u  seqData: %p\n\n", (unsigned)src->seqId, (const void*)src->seqData);
                    sSeqDisasm += linebuf;

                    size_t pc   = 0;
                    int    iter = 0;
                    while (pc < sz && iter < 256) {
                        iter++;
                        size_t opc = pc;
                        uint8_t cmd = d[pc++];

                        const char* mnem = nullptr;
                        char args[128] = "";

                        auto rdU8  = [&]() -> uint8_t  { return (pc < sz) ? d[pc++] : 0; };
                        auto rdS8  = [&]() -> int8_t   { return (int8_t)rdU8(); };
                        auto rdU16 = [&]() -> uint16_t {
                            uint8_t hi = rdU8(), lo = rdU8();
                            return (uint16_t)((hi << 8) | lo);
                        };
                        auto rdCU16 = [&]() -> uint16_t {
                            uint8_t hi = rdU8();
                            if (hi & 0x80) { uint8_t lo = rdU8(); return (uint16_t)(((hi & 0x7F) << 8) | lo); }
                            return hi;
                        };

                        if (cmd == 0xFF) { mnem = "end/return"; }
                        else if (cmd == 0xFE) { mnem = "loop_back (delay 1)"; }
                        else if (cmd == 0xFD) { uint16_t v = rdCU16(); snprintf(args, sizeof(args), "%u", v); mnem = "delay"; }
                        else if (cmd == 0xFC) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "call"; }
                        else if (cmd == 0xFB) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "jump"; }
                        else if (cmd == 0xFA) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "jump_if_zero"; }
                        else if (cmd == 0xF9) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "jump_if_nonneg"; }
                        else if (cmd == 0xF8) { uint8_t c = rdU8(); snprintf(args, sizeof(args), "count=%u", c); mnem = "loop_start"; }
                        else if (cmd == 0xF7) { mnem = "loop_end"; }
                        else if (cmd == 0xF6) { mnem = "loop_break"; }
                        else if (cmd == 0xF5) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "jump_if_neg"; }
                        else if (cmd == 0xF1) { uint8_t c = rdU8(); snprintf(args, sizeof(args), "count=%u", c); mnem = "note_pool_fill"; }
                        else if (cmd == 0xF0) { mnem = "note_pool_clear"; }
                        else if (cmd == 0xDF) { mnem = "transpose=0, then"; }
                        else if (cmd == 0xDE) { int8_t v = rdS8(); snprintf(args, sizeof(args), "%+d", (int)v); mnem = "transpose+="; }
                        else if (cmd == 0xDD) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u (~%.1f BPM)", v, v * 2.34f); mnem = "tempo"; }
                        else if (cmd == 0xDC) { int8_t v = rdS8(); snprintf(args, sizeof(args), "%+d", (int)v); mnem = "tempo_change"; }
                        else if (cmd == 0xDB) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u", v); mnem = "seq_volume"; }
                        else if (cmd == 0xDA) { uint8_t s = rdU8(); uint16_t v = rdU16(); snprintf(args, sizeof(args), "sub=%u val=%u", s, v); mnem = "fade"; }
                        else if (cmd == 0xD9) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u", v); mnem = "fade_vol_mod"; }
                        else if (cmd == 0xD7) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "initchan"; }
                        else if (cmd == 0xD6) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "%#06x", v); mnem = "disablechan"; }
                        else if (cmd == 0xD5) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u", v); mnem = "mute_vol_scale"; }
                        else if (cmd == 0xD4) { mnem = "mute"; }
                        else if (cmd == 0xD3) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%#04x", v); mnem = "mute_behavior"; }
                        else if (cmd == 0xD2) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "@%#06x", v); mnem = "short_note_vel_table"; }
                        else if (cmd == 0xD1) { uint16_t v = rdU16(); snprintf(args, sizeof(args), "@%#06x", v); mnem = "short_note_gate_table"; }
                        else if (cmd == 0xD0) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u", v); mnem = "note_alloc_policy"; }
                        else if (cmd == 0xCC) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u", v); mnem = "io_write"; }
                        else if (cmd == 0xC9) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%#04x", v); mnem = "io_and"; }
                        else if (cmd == 0xC8) { uint8_t v = rdU8(); snprintf(args, sizeof(args), "%u", v); mnem = "io_sub"; }
                        else if (cmd == 0xC7) { uint8_t a = rdU8(); uint16_t o = rdU16(); snprintf(args, sizeof(args), "@%#06x += %u", o, a); mnem = "write_seq_data"; }
                        else if (cmd >= 0xC0) {
                            snprintf(args, sizeof(args), "0x%02X", cmd); mnem = "seq_cmd";
                        } else {
                            uint8_t hi = cmd & 0xF0, ch = cmd & 0x0F;
                            if (hi == 0x90 || hi == 0xA0 || hi == 0x20 || hi == 0xB0) {
                                uint16_t off = rdU16();
                                const char* n = (hi == 0x90) ? "ldchan" : (hi == 0xA0 || hi == 0x20) ? "enable_chan" : "ldchan_dyn";
                                snprintf(args, sizeof(args), "ch=%u @%#06x", ch, off);
                                mnem = n;
                            } else if (hi == 0x30) {
                                uint8_t io = rdU8();
                                snprintf(args, sizeof(args), "ch=%u port=%u", ch, io);
                                mnem = "write_chan_io";
                            } else if (hi == 0x40) {
                                uint8_t io = rdU8();
                                snprintf(args, sizeof(args), "ch=%u port=%u", ch, io);
                                mnem = "read_chan_io";
                            } else if (hi == 0x60) {
                                snprintf(args, sizeof(args), "ch=%u ticks=%u", ch, ch);
                                mnem = "chan_delay";
                            } else {
                                snprintf(args, sizeof(args), "0x%02X", cmd);
                                mnem = "raw";
                            }
                        }

                        snprintf(linebuf, sizeof(linebuf),
                                 "[%04zX]  %-24s %s\n", opc, mnem ? mnem : "?", args);
                        sSeqDisasm += linebuf;

                        if (cmd == 0xFF || cmd == 0xFE) break;
                    }
                    if (iter >= 256) sSeqDisasm += "[...] (truncated at 256 instructions)\n";
                } else {
                    sSeqDisasm = "(sequence not loaded — play it first to populate seqData)";
                }
            }

            ImGui::InputTextMultiline("##seqdisasm",
                const_cast<char*>(sSeqDisasm.c_str()), sSeqDisasm.size() + 1,
                ImVec2(-1.f, 200.f),
                ImGuiInputTextFlags_ReadOnly);
        }
        ImGui::End();
    }

    // ── Active Notes ─────────────────────────────────────────────────────────
    if (sShow_ActiveNotes) {
        struct NoteRow {
            int         noteIdx;
            int         playerIdx;
            int         channelIdx;
            s32         samplePos;
            u32         loopStart, loopEnd, loopCount;
            u16         resampleRate;
            int         codec;
            u32         sampleSize;
            bool        isSynthetic;
            bool        hasLoop;
            std::string samplePath;
        };

        static std::vector<NoteRow> sCachedRows;
        static bool   sFreeze         = false;
        static float  sRefreshHz      = 4.f;
        static double sLastRefreshTime = 0.0;

        auto capture = [&]() {
            std::vector<NoteRow> rows;
            rows.reserve(32);
            if (!gNotes || gNumNotes <= 0) { sCachedRows = std::move(rows); return; }

            for (int ni = 0; ni < gNumNotes; ni++) {
                Note& n = gNotes[ni];
                if (!n.noteSubEu.bitField0.enabled) continue;

                NoteRow r{};
                r.noteIdx      = ni;
                r.samplePos    = n.synthesisState.samplePosInt;
                r.resampleRate = n.noteSubEu.resampleRate;
                r.isSynthetic  = (bool)n.noteSubEu.bitField1.isSyntheticWave;

                {
                    SequenceLayer* layer = n.playbackState.parentLayer;
                    if (layer >= &gSeqLayers[0] && layer < &gSeqLayers[64]) {
                        SequenceChannel* ch = layer->channel;
                        if (ch >= &gSeqChannels[0] && ch < &gSeqChannels[48]) {
                            SequencePlayer* sp = ch->seqPlayer;
                            if (sp >= &gSeqPlayers[0] && sp < &gSeqPlayers[SEQ_PLAYER_MAX]) {
                                r.playerIdx = (int)(sp - gSeqPlayers);
                                for (int ci = 0; ci < SEQ_NUM_CHANNELS; ci++) {
                                    if (sp->channels[ci] == ch) { r.channelIdx = ci; break; }
                                }
                            }
                        }
                    }
                }

                if (!r.isSynthetic) {
                    auto tryReadSample = [&]() {
                        ::Sample* const* addrPtr = n.noteSubEu.waveSampleAddr;
                        if (!addrPtr) return;
                        ::Sample* s = *addrPtr;
                        if (!s) return;
                        r.codec      = (int)s->codec;
                        r.sampleSize = s->size;
                        ::AdpcmLoop* loop = s->loop;
                        if (loop) {
                            r.loopStart = loop->start;
                            r.loopEnd   = loop->end;
                            r.loopCount = loop->count;
                            r.hasLoop   = (loop->count != 0);
                        }
                        std::lock_guard<std::mutex> lk(gSamplePathMapMutex);
                        for (auto& [sd, path] : gSamplePathMap) {
                            if (reinterpret_cast<void*>(s) == reinterpret_cast<void*>(sd) ||
                                (s->sampleAddr &&
                                 reinterpret_cast<void*>(s->sampleAddr) == reinterpret_cast<void*>(sd))) {
                                r.samplePath = path;
                                return;
                            }
                        }
                        if (r.samplePath.empty() && gSnapshotReady.load(std::memory_order_relaxed)) {
                            AudioDebugSnapshot snap = AudioDebug_GetSnapshot();
                            if (snap.sample &&
                                reinterpret_cast<void*>(s) == reinterpret_cast<void*>(snap.sample))
                                r.samplePath = AudioDebug_GetSamplePath(snap.sample);
                        }
                    };
                    tryReadSample();
                } else {
                    r.samplePath = "(synthetic wave)";
                }

                rows.push_back(std::move(r));
            }
            sCachedRows = std::move(rows);
        };

        double now = std::chrono::duration<double>(
            std::chrono::steady_clock::now().time_since_epoch()).count();
        double interval = (sRefreshHz > 0.f) ? 1.0 / sRefreshHz : 1.0;
        bool timeToRefresh = !sFreeze && (now - sLastRefreshTime >= interval);
        if (timeToRefresh) { capture(); sLastRefreshTime = now; }

        ImGui::SetNextWindowSize(ImVec2(720, 360), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Active Notes##sf64ad", &sShow_ActiveNotes)) {
            {
                bool wasFrozen = sFreeze;
                if (wasFrozen)
                    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.7f, 0.5f, 0.1f, 1.f));
                if (ImGui::Button(wasFrozen ? "Frozen" : "Live")) {
                    sFreeze = !sFreeze;
                    if (!sFreeze) { capture(); sLastRefreshTime = now; }
                }
                if (wasFrozen) ImGui::PopStyleColor();
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip(sFreeze
                    ? "Click to resume live updates."
                    : "Click to freeze the table so you can read it.");

            ImGui::SameLine();
            ImGui::SetNextItemWidth(120.f);
            ImGui::SliderFloat("Hz", &sRefreshHz, 0.5f, 30.f, "%.1f Hz");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("How many times per second to refresh the table.");

            ImGui::SameLine();
            if (ImGui::Button("Capture Now")) { capture(); sLastRefreshTime = now; }

            ImGui::SameLine();
            ImGui::TextDisabled("  %d voice(s)", (int)sCachedRows.size());
            if (sFreeze) { ImGui::SameLine(); ImGui::TextColored(ImVec4(1.f,0.7f,0.1f,1.f), "[FROZEN]"); }

            ImGui::Separator();

            if (sCachedRows.empty()) {
                ImGui::TextDisabled("No active voices.");
            } else if (ImGui::BeginTable("##notes", 10,
                    ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                    ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingFixedFit |
                    ImGuiTableFlags_ScrollX,
                    ImVec2(0.f, -1.f))) {

                ImGui::TableSetupScrollFreeze(0, 1);
                ImGui::TableSetupColumn("#",         ImGuiTableColumnFlags_WidthFixed,  22.f);
                ImGui::TableSetupColumn("Pl/Ch",     ImGuiTableColumnFlags_WidthFixed,  42.f);
                ImGui::TableSetupColumn("Sample",    ImGuiTableColumnFlags_WidthStretch);
                ImGui::TableSetupColumn("Codec",     ImGuiTableColumnFlags_WidthFixed,  76.f);
                ImGui::TableSetupColumn("Size",      ImGuiTableColumnFlags_WidthFixed,  64.f);
                ImGui::TableSetupColumn("Position",  ImGuiTableColumnFlags_WidthFixed, 120.f);
                ImGui::TableSetupColumn("Loop",      ImGuiTableColumnFlags_WidthFixed,  32.f);
                ImGui::TableSetupColumn("LoopStart", ImGuiTableColumnFlags_WidthFixed,  72.f);
                ImGui::TableSetupColumn("LoopEnd",   ImGuiTableColumnFlags_WidthFixed,  72.f);
                ImGui::TableSetupColumn("LoopCount", ImGuiTableColumnFlags_WidthFixed,  64.f);
                ImGui::TableHeadersRow();

                for (auto& r : sCachedRows) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%d", r.noteIdx);

                    ImGui::TableSetColumnIndex(1);
                    if (r.playerIdx >= 0 && r.channelIdx >= 0)
                        ImGui::Text("%d/%d", r.playerIdx, r.channelIdx);
                    else if (r.playerIdx >= 0)
                        ImGui::Text("%d/?", r.playerIdx);
                    else
                        ImGui::TextDisabled("?");

                    ImGui::TableSetColumnIndex(2);
                    if (r.isSynthetic) {
                        ImGui::TextDisabled("(synthetic)");
                    } else if (r.samplePath.empty()) {
                        ImGui::TextDisabled("(unknown)");
                    } else {
                        const char* slash = strrchr(r.samplePath.c_str(), '/');
                        ImGui::TextUnformatted(slash ? slash + 1 : r.samplePath.c_str());
                        if (ImGui::IsItemHovered()) {
                            ImGui::BeginTooltip();
                            ImGui::TextUnformatted(r.samplePath.c_str());
                            ImGui::EndTooltip();
                        }
                    }

                    ImGui::TableSetColumnIndex(3);
                    ImGui::TextUnformatted(CodecName(r.codec));

                    ImGui::TableSetColumnIndex(4);
                    ImGui::Text("%u B", r.sampleSize);

                    ImGui::TableSetColumnIndex(5);
                    if (r.hasLoop && r.loopEnd > r.loopStart) {
                        u32 len = r.loopEnd - r.loopStart;
                        s32 posInLoop = r.samplePos - (s32)r.loopStart;
                        float frac = (posInLoop >= 0) ? (float)posInLoop / (float)len : 0.f;
                        frac = frac < 0.f ? 0.f : frac > 1.f ? 1.f : frac;
                        char ov[32]; snprintf(ov, sizeof(ov), "%d", r.samplePos);
                        ImGui::PushStyleColor(ImGuiCol_PlotHistogram, ImVec4(0.2f,0.6f,1.f,1.f));
                        ImGui::ProgressBar(frac, ImVec2(110.f, 0.f), ov);
                        ImGui::PopStyleColor();
                    } else {
                        ImGui::Text("%d", r.samplePos);
                    }

                    ImGui::TableSetColumnIndex(6);
                    ImGui::TextColored(r.hasLoop ? ImVec4(0.4f,1.f,0.4f,1.f)
                                                 : ImVec4(0.5f,0.5f,0.5f,1.f),
                                       r.hasLoop ? "Y" : "N");

                    ImGui::TableSetColumnIndex(7);
                    if (r.hasLoop) ImGui::Text("%u", r.loopStart); else ImGui::TextDisabled("-");

                    ImGui::TableSetColumnIndex(8);
                    if (r.hasLoop) ImGui::Text("%u", r.loopEnd);   else ImGui::TextDisabled("-");

                    ImGui::TableSetColumnIndex(9);
                    if (r.hasLoop) {
                        if (r.loopCount == 0xFFFFFFFF)
                            ImGui::TextColored(ImVec4(0.4f,0.8f,1.f,1.f), "inf");
                        else
                            ImGui::Text("%u", r.loopCount);
                    } else {
                        ImGui::TextDisabled("-");
                    }
                }
                ImGui::EndTable();
            }
        }
        ImGui::End();
    }

    // ── Channel Stats ────────────────────────────────────────────────────────
    if (sShow_ChanStats) {
        ImGui::SetNextWindowSize(ImVec2(560, 400), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Channel Stats##sf64ad", &sShow_ChanStats)) {
            for (int pi = 0; pi < SEQ_PLAYER_MAX; pi++) {
                const SequencePlayer& p = gSeqPlayers[pi];

                int validCount = 0;
                for (int ci = 0; ci < SEQ_NUM_CHANNELS; ci++) {
                    if (IS_SEQUENCE_CHANNEL_VALID(p.channels[ci])) validCount++;
                }

                char hdr[80];
                snprintf(hdr, sizeof(hdr), "Player %d (%s) — %s###chpl%d",
                         pi, SeqPlayerName(pi),
                         p.enabled ? (validCount ? "channels" : "idle (no active channels)")
                                   : "disabled",
                         pi);
                if (!ImGui::TreeNodeEx(hdr, ImGuiTreeNodeFlags_DefaultOpen)) continue;

                if (validCount == 0) {
                    ImGui::TextDisabled("  No active channels.");
                    ImGui::TreePop();
                    continue;
                }

                if (ImGui::BeginTable("##chstats", 8,
                        ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                        ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_ScrollX)) {
                    ImGui::TableSetupColumn("Ch",       ImGuiTableColumnFlags_WidthFixed, 26.f);
                    ImGui::TableSetupColumn("En",       ImGuiTableColumnFlags_WidthFixed, 24.f);
                    ImGui::TableSetupColumn("Muted",    ImGuiTableColumnFlags_WidthFixed, 46.f);
                    ImGui::TableSetupColumn("Volume",   ImGuiTableColumnFlags_WidthFixed, 56.f);
                    ImGui::TableSetupColumn("Pan",      ImGuiTableColumnFlags_WidthFixed, 36.f);
                    ImGui::TableSetupColumn("Reverb",   ImGuiTableColumnFlags_WidthFixed, 50.f);
                    ImGui::TableSetupColumn("Inst/Wave",ImGuiTableColumnFlags_WidthFixed, 70.f);
                    ImGui::TableSetupColumn("Priority", ImGuiTableColumnFlags_WidthFixed, 54.f);
                    ImGui::TableHeadersRow();

                    for (int ci = 0; ci < SEQ_NUM_CHANNELS; ci++) {
                        const SequenceChannel* ch = p.channels[ci];
                        if (!IS_SEQUENCE_CHANNEL_VALID(ch)) continue;

                        ImGui::TableNextRow();
                        bool isMuted = SF64::gMutedChannels[ci].load(std::memory_order_relaxed);

                        if (isMuted)
                            ImGui::TableSetBgColor(ImGuiTableBgTarget_RowBg0,
                                                   IM_COL32(120, 30, 30, 80));

                        ImGui::TableSetColumnIndex(0); ImGui::Text("%d", ci);
                        ImGui::TableSetColumnIndex(1);
                        ImGui::TextColored(ch->enabled ? ImVec4(0.4f,1.f,0.4f,1.f)
                                                       : ImVec4(0.5f,0.5f,0.5f,1.f),
                                           ch->enabled ? "Y" : "N");
                        ImGui::TableSetColumnIndex(2);
                        ImGui::TextColored(isMuted ? ImVec4(1.f,0.4f,0.4f,1.f)
                                                  : ImVec4(0.5f,0.5f,0.5f,1.f),
                                           isMuted ? "YES" : "-");
                        ImGui::TableSetColumnIndex(3); ImGui::Text("%.3f", ch->volume);
                        ImGui::TableSetColumnIndex(4); ImGui::Text("%d",   ch->pan);
                        ImGui::TableSetColumnIndex(5); ImGui::Text("%d",   (int)ch->targetReverbVol);
                        ImGui::TableSetColumnIndex(6);
                        {
                            int iw = ch->instOrWave;
                            if (iw == 0)             ImGui::TextDisabled("none");
                            else if (iw >= 0x80)     ImGui::Text("wave %02X", iw);
                            else                     ImGui::Text("inst %d",   iw - 1);
                        }
                        ImGui::TableSetColumnIndex(7); ImGui::Text("%d", (int)ch->notePriority);
                    }
                    ImGui::EndTable();
                }
                ImGui::TreePop();
            }
        }
        ImGui::End();
    }

    // ── Polyphony ────────────────────────────────────────────────────────────
    if (sShow_Polyphony) {
        ImGui::SetNextWindowSize(ImVec2(380, 160), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Polyphony##sf64ad", &sShow_Polyphony)) {
            int activeCount    = 0;
            int syntheticCount = 0;
            if (gNotes && gNumNotes > 0) {
                for (int ni = 0; ni < gNumNotes; ni++) {
                    if (gNotes[ni].noteSubEu.bitField0.enabled) {
                        activeCount++;
                        if (gNotes[ni].noteSubEu.bitField1.isSyntheticWave)
                            syntheticCount++;
                    }
                }
            }

            ImGui::Text("Active voices:"); ImGui::SameLine();
            ImVec4 voiceCol = (activeCount == 0) ? ImVec4(0.5f,0.5f,0.5f,1.f)
                            : (activeCount < gNumNotes * 3 / 4) ? ImVec4(0.4f,1.f,0.4f,1.f)
                            :                                       ImVec4(1.f,0.7f,0.2f,1.f);
            ImGui::TextColored(voiceCol, "%d / %d", activeCount, gNumNotes);
            ImGui::SameLine(); ImGui::TextDisabled("(%d synthetic)", syntheticCount);

            {
                float frac = (gNumNotes > 0) ? (float)activeCount / (float)gNumNotes : 0.f;
                ImVec4 barCol = (frac < 0.6f) ? ImVec4(0.2f,0.8f,0.2f,1.f)
                              : (frac < 0.85f)? ImVec4(0.9f,0.75f,0.1f,1.f)
                              :                  ImVec4(0.9f,0.2f,0.2f,1.f);
                ImGui::PushStyleColor(ImGuiCol_PlotHistogram, barCol);
                char ov[32]; snprintf(ov, sizeof(ov), "%d / %d", activeCount, gNumNotes);
                ImGui::ProgressBar(frac, ImVec2(-1.f, 0.f), ov);
                ImGui::PopStyleColor();
            }

            auto listLen = [](const AudioListItem& head) -> int {
                int n = 0;
                for (const AudioListItem* it = head.next; it != nullptr && it != &head; it = it->next)
                    n++;
                return n;
            };
            int nDisabled  = listLen(gNoteFreeLists.disabled);
            int nDecaying  = listLen(gNoteFreeLists.decaying);
            int nReleasing = listLen(gNoteFreeLists.releasing);
            int nActive    = listLen(gNoteFreeLists.active);
            ImGui::Spacing();
            ImGui::TextDisabled("Free lists:");
            ImGui::SameLine();
            ImGui::Text("disabled=%d  decaying=%d  releasing=%d  active=%d",
                        nDisabled, nDecaying, nReleasing, nActive);
        }
        ImGui::End();
    }

    // ── Reverb ───────────────────────────────────────────────────────────────
    if (sShow_Reverb) {
        ImGui::SetNextWindowSize(ImVec2(340, 240), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Reverb##sf64ad", &sShow_Reverb)) {
            if (gNumSynthReverbs == 0) {
                ImGui::TextDisabled("No reverb units active.");
            } else {
                for (int ri = 0; ri < gNumSynthReverbs; ri++) {
                    const SynthesisReverb& rv = gSynthReverbs[ri];
                    char hdr[32]; snprintf(hdr, sizeof(hdr), "Reverb Unit %d###rv%d", ri, ri);
                    if (!ImGui::TreeNode(hdr)) continue;

                    ImGui::Columns(2, nullptr, false);
                    ImGui::SetColumnWidth(0, 160.f);

#define RROW(lbl, ...) do { ImGui::TextDisabled(lbl); ImGui::NextColumn(); ImGui::Text(__VA_ARGS__); ImGui::NextColumn(); } while(0)
                    RROW("Use Reverb",    "%s", rv.useReverb ? "yes" : "no");
                    RROW("Decay Ratio",   "0x%04X  (%.3f)", (unsigned)rv.decayRatio,
                                           rv.decayRatio / 65535.f);
                    RROW("Window Size",   "%u", (unsigned)rv.windowSize);
                    RROW("Downsample",    "x%u", (unsigned)rv.downsampleRate);
                    RROW("Leak R→L",      "0x%04X", (unsigned)rv.leakRtL);
                    RROW("Leak L→R",      "0x%04X", (unsigned)rv.leakLtR);
#undef RROW
                    ImGui::Columns(1);
                    ImGui::TreePop();
                }
            }
        }
        ImGui::End();
    }

    // ── Audio Heap ───────────────────────────────────────────────────────────
    if (sShow_AudioHeap) {
        ImGui::SetNextWindowSize(ImVec2(420, 300), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Audio Heap##sf64ad", &sShow_AudioHeap)) {
            struct { const char* name; const AudioAllocPool* pool; } pools[] = {
                { "Init Pool",               &gInitPool },
                { "Session Pool",            &gSessionPool },
                { "Misc Pool",               &gMiscPool },
                { "Cache Pool",              &gCachePool },
                { "Persistent Common",       &gPersistentCommonPool },
                { "Temporary Common",        &gTemporaryCommonPool },
                { "Persistent Sample Cache", &gPersistentSampleCache.pool },
                { "Temporary Sample Cache",  &gTemporarySampleCache.pool },
            };

            s32 totalUsed = 0, totalSize = 0;
            for (auto& e : pools) {
                if (e.pool->size <= 0) continue;
                ImGui::TextDisabled("%s", e.name);
                DrawPoolBar(e.name, *e.pool);
                totalUsed += (s32)(e.pool->curRamAddr - e.pool->startRamAddr);
                totalSize += e.pool->size;
            }

            ImGui::Separator();
            ImGui::Text("Total audio memory: %d KB / %d KB  (%.1f%%)",
                        totalUsed / 1024, totalSize / 1024,
                        totalSize > 0 ? 100.f * totalUsed / totalSize : 0.f);
        }
        ImGui::End();
    }

    // ── System ───────────────────────────────────────────────────────────────
    if (sShow_System) {
        ImGui::SetNextWindowSize(ImVec2(420, 320), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("System##sf64ad", &sShow_System)) {
            ImGui::Columns(2, nullptr, false);
            ImGui::SetColumnWidth(0, 160.f);

#define SROW(lbl, ...) do { ImGui::TextDisabled(lbl); ImGui::NextColumn(); ImGui::Text(__VA_ARGS__); ImGui::NextColumn(); } while(0)
            SROW("Audio Spec",       "%s (%d)", AudioSpecName(gAudioSpecId), (int)gAudioSpecId);
            SROW("Sound Mode",       "%s (%d)", SoundModeName(gAudioSoundMode), (int)gAudioSoundMode);
            SROW("Reset Step",       "%d  (0=idle)", (int)gAudioResetStep);
            SROW("Num Notes",        "%d", gNumNotes);
            SROW("Num Reverbs",      "%d", (int)gNumSynthReverbs);
            SROW("Refresh Rate",     "%d Hz", (int)gRefreshRate);
            SROW("Seq Ticks/Beat",   "%d", (int)gSeqTicksPerBeat);
            SROW("Max Tempo",        "%d", (int)gMaxTempo);
            SROW("Sampling Freq",    "%u Hz", (unsigned)gAudioBufferParams.samplingFrequency);
            SROW("AI Freq",          "%u Hz", (unsigned)gAudioBufferParams.aiSamplingFrequency);
            SROW("Samples/Frame",    "%d  (max %d  min %d)",
                                      (int)gAudioBufferParams.samplesPerFrameTarget,
                                      (int)gAudioBufferParams.maxAiBufferLength,
                                      (int)gAudioBufferParams.minAiBufferLength);
            SROW("Ticks/Update",     "%d", (int)gAudioBufferParams.ticksPerUpdate);
            SROW("Samples/Tick",     "%d  (max %d  min %d)",
                                      (int)gAudioBufferParams.samplesPerTick,
                                      (int)gAudioBufferParams.samplesPerTickMax,
                                      (int)gAudioBufferParams.samplesPerTickMin);
            SROW("Resample Rate",    "%.6f", gAudioBufferParams.resampleRate);
#undef SROW
            ImGui::Columns(1);
        }
        ImGui::End();
    }

    // ── Sample Info (Current Sample + Loop Info + Registered Samples) ────────
    if (sShow_SampleInfo) {
        ImGui::SetNextWindowSize(ImVec2(500, 560), ImGuiCond_FirstUseEver);
        if (ImGui::Begin("Sample Info##sf64ad", &sShow_SampleInfo)) {
            if (!gSnapshotReady.load(std::memory_order_acquire)) {
                ImGui::TextDisabled("No sample has played yet.");
            } else {
                AudioDebugSnapshot s = AudioDebug_GetSnapshot();
                const std::string& path = AudioDebug_GetSamplePath(s.sample);

                if (ImGui::CollapsingHeader("Current Sample", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::Columns(2, "sample_cols", false);
                    ImGui::SetColumnWidth(0, 160.f);

                    ImGui::TextDisabled("Path");         ImGui::NextColumn();
                    ImGui::TextUnformatted(path.empty() ? "(unknown)" : path.c_str());
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Ptr");          ImGui::NextColumn();
                    ImGui::Text("%p", static_cast<void*>(s.sample));
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Codec");        ImGui::NextColumn();
                    ImGui::Text("%s (%d)", CodecName(s.codec), s.codec);
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Size");         ImGui::NextColumn();
                    ImGui::Text("%u B  (%.1f KB)", s.sampleSize, s.sampleSize / 1024.f);
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Position");     ImGui::NextColumn();
                    {
                        float frac = (s.endPos > 0) ? (float)s.samplePos / (float)s.endPos : 0.f;
                        frac = frac < 0.f ? 0.f : frac > 1.f ? 1.f : frac;
                        char ov[64]; snprintf(ov, sizeof(ov), "%d / %u", s.samplePos, s.endPos);
                        ImGui::ProgressBar(frac, ImVec2(-1.f, 0.f), ov);
                    }
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Resample Rate"); ImGui::NextColumn();
                    float pitch = (float)s.resampleRate / 32768.f;
                    ImGui::Text("0x%04X  (%.4fx)", (unsigned)s.resampleRate, pitch);
                    ImGui::SameLine(); HelpMarker("Q15 fixed-point: 0x8000 = 1.0 (no pitch shift)");
                    ImGui::NextColumn();

                    ImGui::Columns(1);
                }

                if (ImGui::CollapsingHeader("Loop Info", ImGuiTreeNodeFlags_DefaultOpen)) {
                    ImGui::Columns(2, "loop_cols", false);
                    ImGui::SetColumnWidth(0, 160.f);

                    bool hasLoop = (s.loopCount != 0);

                    ImGui::TextDisabled("Has Loop");    ImGui::NextColumn();
                    if (hasLoop) ImGui::TextColored(ImVec4(0.4f,1.f,0.4f,1.f), "Yes");
                    else         ImGui::TextDisabled("No");
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Loop Start");  ImGui::NextColumn(); ImGui::Text("%u", s.loopStart);  ImGui::NextColumn();
                    ImGui::TextDisabled("Loop End");    ImGui::NextColumn(); ImGui::Text("%u", s.loopEnd);    ImGui::NextColumn();
                    ImGui::TextDisabled("Loop Length"); ImGui::NextColumn();
                    ImGui::Text("%u samples", (s.loopEnd > s.loopStart) ? s.loopEnd - s.loopStart : 0);
                    ImGui::NextColumn();

                    ImGui::TextDisabled("Loop Count");  ImGui::NextColumn();
                    if (s.loopCount == 0xFFFFFFFF)
                        ImGui::TextColored(ImVec4(0.4f,0.8f,1.f,1.f), "Infinite (0xFFFFFFFF)");
                    else
                        ImGui::Text("%u", s.loopCount);
                    ImGui::NextColumn();

                    if (hasLoop && s.loopEnd > s.loopStart) {
                        ImGui::TextDisabled("Loop Progress"); ImGui::NextColumn();
                        uint32_t len = s.loopEnd - s.loopStart;
                        int posInLoop = s.samplePos - (int)s.loopStart;
                        float frac = (posInLoop >= 0) ? (float)posInLoop / (float)len : 0.f;
                        frac = frac < 0.f ? 0.f : frac > 1.f ? 1.f : frac;
                        char ov[64]; snprintf(ov, sizeof(ov), "%d / %u", posInLoop, len);
                        ImGui::ProgressBar(frac, ImVec2(-1.f, 0.f), ov);
                        ImGui::NextColumn();
                    }

                    ImGui::Columns(1);
                }

                if (ImGui::CollapsingHeader("Registered Samples")) {
                    std::lock_guard<std::mutex> lk(gSamplePathMapMutex);
                    ImGui::Text("%zu sample(s) registered", gSamplePathMap.size());
                    ImGui::Separator();

                    if (ImGui::BeginTable("##samples", 2,
                            ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg |
                            ImGuiTableFlags_ScrollY | ImGuiTableFlags_SizingStretchProp,
                            ImVec2(0.f, 220.f))) {
                        ImGui::TableSetupScrollFreeze(0, 1);
                        ImGui::TableSetupColumn("Path", ImGuiTableColumnFlags_WidthStretch);
                        ImGui::TableSetupColumn("Ptr",  ImGuiTableColumnFlags_WidthFixed, 120.f);
                        ImGui::TableHeadersRow();

                        for (auto& [ptr, p] : gSamplePathMap) {
                            ImGui::TableNextRow();
                            ImGui::TableSetColumnIndex(0);
                            bool isActive = (ptr == s.sample);
                            if (isActive) ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f,1.f,0.4f,1.f));
                            ImGui::TextUnformatted(p.c_str());
                            if (isActive) ImGui::PopStyleColor();
                            ImGui::TableSetColumnIndex(1);
                            ImGui::Text("%p", static_cast<void*>(ptr));
                        }
                        ImGui::EndTable();
                    }
                }
            }
        }
        ImGui::End();
    }
}

} // namespace SF64
