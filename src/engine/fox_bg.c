#include "global.h"
#include "assets/ast_katina.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_bg_planet.h"
#include "assets/ast_versus.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_training.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_sector_z.h"
#include "assets/ast_aquas.h"
#include "assets/ast_bolse.h"
#include "assets/ast_titania.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_andross.h"
#include "assets/ast_solar.h"
#include "assets/ast_warp_zone.h"
#include "assets/ast_area_6.h"
#include "assets/ast_zoness.h"

#include "prevent_bss_reordering2.h"
#include "port/interpolation/FrameInterpolation.h"
// #include "prevent_bss_reordering3.h"

#include "water_effect.inc"

#include <libultra/gbi.h>

f32 gWarpZoneBgAlpha;
u8 D_bg_8015F964;  // related to water surfaces
f32 D_bg_8015F968; // heat shimmer effect for SO and TI?
f32 D_bg_8015F96C; // unused. some sort of starfield motion blur for meteo?
f32 D_bg_8015F970; // these next few vars seem to be related to aquas surface
s32 D_bg_8015F974;
s32 D_bg_8015F978;
s32 D_bg_8015F97C;
s32 D_bg_8015F980;
f32 D_bg_8015F984;             // related to scale of venom in area 6
UNK_TYPE D_bg_8015F988[0x683]; // Unused? Close to being [13][0x80]
f32 gAndrossUnkBrightness;     // can be static

f32 gAndrossUnkAlpha = 0.0f;
u16 gBolseDynamicGround = true;
s32 D_bg_800C9C38 = 0; // unused?

static f32 sGroundPositions360x_FIX[] = {
    // center pieces : 0 - 3
    5999.0f,         -5999.0f, 5999.0f, -5999.0f,
    5999.0f * 3.0f,  // lower right corner piece : 4
    5999.0f * 1.0f,  // lower middle left piece : 5
    -5999.0f * 1.0f, // lower middle right piece : 6
    -5999.0f * 3.0f, // lower left corner piece : 7
    -5999.0f * 3.0f, // upper left corner piece : 8
    -5999.0f * 1.0f, // uppder middle left piece : 9
    +5999.0f * 1.0f, // Upper middle right pieceX : 10
    +5999.0f * 3.0f, // upper right corner piece : 11
    -5999.0f * 3.0f, // side upper left piece : 12
    -5999.0f * 3.0f, // side lower left piece : 13
    +5999.0f * 3.0f, // side upper right piece: 14
    +5999.0f * 3.0f, // side lower right piece : 15
};

static f32 sGroundPositions360z_FIX[] = {
    // center pieces : 0 - 3
    5999.0f,         5999.0f, -5999.0f, -5999.0f,
    5999.0f * 3.0f,  // lower right corner piece : 4
    5999.0f * 3.0f,  // lower middle left piece : 5
    +5999.0f * 3.0f, // lower middle right piece : 6
    5999.0f * 3.0f,  // lower left corner piece : 7
    -5999.0f * 3.0f, // upper left corner piece : 8
    -5999.0f * 3.0f, // uppder middle left piece : 9
    -5999.0f * 3.0f, // Upper middle right pieceX : 10
    -5999.0f * 3.0f, // upper right corner piece : 11
    -5999.0f * 1.0f, // side upper left piece : 12
    5999.0f * 1.0f,  // side lower left piece : 13
    -5999.0f * 1.0f, // side upper right piece: 14
    5999.0f * 1.0f,  // side lower right piece : 15
};

u16 gStarColors[16] = {
    0x108B, 0x108B, 0x1087, 0x1089, 0x39FF, 0x190D, 0x108B, 0x1089,
    0x294B, 0x18DF, 0x294B, 0x1085, 0x39FF, 0x108B, 0x18CD, 0x108B,
};
Gfx* sSunDLs[13] = {
    aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, D_BG_PLANET_20112C0,
    aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, D_BG_PLANET_20112C0,
    aBallDL,
};
Gfx* sKaSunDLs[13] = {
    aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL, aBallDL,
};
f32 sSunShifts[13] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 10.0f, 13.0f, 20.0f, 35.0f, 40.0f, 50.0f, 50.0f, 70.0f,
};
f32 sKaSunShifts[13] = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 10.0f, 16.0f, 20.0f, 30.0f, 45.0f, 60.0f, 70.0f,
};
f32 sSunScales[13] = {
    0.7f, 1.0f, 1.2f, 1.4f, 1.8f, 2.0f, 0.4f, 0.6f, 0.8f, 1.7f, 0.8f, 4.0f, 2.0f,
};
f32 sKaSunScales[13] = {
    0.525f, 0.75f, 0.90000004f, 1.05f, 1.3499999f, 0.15f, 0.25f, 0.35f, 1.0f, 0.6f, 0.35f, 0.9f, 1.0f,
};
Color_RGB8 sSunColors[13] = {
    { 255, 255, 255 }, { 255, 255, 192 }, { 255, 255, 128 }, { 255, 255, 96 }, { 255, 255, 64 },
    { 255, 255, 64 },  { 255, 255, 64 },  { 255, 255, 64 },  { 255, 255, 64 }, { 255, 255, 64 },
    { 255, 255, 64 },  { 255, 255, 64 },  { 255, 255, 64 },
};
Color_RGB8 sKaSunColors[13] = {
    { 255, 128, 64 },  { 255, 128, 64 }, { 255, 128, 64 }, { 255, 128, 64 }, { 255, 128, 64 },
    { 255, 255, 64 },  { 255, 128, 64 }, { 255, 128, 64 }, { 255, 255, 64 }, { 128, 128, 128 },
    { 128, 128, 255 }, { 255, 255, 64 }, { 255, 128, 64 },
};
s32 sSunAlphas[13] = {
    255, 80, 64, 48, 32, 12, 32, 44, 32, 42, 36, 12, 38,
};
s32 sKaSunAlphas[13] = {
    80, 60, 40, 20, 10, 20, 30, 20, 15, 30, 20, 27, 20,
};
s32 sSunGlareAlphaStep[2] = { 10, 4 };
s32 sSunGlareMaxAlpha[2] = { 140, 40 };
f32 sLensFlareAlphaMod[2] = { 1.2f, 0.5f };
f32 sGroundPositions360x[4] = {
    6000.0f,
    -6000.0f,
    6000.0f,
    -6000.0f,
};
f32 sGroundPositions360z[4] = {
    6000.0f,
    6000.0f,
    -6000.0f,
    -6000.0f,
};

// Declare global variables for screen dimensions
float gCurrentScreenWidth = 320.0f * 3;  // Default width
float gCurrentScreenHeight = 240.0f * 3; // Default height

// Custom floating-point modulo function (replaces fmodf)
float FloatMod(float a, float b) {
    float result = a - ((int) (a / b)) * b;
    if (result < 0.0f) {
        result += b;
    }
    return result;
}

// Define a single 1x1 star as two triangles
static Vtx starVerts[4] = {
    // Format: VTX(x, y, z, s, t, r, g, b, a)
    VTX(0, 0, 0, 0, 0, 255, 255, 255, 255), // Bottom-left
    VTX(0, 1, 0, 0, 0, 255, 255, 255, 255), // Top-left
    VTX(1, 0, 0, 0, 0, 255, 255, 255, 255), // Bottom-right
    VTX(1, 1, 0, 0, 0, 255, 255, 255, 255), // Top-right
};

// Display list to render the two triangles forming the star quad
static Gfx starDL[] = {
    gsSPVertex(starVerts, ARRAY_COUNT(starVerts), 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 2, 3, 0),
    gsSPEndDisplayList(),
};

// Display list to render the two triangles forming the partial star quad
static Gfx starDLPartial[] = {
    gsSPVertex(starVerts, ARRAY_COUNT(starVerts), 0),
    gsSP2Triangles(0, 1, 2, 0, 1, 2, 3, 0),
    gsSPEndDisplayList(),
};

// Setup render state for stars
static Gfx starSetupDL[] = {
    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_OFF), // Disable texturing
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR | G_CULL_BACK |
                          G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_PRIMITIVE, G_CC_PRIMITIVE), // Use primitive color
    gsDPSetOtherMode(G_AD_NOTPATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_OPA_SURF | G_RM_OPA_SURF2),
    gsSPEndDisplayList(),
};

// New global variables for storing the previoous positions
f32 gStarPrevX[3000];
f32 gStarPrevY[3000];

// @port: Starfield drawn with triangles, re-engineered by @Tharo & @TheBoy181
void Background_DrawStarfield(void) {
    f32 by;
    f32 bx;
    s32 i;
    s32 starCount;
    f32 zCos;
    f32 zSin;
    f32 xField;
    f32 yField;
    f32* xStar;
    f32* yStar;
    u32* color;
    float currentScreenWidth;
    float currentScreenHeight;
    float starfieldWidth;
    float starfieldHeight;
    float vx;
    float vy;
    const float STAR_MARGIN = 40.0f; // Margin to hide seam stars

    // Set projection to orthographic before drawing stars
    Lib_InitOrtho(&gMasterDisp);

    gSPDisplayList(gMasterDisp++, starSetupDL);

    // Get current screen dimensions
    currentScreenWidth = gCurrentScreenWidth;
    currentScreenHeight = gCurrentScreenHeight;
    starfieldWidth = 1.0f * currentScreenWidth;
    starfieldHeight = 1.0f * currentScreenHeight;

    starCount = gStarCount;

    if (starCount != 0) {
        // Wrapping logic for starfield positions
        if (gStarfieldX >= starfieldWidth) {
            gStarfieldX -= starfieldWidth;
        }
        if (gStarfieldY >= starfieldHeight) {
            gStarfieldY -= starfieldHeight;
        }
        if (gStarfieldX < 0.0f) {
            gStarfieldX += starfieldWidth;
        }
        if (gStarfieldY < 0.0f) {
            gStarfieldY += starfieldHeight;
        }
        xField = gStarfieldX;
        yField = gStarfieldY;

        xStar = gStarOffsetsX;
        yStar = gStarOffsetsY;
        color = gStarFillColors;

        if (gGameState != GSTATE_PLAY) {
            starCount = 1000;
        }

        starCount = starCount * 3; // Adjust multiplier as needed

        zCos = __cosf(gStarfieldRoll);
        zSin = __sinf(gStarfieldRoll);

        if (CVarGetInteger("gDisableStarsInterpolation", 0) == 1) {
            FrameInterpolation_ShouldInterpolateFrame(false);
        }

        float originalWidth = currentScreenWidth / 3;
        float originalAspect = originalWidth / (currentScreenHeight / 3);
        float renderMaskWidth = originalWidth * (OTRGetAspectRatio() / originalAspect);
        float marginX = (currentScreenWidth - renderMaskWidth) / 2;
        float renderMaskHeight = currentScreenHeight / 3;

        for (i = 0; i < starCount; i++, yStar++, xStar++, color++) {
            // Adjust star positions with field offsets
            bx = *xStar + xField;
            by = *yStar + yField;

            // Wrapping logic for individual stars along X-axis
            if (bx >= starfieldWidth) {
                bx -= starfieldWidth;
            }
            if (bx < 0.0f) {
                bx += starfieldWidth;
            }

            // Wrapping logic for individual stars along Y-axis
            if (by >= starfieldHeight) {
                by -= starfieldHeight;
            }
            if (by < 0.0f) {
                by += starfieldHeight;
            }

            // Center the positions
            bx -= starfieldWidth / 2.0f;
            by -= starfieldHeight / 2.0f;

            // Apply rotation
            vx = (zCos * bx) + (zSin * by) + currentScreenWidth / 2.0f;
            vy = (-zSin * bx) + (zCos * by) + currentScreenHeight / 2.0f;

            // Check if the star is within the visible screen area with margin
            if (vx >= (marginX - STAR_MARGIN) && vx <= (marginX + renderMaskWidth + STAR_MARGIN) &&
                vy >= (renderMaskHeight - STAR_MARGIN) && vy <= ((renderMaskHeight * 2) + STAR_MARGIN)) {

                bool skipInterpolation = (fabsf(vx - gStarPrevX[i]) > (marginX + renderMaskWidth) / 2.0f) ||
                                         (fabsf(vy - gStarPrevY[i]) > ((renderMaskHeight * 2)) / 2.0f);

                if (skipInterpolation) {
                    // @port Skip interpolation
                    FrameInterpolation_ShouldInterpolateFrame(false);
                } else {
                    FrameInterpolation_RecordOpenChild("Starfield", i);
                    FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                }

                // Translate to (vx, vy) in ortho coordinates
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, vx - (currentScreenWidth / 2.0f), -(vy - (currentScreenHeight / 2.0f)),
                                 0.0f, MTXF_NEW);
                Matrix_SetGfxMtx(&gMasterDisp);

                // Convert color from fill color (assuming RGB5A1) to RGBA8
                u8 r = ((*color >> 11) & 0x1F);
                r = (r << 3) | (r >> 2); // Convert 5-bit to 8-bit
                u8 g = ((*color >> 6) & 0x1F);
                g = (g << 3) | (g >> 2); // Convert 5-bit to 8-bit
                u8 b = ((*color >> 1) & 0x1F);
                b = (b << 3) | (b >> 2); // Convert 5-bit to 8-bit
                u8 a = 255;              // Fully opaque

                gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, a);

                // Draw the star using the predefined display list
                gSPDisplayList(gMasterDisp++, starDL);
                Matrix_Pop(&gGfxMatrix);

                if (skipInterpolation) {
                    // @port Re-enable Interpolation if it was skipped
                    FrameInterpolation_ShouldInterpolateFrame(true);
                } else {
                    FrameInterpolation_RecordCloseChild();
                }

                gStarPrevX[i] = vx;
                gStarPrevY[i] = vy;
            }
        }

        if (CVarGetInteger("gDisableStarsInterpolation", 0) == 1) {
            FrameInterpolation_ShouldInterpolateFrame(true);
        }
    }

    // Restore original perspective after drawing stars
    Lib_InitPerspective(&gMasterDisp);

    // Finalize rendering state
    gDPPipeSync(gMasterDisp++);
    gDPSetColorDither(gMasterDisp++, G_CD_MAGICSQ);
}

void Background_DrawPartialStarfield(s32 yMin, s32 yMax) { // Stars that are in the Epilogue
    f32 by;
    f32 bx;
    s16 vy;
    s16 vx;
    s32 i;
    s32 var_s2;
    f32 cos;
    f32 sin;
    f32 spf68;
    f32 spf64;
    f32* sp60;
    f32* sp5C;
    u32* sp58;

    // Get current screen dimensions
    float currentScreenWidth = gCurrentScreenWidth;
    float currentScreenHeight = gCurrentScreenHeight;
    float starfieldWidth = 1.0f * currentScreenWidth;
    float starfieldHeight = 1.0f * currentScreenHeight;

    // Graphics pipeline setup
    gDPPipeSync(gMasterDisp++);
    gDPSetCycleType(gMasterDisp++, G_CYC_FILL);
    gDPSetCombineMode(gMasterDisp++, G_CC_SHADE, G_CC_SHADE);
    gDPSetRenderMode(gMasterDisp++, G_RM_OPA_SURF, G_RM_OPA_SURF2);

    if (gStarfieldX >= 1.5f * currentScreenWidth) {
        gStarfieldX -= 1.5f * currentScreenWidth;
    }
    if (gStarfieldY >= 1.5f * currentScreenHeight) {
        gStarfieldY -= 1.5f * currentScreenHeight;
    }
    if (gStarfieldX < 0.0f) {
        gStarfieldX += 1.5f * currentScreenWidth;
    }
    if (gStarfieldY < 0.0f) {
        gStarfieldY += 1.5f * currentScreenHeight;
    }

    spf68 = gStarfieldX;
    spf64 = gStarfieldY;

    sp60 = gStarOffsetsX;
    sp5C = gStarOffsetsY;
    sp58 = gStarFillColors;
    var_s2 = 500;

    cos = __cosf(gStarfieldRoll);
    sin = __sinf(gStarfieldRoll);

    for (i = 0; i < var_s2; i++, sp5C++, sp60++, sp58++) {
        bx = *sp60 + spf68;
        by = *sp5C + spf64;
        if (bx >= starfieldWidth * 1.25f) {
            bx -= 1.5f * starfieldWidth;
        }
        bx -= starfieldWidth / 2.0f;
        if (by >= starfieldHeight * 1.25f) {
            by -= 1.5f * starfieldHeight;
        }
        by -= starfieldHeight / 2.0f;

        // Apply rotation
        vx = (cos * bx) + (sin * by) + currentScreenWidth / 2.0f;
        vy = (-sin * bx) + (cos * by) + currentScreenHeight / 2.0f;

        // Check if the star is within the visible screen area
        if ((vx >= 0) && (vx < currentScreenWidth) && (yMin < vy) && (vy < yMax)) {
            // Tag the transform. Assuming TAG_STARFIELD is a defined base tag value
            FrameInterpolation_RecordOpenChild("SmallStarfield", i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            // Translate to (vx, vy) in ortho coordinates
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, vx - (currentScreenWidth / 2.0f), -(vy - (currentScreenHeight / 2.0f)), 0.0f,
                             MTXF_NEW);
            Matrix_SetGfxMtx(&gMasterDisp);
            Matrix_Pop(&gGfxMatrix);

            // Convert color from fill color (assuming RGB5A1) to RGBA8
            u8 r = ((*sp58 >> 11) & 0x1F);
            r = (r << 3) | (r >> 2); // Convert 5-bit to 8-bit
            u8 g = ((*sp58 >> 6) & 0x1F);
            g = (g << 3) | (g >> 2); // Convert 5-bit to 8-bit
            u8 b = ((*sp58 >> 1) & 0x1F);
            b = (b << 3) | (b >> 2); // Convert 5-bit to 8-bit
            u8 a = 255;              // Fully opaque

            gDPSetPrimColor(gMasterDisp++, 0, 0, r, g, b, a);

            // Draw the star using the predefined display list
            gSPDisplayList(gMasterDisp++, starDLPartial);

            // Pop the transform id
            FrameInterpolation_RecordCloseChild();
        }
    }
    gDPPipeSync(gMasterDisp++);
    gDPSetColorDither(gMasterDisp++, G_CD_MAGICSQ);
}

void func_bg_8003E1E0(void) {
}
#if 0
extern f32 gTestVarF;
#endif
// TODO: use SCREEN_WIDTH and _HEIGHT

static f32 bgPrevPosX = 0.0f;
static u8 skipInterpolation;
void Background_DrawBackdrop(void) {
    f32 sp12C;
    f32 sp13C;
    f32 bgXpos;
    f32 bgYpos;
    f32 sp130;
    f32 camYawDeg;
    f32 scale;
    s32 i;
    u8 levelType;
    s32 levelId;

    if (gDrawBackdrop == 0) {
        return;
    }

    levelType = gLevelType;
    if ((gCurrentLevel == LEVEL_VERSUS) && (gVersusStage == VS_STAGE_SECTOR_Z)) {
        levelType = LEVELTYPE_PLANET;
    }
    if (gCurrentLevel == LEVEL_TRAINING) {
        levelType = LEVELTYPE_SPACE;
    }
    levelId = gCurrentLevel;

    Matrix_Push(&gGfxMatrix);

    if (gFovYMode == 2) {
        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.0f, MTXF_APPLY);
    }

    switch (levelType) {
        case LEVELTYPE_PLANET:
            RCP_SetupDL(&gMasterDisp, SETUPDL_17);
            switch (levelId) {
                case LEVEL_FORTUNA:
                case LEVEL_KATINA:
                case LEVEL_VENOM_2:
                case LEVEL_VERSUS:
                    bgYpos = (gPlayer[gPlayerNum].camPitch * -6000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.4f);
                    sp13C = Math_ModF(Math_RadToDeg(gPlayer[gPlayerNum].camYaw) * (-7280.0f / 360.0f) * 5.0f, 7280.0f);
                    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);

                    // Start by translating the matrix to the far left position
                    Matrix_Translate(gGfxMatrix, sp13C - 14560.0f, -2000.0f + bgYpos, -6000.0f, MTXF_APPLY);

                    if (gCurrentLevel == LEVEL_FORTUNA) {
                        Matrix_Translate(gGfxMatrix, 0.0f, -2000.0f, 0, MTXF_APPLY);
                    } else if (gCurrentLevel == LEVEL_KATINA) {
                        Matrix_Translate(gGfxMatrix, 0.0f, -2500.0f, 0, MTXF_APPLY);
                    }

                    Matrix_SetGfxMtx(&gMasterDisp);

                    skipInterpolation = (fabsf(sp13C - bgPrevPosX) > 7280.0f / 2.0f);

                    // Render the textures across the screen (left to right)
                    for (int i = 0; i < 6; i++) {
                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(false);
                        } else {
                            // @port: Tag the transform.
                            FrameInterpolation_RecordOpenChild("Backdrop", i);
                            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                        }

                        switch (gCurrentLevel) {
                            case LEVEL_VERSUS:
                                if (gVersusStage == VS_STAGE_CORNERIA) {
                                    gSPDisplayList(gMasterDisp++, D_versus_302D4D0);
                                } else if (gVersusStage == VS_STAGE_KATINA) {
                                    gSPDisplayList(gMasterDisp++, D_versus_30146B0);
                                } else {
                                    gSPDisplayList(gMasterDisp++, D_versus_3011E40);
                                }
                                break;
                            case LEVEL_FORTUNA:
                                gSPDisplayList(gMasterDisp++, D_FO_600D9F0);
                                break;
                            case LEVEL_KATINA:
                                gSPDisplayList(gMasterDisp++, D_KA_600F1D0);
                                break;
                            case LEVEL_VENOM_2:
                                gSPDisplayList(gMasterDisp++, D_VE2_600F670);
                                break;
                        }

                        // Translate to the next position (move right by 7280.0f each time)
                        Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);

                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(true);
                        } else {
                            // @port Pop the transform id.
                            FrameInterpolation_RecordCloseChild();
                        }
                    }
                    bgPrevPosX = sp13C;
                    break;

                case LEVEL_CORNERIA:
                case LEVEL_VENOM_1: {
                    Matrix_Push(&gGfxMatrix);
                    // Calculate vertical and horizontal offsets
                    f32 bgYpos = (gPlayer[gPlayerNum].camPitch * -6000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.6f);
                    f32 playerCamYawDeg = Math_RadToDeg(gPlayer[gPlayerNum].camYaw);
                    f32 sp13C = Math_ModF(playerCamYawDeg * (-7280.0f / 360.0f) * 5.0f, 7280.0f);

                    if (gLevelMode == LEVELMODE_ON_RAILS) {
                        if (playerCamYawDeg < 180.0f) {
                            sp13C = -(7280.0f - sp13C);
                        }
                    }

                    skipInterpolation = (fabsf(sp13C - bgPrevPosX) > 7280.0f / 2.0f);

                    f32 bgCutsceneFix;
                    if ((gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) && (gCurrentLevel == LEVEL_CORNERIA)) {
                        bgCutsceneFix = 100.0f;
                    } else {
                        bgCutsceneFix = 0.0f;
                    }

                    // Apply camera roll and translate matrix to the starting position (far left)
                    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, sp13C - (7280.0f * 2.0f), -2000.0f + bgYpos + bgCutsceneFix, -6000.0f,
                                     MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);

                    // Render the textures across a wider range to cover the screen
                    for (int i = 0; i < 6; i++) {
                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(false);
                        } else {
                            // @port: Tag the transform.
                            FrameInterpolation_RecordOpenChild("Backdrop", i);
                            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                        }

                        switch ((s32) gCurrentLevel) {
                            case LEVEL_CORNERIA:
                                gSPDisplayList(gMasterDisp++, D_CO_60059F0);
                                break;
                            case LEVEL_VENOM_1:
                                gSPDisplayList(gMasterDisp++, D_VE1_60046F0);
                                break;
                        }

                        // Translate to the next position (move right by 7280.0f each time)
                        Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);

                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(true);
                        } else {
                            // @port Pop the transform id.
                            FrameInterpolation_RecordCloseChild();
                        }
                    }
                    bgPrevPosX = sp13C;
                    Matrix_Pop(&gGfxMatrix);
                } break;

                case LEVEL_VENOM_ANDROSS: // WIP
                    if (gDrawBackdrop != 6) {
                        bgYpos = (gPlayer[gPlayerNum].camPitch * -6000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.4f);
                        sp13C =
                            Math_ModF(Math_RadToDeg(gPlayer[gPlayerNum].camYaw) * (-7280.0f / 360.0f) * 5.0f, 7280.0f);

                        skipInterpolation = (fabsf(sp13C - bgPrevPosX) > 7280.0f / 2.0f);

                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(false);
                        } else {
                            // @port: Tag the transform.
                            FrameInterpolation_RecordOpenChild("Backdrop", 0);
                            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                        }

                        if ((gDrawBackdrop == 2) || (gDrawBackdrop == 7)) {
                            Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                            Matrix_Translate(gGfxMatrix, 0.0f, -4000.0f, -7000.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_600F670);
                        } else if ((gDrawBackdrop == 3) || (gDrawBackdrop == 4)) {
                            RCP_SetupDL(&gMasterDisp, SETUPDL_62);

                            if (gDrawBackdrop == 4) {
                                if ((gGameFrameCount & 8) == 0) {
                                    Math_SmoothStepToF(&gAndrossUnkBrightness, 0.0f, 1.0f, 30.0f, 0);
                                } else {
                                    Math_SmoothStepToF(&gAndrossUnkBrightness, 120.0f, 1.0f, 30.0f, 0);
                                }
                            } else {
                                gAndrossUnkBrightness = 255.0f;
                            }

                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, (s32) gAndrossUnkBrightness,
                                            (s32) gAndrossUnkBrightness, (s32) gAndrossUnkAlpha);

                            // Leftmost DL (-2x translation)
                            Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                            Matrix_Translate(gGfxMatrix, sp13C - 2 * 7280.0f, -2000.0f + bgYpos, -6000.0f, MTXF_APPLY);
                            Matrix_Translate(gGfxMatrix, 0.0f, -2500.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);

                            // Left DL (-1x translation)
                            Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);

                            // Middle DL (original)
                            Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);

                            // Right DL (+1x translation)
                            Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);

                            // Rightmost DL (+2x translation)
                            Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_VE2_60038E0);
                        } else {
                            RCP_SetupDL(&gMasterDisp, SETUPDL_62);
                            if (gDrawBackdrop == 5) {
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 64);
                            } else {
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 128, (s32) gAndrossUnkAlpha);
                            }
                            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -290.0f, MTXF_APPLY);
                            Matrix_Push(&gGfxMatrix);
                            Matrix_Scale(gGfxMatrix, 11.0f, 11.0f, 1.0f, MTXF_APPLY);
                            Matrix_RotateZ(gGfxMatrix, (gPlayer[0].camRoll + (gGameFrameCount * 1.5f)) * M_DTOR,
                                           MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_ANDROSS_C039208);
                            Matrix_Pop(&gGfxMatrix);
                            if (gDrawBackdrop != 5) {
                                Matrix_Push(&gGfxMatrix);
                                Matrix_Scale(gGfxMatrix, 10.0f, 10.0f, 1.0f, MTXF_APPLY);
                                Matrix_RotateZ(gGfxMatrix, (gPlayer[0].camRoll + (gGameFrameCount * -1.3f)) * M_DTOR,
                                               MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_ANDROSS_C039208);
                                Matrix_Pop(&gGfxMatrix);
                            }
                        }
                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(true);
                        } else {
                            // @port Pop the transform id.
                            FrameInterpolation_RecordCloseChild();
                        }
                        bgPrevPosX = sp13C;
                    }
                    break;

                case LEVEL_AQUAS:
                    if (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) {
                        sp13C = Math_RadToDeg(gPlayer[gPlayerNum].camYaw) - gPlayer[gPlayerNum].yRot_114;
                        bgYpos = (gPlayer[gPlayerNum].camPitch * -7000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.6f);
                        sp13C = Math_ModF(sp13C * -40.44444f * 2.0f, 7280.0f); // close to 7280.0f / 180.0f
                        RCP_SetupDL_17();
                        Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                        Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);

                        // Start by translating the matrix to the far left position
                        Matrix_Translate(gGfxMatrix, sp13C - 14560.0f, bgYpos, -7000.0f, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);

                        // Render the textures across the screen (left to right)
                        for (int i = 0; i < 5; i++) {
                            FrameInterpolation_RecordOpenChild("Backdrop", i);
                            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                            if (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) {
                                gSPDisplayList(gMasterDisp++, D_AQ_601AFF0);
                            } else {
                                gSPDisplayList(gMasterDisp++, D_AQ_601C080);
                            }

                            // Translate to the next position (move right by 7280.0f each time)
                            Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);

                            FrameInterpolation_RecordCloseChild();
                        }
                        Matrix_Pop(&gGfxMatrix);
                    }
                    break;

                case LEVEL_SOLAR:
                case LEVEL_ZONESS:
                case LEVEL_MACBETH:
                case LEVEL_TITANIA:
                    camYawDeg = Math_RadToDeg(gPlayer[gPlayerNum].camYaw) - gPlayer[gPlayerNum].yRot_114;
                    bgYpos = (gPlayer[gPlayerNum].camPitch * -7000.0f) - (gPlayer[gPlayerNum].cam.eye.y * 0.6f);
                    sp13C = camYawDeg * -40.44444f * 2.0f; // close to 7280.0f / 180.0f

                    if ((gCurrentLevel == LEVEL_TITANIA) && (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) &&
                        (gPlayer[0].csState < 3)) {
                        D_bg_8015F968 += __sinf(gPlayer[0].camYaw) * 20.0f;
                        sp13C += D_bg_8015F968;
                    }
                    if ((gCurrentLevel == LEVEL_SOLAR) && (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) &&
                        (gPlayer[0].csState >= 2) && (gPlayer[0].cam.eye.z <= -1900.0f)) {
                        D_bg_8015F968 = __sinf(gPlayer[0].camPitch) * 7000.0f;
                        bgYpos -= fabsf(D_bg_8015F968);
                    }

                    sp13C = Math_ModF(sp13C, 7280.0f);

                    f32 corneriaCamYawDeg = Math_RadToDeg(gPlayer[0].camYaw);
                    if (gLevelMode == LEVELMODE_ON_RAILS) {
                        if (corneriaCamYawDeg < 180.0f) {
                            sp13C = -(7280.0f - sp13C);
                        }
                    }

                    skipInterpolation = (fabsf(sp13C - bgPrevPosX) > 7280.0f / 2.0f);

                    RCP_SetupDL_17();
                    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);

                    if ((gCurrentLevel == LEVEL_TITANIA) || (gCurrentLevel == LEVEL_ZONESS)) {
                        Matrix_Translate(gGfxMatrix, sp13C - 14560.0f, -3000.0f + bgYpos, -7000.0f, MTXF_APPLY);
                    } else if (gCurrentLevel == LEVEL_SOLAR) {
                        Matrix_Translate(gGfxMatrix, sp13C - 14560.0f, -3500.0f + bgYpos, -7000.0f, MTXF_APPLY);
                    } else if (gCurrentLevel == LEVEL_MACBETH) {
                        Matrix_Translate(gGfxMatrix, sp13C - 14560.0f, -4000.0f + bgYpos, -7000.0f, MTXF_APPLY);
                    }
                    Matrix_SetGfxMtx(&gMasterDisp);

                    // Render the textures across a wider range to cover the screen
                    for (int i = 0; i < 6; i++) {
                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(false);
                        } else {
                            // @port: Tag the transform.
                            FrameInterpolation_RecordOpenChild("Backdrop", i);
                            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                        }

                        if (gCurrentLevel == LEVEL_TITANIA) {
                            gSPDisplayList(gMasterDisp++, D_TI_6000A80);
                        } else if (gCurrentLevel == LEVEL_MACBETH) {
                            gSPDisplayList(gMasterDisp++, D_MA_6019220);
                        } else if (gCurrentLevel == LEVEL_ZONESS) {
                            gSPDisplayList(gMasterDisp++, D_ZO_6013480);
                        } else if (gCurrentLevel == LEVEL_SOLAR) {
                            gSPDisplayList(gMasterDisp++, D_SO_601E150);
                        }

                        // Move the matrix to the right by 7280.0f each time to draw the next texture
                        Matrix_Translate(gGfxMatrix, 7280.0f, 0.0f, 0.0f, MTXF_APPLY);

                        Matrix_SetGfxMtx(&gMasterDisp);

                        if (skipInterpolation) {
                            // @port Skip interpolation
                            FrameInterpolation_ShouldInterpolateFrame(true);
                        } else {
                            // @port Pop the transform id.
                            FrameInterpolation_RecordCloseChild();
                        }
                    }
                    bgPrevPosX = sp13C;
                    break;
            }
            break;

        case LEVELTYPE_SPACE:
            if (gPlayer[0].state != PLAYERSTATE_ENTER_WARP_ZONE) {
                Matrix_Push(&gGfxMatrix);
                camYawDeg = Math_RadToDeg(gPlayer[0].camYaw);
                sp130 = Math_RadToDeg(gPlayer[0].camPitch);
                if (((camYawDeg < 110.0f) || (camYawDeg > 260.0f)) && ((sp130 < 40.0f) || (sp130 > 325.0f))) {
                    RCP_SetupDL_36();
                    bgXpos = gStarfieldX; /* @port. Range: 0.0f - 960.0f */
                    bgYpos = gStarfieldY;

                    if (((gCurrentLevel == LEVEL_SECTOR_X) || (gCurrentLevel == LEVEL_METEO)) && (gLevelPhase == 1)) {
                        levelId = LEVEL_WARP_ZONE;
                    }

                    if (levelId == LEVEL_SECTOR_X) {
                        // @port. Accomodate for expanded aspect ratio
                        bgXpos = Math_ModF(bgXpos + 60.0f, (320.0f * 3.0f) + 120.0f);
                        bgYpos = Math_ModF(bgYpos + 360.0f - 40.0f, 360.0f);
                    } else if (levelId == LEVEL_TRAINING) {
                        // @port. Accomodate for expanded aspect ratio
                        bgXpos = Math_ModF(bgXpos - 30.0f, (320.0f * 3.0f) + 120.0f);
                        bgYpos = Math_ModF(bgYpos + 360.0f - 40.0f, 360.0f);
                    } else if ((levelId == LEVEL_SECTOR_Y) && (gLevelMode == LEVELMODE_ON_RAILS)) {
                        // @port. Accomodate for expanded aspect ratio
                        bgXpos = Math_ModF(bgXpos + (320.0f * 3.0f) + 120.0f /* - 60.0f*/, (320.0f * 3.0f) + 120.0f);
                        bgYpos = Math_ModF(bgYpos, 360.0f);
                    } else if (levelId == LEVEL_FORTUNA) {
                        // @port. Accomodate for expanded aspect ratio
                        bgXpos = Math_ModF(bgXpos - 34.5f, (320.0f * 3.0f) + 120.0f);
                        bgYpos = Math_ModF(bgYpos + 19.0f, 360.0f);
                    } else if (levelId == LEVEL_BOLSE) {
                        if ((gPlayer[0].state != PLAYERSTATE_LEVEL_COMPLETE) || (gPlayer[0].csState < 10)) {
                            bgYpos = Math_ModF(bgYpos + 360.0f - 100.0f, 360.0f);
                        }
                    } else {
                        // @port. Accomodate for expanded aspect ratio
                        bgXpos = Math_ModF(bgXpos, (320.0f * 3.0f) + 120.0f);
                        bgYpos = Math_ModF(bgYpos, 360.0f);
                    }

                    if ((camYawDeg < 180.0f) && (bgXpos > 380.0f)) {
                        // @port. Accomodate for expanded aspect ratio
                        bgXpos = -((320.0f * 3.0f) - bgXpos);
                    }
                    if ((sp130 > 180.0f) && (bgYpos > 280.0f)) {
                        bgYpos = -(360.0f - bgYpos);
                    }

                    // @port: Tag the transform.
                    FrameInterpolation_RecordOpenChild("Backdrop_Space", 0);

                    Matrix_RotateZ(gGfxMatrix, gStarfieldRoll, MTXF_APPLY);

                    switch (levelId) {
                        case LEVEL_SECTOR_Z:
                            Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
                            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, aSzBackgroundDL);
                            break;

                        case LEVEL_WARP_ZONE:
                            if ((s32) gWarpZoneBgAlpha != 0) {
                                RCP_SetupDL_62();
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) gWarpZoneBgAlpha);
                                Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 1.7f, 1.7f, 1.0f, MTXF_APPLY);
                                Matrix_Push(&gGfxMatrix);
                                Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 1.07f, 0.93f, 1.0f, MTXF_APPLY);
                                Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 10.0f * M_DTOR, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 1.07f, 0.93f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_WZ_7001540);
                                Matrix_Pop(&gGfxMatrix);
                            }
                            break;

                        case LEVEL_METEO:
                            if ((gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) && (gCsFrameCount > 260)) {
                                Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f) - 30.0f, -290.0f,
                                                 MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_ME_600DDF0);
                            } else if (gPathProgress > 185668.0f) {
                                Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f) - 130.0f, -290.0f,
                                                 MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                gSPDisplayList(gMasterDisp++, D_ME_600DDF0);
                            }
                            break;

                        case LEVEL_SECTOR_X:
                            if (gSceneSetup == 0) {
                                Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                                Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 1.0f, MTXF_APPLY);
                                Matrix_SetGfxMtx(&gMasterDisp);
                                RCP_SetupDL_62();
                                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
                                gSPDisplayList(gMasterDisp++, D_SX_6029890);
                            }
                            break;

                        case LEVEL_TRAINING:
                            Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, 0.2f, 0.2f, 1.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            RCP_SetupDL_62();
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                            gSPDisplayList(gMasterDisp++, D_TR_6003760);
                            break;

                        case LEVEL_AREA_6:
                        case LEVEL_UNK_4:
                            scale = (gPathProgress * 0.00004f) + 0.5f;
                            if (scale > 3.5f) {
                                scale = 3.5f;
                            }
                            if (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) {
                                scale = D_bg_8015F984;
                                if (scale > 3.5f) {
                                    scale = 3.5f;
                                }
                            }
                            Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, scale * 0.75, scale * 0.75f, 1.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_A6_601BB40);
                            break;

                        case LEVEL_FORTUNA:
                            scale = 1.5f;
                            /**
                             * @port: Bg planet Fortuna shrinks after 400 frames in the original game
                             * after the first camera go around to give the impression of travel.
                             * Adjusting the shrink 100 frames later hides this event from wide screens.
                             */
                            if ((gCsFrameCount > 500 /*400*/) && (gMissionStatus == MISSION_COMPLETE)) {
                                scale = 0.75f;
                            }
                            Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_FO_600B4B0);
                            break;

                        case LEVEL_BOLSE:
                            scale = 1.0f;
                            if ((gCsFrameCount > 500) && (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE)) {
                                scale = 1.3f;
                            }
                            Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_BO_600D190);
                            break;

                        case LEVEL_SECTOR_Y:
                            Matrix_Translate(gGfxMatrix, bgXpos - 120.0f, -(bgYpos - 120.0f), -290.0f, MTXF_APPLY);
                            Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, 1.0f, MTXF_APPLY);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            RCP_SetupDL_62();
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
                            gSPDisplayList(gMasterDisp++, D_SY_6001840);
                            break;
                    }
                    // @port Pop the transform id.
                    FrameInterpolation_RecordCloseChild();
                }
                Matrix_Pop(&gGfxMatrix);
            }

            if (gStarWarpDistortion > 0.0f) {
                f32* xStar = gStarOffsetsX;
                f32* yStar = gStarOffsetsY;
                f32 zRot;

                RCP_SetupDL_14();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 128, 128, 255, 255);

                zRot = 0.0f;
                for (i = 0; i < 300 * 3; i++, xStar++, yStar++) {
                    *xStar = RAND_FLOAT_SEEDED(480.0f * 3.0f) - 80.0f;
                    *yStar = RAND_FLOAT_SEEDED(360.0f * 3.0f) - 60.0f;
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, (*xStar - 160.0f - 480.0f) * 10.0f, (*yStar - 120.0f - 20.0f) * 10.0f,
                                     -5000.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, zRot, MTXF_APPLY);
                    Matrix_Scale(gGfxMatrix, 10.0f, 1.0f, -gStarWarpDistortion, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_edisplay_800CFD80);
                    Matrix_Pop(&gGfxMatrix);
                    zRot += M_PI / 4;
                }
            }
            break;
    }
    Matrix_Pop(&gGfxMatrix);
}

void Background_DrawSun(void) {
    f32 camYaw;
    f32 camPitch;
    Color_RGB8* sunColor;
    s32* sunAlpha;
    Gfx** sunDL;
    f32* sunScale;
    s32 i;
    s32 levelType = gLevelType;

    if ((gCurrentLevel == LEVEL_KATINA) || (gCurrentLevel == LEVEL_VENOM_2) || (gCurrentLevel == LEVEL_VENOM_ANDROSS) ||
        (gCurrentLevel == LEVEL_SOLAR) || (gCurrentLevel == LEVEL_TRAINING) || gVersusMode) {
        return;
    }
    gPlayerGlareAlphas[gPlayerNum] -= sSunGlareAlphaStep[levelType];
    if (gPlayerGlareAlphas[gPlayerNum] > 300) {
        gPlayerGlareAlphas[gPlayerNum] = 0;
    }

    if (((gCurrentLevel == LEVEL_AQUAS) && (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO)) ||
        (((gPlayer[gPlayerNum].state == PLAYERSTATE_U_TURN) || (gLevelMode == LEVELMODE_ALL_RANGE) ||
          (gPlayer[gPlayerNum].state == PLAYERSTATE_LEVEL_COMPLETE)) &&
         (gLevelType == LEVELTYPE_PLANET) && (gCurrentLevel != LEVEL_TITANIA) && (gCurrentLevel != LEVEL_AQUAS))) {
        gPlayerGlareReds[gPlayerNum] = 128;
        gPlayerGlareGreens[gPlayerNum] = 128;
        gPlayerGlareBlues[gPlayerNum] = 128;
        camYaw = Math_RadToDeg(gPlayer[gPlayerNum].camYaw);
        camPitch = Math_RadToDeg(gPlayer[gPlayerNum].camPitch);
        if (camPitch > 180.0f) {
            camPitch -= 360.0f;
        }

        camYaw -= 135.0f;
        gSunViewX = -camYaw * 3.2f;
        gSunViewY = (-camPitch * 3.2f) + 130.0f - ((gPlayer[gPlayerNum].cam.eye.y - 350.0f) * 0.015f);

        if (gCurrentLevel == LEVEL_KATINA) {
            gSunViewY -= 80.0f;
        }
        if ((gCurrentLevel == LEVEL_ZONESS) && (gPlayer[0].csState >= 2) && !gMissedZoSearchlight) {
            gSunViewY -= 60.0f;
            gSunViewX -= 480.0f;
        }
        if ((gSunViewX < 120.0f) && (gSunViewX > -120.0f) && (gSunViewY < 120.0f)) {
            gPlayerGlareAlphas[gPlayerNum] += sSunGlareAlphaStep[levelType] * 2;
            if (sSunGlareMaxAlpha[levelType] < gPlayerGlareAlphas[gPlayerNum]) {
                gPlayerGlareAlphas[gPlayerNum] = sSunGlareMaxAlpha[levelType];
            }
        }
    }
    if (gPlayerGlareAlphas[gPlayerNum] != 0) {
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, gSunViewX, gSunViewY, -200.0f, MTXF_APPLY);
        RCP_SetupDL_62();
        sunColor = sSunColors;
        sunAlpha = sSunAlphas;
        sunDL = sSunDLs;
        sunScale = sSunScales;
        if (gCurrentLevel == LEVEL_KATINA) {
            sunColor = sKaSunColors;
            sunAlpha = sKaSunAlphas;
            sunDL = sKaSunDLs;
            sunScale = sKaSunScales;
        }
        for (i = 0; i < 5; i++, sunColor++, sunAlpha++, sunDL++, sunScale++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Scale(gGfxMatrix, *sunScale, *sunScale, *sunScale, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, sunColor->r, sunColor->g, sunColor->b, *sunAlpha);
            gSPDisplayList(gMasterDisp++, *sunDL);
            Matrix_Pop(&gGfxMatrix);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Background_DrawLensFlare(void) {
    s32 i;
    Color_RGB8* lensFlareColor;
    s32* lensFlareAlpha;
    Gfx** lensFlareDL;
    f32* lensFlareScale;
    f32* lensFlareShift;
    f32 lensFlareOffsetX;
    f32 lensFlareOffsetY;
    f32 alphaMod;
    f32 alpha;

    if ((gCurrentLevel == LEVEL_VENOM_ANDROSS) || (gLevelType == LEVELTYPE_SPACE) ||
        (gPlayerGlareAlphas[gPlayerNum] == 0)) {
        return;
    }
    alphaMod = 1.0f;
    if (gPlayerGlareAlphas[gPlayerNum] < 80) {
        alphaMod = gPlayerGlareAlphas[gPlayerNum] / 80.0f;
    }
    alphaMod *= sLensFlareAlphaMod[gLevelType];
    Matrix_Push(&gGfxMatrix);
    Matrix_RotateZ(gGfxMatrix, gPlayer[gPlayerNum].camRoll * M_DTOR, MTXF_APPLY);
    Matrix_Translate(gGfxMatrix, gSunViewX, gSunViewY, -200.0f, MTXF_APPLY);
    RCP_SetupDL_62();

    lensFlareOffsetX = gSunViewX * -0.03f;
    lensFlareOffsetY = gSunViewY * 0.03f;
    lensFlareColor = &sSunColors[5];
    lensFlareAlpha = &sSunAlphas[5];
    lensFlareDL = &sSunDLs[5];
    lensFlareScale = &sSunScales[5];
    lensFlareShift = &sSunShifts[5];
    if (gCurrentLevel == LEVEL_KATINA) {
        lensFlareColor = &sKaSunColors[5];
        lensFlareAlpha = &sKaSunAlphas[5];
        lensFlareDL = &sKaSunDLs[5];
        lensFlareScale = &sKaSunScales[5];
        lensFlareShift = &sKaSunShifts[5];
    }
    for (i = 5; i < 13; i++, lensFlareColor++, lensFlareAlpha++, lensFlareDL++, lensFlareScale++, lensFlareShift++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, *lensFlareShift * lensFlareOffsetX, *lensFlareShift * -lensFlareOffsetY, 0.0f,
                         MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, *lensFlareScale, *lensFlareScale, *lensFlareScale, MTXF_APPLY);
        if (((i == 5) || (i == 11)) && (gCurrentLevel != LEVEL_KATINA)) {
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        alpha = *lensFlareAlpha;
        if (i >= 5) {
            alpha *= alphaMod;
        }
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, lensFlareColor->r, lensFlareColor->g, lensFlareColor->b,
                        (s32) alpha);
        gSPDisplayList(gMasterDisp++, *lensFlareDL);
        Matrix_Pop(&gGfxMatrix);
    }
    Matrix_Pop(&gGfxMatrix);
}

void Background_dummy_80040CDC(void) {
}

#if 0
Gfx dynaFloor1[724];
Gfx dynaFloor2[724];
Vtx dynaFloor1Vtx[17 * 17];
Vtx dynaFloor2Vtx[17 * 17];
#endif

void AllRangeGround_Draw(void) {
    for (int i = 0; i < ARRAY_COUNT(sGroundPositions360x_FIX); i++) {
        const f32 maxDistZ = 0.0f;
        const f32 maxDistX = 0.0f;

        // UPPER LEFT QUADRANT
        if (gPlayer[0].pos.x < maxDistX && gPlayer[0].pos.z < maxDistZ) {
            // upper left corner piece : 8
            // side upper  left piece : 12
            // side lower left piece : 13
            // Upper middle right piece : 10
            // upper middle left piece : 9
            if ((i > 3) && (i != 8) && (i != 12) && (i != 9) && (i != 13) && (i != 10)) {
                continue;
            }
        }

        // LOWER LEFT QUADRANT
        if (gPlayer[0].pos.x < maxDistX && gPlayer[0].pos.z > maxDistZ) {
            // lower middle left piece: 5
            // lower middle right piece : 6
            // lower left corner piece: 7
            // side upper left piece : 12
            // side lower left piece : 13
            if ((i > 3) && (i != 5) && (i != 7) && (i != 13) && (i != 6) && (i != 12)) {
                continue;
            }
        }

        // UPPER RIGHT QUADRANT
        if (gPlayer[0].pos.x > maxDistX && gPlayer[0].pos.z < maxDistZ) {
            // uppder middle left piece : 9
            // Upper middle right piece : 10
            // upper right corner piece : 11
            // side upper right piece: 14
            // side lower right piece : 15
            if ((i > 3) && (i != 10) && (i != 11) && (i != 14) && (i != 9) && (i != 15)) {
                continue;
            }
        }

        // LOWER RIGHT QUADRANT
        if (gPlayer[0].pos.x > maxDistX && gPlayer[0].pos.z > maxDistZ) {
            // lower right corner piece : 4
            // // lower middle left piece : 5
            // lower middle right piece : 6
            // side upper right piece: 14
            // side lower right piece : 15
            if ((i > 3) && ((i != 4) && (i != 6) && (i != 15) && (i != 14) && (i != 5))) {
                continue;
            }
        }

        Matrix_Push(&gGfxMatrix);

        // @port: Tag the transform.
        FrameInterpolation_RecordOpenChild("360Ground", i);

        Matrix_Translate(gGfxMatrix, sGroundPositions360x_FIX[i], 0.0f, sGroundPositions360z_FIX[i], MTXF_APPLY);

        if (gCurrentLevel == LEVEL_TRAINING) {
            Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);

        switch (gCurrentLevel) {
            case LEVEL_FORTUNA:
                gSPDisplayList(gMasterDisp++, D_FO_6001360);
                break;
            case LEVEL_KATINA:
                gSPDisplayList(gMasterDisp++, D_KA_6009250);
                break;
            case LEVEL_BOLSE:
                gSPDisplayList(gMasterDisp++, D_BO_600A810);
                break;
            case LEVEL_VENOM_2:
                gSPDisplayList(gMasterDisp++, D_VE2_6010700);
                break;
            case LEVEL_CORNERIA:
                gSPDisplayList(gMasterDisp++, D_CO_601EAA0);
                break;
            case LEVEL_TRAINING:
                gSPDisplayList(gMasterDisp++, D_TR_6005880);
                break;
            case LEVEL_VERSUS:
                if (gVersusStage == VS_STAGE_CORNERIA) {
                    gSPDisplayList(gMasterDisp++, D_versus_3018800);
                } else {
                    gSPDisplayList(gMasterDisp++, D_versus_30160A0);
                }
                break;
        }
        Matrix_Pop(&gGfxMatrix);

        // @port: Pop the transform.
        FrameInterpolation_RecordCloseChild();
    }
}

void Background_DrawGround(void) {
    f32 sp1D4;
    s32 i;
    u32 temp_fv0;
    u32 temp_s0;
    u16* sp1C4;
    Gfx* sp1C0;
    f32 temp_fv1;
    f32 temp_fa0;

    if ((gCurrentLevel != LEVEL_VENOM_2) && ((gPlayer[0].cam.eye.y > 4000.0f) || !gDrawGround)) {
        return;
    }
    if ((gCurrentLevel == LEVEL_BOLSE) && gBolseDynamicGround) {
        Bolse_DrawDynamicGround();
        return;
    }

    sp1D4 = 0.0f;
    if ((gGroundType != 10) && (gGroundType != 11)) {
        sp1D4 = -4000.0f;
    }
    if (gGroundType == 7) {
        sp1D4 = 0.0f;
        gPlayer[gPlayerNum].xPath = 0.0f;
    }

    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        Vec3f sp1B4;
        Vec3f sp1A8;

        sp1D4 = 0.0f;
        gPlayer[gPlayerNum].xPath = 0.0f;

        sp1B4.x = 0;
        sp1B4.y = 0;
        sp1B4.z = -5500.0f;

        Matrix_RotateY(gCalcMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_NEW);
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp1B4, &sp1A8);

        // @port: We no longer warp the floor.
#if 0
        temp_fv1 = gPlayer[gPlayerNum].cam.eye.x + sp1A8.x;
        temp_fa0 = gPlayer[gPlayerNum].cam.eye.z + sp1A8.z;

        if (temp_fv1 > 6000.0f) {
            gPlayer[gPlayerNum].xPath = 12000.0f;
        }
        if (temp_fv1 > 18000.0f) {
            gPlayer[gPlayerNum].xPath = 24000.0f;
        }
        if (temp_fv1 < -6000.0f) {
            gPlayer[gPlayerNum].xPath = -12000.0f;
        }
        if (temp_fv1 < -18000.0f) {
            gPlayer[gPlayerNum].xPath = -24000.0f;
        }

        if (temp_fa0 > 6000.0f) {
            sp1D4 = 12000.0f;
        }
        if (temp_fa0 > 18000.0f) {
            sp1D4 = 24000.0f;
        }
        if (temp_fa0 < -6000.0f) {
            sp1D4 = -12000.0f;
        }
        if (temp_fa0 < -18000.0f) {
            sp1D4 = -24000.0f;
        }
#endif
    }

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, gPlayer[gPlayerNum].xPath, -3.0f + gCameraShakeY, sp1D4, MTXF_APPLY);

    if (gFovYMode == 2) {
        Matrix_Scale(gGfxMatrix, 1.2f, 1.2f, 1.0f, MTXF_APPLY);
    }

    Matrix_SetGfxMtx(&gMasterDisp);

    switch (gCurrentLevel) {
        case LEVEL_CORNERIA:
            if (gGroundClipMode != 0) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_20(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }

            if (gLevelMode == LEVELMODE_ON_RAILS) {
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, SEGMENTED_TO_VIRTUAL(D_CO_601B6C0));
                
				int interpolatedFrames = GameEngine_GetInterpolationFrameCount();

				temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f)); // 0.64f / 3.0f
				temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);

				float xScroll = temp_fv0;
				float yScroll = temp_s0;

				float inc = (2.0f * (gPathTexScroll - gLastPathTexScroll) * 0.2133333f) / (float)interpolatedFrames;

				for (int i = 0; i < interpolatedFrames; i++)
				{
					gDPSetInterpolation(gMasterDisp++, i);

					gDPSetupTile2(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
						G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

					gDPSetTileSizeInterp(gMasterDisp, G_TX_RENDERTILE, xScroll, yScroll, 32 << 2, 32 << 2);

					gMasterDisp += 3;

					yScroll += inc >= 0 ? inc : -inc;
					yScroll = fabs(Math_ModF(yScroll, 128.0f));
				}

                switch (gGroundSurface) {
                    case SURFACE_GRASS:
                        gDPLoadTileTexture(gMasterDisp++, D_CO_601B6C0, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                        gBgColor = 0x845; // 8, 8, 32
                        break;
                    case SURFACE_ROCK:
                        gDPLoadTileTexture(gMasterDisp++, D_CO_6028260, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                        gBgColor = 0x845; // 8, 8, 32
                        break;
                    case SURFACE_WATER:
                        RCP_SetupDL_45(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);
                        gDPLoadTileTexture(gMasterDisp++, D_CO_6028A60, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32);
                        gBgColor = 0x190F; // 24, 32, 56
                        break;
                }
                // Drawing the original water in the middle
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY); // Center water
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
                Matrix_Pop(&gGfxMatrix);

                // Extend water to the left
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, -3000.0f, MTXF_APPLY); // Left water
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
                Matrix_Pop(&gGfxMatrix);

                // Extend water to the right
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, -3000.0f, MTXF_APPLY); // Right water
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
                Matrix_Pop(&gGfxMatrix);

                // Drawing the original water in the middle
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f, MTXF_APPLY); // Center water
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
                Matrix_Pop(&gGfxMatrix);

                // Extend water to the left
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, 3000.0f, MTXF_APPLY); // Left water
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);
                Matrix_Pop(&gGfxMatrix);

                // Extend water to the right
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, 3000.0f, MTXF_APPLY); // Right water
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_CO_601B640);

                Matrix_Pop(&gGfxMatrix);
            } else {
                gGroundSurface = SURFACE_GRASS;
                gBgColor = 0x845; // 8, 8, 32

                AllRangeGround_Draw();
            }
            break;

        case LEVEL_VENOM_1:
        case LEVEL_MACBETH:
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            switch (gCurrentLevel) {
                case LEVEL_VENOM_1:
                    sp1C4 = D_VE1_6006750;
                    sp1C0 = D_VE1_60066D0;
                    gDPLoadTextureBlock(gMasterDisp++, sp1C4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD,
                                        G_TX_NOLOD);
                    break;
                case LEVEL_MACBETH:
                    sp1C4 = D_MA_602DCB8;
                    sp1C0 = D_MA_60306D0;
                    gDPLoadTextureBlock(gMasterDisp++, sp1C4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0,
                                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD,
                                        G_TX_NOLOD);
                    break;
            }
            gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1C4);
            
            //gDPSetupTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
                         //G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

			int interpolatedFrames = GameEngine_GetInterpolationFrameCount();

			temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f));
			temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);

			float xScroll = temp_fv0;
			float yScroll = temp_s0;

			float inc = (2.0f * (gPathTexScroll - gLastPathTexScroll) * 0.2133333f) / (float)interpolatedFrames;

			for (int i = 0; i < interpolatedFrames; i++)
			{
				gDPSetInterpolation(gMasterDisp++, i);

				gDPSetupTile2(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
					G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

				gDPSetTileSizeInterp(gMasterDisp, G_TX_RENDERTILE, xScroll, yScroll, 32 << 2, 32 << 2);

				gMasterDisp += 3;

				yScroll += inc >= 0 ? inc : -inc;
				yScroll = fabs(Math_ModF(yScroll, 128.0f));
			}

            // CENTER FAR
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);

            // LEFT FAR (Mirrored)
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling for mirrored object
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, -3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, -1.0f, 1.0f, 0.5f, MTXF_APPLY); // Apply negative X scaling to mirror
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling

            // RIGHT FAR
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, -3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);

            // CENTER
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);

            // LEFT (Mirrored)
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling for mirrored object
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, 3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, -1.0f, 1.0f, 0.5f, MTXF_APPLY); // Apply negative X scaling to mirror
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);
            Matrix_Pop(&gGfxMatrix);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling

            // RIGHT
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, 3000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, sp1C0);

            Matrix_Pop(&gGfxMatrix);
            break;

        case LEVEL_TRAINING: {
            static Vtx trainingGroundVtx_FIX[] = {
                { { { 4000, 0, -6000 }, 0, { 20947, -19923 }, { 0, 120, 0, 255 } } },
                { { { -4000, 0, -6000 }, 0, { 0, -19923 }, { 0, 120, 0, 255 } } },
                { { { -4000, 0, 0 }, 0, { 0, -9449 }, { 0, 120, 0, 255 } } },
                { { { 4000, 0, 0 }, 0, { 20947, -9449 }, { 0, 120, 0, 255 } } },
                { { { -4000, 0, 6000 }, 0, { 0, 1023 }, { 0, 120, 0, 255 } } },
                { { { 4000, 0, 6000 }, 0, { 20947, 1023 }, { 0, 120, 0, 255 } } },
            };

            static Gfx trainingGroundDL_FIX[] = {
                gsSPVertex(trainingGroundVtx_FIX, 6, 0),
                gsSP2Triangles(1, 2, 3, 0, 1, 3, 0, 0),
                gsSP2Triangles(4, 5, 3, 0, 4, 3, 2, 0),
                gsSPEndDisplayList(),
            };

            sp1C4 = D_TR_6005938;
            sp1C0 = trainingGroundDL_FIX;
            gDPLoadTextureBlock(gMasterDisp++, sp1C4, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                                G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

            if (gLevelMode == LEVELMODE_ON_RAILS) {
                // if (gPathTexScroll > (32.0f * 36.7f) / 2.0f) {
                //     gPathTexScroll -= (32.0f * 36.7f) / 2.0f;
                // }
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, sp1C4);
                
				int interpolatedFrames = GameEngine_GetInterpolationFrameCount();

				temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f)); // 0.64f / 3.0f
				temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);

				float xScroll = temp_fv0;
				float yScroll = temp_s0;

				float inc = (2.0f * (gPathTexScroll - gLastPathTexScroll) * 0.2133333f) / (float)interpolatedFrames;

				for (int i = 0; i < interpolatedFrames; i++)
				{
					gDPSetInterpolation(gMasterDisp++, i);

					gDPSetupTile2(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
						G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

					gDPSetTileSizeInterp(gMasterDisp, G_TX_RENDERTILE, xScroll, yScroll, 32 << 2, 32 << 2);

					gMasterDisp += 3;

					yScroll += inc >= 0 ? inc : -inc;
					yScroll = fabs(Math_ModF(yScroll, 128.0f));
				}

                // Original Display (Center)
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -2500.0f /*+ gPathTexScroll*/, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);

                // Mirrored Display - Left side
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, -2500.0f /*+ gPathTexScroll*/,
                                 MTXF_APPLY); // Move left by the width of the original (-8000.0f)
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);

                // Mirrored Display - Right side
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, -2500.0f /*+ gPathTexScroll*/,
                                 MTXF_APPLY); // Move right by the width of the original (+8000.0f)
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);

                // Original Display for the second section (Center)
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -8435.0f + 65 /*+ gPathTexScroll*/, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);

                // Mirrored Display - Left side for the second section
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, -8435.0f + 65 /*+ gPathTexScroll*/,
                                 MTXF_APPLY); // Move left by the width of the original (-8000.0f)
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);

                // Mirrored Display - Right side for the second section
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, -8435.0f + 65 /*+ gPathTexScroll*/,
                                 MTXF_APPLY); // Move right by the width of the original (+8000.0f)
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
            } else {
                AllRangeGround_Draw();
            }
            break;
        }

        case LEVEL_AQUAS:
            RCP_SetupDL(&gMasterDisp, SETUPDL_20);
            sp1C0 = D_AQ_600AB10;
            gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);

            // Bottom Water floor
            if ((D_bg_8015F964 == 0) && ((gAqDrawMode == 0) || (gAqDrawMode == 2))) {

                gDPLoadTileTexture(gMasterDisp++, SEGMENTED_TO_VIRTUAL(D_AQ_600AB68), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32,
                                   32);
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, SEGMENTED_TO_VIRTUAL(D_AQ_600AB68));

				int interpolatedFrames = GameEngine_GetInterpolationFrameCount();

				temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f));
				temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);

				float xScroll = temp_fv0;
				float yScroll = temp_s0;

				float inc = (2.0f * (gPathTexScroll - gLastPathTexScroll) * 0.2133333f) / (float)interpolatedFrames;

				for (int i = 0; i < interpolatedFrames; i++)
				{
					gDPSetInterpolation(gMasterDisp++, i);

					gDPSetupTile2(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
						G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

					gDPSetTileSizeInterp(gMasterDisp, G_TX_RENDERTILE, xScroll, yScroll, 32 << 2, 32 << 2);

					gMasterDisp += 3;

					yScroll += inc >= 0 ? inc : -inc;
					yScroll = fabs(Math_ModF(yScroll, 128.0f));
				}
			
                // CENTER FAR
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
                // LEFT
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, -3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
                // RIGHT
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, -3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);

                // CENTER
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
                // LEFT
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -8000.0f, 0.0f, 3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
                // RIGHT
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 8000.0f, 0.0f, 3000.0f, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, sp1C0);
                Matrix_Pop(&gGfxMatrix);
            }

            // Top water surface:
            if ((D_bg_8015F964 != 0) || (gAqDrawMode == 0)) {
                gDPLoadTileTexture(gMasterDisp++, SEGMENTED_TO_VIRTUAL(D_AQ_602ACC0), G_IM_FMT_RGBA, G_IM_SIZ_16b, 32,
                                   32);
                gDPSetTextureImage(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 1, SEGMENTED_TO_VIRTUAL(D_AQ_602ACC0));

				int interpolatedFrames = GameEngine_GetInterpolationFrameCount();

				temp_s0 = fabsf(Math_ModF(2.0f * (gPathTexScroll * 0.2133333f), 128.0f));
				temp_fv0 = Math_ModF((10000.0f - gPlayer[gPlayerNum].xPath) * 0.32f, 128.0f);

				float xScroll = temp_fv0;
				float yScroll = temp_s0;

				float inc = (2.0f * (gPathTexScroll - gLastPathTexScroll) * 0.2133333f) / (float)interpolatedFrames;

				for (int i = 0; i < interpolatedFrames; i++)
				{
					gDPSetInterpolation(gMasterDisp++, i);

					gDPSetupTile2(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 32, 32, temp_fv0, temp_s0,
						G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

					gDPSetTileSizeInterp(gMasterDisp, G_TX_RENDERTILE, xScroll, yScroll, 32 << 2, 32 << 2);

					gMasterDisp += 3;

					yScroll += inc >= 0 ? inc : -inc;
					yScroll = fabs(Math_ModF(yScroll, 128.0f));
				}

                if (gAqDrawMode != 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_47);
                } else {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_37);
                }

                if ((gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) && (gPlayer[0].csState < 2)) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                } else if (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_bg_8015F974, D_bg_8015F978, D_bg_8015F97C,
                                    D_bg_8015F980);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) D_AQ_801C4188);
                }

                // Render the original object in the middle TEST
                Matrix_Push(&gGfxMatrix);

                Matrix_Translate(gGfxMatrix, 0.0f, D_bg_8015F970, -9000.0f, MTXF_APPLY); // Center
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);
                // Render the extended object to the left
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -16000.0f, D_bg_8015F970, -9000.0f,
                                 MTXF_APPLY); // Left (-6000.0f on X-axis)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the extended object to the right
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 16000.0f, D_bg_8015F970, -9000.0f,
                                 MTXF_APPLY); // Right (6000.0f on X-axis)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the original object in the middle
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, D_bg_8015F970, -3000.0f, MTXF_APPLY); // Center
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the extended object to the left
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -16000.0f, D_bg_8015F970, -3000.0f,
                                 MTXF_APPLY); // Left (-6000.0f on X-axis)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the extended object to the right
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 16000.0f, D_bg_8015F970, -3000.0f,
                                 MTXF_APPLY); // Right (6000.0f on X-axis)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the original object in the middle (other row)
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, D_bg_8015F970, 3000.0f, MTXF_APPLY); // Center (other row)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the extended object to the left (other row)
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, -16000.0f, D_bg_8015F970, 3000.0f,
                                 MTXF_APPLY); // Left (-6000.0f on X-axis, other row)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);

                // Render the extended object to the right (other row)
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 16000.0f, D_bg_8015F970, 3000.0f,
                                 MTXF_APPLY); // Right (6000.0f on X-axis, other row)
                Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.5f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_AQ_602AC40);
                Matrix_Pop(&gGfxMatrix);
            }
            break;

        case LEVEL_FORTUNA:
        case LEVEL_KATINA:
        case LEVEL_BOLSE:
        case LEVEL_VENOM_2:
            if ((gGroundClipMode != 0) || (gCurrentLevel == LEVEL_BOLSE)) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_20(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }

            AllRangeGround_Draw();
            break;

        case LEVEL_VERSUS:
            if (gGroundClipMode != 0) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_20(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }

            AllRangeGround_Draw();
            break;

        case LEVEL_SOLAR: // WIP
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

            // Render the object at the center (No mirroring)
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -2000.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, (gGameFrameCount % 2) ? D_SO_60005B0 : D_SO_6002E60);
            Matrix_Pop(&gGfxMatrix);

// Render mirrored objects on both sides (Left: -1, Right: 1)
// Render mirrored objects on both sides (Left: -1, Right: 1)
#if 1
            for (s32 i = -1; i <= 1; i += 2) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, i * 4800.0f, 0.0f, -2000.0f,
                                 MTXF_APPLY);                            // Translate left (-) or right (+)
                Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY); // Mirror geometry (negative X scale)
                Matrix_SetGfxMtx(&gMasterDisp);

                // Disable backface culling for mirrored geometry
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

                // Apply texture mirroring
                gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

                // Adjust UV mapping for the left side only
                if (i == -1) {
                    // Adjust UVs slightly for the left side to fix texture alignment
                    gDPSetTileSize(gMasterDisp++, G_TX_RENDERTILE, 4 << G_TEXTURE_IMAGE_FRAC, 0,
                                   (31 << G_TEXTURE_IMAGE_FRAC), (31 << G_TEXTURE_IMAGE_FRAC));
                } else {
                    // Standard UVs for the right side
                    gDPSetTileSize(gMasterDisp++, G_TX_RENDERTILE, 0 << G_TEXTURE_IMAGE_FRAC, 0,
                                   (31 << G_TEXTURE_IMAGE_FRAC), (31 << G_TEXTURE_IMAGE_FRAC));
                }

                gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5,
                           G_TX_NOLOD, G_TX_MIRROR | G_TX_WRAP, 5, G_TX_NOLOD);

                /*
                memcpy(dynaFloor1, LOAD_ASSET(D_SO_6002E60), 724 * sizeof(Gfx));
                memcpy(dynaFloor2, LOAD_ASSET(D_SO_60005B0), 724 * sizeof(Gfx));
                memcpy(dynaFloor1Vtx, LOAD_ASSET(D_SO_6001C50), 17 * 17 * sizeof(Vtx));
                memcpy(dynaFloor2Vtx, LOAD_ASSET(D_SO_6004500), 17 * 17 * sizeof(Vtx));
                */

                // Render the display list based on the current frame
                gSPDisplayList(gMasterDisp++, (gGameFrameCount % 2) ? D_SO_60005B0_copy : D_SO_6002E60_copy);

                // Re-enable backface culling
                gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                Matrix_Pop(&gGfxMatrix);
            }
#endif

            break;

        case LEVEL_ZONESS:
            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

            // Center Further (main object)
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -3000.0f, MTXF_APPLY); // Center Further
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0);
            }
            Matrix_Pop(&gGfxMatrix);

            // Center Further - Left Mirror
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -4800.0f, 0.0f, -3000.0f, MTXF_APPLY); // Left (-4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);            // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center Further - Right Mirror
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 4800.0f, 0.0f, -3000.0f, MTXF_APPLY); // Right (4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);           // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center Far (main object)
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -6000.0f, MTXF_APPLY); // Center Far
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0);
            }
            Matrix_Pop(&gGfxMatrix);

            // Center Far - Left Mirror
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -4800.0f, 0.0f, -6000.0f, MTXF_APPLY); // Left (-4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);            // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center Far - Right Mirror
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 4800.0f, 0.0f, -6000.0f, MTXF_APPLY); // Right (4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);           // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center (Main object at center, no mirroring)
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -1500.0f, MTXF_APPLY); // Center
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0);
            }
            Matrix_Pop(&gGfxMatrix);

            // Center - Left Mirror
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -4800.0f, 0.0f, -1500.0f, MTXF_APPLY); // Left (-4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);            // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center - Right Mirror
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 4800.0f, 0.0f, -1500.0f, MTXF_APPLY); // Right (4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);           // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center (Main object at center, no mirroring) Near
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 0.0f, MTXF_APPLY); // Center
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0);
            }
            Matrix_Pop(&gGfxMatrix);

            // Center - Left Mirror Near
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -4800.0f, 0.0f, 0.0f, MTXF_APPLY); // Left (-4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);        // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center - Right Mirror Near
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 4800.0f, 0.0f, 0.0f, MTXF_APPLY); // Right (4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);       // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center (Main object at center, no mirroring) Nearer
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 1500.0f, MTXF_APPLY); // Center
            Matrix_Scale(gGfxMatrix, 3.0f, 2.0f, 3.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0);
            }
            Matrix_Pop(&gGfxMatrix);

            // Center - Left Mirror Nearer
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, -4800.0f, 0.0f, 1500.0f, MTXF_APPLY); // Left (-4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);           // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);

            // Center - Right Mirror Nearer
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, 4800.0f, 0.0f, 1500.0f, MTXF_APPLY); // Right (4800.0f on X-axis)
            Matrix_Scale(gGfxMatrix, -3.0f, 2.0f, 3.0f, MTXF_APPLY);          // Mirror by negative X scale
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK); // Disable backface culling
            gSPTexture(gMasterDisp++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTile(gMasterDisp++, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, G_TX_RENDERTILE, 0, G_TX_WRAP, 5, G_TX_NOLOD,
                       G_TX_WRAP, 5, G_TX_NOLOD);

            if ((gGameFrameCount % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_ZO_6008830_copy);
            } else {
                gSPDisplayList(gMasterDisp++, D_ZO_600B0E0_copy);
            }
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK); // Re-enable backface culling
            Matrix_Pop(&gGfxMatrix);
            break;
    }
    Matrix_Pop(&gGfxMatrix);
}

// Unused. Early water implementation in Aquas?
void func_bg_80042D38(void) {
    f32 xEye;
    f32 zEye;

    // all sorts of fake

    if (gPlayer[gPlayerNum].cam.eye.x == 0.0f) {
        // Commented out code?
    }
    if (gPlayer[gPlayerNum].cam.eye.z == 0.0f) {
        // Commented out code?
    }

    Matrix_Push(&gGfxMatrix);

    xEye = gPlayer[gPlayerNum].cam.eye.x;
    if (0) {} //! FAKE
    zEye = gPlayer[gPlayerNum].cam.eye.z;

    Matrix_Translate(gGfxMatrix, xEye, 2.0f + gCameraShakeY, zEye, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.5f, 1.0f, 1.0f, MTXF_APPLY);

    RCP_SetupDL_37(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 125);

    Matrix_SetGfxMtx(&gMasterDisp);

    if ((gGameFrameCount % 2) != 0) {
        gSPDisplayList(gMasterDisp++, D_AQ_602C030);
    } else {
        gSPDisplayList(gMasterDisp++, D_AQ_602C088);
    }

    Matrix_Pop(&gGfxMatrix);
}
