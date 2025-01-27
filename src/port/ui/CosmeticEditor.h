#include <libultraship/libultraship.h>

#ifdef __cplusplus

namespace CosmeticEditor {
class CosmeticEditorWindow : public Ship::GuiWindow {
  public:
    using GuiWindow::GuiWindow;

    void InitElement() override;
    void DrawElement() override;
    void UpdateElement() override{};
};
}
extern "C" {
#endif //__cplusplus

void gDPSetPrimColorWithOverride(Gfx* pkt, u8 m, u8 l, u8 r, u8 g, u8 b, u8 a, const char* cvar);

Color_RGBA8 CosmeticEditor_getChangedColor(u8 r, u8 g, u8 b, u8 a, const char* cvar);

typedef enum CosmeticEditorElementID{
    COSMETIC_ELEMENT_NONE = -1,
    COSMETIC_ELEMENT_FOX_RADAR_COLOR,
    COSMETIC_ELEMENT_FOX_RADAR_COLOR_DARK,
    COSMETIC_ELEMENT_FALCO_RADAR_COLOR,
    // COSMETIC_ELEMENT_FALCO_RADAR_COLOR_DARK, //These will only be useful when we have Multiplayer
    COSMETIC_ELEMENT_PEPPY_RADAR_COLOR,
    // COSMETIC_ELEMENT_PEPPY_RADAR_COLOR_DARK,
    COSMETIC_ELEMENT_SLIPPY_RADAR_COLOR,
    // COSMETIC_ELEMENT_SLIPPY_RADAR_COLOR_DARK,

    COSMETIC_ELEMENT_WOLF_RADAR_COLOR,
    COSMETIC_ELEMENT_LEON_RADAR_COLOR,
    COSMETIC_ELEMENT_PIGMA_RADAR_COLOR,
    COSMETIC_ELEMENT_ANDREW_RADAR_COLOR,
    COSMETIC_ELEMENT_MAX
} CosmeticEditorElementID;

typedef struct {
    CosmeticEditorElementID id;
    const char* parentName;
    const char* name;
    uint8_t defaultR;
    uint8_t defaultG;
    uint8_t defaultB;
    uint8_t defaultA;
    CosmeticEditorElementID derivedFrom;
    float multiplier;
    const char* colorCvar;
    const char* colorChangedCvar;
} CosmeticEditorElement;

#define COSMETIC_EDITOR_ELEMENT(id, parentName, name, cvar, defaultR, defaultG, defaultB, defaultA)     \
    {                                                                                                   \
        (CosmeticEditorElementID)id, parentName, name, defaultR, defaultG, defaultB, defaultA, COSMETIC_ELEMENT_NONE, 0.0f, "gCosmetic." cvar ".Color",   \
            "gCosmetic." cvar ".Changed"                                                                \
    }

#define COSMETIC_EDITOR_DERIVED_ELEMENT(id, parentName, name, cvar, defaultR, defaultG, defaultB, defaultA, derivedFrom, multiplier)\
    {                                                                                                                               \
        (CosmeticEditorElementID)id, parentName, name, defaultR, defaultG, defaultB, defaultA, derivedFrom, multiplier, "gCosmetic." cvar ".Color",          \
            "gCosmetic." cvar ".Changed"                                                                                            \
    }
#ifdef __cplusplus
}
#endif //__cplusplus