#include "object_ram.h"

static RamEntry oRamEntries[7] = {
    ORAM_ENTRY(PlayerShot, 15, obj.id, u8),
    ORAM_ENTRY(Player, 0, pos.y, f32),
    ORAM_ENTRY(Player, 0, pos.z, f32),
    ORAM_ENTRY(Actor, 0, obj.status, x32),
    ORAM_OFF,
    ORAM_OFF,
    ORAM_OFF,
};

static s32 holdTimer = 0;
static s32 selectNum = 0;
static RamModMode oRamActive = RAMMOD_OFF;
static s32 editMode = EDM_TYPE;
static s32 editing = false;
static s32 editingValue = false;
static fu dataTemp;
static OSContPad* contPress;
static OSContPad* contHold;

static ObjArrayInfo objArrays[] = {
    { NULL, 0, 1, "--" },
    { NULL, sizeof(Player), 1, "PL" },
    { NULL, sizeof(Scenery360), 200, "SC" },
    OBJ_ARRAY_INFO(gScenery, "SC"),
    OBJ_ARRAY_INFO(gSprites, "SP"),
    OBJ_ARRAY_INFO(gActors, "AC"),
    OBJ_ARRAY_INFO(gBosses, "BS"),
    OBJ_ARRAY_INFO(gItems, "IT"),
    OBJ_ARRAY_INFO(gEffects, "EF"),
    OBJ_ARRAY_INFO(gPlayerShots, "SH"),
    OBJ_ARRAY_INFO(gTexturedLines, "TL"),
    OBJ_ARRAY_INFO(gRadarMarks, "RM"),
    OBJ_ARRAY_INFO(gBonusText, "BT"),
};

void ObjectRam_EditPosition(RamEntry* entry) {
    if ((contPress->button & U_JPAD) && (entry->y > 0)) {
        entry->y--;
    } else if ((contPress->button & D_JPAD) && (entry->y < SCREEN_HEIGHT)) {
        entry->y++;
    } else if ((contPress->button & L_JPAD) && (entry->x > 0)) {
        entry->x--;
    } else if ((contPress->button & R_JPAD) && (entry->x < SCREEN_WIDTH / 2)) {
        entry->x++;
    }
}

void ObjectRam_EditObject(RamEntry* entry) {
    if (contPress->button & U_JPAD) {
        entry->type++;
        if ((entry->type == ORAM_Scenery360) && (gLevelMode != LEVELMODE_ALL_RANGE)) {
            entry->type = ORAM_Scenery;
        } else if ((entry->type == ORAM_Scenery) && (gLevelMode == LEVELMODE_ALL_RANGE)) {
            entry->type = ORAM_Sprite;
        }
    } else if (contPress->button & D_JPAD) {
        entry->type--;
        if ((entry->type == ORAM_Scenery360) && (gLevelMode != LEVELMODE_ALL_RANGE)) {
            entry->type = ORAM_Player;
        } else if ((entry->type == ORAM_Scenery) && (gLevelMode == LEVELMODE_ALL_RANGE)) {
            entry->type = ORAM_Scenery360;
        }
    }
    entry->type = WRAP_MODE(entry->type, ORAM_MAX);
}

void ObjectRam_EditIndex(RamEntry* entry) {
    ObjArrayInfo* objInfo = &objArrays[entry->type];

    entry->index = MIN(entry->index, objInfo->count - 1);

    if (contPress->button & U_JPAD) {
        entry->index++;
    } else if (contPress->button & D_JPAD) {
        entry->index--;
    }

    entry->index = WRAP_MODE(entry->index, objInfo->count);
}

void ObjectRam_EditFormat(RamEntry* entry) {
    if (contPress->button & U_JPAD) {
        entry->fmt--;
    } else if (contPress->button & D_JPAD) {
        entry->fmt++;
    }
    entry->fmt = WRAP_MODE(entry->fmt, FMT_MAX);
    if (entry->fmt == FMT_FLOAT) {
        entry->width = 2;
        entry->offset &= ~((1 << entry->width) - 1);
    }
}

void ObjectRam_EditWidth(RamEntry* entry) {
    if ((contPress->button & U_JPAD) && (entry->width < 2)) {
        entry->width++;
    } else if ((contPress->button & D_JPAD) && (entry->width > 0)) {
        entry->width--;
    }
    if (entry->fmt == FMT_FLOAT) {
        entry->width = 2;
    }
    entry->offset &= ~((1 << entry->width) - 1);
}

void ObjectRam_EditOffset(RamEntry* entry) {
    s32 inc;
    ObjArrayInfo* objInfo = &objArrays[entry->type];

    entry->offset = MIN(entry->offset, objInfo->size - (1 << entry->width));

    if (contHold->button & Z_TRIG) {
        inc = 0x10;
    } else if (contHold->button & R_TRIG) {
        inc = 0x100;
    } else {
        inc = 1 << entry->width;
    }
    inc *= (contPress->button & D_JPAD) ? -1 : 1;
    if (contPress->button & (U_JPAD | D_JPAD)) {
        entry->offset += inc;
    }
    if (entry->offset < 0) {
        entry->offset = 0;
    } else if (entry->offset >= objInfo->size) {
        entry->offset = objInfo->size - (1 << entry->width);
    }
}

void ObjectRam_EditValue(RamEntry* entry) {
    fu* data = entry->dataPtr;
    s32 inc;

    if (contHold->button & Z_TRIG) {
        inc = (entry->fmt == FMT_HEX) ? 0x10 : 10;
    } else if (contHold->button & R_TRIG) {
        inc = (entry->fmt == FMT_HEX) ? 0x100 : 100;
    } else {
        inc = 1;
    }
    inc *= (contPress->button & D_JPAD) ? -1 : 1;

    if (contPress->button & (U_JPAD | D_JPAD)) {
        if (!editingValue) {
            dataTemp.i = ObjectRam_GetData(entry);
            editingValue = true;
        }
        if (entry->fmt == FMT_FLOAT) {
            dataTemp.f += inc;
        } else {
            dataTemp.i += inc;
        }
    }
}

void ObjectRam_Select(void) {
    if ((contPress->button & U_JPAD) && !editing) {
        selectNum--;
    } else if ((contPress->button & D_JPAD) && !editing) {
        selectNum++;
    } else if (contPress->button & L_JPAD) {
        editMode--;
    } else if (contPress->button & R_JPAD) {
        editMode++;
    }
    selectNum = WRAP_MODE(selectNum, ARRAY_COUNT(oRamEntries));
    editMode = WRAP_MODE(editMode, EDM_MAX);
    if (oRamEntries[selectNum].type == ORAM_NONE) {
        editMode = EDM_TYPE;
    }
}

u32 ObjectRam_GetData(RamEntry* entry) {
    fu data;
    uintptr_t ptr;
    s32 offset;
    s32 index;

    if ((entry->type <= ORAM_NONE) || (entry->type >= ORAM_MAX)) {
        return 0;
    }

    switch (entry->width) {
        case 0:
            data.i = *((u8*) entry->dataPtr);
            if ((entry->fmt == FMT_SIGN) && (data.i >= 0x80)) {
                data.i -= 0x80;
            }
            break;
        case 1:
            data.i = *((u16*) entry->dataPtr);
            if ((entry->fmt == FMT_SIGN) && (data.i >= 0x8000)) {
                data.i -= 0x8000;
            }
            break;
        case 2:
            if (entry->fmt == FMT_FLOAT) {
                data.f = *((f32*) entry->dataPtr);
            } else {
                data.i = *((u32*) entry->dataPtr);
            }
            break;
    }
    return data.i;
}

void ObjectRam_WriteValue(RamEntry* entry) {
    switch (entry->width) {
        case 0:
            *((u8*) entry->dataPtr) = dataTemp.i;
            break;
        case 1:
            *((u16*) entry->dataPtr) = dataTemp.i;
            break;
        case 2:
            if (entry->fmt == FMT_FLOAT) {
                *((f32*) entry->dataPtr) = dataTemp.f;
            } else {
                *((u32*) entry->dataPtr) = dataTemp.i;
            }
            break;
    }
}

static char* objTypes[] = { "--", "PL", "SC", "SC", "SP", "AC", "BS", "IT", "EF", "SH", "TL", "RM", "BT" };
static char* fmtTypes[] = { "X", "S", "U", "F" };

#define SET_DRAW_COLOR(mode)                                        \
    if (num == selectNum) {                                         \
        if (editing && (editMode == mode)) {                        \
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 0, 0, 255);   \
        } else if (editing || (editMode == mode)) {                 \
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 85, 0, 255);  \
        } else {                                                    \
            gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 170, 0, 255); \
        }                                                           \
    } else {                                                        \
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);     \
    }

void ObjectRam_DrawEntry(RamEntry* entry, s32 num) {
    fu data;
    s32 x = entry->x;
    s32 y = entry->y + 50 + 27 * num;
    s32 i;
    s32 offset;
    s32 index;
    ObjArrayInfo* objInfo;

    if ((entry->type < ORAM_NONE) || (entry->type >= ORAM_MAX)) {
        return;
    }

    objInfo = &objArrays[entry->type];

    offset = MIN(entry->offset, objInfo->size - (1 << entry->width));
    index = MIN(entry->index, objInfo->count - 1);

    entry->objPtr = (uintptr_t) objInfo->ptr + index * objInfo->size;
    entry->dataPtr = (uintptr_t) entry->objPtr + offset;

    SET_DRAW_COLOR(EDM_TYPE)
    Graphics_DisplaySmallText(x + 10, y, 1.0f, 1.0f, objInfo->name);

    if (entry->type == ORAM_NONE) {
        return;
    }
    SET_DRAW_COLOR(EDM_MAX)
    Graphics_DisplaySmallText(x + 26, y, 1.0f, 1.0f, "-");

    SET_DRAW_COLOR(EDM_INDEX)
    Graphics_Printf("%02d", index);
    Graphics_DisplaySmallText(x + 32, y, 1.0f, 1.0f, D_801619A0);

    SET_DRAW_COLOR(EDM_MAX)
    Graphics_DisplaySmallText(x + 50, y, 1.0f, 1.0f, ".");

    SET_DRAW_COLOR(EDM_OFFSET)
    Graphics_Printf("%03X", offset);
    Graphics_DisplaySmallText(x + 56, y, 1.0f, 1.0f, D_801619A0);

    SET_DRAW_COLOR(EDM_FORMAT)
    Graphics_DisplaySmallText(x + 90, y, 1.0f, 1.0f, fmtTypes[entry->fmt]);
    SET_DRAW_COLOR(EDM_WIDTH)
    Graphics_Printf("%-2d", 1 << (entry->width + 3));
    Graphics_DisplaySmallText(x + 100, y, 1.0f, 1.0f, D_801619A0);

    SET_DRAW_COLOR(EDM_VALUE)
    if ((num != selectNum) || !editingValue) {
        data.i = ObjectRam_GetData(entry);
    } else if (entry->fmt == FMT_FLOAT) {
        data.f = dataTemp.f;
    } else {
        data.i = dataTemp.i;
    }

    switch (entry->fmt) {
        case FMT_HEX:
            Graphics_Printf("0X%0*X", 1 << (entry->width + 1), data.i);
            x += (8 - (1 << (entry->width + 1))) * 9;
            break;
        case FMT_SIGN:
            Graphics_Printf("%10d", data.i);
            break;
        case FMT_UNSIGN:
            Graphics_Printf("%10u", data.i);
            break;
        case FMT_FLOAT:
            Graphics_Printf("%10.2f", data.f);
            break;
    }
    Graphics_DisplaySmallText(x + 25, y + 12, 1.0f, 1.0f, D_801619A0);
}

// static char* omStr[] = { "OBJECT", "INDEX", "OFFSET", "FORMAT", "WIDTH", "VALUE" }; // "POSITION" };

void ObjectRam_Update(void) {
    s32 i;
    objArrays[ORAM_Player].ptr = gPlayer;
    objArrays[ORAM_Scenery360].ptr = gScenery360;
    objArrays[ORAM_Player].count = gCamCount;

    if (contPress->button & L_TRIG) {
        editing ^= 1;
    }

    ObjectRam_Select();

    if (editingValue && !(editing && (editMode == EDM_VALUE))) {
        ObjectRam_WriteValue(&oRamEntries[selectNum]);
        editingValue = false;
    }

    if (editing) {
        switch (editMode) {
            case EDM_TYPE:
                ObjectRam_EditObject(&oRamEntries[selectNum]);
                break;
            case EDM_INDEX:
                ObjectRam_EditIndex(&oRamEntries[selectNum]);
                break;
            case EDM_OFFSET:
                ObjectRam_EditOffset(&oRamEntries[selectNum]);
                break;
            case EDM_FORMAT:
                ObjectRam_EditFormat(&oRamEntries[selectNum]);
                break;
            case EDM_WIDTH:
                ObjectRam_EditWidth(&oRamEntries[selectNum]);
                break;
            case EDM_VALUE:
                ObjectRam_EditValue(&oRamEntries[selectNum]);
                break;
                // case EDM_POS:
                //     ObjectRam_EditPosition(&oRamEntries[selectNum]);
                //     break;
        }
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    // Graphics_DisplaySmallText(20, 50, 1.0f, 1.0f, omStr[editMode]);
    for (i = 0; i < ARRAY_COUNT(oRamEntries); i++) {
        ObjectRam_DrawEntry(&oRamEntries[i], i);
    }

    if ((oRamEntries[selectNum].type > ORAM_Player) && (oRamEntries[selectNum].type < ORAM_TexturedLine)) {
        gTexturedLines[99].mode = 3;
        gTexturedLines[99].xyScale = 3.0f;
        gTexturedLines[99].posAA.x = gPlayer[0].pos.x;
        gTexturedLines[99].posAA.y = gPlayer[0].pos.y;
        gTexturedLines[99].posAA.z = gPlayer[0].pos.z - 100.0f;
        if (oRamEntries[selectNum].objPtr->status != OBJ_FREE) {
            gTexturedLines[99].timer = 15;
        }
        gTexturedLines[99].prim.r = 255;
        gTexturedLines[99].prim.g = (editing) ? 128 : 255;
        gTexturedLines[99].prim.b = 0;
        gTexturedLines[99].prim.a = 255;
        gTexturedLines[99].posBB.x = oRamEntries[selectNum].objPtr->pos.x;
        gTexturedLines[99].posBB.y = oRamEntries[selectNum].objPtr->pos.y;
        gTexturedLines[99].posBB.z = oRamEntries[selectNum].objPtr->pos.z;
    }
}

bool sCheatSetup = false;

s32 sCheatOptions[] = { 2, 5, 1, 2, 1, 4, 2, 1, 2 };
s32 sCheatStates[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

CheatEntry cheats[CHEAT_MAX];

void CheatRam_Select(void) {
    if (contPress->button & (U_JPAD | D_JPAD)) {
        editMode += (contPress->button & D_JPAD) ? 1 : -1;
        editMode = WRAP_MODE(editMode, ARRAY_COUNT(cheats));
        selectNum = cheats[editMode].option;
    } else if (contPress->button & (L_JPAD | R_JPAD)) {
        selectNum += (contPress->button & R_JPAD) ? 1 : -1;
    }
    selectNum = WRAP_MODE(selectNum, cheats[editMode].optionMax + 1);
    cheats[editMode].option = selectNum;
}

void CheatRam_RepairWings(void) {
    if ((gPlayer[0].wings.rightState <= WINGSTATE_BROKEN) || (gPlayer[0].wings.leftState <= WINGSTATE_BROKEN)) {
        func_enmy_80067A40();
    }
}

void CheatRam_SpawnCheckpoint(void) {
    static ItemCheckpoint* checkpoint = NULL;
    s32 i;

    if ((gLevelMode != LEVELMODE_ON_RAILS) || (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_ACTIVE)) {
        return;
    }

    if ((checkpoint != NULL) && (checkpoint->obj.status != OBJ_FREE)) {
        return;
    }
    for (i = 0; i < ARRAY_COUNT(gItems); i++) {
        if (gItems[i].obj.status == OBJ_FREE) {
            Item_Initialize(&gItems[i]);
            gItems[i].obj.status = OBJ_ACTIVE;
            gItems[i].obj.id = OBJ_ITEM_CHECKPOINT;
            gItems[i].obj.pos.x = gPlayer[0].pos.x + gPlayer[0].vel.x;
            gItems[i].obj.pos.y = gPlayer[0].pos.y + gPlayer[0].vel.y;
            gItems[i].obj.pos.z = gPlayer[0].trueZpos + gPlayer[0].vel.z;
            Object_SetInfo(&gItems[i].info, gItems[i].obj.id);
            break;
        }
    }
    if (i == ARRAY_COUNT(gItems)) {
        checkpoint = NULL;
    }
}

void CheatRam_Setup(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(cheats); i++) {
        CheatEntry* cheat = &cheats[i];

        cheat->mode = i;
        switch (cheat->mode) {
            case CHEAT_SHIELDS:
                cheat->option = cheat->optionMax = 100;
                SET_CHEAT_RAM(&cheat->ram[0], &gPlayer[0].shields, Play_GetMaxShields())
                break;
            case CHEAT_LASERS:
                cheat->option = LASERS_HYPER;
                cheat->optionMax = LASERS_MAX - 1;
                SET_CHEAT_RAM(&cheat->ram[0], &gLaserStrength[0], cheat->option)
                cheat->ram[1].func = CheatRam_RepairWings;
                break;
            case CHEAT_BOMBS:
                cheat->option = cheat->optionMax = 9;
                SET_CHEAT_RAM(&cheat->ram[0], &gBombCount[0], cheat->option)
                break;
            case CHEAT_BOOST:
                SET_CHEAT_RAM(&cheat->ram[0], &gPlayer[0].boostMeter, 0)
                SET_CHEAT_RAM(&cheat->ram[1], &gPlayer[0].boostCooldown, false)
                cheat->action = 1;
                break;
            case CHEAT_LIVES:
                cheat->option = cheat->optionMax = 99;
                SET_CHEAT_RAM(&cheat->ram[0], &gLifeCount[0], cheat->option)
                break;
            case CHEAT_TEAMMATES:
                cheat->option = 0;
                cheat->optionMax = 7;
                SET_CHEAT_RAM(&cheat->ram[0], &gTeamShields[TEAM_ID_FALCO], 255)
                SET_CHEAT_RAM(&cheat->ram[1], &gTeamShields[TEAM_ID_SLIPPY], 255)
                SET_CHEAT_RAM(&cheat->ram[2], &gTeamShields[TEAM_ID_PEPPY], 255)
                break;
            case CHEAT_SPEED:
                cheat->option = 60;
                cheat->optionMax = 100;
                cheat->action = 1;
                SET_CHEAT_RAM(&cheat->ram[0], &gPlayer[0].baseSpeed, cheat->option)
                break;
            case CHEAT_HITS:
                cheat->option = 500;
                cheat->optionMax = 999;
                SET_CHEAT_RAM(&cheat->ram[0], &gHitCount, cheat->option);
                break;
            case CHEAT_CHECKPOINT:
                cheat->action = -1;
                cheat->ram[0].func = CheatRam_SpawnCheckpoint;
                break;
            case CHEAT_COMPLETE:
                cheat->option = MISSION_COMPLETE;
                cheat->optionMax = MISSION_WARP;
                cheat->action = 1;
                if ((gCurrentLevel == LEVEL_METEO) || (gCurrentLevel == LEVEL_SECTOR_X)) {}
                SET_CHEAT_RAM(&cheat->ram[0], &gMissionStatus, cheat->option)
                break;
        }
    }
}

void CheatRam_SetValues(CheatRamEntry* cheat) {
    s32 i;

    for (i = 0; i < 4; i++) {
        if (cheat[i].addr != NULL) {
            switch (cheat[i].size) {
                case 0:
                    cheat[i].func();
                    break;
                case 1:
                    *((u8*) cheat[i].addr) = cheat[i].data.i;
                    break;
                case 2:
                    *((u16*) cheat[i].addr) = cheat[i].data.i;
                    break;
                case 3:
                    break;
                case 4:
                    *cheat[i].addr = cheat[i].data;
                    break;
            }
        }
    }
}

void CheatRam_UpdateEntry(CheatEntry* cheat) {
    s32 teamnum;
    s32 i;
    s32 press = false;
    s32 doublepress = false;

    if (holdTimer == 0) {
        holdTimer = 10;
        press = true;
    } else if (holdTimer != 0) {
        doublepress = true;
    }
    if (cheat->action == 0) {
        cheat->hold ^= doublepress;
    } else if (cheat->action == 1) {
        cheat->hold ^= press;
    }

    switch (editMode) {
        case CHEAT_SHIELDS:
            cheat->ram[0].data.i = (cheat->option / 100.0f) * Play_GetMaxShields();
            break;
        case CHEAT_BOOST:
            break;
        case CHEAT_SPEED:
            cheat->ram[0].data.f = cheat->hold ? cheat->option : 40.0f;
            break;
        case CHEAT_TEAMMATES:
            teamnum = (cheat->option % 4) - 1;
            for (i = 0; i < 3; i++) {
                cheat->ram[i].data.i = (cheat->option > 3) ? -1 : 255;
                cheat->ram[i].size = (teamnum == -1) ? 4 : 3;
            }
            if (teamnum != -1) {
                cheat->ram[teamnum].size = 4;
            }
            break;
        case CHEAT_COMPLETE:
            if ((gCurrentLevel == LEVEL_CORNERIA) && (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
                if ((gLevelMode == LEVELMODE_ON_RAILS) && (cheat->option == MISSION_COMPLETE)) {
                    gScenery360 = Memory_Allocate(200 * sizeof(Scenery360));
                    gLevelMode = LEVELMODE_ALL_RANGE;
                } else if ((gLevelMode == LEVELMODE_ALL_RANGE) && (cheat->option == MISSION_ACCOMPLISHED)) {
                    gLevelMode = LEVELMODE_ON_RAILS;
                }
            }
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
        default:
            cheat->ram[0].data.i = cheat->option;
            break;
    }

    CheatRam_SetValues(cheat->ram);
}

const char* cheatNames[] = { "SHIELDS", "LASERS", "BOMBS", "BOOST",      "LIVES",
                             "TEAM",    "SPEED",  "HITS",  "CHECKPOINT", "MISSION" };
const char* laserNames[] = { "SINGLE", "TWIN", "HYPER", "UNUSED" };
const char* teamNames[] = { "ALL", "FALCO", "SLIPPY", "PEPPY" };
const char* statusNames[] = { "COMPLETE", "ACCOMPLISHED", "WARP" };

void CheatRam_DrawEntry(CheatMode mode, s32 x, s32 y, s32 option) {
    switch (mode) {
        case CHEAT_SHIELDS:
        case CHEAT_HITS:
            Graphics_Printf("%s: %3d", cheatNames[mode], option);
            break;
        case CHEAT_LASERS:
            Graphics_Printf("%s: %s", cheatNames[mode], laserNames[option]);
            break;
        case CHEAT_COMPLETE:
            Graphics_Printf("%s: %s", cheatNames[mode], statusNames[option]);
            break;
        case CHEAT_LIVES:
        case CHEAT_BOMBS:
        case CHEAT_SPEED:
            Graphics_Printf("%s: %d", cheatNames[mode], option);
            break;
        case CHEAT_CHECKPOINT:
        case CHEAT_BOOST:
            Graphics_Printf("%s", cheatNames[mode]);
            break;
        case CHEAT_TEAMMATES:
            Graphics_Printf("%s: %s %s", cheatNames[mode], (option > 3) ? "DOWN" : "HEAL", teamNames[option % 4]);
            break;
    }
    Graphics_DisplaySmallText(x, y, 1.0f, 1.0f, D_801619A0);
}

s32 medalCount[] = { 150, 200, 150, 300, 0, 200, 100, 250, 200, 0, 150, 100, 150, 50, 0, 150, 150, 100, 200 };

void CheatRam_Update(void) {
    s32 i;
    s32 x = 10;
    s32 y = 50;

    if (!sCheatSetup) {
        CheatRam_Setup();
        selectNum = cheats[editMode].option;
        sCheatSetup = true;
    }
    CheatRam_Select();
    if (holdTimer != 0) {
        holdTimer--;
    }
    if (contPress->button & L_TRIG) {
        CheatRam_UpdateEntry(&cheats[editMode]);
    }
    for (i = 0; i < ARRAY_COUNT(cheats); i++) {
        if ((cheats[i].action != -1) && (cheats[i].hold || ((i == editMode) && (holdTimer != 0)))) {
            CheatRam_SetValues(cheats[i].ram);
        }
    }
    RCP_SetupDL(&gMasterDisp, SETUPDL_76);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplaySmallText(x, y, 1.0f, 1.0f, "CHEATS");
    y += 14;
    for (i = 0; i < ARRAY_COUNT(cheats); i++) {
        if (cheats[i].hold) {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
        } else if (i == editMode) {
            if (holdTimer == 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 170, 0, 255);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 85, 0, 255);
            }
        } else {
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
        }

        CheatRam_DrawEntry(cheats[i].mode, x, y + 11 * i, cheats[i].option);
    }
}

void RamMod_Update(void) {
    contPress = &gControllerPress[gMainController];
    contHold = &gControllerHold[gMainController];

    if ((gGameState != GSTATE_PLAY) || (gPlayState <= PLAY_INIT)) {
        return;
    }

    if ((contPress->button & START_BUTTON) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_LEVEL_COMPLETE)) {
        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_NEXT;
        Audio_FadeOutAll(10);
        gFadeoutType = 4;
        gLeveLClearStatus[gCurrentLevel] = Play_CheckMedalStatus(medalCount[gCurrentLevel]) + 1;
        cheats[CHEAT_COMPLETE].hold = false;
    }

    if ((gPlayState == PLAY_PAUSE) && (contPress->button & R_CBUTTONS)) {
        oRamActive++;
        oRamActive = WRAP_MODE(oRamActive, RAMMOD_MAX);
    }

    switch (oRamActive) {
        case RAMMOD_OFF:
            break;
        case RAMMOD_CHEAT:
            CheatRam_Update();
            break;
        case RAMMOD_OBJECT:
            ObjectRam_Update();
            break;
    }
}
