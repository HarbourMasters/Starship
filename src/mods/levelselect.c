#include "global.h"
#include "fox_map.h"

extern PlanetId sPlanetList[15];
extern PlanetId sCurrentPlanetId;
extern s32 D_menu_801B8280;
extern s32 D_menu_801CD968;
extern s32 D_menu_801CD944;
extern s32 D_menu_801CD948;

void Map_801A61B4(LevelId level);
void Map_801A6368(void);
void Map_801A914C(void);
void Map_801A6628(void);

static PlanetId sPlanetArray[][3] = {
    { PLANET_CORNERIA, PLANET_CORNERIA, PLANET_CORNERIA }, { PLANET_METEO, PLANET_METEO, PLANET_SECTOR_Y },
    { PLANET_FORTUNA, PLANET_KATINA, PLANET_AQUAS },       { PLANET_SECTOR_X, PLANET_SOLAR, PLANET_ZONESS },
    { PLANET_TITANIA, PLANET_MACBETH, PLANET_SECTOR_Z },   { PLANET_BOLSE, PLANET_BOLSE, PLANET_AREA_6 },
    { PLANET_VENOM, PLANET_VENOM, SAVE_SLOT_VENOM_2 },
};

void Map_LevelSelect(void) {
    static s32 mission = 0;
    static s32 difficulty = 0;
    static char* sLevelSelectPlanetNames[] = {
        "METEO",  "AREA 6",   "BOLSE",   "SECTOR Z", "SECTOR X", "SECTOR Y", "KATINA", "MACBETH",
        "ZONESS", "CORNERIA", "TITANIA", "AQUAS",    "FORTUNA",  "VENOM 1",  "SOLAR",  "VENOM 2",
    };
    static s32 startOption = 0;
    // static f32 zStart = 0.0f;
    // f32 zInc;
    s32 nextPlanetId;

    if (gControllerPress[0].button & L_JPAD) {
        mission--;
        if (mission < 0) {
            mission = 6;
        }
    } else if (gControllerPress[0].button & R_JPAD) {
        mission++;
        if (mission > 6) {
            mission = 0;
        }
    } else if ((gControllerPress[0].button & U_JPAD) && (mission != 0)) {
        difficulty++;
        if (difficulty > 2) {
            difficulty = 0;
        }
        if ((difficulty == 1) && ((mission == 1) || (mission == 5) || (mission == 6))) {
            difficulty = 2;
        }
    } else if ((gControllerPress[0].button & D_JPAD) && (mission != 0)) {
        difficulty--;
        if ((difficulty != 2) && ((mission == 1) || (mission == 5) || (mission == 6))) {
            difficulty--;
        }
        if (difficulty < 0) {
            difficulty = 2;
        }
    }

    nextPlanetId =
        (sPlanetArray[mission][difficulty] == SAVE_SLOT_VENOM_2) ? PLANET_VENOM : sPlanetArray[mission][difficulty];
    if (sCurrentPlanetId != nextPlanetId) {
        sCurrentPlanetId = nextPlanetId;
        startOption = 0;
        Map_801A6368();
        Map_801A914C();
    }
    if (gControllerPress[0].button & L_TRIG) {
        startOption ^= 1;
    }

    // if (gControllerPress[0].button & U_CBUTTONS) {
    //     zInc = 100.0f;
    // } else if (gControllerPress[0].button & R_CBUTTONS) {
    //     zInc = 1000.0f;
    // } else if (gControllerPress[0].button & D_CBUTTONS) {
    //     zInc = -100.0f;
    // } else if (gControllerPress[0].button & L_CBUTTONS) {
    //     zInc = -1000.0f;
    // }
    // if (gControllerHold[0].button & R_TRIG) {
    //     zInc *= 100.0f;
    // }
    // zStart += zInc;
    // if(zStart < 0.0f) {
    //     zStart = 0.0f;
    // } else if (zStart > 500000.0f) {
    //     zStart = 500000.0f;
    // }

    /* Draw */
    if ((sCurrentPlanetId >= 0) && (sCurrentPlanetId < PLANET_MAX)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

        Graphics_DisplaySmallText(20, 200, 1.0f, 1.0f, "PLANET:");
        Graphics_DisplaySmallText(80, 200, 1.0f, 1.0f, sLevelSelectPlanetNames[sPlanetArray[mission][difficulty]]);

        if (startOption) {
            if ((sCurrentPlanetId == PLANET_SECTOR_X) || (sCurrentPlanetId == PLANET_METEO)) {
                Graphics_DisplaySmallText(80, 210, 1.0f, 1.0f, "WARP ZONE");
            } else if (sCurrentPlanetId == PLANET_VENOM) {
                Graphics_DisplaySmallText(80, 210, 1.0f, 1.0f, "ANDROSS");
            } else if (sCurrentPlanetId == PLANET_AREA_6) {
                Graphics_DisplaySmallText(80, 210, 1.0f, 1.0f, "BETA SB");
            }
        }
    }

    // Bypass briefing
    if ((D_menu_801CD944 == 2) && (D_menu_801CD948 > 0)) {
        if (sCurrentPlanetId == PLANET_VENOM) {
            if (startOption) {
                gCurrentLevel = LEVEL_VENOM_ANDROSS;
            } else if (sPlanetArray[mission][difficulty] == SAVE_SLOT_VENOM_2) {
                gCurrentLevel = LEVEL_VENOM_2;
            }
        } else if ((sCurrentPlanetId == PLANET_AREA_6) && startOption) {
            gCurrentLevel = LEVEL_UNK_4;
        }
        Map_801A61B4(gCurrentLevel);
        D_menu_801B8280 = 0;
        D_menu_801CD968 = 0;
        Map_801A6628();
        if (startOption && ((gCurrentLevel == LEVEL_METEO) || (gCurrentLevel == LEVEL_SECTOR_X) ||
                            (sPlanetArray[mission][difficulty] == SAVE_SLOT_VENOM_2))) {
            gLevelPhase = 1;
        }
        // gSavedPathProgress = gPathProgress = zStart;
    }
}
