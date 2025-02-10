#include "CosmeticEditor.h"
#include "port/ui/UIWidgets.h"
#include "macros.h"

std::vector<const char*> cosmeticEditorParentElements;


CosmeticEditorElement cosmeticEditorElements[COSMETIC_ELEMENT_MAX] = {
    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_FOX_RADAR_COLOR, "Radar (Star Fox)", "Fox", "Radar.Fox", 177, 242, 12, 255),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_FOX_RADAR_COLOR_DARK, "Radar (Star Fox)", "", "Radar.Fox_Dark", 89, 121, 6, 128, COSMETIC_ELEMENT_FOX_RADAR_COLOR, 0.5f),
    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_FALCO_RADAR_COLOR, "Radar (Star Fox)", "Falco", "Radar.Falco", 90, 90, 255, 255),
    // COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_FALCO_RADAR_COLOR_DARK, "Radar (Star Fox)", "Falco (Blink)", "Radar.Falco_Dark", 45, 45, 128, 128, COSMETIC_ELEMENT_FALCO_RADAR_COLOR, 0.5f),
    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_PEPPY_RADAR_COLOR, "Radar (Star Fox)", "Peppy", "Radar.Peppy", 255, 30, 0, 255),
    // COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_PEPPY_RADAR_COLOR_DARK, "Radar (Star Fox)", "Peppy (Blink)", "Radar.Peppy_Dark", 128, 15, 0, 128, COSMETIC_ELEMENT_PEPPY_RADAR_COLOR, 0.5f),
    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_SLIPPY_RADAR_COLOR, "Radar (Star Fox)", "Slippy", "Radar.Slippy", 0, 179, 67, 255),
    // COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_SLIPPY_RADAR_COLOR_DARK, "Radar (Star Fox)", "Slippy (Blink)", "Radar.Slippy_Dark", 0, 90, 34, 128, COSMETIC_ELEMENT_SLIPPY_RADAR_COLOR, 0.5f),

    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_WOLF_RADAR_COLOR, "Radar (Star Wolf)", "Wolf", "Radar.Wolf", 0, 0, 0, 255),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_LEON_RADAR_COLOR, "Radar (Star Wolf)", "Leon", "Radar.Leon", 0, 0, 0, 255, COSMETIC_ELEMENT_WOLF_RADAR_COLOR, 1.0f),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_PIGMA_RADAR_COLOR, "Radar (Star Wolf)", "Pigma", "Radar.Pigma", 0, 0, 0, 255, COSMETIC_ELEMENT_WOLF_RADAR_COLOR, 1.0f),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_ANDREW_RADAR_COLOR, "Radar (Star Wolf)", "Andrew", "Radar.Andrew", 0, 0, 0, 255, COSMETIC_ELEMENT_WOLF_RADAR_COLOR, 1.0f),

    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_ARWING_ENGINE_PLANET, "Arwing Engine Glows", "Atmosphere", "Engine.Arwing.Planet", 255, 0, 0, 255),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_ARWING_ENGINE_PLANET_SECONDARY, "Arwing Engine Glows", "", "Engine.Arwing.Planet_Secondary", 255, 255, 255, 255, COSMETIC_ELEMENT_ARWING_ENGINE_PLANET, 1.0f),
    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_ARWING_ENGINE_SPACE, "Arwing Engine Glows", "Space", "Engine.Arwing.Space", 0, 0, 255, 255),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_ARWING_ENGINE_SPACE_SECONDARY, "Arwing Engine Glows", "", "Engine.Arwing.Space_Secondary", 255, 255, 255, 255, COSMETIC_ELEMENT_ARWING_ENGINE_SPACE, 1.0f),

    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_WOLFEN_ENGINE_PLANET, "Wolfen Engine Glows", "Atmosphere", "Engine.Wolfen.Planet", 0, 255, 0, 255),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_WOLFEN_ENGINE_PLANET_SECONDARY, "Wolfen Engine Glows", "", "Engine.Wolfen.Planet_Secondary", 255, 255, 255, 255, COSMETIC_ELEMENT_WOLFEN_ENGINE_PLANET, 1.0f),
    COSMETIC_EDITOR_ELEMENT(COSMETIC_ELEMENT_WOLFEN_ENGINE_SPACE, "Wolfen Engine Glows", "Space", "Engine.Wolfen.Space", 255, 64, 0, 255),
    COSMETIC_EDITOR_DERIVED_ELEMENT(COSMETIC_ELEMENT_WOLFEN_ENGINE_SPACE_SECONDARY, "Wolfen Engine Glows", "", "Engine.Wolfen.Space_Secondary", 255, 255, 255, 255, COSMETIC_ELEMENT_WOLFEN_ENGINE_SPACE, 1.0f),

};

void CopyFloatArray(CosmeticEditorElementID id, float currentColor[4], bool isChanged) {
    if (isChanged) {
        Color_RGBA8 changedColor = CVarGetColor(cosmeticEditorElements[id].colorCvar, {});
        currentColor[0] = changedColor.r / 255.0f;
        currentColor[1] = changedColor.g / 255.0f;
        currentColor[2] = changedColor.b / 255.0f;
        currentColor[3] = changedColor.a / 255.0f;
    } else {
        currentColor[0] = cosmeticEditorElements[id].defaultR / 255.0f;
        currentColor[1] = cosmeticEditorElements[id].defaultG / 255.0f;
        currentColor[2] = cosmeticEditorElements[id].defaultB / 255.0f;
        currentColor[3] = cosmeticEditorElements[id].defaultA / 255.0f;
    }
};

Color_RGBA8 CosmeticEditor_getChangedColor(u8 r, u8 g, u8 b, u8 a, const char* cvar) {
    std::string cvarString = "gCosmetic.";
    cvarString += cvar;

    Color_RGBA8 returnedColor;

    if (CVarGetInteger((cvarString + ".Changed").c_str(), false)) {
        Color_RGBA8 changedColor = CVarGetColor((cvarString + ".Color").c_str(), {});
        float gammaBoost = CVarGetInteger("gGraphics.GammaMode", 1) == 1 ? 2.14f : 1.0f; // We want to not distort the color the user chooses. 
        returnedColor.r = static_cast<uint8_t>(ImPow(changedColor.r/256.f, (gammaBoost))*256.f);
        returnedColor.g = static_cast<uint8_t>(ImPow(changedColor.g/256.f, (gammaBoost))*256.f);
        returnedColor.b = static_cast<uint8_t>(ImPow(changedColor.b/256.f, (gammaBoost))*256.f);
        returnedColor.a = static_cast<uint8_t>(changedColor.a);
    } else {
        returnedColor.r = r;
        returnedColor.g = g;
        returnedColor.b = b;
        returnedColor.a = a;
    }

    return returnedColor;
}

extern "C" void gDPSetPrimColorWithOverride(Gfx* pkt, u8 m, u8 l, u8 r, u8 g, u8 b, u8 a, const char* cvar) {
    Color_RGBA8 setColor = CosmeticEditor_getChangedColor(r, g, b, a, cvar);
    gDPSetPrimColor(pkt, m, l, setColor.r, setColor.g, setColor.b, setColor.a);
}
extern "C" void gDPSetEnvColorWithOverride(Gfx* pkt, u8 r, u8 g, u8 b, u8 a, const char* cvar){
    Color_RGBA8 setColor = CosmeticEditor_getChangedColor(r, g, b, a, cvar);
    gDPSetEnvColor(pkt, setColor.r, setColor.g, setColor.b, setColor.a);
}

std::vector<CosmeticEditorElementID> GetAllDerivedFrom(CosmeticEditorElementID id)
{
    std::vector<CosmeticEditorElementID> Found;
    u8 i = 0;
    for (auto& entry : cosmeticEditorElements) {
        if (entry.derivedFrom == id)
        {
            Found.push_back(entry.id);
        }
    }
    
    return Found;
}

extern "C" const char* GetEngineGlowString(CosmeticEngineGlow glow)
{
    switch (glow){
        case COSMETIC_GLOW_ARWING:
        return "Arwing";
        case COSMETIC_GLOW_WOLFEN:
        return "Wolfen";
        default: //temp
        return "Arwing";
    }
}


extern "C" bool gCosmeticEngineGlowChanged(u8 levelType, CosmeticEngineGlow glowType){
    const char* glowString = GetEngineGlowString(glowType);
    const char* levelTypeString = levelType == 0 ? "Planet" : "Space";
    const char* suffix = "_Secondary";

    char cVarString[200]; 
    sprintf(cVarString, "gCosmetic.Engine.%s.%s.Changed", glowString, levelTypeString);

    char cVarStringSecondary[200];
    sprintf(cVarStringSecondary, "gCosmetic.Engine.%s.%s%s.Changed" , glowString, levelTypeString, suffix);
    
    return CVarGetInteger(cVarString, 0) || CVarGetInteger(cVarStringSecondary, 0); 
}
extern "C" Color_RGBA8 gCosmeticEngineGlowColor(u8 levelType, CosmeticEngineGlow glowType, bool secondary){
    const char* glowString = GetEngineGlowString(glowType);
    const char* levelTypeString = levelType == 0 ? "Planet" : "Space"; 
    const char* suffix = secondary ? "_Secondary" : "";
    char cVarString[200];
    sprintf(cVarString, "Engine.%s.%s%s" , glowString, levelTypeString, suffix);
    return CosmeticEditor_getChangedColor(255,0,255, 255, cVarString); //Magenta to detect issues
}
void CosmeticEditorRandomizeElement(CosmeticEditorElement id) {
    Color_RGBA8 colorSelected;
    colorSelected.r = static_cast<uint8_t>((rand() % 256) * 255.0f);
    colorSelected.g = static_cast<uint8_t>((rand() % 256) * 255.0f);
    colorSelected.b = static_cast<uint8_t>((rand() % 256) * 255.0f);
    colorSelected.a = static_cast<uint8_t>((rand() % 256) * 255.0f);

    CVarSetColor(id.colorCvar, colorSelected);
    CVarSetInteger(id.colorChangedCvar, true);
}

bool CosmeticEditorCompareColors(Color_RGBA8 first, Color_RGBA8 second){
    return (first.r == second.r && first.g == second.g && first.b == second.b && first.a == second.a);
}

void CosmeticEditorCalculateDerivedElement(CosmeticEditorElement entry) {
    if (entry.derivedFrom == COSMETIC_ELEMENT_NONE) {
        return;
    }
    CosmeticEditorElement originalEntry = cosmeticEditorElements[entry.derivedFrom];
    Color_RGBA8 myDefault = {entry.defaultR, entry.defaultG, entry.defaultB, entry.defaultA};
    Color_RGBA8 original = CVarGetColor(originalEntry.colorCvar, {originalEntry.defaultR, originalEntry.defaultG, originalEntry.defaultB, originalEntry.defaultA});
    Color_RGBA8 result;
    result.r = static_cast<uint8_t>(CLAMP(original.r * entry.multiplier, 0, 255));
    result.g = static_cast<uint8_t>(CLAMP(original.g * entry.multiplier, 0, 255));
    result.b = static_cast<uint8_t>(CLAMP(original.b * entry.multiplier, 0, 255));
    result.a = static_cast<uint8_t>(CLAMP(original.a * entry.multiplier, 0, 255));

    CVarSetColor(entry.colorCvar, result);
    CVarSetInteger(entry.colorChangedCvar, CVarGetInteger(originalEntry.colorChangedCvar, 0));
}


void CosmeticEditorRandomizeAllElements() {
    for (auto& element : cosmeticEditorElements) {
        CosmeticEditorRandomizeElement(element);
    }
}

void CosmeticEditorResetAllElements() {
    for (auto& element : cosmeticEditorElements) {
        CVarClear(element.colorCvar);
        CVarClear(element.colorChangedCvar);
    }
}

void CosmeticEditorCalculateAllDerived() {
    for (auto& element : cosmeticEditorElements) {
        if (element.derivedFrom != COSMETIC_ELEMENT_NONE){
            CosmeticEditorCalculateDerivedElement(element);
        }
    }
}
void CosmeticEditorDrawColorTab() {
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.2f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.1f));
    std::string resetAllText = ICON_FA_UNDO;
    resetAllText += " All";
    std::string randomAllText = ICON_FA_RECYCLE;
    randomAllText += " All";
    std::string calculateAllText = ICON_FA_ARROW_DOWN;
    calculateAllText += " All";
    if (ImGui::Button(resetAllText.c_str())) {
        CosmeticEditorResetAllElements();
    }
    UIWidgets::Tooltip("Resets All Elements to their Defaults");
    ImGui::SameLine();
    if (ImGui::Button(randomAllText.c_str())) {
        CosmeticEditorRandomizeAllElements();
    }
    ImGui::SameLine();
    if (ImGui::Button(calculateAllText.c_str())) {
        CosmeticEditorCalculateAllDerived();
    }
    UIWidgets::Tooltip("Randomizes All Elements");
    for (auto& parent : cosmeticEditorParentElements) {
        ImGui::SeparatorText(parent);
        ImGui::BeginTable(parent, 2);
        ImGui::TableSetupColumn("Element Name", ImGuiTableColumnFlags_WidthStretch, 1.4f);
        ImGui::TableSetupColumn("Options", ImGuiTableColumnFlags_WidthStretch, 2.0f);
        for (auto& entry : cosmeticEditorElements) {
            if (parent != entry.parentName) {
                continue;
            }
            bool derived = entry.derivedFrom != COSMETIC_ELEMENT_NONE;
            if (entry.name == "" && derived) { //Is a subEntry
                continue;
            }
            
            float currentColor[4];

            ImGui::PushID(entry.id);
            ImGui::TableNextColumn();
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() +
                                 ((ImGui::GetFrameHeight() - (ImGui::CalcTextSize(entry.name).y)) / 2.0f));
            ImGui::Text(entry.name);
            ImGui::TableNextColumn();
            CopyFloatArray(entry.id, currentColor, CVarGetInteger(entry.colorChangedCvar, false));
            bool colorChanged =
                ImGui::ColorEdit4("Color", currentColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);

            std::vector<CosmeticEditorElementID> subEntries = GetAllDerivedFrom(entry.id);
            bool subEntryChanged = false;
            for (int i = 0; i < subEntries.size(); i++){

                float currentSecondaryColor[4];
                ImGui::SameLine();
                CosmeticEditorElement subEntry = cosmeticEditorElements[subEntries[i]];
                if (subEntry.name != "") { 
                    continue;
                }
                CopyFloatArray(subEntry.id, currentSecondaryColor, CVarGetInteger(subEntry.colorChangedCvar, false));
                bool secondaryColorChanged =
                    ImGui::ColorEdit4("SubColor", currentSecondaryColor, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
                if (secondaryColorChanged || colorChanged) {
                    subEntryChanged = true;
                    Color_RGBA8 colorSelected;
                    colorSelected.r = static_cast<uint8_t>(currentSecondaryColor[0] * 255.0f);
                    colorSelected.g = static_cast<uint8_t>(currentSecondaryColor[1] * 255.0f);
                    colorSelected.b = static_cast<uint8_t>(currentSecondaryColor[2] * 255.0f);
                    colorSelected.a = static_cast<uint8_t>(currentSecondaryColor[3] * 255.0f);

                    CVarSetColor(subEntry.colorCvar, colorSelected);
                    CVarSetInteger(subEntry.colorChangedCvar, true);
                }
            }

            if (colorChanged || subEntryChanged) {
                Color_RGBA8 colorSelected;
                colorSelected.r = static_cast<uint8_t>(currentColor[0] * 255.0f);
                colorSelected.g = static_cast<uint8_t>(currentColor[1] * 255.0f);
                colorSelected.b = static_cast<uint8_t>(currentColor[2] * 255.0f);
                colorSelected.a = static_cast<uint8_t>(currentColor[3] * 255.0f);

                CVarSetColor(entry.colorCvar, colorSelected);
                CVarSetInteger(entry.colorChangedCvar, true);
            }

            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_UNDO, ImVec2(27.0f, 27.0f))) {
                CVarClear(entry.colorCvar);
                CVarClear(entry.colorChangedCvar);
                for (int i = 0; i < subEntries.size(); i++){
                    CosmeticEditorElement subEntry = cosmeticEditorElements[subEntries[i]];
                    CVarClear(subEntry.colorCvar);
                    CVarClear(subEntry.colorChangedCvar);
                }
            }
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_RECYCLE, ImVec2(27.0f, 27.0f))) {
                CosmeticEditorRandomizeElement(entry);
            }
            ImGui::SameLine();
            ImGui::TextColored(CVarGetInteger(entry.colorChangedCvar, 0) ? UIWidgets::Colors::LightGreen
                                                                         : UIWidgets::Colors::Gray,
                               CVarGetInteger(entry.colorChangedCvar, 0) ? "Modified" : "Default");
            if (derived) {
                ImGui::SameLine();
                if (ImGui::Button(ICON_FA_ARROW_DOWN, ImVec2(27.0f, 27.0f))) {
                    CosmeticEditorCalculateDerivedElement(entry);
            }
            }
            ImGui::PopID();
        }
        ImGui::EndTable();
    }
    ImGui::PopStyleColor(3);
}

// Tab Bar is unused until other options are available.
void CosmeticEditorDrawTabBar() {
    ImGui::BeginTabBar("Cosmetic Tab Bar");
    if (ImGui::BeginTabItem("Colors")) {
        CosmeticEditorDrawColorTab();
        ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
}

namespace CosmeticEditor {
void CosmeticEditorWindow::DrawElement() {
    CosmeticEditorDrawColorTab();
}

void CosmeticEditorWindow::InitElement() {
    cosmeticEditorParentElements.clear();
    for (auto& insert : cosmeticEditorElements) {
        if (std::find(cosmeticEditorParentElements.begin(), cosmeticEditorParentElements.end(), insert.parentName) !=
            cosmeticEditorParentElements.end()) {
            continue;
        }
        cosmeticEditorParentElements.push_back(insert.parentName);
    }
}
}