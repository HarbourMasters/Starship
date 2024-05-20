/*
 * File: fox_co.c
 * System: Corneria
 * Description: Level: Corneria
 */

#include "global.h"
#include "assets/ast_arwing.h"
#include "assets/ast_corneria.h"

u8 D_i1_8019B6D0;
f32 D_i1_8019B6D8[68];

void Corneria_80187530(Scenery* scenery) {
}

void Corneria_8018753C(Scenery* scenery) {
    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, D_CO_60199D0);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
}

void Corneria_801875A4(Sprite* sprite) {
    f32 sp1C;
    f32 sp18;
    f32 var_f;

    if (((gGameFrameCount % 4) == 0)) {
        sp1C = RAND_FLOAT_CENTERED(10.0f);
        sp18 = RAND_FLOAT_CENTERED(10.0f);
        var_f = RAND_FLOAT(0.5f) + 1.0f;
        func_effect_8007C85C(sprite->obj.pos.x + sp1C, sprite->obj.pos.y + sp18, sprite->obj.pos.z, 4.0f * var_f);
    }
}

void Corneria_80187670(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 arg4, f32 xRot, f32 yRot, s32 arg7, s32 arg8,
                       ObjectId objId) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = objId;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    actor->obj.rot.x = xRot;
    actor->obj.rot.y = yRot;
    actor->timer_0BC = arg7;
    actor->timer_0BE = 20;
    actor->eventType = arg8;
    actor->fwork[5] = arg4;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Corneria_80187710(f32 xPos, f32 yPos, f32 zPos, f32 arg3, f32 xRot, f32 yRot, s32 arg6, s32 arg7, ObjectId objId) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            PRINTF("Enms[1].obj.mode %d\n");
            Corneria_80187670(&gActors[i], xPos, yPos, zPos, arg3, xRot, yRot, arg6, arg7, objId);
            return;
        }
    }
}

void Corneria_801877A0(Boss* boss, f32 x, f32 y, f32 z) {
    Vec3f src;
    Vec3f dest;

    src.x = x;
    src.y = y;
    src.z = z;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    func_effect_8007F11C(OBJ_EFFECT_353, boss->obj.pos.x + dest.x, boss->obj.pos.y + dest.y, boss->obj.pos.z + dest.z,
                         100.0f);
}

// Maybe Corneria_SpawnItem
void Corneria_80187838(Boss* arg0, f32 x, f32 y, f32 z, ObjectId item) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gItems); i++) {
        if (gItems[i].obj.status == OBJ_FREE) {
            Item_Initialize(&gItems[i]);
            gItems[i].obj.status = OBJ_INIT;
            gItems[i].obj.id = item;
            gItems[i].timer_4A = 8;
            gItems[i].obj.pos.x = x;
            gItems[i].obj.pos.y = y;
            gItems[i].obj.pos.z = z;
            Object_SetInfo(&gItems[i].info, gItems[i].obj.id);
            return;
        }
    }
}

void Corneria_Boss292_Init(Boss292* this) {
    s32 i;

    gBossFrameCount = 0;

    if (gLevelMode == LEVELMODE_ON_RAILS) {
        if (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) {
            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_START_360;
            gPlayer[0].csState = 0;
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
        }
        Object_Kill(&this->obj, this->sfxSource);
        return;
    }

    for (i = 0; i < ARRAY_COUNT(D_i1_8019B6D8); i++) {
        D_i1_8019B6D8[i] = 0.0f;
    }
}

void Corneria_8018798C(Boss* boss, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_effect_8007BFFC(arg1, arg2, arg3, 0.0f, 0.0f, 0.0f, arg4, 30);
    func_effect_8007A6F0(&boss->obj.pos, NA_SE_OB_DAMAGE_M);
}

void Corneria_801879F0(Boss* boss, f32 arg1, f32 arg2, f32 arg3, f32 arg4) {
    func_effect_8007D1E0(arg1, arg2, arg3, arg4);
    func_effect_8007A6F0(&boss->obj.pos, NA_SE_OB_DAMAGE_M);
}

void Corneria_80187A38(Boss* boss, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5) {
    func_effect_8007C120(arg1, arg2, arg3, boss->vel.x, boss->vel.y, boss->vel.z, arg4, arg5);
}

f32 Corneria_80187A88(s32 arg0) {
    f32 ret = arg0 * 0.5f;

    if (ret > 8.0f) {
        ret = 8.0f;
    }
    return ret;
}

void Corneria_80187AC8(Boss* boss) {
    Sprite* sprite;
    s32 item;
    s32 var_s1;
    s32 var_s1_2;

    if (boss->dmgType != DMG_NONE) {
        boss->dmgType = DMG_NONE;

        if (boss->dmgPart == 0) {
            boss->swork[10] = 15;
            boss->swork[29] -= boss->damage;

            Corneria_80187A38(boss, D_i1_8019B6D8[62], D_i1_8019B6D8[63], D_i1_8019B6D8[64], 0.2f, 20);

            if (boss->swork[29] < 30) {
                func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_KNOCK_DOWN);
            } else {
                func_effect_8007A6F0(&boss->obj.pos, NA_SE_OB_DAMAGE_M);
            }

            Radio_PlayMessage(gMsg_ID_2270, RCID_BOSS_CORNERIA);

            if (boss->swork[29] <= 0) {
                boss->swork[10] = 1000;
                boss->info.hitbox[1 + 0] = 100000.0f;

                Corneria_8018798C(boss, D_i1_8019B6D8[62], D_i1_8019B6D8[63], D_i1_8019B6D8[64], 10.0f);

                AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);

                gScreenFlashTimer = 8;

                if (fabsf(boss->obj.rot.x) < 20.0f) {
                    boss->swork[32] = 1;
                }

                boss->state = 7;
                boss->timer_050 = 100;

                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 80);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 80);

                gCsFrameCount = 0;

                if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                    (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_LEVEL_COMPLETE;
                    gPlayer[0].csState = gPlayer[0].csTimer = 0;
                    gPlayer[0].rot.y += gPlayer[0].yRot_114;

                    if (gPlayer[0].rot.y > 360.0f) {
                        gPlayer[0].rot.y -= 360.0f;
                    }
                    if (gPlayer[0].rot.y < 0.0f) {
                        gPlayer[0].rot.y += 360.0f;
                    }
                    gPlayer[0].yRot_114 = 0.0f;
                }

                Radio_PlayMessage(gMsg_ID_2280, RCID_BOSS_CORNERIA);

                Boss_AwardBonus(boss);

                gBossFrameCount = 100000;
                return;
            }
        } else if (boss->dmgPart == 3) {
            boss->swork[3] = 15;
            boss->swork[20] = 30;
            boss->swork[28] -= boss->damage;

            Corneria_801879F0(boss, D_i1_8019B6D8[12] + RAND_FLOAT_CENTERED(60.0f), D_i1_8019B6D8[13],
                              D_i1_8019B6D8[14] + RAND_FLOAT_CENTERED(60.0f), 2.0f);
            Corneria_80187A38(boss, D_i1_8019B6D8[12], D_i1_8019B6D8[13], D_i1_8019B6D8[14], 0.1f, 20);

            if (boss->swork[28] <= 0) {
                boss->swork[3] = 1000;
                boss->info.hitbox[1 + 18] = 100000.0f;
                Corneria_8018798C(boss, D_i1_8019B6D8[12], D_i1_8019B6D8[13], D_i1_8019B6D8[14], 10.0f);
            }
        }

        if (boss->dmgPart == 1) {
            boss->swork[2] = 15;
            boss->swork[21] = 30;
            boss->swork[26] -= boss->damage;

            Corneria_801879F0(boss, D_i1_8019B6D8[6] + RAND_FLOAT_CENTERED(60.0f), D_i1_8019B6D8[7],
                              D_i1_8019B6D8[8] + RAND_FLOAT_CENTERED(60.0f), 2.0f);
            Corneria_80187A38(boss, D_i1_8019B6D8[6], D_i1_8019B6D8[7], D_i1_8019B6D8[8], 0.1f, 20);

            if (boss->swork[26] <= 0) {
                boss->swork[2] = 1000;
                boss->info.hitbox[1 + 6] = 100000.0f;
                Corneria_8018798C(boss, D_i1_8019B6D8[6], D_i1_8019B6D8[7], D_i1_8019B6D8[8], 7.0f);
            }
        } else if (boss->dmgPart == 2) {
            boss->swork[1] = 15;
            boss->swork[22] = 30;
            boss->swork[27] -= boss->damage;

            Corneria_801879F0(boss, D_i1_8019B6D8[0] + RAND_FLOAT_CENTERED(60.0f), D_i1_8019B6D8[1],
                              D_i1_8019B6D8[2] + RAND_FLOAT_CENTERED(60.0f), 2.0f);
            Corneria_80187A38(boss, D_i1_8019B6D8[0], D_i1_8019B6D8[1], D_i1_8019B6D8[2], 0.1f, 20);

            if (boss->swork[27] <= 0) {
                boss->swork[1] = 1000;
                boss->info.hitbox[1 + 12] = 100000.0f;
                Corneria_8018798C(boss, D_i1_8019B6D8[0], D_i1_8019B6D8[1], D_i1_8019B6D8[2], 7.0f);
            }
        } else if ((boss->dmgPart == 4) || (boss->dmgPart == 5)) {
            AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, boss->sfxSource, 4);
            boss->swork[23] = 200;

            if (boss->dmgPart == 4) {
                boss->swork[24] -= boss->damage;
                boss->swork[7] = boss->swork[8] = boss->swork[9] = 5;
                boss->swork[18] = 30;

                if (boss->swork[24] <= 0) {
                    boss->swork[7] = boss->swork[8] = boss->swork[9] = 1000;
                    boss->info.hitbox[1 + 24] = 100000.0f;

                    for (var_s1 = 3; var_s1 < 6; var_s1++) {
                        Boss_SpawnDebris(D_i1_8019B6D8[18 + var_s1 + 2], D_i1_8019B6D8[24 + var_s1 + 2],
                                         D_i1_8019B6D8[30 + var_s1 + 2], D_i1_8019B6D8[36 + var_s1 + 2],
                                         D_i1_8019B6D8[42 + var_s1 + 2], D_i1_8019B6D8[48 + var_s1 + 2], 0.0f,
                                         RAND_FLOAT(20.0f), 0.0f, 5.5f, var_s1 + 28, RAND_INT(30.0f) + 60.0f);
                    }

                    if (boss->state < 5) {
                        boss->state = 5;
                        boss->timer_050 = 60;
                    }
                }
            } else {
                boss->swork[25] -= boss->damage;
                boss->swork[4] = boss->swork[5] = boss->swork[6] = 5;
                boss->swork[19] = 30;

                if (boss->swork[25] <= 0) {
                    boss->swork[4] = boss->swork[5] = boss->swork[6] = 1000;
                    boss->info.hitbox[1 + 30] = 100000.0f;

                    for (var_s1 = 0; var_s1 < 3; var_s1++) {
                        Boss_SpawnDebris(D_i1_8019B6D8[18 + var_s1 + 2], D_i1_8019B6D8[24 + var_s1 + 2],
                                         D_i1_8019B6D8[30 + var_s1 + 2], D_i1_8019B6D8[36 + var_s1 + 2],
                                         D_i1_8019B6D8[42 + var_s1 + 2], D_i1_8019B6D8[48 + var_s1 + 2], 0.0f,
                                         RAND_FLOAT(20.0f), 0.0f, 5.5f, var_s1 + 28, RAND_INT(30.0f) + 60.0f);
                    }

                    if (boss->state < 5) {
                        boss->state = 6;
                        boss->timer_050 = 60;
                    }
                }
            }

            if (boss->timer_050 < 50) {
                boss->timer_050 += 10;
            }

            if ((boss->state != 0) && (boss->state < 5)) {
                boss->fwork[14] = 0.0f;

                if (Rand_ZeroOne() < 0.5f) {
                    item = OBJ_ITEM_SILVER_RING;
                } else {
                    item = OBJ_ITEM_BOMB;
                }
                Corneria_80187838(boss, boss->obj.pos.x, boss->obj.pos.y + 100.0f, boss->obj.pos.z, item);
            }

            if (boss->state < 5) {
                boss->state = 0;

                switch (RAND_INT(5.0f)) {
                    case 0:
                        boss->swork[31] = 2;
                        break;
                    case 1:
                        boss->swork[31] = 3;
                        break;
                    case 2:
                    case 3:
                    case 4:
                        boss->swork[31] = 4;
                        break;
                }
            }
        } else {
            func_effect_8007A6F0(&boss->obj.pos, NA_SE_EN_REFLECT);
        }
    }

    if (!(D_edisplay_801615D0.y < 0.0f)) {
        for (sprite = gSprites, var_s1 = 0; var_s1 < ARRAY_COUNT(gSprites); var_s1++, sprite++) {
            if ((sprite->obj.status == OBJ_ACTIVE) && (sprite->obj.id == OBJ_SPRITE_CO_TREE)) {
                if ((fabsf(sprite->obj.pos.x - D_i1_8019B6D8[20]) < 90.0f) &&
                    (fabsf(sprite->obj.pos.z - D_i1_8019B6D8[32]) < 90.0f)) {
                    sprite->destroy = 1;
                    break;
                } else if ((fabsf(sprite->obj.pos.x - D_i1_8019B6D8[23]) < 90.0f) &&
                           (fabsf(sprite->obj.pos.z - D_i1_8019B6D8[35]) < 90.0f)) {
                    sprite->destroy = 1;
                    break;
                }
            }
        }

        if ((boss->swork[1] == 1000) && ((gGameFrameCount % 4) == 0)) {
            func_effect_8007BFFC(D_i1_8019B6D8[3], D_i1_8019B6D8[4], D_i1_8019B6D8[5],
                                 (D_i1_8019B6D8[3] - boss->obj.pos.x) * 0.1f, 0.0f,
                                 (D_i1_8019B6D8[5] - boss->obj.pos.z) * 0.1f, 1.5f, 5);
        }
        if ((boss->swork[2] == 1000) && ((gGameFrameCount % 4) == 0)) {
            func_effect_8007BFFC(D_i1_8019B6D8[9], D_i1_8019B6D8[10], D_i1_8019B6D8[11],
                                 (D_i1_8019B6D8[9] - boss->obj.pos.x) * 0.1f, 0.0f,
                                 (D_i1_8019B6D8[11] - boss->obj.pos.z) * 0.1f, 1.5f, 5);
        }
        if ((boss->swork[3] == 1000) && ((gGameFrameCount % 4) == 0)) {
            func_effect_8007BFFC(D_i1_8019B6D8[12], D_i1_8019B6D8[13], D_i1_8019B6D8[14], 0.0f, 20.0f, 0.0f, 2.0f, 5);
        }
        if ((boss->swork[4] == 1000) && ((gGameFrameCount % 4) == 0)) {
            func_effect_8007BFFC(D_i1_8019B6D8[56], D_i1_8019B6D8[57], D_i1_8019B6D8[58], 0.0f, 10.0f, 0.0f, 2.0f, 5);
        }
        if ((boss->swork[7] == 1000) && ((gGameFrameCount % 4) == 0)) {
            func_effect_8007BFFC(D_i1_8019B6D8[59], D_i1_8019B6D8[60], D_i1_8019B6D8[61], 0.0f, 10.0f, 0.0f, 2.0f, 5);
        }
    }
}

ObjectId Corneria_80188750(Boss* boss) {
    boss->swork[35]++;

    if (boss->swork[35] >= 5) {
        boss->swork[35] = 0;
        return OBJ_ACTOR_191;
    } else if (func_hud_8008AC54(0) < 4) {
        return OBJ_ACTOR_190;
    } else {
        return 0;
    }
}

void Corneria_801887AC(Boss* boss) {
    Vec3f sp3C;
    ObjectId objId;

    if ((gBossFrameCount < 500)) {
        return;
    }

    switch (boss->swork[30]) {
        case 0:
            break;

        case 1:
            objId = Corneria_80188750(boss);
            if (objId != 0) {
                if (boss->swork[1] != 1000) {
                    Corneria_80187710(D_i1_8019B6D8[0], D_i1_8019B6D8[1], D_i1_8019B6D8[2], 65.0f, 0.0f,
                                      D_i1_8019B6D8[16] + boss->obj.rot.y, 0, 0, objId);
                }
                if (boss->swork[2] != 1000) {
                    Corneria_80187710(D_i1_8019B6D8[6], D_i1_8019B6D8[7], D_i1_8019B6D8[8], 65.0f, 0.0f,
                                      D_i1_8019B6D8[16] + boss->obj.rot.y, 0, 0, objId);
                }
            }
            boss->swork[30] = 0;
            break;

        case 2:
            Corneria_801877A0(boss, 40.0f, 228.0f, 212.0f);
            Corneria_801877A0(boss, -40.0f, 228.0f, 212.0f);
            boss->swork[30] = 0;
            break;

        case 3:
            if (boss->swork[3] != 1000) {
                sp3C.x = gPlayer[0].pos.x;
                sp3C.y = gPlayer[0].pos.y;
                sp3C.z = gPlayer[0].trueZpos;

                gPlayer[0].pos.x += RAND_FLOAT_CENTERED(300.0f);
                gPlayer[0].pos.y += RAND_FLOAT_CENTERED(300.0f);
                gPlayer[0].trueZpos += RAND_FLOAT_CENTERED(300.0f);

                func_effect_8007F11C(OBJ_EFFECT_376, D_i1_8019B6D8[12], D_i1_8019B6D8[13], D_i1_8019B6D8[14], 60.0f);

                gPlayer[0].pos.x = sp3C.x;
                gPlayer[0].pos.y = sp3C.y;
                gPlayer[0].trueZpos = sp3C.z;
            }
            boss->swork[30] = 0;
            break;
    }
}

void Corneria_80188A18(Boss* boss) {
    if (boss->timer_050 == 0) {
        boss->state = 0;
        boss->timer_050 = RAND_INT(20.0f) + 20;
        boss->fwork[14] = 0.0f;

        switch (RAND_INT(8.0f)) {
            case 0:
            case 1:
                boss->swork[31] = 1;
                break;

            case 2:
            case 3:
                boss->swork[31] = 2;
                break;

            case 4:
                if (D_edisplay_801615D0.y < 0.0f) {
                    boss->swork[31] = 4;
                } else {
                    boss->swork[31] = 3;
                }
                break;

            case 5:
            case 6:
            case 7:
                boss->swork[31] = 4;
                break;
        }

        if ((gBossFrameCount > 1000) && (Rand_ZeroOne() < 0.3f)) {
            if (Rand_ZeroOne() < 0.5f) {
                AllRange_PlayMessage(gMsg_ID_2263, RCID_BOSS_CORNERIA);
            } else {
                AllRange_PlayMessage(gMsg_ID_2265, RCID_BOSS_CORNERIA);
            }
        }
    }

    if ((gBossFrameCount > 800) && ((gBossFrameCount % 512) == 0)) {
        if (gCoUturnCount < 2) {
            Radio_PlayMessage(gMsg_ID_20237, RCID_PEPPY);
        } else if (D_edisplay_801615D0.z > 0.0f) {
            Radio_PlayMessage(gMsg_ID_2233, RCID_FALCO);
        } else {
            Radio_PlayMessage(gMsg_ID_2282, RCID_PEPPY);
        }
    }
}

void Corneria_80188C7C(Boss* boss) {
    if (boss->unk_044 == 0) {
        boss->unk_044++;
        boss->fwork[12] *= -0.2f;
        AUDIO_PLAY_SFX(NA_SE_OB_METAL_BOUND_L, boss->sfxSource, 4);
        func_enmy_80062B60(D_i1_8019B6D8[56], D_i1_8019B6D8[58], 0, 30.0f);
        boss->swork[18] = 13;
        boss->swork[19] = 15;
        boss->swork[21] = 10;
        boss->swork[22] = 12;
        boss->swork[20] = 17;
        gCameraShake = 20;
    } else {
        boss->fwork[12] = 0.0f;
    }
}

void Corneria_80188D50(Boss* boss) {
    static s32 D_i1_801997E0 = 0;
    s32 i;
    Vec3f src;
    Vec3f dest;
    s32 rnd;

    if (boss->swork[36] == 0) {
        if (gPlayer[0].hitTimer != 0) {
            D_i1_801997E0 = 80;
        }

        if (D_i1_801997E0 != 0) {
            D_i1_801997E0--;
        } else if ((gPlayer[0].pos.y < 200.0f) && (boss->state < 5) &&
                   (fabsf(boss->obj.pos.x - gPlayer[0].pos.x) < 200.0f) &&
                   (fabsf(boss->obj.pos.z - gPlayer[0].trueZpos) < 200.0f) && (gPlayer[0].aerobaticPitch > 180.0f)) {
            boss->swork[36]++;
            D_i1_801997E0 = 20;

            AUDIO_PLAY_SFX(NA_SE_RING_PASS, gDefaultSfxSource, 4);

            if ((gTeamShields[TEAM_ID_FALCO] > 0) || (gTeamShields[TEAM_ID_SLIPPY] > 0) ||
                (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                if (0) {};

                do {
                    rnd = RAND_INT(2.9f) + 1;
                } while (gTeamShields[rnd] <= 0);

                switch (rnd) {
                    case 1:
                        Radio_PlayMessage(gMsg_ID_7100, RCID_FALCO);
                        break;
                    case 2:
                        Radio_PlayMessage(gMsg_ID_15252, RCID_SLIPPY);
                        break;
                    case 3:
                        Radio_PlayMessage(gMsg_ID_17160, RCID_PEPPY);
                        break;
                }
            }

            Matrix_RotateY(gCalcMatrix, (gPlayer[0].yRot_114 + gPlayer[0].rot.y) * M_DTOR, MTXF_NEW);

            src.x = 0.0f;
            src.y = 0.0f;
            src.z = -2500.0f;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

            for (i = 0; i < ARRAY_COUNT(gItems); i++) {
                if (gItems[i].obj.status == OBJ_FREE) {
                    Item_Initialize(&gItems[i]);

                    gItems[i].obj.status = OBJ_INIT;
                    gItems[i].obj.id = OBJ_ITEM_1UP;
                    gItems[i].obj.pos.x = gPlayer[0].pos.x + dest.x;
                    gItems[i].obj.pos.y = gPlayer[0].pos.y + 100.0f;
                    gItems[i].obj.pos.z = gPlayer[0].trueZpos + dest.z;
                    gItems[i].timer_4A = 8;

                    Object_SetInfo(&gItems[i].info, gItems[i].obj.id);
                    func_effect_8007B344(gItems[i].obj.pos.x, gItems[i].obj.pos.y, gItems[i].obj.pos.z, 5.0f, 0);
                    break;
                }
            }
        }
    }
}

void Corneria_80189058(Boss* boss) {
    Vec3f sp21C = { 0.0f, 0.0f, 0.0f };
    s32 sp218;
    f32 sp214;
    f32 sp210;
    f32 sp20C;
    s32 var_v0;
    f32 sp204;
    f32 sp200;
    f32 sp1FC;
    f32 sp1F8;
    Vec3f sp1EC = { 0.0f, 0.0f, 5.0f };
    Vec3f sp84[30];
    Vec3f sp78 = { 0.0f, 0.0f, 40.0f };
    Vec3f sp6C = { 0.0f, 0.0f, -30.0f };
    f32 sp5C;

    if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_START_360) {
        if (boss->swork[33] == 0) {
            boss->swork[33]++;
            gBossActive = 2;

            boss->drawShadow = true;

            boss->swork[24] = 150;
            boss->swork[25] = 150;
            boss->swork[26] = 40;
            boss->swork[27] = 40;
            boss->swork[28] = 40;
            boss->swork[29] = 130;

            boss->info.hitbox[1 + 0] = -241.0f;
            boss->info.hitbox[1 + 6] = 0.0f;
            boss->info.hitbox[1 + 12] = 0.0f;
            boss->info.hitbox[1 + 18] = 0.0f;
            boss->info.hitbox[1 + 24] = 0.0f;
            boss->info.hitbox[1 + 30] = 0.0f;

            boss->timer_052 = 100;
            boss->state = 0;
            boss->swork[31] = 1;

            D_i1_8019B6D8[66] = 0.0f;
            D_i1_8019B6D8[67] = 10000.0f;

            boss->timer_050 = 30;

            Animation_GetFrameData(D_CO_602C0D0, 0, boss->vwork);

            gBossFrameCount = 0;
        }
        gBossFrameCount++;
        gRadarMarks[59].status = 1;
        gRadarMarks[59].type = 102;
        gRadarMarks[59].pos.x = boss->obj.pos.x;
        gRadarMarks[59].pos.y = boss->obj.pos.y;
        gRadarMarks[59].pos.z = boss->obj.pos.z;

        gRadarMarks[59].yRot = boss->obj.rot.y + 180.0f;

        Corneria_80188D50(boss);

        if (D_edisplay_801615D0.z > 0.0f) {
            if (D_edisplay_801615D0.x > 0.0f) {
                gPlayer[0].flags_228 = PFLAG_228_4;
            } else {
                gPlayer[0].flags_228 = PFLAG_228_5;
            }
        }

        switch (gBossFrameCount) {
            case 20:
                Radio_PlayMessage(gMsg_ID_2240, RCID_BOSS_CORNERIA);
                break;
            case 160:
                Radio_PlayMessage(gMsg_ID_2250, RCID_BOSS_CORNERIA);
                break;
            case 330:
                Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
                break;
            case 486:
                gShowBossHealth = 1;
                break;
            case 500:
                Radio_PlayMessage(gMsg_ID_2260, RCID_BOSS_CORNERIA);
                break;
            case 900:
                Radio_PlayMessage(gMsg_ID_2230, RCID_PEPPY);
                break;
            case 3840:
                if (boss->state < 5) {
                    Radio_PlayMessage(gMsg_ID_2230, RCID_PEPPY);
                }
                break;
        }

        if (gBossFrameCount >= 487) {
            gBossHealthBar = boss->swork[29] * 2;
        }

        for (sp218 = 0; sp218 < 24; sp218++) {
            if ((boss->swork[sp218] != 0) && (boss->swork[sp218] < 1000)) {
                boss->swork[sp218]--;
            }
        }

        Corneria_80187AC8(boss);

        boss->fwork[0] = SIN_DEG(boss->swork[18] * 50.0f) * Corneria_80187A88(boss->swork[18]);
        boss->fwork[1] = SIN_DEG(boss->swork[19] * 50.0f) * Corneria_80187A88(boss->swork[19]);
        boss->fwork[2] = SIN_DEG(boss->swork[20] * 50.0f) * Corneria_80187A88(boss->swork[20]);
        boss->fwork[3] = SIN_DEG(boss->swork[21] * 50.0f) * Corneria_80187A88(boss->swork[21]);
        boss->fwork[4] = SIN_DEG(boss->swork[22] * 50.0f) * Corneria_80187A88(boss->swork[22]);

        if (boss->state < 5) {
            sp5C = SIN_DEG(boss->swork[23] * 12.0f) * Corneria_80187A88(boss->swork[23]) * 0.3f;
            Math_SmoothStepToF(&boss->obj.rot.z, sp5C, 0.2f, 100.0f, 0.001f);
        }

        if (boss->obj.pos.y <= 10.0f) {
            boss->obj.pos.y = 10.0f;
        }

        sp214 = D_i1_8019B6D8[17] - boss->obj.pos.x;
        sp210 = D_i1_8019B6D8[18] - (boss->obj.pos.y + 300.0f);
        sp20C = D_i1_8019B6D8[19] - boss->obj.pos.z;

        sp1FC = Math_RadToDeg(Math_Atan2F(sp214, sp20C));
        sp204 = sqrtf((sp214 * sp214) + (sp20C * sp20C));
        sp200 = Math_RadToDeg(-Math_Atan2F(sp210, sp204));

        if ((sp200 > 50.0f) && (sp200 < 180.0f)) {
            sp200 = 50.0f;
        }
        if ((sp200 < 310.0f) && (sp200 > 180.0f)) {
            sp200 = 310.0f;
        }

        sp1FC -= boss->obj.rot.y;
        if (sp1FC > 360.0f) {
            sp1FC -= 360.0f;
        }
        if (sp1FC < 0.0f) {
            sp1FC += 360.0f;
        }
        if ((sp1FC > 50.0f) && (sp1FC < 180.0f)) {
            sp1FC = 50.0f;
        }
        if ((sp1FC < 310.0f) && (sp1FC > 180.0f)) {
            sp1FC = 310.0f;
        }

        Math_SmoothStepToAngle(&D_i1_8019B6D8[16], sp1FC, 0.1f, 3.0f, 0.0f);
        Math_SmoothStepToAngle(&D_i1_8019B6D8[15], sp200, 0.1f, 3.0f, 0.0f);

        if (boss->state != 0) {
            sp1F8 =
                Math_RadToDeg(Math_Atan2F(D_i1_8019B6D8[66] - boss->obj.pos.x, D_i1_8019B6D8[67] - boss->obj.pos.z));
            Math_SmoothStepToAngle(&boss->obj.rot.y, sp1F8, 0.1f, 3.0f, 0.0f);
        }

        Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, 0U);

        switch (boss->state) {
            case 0:
                boss->unk_04C = 0;
                D_i1_8019B6D8[17] = gPlayer[0].pos.x;
                D_i1_8019B6D8[18] = gPlayer[0].pos.y;
                D_i1_8019B6D8[19] = gPlayer[0].trueZpos;

                if (boss->timer_050 == 0) {
                    switch (boss->swork[31]) {
                        case 1:
                            boss->state = 1;
                            boss->timer_050 = RAND_INT(50.0f) + 50;
                            boss->fwork[14] = 0.0f;
                            break;

                        case 2:
                            boss->state = 2;
                            boss->timer_050 = RAND_INT(100.0f) + 150;
                            boss->timer_052 = 40;
                            boss->timer_054 = 40;
                            boss->fwork[14] = 0.07f;
                            break;

                        case 4:
                            boss->state = 4;
                            boss->timer_050 = RAND_INT(70.0f) + 100;
                            boss->fwork[14] = 0.1f;
                            D_i1_8019B6D8[66] = RAND_FLOAT_CENTERED(6000.0f);
                            D_i1_8019B6D8[67] = RAND_FLOAT_CENTERED(6000.0f);
                            boss->fwork[14] = 0.07f;
                            break;

                        case 3:
                            boss->state = 3;
                            boss->timer_050 = RAND_INT(100.0f) + 150;
                            boss->fwork[14] = 0.07f;
                            break;
                    }
                }

                Animation_GetFrameData(D_CO_602C0D0, boss->unk_04C, sp84);

                if (boss->timer_052 == 0) {
                    boss->timer_052 = 150;
                    boss->swork[30] = 1;
                }
                break;

            case 1:
                D_i1_8019B6D8[17] = D_i1_8019B6D8[66] = gPlayer[0].pos.x;
                D_i1_8019B6D8[18] = gPlayer[0].pos.y;
                D_i1_8019B6D8[19] = D_i1_8019B6D8[67] = gPlayer[0].trueZpos;

                boss->unk_04C += 2;
                if (boss->unk_04C >= Animation_GetFrameCount(D_CO_602BC18)) {
                    boss->unk_04C = 0;
                }

                Animation_GetFrameData(D_CO_602BC18, boss->unk_04C, sp84);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp1EC, &sp21C);

                if (boss->timer_052 == 0) {
                    boss->timer_052 = 150;
                    boss->swork[30] = 1;
                }

                Corneria_80188A18(boss);
                break;

            case 2:
                D_i1_8019B6D8[17] = D_i1_8019B6D8[66] = gPlayer[0].pos.x;
                D_i1_8019B6D8[18] = gPlayer[0].pos.y;
                D_i1_8019B6D8[19] = D_i1_8019B6D8[67] = gPlayer[0].trueZpos;

                boss->unk_04C -= 4;
                if (boss->unk_04C < 0) {
                    boss->unk_04C = 100;
                }

                Animation_GetFrameData(D_CO_602BC18, boss->unk_04C, sp84);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp6C, &sp21C);

                if (boss->timer_052 == 0) {
                    boss->timer_052 = 30;
                    boss->swork[30] = 2;
                }
                if (boss->timer_054 == 0) {
                    boss->timer_054 = 9;
                    boss->swork[30] = 3;
                }

                Corneria_80188A18(boss);
                break;

            case 3:
                D_i1_8019B6D8[17] = D_i1_8019B6D8[66] = gPlayer[0].pos.x;
                D_i1_8019B6D8[18] = gPlayer[0].pos.y;
                D_i1_8019B6D8[19] = D_i1_8019B6D8[67] = gPlayer[0].trueZpos;

                boss->unk_04C += 4;
                if (boss->unk_04C > 100) {
                    boss->unk_04C = 0;
                }

                Animation_GetFrameData(D_CO_602BC18, boss->unk_04C, sp84);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp21C);

                if (boss->timer_052 == 0) {
                    boss->timer_052 = 30;
                    boss->swork[30] = 2;
                }
                if (boss->timer_054 == 0) {
                    boss->timer_054 = 9;
                    boss->swork[30] = 3;
                }

                Corneria_80188A18(boss);
                break;

            case 4:
                D_i1_8019B6D8[17] = gPlayer[0].pos.x;
                D_i1_8019B6D8[18] = gPlayer[0].pos.y;
                D_i1_8019B6D8[19] = gPlayer[0].trueZpos;

                boss->unk_04C += 4;
                if (boss->unk_04C > 100) {
                    boss->unk_04C = 0;
                }

                Animation_GetFrameData(D_CO_602BC18, boss->unk_04C, sp84);
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp21C);

                Corneria_80188A18(boss);
                break;

            case 5:
            case 6:
                boss->drawShadow = false;
                gGroundClipMode = 1;

                if (((gGameFrameCount % 8) == 0)) {
                    D_i1_8019B6D8[17] = gPlayer[0].pos.x + RAND_FLOAT_CENTERED(2000.0f);
                    D_i1_8019B6D8[18] = gPlayer[0].pos.y;
                    D_i1_8019B6D8[19] = gPlayer[0].trueZpos + RAND_FLOAT_CENTERED(2000.0f);
                }

                boss->fwork[12] += 0.05f;

                if (boss->state == 6) {
                    boss->obj.rot.z += boss->fwork[12];
                    if (boss->obj.rot.z > 60.0f) {
                        boss->obj.rot.z = 60.0f;
                        Corneria_80188C7C(boss);

                        if ((gGameFrameCount % 512U) == 0) {
                            Radio_PlayMessage(gMsg_ID_2275, RCID_BOSS_CORNERIA);
                        }

                        if ((gGameFrameCount % 512U) == 256) {
                            Radio_PlayMessage(gMsg_ID_2220, RCID_BOSS_CORNERIA);
                        }
                    }
                    boss->obj.rot.x = boss->obj.rot.z;
                } else {
                    boss->obj.rot.z -= boss->fwork[12];
                    if (boss->obj.rot.z < -60.0f) {
                        boss->obj.rot.z = -60.0f;
                        Corneria_80188C7C(boss);

                        if ((gGameFrameCount % 512U) == 0) {
                            Radio_PlayMessage(gMsg_ID_2275, RCID_BOSS_CORNERIA);
                        }
                        if ((gGameFrameCount % 512U) == 256) {
                            Radio_PlayMessage(gMsg_ID_2220, RCID_BOSS_CORNERIA);
                        }
                    }
                    boss->obj.rot.x = -boss->obj.rot.z;
                }

                if (boss->timer_050 == 0) {
                    ObjectId objId;

                    boss->timer_050 = 60;
                    objId = Corneria_80188750(boss);

                    if (objId != 0) {
                        Corneria_80187710(D_i1_8019B6D8[62], D_i1_8019B6D8[63], D_i1_8019B6D8[64], 65.0f, 270.0f, 0.0f,
                                          0, 0, objId);
                    }
                }

                boss->yOffset = SIN_DEG(boss->obj.rot.z) * 30.0f;

                if (((gGameFrameCount % 16) == 0)) {
                    boss->unk_04C = RAND_INT(100.0f);
                }

                Animation_GetFrameData(D_CO_602BC18, boss->unk_04C, sp84);
                boss->fwork[14] = 0.03f;
                break;

            case 7:
                if (boss->swork[32] != 0) {
                    boss->fwork[12] += 0.05f;
                    boss->obj.rot.x += boss->fwork[12];
                    if (boss->obj.rot.x > 60.0f) {
                        boss->obj.rot.x = 60.0f;
                        Corneria_80188C7C(boss);
                    }
                }

                boss->swork[24] = boss->swork[25] = boss->swork[26] = boss->swork[27] = boss->swork[28] = 0;

                if (boss->timer_050 == 12) {
                    Object_Kill(&gEffects[0].obj, gEffects[0].sfxSource);
                    func_effect_8007D0E0(D_i1_8019B6D8[62], D_i1_8019B6D8[63] - 100.0f, D_i1_8019B6D8[64], 25.0f);
                }
                if (boss->timer_050 == 10) {
                    for (sp218 = 0; sp218 < 50; sp218++) {
                        if (gEffects[sp218].obj.status != OBJ_FREE) {
                            Object_Kill(&gEffects[sp218].obj, gEffects[sp218].sfxSource);
                        }
                    }

                    func_effect_8007A568(D_i1_8019B6D8[62], D_i1_8019B6D8[63] - 100.0f, D_i1_8019B6D8[64], 40.0f);
                    func_effect_8007D0E0(D_i1_8019B6D8[62], D_i1_8019B6D8[63] - 100.0f, D_i1_8019B6D8[64], 30.0f);
                    func_enmy_80062B60(D_i1_8019B6D8[62], D_i1_8019B6D8[64], 0, 120.0f);

                    gCameraShake = 25;
                    gShowBossHealth = 0;

                    for (sp218 = 0; sp218 < 100; sp218++) {
                        func_effect_80079618(D_i1_8019B6D8[62] + RAND_FLOAT_CENTERED(600.0f),
                                             (D_i1_8019B6D8[63] + RAND_FLOAT_CENTERED(500.0f)) - 100.0f,
                                             D_i1_8019B6D8[64] + RAND_FLOAT_CENTERED(600.0f), 2.0f);
                    }
                }

                if (boss->timer_050 < 50) {
                    boss->dmgPart = boss->timer_050 % 8U;

                    switch (boss->dmgPart) {
                        case 1:
                            if (boss->swork[2] != 1000) {
                                boss->dmgType = DMG_BEAM;
                            }
                            break;

                        case 2:
                            if (boss->swork[1] != 1000) {
                                boss->dmgType = DMG_BEAM;
                            }
                        case 3:
                            if (boss->swork[3] != 1000) {
                                boss->dmgType = DMG_BEAM;
                            }
                            break;

                        case 4:
                            if (boss->swork[7] != 1000) {
                                boss->dmgType = DMG_BEAM;
                            }
                        case 5:
                            if (boss->swork[4] != 1000) {
                                boss->dmgType = DMG_BEAM;
                            }
                            break;
                    }
                }

                if (boss->timer_050 == 0) {
                    Object_Kill(&boss->obj, boss->sfxSource);
                }
                Animation_GetFrameData(D_CO_602BC18, 0, sp84);
                break;

            default:
                Animation_GetFrameData(D_CO_602C0D0, boss->unk_04C, sp84);
                break;
        }

        Math_SmoothStepToF(&boss->vel.x, sp21C.x, 0.3f, 5.0f, 0.0f);
        Math_SmoothStepToF(&boss->vel.z, sp21C.z, 0.3f, 5.0f, 0.0f);

        Corneria_801887AC(boss);

        Math_SmoothStepToVec3fArray(sp84, boss->vwork, 1, 19, boss->fwork[14], 100.0f, 0.0f);
        Math_SmoothStepToF(&boss->fwork[14], 1.0f, 1.0f, 0.01f, 0.0f);

        if (boss->state < 5) {
            if (((fabsf(boss->obj.pos.x) > 4000.0f) || (fabsf(boss->obj.pos.z) > 4000.0f)) && (boss->state != 4)) {
                boss->state = 4;
                boss->timer_050 = 150;
                D_i1_8019B6D8[66] = 0.0f;
                D_i1_8019B6D8[67] = 0.0f;
                boss->swork[31] = 0;
            }

            if ((boss->state != 0) && ((boss->unk_04C == 0) || (boss->unk_04C == 52))) {
                AUDIO_PLAY_SFX(NA_SE_EN_HEAVY_WALK, boss->sfxSource, 4);
            }

            if (gPlayer[0].somersault && (boss->state != 0)) {
                boss->state = 0;
                boss->swork[31] = 1;
                boss->timer_050 = 100;
                boss->fwork[14] = 0.0f;
            }
        }
    }
}

bool Corneria_8018A434(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Boss* boss = (Boss*) data;

    if (boss->swork[limbIndex] == 1000) {
        *dList = 0;
    }

    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, 1001);

    switch (limbIndex) {
        case 6:
            rot->x += boss->fwork[1];
            rot->y += boss->fwork[1];
            rot->y -= boss->fwork[13] * 0.6f;
            break;

        case 5:
            rot->x -= boss->fwork[1];
            rot->y -= boss->fwork[1];
            rot->z += boss->fwork[1];
            break;

        case 4:
            rot->x += boss->fwork[1];
            rot->y += boss->fwork[1];
            rot->z -= boss->fwork[1];
            break;

        case 9:
            rot->x -= boss->fwork[0];
            rot->y -= boss->fwork[0];
            rot->y += boss->fwork[13];
            break;

        case 8:
            rot->x += boss->fwork[0];
            rot->y += boss->fwork[0];
            rot->z -= boss->fwork[0];
            break;

        case 7:
            rot->x -= boss->fwork[0];
            rot->y -= boss->fwork[0];
            rot->z += boss->fwork[0];
            break;

        case 3:
            rot->x += boss->fwork[2];
            rot->y += boss->fwork[2];
            rot->z += D_i1_8019B6D8[15];
            break;

        case 1:
            rot->x += boss->fwork[4] - D_i1_8019B6D8[15];
            rot->y += boss->fwork[4];
            break;

        case 2:
            rot->x += boss->fwork[3] + D_i1_8019B6D8[15];
            rot->y += boss->fwork[3];
            break;

        case 16:
            rot->x += D_i1_8019B6D8[16];
            break;
    }

    if (((boss->swork[limbIndex] % 2) != 0) || ((boss->timer_05C % 2) != 0)) {
        RCP_SetupDL_64();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 64, 64, 255, 255);
    }
    return false;
}

void Corneria_8018A730(s32 limbIndex, Vec3f* rot, void* data) {
    s32 pad;
    Vec3f sp80 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp74;
    Vec3f sp68 = { 75.0f, 0.0f, 0.0f };
    Vec3f sp5C = { 190.0f, 0.0f, 0.0f };
    Vec3f sp50 = { 96.0f, 34.0f, 0.0f };
    Vec3f sp44 = { 70.0f, 170.0f, 11.0f };
    Vec3f sp38 = { 70.0f, -170.0f, 11.0f };
    Vec3f sp2C = { 64.0f, 0.0f, -236.0f };

    if ((limbIndex >= 4) && (limbIndex < 10)) {
        Matrix_MultVec3f(gCalcMatrix, &sp80, &sp74);

        D_i1_8019B6D8[limbIndex + 16] = sp74.x;
        D_i1_8019B6D8[limbIndex + 22] = sp74.y;
        D_i1_8019B6D8[limbIndex + 28] = sp74.z;

        Matrix_GetYRPAngles(gCalcMatrix, &sp74);

        D_i1_8019B6D8[limbIndex + 34] = sp74.x;
        D_i1_8019B6D8[limbIndex + 40] = sp74.y;
        D_i1_8019B6D8[limbIndex + 46] = sp74.z;
    }

    switch (limbIndex) {
        case 1:
            Matrix_MultVec3f(gCalcMatrix, &sp68, &sp74);
            D_i1_8019B6D8[3] = sp74.x;
            D_i1_8019B6D8[4] = sp74.y;
            D_i1_8019B6D8[5] = sp74.z;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp74);
            D_i1_8019B6D8[0] = sp74.x;
            D_i1_8019B6D8[1] = sp74.y;
            D_i1_8019B6D8[2] = sp74.z;
            break;

        case 2:
            Matrix_MultVec3f(gCalcMatrix, &sp68, &sp74);
            D_i1_8019B6D8[9] = sp74.x;
            D_i1_8019B6D8[10] = sp74.y;
            D_i1_8019B6D8[11] = sp74.z;
            Matrix_MultVec3f(gCalcMatrix, &sp5C, &sp74);
            D_i1_8019B6D8[6] = sp74.x;
            D_i1_8019B6D8[7] = sp74.y;
            D_i1_8019B6D8[8] = sp74.z;
            break;

        case 3:
            Matrix_MultVec3f(gCalcMatrix, &sp50, &sp74);
            D_i1_8019B6D8[12] = sp74.x;
            D_i1_8019B6D8[13] = sp74.y;
            D_i1_8019B6D8[14] = sp74.z;
            break;

        case 17:
            Matrix_MultVec3f(gCalcMatrix, &sp44, &sp74);
            D_i1_8019B6D8[56] = sp74.x;
            D_i1_8019B6D8[57] = sp74.y;
            D_i1_8019B6D8[58] = sp74.z;
            Matrix_MultVec3f(gCalcMatrix, &sp38, &sp74);
            D_i1_8019B6D8[59] = sp74.x;
            D_i1_8019B6D8[60] = sp74.y;
            D_i1_8019B6D8[61] = sp74.z;
            break;

        case 10:
            Matrix_MultVec3f(gCalcMatrix, &sp2C, &sp74);
            D_i1_8019B6D8[62] = sp74.x;
            D_i1_8019B6D8[63] = sp74.y;
            D_i1_8019B6D8[64] = sp74.z;
            break;

        default:
            break;
    }
}

void Corneria_8018AA74(Boss* boss) {
    Matrix_Translate(gCalcMatrix, 0.0f, 700.0f, 0.0f, MTXF_APPLY);
    Animation_DrawSkeleton(2, D_CO_602BE64, boss->vwork, Corneria_8018A434, Corneria_8018A730, boss, gCalcMatrix);
    Matrix_Pop(&gGfxMatrix);
    Matrix_Push(&gGfxMatrix);
}

bool Corneria_8018AB08(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

    if (limbIndex == 1) {
        rot->x += actor->fwork[1];
    }
    if ((limbIndex == 3) && (actor->obj.id == OBJ_ACTOR_176)) {
        rot->x += actor->fwork[1];
    }
    return false;
}

s32 Corneria_8018AB64(Actor* actor) {
    s32 pad[2];
    s32 i;
    s32 temp_v0;
    Vec3f sp7C;
    Vec3f sp70 = { 0.0f, -10.0f, 0.0f };
    f32 sp60[4] = { 130.0f, -130.0f, 0.0f, 0.0f };
    f32 sp50[4] = { 0.0f, 0.0f, 130.0f, -130.0f };

    for (i = 0; i < 4; i++) {
        sp7C.x = sp60[i] + actor->obj.pos.x;
        sp7C.y = actor->obj.pos.y;
        sp7C.z = sp50[i] + actor->obj.pos.z;

        temp_v0 = Object_CheckCollision(actor->index, &sp7C, &sp70, 1);
        if ((temp_v0 != 0) && (temp_v0 >= 10)) {
            if ((gScenery[temp_v0 - 10].obj.status == OBJ_ACTIVE) &&
                (gScenery[temp_v0 - 10].obj.id == OBJ_SCENERY_40)) {
                return temp_v0 - 9;
            }
        }
    }
    return 0;
}

void Corneria_8018ACE0(Actor* actor) {
    if (actor->dmgType != DMG_NONE) {
        actor->dmgType = DMG_NONE;

        if (actor->dmgPart == 0) {
            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, actor->sfxSource, 4);
            func_effect_8007C120(actor->obj.pos.x, actor->obj.pos.y + 200.0f, actor->obj.pos.z, actor->vel.x,
                                 actor->vel.y, actor->vel.z, 0.1f, 20);
            actor->timer_0C6 = 15;
            actor->health -= actor->damage;

            if (actor->health <= 0) {
                actor->obj.id = OBJ_ACTOR_179;
                Object_SetInfo(&actor->info, actor->obj.id);
                actor->state = 100;
                actor->timer_0BC = 10;
                actor->lockOnTimers[TEAM_ID_FOX] = 0;
                actor->vel.x = actor->vel.y = actor->vel.z = 0.0f;
            }
        }
    }

    if ((actor->health < 11) && ((gGameFrameCount % 4) == 0)) {
        func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                             actor->obj.pos.y + 200.0f + RAND_FLOAT_CENTERED(100.0f),
                             actor->obj.pos.z + 50.0f + RAND_FLOAT(50.0f), 3.0f);
        func_effect_8007C120(actor->obj.pos.x, actor->obj.pos.y + 200.0f, actor->obj.pos.z, actor->vel.x, actor->vel.y,
                             actor->vel.z, 0.1f, 10);
    }
}

void Corneria_8018AED0(Actor* actor) {
    Vec3f sp40[20];
    f32 temp_sin;
    f32 temp_cos;

    Corneria_8018ACE0(actor);

    Math_SmoothStepToVec3fArray(sp40, actor->vwork, 0, Animation_GetFrameData(D_CO_602991C, actor->animFrame, sp40),
                                1.0f, 1.0f, 1.0f);

    temp_sin = SIN_DEG(actor->obj.rot.y);
    actor->vel.x = actor->fwork[0] * temp_sin;
    temp_cos = COS_DEG(actor->obj.rot.y);
    actor->vel.z = actor->fwork[0] * temp_cos;

    switch (actor->state) {
        case 0:
            actor->fwork[1] += 20.0f;
            Texture_Scroll(D_CO_60329C0, 16, 16, 1);
            actor->animFrame = 0;

            actor->fwork[0] += 1.0f;
            if (actor->fwork[0] > 10.0f) {
                actor->fwork[0] = 10.0f;
            }

            actor->iwork[0] = Corneria_8018AB64(actor);
            if (actor->iwork[0] != 0) {
                actor->state++;
            }
            break;

        case 1:
            actor->animFrame++;
            actor->fwork[1] += 20.0f;
            actor->fwork[0] = 0.0f;

            if (actor->animFrame == 50) {
                gScenery[actor->iwork[0] - 1].state = 1;
            }
            if (actor->animFrame >= Animation_GetFrameCount(&D_CO_602991C)) {
                actor->state++;
            }
            break;

        case 2:
            actor->animFrame = 0;
            actor->fwork[1] += 20.0f;
            break;
    }
}

void Corneria_8018B0B4(Actor* actor) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
        if (gScenery[i].obj.status == OBJ_FREE) {
            Scenery_Initialize(&gScenery[i]);
            gScenery[i].obj.status = OBJ_INIT;
            gScenery[i].obj.id = OBJ_SCENERY_42;
            gScenery[i].obj.pos.x = actor->obj.pos.x;
            gScenery[i].obj.pos.y = actor->obj.pos.y;
            gScenery[i].obj.pos.z = actor->obj.pos.z;
            gScenery[i].obj.rot.y = actor->obj.rot.y;
            Object_SetInfo(&gScenery[i].info, gScenery[i].obj.id);
            actor->iwork[0] = i;
            return;
        }
    }
}

void Corneria_8018B15C(Actor* actor) {
    Vec3f sp60[20];
    Vec3f sp54;
    Vec3f sp48;
    Scenery* scenery;
    f32 temp_sin;
    f32 temp_cos;

    Corneria_8018ACE0(actor);

    scenery = &gScenery[actor->iwork[0]];

    temp_sin = SIN_DEG(actor->obj.rot.y);
    actor->vel.x = actor->fwork[0] * temp_sin;
    temp_cos = COS_DEG(actor->obj.rot.y);
    actor->vel.z = actor->fwork[0] * temp_cos;

    Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, MTXF_NEW);

    switch (actor->state) {
        case 3:
            break;

        case 0:
            actor->timer_0BC = 40;
            actor->state = 1;
            actor->animFrame = 0;
            break;

        case 1:
            actor->fwork[0] = -10.0f;
            Texture_Scroll(D_CO_60329C0, 16, 16, 1);
            if (actor->timer_0BC == 0) {
                actor->state = 2;
                actor->iwork[2] = RAND_INT(10.0f) + 10;
            }
            break;

        case 2:
            actor->fwork[0] = -10.0f;
            Texture_Scroll(D_CO_60329C0, 16, 16, 1);
            actor->animFrame++;

            if (actor->animFrame >= Animation_GetFrameCount(&D_CO_602AA04)) {
                actor->state = 3;
            }
            if (actor->animFrame == (Animation_GetFrameCount(&D_CO_602AA04) - actor->iwork[2])) {
                actor->iwork[1] = 1;
                scenery->state = 1;
                sp54.x = 0.0f;
                sp54.y = 0.0f;
                sp54.z = 30.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp54, &sp48);
                scenery->vel.x = sp48.x;
                scenery->vel.y = sp48.y;
                scenery->vel.z = sp48.z;
                AUDIO_PLAY_SFX(NA_SE_EN_THROW, actor->sfxSource, 4);
            }
            break;
    }

    if (actor->iwork[1] == 0) {
        scenery->obj.pos.x = actor->fwork[2];
        scenery->obj.pos.y = actor->fwork[6];
        scenery->obj.pos.z = actor->fwork[10];
        scenery->obj.rot.y = actor->obj.rot.y;
        scenery->vel.y = 0.0f;
    }

    Math_SmoothStepToVec3fArray(sp60, actor->vwork, 0, Animation_GetFrameData(D_CO_602AA04, actor->animFrame, sp60),
                                1.0f, 1.0f, 1.0f);
}

void Corneria_8018B418(Actor* actor) {
    s32 pad;
    Vec3f sp54[20];
    Scenery* temp_v0_2;
    f32 temp_sin;
    f32 temp_cos;
    s32 pad2[4];

    Corneria_8018ACE0(actor);

    temp_sin = SIN_DEG(actor->obj.rot.y);
    actor->vel.x = actor->fwork[0] * temp_sin;
    temp_cos = COS_DEG(actor->obj.rot.y);
    actor->vel.z = actor->fwork[0] * temp_cos;

    switch (actor->state) {
        case 0:
            actor->state = 1;
            break;

        case 1:
            actor->fwork[0] = 5.0f;
            actor->fwork[1] += 5.0f;
            Texture_Scroll(D_CO_60329C0, 16, 16, 1);
            actor->animFrame++;
            if (actor->animFrame >= Animation_GetFrameCount(&D_CO_602A520)) {
                actor->animFrame = 0;
            }
            break;
    }

    if (actor->iwork[1] == 0) {
        temp_v0_2 = &gScenery[actor->iwork[0]];
        temp_v0_2->obj.pos.x = actor->fwork[2];
        temp_v0_2->obj.pos.y = actor->fwork[6];
        temp_v0_2->obj.pos.z = actor->fwork[10];
        temp_v0_2->obj.rot.y = actor->fwork[1];
        temp_v0_2->vel.y = 0.0f;
    }

    Math_SmoothStepToVec3fArray(sp54, actor->vwork, 0, Animation_GetFrameData(D_CO_602A520, actor->animFrame, sp54),
                                1.0f, 1.0f, 1.0f);
}

void Corneria_8018B58C(Actor* actor) {
    s32 i;
    f32 spB4[4] = { -10.0f, -5.0f, 10.0f, 5.0f };
    f32 spA4[4] = { 10.0f, 15.0f, 10.0f, 15.0f };

    Math_SmoothStepToF(&actor->vel.x, 0.0f, 0.05f, 1.0f, 0.0001f);
    Math_SmoothStepToF(&actor->vel.y, 0.0f, 0.05f, 1.0f, 0.0001f);
    Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.05f, 1.0f, 0.0001f);

    switch (actor->state) {
        case 100:
            if ((actor->timer_0BC & 3) == 0) {

                func_effect_8007D2C8(actor->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                                     actor->obj.pos.y + 200.0f + RAND_FLOAT_CENTERED(100.0f),
                                     actor->obj.pos.z + 50.0f + RAND_FLOAT(50.0f), 3.0f);
                func_effect_8007C120(actor->obj.pos.x, actor->obj.pos.y + 200.0f, actor->obj.pos.z, actor->vel.x,
                                     actor->vel.y, actor->vel.z, 0.1f, 10);
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_S, actor->sfxSource, 4);
            }

            if (actor->timer_0BC == 0) {
                for (i = 0; i < 4; i++) {

                    Boss_SpawnDebris(actor->fwork[2 + i], actor->fwork[6 + i], actor->fwork[10 + i], 0.0f, 0.0f, 0.0f,
                                     spB4[i] * (RAND_FLOAT(0.75f) + 0.5f), spA4[i] * (RAND_FLOAT(0.75f) + 0.5f),
                                     RAND_FLOAT_CENTERED(20.0f), 3.0f, i + 24, RAND_INT(30.0f) + 60.0f);
                }

                if ((fabsf(actor->obj.pos.z - gPlayer[0].trueZpos) < 500.0f) &&
                    (fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 200.0f) &&
                    (fabsf(actor->obj.pos.y - gPlayer[0].pos.y) < 200.0f)) {
                    *gControllerRumbleTimers = 25;
                }
                BonusText_Display(actor->obj.pos.x, actor->obj.pos.y + 250.0f, actor->obj.pos.z, 5);
                gHitCount += 6;
                D_ctx_80177850 = 15;
                actor->state = 101;
                actor->timer_0BE = 50;
            }

            if (actor->timer_0BC == 8) {
                func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y + 200.0f, actor->obj.pos.z + 50.0f, 0.0f, 0.0f,
                                     0.0f, 5.0f, 30);
                AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, actor->sfxSource, 4);
            }
            break;

        case 101:
            if ((actor->timer_0BE != 0) && ((gGameFrameCount % 2) == 0)) {
                func_effect_8007797C(actor->obj.pos.x, actor->obj.pos.y + 150.0f, actor->obj.pos.z, 0.0f, 10.0f, 0.0f,
                                     3.0f);
            }
            break;
    }
}

void Corneria_8018BAAC(Actor* actor) {
    Animation_DrawSkeleton(3, D_CO_6029A48, actor->vwork, Corneria_8018AB08, NULL, actor, gCalcMatrix);
}

void Corneria_8018BAFC(s32 limbIndex, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;
    Vec3f sp28 = { 120.0f, 0.0f, 0.0f };
    Vec3f sp1C;

    if (limbIndex == 1) {
        Matrix_MultVec3f(gCalcMatrix, &sp28, &sp1C);
        actor->fwork[2] = sp1C.x;
        actor->fwork[6] = sp1C.y;
        actor->fwork[10] = sp1C.z;
        if (actor->iwork[1] == 0) {
            gScenery[actor->iwork[0]].obj.rot.x = -rot->y;
        }
    }
}

void Corneria_8018BBA4(Actor* actor) {
    Animation_DrawSkeleton(3, D_CO_6029A48, actor->vwork, NULL, Corneria_8018BAFC, actor, gCalcMatrix);
}

void Corneria_8018BBF8(Actor* actor) {
    Animation_DrawSkeleton(3, D_CO_6029A48, actor->vwork, Corneria_8018AB08, Corneria_8018BAFC, actor, gCalcMatrix);
}

bool Corneria_8018BC50(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;

    if ((actor->state == 101) && (limbIndex != 8)) {
        *dList = NULL;
    }
    return false;
}

void Corneria_8018BC84(s32 limbIndex, Vec3f* rot, void* data) {
    Actor* actor = (Actor*) data;
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;

    Matrix_MultVec3f(gCalcMatrix, &src, &dest);

    switch (limbIndex) {
        case 1:
            actor->fwork[2] = dest.x;
            actor->fwork[6] = dest.y;
            actor->fwork[10] = dest.z;
            break;

        case 2:
            actor->fwork[3] = dest.x;
            actor->fwork[7] = dest.y;
            actor->fwork[11] = dest.z;
            break;

        case 3:
            actor->fwork[4] = dest.x;
            actor->fwork[8] = dest.y;
            actor->fwork[12] = dest.z;
            break;

        case 4:
            actor->fwork[5] = dest.x;
            actor->fwork[9] = dest.y;
            actor->fwork[13] = dest.z;
            break;
    }
}

void Corneria_8018BD7C(Actor* actor) {
    Animation_DrawSkeleton(3, D_CO_6029A48, actor->vwork, Corneria_8018BC50, Corneria_8018BC84, actor, gCalcMatrix);
}

void Corneria_8018BDD4(Boss* boss, f32 xPos, f32 yPos, f32 zPos, f32 arg4, s32 arg5, s32 arg6) {
    ObjectId objId = OBJ_ACTOR_191;

    if (func_hud_8008AC54(0) < 4) {
        objId = OBJ_ACTOR_190;
    }

    Corneria_80187710(boss->obj.pos.x + xPos, boss->obj.pos.y + yPos, boss->obj.pos.z + zPos, arg4, boss->obj.rot.x,
                      boss->obj.rot.y, arg5, arg6, objId);
}

void Corneria_Boss293_Init(Boss293* this) {
    s32 i;
    s16 temp_s1;

    gBossActive = 1;
    gBossFrameCount = 0;

    this->drawShadow = true;
    this->timer_050 = 354;
    this->health = 601;
    this->fwork[18] = -gArwingSpeed - 10.0f;

    if (fabsf(gPlayer[0].xPath) < 1.0f) {
        this->timer_05A = 30000;
        this->obj.pos.z = (gPlayer[0].cam.eye.z - gPathProgress) - 2000.0f;
        AUDIO_PLAY_SFX(NA_SE_A_CARRIER_ENGINE, this->sfxSource, 4);
        D_i1_8019B6D0 = 0;
    } else {
        D_i1_8019B6D0 = 1;
        this->obj.rot.y = 180.0f;
        this->fwork[6] = 800.0f;
        this->obj.pos.z = gPlayer[0].trueZpos + 2000.0f;
        this->fwork[7] = this->obj.pos.x;
        this->fwork[5] = 30.0f;
        AUDIO_PLAY_SFX(NA_SE_A_CARRIER_ENGINE, this->sfxSource, 4);
        this->swork[10] = 3;
        this->swork[8] = 3;
    }

    temp_s1 = this->timer_05A;

    // Bosses OBJ_BOSS_294 to OBJ_BOSS_296
    for (i = 1; i < ARRAY_COUNT(gBosses); i++) {
        Boss_Initialize(&gBosses[i]);
        gBosses[i].obj.status = OBJ_INIT;
        gBosses[i].obj.id = i + 293;
        gBosses[i].obj.pos.x = this->obj.pos.x;
        gBosses[i].obj.pos.y = this->obj.pos.y;
        gBosses[i].obj.pos.z = this->obj.pos.z;
        gBosses[i].health = 200;
        gBosses[i].drawShadow = true;
        gBosses[i].timer_05A = temp_s1;
        Object_SetInfo(&gBosses[i].info, gBosses[i].obj.id);
        gBosses[3].drawShadow = false;
    }
}

void Corneria_8018C0B0(Boss* boss) {
    func_effect_8007D9DC(boss->obj.pos.x, gGroundHeight + 2.0f, boss->obj.pos.z, 5.0f, 100.0f, 0);
    func_effect_8007D9DC(boss->obj.pos.x, gGroundHeight + 2.0f, boss->obj.pos.z, 5.0f, 100.0f, 5);
    func_effect_8007D9DC(boss->obj.pos.x, gGroundHeight + 2.0f, boss->obj.pos.z, 5.0f, 100.0f, 10);
    func_effect_8007ADF4(boss->obj.pos.x, gGroundHeight, boss->obj.pos.z, 1.0f, 10.0f);
}

static Vec3f D_i1_801998CC = { 442.0f, 5.0f, 360.0f };
static Vec3f D_i1_801998D8 = { -439.0f, 180.0f, 323.0f };
static Vec3f D_i1_801998E4 = { -439.0f, -180.0f, 323.0f };
static Vec3f D_i1_801998F0[2] = {
    { 0.0f, 50.0f, 473.0f },
    { 300.0f, 70.0f, 200.0f },
};
static Vec3f D_i1_80199908 = { 230.0f, 30.0f, -200.0f };
static Vec3f D_i1_80199914[2] = {
    { 434.0f, -74.0f, -580.0f },
    { -438.0f, -277.0f, -750.0f },
};
static Vec3f D_i1_8019992C = { -438.0f, 275.0f, -750.0f };
static Vec3f D_i1_80199938 = { -426.0f, 147.0f, 2.0f };
static Vec3f D_i1_80199944 = { -437.0f, -135.0f, 2.0f };
static Vec3f D_i1_80199950 = { -250.0f, 30.0f, -200.0f };
static Vec3f D_i1_8019995C[20] = {
    { 67.0f, 44.0f, 377.0f },     { -146.0f, 24.0f, 376.0f }, { -88.0f, 85.0f, -15.0f },   { 105.0f, 89.0f, -169.0f },
    { -107.0f, -36.0f, 367.0f },  { 110.0f, -39.0f, 286.0f }, { -126.0f, -93.0f, 221.0f }, { 88.0f, -94.0f, 155.0f },
    { 126.0f, -179.0f, -101.0f }, { -94.0f, -151.0f, 29.0f }, { 105.0f, -140.0f, 2.0f },   { -18.0f, -101.0f, 77.0f },
    { -60.0f, -151.0f, 29.0f },   { -132.0f, 9.0f, 430.0f },  { 52.0f, 29.0f, 431.0f },    { -23.0f, 68.0f, 325.0f },
    { 116.0f, 34.0f, 368.0f },    { -49.0f, -53.0f, 366.0f }, { 113.0f, -62.0f, 255.0f },  { -114.0f, -88.0f, 182.0f }
};

static s32 D_i1_80199A4C[4] = { 150, 200, 150, 200 };

static f32 D_i1_80199A5C[4] = { -225.0f, 0.0f, 225.0f, 0.0f };

void Corneria_8018C19C(Boss* boss) {
    // todo: figure out vec3f stack
    s32 pad[9];
    Vec3f sp84[30];
    Vec3f sp78;
    Vec3f sp6C;
    Effect* effect;
    f32 temp_fv0_2;
    s32 pad2;
    s32 var_v1;
    s32 var_v0;
    s32 i;
    s32 pad3;
    f32* temp_a0;
    f32* temp_a1;

    gBossFrameCount++;

    Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);

    if (D_i1_8019B6D0 == 0) {
        if (boss->obj.pos.x > 6000.0f) {
            Object_Kill(&boss->obj, boss->sfxSource);
            for (i = 1; i < ARRAY_COUNT(gBosses); i++) {
                Object_Kill(&gBosses[i].obj, gBosses[i].sfxSource);
            }
            return;
        }

        sp78.x = 0.0f;
        sp78.y = 0.0f;
        sp78.z = 60.0f;

        Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

        boss->vel.x = sp6C.x;
        boss->vel.y = sp6C.y;
        boss->vel.z = sp6C.z - gPathVelZ;

        boss->fwork[16] = 4.0f;

        if (((gGameFrameCount % 2) == 0)) {
            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199914[0], &sp84[6]);
            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199914[1], &sp84[7]);
            Matrix_MultVec3f(gCalcMatrix, &D_i1_8019992C, &sp84[8]);
            func_effect_8007BC7C(sp84[6].x + boss->obj.pos.x, sp84[6].y + boss->obj.pos.y, sp84[6].z + boss->obj.pos.z,
                                 20.0f);
            func_effect_8007BC7C(sp84[7].x + boss->obj.pos.x, sp84[7].y + boss->obj.pos.y, sp84[7].z + boss->obj.pos.z,
                                 10.0f);
            func_effect_8007BC7C(sp84[8].x + boss->obj.pos.x, sp84[8].y + boss->obj.pos.y, sp84[8].z + boss->obj.pos.z,
                                 10.0f);
        }
    } else {
        if ((gBossFrameCount > 380) && (gBossFrameCount < 430)) {
            gLight2colorStep = 5;
            gLight2RTarget = 20;
            gLight2GTarget = 20;
            gLight2BTarget = 20;
            gPlayer[0].shadowing = 100;
        }
        Matrix_MultVec3f(gCalcMatrix, &D_i1_801998CC, &sp84[0]);
        Matrix_MultVec3f(gCalcMatrix, &D_i1_801998D8, &sp84[1]);
        Matrix_MultVec3f(gCalcMatrix, &D_i1_801998E4, &sp84[2]);

        if (boss->health != 601) {
            var_v1 = boss->health - 601;

            if (var_v1 < 0) {
                var_v1 *= -1;
            }

            for (i = 0; var_v1 >= 60; i++, var_v1 -= 60) {}

            for (var_v0 = 0, var_v1 = 13; var_v0 < i; var_v0++, var_v1++) {
                if ((gGameFrameCount % 16U) == (var_v0 % 16U)) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i1_8019995C[var_v0], &sp84[var_v1]);
                    func_effect_8007D0E0(sp84[var_v1].x + boss->obj.pos.x, sp84[var_v1].y + boss->obj.pos.y,
                                         sp84[var_v1].z + boss->obj.pos.z, boss->fwork[17]);
                    func_effect_8007C120(sp84[var_v1].x + boss->obj.pos.x, sp84[var_v1].y + boss->obj.pos.y,
                                         sp84[var_v1].z + boss->obj.pos.z, boss->vel.x, boss->vel.y, boss->vel.z, 0.1f,
                                         7);
                }
            }
        }

        if (boss->dmgType != DMG_NONE) {
            boss->dmgType = DMG_NONE;
            if ((gBosses[1].state != 0) && (gBosses[2].state != 0) && (gBosses[3].state != 0)) {
                if (boss->health >= 2) {
                    boss->timer_05C = 15;
                    boss->health -= boss->damage;
                    if (boss->health < 120) {
                        boss->fwork[17] = 2.8f;
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, boss->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, boss->sfxSource, 4);
                    }
                }
            } else {
                AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
            }
        }

        boss->vel.z = boss->fwork[18];

        if (boss->state > 0) {
            boss->fwork[3] = (gPlayer[0].cam.eye.z - gPathProgress) - 2500.0f;
        }

        if (boss->state != 7) {
            Math_SmoothStepToF(&boss->fwork[4], boss->fwork[5], 0.1f, 2.0f, 0.00001f);
            Math_SmoothStepToF(&boss->obj.pos.z, boss->fwork[3], 0.1f, boss->fwork[4], 0.00001f);
        }

        Math_SmoothStepToF(&boss->obj.pos.y, boss->fwork[6], 0.02f, 2.0f, 0.00001f);
        Math_SmoothStepToAngle(&boss->fwork[0], boss->fwork[9], 0.2f, 5.0f, 0.00001f);
        Math_SmoothStepToAngle(&boss->fwork[1], boss->fwork[10], 0.2f, 5.0f, 0.00001f);
        Math_SmoothStepToAngle(&boss->fwork[2], boss->fwork[11], 0.2f, 5.0f, 0.00001f);

        if (boss->state < 6) {
            Math_SmoothStepToAngle(&boss->obj.rot.y, boss->fwork[13], 0.03f, boss->fwork[8], 0.00001f);
            Math_SmoothStepToF(&boss->fwork[8], boss->fwork[12], 0.1f, 0.02f, 0.001f);
            Math_SmoothStepToAngle(&boss->obj.rot.z, boss->fwork[14], 0.03f, boss->fwork[15], 0.00001f);

            if (boss->timer_056 == 1) {
                boss->fwork[14] = 0.0f;
                boss->fwork[15] = 0.5f;
            }
        }

        if ((gBosses[1].state != 0) && ((gGameFrameCount % 16) == 0)) {
            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199908, &sp84[5]);
            func_effect_8007D0E0(gBosses[0].obj.pos.x + sp84[5].x, gBosses[0].obj.pos.y + sp84[5].y,
                                 gBosses[0].obj.pos.z + sp84[5].z, 5.0f);
        }

        if (gBosses[2].state != 0) {
            gBosses[3].drawShadow = true;
            if (gBosses[3].state != 0) {
                if (((gGameFrameCount % 8) == 0)) {
                    Matrix_MultVec3f(gCalcMatrix, &D_i1_80199950, &sp84[11]);
                    func_effect_8007D0E0(gBosses[0].obj.pos.x + sp84[11].x, gBosses[0].obj.pos.y + sp84[11].y,
                                         gBosses[0].obj.pos.z + sp84[11].z, 7.0f);
                }
            } else if (((gGameFrameCount % 16) == 0)) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199938, &sp84[9]);
                func_effect_8007D0E0(gBosses[0].obj.pos.x + sp84[9].x, gBosses[0].obj.pos.y + sp84[9].y,
                                     gBosses[0].obj.pos.z + sp84[9].z, 5.0f);
            }
        }

        if ((gBosses[3].state != 0) && (gBosses[2].state == 0) && ((gGameFrameCount % 16) == 0)) {
            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199944, &sp84[10]);
            func_effect_8007D0E0(gBosses[0].obj.pos.x + sp84[10].x, gBosses[0].obj.pos.y + sp84[10].y,
                                 gBosses[0].obj.pos.z + sp84[10].z, 5.0f);
        }

        if (((boss->state == 1) || (boss->state == 2)) && ((gGameFrameCount % 8) == 0)) {
            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199914[0], &sp84[6]);
            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199914[1], &sp84[7]);
            Matrix_MultVec3f(gCalcMatrix, &D_i1_8019992C, &sp84[8]);

            func_effect_8007BC7C(sp84[6].x + boss->obj.pos.x, sp84[6].y + boss->obj.pos.y, sp84[6].z + boss->obj.pos.z,
                                 20.0f);
            func_effect_8007BC7C(sp84[7].x + boss->obj.pos.x, sp84[7].y + boss->obj.pos.y, sp84[7].z + boss->obj.pos.z,
                                 10.0f);
            func_effect_8007BC7C(sp84[8].x + boss->obj.pos.x, sp84[8].y + boss->obj.pos.y, sp84[8].z + boss->obj.pos.z,
                                 10.0f);
        }

        if (boss->timer_052 != 0) {
            Math_SmoothStepToF(&D_ctx_801779A8[0], 50.0f, 1.0f, 1.6f, 0.0001f);
        }

        switch (boss->state) {
            case 0:
                boss->fwork[3] = gPlayer[0].trueZpos + 1500.0f;

                if (boss->timer_050 == 350) {
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);
                    Radio_PlayMessage(gMsg_ID_2290, RCID_BOSS_CORNERIA2);
                }

                if (boss->timer_050 == 180) {
                    Radio_PlayMessage(gMsg_ID_2298, RCID_PEPPY);
                    boss->timer_052 = 350;
                }

                if (boss->timer_050 == 0) {
                    boss->obj.pos.y = 900.0f;
                    boss->state = 1;
                    boss->fwork[13] = 180.0f;
                    boss->fwork[12] = 1.5f;
                    boss->fwork[6] = 800.0f;
                    boss->fwork[3] = gPlayer[0].cam.eye.z - gPathProgress - 2500.0f;
                    boss->fwork[18] = -gArwingSpeed;
                    AUDIO_PLAY_BGM(NA_BGM_BOSS_A_CARRIER);
                    boss->timer_050 = 40;
                }
                break;

            case 1:
                if (boss->timer_050 == 0) {
                    boss->state = 2;
                    boss->fwork[8] = 0.0f;
                    boss->fwork[13] = 359.9f;
                    boss->timer_050 = 250;
                }
                break;

            case 2:
                if (boss->timer_050 == 0) {
                    boss->state = 3;
                    boss->swork[0] = 4;
                    boss->timer_050 = 75;
                    boss->timer_054 = 0;
                    boss->fwork[8] = 0.0f;
                    Radio_PlayMessage(gMsg_ID_2291, RCID_BOSS_CORNERIA2);
                    boss->swork[4]++;
                }
                break;

            case 3:
                boss->fwork[12] = 1.5f;
                boss->fwork[11] = 0.0f;
                boss->fwork[9] = 0.0f;
                boss->fwork[10] = 0.0f;
                boss->fwork[13] = 0.0f;

                if (boss->timer_050 == 0) {
                    boss->state = boss->swork[0];
                    boss->timer_050 = 60;
                    boss->fwork[8] = 0.0f;
                    AUDIO_PLAY_SFX(NA_SE_EN_HATCH, boss->sfxSource, 4);
                }
                break;

            case 4:
                boss->fwork[11] = 120.0f;
                boss->fwork[13] = 340.0f;

                if ((boss->timer_050 == 0) || (gBosses[1].state != 0)) {
                    boss->state = 3;
                    boss->swork[0] = 5;
                    boss->timer_050 = 20;
                    boss->fwork[8] = 0.0f;

                    if (gBosses[1].state == 0) {
                        AUDIO_PLAY_SFX(NA_SE_EN_HATCH, boss->sfxSource, 4);
                    }

                    if ((boss->swork[5] == 0) && ((gBosses[2].state == 0) || (gBosses[3].state == 0))) {
                        Radio_PlayMessage(gMsg_ID_2292, RCID_BOSS_CORNERIA2);
                    }

                    boss->swork[5]++;
                    boss->swork[5] &= 3;

                } else if ((boss->fwork[2] > 60.0f) && (boss->timer_054 == 0)) {
                    boss->timer_054 = 20;
                    Corneria_8018BDD4(boss, sp84[0].x, sp84[0].y, sp84[0].z, 30.0f, 0, 1);
                }
                break;

            case 5:
                boss->fwork[9] = 120.0f;
                boss->fwork[10] = 120.0f;
                boss->fwork[13] = 20.0f;

                if ((boss->fwork[0] > 60.0f) && (gBosses[2].state == 0) && (boss->swork[1] == 0)) {
                    Corneria_8018BDD4(boss, sp84[1].x, sp84[1].y + 50.0f, sp84[1].z, 45.0f, 0, 0);
                    AUDIO_PLAY_SFX(NA_SE_EN_BARREL_SHOT, boss->sfxSource, 4);
                    Corneria_8018BDD4(boss, sp84[1].x, sp84[1].y - 50.0f, sp84[1].z, 40.0f, 0, 0);
                    boss->swork[1] = 1;
                }

                if ((boss->fwork[1] > 60.0f) && (gBosses[3].state == 0) && (boss->swork[2] == 0)) {
                    Corneria_8018BDD4(boss, sp84[2].x, sp84[2].y + 50.0f, sp84[2].z, 35.0f, 0, 0);
                    AUDIO_PLAY_SFX(NA_SE_EN_BARREL_SHOT, boss->sfxSource, 4);
                    Corneria_8018BDD4(boss, sp84[2].x, sp84[2].y - 50.0f, sp84[2].z, 30.0f, 0, 0);
                    boss->swork[2] = 1;
                }

                if ((boss->timer_050 == 0) || ((gBosses[3].state != 0) && (gBosses[2].state != 0))) {
                    boss->state = 3;
                    boss->swork[0] = 4;
                    boss->timer_050 = 70;
                    boss->swork[1] = 0;
                    boss->swork[2] = 0;
                    boss->fwork[8] = 0.0f;

                    if ((boss->swork[4] == 0) && (gBosses[1].state == 0)) {
                        Radio_PlayMessage(gMsg_ID_2291, RCID_BOSS_CORNERIA2);
                    }

                    if ((boss->swork[4] == 2) && (boss->swork[7] == 0) &&
                        ((gBosses[3].state == 0) || (gBosses[2].state == 0) || (gBosses[1].state == 0))) {
                        Radio_PlayMessage(gMsg_ID_2299, RCID_PEPPY);
                        boss->swork[7]++;
                    }

                    boss->swork[4]++;
                    boss->swork[4] &= 3;

                    if ((gBosses[3].state == 0) && (gBosses[2].state == 0)) {
                        AUDIO_PLAY_SFX(NA_SE_EN_HATCH, boss->sfxSource, 4);
                    }
                }
                break;

            case 6:
                Math_SmoothStepToAngle(&boss->obj.rot.y, boss->fwork[13], 0.1f, 5.0f, 0.01f);
                Math_SmoothStepToAngle(&boss->obj.rot.z, boss->fwork[14], 0.1f, 5.0f, 0.01f);

                if ((boss->obj.rot.y == 0.0f) || (boss->timer_058 == 0)) {
                    boss->timer_058 = 0;
                    boss->state = 7;
                    boss->obj.rot.z = 0.0f;
                    boss->obj.rot.y = 0.0f;
                }
                break;

            case 7:
                boss->fwork[3] = (gPlayer[0].cam.eye.z - gPathProgress) - 4000.0f;
                Math_SmoothStepToF(&boss->obj.pos.z, boss->fwork[3], 0.1f, 15.0f, 0.00001f);

                if (boss->timer_058 == 0) {
                    boss->timer_058 = D_i1_80199A4C[boss->swork[3]];
                    boss->fwork[20] = D_i1_80199A5C[boss->swork[3]];
                    boss->swork[3]++;
                    boss->swork[3] &= 3;
                    boss->fwork[8] = 0.0f;

                    if ((boss->swork[3] != 1) || (boss->swork[3] != 3)) {
                        Audio_KillSfxBySourceAndId(boss->sfxSource, NA_SE_EN_ZOBOSS_BEAM);
                        boss->swork[9] = 0;
                    }
                }

                if ((boss->swork[3] == 0) || (boss->swork[3] == 2)) {
                    if ((boss->obj.rot.y < 20.0f) && (boss->obj.rot.y > -20.0f)) {
                        if (boss->swork[9] == 0) {
                            boss->swork[9]++;
                            AUDIO_PLAY_SFX(NA_SE_EN_ZOBOSS_BEAM, boss->sfxSource, 4);
                            if (boss->swork[6] == 0) {
                                Radio_PlayMessage(gMsg_ID_2293, RCID_BOSS_CORNERIA2);
                            }
                            boss->swork[6]++;
                            boss->swork[6] &= 1;
                        }

                        if (((gGameFrameCount % 8) == 0)) {
                            if (fabsf(boss->obj.pos.z - gPlayer[0].trueZpos) > 700.0f) {

                                Matrix_MultVec3f(gCalcMatrix, &D_i1_801998F0[0], &sp84[3]);

                                for (effect = gEffects, i = 0; i < ARRAY_COUNT(gEffects); i++, effect++) {
                                    if (effect->obj.status == OBJ_FREE) {
                                        Effect_Initialize(effect);
                                        effect->obj.status = OBJ_INIT;
                                        effect->obj.id = OBJ_EFFECT_398;
                                        effect->timer_50 = 100;
                                        effect->unk_44 = 1;
                                        effect->scale2 = 1.0f;
                                        effect->obj.rot.z = 30.0f;
                                        effect->obj.pos.x = sp84[3].x + boss->obj.pos.x;
                                        effect->obj.pos.y = sp84[3].y + boss->obj.pos.y;
                                        effect->obj.pos.z = sp84[3].z + boss->obj.pos.z;
                                        Object_SetInfo(&effect->info, effect->obj.id);
                                        break;
                                    }
                                }

                                if (i >= 60) {
                                    effect->obj.status = OBJ_FREE;
                                }
                            }
                        }
                    }
                }

                if (boss->health < 2) {
                    gTeamLowHealthMsgTimer = -1;

                    Audio_KillSfxBySourceAndId(boss->sfxSource, NA_SE_EN_ZOBOSS_BEAM);

                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 40);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 40);

                    AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, boss->sfxSource, 4);

                    gScreenFlashTimer = 8;
                    gShowBossHealth = false;

                    Radio_PlayMessage(gMsg_ID_2294, RCID_BOSS_CORNERIA2);
                    boss->health = 1;
                    boss->timer_056 = 150;
                    boss->state = 8;
                    boss->fwork[19] = 15.0f;
                } else {
                    Math_SmoothStepToF(&boss->fwork[8], 3.0f, 0.1f, 0.5f, 0.001f);
                    Math_SmoothStepToAngle(&boss->obj.rot.z, boss->fwork[14], 0.1f, 3.0f, 0.00001f);

                    temp_fv0_2 = Math_SmoothStepToF(&boss->obj.rot.y, boss->fwork[20], 0.1f, boss->fwork[8], 0.00001f);
                    boss->fwork[14] = 0.0f;
                    if (temp_fv0_2 < -1.0f) {
                        boss->fwork[14] = 25.0f;
                    }
                    if (temp_fv0_2 > 1.0f) {
                        boss->fwork[14] = 335.0f;
                    }

                    sp78.x = 0.0f;
                    sp78.y = 0.0f;
                    sp78.z = 40.0f;

                    Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);

                    boss->vel.x = sp6C.x;
                    boss->vel.y = sp6C.y;
                    boss->vel.z = sp6C.z - gPathVelZ;
                }
                break;

            case 8:
                D_ctx_801779A8[0] = 20.0f;

                if (((gGameFrameCount % 32) == 0)) {
                    for (i = 0; i < 10; i++) {
                        func_effect_80079618(RAND_FLOAT_CENTERED(300.0f) + boss->obj.pos.x, boss->obj.pos.y,
                                             boss->obj.pos.z, 1.0f);
                    }
                }

                Math_SmoothStepToF(&boss->obj.pos.x, boss->fwork[7], 1.0f, 10.0f, 0.00001f);
                Math_SmoothStepToF(&boss->vel.x, 0.0f, 0.1f, 2.0f, 0.00001f);
                Math_SmoothStepToF(&boss->vel.y, 0.0f, 0.1f, 2.0f, 0.00001f);
                Math_SmoothStepToF(&boss->vel.z, 0.0f, 0.1f, 2.0f, 0.00001f);

                if (boss->obj.rot.z == boss->fwork[14]) {
                    if (boss->fwork[14] == boss->fwork[19]) {
                        boss->fwork[14] = 360.0f - boss->fwork[19];
                    } else {
                        boss->fwork[14] = boss->fwork[19];
                    }
                }

                Math_SmoothStepToAngle(&boss->obj.rot.z, boss->fwork[14], 1.0f, 1.0f, 0.001f);

                if (boss->health != 0) {
                    if (boss->timer_056 == 0) {
                        Boss_AwardBonus(boss);
                        boss->fwork[17] = 10.0f;
                        boss->vel.y *= 1.5f;
                        gMissionStatus = MISSION_ACCOMPLISHED;

                        if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_ACTIVE) ||
                            (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_U_TURN)) {
                            Boss_CompleteLevel(gPlayer, boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z);
                        }

                        boss->health--;
                        boss->fwork[8] = 0.0f;
                        Radio_PlayMessage(gMsg_ID_2296, RCID_BOSS_CORNERIA2);
                    } else {
                        Math_SmoothStepToF(&boss->obj.rot.y, 0.0f, 0.1f, boss->fwork[8], 0.00001f);
                        sp78.x = 0.0f;
                        sp78.y = 0.0f;
                        sp78.z = 20.0f;
                        Matrix_MultVec3f(gCalcMatrix, &sp78, &sp6C);
                        boss->vel.x = sp6C.x;
                        boss->vel.y = sp6C.y;
                        boss->vel.z = sp6C.z - gPathVelZ;
                        if (boss->timer_056 == 60) {
                            Radio_PlayMessage(gMsg_ID_2295, RCID_FOX);
                        }
                    }
                } else {
                    boss->state = 9;
                }
                break;

            case 9:
                if (((gGameFrameCount % 16) == 0)) {
                    for (i = 0; i < 10; i++) {
                        func_effect_80079618(RAND_FLOAT_CENTERED(300.0f) + boss->obj.pos.x, boss->obj.pos.y,
                                             boss->obj.pos.z, 1.0f);
                    }
                }
                Math_SmoothStepToF(&boss->vel.x, 0.0f, 0.1f, 2.0f, 0.00001f);
                Math_SmoothStepToF(&boss->vel.y, 0.0f, 0.1f, 2.0f, 0.00001f);
                Math_SmoothStepToF(&boss->vel.z, 0.0f, 0.1f, 2.0f, 0.00001f);

                boss->obj.rot.z -= 2.0f;
                boss->gravity = 1.0f;

                if (boss->obj.pos.y < (gGroundHeight + 150.0f)) {
                    gCameraShake = 100;
                    func_effect_80081A8C(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f, 12);
                    boss->timer_050 = 20;
                    boss->vel.y = -10.0f;
                    boss->gravity = 0.0f;
                    boss->fwork[17] = 20.0f;
                    Corneria_8018C0B0(boss);
                    boss->state = 10;
                }
                break;

            case 10:
                if (((gGameFrameCount % 8) == 0)) {
                    for (i = 0; i < 10; i++) {
                        func_effect_80079618(RAND_FLOAT_CENTERED(300.0f) + boss->obj.pos.x, boss->obj.pos.y,
                                             boss->obj.pos.z, 1.0f);
                    }
                }

                if (boss->timer_050 == 0) {
                    func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y + 500.0f, boss->obj.pos.z, 120.0f);
                    Object_Kill(&boss->obj, boss->sfxSource);
                }
                break;
        }
        temp_a0 = (float*) LOAD_ASSET(D_CO_603E748);
        temp_a1 = (float*) LOAD_ASSET(D_CO_603E7C4);
        temp_a0[9] = -100000.0f;
        temp_a0[3] = 172.0f;
        temp_a1[9] = -100000.0f;
        temp_a1[3] = -150.0f;

        if (boss->fwork[0] > 60.0f) {
            temp_a0[3] = -100000.0f;
            temp_a0[9] = 543.0f;
        }

        if (boss->fwork[1] > 60.0f) {
            temp_a1[3] = -100000.0f;
            temp_a1[9] = -557.0f;
        }

        boss->fwork[16] = 4.0f;

        if ((boss->swork[10] == 0) && (boss->state < 6)) {
            boss->fwork[17] = 1.8f;
            AUDIO_PLAY_SFX(NA_SE_EXPLOSION_DEMO6, boss->sfxSource, 4);
            boss->timer_058 = 71;
            boss->state = 6;
            boss->fwork[12] = 0.0f;
            boss->fwork[8] = 0.0f;
            boss->fwork[14] = 0.0f;
            boss->fwork[13] = 0.0f;
        }

        if (gBossFrameCount == 430) {
            Radio_PlayMessage(gMsg_ID_2225, RCID_SLIPPY);
        }
        if (gBossFrameCount == 586) {
            gShowBossHealth = true;
        }
        if (gBossFrameCount >= 587) {
            gBossHealthBar = (boss->health / 601.0f) * 255.0f;
        }
    }
}

static Vec3f D_i1_80199A6C = { -270.0f, 0.0f, 200.0f };
static Vec3f D_i1_80199A78 = { 440.0f, 0.0f, 0.0f };

void Corneria_8018DDAC(Boss* boss) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 i;

    switch (boss->state) {
        case 0:
            if (boss->dmgType != DMG_NONE) {
                boss->dmgType = DMG_NONE;
                if (boss->dmgPart == 0) {
                    if (boss->fwork[2] > 60.0f) {
                        if (boss->health != 0) {
                            boss->timer_05C = 15;
                            boss->health -= boss->damage;
                            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, boss->sfxSource, 4);
                            if (boss->health <= 0) {
                                gBosses[0].swork[8]--;
                                if (gBosses[0].swork[8] != 0) {
                                    Radio_PlayMessage(gMsg_ID_15130, RCID_FALCO);
                                } else {
                                    Radio_PlayMessage(gMsg_ID_7085, RCID_FALCO);
                                }

                                boss->info.cullDistance = 300.0f;

                                gBosses[0].fwork[14] = 25.0f;
                                gBosses[0].fwork[15] = 0.0f;

                                AUDIO_PLAY_SFX(NA_SE_EN_PARTS_BROKEN, boss->sfxSource, 4);

                                if (gBosses[0].swork[10] != 0) {
                                    gBosses[0].swork[10]--;
                                }
                                gBosses[0].timer_056 = 30;
                                boss->state = 1;
                                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A6C, &sp4C);

                                for (i = 0; i < 10; i++) {
                                    func_effect_80079618(boss->obj.pos.x + sp4C.x, boss->obj.pos.y + sp4C.y,
                                                         boss->obj.pos.z + sp4C.z, 1.0f);
                                }

                                if ((gBosses[2].state == 1) && (gBosses[3].state == 1)) {
                                    gBosses[0].fwork[14] = 335.0f;
                                }
                            }
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                }
            }
            boss->obj.rot.x = gBosses[0].obj.rot.x;
            boss->obj.rot.y = gBosses[0].obj.rot.y;
            boss->obj.rot.z = gBosses[0].obj.rot.z;

            Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);

            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A78, &sp40);

            boss->obj.pos.x = gBosses[0].obj.pos.x + sp40.x;
            boss->obj.pos.y = gBosses[0].obj.pos.y + sp40.y;
            boss->obj.pos.z = gBosses[0].obj.pos.z + sp40.z;

            boss->fwork[2] = gBosses[0].fwork[2];
            break;

        case 1:
            Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_NEW);
            gBosses[0].fwork[15] += 0.5f;

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                boss->timer_05C = 4;
            }

            if (((gGameFrameCount % 2) == 0)) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A6C, &sp4C);
                func_effect_8007C120(boss->obj.pos.x + sp4C.x, boss->obj.pos.y + sp4C.y, boss->obj.pos.z + sp4C.z,
                                     boss->vel.x, boss->vel.y, boss->vel.z, 0.2f, 10);
            }

            if (boss->obj.pos.y < (gGroundHeight + 150.0f)) {
                if (boss->swork[0] == 0) {
                    boss->vel.y = -5.0f;
                    boss->swork[0] = 1;
                    boss->gravity = 0.0f;
                    Corneria_8018C0B0(boss);
                    AUDIO_PLAY_SFX(NA_SE_OB_WATER_BOUND_M, boss->sfxSource, 4);
                }
            } else {
                boss->obj.rot.z -= 2.0f;
                boss->gravity = 1.0f;
            }
            break;
    }
}

static Vec3f D_i1_80199A84 = { 20.0f, -90.0f, 0.0f };
static Vec3f D_i1_80199A90 = { -440.0f, 210.0f, 0.0f };

void Corneria_8018E290(Boss* boss) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 i;

    switch (boss->state) {
        case 0:
            if (boss->dmgType != DMG_NONE) {
                boss->dmgType = DMG_NONE;
                if (boss->dmgPart == 2) {
                    if (boss->fwork[0] > 60.0f) {
                        if (boss->health != 0) {
                            boss->timer_05C = 15;
                            boss->health -= boss->damage;

                            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, boss->sfxSource, 4);

                            if (boss->health <= 0) {
                                gBosses[0].swork[8]--;

                                if (gBosses[0].swork[8] != 0) {
                                    Radio_PlayMessage(gMsg_ID_15130, RCID_FALCO);
                                } else {
                                    Radio_PlayMessage(gMsg_ID_7085, RCID_FALCO);
                                }

                                boss->info.cullDistance = 300.0f;

                                gBosses[0].fwork[15] = 0.0f;
                                gBosses[0].fwork[14] = 335.0f;
                                boss->health = 0;

                                AUDIO_PLAY_SFX(NA_SE_EN_PARTS_BROKEN, boss->sfxSource, 4);

                                if (gBosses[0].swork[10] != 0) {
                                    gBosses[0].swork[10]--;
                                }

                                gBosses[0].timer_056 = 30;
                                boss->state = 1;

                                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A84, &sp4C);

                                for (i = 0; i < 10; i++) {
                                    func_effect_80079618(boss->obj.pos.x + sp4C.x, boss->obj.pos.y + sp4C.y,
                                                         boss->obj.pos.z + sp4C.z, 1.0f);
                                }

                                if (gBosses[1].state == 1) {
                                    gBosses[0].fwork[14] = 25.0f;
                                }
                            }
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                }
            }
            boss->obj.rot.x = gBosses[0].obj.rot.x;
            boss->obj.rot.y = gBosses[0].obj.rot.y;
            boss->obj.rot.z = gBosses[0].obj.rot.z;

            Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);

            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A90, &sp40);

            boss->obj.pos.x = gBosses[0].obj.pos.x + sp40.x;
            boss->obj.pos.y = gBosses[0].obj.pos.y + sp40.y;
            boss->obj.pos.z = gBosses[0].obj.pos.z + sp40.z;

            boss->fwork[0] = gBosses[0].fwork[0];
            break;

        case 1:
            Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_NEW);
            gBosses[0].fwork[15] += 0.5f;

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                boss->timer_05C = 4;
            }

            if (((gGameFrameCount % 2) == 0)) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A84, &sp4C);
                func_effect_8007C120(boss->obj.pos.x + sp4C.x, boss->obj.pos.y + sp4C.y, boss->obj.pos.z + sp4C.z,
                                     boss->vel.x, boss->vel.y, boss->vel.z, 0.2f, 10);
            }

            if (boss->obj.pos.y < (gGroundHeight + 150.0f)) {
                if (boss->swork[0] == 0) {
                    boss->vel.y = -5.0f;
                    boss->swork[0] = 1;
                    boss->gravity = 0.0f;
                    Corneria_8018C0B0(boss);
                    AUDIO_PLAY_SFX(NA_SE_OB_WATER_BOUND_M, boss->sfxSource, 4);
                }
            } else {
                boss->obj.rot.z -= 2.0f;
                boss->gravity = 1.0f;
            }
            break;
    }
}

static Vec3f D_i1_80199A9C = { 20.0f, 90.0f, 0.0f };
static Vec3f D_i1_80199AA8 = { -440.0f, -210.0f, 0.0f };

void Corneria_8018E76C(Boss* boss) {
    Vec3f sp4C;
    Vec3f sp40;
    s32 i;

    switch (boss->state) {
        case 0:
            if (boss->dmgType != DMG_NONE) {
                boss->dmgType = DMG_NONE;
                if (boss->dmgPart == 2) {
                    if (boss->fwork[1] > 60.0f) {
                        if (boss->health != 0) {
                            boss->timer_05C = 15;
                            boss->health -= boss->damage;

                            AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, boss->sfxSource, 4);

                            if (boss->health <= 0) {
                                gBosses[0].swork[8]--;
                                if (gBosses[0].swork[8] != 0) {
                                    Radio_PlayMessage(gMsg_ID_15130, RCID_FALCO);
                                } else {
                                    Radio_PlayMessage(gMsg_ID_7085, RCID_FALCO);
                                }

                                boss->info.cullDistance = 300.0f;

                                gBosses[0].fwork[15] = 0.0f;
                                gBosses[0].fwork[14] = 335.0f;

                                boss->health = 0;

                                AUDIO_PLAY_SFX(NA_SE_EN_PARTS_BROKEN, boss->sfxSource, 4);

                                if (gBosses[0].swork[10] != 0) {
                                    gBosses[0].swork[10]--;
                                }

                                gBosses[0].timer_056 = 30;
                                boss->state = 1;
                                gBosses[0].fwork[6] = 500.0f;

                                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A9C, &sp4C);

                                for (i = 0; i < 10; i++) {
                                    func_effect_80079618(boss->obj.pos.x + sp4C.x, boss->obj.pos.y + sp4C.y,
                                                         boss->obj.pos.z + sp4C.z, 1.0f);
                                }

                                if (gBosses[1].state == 1) {
                                    gBosses[0].fwork[14] = 25.0f;
                                }
                            }
                        }
                    }
                } else {
                    AUDIO_PLAY_SFX(NA_SE_EN_REFLECT, boss->sfxSource, 4);
                }
            }
            boss->obj.rot.x = gBosses[0].obj.rot.x;
            boss->obj.rot.y = gBosses[0].obj.rot.y;
            boss->obj.rot.z = gBosses[0].obj.rot.z;

            Matrix_RotateY(gCalcMatrix, boss->obj.rot.y * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, boss->obj.rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_APPLY);

            Matrix_MultVec3f(gCalcMatrix, &D_i1_80199AA8, &sp40);

            boss->obj.pos.x = gBosses[0].obj.pos.x + sp40.x;
            boss->obj.pos.y = gBosses[0].obj.pos.y + sp40.y;
            boss->obj.pos.z = gBosses[0].obj.pos.z + sp40.z;

            boss->fwork[1] = gBosses[0].fwork[1];
            break;

        case 1:
            Matrix_RotateZ(gCalcMatrix, boss->obj.rot.z * M_DTOR, MTXF_NEW);

            gBosses[0].fwork[15] += 0.5f;

            if (((gGameFrameCount % 8) == 0) && (Rand_ZeroOne() < 0.5f)) {
                boss->timer_05C = 4;
            }

            if (((gGameFrameCount % 2) == 0)) {
                Matrix_MultVec3f(gCalcMatrix, &D_i1_80199A9C, &sp4C);
                func_effect_8007C120(boss->obj.pos.x + sp4C.x, boss->obj.pos.y + sp4C.y, boss->obj.pos.z + sp4C.z,
                                     boss->vel.x, boss->vel.y, boss->vel.z, 0.2f, 10);
            }

            if (boss->obj.pos.y < (gGroundHeight + 150.0f)) {
                if (boss->swork[0] == 0) {
                    boss->vel.y = -5.0f;
                    boss->swork[0] = 1;
                    boss->gravity = 0.0f;
                    Corneria_8018C0B0(boss);
                    AUDIO_PLAY_SFX(NA_SE_OB_WATER_BOUND_M, boss->sfxSource, 4);
                }
            } else {
                boss->obj.rot.z -= 2.0f;
                boss->gravity = 1.0f;
            }
            break;
    }
}

bool Corneria_8018EC54(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if ((limbIndex == 10) && (gBosses[2].state != 0) && (gBosses[3].state != 0)) {
        *dList = NULL;
    }
    if ((limbIndex != 12) && (limbIndex != 10)) {
        *dList = NULL;
    }
    return false;
}

void Corneria_8018ECAC(Boss* boss) {
    Animation_GetFrameData(D_CO_602D400, 0, boss->vwork);
    Animation_DrawSkeleton(1, D_CO_602D5AC, boss->vwork, Corneria_8018EC54, NULL, &boss->index, &gIdentityMatrix);
}

bool Corneria_8018ED1C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex == 5) {
        rot->y -= gBosses[*(s32*) data].fwork[2];
    }
    if ((limbIndex != 6) && (limbIndex != 5)) {
        *dList = NULL;
    }
    return false;
}

void Corneria_8018ED78(Boss* boss) {
    Matrix_Translate(gGfxMatrix, -D_i1_80199A78.x, -D_i1_80199A78.y, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Animation_GetFrameData(D_CO_602D400, 0, boss->vwork);
    Animation_DrawSkeleton(1, D_CO_602D5AC, boss->vwork, Corneria_8018ED1C, NULL, &boss->index, &gIdentityMatrix);
}

bool Corneria_8018EE2C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex == 1) {
        rot->z -= gBosses[*(s32*) data].fwork[0];
    }
    if ((limbIndex != 1) && (limbIndex != 2)) {
        *dList = NULL;
    }
    return false;
}

void Corneria_8018EE84(Boss* boss) {
    Matrix_Translate(gGfxMatrix, -D_i1_80199A90.x, -D_i1_80199A90.y, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Animation_GetFrameData(D_CO_602D400, 0, boss->vwork);
    Animation_DrawSkeleton(1, D_CO_602D5AC, boss->vwork, Corneria_8018EE2C, NULL, &boss->index, &gIdentityMatrix);
}

bool Corneria_8018EF38(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex == 3) {
        rot->z -= gBosses[*(s32*) data].fwork[1];
    }
    if ((limbIndex != 3) && (limbIndex != 4)) {
        *dList = NULL;
    }
    return false;
}

void Corneria_8018EF90(Boss* boss) {
    Matrix_Translate(gGfxMatrix, -D_i1_80199AA8.x, -D_i1_80199AA8.y, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Animation_GetFrameData(D_CO_602D400, 0, boss->vwork);
    Animation_DrawSkeleton(1, D_CO_602D5AC, boss->vwork, Corneria_8018EF38, NULL, &boss->index, &gIdentityMatrix);
}

void Corneria_8018F044(Scenery* scenery) {
    switch (scenery->state) {
        case 0:
            if (scenery->dmgType != DMG_NONE) {
                scenery->dmgType = DMG_NONE;
                if (scenery->dmgPart < 2) {
                    scenery->unk_44++;
                    scenery->timer_4C = 5;
                    scenery->vel.x += 2.0f;
                    scenery->vel.y += 2.0f;
                    if (scenery->unk_44 >= 3) {
                        scenery->state = 1;
                        scenery->info.hitbox = (float*) LOAD_ASSET(&D_CO_603E924);
                        AUDIO_PLAY_SFX(NA_SE_OB_GATE_OPEN, scenery->sfxSource, 0);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_EN_DAMAGE_S, scenery->sfxSource, 0);
                    }
                }
            }
            break;

        case 1:
            Math_SmoothStepToF(&scenery->vel.x, 80.0f, 0.2f, 10.0f, 0.0f);
            Math_SmoothStepToF(&scenery->vel.y, 80.0f, 0.2f, 10.0f, 0.0f);
            break;
    }
}

bool Corneria_8018F1C8(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Scenery* scenery = (Scenery*) data;

    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

    switch (limbIndex) {
        case 1:
            rot->y -= scenery->vel.x;
            if ((scenery->timer_4C % 2) != 0) {
                RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            break;

        case 2:
            rot->y += scenery->vel.y;
            if ((scenery->timer_4C % 2) != 0) {
                RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
            break;
    }
    return 0;
}

void Corneria_8018F31C(Scenery* scenery) {
    Vec3f sp28[10];

    Animation_GetFrameData(D_CO_602AA7C, 0, sp28);
    Animation_DrawSkeleton(3, D_CO_602AB48, sp28, Corneria_8018F1C8, NULL, scenery, gCalcMatrix);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
}

void Corneria_8018F3BC(Scenery* scenery, f32 arg1) {
    Scenery_Initialize(scenery);

    scenery->obj.status = OBJ_INIT;
    scenery->obj.pos.x = RAND_FLOAT_CENTERED(1000.0f) + arg1;
    scenery->obj.rot.y = RAND_FLOAT(90.0f) + 45.0f;

    if (arg1 > 0.0f) {
        scenery->obj.rot.y *= -1.0f;
    }

    scenery->obj.pos.y = 0.0f;
    scenery->obj.id = OBJ_SCENERY_1;
    scenery->effectVel.z = 60.0f;
    Object_SetInfo(&scenery->info, scenery->obj.id);
    scenery->obj.pos.z = -2000.0f;
    scenery->info.cullDistance = 15000.0f;
}

void Corneria_8018F4A4(void) {
    s32 i;

    if (((gGameFrameCount % 16) == 0) && !(gPlayer[0].csState < 4)) {
        for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
            if (gScenery[i].obj.status == OBJ_FREE) {
                Corneria_8018F3BC(&gScenery[i], 4000.0f);
                break;
            }
        }

        for (i = 0; i < ARRAY_COUNT(gScenery); i++) {
            if (gScenery[i].obj.status == OBJ_FREE) {
                Corneria_8018F3BC(&gScenery[i], -4000.0f);
                break;
            }
        }
    }
}

void Corneria_8018F55C(Effect* effect) {

    Effect_Initialize(effect);
    effect->obj.status = OBJ_INIT;
    effect->obj.pos.x = gPlayer[0].cam.eye.x + RAND_FLOAT_CENTERED(500.0f);
    effect->obj.pos.y = gPlayer[0].cam.eye.y + RAND_RANGE(-280.0f, 70.0f);
    effect->obj.id = OBJ_EFFECT_352;
    effect->timer_50 = 80;
    effect->unk_46 = 144;
    effect->obj.pos.z = -4000.0f;
    effect->vel.z = 60.0f;
    effect->scale2 = 10.0f + RAND_FLOAT(15.0f);

    if (Rand_ZeroOne() < 0.5f) {
        effect->obj.rot.z = 180.0f;
    }

    Object_SetInfo(&effect->info, effect->obj.id);
}

void Corneria_8018F678(void) {
    s32 i;

    if (((gGameFrameCount % 32) == 0) && gPlayer[0].pos.x == 0.0f) {
        for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
            if (gEffects[i].obj.status == OBJ_FREE) {
                Corneria_8018F55C(&gEffects[i]);
                return;
            }
        }
    }
}

static f32 D_i1_80199AB4[3] = { 180.0f, -180.0f, 0.0f };

static f32 D_i1_80199AC0[3] = { 200.0f, 140.0f, 200.0f };

static f32 D_i1_80199ACC[3] = { 160.0f, 160.0f, 320.0f };

static f32 D_i1_80199AD8[3] = { -60.0f, 60.0f, -45.0f };

void Corneria_8018F6F8(Actor* actor, s32 arg1) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;

    actor->obj.pos.x = (D_i1_80199AB4[arg1] * 4.0f) + gPlayer[0].pos.x;
    actor->obj.pos.y = (D_i1_80199AC0[arg1] * 2.0f) + gPlayer[0].pos.y;
    actor->obj.pos.z = (D_i1_80199ACC[arg1] * 3.0f) + gPlayer[0].trueZpos;

    actor->vwork[20].x = D_i1_80199AB4[arg1] + gPlayer[0].pos.x;
    actor->vwork[20].y = gPlayer[0].pos.y;
    actor->vwork[20].z = D_i1_80199ACC[arg1] + gPlayer[0].trueZpos;

    actor->obj.rot.z = D_i1_80199AD8[arg1];
    actor->obj.rot.y = 180.0f;

    actor->state = 100;
    actor->fwork[0] = RAND_FLOAT(360.0f);

    Object_SetInfo(&actor->info, actor->obj.id);

    actor->drawShadow = true;
    actor->iwork[11] = 1;
    actor->info.cullDistance = 200.0f;
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void Corneria_LevelStart(Player* player) {
    s32 i;
    Actor* actor0 = &gActors[0];
    Actor* actor1 = &gActors[1];
    Actor* actor2 = &gActors[2];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    if (gCsFrameCount < 815) {
        sp3C = player->pos.x;
        sp38 = player->pos.y + 15.0f;
        sp34 = player->trueZpos - 20.0f;
    } else {
        if (gCsFrameCount < 1009) {
            sp3C = actor0->obj.pos.x;
            sp38 = actor0->obj.pos.y + 15.0f;
            sp34 = actor0->obj.pos.z - 20.0f;
        } else if (gCsFrameCount < 1198) {
            sp3C = actor2->obj.pos.x;
            sp38 = actor2->obj.pos.y + 15.0f;
            sp34 = actor2->obj.pos.z - 20.0f;
        } else {
            sp3C = actor1->obj.pos.x;
            sp38 = actor1->obj.pos.y + 15.0f;
            sp34 = actor1->obj.pos.z - 20.0f;
        }
    }

    sp2C = -Math_Atan2F(player->cam.eye.x - sp3C, player->cam.eye.z - sp34);
    sp30 = -Math_Atan2F(player->cam.eye.y - sp38, sqrtf(SQ(player->cam.eye.z - sp34) + SQ(player->cam.eye.x - sp3C)));
    sp44 = Math_RadToDeg(sp2C) - D_ctx_80177A48[4];
    sp40 = Math_RadToDeg(sp30) - D_ctx_80177A48[5];

    if (sp44 > 180.0f) {
        sp44 -= 360.0f;
    }
    if (sp44 < -180.0f) {
        sp44 += 360.0f;
    }
    if (sp40 > 180.0f) {
        sp40 -= 360.0f;
    }
    if (sp40 < -180.0f) {
        sp40 += 360.0f;
    }

    D_ctx_80177A48[6] += fabsf(sp44);
    D_ctx_80177A48[7] += fabsf(sp40);

    if (sp2C >= 0.0f) {
        Texture_Scroll(D_arwing_30184D8, 64, 32, 2);
        Texture_Scroll(D_arwing_30184D8, 64, 32, 2);
    } else {
        Texture_Scroll(D_arwing_30184D8, 64, 32, 3);
        Texture_Scroll(D_arwing_30184D8, 64, 32, 3);
    }

    for (i = 0; (i < 40 && D_ctx_80177A48[6] >= 0.2f); i++, D_ctx_80177A48[6] -= 0.2f) {
        if (sp44 >= 0) {
            Texture_Scroll(D_arwing_30184D8, 64, 32, 2);
        } else {
            Texture_Scroll(D_arwing_30184D8, 64, 32, 3);
        }
    }

    for (i = 0; (i < 40 && D_ctx_80177A48[7] >= 0.3f); i++, D_ctx_80177A48[7] -= 0.3f) {
        if (sp40 >= 0) {
            Texture_Scroll(D_arwing_30184D8, 64, 32, 0);
        } else {
            Texture_Scroll(D_arwing_30184D8, 64, 32, 1);
        }
    }

    D_ctx_80177A48[4] = Math_RadToDeg(sp2C);
    D_ctx_80177A48[5] = Math_RadToDeg(sp30);

    player->flags_228 = 0;

    D_ctx_80177950 = -1.0f;
    if ((Math_RadToDeg(gPlayer[0].camYaw) < 90.0f) || (Math_RadToDeg(gPlayer[0].camYaw) > 270.0f)) {
        D_ctx_80177950 = 1.0f;
    }

    player->vel.z = 0.0f;
    player->pos.z = player->pos.z;
    player->trueZpos = player->pos.z + player->camDist;
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.5f;
    player->rockPhase += 3.0f;
    player->rockAngle = SIN_DEG(player->rockPhase) * 1.5f;

    Corneria_8018F678();

    player->wings.unk_30 = 0;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->csState = 1;
            player->csTimer = 600;
            player->pos.y = 6000.0f;
            player->pos.x = 0.1f;

            Corneria_8018F6F8(&gActors[0], 0);
            Corneria_8018F6F8(&gActors[1], 1);
            Corneria_8018F6F8(&gActors[2], 2);

            actor0->iwork[14] = 2;
            actor1->iwork[14] = 3;
            actor2->iwork[14] = 4;

            player->cam.eye.x = gCsCamEyeX = player->pos.x - 400.0f;
            gPlayer[0].cam.eye.y = gCsCamEyeY = player->pos.y + 600.0f;
            player->cam.eye.z = gCsCamEyeZ = player->trueZpos + 2000.0f;

            player->cam.at.x = gCsCamAtX = player->pos.x;
            player->cam.at.y = gCsCamAtY = player->pos.y;
            player->cam.at.z = gCsCamAtZ = player->trueZpos + 300.0f;

            D_ctx_80177A48[0] = 0;
            D_ctx_80177A48[1] = D_ctx_80177A48[2] = 0;

            gFillScreenAlphaTarget = 255;
            gFillScreenAlpha = 255;
            gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            break;

        case 1:
            if (player->csTimer < 550) {
                gFillScreenAlphaTarget = 0;
                gFillScreenAlphaStep = 3;
                Math_SmoothStepToF(&D_ctx_80177A48[0], 0.01f, 1.0f, 0.0005f, 0.0f);
            }

            gCsCamEyeX = player->pos.x - 150.0f;
            gCsCamEyeY = player->pos.y - 70.0f;
            gCsCamEyeZ = player->trueZpos + 150.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->trueZpos;

            if (player->csTimer == 0) {
                player->csState = 2;
                player->csTimer = 130;
                D_ctx_80177A48[0] = 0.0f;
            }

            if (player->csTimer == 315) {
                player->pos.x = 0.0f;
            }

            if (player->csTimer == 270) {
                gHideRadio = false;
                Radio_PlayMessage(gMsg_ID_2005, RCID_FOX);
            }

            if (player->csTimer == 180) {
                AUDIO_PLAY_SFX(NA_SE_WING_OPEN, player->sfxSource, 0);
            }

            if (player->csTimer == 120) {
                AUDIO_PLAY_SFX(NA_SE_WING_OPEN_END, player->sfxSource, 0);
            }

            if ((player->csTimer < 190) && (player->csTimer > 150)) {
                Math_SmoothStepToF(&player->wings.unk_24, 2.0f, 0.2f, 0.5f, 0.0f);
            }

            if (player->csTimer < 150) {
                player->unk_204 = 0;
            }

            if ((player->csTimer < 120) && ((player->csTimer % 16) == 0)) {
                D_ctx_80177A48[1] = RAND_FLOAT_CENTERED(60.0f);
                D_ctx_80177A48[2] = RAND_FLOAT_CENTERED(60.0f);
            }

            if (player->csTimer == 0) {
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = D_ctx_80177A48[1];
            }
            break;

        case 2:
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.001f, 0.0f);

            gCsCamEyeX = player->pos.x - 50.0f;
            gCsCamEyeY = player->pos.y + 10.0f;
            gCsCamEyeZ = player->trueZpos - 10.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 10.0f;
            gCsCamAtZ = player->trueZpos + 10.0f;

            if (player->csTimer == 20) {
                Radio_PlayMessage(gMsg_ID_2010, RCID_FOX);
            }

            if (player->csTimer == 0) {
                player->csState = 3;
                player->csTimer = 180;
                player->unk_004 = 0.0f;
                actor0->state = 0;
                actor2->state = 0;
                actor1->state = 0;
                actor0->obj.pos.y = player->pos.y + 80.0f;
                actor0->obj.pos.z += 100.0f;
            }

            if (gMsgCharIsPrinting && (gGameFrameCount & 2)) {
                player->wings.unk_30 = 5.0f;
            }
            break;

        case 3:
            if (fabsf(Math_SmoothStepToF(&actor0->obj.pos.z, player->pos.z + 100.0f, 0.05f, 5.0f, 0.0f)) < 1.0f) {
                player->csState = 4;
                D_ctx_80177A48[0] = 0.0f;
                player->csTimer = 190;
            }

            if (gMsgCharIsPrinting && ((gGameFrameCount & 2) != 0)) {
                player->wings.unk_30 = 5.0f;
            }

            gCsCamEyeY = player->pos.y + 10.0f;
            gCsCamAtY = player->pos.y + 10.0f;
            break;

        case 4:
            if (gMsgCharIsPrinting && ((gGameFrameCount & 2) != 0)) {
                player->wings.unk_30 = 5.0f;
            }

            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.001f, 0.0f);

            gCsCamEyeX = actor0->obj.pos.x - 50.0f;
            gCsCamEyeY = actor0->obj.pos.y + 10.0f;
            gCsCamEyeZ = actor0->obj.pos.z - 10.0f;

            gCsCamAtX = actor0->obj.pos.x;
            gCsCamAtY = actor0->obj.pos.y + 10.0f;
            gCsCamAtZ = actor0->obj.pos.z + 10.0f;

            if (player->csTimer == 0) {
                player->csState = 5;
                player->csTimer = 5;
            }

            if (player->csTimer == 80) {
                Radio_PlayMessage(gMsg_ID_2020, RCID_FALCO);
            }

            if (player->csTimer < 100) {
                Math_SmoothStepToF(&actor0->fwork[19], 50.0f, 0.1f, 3.0f, 0.01f);
            }

            actor0->fwork[20] = 0.0f;

            if (gMsgCharIsPrinting && ((gGameFrameCount & 2) != 0)) {
                actor0->fwork[20] = 5.0f;
            }
            break;

        case 5:
            Math_SmoothStepToF(&actor0->fwork[19], 0, 0.1f, 3.0f, 0.01f);

            if (player->csTimer == 0) {
                player->csState = 6;
                D_ctx_80177A48[0] = 0.0f;
                player->csTimer = 190;
            }

            gCsCamEyeY = actor0->obj.pos.y + 10.0f;
            gCsCamAtY = actor0->obj.pos.y + 10.0f;
            break;

        case 6:
            Math_SmoothStepToF(&actor0->fwork[19], 0.0f, 0.1f, 3.0f, 0.01f);
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.001f, 0.0f);

            D_ctx_80177A48[3] -= 0.5f;

            gCsCamEyeX = actor2->obj.pos.x + 100.0f + D_ctx_80177A48[3];
            gCsCamEyeY = actor2->obj.pos.y + 10.0f;
            gCsCamEyeZ = actor2->obj.pos.z - 70.0f;

            gCsCamAtX = actor2->obj.pos.x + 20.0f + (D_ctx_80177A48[3] * 0.5f);
            gCsCamAtY = actor2->obj.pos.y + 10.0f;
            gCsCamAtZ = actor2->obj.pos.z + 10.0f;

            if (player->csTimer == 0) {
                player->csState = 7;
                player->csTimer = 190;
                D_ctx_80177A48[0] = 0.0f;
                actor0->obj.pos.y = player->pos.y;
                actor0->obj.pos.z = player->trueZpos + 240.0f;
            }

            if (player->csTimer == 80) {
                Radio_PlayMessage(gMsg_ID_2030, RCID_PEPPY);
            }

            actor2->fwork[20] = 0.0f;

            if (gMsgCharIsPrinting && ((gGameFrameCount & 2) != 0)) {
                actor2->fwork[20] = 5.0f;
            }
            break;

        case 7:
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.001f, 0.0f);

            gCsCamEyeX = actor1->obj.pos.x + 20.0f;
            gCsCamEyeY = actor1->obj.pos.y + 10.0f;
            gCsCamEyeZ = actor1->obj.pos.z - 50.0f;

            gCsCamAtX = actor1->obj.pos.x + 10.0f;
            gCsCamAtY = actor1->obj.pos.y + 10.0f;
            gCsCamAtZ = actor1->obj.pos.z + 10.0f;

            if (player->csTimer == 0) {
                player->csState = 8;
                D_ctx_80177A48[0] = 0.0f;
                player->csTimer = 300;
                D_ctx_80177A48[8] = 50.0f;
                D_ctx_80177A48[3] = 0.0f;
            }

            if (player->csTimer == 80) {
                Radio_PlayMessage(gMsg_ID_2040, RCID_SLIPPY);
                player->pos.x = 0.1f;
            }

            if (player->csTimer < 100) {
                Math_SmoothStepToF(&actor1->fwork[19], -20.0f, 0.1f, 3.0f, 0.01f);
            }

            actor1->fwork[20] = 0.0f;

            if (gMsgCharIsPrinting && ((gGameFrameCount & 2) != 0)) {
                actor1->fwork[20] = 5.0f;
            }
            break;

        case 8:
            Math_SmoothStepToF(&D_ctx_80177A48[0], 0.1f, 1.0f, 0.001f, 0.0f);

            if (player->csTimer < 150) {
                D_ctx_80177A48[3] += player->unk_004;
                Math_SmoothStepToF(&player->unk_004, 2.0f, 1.0f, 0.2f, 0.0f);
            }
            gCsCamEyeX = player->pos.x;
            gCsCamEyeZ = (player->trueZpos - 600.0f) + D_ctx_80177A48[3];
            gCsCamEyeY = player->pos.y + D_ctx_80177A48[8];

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y + 20.0f;
            gCsCamAtZ = player->trueZpos + 100.0f;

            if (player->csTimer < 100) {
                Math_SmoothStepToF(&D_ctx_80177A48[8], 10.0f, 0.1f, 0.7f, 0.0f);
            }

            if (player->csTimer == 200) {
                Radio_PlayMessage(gMsg_ID_2050, RCID_FOX);
            }

            player->wings.unk_30 = 0.0f;

            if (gMsgCharIsPrinting && ((gGameFrameCount & 2) != 0)) {
                player->wings.unk_30 = 5.0f;
            }

            if (player->csTimer == 80) {
                actor0->fwork[29] = 5.0f;
            }

            if (player->csTimer == 60) {
                actor1->fwork[29] = 5.0f;
            }

            if (player->csTimer == 40) {
                actor2->fwork[29] = 5.0f;
            }

            if ((player->csTimer > 70) && (player->csTimer < 80)) {
                actor0->iwork[11] = 2;
            }

            if ((player->csTimer > 50) && (player->csTimer < 60)) {
                actor1->iwork[11] = 2;
            }

            if ((player->csTimer > 30) && (player->csTimer < 40)) {
                actor2->iwork[11] = 2;
            }

            if (player->csTimer == 70) {
                actor0->state = 1;
                Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_BOOST);
            }

            if (player->csTimer == 50) {
                actor1->state = 2;
                Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_BOOST);
            }

            if (player->csTimer == 30) {
                actor2->state = 3;
                Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_BOOST);
            }

            if (player->csTimer == 0) {
                player->csState = 9;
                Play_PlaySfxFirstPlayer(player->sfxSource, NA_SE_ARWING_BOOST);
                player->csTimer = 3;
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
            }
            break;

        case 9:
            gCsCamEyeX = player->pos.x;
            gCsCamEyeY = player->pos.y;
            gCsCamEyeZ = player->trueZpos + 1000.0f;

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->trueZpos + 1100.0f;

            D_ctx_80177A48[0] = 0.03f;

            player->unk_190 = 2.0f;

            if (player->csTimer == 0) {
                gFillScreenAlphaTarget = 255;
                gFillScreenAlphaStep = 48;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
            }

            if (gFillScreenAlpha == 255) {
                AUDIO_PLAY_BGM(gBgmSeqId);

                Object_Kill(&actor0->obj, actor0->sfxSource);
                Object_Kill(&actor1->obj, actor1->sfxSource);
                Object_Kill(&actor2->obj, actor2->sfxSource);

                gLevelStartStatusScreenTimer = 80;

                player->pos.y = 350.0f;
                player->cam.eye.x = player->pos.x;
                player->cam.eye.y = (player->pos.y * player->unk_148) + 50.0f;
                player->cam.eye.z = 30.0f;
                player->state_1C8 = PLAYERSTATE_1C8_ACTIVE;
                player->csState = 0;
                player->cam.at.x = player->pos.x;
                player->cam.at.y = (player->pos.y * player->unk_148) + 20.0f;
                player->cam.at.z = player->trueZpos;

                D_ctx_80177950 = 1.0f;

                gPlayerGlareAlphas[0] = gPlayerGlareAlphas[1] = gPlayerGlareAlphas[2] = gPlayerGlareAlphas[3] = 0;
                gLoadLevelObjects = 1;
                gFillScreenAlphaTarget = 0;
                player->csTimer = 15;
            }
            break;

        case 10:
            break;
    }

    Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.y, player->yBob + gCsCamEyeY, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 20000.0f, 0.0f);

    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY - player->yBob, D_ctx_80177A48[0], 20000.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 20000.0f, 0.0f);

    Math_SmoothStepToF(&player->wings.unk_04, D_ctx_80177A48[1], 0.2f, 1.0f, 0.0f);
    Math_SmoothStepToF(&player->wings.unk_0C, D_ctx_80177A48[2], 0.2f, 1.0f, 0.0f);

    player->wings.unk_08 = player->wings.unk_04;
    player->wings.unk_10 = player->wings.unk_0C;

    player->cam.eye.y -= 3.0f;
    player->cam.at.y -= 3.0f;
    player->pos.y -= 3.0f;

    actor0->vwork[20].y -= 3.0f;
    actor0->obj.pos.y -= 3.0f;
    actor2->vwork[20].y -= 3.0f;
    actor2->obj.pos.y -= 3.0f;
    actor1->vwork[20].y -= 3.0f;
    actor1->obj.pos.y -= 3.0f;
}

static f32 D_i1_80199AE4[3] = { -1500.0f, 700.0f, 0.0f };

static f32 D_i1_80199AF0[3] = { -300.0f, 400.0f, 500.0f };

static f32 D_i1_80199AFC[3] = { 500.0f, 800.0f, 1200.0f };

static f32 D_i1_80199B08[3] = { -150.0f, 150.0f, 0.0f };

static f32 D_i1_80199B14[3] = { 0.0f, 0.0f, 0.0f };

static f32 D_i1_80199B20[3] = { 200.0f, 200.0f, 400.0f };

static f32 D_i1_80199B2C[3] = { 180.0f, -120.0f, 180.0f };

void Corneria_80190F74(Actor* actor, s32 arg1) {
    Vec3f sp5C;
    Vec3f sp50;
    Vec3f sp44;
    Vec3f sp38;
    Player* player = &gPlayer[0];

    Matrix_RotateY(gCalcMatrix, player->rot.y * M_DTOR, MTXF_NEW);
    sp5C.x = D_i1_80199AE4[arg1];
    sp5C.y = D_i1_80199AF0[arg1];
    sp5C.z = D_i1_80199AFC[arg1];

    sp44.x = D_i1_80199B08[arg1];
    sp44.y = D_i1_80199B14[arg1];
    sp44.z = D_i1_80199B20[arg1];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp5C, &sp50);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);

    Actor_Initialize(actor);

    actor->obj.pos.x = player->pos.x + sp50.x;
    actor->obj.pos.y = player->pos.y + sp50.y;
    actor->obj.pos.z = player->pos.z + sp50.z;

    actor->fwork[0] = sp38.x;
    actor->fwork[1] = sp38.y;
    actor->fwork[2] = sp38.z;

    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);

    actor->vel.x = player->vel.x;
    actor->vel.y = player->vel.y;
    actor->vel.z = player->vel.z;

    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.rot.z = D_i1_80199B2C[arg1];

    Object_SetInfo(&actor->info, actor->obj.id);

    actor->iwork[11] = 1;
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void Corneria_LevelComplete1(Player* player) {
    Vec3f sp64;
    Vec3f sp58;
    f32 sp54;
    f32 var_fv1;
    f32 sp4C;
    f32 temp_fa0;
    f32 temp_fa1;
    f32 temp_deg;

    player->wings.unk_04 = player->wings.unk_0C = player->wings.unk_08 = player->wings.unk_10 = 0.0f;

    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->boostSpeed, 0.0f, 0.1f, 3.0f, 0.0f);

    if (player->csState >= 3) {
        player->cam.eye.y += 3.0f;
        player->cam.at.y += 3.0f;
        player->pos.y += 3.0f;
        gActors[0].obj.pos.y += 3.0f;
        gActors[1].obj.pos.y += 3.0f;
        gActors[2].obj.pos.y += 3.0f;
    }

    gBgColor = 0x845; // 8, 8, 32

    switch (player->csState) {
        case 0:
            Audio_StopSfxByBankAndSource(1, player->sfxSource);

            sp54 = player->cam.eye.x - D_i1_8019B6D8[62];
            sp4C = player->cam.eye.z - D_i1_8019B6D8[64];

            D_ctx_80177A48[0] = Math_RadToDeg(Math_Atan2F(sp54, sp4C));
            D_ctx_80177A48[1] = sqrtf(SQ(sp54) + SQ(sp4C));

            player->csState++;

            D_ctx_80177A48[5] = 0.0f;
            D_ctx_80177A48[4] = D_ctx_80177A48[5];
            D_ctx_80177A48[2] = D_ctx_80177A48[5];
            /* fallthrough */
        case 1:
            Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 5.0f, 0.0f);
            Math_SmoothStepToF(&player->pos.y, 400.0f, 0.05f, 3.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[1], 1300.0f, 0.05f, 1000.0f, 0.0f);

            if (player->rot.y > 180.0f) {
                D_ctx_80177A48[0] += 0.5f;
            } else {
                D_ctx_80177A48[0] -= 0.5f;
            }

            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[0] * M_DTOR, MTXF_NEW);

            sp64.x = 0.0f;
            sp64.y = 0.0f;
            sp64.z = D_ctx_80177A48[1];

            Matrix_MultVec3f(gCalcMatrix, &sp64, &sp58);

            Math_SmoothStepToF(&player->cam.eye.x, D_i1_8019B6D8[62] + sp58.x, 0.05f, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.y, D_i1_8019B6D8[63] + 100.0f, 0.05f, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.z, D_i1_8019B6D8[64] + sp58.z, 0.05f, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.x, D_i1_8019B6D8[62], 0.05f, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, D_i1_8019B6D8[63], 0.05f, 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, D_i1_8019B6D8[64], 0.05f, 500.0f, 0.0f);

            temp_fa0 = player->pos.x - D_i1_8019B6D8[62];
            temp_fa1 = player->pos.z - D_i1_8019B6D8[64];

            if (gCsFrameCount < 30) {
                temp_deg = Math_RadToDeg(-Math_Atan2F(temp_fa0, temp_fa1));
                var_fv1 = Math_SmoothStepToAngle(&player->rot.y, temp_deg, 0.5f, 4.0f, 0.0001f) * 20.0f;
            } else {
                temp_deg = Math_RadToDeg(Math_Atan2F(temp_fa0, temp_fa1));
                var_fv1 = Math_SmoothStepToAngle(&player->rot.y, temp_deg, 0.5f, 2.0f, 0.0001f) * 30.0f;
            }

            Math_SmoothStepToAngle(&player->rot.z, var_fv1, 0.1f, 5.0f, 0.0001f);

            if (gCsFrameCount == 220) {
                player->csState++;
            }
            break;

        case 2:
            Math_SmoothStepToAngle(&player->rot.x, 20.0f, 0.1f, 0.5f, 0.0001f);
            Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.1f, 1.0f, 0.0001f);

            Math_SmoothStepToF(&D_ctx_80177A48[2], 0.05f, 1.0f, 0.005f, 0.0001f);

            Math_SmoothStepToF(&player->cam.at.x, player->pos.x, D_ctx_80177A48[2], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, player->pos.y, D_ctx_80177A48[2], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, player->pos.z, D_ctx_80177A48[2], 500.0f, 0.0f);

            if (gCsFrameCount == 350) {
                player->csState++;
                D_ctx_80177A48[2] = 0.0f;
                D_ctx_80177A48[3] = 0.05f;
            }
            break;

        case 3:
            if ((gCsFrameCount > 700) && (gCsFrameCount < 1000)) {
                func_demo_8004AA84();
            }
            Math_SmoothStepToAngle(&player->rot.x, 20.0f, 0.1f, 0.5f, 0);
            Math_SmoothStepToAngle(&player->rot.z, 0.0f, 0.1f, 1.0f, 0);

            Math_SmoothStepToF(&player->baseSpeed, 0.0f, 0.1f, 2.0f, 0.0f);

            Math_SmoothStepToF(&D_ctx_80177A48[2], 0.1f, 1.0f, 0.002f, 0);
            Math_SmoothStepToF(&D_ctx_80177A48[3], 0.1f, 1.0f, 0.002f, 0);

            Matrix_RotateY(gCalcMatrix, player->rot.y * M_DTOR, MTXF_NEW);
            Matrix_Push(&gCalcMatrix);
            Matrix_RotateY(gCalcMatrix, D_ctx_80177A48[5] * M_DTOR, MTXF_APPLY);

            sp64.x = 0.0f;
            sp64.y = -200.0f;
            sp64.z = 800.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp64, &sp58);

            Math_SmoothStepToF(&player->cam.eye.x, player->pos.x + sp58.x, D_ctx_80177A48[2], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.y, player->pos.y + sp58.y, D_ctx_80177A48[2], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.z, player->pos.z + sp58.z, D_ctx_80177A48[2], 500.0f, 0.0f);

            Matrix_Pop(&gCalcMatrix);

            sp64.x = 0.0f;
            sp64.y = 0;
            sp64.z = 150.0f;

            Matrix_MultVec3f(gCalcMatrix, &sp64, &sp58);

            Math_SmoothStepToF(&player->cam.at.x, player->pos.x + sp58.x, D_ctx_80177A48[3], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.y, player->pos.y + sp58.y, D_ctx_80177A48[3], 500.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.at.z, player->pos.z + sp58.z, D_ctx_80177A48[3], 500.0f, 0.0f);

            D_ctx_80177A48[5] += D_ctx_80177A48[4];

            if ((gCsFrameCount > 400) && (gCsFrameCount < 1000)) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 0.5f, 1.0f, 0.003f, 0);
            }
            if (gCsFrameCount > 1100) {
                Math_SmoothStepToF(&D_ctx_80177A48[4], 0.0f, 1.0f, 0.003f, 0);
            }
            if (gCsFrameCount == 1270) {
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 50);
                SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 50);
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
                player->csState++;
                player->baseSpeed = 2.0f;
                player->unk_194 = 5.0f;
                player->unk_190 = 5.0f;
            }
            break;

        case 4:
            if (gCsFrameCount >= 1270) {
                player->baseSpeed *= 1.2f;
                player->contrailScale += 0.04f;
                if (player->contrailScale > 0.6f) {
                    player->contrailScale = 0.6f;
                }
                player->unk_190 = 2.0f;
            }

            if (gCsFrameCount == 1290) {
                Audio_FadeOutAll(50);
            }

            if (gCsFrameCount > 1300) {
                gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaStep = 8;

                if (gFillScreenAlpha == 255) {
                    player->state_1C8 = PLAYERSTATE_1C8_NEXT;
                    player->csTimer = 0;
                    gFadeoutType = 4;
                    gLeveLClearStatus[gCurrentLevel] = Play_CheckMedalStatus(150) + 1;
                }
            }
            break;
    }

    switch (gCsFrameCount) {
        case 981:
            gShowLevelClearStatusScreen = 1;
            break;

        case 1181:
            gShowLevelClearStatusScreen = 0;
            break;

        case 240:
            AUDIO_PLAY_BGM(NA_BGM_COURSE_CLEAR);
            break;

        case 330:
            gLevelClearScreenTimer = 100;
            break;

        case 470:
            Play_ClearObjectData();
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                Corneria_80190F74(&gActors[0], 0);
            }
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                Corneria_80190F74(&gActors[1], 1);
            }
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                Corneria_80190F74(&gActors[2], 2);
            }
            break;

        case 410:
            Radio_PlayMessage(gMsg_ID_2335, RCID_FOX);
            break;

        case 550:
            if ((gTeamShields[TEAM_ID_SLIPPY] == -1) || (gTeamShields[TEAM_ID_SLIPPY] == 0)) {
                Radio_PlayMessage(gMsg_ID_20333, RCID_ROB64);
            } else {
                Radio_PlayMessage(gMsg_ID_2300, RCID_SLIPPY);
            }
            break;

        case 682:
            if ((gTeamShields[TEAM_ID_PEPPY] == -1) || (gTeamShields[TEAM_ID_PEPPY] == 0)) {
                Radio_PlayMessage(gMsg_ID_20332, RCID_ROB64);
            } else {
                Radio_PlayMessage(gMsg_ID_2310, RCID_PEPPY);
            }
            break;

        case 816:
            if ((gTeamShields[TEAM_ID_FALCO] == -1) || (gTeamShields[TEAM_ID_FALCO] == 0)) {
                Radio_PlayMessage(gMsg_ID_20331, RCID_ROB64);
            } else {
                Radio_PlayMessage(gMsg_ID_2320, RCID_FALCO);
            }
            break;

        case 1150:
            if (gTeamShields[TEAM_ID_FALCO] > 0) {
                gActors[0].state = 1;
                gActors[0].fwork[9] = 2.0f;
                gActors[0].timer_0BC = 50;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[0].sfxSource, 0);
                gActors[0].fwork[29] = 5.0f;
            }
            break;

        case 1190:
            if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                gActors[1].state = 1;
                gActors[1].fwork[9] = 2.0f;
                gActors[1].timer_0BC = 50;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[1].sfxSource, 0);
                gActors[1].fwork[29] = 5.0f;
            }
            break;

        case 1230:
            if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                gActors[2].state = 1;
                gActors[2].fwork[9] = 2.0f;
                gActors[2].timer_0BC = 50;
                AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, gActors[2].sfxSource, 0);
                gActors[2].fwork[29] = 5.0f;
            }
            break;
    }

    Matrix_RotateY(gCalcMatrix, (player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -((player->rot.x + player->aerobaticPitch) * M_DTOR), MTXF_APPLY);

    sp64.x = 0.0f;
    sp64.y = 0.0f;
    sp64.z = player->baseSpeed + player->boostSpeed;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp64, &sp58);

    player->vel.x = sp58.x;
    player->vel.z = sp58.z;
    player->vel.y = sp58.y;

    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;

    player->trueZpos = player->pos.z;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    player->bobPhase += 10.0f;
    player->yBob = -SIN_DEG(player->bobPhase) * 0.3f;
    player->rockPhase += 8.0f;
    player->rockAngle = SIN_DEG(player->rockPhase);
}
