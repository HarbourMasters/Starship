
// #include "prevent_bss_reordering.h"
#include "global.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_andross.h"
#include "assets/ast_arwing.h"
#include "assets/ast_bg_planet.h"
#include "prevent_bss_reordering.h"
#include "prevent_bss_reordering2.h"
f32 D_i6_801A7F5C;
f32 D_i6_801A7F64;
f32 D_i6_801A7F6C;
f32 D_i6_801A7F74;
f32 D_i6_801A7F7C;
Vec3f D_i6_801A7F80[100];
f32 D_i6_801A8430;

f32 D_Andross_801A7F58;
f32 D_Andross_801A7F60;
f32 D_Andross_801A7F68;
f32 D_Andross_801A7F70;
f32 D_Andross_801A7F78;

static f32* D_i6_801A6760[12] = {
    D_ANDROSS_C037FCC, D_ANDROSS_C0380C0, D_ANDROSS_C0381B4, D_ANDROSS_C0382A8, D_ANDROSS_C03839C, D_ANDROSS_C038490,
    D_ANDROSS_C038584, D_ANDROSS_C038678, D_ANDROSS_C03876C, D_ANDROSS_C038860, D_ANDROSS_C038954, D_ANDROSS_C038954,
};

void Andross_80193710(void);

void Andross_80187530(Actor* actor) {
    s32 index;

    switch (actor->unk_048) {
        case 0:
            break;
        case 1:
            actor->unk_0B6 += (s32) actor->fwork[22];
            if (actor->unk_0B6 >= Animation_GetFrameCount(&D_VE2_6014658)) {
                actor->unk_0B6 = Animation_GetFrameCount(&D_VE2_6014658) - 1;
            }
            break;
        case 2:
            actor->unk_0B6 -= (s32) actor->fwork[22];
            if (actor->unk_0B6 <= 0) {
                actor->unk_0B6 = 0;
            }
            break;
        default:
            break;
    }

    index = actor->unk_0B6 / 18.0f;
    actor->info.hitbox = LOAD_ASSET(D_i6_801A6760[index]);
    actor->obj.rot.z = D_Andross_801A7F68;
}

bool Andross_8018767C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex == 13) {
        *dList = NULL;
    }
    return 0;
}

void Andross_8018769C(Actor* actor) {
    Vec3f sp28[20];

    Animation_GetFrameData(&D_VE2_6014658, actor->unk_0B6, sp28);
    Animation_DrawSkeleton(1, D_VE2_6014844, sp28, Andross_8018767C, NULL, NULL, &gIdentityMatrix);
}

void Andross_801876FC(void) {
    s32 temp_ft3;
    s32* var_s0;
    s32* var_s3;
    s32 i;
    s32 j;

    var_s0 = LOAD_ASSET(&D_ANDROSS_C039290);
    var_s3 = LOAD_ASSET(&D_ANDROSS_C03A290);

    for (i = 0; i < 32 * 32; i += 32) {
        temp_ft3 = 4.0f * __sinf((s32) (((i / 32) + (gGameFrameCount / 2)) % 32U) * (2 * M_PI / 32));

        for (j = 0; j < 32; j++) {
            var_s0[i + ((temp_ft3 + j) % 32U)] = var_s3[i + j];
        }
    }
}

void Andross_801878A8() {
    Actor* actor;
    Item* item;
    Object_58* obj58;
    s32 i;

    gLevelObjects = LOAD_ASSET(&D_ANDROSS_C0356CC);

    for (obj58 = gObjects58, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if (gLevelObjects[i].id <= OBJ_80_160) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[i].id;
            obj58->obj.pos.x = gLevelObjects[i].xPos;
            obj58->obj.pos.z = -gLevelObjects[i].zPos1;
            obj58->obj.pos.z += gLevelObjects[i].zPos2;
            obj58->obj.pos.y = gLevelObjects[i].yPos;
            obj58->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&obj58->info, obj58->obj.id);
            if (obj58->obj.id == OBJ_80_131) {
                obj58->info.hitbox = LOAD_ASSET(&D_ANDROSS_C038CCC);
            }
            obj58++;
        }
    }

    for (actor = &gActors[1], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if ((gLevelObjects[i].id <= OBJ_ACTOR_SUPPLIES) && (gLevelObjects[i].id >= OBJ_ACTOR_176)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_ACTIVE;
            actor->obj.id = gLevelObjects[i].id;
            actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->obj.pos.z += gLevelObjects[i].zPos2;
            actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }

    for (item = gItems, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if ((gLevelObjects[i].id <= OBJ_ITEM_TRAINING_RING) && (gLevelObjects[i].id >= OBJ_ITEM_LASERS)) {
            Item_Initialize(item);
            item->obj.status = OBJ_ACTIVE;
            item->obj.id = gLevelObjects[i].id;
            item->obj.pos.x = gLevelObjects[i].xPos;
            item->obj.pos.z = -gLevelObjects[i].zPos1;
            item->obj.pos.z += gLevelObjects[i].zPos2;
            item->obj.pos.y = gLevelObjects[i].yPos;
            Object_SetInfo(&item->info, item->obj.id);
            item++;
        }
    }
}

void Andross_80187C5C(void) {
    Actor* actor;
    Item* item;
    Object_58* obj58;
    s32 i;

    switch (RAND_INT(2.9f)) {
        case 0:
            gLevelObjects = LOAD_ASSET(&D_ANDROSS_C036310);
            break;
        case 1:
            gLevelObjects = LOAD_ASSET(&D_ANDROSS_C036B6C);
            break;
        default:
        case 2:
            gLevelObjects = LOAD_ASSET(&D_ANDROSS_C03733C);
            break;
    }

    for (obj58 = gObjects58, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if (gLevelObjects[i].id <= OBJ_80_160) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[i].id;
            obj58->obj.pos.x = gLevelObjects[i].xPos;
            obj58->obj.pos.z = -gLevelObjects[i].zPos1;
            obj58->obj.pos.z += gLevelObjects[i].zPos2;
            obj58->obj.pos.y = gLevelObjects[i].yPos;
            obj58->obj.rot.y = gLevelObjects[i].rot.y;
            if (obj58->obj.id == OBJ_80_147) {
                obj58->unk_40 = gLevelObjects[i].rot.z;
            }
            Object_SetInfo(&obj58->info, obj58->obj.id);
            if (obj58->obj.id == OBJ_80_131) {
                obj58->info.hitbox = LOAD_ASSET(&D_ANDROSS_C038CCC);
            }
            obj58++;
        }
    }

    for (actor = &gActors[1], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if ((gLevelObjects[i].id <= OBJ_ACTOR_SUPPLIES) && (gLevelObjects[i].id >= OBJ_ACTOR_176)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_ACTIVE;
            actor->obj.id = gLevelObjects[i].id;
            actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->obj.pos.z += gLevelObjects[i].zPos2;
            actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }

    for (item = gItems, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }
        if ((gLevelObjects[i].id <= OBJ_ITEM_TRAINING_RING) && (gLevelObjects[i].id >= OBJ_ITEM_LASERS)) {
            Item_Initialize(item);
            item->obj.status = OBJ_ACTIVE;
            item->obj.id = gLevelObjects[i].id;
            item->obj.pos.x = gLevelObjects[i].xPos;
            item->obj.pos.z = -gLevelObjects[i].zPos1;
            item->obj.pos.z += gLevelObjects[i].zPos2;
            item->obj.pos.y = gLevelObjects[i].yPos;
            Object_SetInfo(&item->info, item->obj.id);
            item++;
        }
    }
}

void Andross_801880E4(Actor* actor) {
    s32 i;
    f32 xDisplacement;
    f32 yDisplacement;
    f32 zDisplacement;
    Object_58* obj58;
    f32 yaw;
    f32 var_fv0;
    Vec3f sp48;
    Vec3f vel;
    f32 temp_fv1;

    for (obj58 = gObjects58, i = 0; i < 200; i++, obj58++) {
        if ((obj58->obj.id == OBJ_80_147) && (obj58->unk_40 == (u8) actor->unk_04E)) {
            actor->fwork[3] = obj58->obj.pos.x;
            actor->fwork[4] = obj58->obj.pos.y;
            actor->fwork[5] = obj58->obj.pos.z;
            break;
        }
    }
    actor->fwork[2] = 3.0f;
    xDisplacement = actor->fwork[3] - actor->obj.pos.x;
    yDisplacement = actor->fwork[4] - actor->obj.pos.y;
    zDisplacement = actor->fwork[5] - actor->obj.pos.z;
    if ((fabsf(xDisplacement) < 300.0f) && (fabsf(yDisplacement) < 300.0f) && (fabsf(zDisplacement) < 300.0f)) {
        actor->unk_04E++;
    }
    if (((gGameFrameCount % 32) == 0)) {
        actor->iwork[11] = 1;
        actor->fwork[1] = 47.0f;
        if ((fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 1000.0f) &&
            (fabsf(actor->obj.pos.y - gPlayer[0].pos.y) < 500.0f) &&
            (fabsf(actor->obj.pos.z - gPlayer[0].unk_138) < 1000.0f)) {
            actor->iwork[11] = 2;
            actor->fwork[1] = 65.0f;
        }
    }

    Math_SmoothStepToF(&actor->fwork[0], actor->fwork[1], 0.2f, 3.0f, 0.00001f);
    yaw = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
    Math_SmoothStepToAngle(&actor->unk_0F4.x,
                           Math_RadToDeg(Math_Atan2F(yDisplacement, sqrtf(SQ(xDisplacement) + SQ(zDisplacement)))),
                           0.1f, actor->fwork[2], 0.0f);
    temp_fv1 = Math_SmoothStepToAngle(&actor->unk_0F4.y, yaw, 0.1f, actor->fwork[2], 0.0001f) * 40.0f;
    if (temp_fv1 < 0.0f) {
        var_fv0 = temp_fv1 * -1.0f;
    } else {
        var_fv0 = 360.0f - temp_fv1;
    }
    Math_SmoothStepToAngle(&actor->obj.rot.z, var_fv0, 0.1f, 3.0f, 0.01f);

    actor->obj.rot.y = actor->unk_0F4.y;
    actor->obj.rot.x = -actor->unk_0F4.x;
    Matrix_RotateY(gCalcMatrix, actor->unk_0F4.y * M_DTOR, 0);
    Matrix_RotateX(gCalcMatrix, -actor->unk_0F4.x * M_DTOR, 1);
    sp48.x = 0;
    sp48.y = 0;
    sp48.z = actor->fwork[0];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp48, &vel);
    actor->vel.x = vel.x;
    actor->vel.y = vel.y;
    actor->vel.z = vel.z;
}

void Andross_80188448(Actor* actor) {
    func_edisplay_8005B388(actor);
}

void Andross_80188468(void) {
    Actor* actor = &gActors[0];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.pos.x = -23180.0f;
    actor->obj.pos.y = 300.0f;
    actor->obj.pos.z = -11959.0f;
    actor->iwork[11] = 1;
    actor->iwork[14] = 1;
    actor->obj.id = OBJ_ACTOR_199;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
}

void Andross_80188528(Actor* actor) {
    Math_SmoothStepToF(&actor->vel.x, 0.0f, 0.2f, 0.5f, 0.0f);
    Math_SmoothStepToF(&actor->vel.y, 0.0f, 0.2f, 0.5f, 0.0f);
    Math_SmoothStepToF(&actor->vel.z, 0.0f, 0.2f, 0.5f, 0.0f);
    if (actor->unk_0D0 != 0) {
        func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
        Object_Kill(&actor->obj, actor->sfxSource);
        func_effect_8007B344(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 3.0f, 5);
    } else if (actor->timer_0BC == 0) {
        Object_Kill(&actor->obj, actor->sfxSource);
    }
    actor->obj.rot.y = RAD_TO_DEG(-gPlayer[0].unk_058);
    actor->obj.rot.x = RAD_TO_DEG(gPlayer[0].unk_05C);
    actor->unk_0F4.z += actor->fwork[0];
}

void Andross_80188660(Actor* actor) {
    RCP_SetupDL(&gMasterDisp, 0x3D);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    Matrix_RotateZ(gGfxMatrix, actor->unk_0F4.z * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, 1.1f, 0.9f, 1.0f, 1);
    Matrix_RotateZ(gGfxMatrix, -actor->unk_0F4.z * M_DTOR, 1);
    Matrix_Scale(gGfxMatrix, 1.1f, 0.9f, 1.0f, 1);
    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 1.0f, 1);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, D_VE2_6009300);
}

void Andross_801887B0(Actor* actor, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_286;
    actor->vel.x = xVel;
    actor->vel.y = yVel;
    actor->vel.z = zVel;
    actor->obj.pos.x = xPos;
    actor->obj.pos.y = yPos;
    actor->obj.pos.z = zPos;
    if (Rand_ZeroOne() < 0.5f) {
        actor->fwork[0] = 10.0f;
    } else {
        actor->fwork[0] = -10.0f;
    }
    actor->timer_0BC = 300;
    Object_SetInfo(&actor->info, actor->obj.id);
}

void Andross_8018887C(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Andross_801887B0(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

void Andross_801888F4(Actor* actor) {
    s32 i;

    actor->obj.rot.z -= 8.0f;
    if ((actor->timer_0BC % 2U) == 1) {
        func_effect_8007D2C8(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 5.0f);
    }
    if ((actor->timer_0BC == 0) || (actor->unk_0D0 != 0)) {
        func_effect_8007BFFC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, actor->vel.x, actor->vel.y,
                             actor->vel.z, 7.0f, 20);
        func_effect_8007B344(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 10.0f, 5);

        for (i = 0; i < 6; i++) {
            func_effect_800794CC(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 1.0f);
        }

        func_effect_8007A6F0(&actor->obj.pos, 0x2903B009);
        Object_Kill(&actor->obj, actor->sfxSource);
        BonusText_Display(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 5);
        gHitCount += 6;
        D_ctx_80177850 = 15;
    }
}

void Andross_80188A4C(Boss* boss) {

    if (boss->damage > 20) {
        boss->damage = 20;
    }
    if (boss->dmgType != DMG_NONE) {
        boss->dmgType = DMG_NONE;
        if (boss->state < 10 && !(boss->fwork[21] < 250.0f)) {
            switch (boss->dmgPart) {
                case 0:
                    boss->swork[1] = 15;
                    boss->swork[7] = 30;
                    break;
                case 1:
                case 2:
                    if (boss->swork[4] == 0) {
                        boss->swork[2] = 10;
                        boss->swork[3] = 15;
                        AUDIO_PLAY_SFX(0x2943500FU, boss->sfxSource, 4);
                        boss->health -= boss->damage;
                        if ((boss->health != 0) && (boss->health <= 0)) {
                            gScreenFlashTimer = 8;
                            AUDIO_PLAY_SFX(0x2940D09AU, boss->sfxSource, 4);
                            func_boss_80042EC0(boss);
                            gPlayer[0].state_1C8 = PLAYERSTATE_1C8_0;
                            boss->state = 20;
                            boss->swork[1] = 1000;
                            boss->swork[2] = 1000;
                            boss->swork[6] = 1;
                            D_ctx_80177A48[0] = 0.0f;
                            D_ctx_80177A48[1] = 0.1f;
                            gCsFrameCount = 0;
                            Audio_KillSfxBySourceAndId(boss->sfxSource, 0x11034074U);
                            Audio_KillSfxBySourceAndId(boss->sfxSource, 0x31408097U);
                            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                        }
                    }
                    break;
                default:
                    if (boss->swork[4] == 0) {
                        boss->swork[8]++;
                        if (boss->swork[8] >= 6) {
                            boss->swork[8] = 0;
                            boss->state = 12;
                            boss->timer_050 = 50;
                            boss->fwork[3] = gPlayer[0].pos.x;
                            boss->fwork[5] = gPlayer[0].unk_138;
                            AUDIO_PLAY_SFX(0x2940B096U, boss->sfxSource, 4);
                        }
                    }
                    break;
            }
        }
    }
}

void Andross_80188CB8(Boss* boss) {
    s32 i;
    Vec3f sp50;
    Vec3f sp44;

    boss->unk_04C++;
    if (boss->unk_04C >= Animation_GetFrameCount(&D_VE2_600C038)) {
        boss->unk_04C = 0;
    }
    Animation_GetFrameData(&D_VE2_600C038, boss->unk_04C, boss->vwork);

    if (boss->swork[3] != 0) {
        boss->swork[3]--;
    }

    if (boss->swork[2] != 0) {
        boss->swork[2]--;
        Math_SmoothStepToF(&boss->fwork[15], -15.0f, 0.8f, 5.0f, 0.0f);
        Math_SmoothStepToF(&boss->fwork[16], 0.05f, 0.8f, 0.02f, 0.0f);
    } else {
        Math_SmoothStepToF(&boss->fwork[15], 4.0f, 0.05f, 0.2f, 0.0f);
        Math_SmoothStepToF(&boss->fwork[16], 0.03f, 0.05f, 0.001f, 0.0f);
    }
    Math_SmoothStepToF(&boss->fwork[10], boss->fwork[11], boss->fwork[12], boss->fwork[13], 0.0f);
    if (boss->swork[1] != 0) {
        boss->swork[1]--;
        boss->fwork[11] = 30.0f;
        boss->fwork[12] = 0.8f;
        boss->fwork[13] = 3.0f;
    } else {
        boss->fwork[11] = 8.0f;
        boss->fwork[12] = 0.05f;
        boss->fwork[13] = 0.5f;
    }

    if (boss->swork[7] != 0) {
        boss->swork[7]--;
        if (((gGameFrameCount % 2) == 0)) {
            Andross_8018887C(RAND_FLOAT_CENTERED(100.0f) + boss->obj.pos.x,
                             RAND_FLOAT_CENTERED(300.0f) + (boss->obj.pos.y - 250.0f),
                             RAND_FLOAT_CENTERED(100.0f) + boss->obj.pos.z, RAND_FLOAT_CENTERED(50.0f),
                             RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(50.0f));
        }
    }
    boss->fwork[14] += boss->fwork[15];
    Matrix_RotateY(gCalcMatrix, -gPlayer[0].unk_058, 0);
    sp50.x = boss->vel.z * 0.25f;
    sp50.y = 0.0f;
    sp50.z = boss->vel.x * 0.25f;
    Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);
    boss->fwork[18] = -sp44.z;
    boss->fwork[17] = sp44.x;
    boss->swork[4] = 0;
    boss->fwork[19] = -26.0f;

    for (i = 10; i < 12; i++) {
        if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_ALLRANGE)) {
            gTexturedLines[i].mode = 50;
            gTexturedLines[i].unk_28 = 1.0f;
            gTexturedLines[i].unk_04.x = boss->obj.pos.x;
            gTexturedLines[i].unk_04.y = boss->obj.pos.y - 200.0f;
            gTexturedLines[i].unk_04.z = boss->obj.pos.z;
            gTexturedLines[i].timer = 3;
            gTexturedLines[i].unk_10.x = gActors[i].obj.pos.x;
            gTexturedLines[i].unk_10.y = gActors[i].obj.pos.y;
            gTexturedLines[i].unk_10.z = gActors[i].obj.pos.z;
            boss->swork[4] = 1;
        }
    }
}

void Andross_80189098(Boss* boss) {
    Actor* actor = &gActors[10];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = AI360_10;
    actor->aiIndex = AI360_FOX;
    actor->health = 200;
    actor->obj.pos.x = 200.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = boss->obj.pos.z;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.hitbox = LOAD_ASSET(&gDefaultCubeHitbox150);

    actor++;

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = AI360_10;
    actor->aiIndex = AI360_FOX;
    actor->health = 200;
    actor->obj.pos.x = -200.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = boss->obj.pos.z;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.hitbox = LOAD_ASSET(&gDefaultCubeHitbox150);

    gActors[0].state = 2;
}

void Andross_80189214(void) {
    s32 i;
    Player* player = &gPlayer[0];

    func_play_800A6148();

    for (i = 0; i < 200; i++) {
        gObjects58[i].obj.status = OBJ_FREE;
    }

    gLevelMode = LEVELMODE_ON_RAILS;
    player->unk_204 = 0;
    gPlayer[0].pos.x = 0.0f;
    player->camEye.z = 400.0f;
    player->camAt.z = player->camEye.z - 1000.0f;
    player->unk_148 = player->unk_14C = 0.74f;
    player->camEye.y = player->pos.y * player->unk_14C + 10.0f;
    player->camEye.x = player->pos.x * player->unk_148;
    D_ctx_80177DC8 = 0;
    // FAKE
    if (1) {}
    PRINTF("FO_Game_Sw %d\n");
    player->camAt.x = 0.0f;
    player->camAt.y = 0.0f;
    player->unk_114 = 0.0f;
    player->unk_144 = 0.0f;
    D_ctx_80177D20 = 0.0f;
    player->unk_018 = player->unk_014 = 1.0f;
    player->pos.z = player->unk_138 = -player->unk_144;
    func_play_800B56BC(player);
}

void Andross_8018933C(Actor* actor) {
    if ((fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 1000.0f) &&
        (fabsf(actor->obj.pos.z - gPlayer[0].unk_138) < 1000.0f)) {
        D_Timer_80177B44 = 50;
        Object_Kill(&actor->obj, actor->sfxSource);
    }
}

void Andross_801893B8(Actor* actor) {

    if (gAllRangeCheckpoint == 0) {
        actor->unk_04E++;
        switch (actor->unk_04E) {
            case 200:
                Radio_PlayMessage(gMsg_ID_8250, RCID_ANDROSS_RED);
                return;
            case 400:
                Radio_PlayMessage(gMsg_ID_8255, RCID_ANDROSS_RED);
                return;
            case 600:
                Radio_PlayMessage(gMsg_ID_8260, RCID_ANDROSS_RED);
                return;
            case 800:
                Radio_PlayMessage(gMsg_ID_19325, RCID_ANDROSS_RED);
                break;
        }
    }
}

void Andross_80189470(Actor* actor) {
    s32 i;
    Player* player = &gPlayer[0];

    if ((D_ctx_80177AB0 != 7) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) &&
        (fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 9000.0f) &&
        (fabsf(actor->obj.pos.z - gPlayer[0].unk_138) < 9000.0f)) {
        D_ctx_80177AB0 = 7;
        Radio_PlayMessage(gMsg_ID_19370, RCID_JAMES);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 20);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 20);
    }

    if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) && (fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 500.0f) &&
        (fabsf(actor->obj.pos.z - gPlayer[0].unk_138) < 500.0f)) {
        Audio_KillSfxById(0x11403076);
        Audio_SetBaseSfxReverb(0);
        gCurrentLevel = LEVEL_VENOM_2;
        gLevelStage = 1;
        D_play_800D2F68 = 1;
        player->state_1C8 = PLAYERSTATE_1C8_7;
        player->unk_1D0 = 3;
        player->unk_144 = D_ctx_80177D20 = 0.0f;
        D_ctx_80177AB0 = D_ctx_80177A98 = 1;
        player->camEye.x = 1200.0f;
        player->camEye.z = 1200.0f;
        player->camEye.y = 1800.0f;
        gCsCamAtX = 0.0f;
        gCsCamAtY = 620.0f;
        gCsCamAtZ = 0.0f;
        player->unk_234 = 0;
        player->unk_034 = 0.0f;
        D_ctx_80177A48[0] = 1.0f;
        func_play_800A6148();

        for (i = 0; i < 200; i++) {
            gObjects58[i].obj.status = OBJ_FREE;
        }

        Andross_80193710();
        D_ctx_8017782C = 1;
        func_play_800A594C();
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
        player->timer_1F8 = 2;
        gCsFrameCount = 0;
        D_ctx_80177A48[1] = 0.0f;
    }
}

void Andross_80189724(Actor* actor) {
    s32 i;
    Vec3f vec;
    Vec3f displacement;
    Vec3f vel;

    if ((fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 2000.0f) &&
        (fabsf(actor->obj.pos.z - gPlayer[0].unk_138) < 2000.0f)) {
        Matrix_RotateY(gCalcMatrix, actor->obj.rot.y * M_DTOR, 0);
        vec.x = 0.0f;
        vec.y = 0.0f;
        vec.z = -30.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &vel);
        Matrix_RotateZ(gCalcMatrix, 2.0f * RAND_FLOAT(M_PI), 1);
        vec.x = RAND_FLOAT(300.0f);
        vec.y = 0.0f;
        vec.z = 0.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &displacement);

        actor->vel.x = vel.x * 0.2f;
        actor->vel.y = vel.y * 0.2f;
        actor->vel.z = vel.z * 0.2f;
        for (i = 0; i < 1; i++) {
            func_effect_8007797C(actor->obj.pos.x + displacement.x, actor->obj.pos.y + displacement.y,
                                 actor->obj.pos.z + displacement.z, vel.x, vel.y, vel.z, RAND_FLOAT(2.5f) + 15.5f);
        }
    }
    if ((fabsf(actor->obj.pos.x - gPlayer[0].pos.x) < 500.0f) &&
        (fabsf(actor->obj.pos.z - gPlayer[0].unk_138) < 500.0f)) {
        if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3 || gPlayer[0].state_1C8 == PLAYERSTATE_1C8_5)) {
            gPlayer[0].shields = 0;
            gRightWingHealth[0] = gLeftWingHealth[0] = 0;
            Player_ApplyDamage(&gPlayer[0], 1, 60);
            Player_ApplyDamage(&gPlayer[0], 2, 60);
            actor->timer_0BC = 10;
            gPlayer[0].timer_220 = 200;
        }
    }
    if (actor->timer_0BC == 1) {
        func_demo_8004D440(&gPlayer[0]);
    }
}

void Andross_801899E4(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 scale2, u8 arg5) {

    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_357;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->unk_4C = arg5;
    effect->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale2;
    effect->timer_50 = 100;
    effect->obj.rot.x = RAND_FLOAT(360.0f);
    effect->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
    effect->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
    effect->unk_60.z = RAND_FLOAT_CENTERED(30.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Andross_80189B00(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_801899E4(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

void Andross_80189B70(Boss* boss) {
    s32 i;
    s32 sp98;
    s32 frameCountMask;
    f32 xDisplacement;
    f32 yDisplacement;
    f32 zDisplacement;
    s32 pad84;
    f32 yaw;
    s32 pad7C;
    Vec3f vec;
    Vec3f sp64;
    Vec3f sp58;
    s32 pad;

    Andross_80188A4C(boss);
    Andross_80188CB8(boss);
    boss->info.hitbox = LOAD_ASSET(&D_ANDROSS_C038F24);
    Math_SmoothStepToF(&D_bg_800C9C30, 255.0f, 1.0f, 4.0f, 0);
    Math_SmoothStepToF(&boss->unk_3F8, 10.0f, 0.2f, 0.2f, 0);
    if (!(gGameFrameCount & 0x10)) {
        Math_SmoothStepToF(&boss->fwork[25], 255.0f, 1.0f, 10.0f, 0);
    } else {
        Math_SmoothStepToF(&boss->fwork[25], 100.0f, 1.0f, 10.0f, 0);
    }
    if ((fabsf(boss->obj.pos.x - gPlayer[0].pos.x) < 300.0f) &&
        (fabsf((boss->obj.pos.y - 300.0f) - gPlayer[0].pos.y) < 300.0f) &&
        (fabsf(boss->obj.pos.z - gPlayer[0].unk_138) < 300.0f) && (boss->state < 11) && (boss->timer_05A == 0)) {
        boss->state = 11;
        boss->timer_050 = 150;
        AUDIO_PLAY_SFX(0x31408097, boss->sfxSource, 4);
    }

    switch (boss->state) {
        case 0:
            boss->health = 200;
            D_ctx_80177AB0 = 3;
            boss->fwork[19] = -26.0f;
            boss->fwork[10] = 8.0f;
            Andross_80189098(boss);
            boss->swork[5] = 300;
            boss->state++;
            AUDIO_PLAY_SFX(0x11034074, boss->sfxSource, 4);
            boss->fwork[21] = 255.0f;
            boss->fwork[22] = 255.0f;
            boss->fwork[23] = 0.0f;
            boss->fwork[24] = 0.0f;
            break;
        case 10:
            boss->fwork[23] = 0.0f;
            boss->fwork[24] = 0.0f;
            boss->fwork[21] = 255.0f;
            boss->fwork[22] = 255.0f;
            boss->fwork[1] = 10.0f;
            boss->fwork[2] = 2.0f;
            boss->fwork[3] = 0.0f;
            boss->fwork[4] = 0.0f;
            boss->fwork[5] = gPlayer[0].pos.z - 3000.0f;
            boss->fwork[19] = -26.0f;
            boss->swork[5] = 100;
            if (boss->timer_050 == 0) {
                gPlayer[0].state_1C8 = PLAYERSTATE_1C8_9;
                gPlayer[0].unk_1D0 = 0;
                boss->state = 1;
                gPlayer[0].unk_240 = 1;
            }
            break;
        case 1:
            if ((gPlayer[0].state_1C8 != PLAYERSTATE_1C8_9) && (boss->timer_050 == 0)) {
                boss->fwork[2] = 1.6f;
                boss->timer_050 = RAND_INT(1.0f) * 50.0f + 50;
                boss->fwork[3] = RAND_FLOAT_CENTERED(10000.0f);
                boss->fwork[4] = RAND_FLOAT_CENTERED(1000.0f);
                boss->fwork[5] = RAND_FLOAT_CENTERED(10000.0f);
                if (Rand_ZeroOne() < 0.3f) {
                    boss->state = 2;
                    boss->timer_050 = RAND_INT(1.0f) * 100.0f + 50;
                    boss->fwork[1] = 0.0f;
                }
            }
            break;
        case 2:
            if (boss->timer_050 == 0) {
                boss->state = 1;
                boss->timer_050 = RAND_INT(1.0f) * 50.0f + 50;
                boss->fwork[1] = 50.0f;
            }
            break;
        case 11:
            boss->info.hitbox = LOAD_ASSET(&gHitboxNone);
            if (boss->timer_050 < 120) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 80;
                gFillScreenAlphaStep = 1;
                gPlayer[0].timer_224 = gGameFrameCount % 8U;
                gPlayer[0].timer_220 = 3;
                Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 40.0f, 1.0f, 3.0f, 0.0f);
                if (((gGameFrameCount % 32) == 0) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3)) {
                    Player_ApplyDamage(&gPlayer[0], 3, 10);
                }
            }
            Math_SmoothStepToF(&gPlayer[0].unk_0D0, 0.0f, 2.0f, 2.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].pos.x, boss->obj.pos.x, 0.8f, 50.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].pos.y, boss->obj.pos.y - 300.0f, 0.8f, 50.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].pos.z, boss->obj.pos.z, 0.8f, 50.0f, 0.0f);
            boss->fwork[11] = 45.0f;
            boss->fwork[12] = 0.8f;
            boss->fwork[13] = 1.0f;
            boss->fwork[19] = 23.0f;
            boss->fwork[1] = 0.0f;
            gPlayer[0].cockpitView = 1;
            Math_SmoothStepToF(&D_display_800CA230, 0.15f, 0.2f, 0.004f, 0.0f);
            if (boss->timer_050 == 120) {
                AUDIO_PLAY_SFX(0x1940306E, boss->sfxSource, 4);
            }
            if (boss->timer_050 == 0) {
                gPlayer[0].unk_0D0 = D_play_80161A54;
                gPlayer[0].cockpitView = 0;
                gFillScreenAlphaTarget = 0;
                boss->timer_05A = 50;
                if (boss->swork[4] != 0) {
                    boss->state = 1;
                    boss->timer_050 = RAND_INT(1.0f) * 50.0f + 50;
                    boss->fwork[1] = 50.0f;
                } else {
                    boss->state = 3;
                }
                Audio_KillSfxBySourceAndId(boss->sfxSource, 0x31408097);
            }
            break;
        case 3:
            boss->fwork[1] = 42.0f;
            boss->fwork[2] = 1.3f;
            boss->fwork[3] = gPlayer[0].pos.x;
            boss->fwork[4] = gPlayer[0].pos.y;
            boss->fwork[5] = gPlayer[0].unk_138;
            break;
        case 12:
            boss->info.hitbox = LOAD_ASSET(&gHitboxNone);
            boss->fwork[1] = 0;
            boss->fwork[24] = 0.2f;
            boss->fwork[22] = 0.0f;
            if ((boss->fwork[22] < 1.0f) && (boss->timer_050 == 0)) {
                xDisplacement = boss->fwork[3] - boss->obj.pos.x;
                zDisplacement = boss->fwork[5] - boss->obj.pos.z;
                Matrix_RotateY(gCalcMatrix, Math_Atan2F(xDisplacement, zDisplacement), 0);
                vec.x = 0.0f;
                vec.y = 0.0f;
                vec.z = 4000.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);
                boss->obj.pos.x = boss->fwork[3] + sp64.x;
                boss->obj.pos.z = boss->fwork[5] + sp64.z;
                boss->unk_078.y = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
                boss->state = 13;
                AUDIO_PLAY_SFX(0x1940306E, boss->sfxSource, 4);
                boss->timer_054 = 90;
            }
            break;
        case 13:
            boss->info.hitbox = LOAD_ASSET(&gHitboxNone);
            boss->fwork[24] = 0.0f;
            boss->fwork[22] = 255.0f;
            if (250.0f < boss->fwork[22]) {
                boss->state = 3;
            }
            break;
        case 20:
            gCsFrameCount++;
            boss->fwork[0] = 0.0f;
            boss->fwork[1] = 0.0f;
            boss->obj.rot.z += 0.2f;
            boss->obj.rot.x += 0.1f;
            boss->obj.pos.y -= 3.0f;
            Matrix_RotateY(gCalcMatrix, -gPlayer[0].unk_058, 0U);
            vec.x = RAND_FLOAT_CENTERED(700.0f);
            vec.y = RAND_FLOAT_CENTERED(300.0f);
            vec.z = 500.0f;
            Matrix_MultVec3f(gCalcMatrix, &vec, &sp64);
            func_effect_8007797C(boss->obj.pos.x + sp64.x, boss->obj.pos.y + sp64.y, boss->obj.pos.z + sp64.z, 0.0f,
                                 0.0f, 0.0f, RAND_FLOAT(5.0f) + 7.0f);
            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007C484(RAND_FLOAT_CENTERED(600.0f) + boss->obj.pos.x,
                                     RAND_FLOAT(100.0f) + (boss->obj.pos.y + 100.0f), boss->obj.pos.z, 0.0f, 0.0f, 0.0f,
                                     RAND_FLOAT(0.3f) + 0.5f, 0);
            }
            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = 2000.0f;
            Matrix_MultVec3f(gCalcMatrix, &vec, &sp64);
            Math_SmoothStepToF(&D_ctx_80177A48[0], 100.0f, 1.0f, 2.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[1], 100.0f, 1.0f, 10.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].camEye.x, boss->obj.pos.x + sp64.x, 0.02f, D_ctx_80177A48[0], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].camEye.y, boss->obj.pos.y + sp64.y, 0.02f, D_ctx_80177A48[0], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].camEye.z, boss->obj.pos.z + sp64.z, 0.02f, D_ctx_80177A48[0], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].camAt.x, boss->obj.pos.x, 0.05f, D_ctx_80177A48[1], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].camAt.y, boss->obj.pos.y, 0.05f, D_ctx_80177A48[1], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].camAt.z, boss->obj.pos.z, 0.05f, D_ctx_80177A48[1], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].unk_034, 0.0f, 0.5f, 0.5f, 0.0f);

            if (gCsFrameCount == 50) {
                Radio_PlayMessage(gMsg_ID_19335, RCID_ANDROSS_RED);
            }
            if (gCsFrameCount == 200) {
                gBossActive = 0;
                gPlayer[0].unk_0D0 = D_play_80161A54;
                func_8001CA24(0);
                boss->state = 21;
                func_effect_8007B344(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 60.0f, 5);
                func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f);

                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_286)) {
                        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                    }
                }
                D_ctx_80177AB0 = 4;
                gCsFrameCount = 0;
            }
            break;
        case 21:
            Andross_801876FC();
            gCsFrameCount++;
            gCameraShake = 10;
            if (gCsFrameCount < 200) {
                gPlayerFillScreenAlphas[0] += 4;
                if (gPlayerFillScreenAlphas[0] >= 255) {
                    gPlayerFillScreenAlphas[0] = 255;
                }
                gPlayerFillScreenReds[0] = gPlayerFillScreenGreens[0] = gPlayerFillScreenBlues[0] = 255;
                Math_SmoothStepToF(&D_display_800CA230, 0.15f, 0.2f, 0.004f, 0.0f);
                Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 70.0f, 1.0f, 4.0f, 0.0f);
            }
            switch (gCsFrameCount) {
                case 30:
                    gRadioState = 0;
                    Radio_PlayMessage(gMsg_ID_20318, RCID_FOX);
                    gPlayer[0].timer_220 = 200;
                    break;
                case 350:
                    Radio_PlayMessage(gMsg_ID_19468, RCID_JAMES);
                    break;
                case 500:
                    Radio_PlayMessage(gMsg_ID_19350, RCID_FOX);
                    gAllRangeCheckpoint = 1;
                    break;
                case 600:
                    D_ctx_80177AB0 = 5;
                    gFogRed = 129;
                    gFogGreen = 27;
                    gFogBlue = 0;
                    gFogNear = 996;
                    gFogFar = 1007;
                    gBgColor = 0x4081; // 64, 16, 0
                    D_game_80161A44 = 30000.0f;
                    gGroundLevel = -50.0f;
                    gPlayer[0].pos.x = -25995.0f;
                    gPlayer[0].pos.y = 300.0f;
                    gPlayer[0].pos.z = -11140.0f;
                    gPlayer[0].unk_08C = 0.0f;
                    gPlayer[0].unk_114 = 271.0f;
                    gPlayer[0].unk_110 = gPlayer[0].unk_4D8 = gPlayer[0].unk_0E8 = gPlayer[0].unk_0E4 =
                        gPlayer[0].unk_0EC = 0.0f;
                    gPlayer[0].unk_12C = 150.0f;
                    gPlayer[0].unk_034 = -90.0f;
                    gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
                    gPlayer[0].unk_1D0 = 100;
                    gPlayer[0].timer_1F8 = 240;
                    gPlayer[0].unk_234 = 1;
                    D_ctx_80177A48[5] = -1200.0f;

                    Andross_80188468();
                    Andross_80187C5C();
                    gPlayer[0].unk_014 = 1.0f;
                    func_play_800B7184(gPlayer, 1);
                    func_8001C8B8(0);
                    AUDIO_PLAY_BGM(D_boss_800C9E90[gCurrentLevel]);
                    AUDIO_PLAY_SFX(0x11403076, gDefaultSfxSource, 0);

                    D_ctx_80177CA4 = gHitCount;
                    break;
                case 800:
                    Radio_PlayMessage(gMsg_ID_19340, RCID_JAMES);
                    break;
                case 1000:
                    Audio_SetBaseSfxReverb(0);
                    break;
                case 1300:
                    Radio_PlayMessage(gMsg_ID_19355, RCID_JAMES);
                    break;
                case 1800:
                    Radio_PlayMessage(gMsg_ID_19360, RCID_JAMES);
                    break;
            }
            if (gCsFrameCount > 600) {
                Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 10.0f, 1.0f, 2.0f, 0.0f);
            }
            boss->obj.pos.y = 10000.0f;

            if ((gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) && ((gGameFrameCount % 4) == 0)) {
                Matrix_RotateY(gCalcMatrix, (gPlayer[0].unk_114 + gPlayer[0].unk_0E8) * M_DTOR, 0U);
                vec.x = RAND_FLOAT_CENTERED(800.0f);
                vec.y = 600.0f;
                vec.z = RAND_FLOAT(1000.0f) + -3000.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);
                Andross_80189B00(gPlayer[0].pos.x + sp64.x, sp64.y, gPlayer[0].unk_138 + sp64.z, 1.2f);
            }
            if (gPlayer[0].state_1C8 != PLAYERSTATE_1C8_0) {
                Matrix_RotateY(gCalcMatrix, -gPlayer[0].unk_058, 0);
                vec.x = 0.0f;
                vec.y = 0.0f;
                vec.z = -50.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp58);
                Matrix_RotateZ(gCalcMatrix, 2.0f * RAND_FLOAT(M_PI), 1);
                vec.x = RAND_FLOAT(50.0f) + 120.0f;
                vec.y = 0.0f;
                vec.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);
                if (gCsFrameCount < 1000) {
                    frameCountMask = 1;
                } else if (gCsFrameCount < 1500) {
                    frameCountMask = 3;
                } else if (gCsFrameCount < 2000) {
                    frameCountMask = 1;
                } else {
                    frameCountMask = 1;
                }
                sp98 = 1;
                if (!(gGameFrameCount & frameCountMask)) {
                    for (i = 0; i < sp98; i++) {
                        func_effect_8007797C(gPlayer[0].camEye.x + sp64.x, gPlayer[0].camEye.y + sp64.y,
                                             gPlayer[0].camEye.z + sp64.z, sp58.x, sp58.y, sp58.z,
                                             RAND_FLOAT(2.5f) + 2.5f);
                    }
                }
            }
            break;
    }
    xDisplacement = boss->fwork[3] - boss->obj.pos.x;
    yDisplacement = boss->fwork[4] - boss->obj.pos.y;
    zDisplacement = boss->fwork[5] - boss->obj.pos.z;
    yaw = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
    Math_SmoothStepToAngle(&boss->unk_078.x,
                           Math_RadToDeg(Math_Atan2F(yDisplacement, sqrtf(SQ(xDisplacement) + SQ(zDisplacement)))),
                           0.1f, boss->fwork[2], 0.0f);
    Math_SmoothStepToAngle(&boss->unk_078.y, yaw, 0.1f, boss->fwork[2], 0.0f);
    if (boss->swork[4] != 0) {
        Math_SmoothStepToAngle(&boss->obj.rot.y, Math_RadToDeg(-gPlayer[0].unk_058), 0.3f, 5.0f, 0.0f);
    } else if (boss->timer_054 == 0) {
        Math_SmoothStepToAngle(&boss->obj.rot.y, Math_RadToDeg(-gPlayer[0].unk_058), 0.3f, 1.5f, 0.0f);
    }
    Math_SmoothStepToF(&boss->fwork[0], boss->fwork[1], 0.2f, 1.0f, 0.00001f);
    Matrix_RotateY(gCalcMatrix, boss->unk_078.y * M_DTOR, 0U);
    Matrix_RotateX(gCalcMatrix, -boss->unk_078.x * M_DTOR, 1U);
    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = boss->fwork[0];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);
    boss->vel.x = sp64.x;
    boss->vel.y = sp64.y;
    boss->vel.z = sp64.z - D_ctx_80177D08;
    if (boss->state < 20) {
        gRadarMarks[59].unk_00 = 1;
        gRadarMarks[59].unk_02 = 102;
        gRadarMarks[59].pos.x = boss->obj.pos.x;
        gRadarMarks[59].pos.y = boss->obj.pos.y;
        gRadarMarks[59].pos.z = boss->obj.pos.z;
        gRadarMarks[59].unk_10 = boss->unk_078.y + 180.0f;
    }
    gActors[10].info.unk_1C = 1.0f;
    gActors[11].info.unk_1C = 1.0f;
    if (boss->swork[5] != 0) {
        boss->swork[5]--;
        if (boss->swork[5] == 0) {
            AUDIO_PLAY_SFX(0x11032075, gActors[10].sfxSource, 4);
            AUDIO_PLAY_SFX(0x11032075, gActors[11].sfxSource, 4);
            AUDIO_PLAY_SFX(0x3103108B, gActors[10].sfxSource, 4);
            AUDIO_PLAY_SFX(0x3103108B, gActors[11].sfxSource, 4);
        }
        gActors[10].obj.pos.x = boss->obj.pos.x + 200.0f;
        gActors[10].obj.pos.y = boss->obj.pos.y - 200.0f;
        gActors[10].obj.pos.z = boss->obj.pos.z + 200.0f;
        gActors[10].state = 0;
        gActors[10].timer_0C2 = 20;
        gActors[10].info.unk_1C = 0.0f;
        gActors[11].obj.pos.x = boss->obj.pos.x - 200.0f;
        gActors[11].obj.pos.y = boss->obj.pos.y - 200.0f;
        gActors[11].obj.pos.z = boss->obj.pos.z + 200.0f;
        gActors[11].state = 0;
        gActors[11].timer_0C2 = 20;
        gActors[11].info.unk_1C = 0.0f;
    }
    Math_SmoothStepToF(&boss->fwork[21], boss->fwork[22], 1.0f, 6.0f, 0);
    Math_SmoothStepToF(&boss->fwork[23], boss->fwork[24], 0.3f, 0.01f, 0);
}

bool Andross_8018B47C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Boss* boss = (Boss*) data;

    if (boss->fwork[21] >= 254.0f) {
        if (limbIndex == 2) {
            RCP_SetupDL(&gMasterDisp, 0x16);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) boss->fwork[25], 255, 255, 255);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x17);
        }
    } else {
        RCP_SetupDL(&gMasterDisp, 0x33);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) boss->fwork[21]);
    }
    if ((limbIndex == 2) && (boss->swork[6] != 0)) {
        *dList = NULL;
        return false;
    }
    if ((limbIndex == 1) || (limbIndex == 2)) {
        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, 1);
        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, 1);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, 1);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, 1);
        if (*dList != NULL) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Push(&gCalcMatrix);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
            if (limbIndex == 1) {
                Matrix_RotateY(gGfxMatrix, -boss->fwork[14] * M_DTOR, 1);
                Matrix_Scale(gGfxMatrix, boss->fwork[16] + 1.0f, 1.0f, 1.0f - boss->fwork[16], 1);
                Matrix_RotateY(gGfxMatrix, boss->fwork[14] * M_DTOR, 1);
            } else {
                Matrix_RotateY(gGfxMatrix, boss->fwork[14] * 1.5f * M_DTOR, 1);
                Matrix_Scale(gGfxMatrix, 2.0f * boss->fwork[16] + 1.0f, 1.0f, 1.0f - 2.0f * boss->fwork[16], 1);
                Matrix_RotateY(gGfxMatrix, -boss->fwork[14] * 1.5f * M_DTOR, 1);
            }
            Matrix_SetGfxMtx(&gMasterDisp);
            if (((boss->swork[3] % 2) != 0) && (boss->fwork[21] >= 254.0f)) {
                RCP_SetupDL(&gMasterDisp, 0x1B);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }

            gSPDisplayList(gMasterDisp++, *dList);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Pop(&gCalcMatrix);
        }
        return true;
    }
    return false;
}

void Andross_8018B8C0(Boss* boss) {
    s32 j;
    s32 i;
    f32 temp;
    s32 pad;
    Vec3f spAC;
    Vec3f spA0;

    if (boss->state != 21) {
        Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 20.0f * M_DTOR, 1);
        Matrix_Scale(gGfxMatrix, boss->fwork[23] + 1.0f, 1.0f - boss->fwork[23], 1.0f, 1);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 20.0f * M_DTOR, 1);
        Matrix_Scale(gGfxMatrix, boss->fwork[23] + 1.0f, 1.0f - boss->fwork[23], 1.0f, 1);
        Matrix_Scale(gGfxMatrix, boss->unk_3F8, boss->unk_3F8, boss->unk_3F8, 1);
        Animation_DrawSkeleton(0, D_VE2_600C0A4, boss->vwork, Andross_8018B47C, NULL, boss, &gIdentityMatrix);
        if (boss->fwork[21] >= 254) {
            RCP_SetupDL(&gMasterDisp, 0x36);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 64, 64, 255);
        } else {
            RCP_SetupDL(&gMasterDisp, 0x46);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 64, 64, (s32) boss->fwork[21]);
        }
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        Matrix_Translate(gGfxMatrix, 0.0f, -16.0f, 0.0f, 1);
        Matrix_Scale(gGfxMatrix, 0.3f, 0.6f, 0.3f, 1);

        for (i = 0; i < 30; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateY(gCalcMatrix, i * 50.0f * M_DTOR, 0U);
            spAC.x = 0.0f;
            spAC.y = 0.0f;
            spAC.z = i * 0.8f;
            Matrix_MultVec3f(gCalcMatrix, &spAC, &spA0);
            Matrix_Translate(gGfxMatrix, spA0.x, 10.0f, spA0.z, 1);
            Matrix_RotateY(gGfxMatrix, M_DTOR * -boss->obj.rot.y - gPlayer[0].unk_058, 1);

            for (j = 0; j < 10; j++) {
                Matrix_Translate(gGfxMatrix, 0.0f, -10.0f, 0.0f, 1);
                temp = SIN_DEG((s32) boss->fwork[19] * (i * 10 + j) + (gGameFrameCount * 5)) * boss->fwork[10];
                Matrix_RotateZ(gGfxMatrix, (boss->fwork[18] + temp) * M_DTOR, 1);
                Matrix_RotateX(gGfxMatrix, boss->fwork[17] * M_DTOR, 1);
                Matrix_Push(&gGfxMatrix);
                Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                if (j == 9) {
                    gSPDisplayList(gMasterDisp++, D_VE2_600C2D0);
                } else {
                    gSPDisplayList(gMasterDisp++, D_VE2_600C560);
                }
                Matrix_Pop(&gGfxMatrix);
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }
}

void Andross_8018BDD8(void) {
    s32 i;
    f32 spC0[17];
    f32 sp7C[17];
    s32 temp_lo;
    Vtx* sp74;
    Vtx* sp70;

    sp74 = LOAD_ASSET(D_ANDROSS_C038FE8);
    sp70 = LOAD_ASSET(D_ANDROSS_C017598);

    for (i = 0; i < 17; i++) {
        if (i == 0 || i == 16) {
            spC0[i] = 0.0f;
            sp7C[i] = 0.0f;
        } else if (gLevelMode == LEVELMODE_ALL_RANGE) {
            spC0[i] = RAND_FLOAT_CENTERED(120.0f);
            sp7C[i] = RAND_FLOAT_CENTERED(120.0f);
        } else {
            spC0[i] = RAND_FLOAT_CENTERED(30.0f);
            sp7C[i] = RAND_FLOAT_CENTERED(30.0f);
        }
    }

    for (i = 0; i < 34; i++) {
        temp_lo = (sp74[i].v.ob[2] + 200) / 25;
        sp70[i].v.ob[0] = sp74[i].v.ob[0] + spC0[temp_lo];
        sp70[i].v.ob[1] = sp74[i].v.ob[1] + sp7C[temp_lo];
    }

    if (gBossActive != 0) {
        Math_SmoothStepToF(&D_Andross_801A7F58, 0.0f, 1.0f, 10.0f, 0.0f);
    } else {
        Math_SmoothStepToF(&D_Andross_801A7F58, D_Andross_801A7F60, 1.0f, 1.0f, 0.0f);
    }

    D_Andross_801A7F68 += D_Andross_801A7F70;
    Math_SmoothStepToF(&D_Andross_801A7F70, D_Andross_801A7F78, 1.0f, 0.1f, 0.0f);
}

void Andross_8018C390(Player* player) {

    player->unk_2B4 = 1;
    player->unk_280 = 0;
    switch (player->unk_1D0) {
        case 2:
        case 3:
            break;
        case 0:
            Math_SmoothStepToF(&player->pos.x, gBosses[0].obj.pos.x, 0.5f, 30.0f, 0);
            Math_SmoothStepToF(&player->pos.y, gBosses[0].obj.pos.y - 150.0f, 0.5f, 30.0f, 0);
            Math_SmoothStepToF(&player->pos.z, gBosses[0].obj.pos.z - 100.0f, 0.5f, 60.0f, 0);
            D_ctx_80177D20 = player->unk_144 = -player->pos.z;
            Math_SmoothStepToF(&player->camEye.z, 2000.0f, 0.05f, 20.0f, 0);
            Math_SmoothStepToF(&player->camEye.x, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->camEye.y, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->camAt.x, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->camAt.y, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->camAt.z, 100.0f, 0.05f, 10.0f, 0.0f);
            break;
        case 1:
            player->unk_0E4 += 15.0f;

            if (player->unk_0E4 > 180.0f) {
                player->unk_0E4 -= 360.0f;
            }
            player->unk_0E8 += 9.0f;
            if (player->unk_0E8 > 180.0f) {
                player->unk_0E8 -= 360.0f;
            }
            Math_SmoothStepToF(&player->camEye.z, 400.0f, 0.05f, 20.0f, 0.0f);
            if (player->timer_1F8 != 0) {
                if (gControllerPress[gMainController].button != 0) {
                    player->timer_1F8--;
                }
            }
            if (player->timer_1F8 == 0) {
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
            }
            break;
    }
    player->unk_138 = player->pos.z + player->unk_08C;
    func_play_800A46A0(player);
}

void Andross_8018C660(Effect* effect, f32 xPos, f32 yPos, f32 zPos, s32 arg4) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_396;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->unk_4C = arg4;
    effect->scale2 = RAND_FLOAT(2.5f) + 5.0f;
    effect->unk_60.x = RAND_FLOAT_CENTERED(20.0f);
    effect->unk_60.y = RAND_FLOAT_CENTERED(20.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
}

void Andross_8018C734(f32 xPos, f32 yPos, f32 zPos, s32 arg3) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_8018C660(&gEffects[i], xPos, yPos, zPos, arg3);
            break;
        }
    }
}

void Andross_8018C7A0(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 arg7) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_396;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;
    effect->state = 1;
    effect->unk_4C = arg7;
    if (arg7 < 8) {
        effect->scale2 = RAND_FLOAT(2.5f) + 5.0f;
    }
    effect->obj.rot.x = RAND_FLOAT(360.0f);
    effect->obj.rot.y = RAND_FLOAT(360.0f);
    effect->unk_60.x = RAND_FLOAT(10.0f) + 10.0f;
    effect->unk_60.y = RAND_FLOAT(10.0f) + 10.0f;
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.unk_10 = 100.0f;
}

void Andross_8018C8D4(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 arg6) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_8018C7A0(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, arg6);
            break;
        }
    }
}

void Andross_8018C958(Effect* effect, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    Effect_Initialize(effect);
    effect->obj.status = OBJ_ACTIVE;
    effect->obj.id = OBJ_EFFECT_396;
    effect->state = 10;
    effect->obj.pos.x = xPos;
    effect->obj.pos.y = yPos;
    effect->obj.pos.z = zPos;
    effect->vel.x = xVel;
    effect->vel.y = yVel;
    effect->vel.z = zVel;
    effect->scale1 = scale;
    effect->scale2 = scale * 0.1f;
    effect->unk_44 = 100;
    effect->obj.rot.z = RAND_FLOAT(360.0f);
    effect->unk_60.z = RAND_FLOAT_CENTERED(20.0f);
    Object_SetInfo(&effect->info, effect->obj.id);
    effect->info.unk_14 = 1;
    effect->info.unk_10 = 100.0f;
}

void Andross_8018CA50(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_8018C958(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale);
            break;
        }
    }
}

void Andross_8018CAD4(Effect* effect) {
    s32 i;
    Item* item;
    Vec3f vec;
    Vec3f vel;
    f32 effectXpos;
    f32 effectYpos;
    f32 effectZpos;
    f32 pitch;
    f32 yaw;
    f32 sp40;
    f32 sp3C;
    f32 sp38;
    f32 sp34;

    effect->obj.rot.x += effect->unk_60.x;
    effect->obj.rot.y += effect->unk_60.y;
    switch (effect->state) {
        case 0:
            if (gBosses[0].state == 17) {
                Math_SmoothStepToF(&effect->obj.pos.x, gBosses[0].obj.pos.x, 0.03f, 10.0f, 0);
                Math_SmoothStepToF(&effect->obj.pos.y, gBosses[0].obj.pos.y - 200.0f, 0.03f, 10.0f, 0);
                effectXpos = effect->obj.pos.x;
                effectYpos = effect->obj.pos.y;
                effectZpos = effect->obj.pos.z;
                sp3C = gBosses[0].obj.pos.x;
                sp38 = gBosses[0].obj.pos.y - 150.0f;
                sp34 = gBosses[0].obj.pos.z - 100.0f;
                yaw = Math_Atan2F(sp3C - effectXpos, sp34 - effectZpos);
                sp40 = sqrtf(SQ(sp3C - effectXpos) + SQ(sp34 - effectZpos));
                pitch = -Math_Atan2F(sp38 - effectYpos, sp40);
                Matrix_RotateY(gCalcMatrix, yaw, 0);
                Matrix_RotateX(gCalcMatrix, pitch, 1);
                vec.x = 0.0f;
                vec.y = 0.0f;
                vec.z = 30.0f;
                Matrix_MultVec3f(gCalcMatrix, &vec, &vel);
                effect->vel.x = vel.x;
                effect->vel.y = vel.y;
                effect->vel.z = vel.z - D_ctx_80177D08;
                if ((fabsf(effect->obj.pos.x - gBosses[0].obj.pos.x) <= 100.0f) &&
                    (fabsf(effect->obj.pos.z - (gBosses[0].obj.pos.z - 100.0f)) <= 100.0f)) {
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            } else {
                effect->info.unk_10 = 100.0f;
                Math_SmoothStepToF(&effect->vel.x, 0.0f, 0.05f, 1.0f, 0);
                Math_SmoothStepToF(&effect->vel.y, 0.0f, 0.05f, 1.0f, 0);
                Math_SmoothStepToF(&effect->vel.z, 70.0f, 0.05f, 2.0f, 0);
                func_effect_8007A774(&gPlayer[0], effect, 100.0f);
                if (effect->unk_44 != 0) {
                    func_effect_8007D0E0(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 10.0f);
                    func_effect_8007A6F0(&effect->obj.pos, 0x2903A008);
                    Object_Kill(&effect->obj, effect->sfxSource);
                }
            }
            effect->unk_44 = 0;
            break;
        case 1:
            func_effect_8007A774(&gPlayer[0], effect, 100.0f);
            if (effect->unk_44 != 0) {
                func_effect_8007D0E0(effect->obj.pos.x, effect->obj.pos.y, effect->obj.pos.z, 10.0f);
                func_effect_8007A6F0(&effect->obj.pos, 0x2903A008);
                Object_Kill(&effect->obj, effect->sfxSource);
                if (Rand_ZeroOne() < 0.1f) {
                    item = gItems;
                    for (i = 0; i < 20; i++, item++) {
                        if (item->obj.status == OBJ_FREE) {
                            Item_Initialize(item);
                            item->obj.status = OBJ_INIT;
                            if (Rand_ZeroOne() < 0.5f) {
                                item->obj.id = OBJ_ITEM_SILVER_RING;
                            } else {
                                item->obj.id = OBJ_ITEM_BOMB;
                            }
                            item->obj.pos.x = effect->obj.pos.x;
                            item->obj.pos.y = effect->obj.pos.y;
                            item->obj.pos.z = effect->obj.pos.z;
                            item->timer_4A = 8;
                            Object_SetInfo(&item->info, item->obj.id);
                            item->unk_50 = 90.0f;
                            break;
                        }
                    }
                }
            }
            break;
        case 10:
            effect->obj.rot.z += effect->unk_60.z;
            Math_SmoothStepToF(&effect->scale2, effect->scale1, 0.05f, 0.3f, 0);
            Math_SmoothStepToF(&effect->vel.y, 0.0f, 0.05f, 0.5f, 0.0f);
            Math_SmoothStepToF(&effect->vel.x, 0.0f, 0.05f, 0.5f, 0.0f);
            effect->unk_44 -= 10;
            if (effect->unk_44 < 0) {
                Object_Kill(&effect->obj, effect->sfxSource);
            }
            break;
    }
}

static Gfx* D_i6_801A6790[10] = {
    D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880,
    D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880, D_arwing_3016660,  D_arwing_3015D80,
};

void Andross_8018CF98(Effect* effect) {

    if (effect->state == 10) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, effect->unk_44);
        Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x1D);
        if (effect->unk_4C < 8) {
            Matrix_Scale(gGfxMatrix, effect->scale2, effect->scale2, effect->scale2, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
        gSPDisplayList(gMasterDisp++, D_i6_801A6790[effect->unk_4C]);
        RCP_SetupDL(&gMasterDisp, 0x40);
    }
}

void Andross_8018D0D8(Boss* boss) {
    if ((gPlayer[0].timer_498 == 0) && (gPlayer[0].state_1C8 == PLAYERSTATE_1C8_3) &&
        (fabsf(boss->vwork[10].x - gPlayer[0].pos.x) < 700.0f) &&
        (fabsf(boss->vwork[10].y - gPlayer[0].pos.y) < 700.0f)) {
        Player_ApplyDamage(&gPlayer[0], 0, 40);
    }
}

void Andross_Boss320_Init(Boss320* this) {
    Audio_SetBaseSfxReverb(0x18);
    D_i6_801A7F5C = D_i6_801A7F64 = D_i6_801A7F6C = D_i6_801A7F74 = D_i6_801A7F7C = D_i6_801A8430 = 0.0f;
    D_bg_800C9C30 = 0.0f;
    this->health = 100;
    this->fwork[18] = 1.0f;
    this->fwork[17] = 1.0f;
    gLight1R = 255;
    gLight1G = 80;
    gLight1B = 20;
    gAmbientR = 1;
    gAmbientG = 0;
    gAmbientB = 20;
    this->timer_058 = 10;
    this->swork[4] = this->swork[5] = 200;
    this->swork[6] = 100;
    gBossActive = 1;
    D_ctx_80177AB0 = 1;
    this->info.hitbox[16] = 200.0f;
    this->info.hitbox[22] = 200.0f;
    Audio_PlaySequence(SEQ_PLAYER_BGM, SEQ_ID_AND_BOSS | SEQ_FLAG, 0, 0);
}

void Andross_8018D2B0(Boss* boss) {
    s32 i;
    Vec3f sp68;

    if ((boss->swork[5] < 0) && (boss->swork[4] < 0)) {
        if ((boss->dmgType != DMG_NONE) && (boss->dmgPart == 0 || boss->dmgPart == 1)) {
            boss->dmgType = DMG_NONE;
            if (boss->state < 12) {
                boss->health -= boss->damage;
                boss->timer_05C = 20;
                if ((boss->state == 9) || (boss->state == 10)) {
                    if (boss->health <= 0) {
                        gScreenFlashTimer = 8;
                        AUDIO_PLAY_SFX(0x2940D09A, boss->sfxSource, 4);
                        AUDIO_PLAY_SFX(0x31009063, boss->sfxSource, 4);
                        AUDIO_PLAY_SFX(0x19403070, boss->sfxSource, 4);
                        Audio_KillSfxBySourceAndId(boss->sfxSource, 0x11030073);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                        boss->state = 31;
                        boss->timer_050 = 200;
                        gPlayer[0].state_1C8 = PLAYERSTATE_1C8_7;
                        gPlayer[0].unk_1D0 = 0;
                    } else if (boss->health < 50) {
                        AUDIO_PLAY_SFX(0x2943500F, boss->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(0x29034003, boss->sfxSource, 4);
                    }
                } else if (boss->health <= 0) {
                    AUDIO_PLAY_SFX(0x19403070, boss->sfxSource, 4);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                    if (gLevelStage == 0) {
                        boss->state = 30;
                    } else {
                        boss->state = 32;
                    }
                    boss->fwork[9] = 0.0f;
                    boss->unk_04C = 0;
                    gCsFrameCount = 0;
                    boss->timer_05C = 100;
                } else {
                    AUDIO_PLAY_SFX(0x29034003, boss->sfxSource, 4);
                }
            }
        }
    } else if (boss->dmgType != DMG_NONE) {
        switch (boss->dmgPart) {
            case 0:
                if (boss->state < 11) {
                    boss->swork[6] -= boss->damage;
                    boss->swork[0] = 30;
                    AUDIO_PLAY_SFX(0x29034003, boss->sfxSource, 4);
                    if (boss->swork[6] <= 0) {
                        boss->swork[6] = 100;
                        boss->state = 12;
                        boss->timer_050 = 120;
                        boss->unk_04C = 0;
                        boss->fwork[9] = 0.0f;
                        AUDIO_PLAY_SFX(0x1940306F, boss->sfxSource, 4);
                    }
                }
                break;
            case 1:
                if (boss->state < 12) {
                    boss->swork[6] -= boss->damage;
                    boss->swork[1] = 30;
                    AUDIO_PLAY_SFX(0x29034003, boss->sfxSource, 4);
                    if (boss->swork[6] <= 0) {
                        boss->swork[6] = 100;
                        boss->state = 13;
                        boss->timer_050 = 120;
                        boss->unk_04C = 0;
                        boss->fwork[9] = 0.0f;
                        AUDIO_PLAY_SFX(0x1940306F, boss->sfxSource, 4);
                    }
                }
                break;
            case 2:
            case 3:
                if (boss->swork[7] == 0) {
                    boss->swork[boss->dmgPart] = 30;
                    if (boss->dmgPart == 2) {
                        sp68.x = boss->vwork[0].x;
                        sp68.y = boss->vwork[0].y;
                        sp68.z = boss->vwork[0].z;
                        boss->swork[4] -= boss->damage;
                        if (boss->swork[4] < 0) {
                            boss->info.hitbox[16] = 0.0f;
                            func_effect_8007BFFC(boss->vwork[0].x, boss->vwork[0].y, boss->vwork[0].z, 0.0f, 0.0f, 0.0f,
                                                 20.0f, 15);

                            for (i = 0; i < 30; i++) {
                                func_effect_800794CC(boss->vwork[0].x + RAND_FLOAT_CENTERED(500.0f),
                                                     boss->vwork[0].y + RAND_FLOAT_CENTERED(500.0f), boss->vwork[0].z,
                                                     RAND_FLOAT(1.0f) + 1.0f);
                            }
                            func_effect_8007B344(boss->vwork[0].x, boss->vwork[0].y, boss->vwork[0].z, 20.0f, 5);
                            func_effect_8007A6F0(&sp68, 0x2903B009);
                        } else {
                            func_effect_8007A6F0(&sp68, 0x29034003);
                        }
                    } else {
                        sp68.x = boss->vwork[1].x;
                        sp68.y = boss->vwork[1].y;
                        sp68.z = boss->vwork[1].z;
                        boss->swork[5] -= boss->damage;
                        if (boss->swork[5] < 0) {
                            boss->info.hitbox[22] = 0.0f;
                            func_effect_8007BFFC(boss->vwork[1].x, boss->vwork[1].y, boss->vwork[1].z, 0.0f, 0.0f, 0.0f,
                                                 20.0f, 15);

                            for (i = 0; i < 30; i++) {
                                func_effect_800794CC(boss->vwork[1].x + RAND_FLOAT_CENTERED(500.0f),
                                                     boss->vwork[1].y + RAND_FLOAT_CENTERED(500.0f), boss->vwork[1].z,
                                                     RAND_FLOAT(1.0f) + 1.0f);
                            }
                            func_effect_8007B344(boss->vwork[1].x, boss->vwork[1].y, boss->vwork[1].z, 20.0f, 5);
                            func_effect_8007A6F0(&sp68, 0x2903B009);
                        } else {
                            func_effect_8007A6F0(&sp68, 0x29034003);
                        }
                    }
                }
                break;
        }
        boss->dmgType = DMG_NONE;
    }
}

void Andross_8018D9C0(Boss* boss) {

    switch (boss->state) {
        case 2:
            boss->state = 3;
            break;
        case 3:
            boss->state = 4;
            break;
        case 4:
            boss->state = 5;
            boss->timer_050 = 30;
            break;
        case 5:
            boss->state = 6;
            boss->timer_050 = 40;
            break;
        case 6:
            boss->state = 17;
            boss->timer_050 = 180;
            boss->fwork[16] = 0.0f;
            break;
        case 12:
        case 13:
        case 14:
            boss->state = 7;
            boss->timer_050 = 150;
            break;
        default:
            boss->state = 2;
            break;
    }
    boss->fwork[9] = 0.0f;
    boss->unk_04C = 0;
    boss->fwork[1] = 0.0f;
    boss->fwork[4] = 0.0f;
    boss->fwork[7] = 0.0f;
}

void Andross_8018DA94(Boss* boss, Vec3f* arg1) {
    s32 i;

    func_effect_8007BFFC(arg1->x, arg1->y, arg1->z, 0.0f, 0.0f, 0.0f, 10.0f, 10);
    for (i = 0; i < 7; i++) {
        func_effect_800794CC(RAND_FLOAT_CENTERED(200.0f) + arg1->x, RAND_FLOAT_CENTERED(200.0f) + arg1->y, arg1->z,
                             RAND_FLOAT(0.5f) + 1.0f);
    }
    func_effect_8007B344(arg1->x, arg1->y, arg1->z, 10.0f, 5);
    AUDIO_PLAY_SFX(0x2903B009, boss->sfxSource, 4);
}

static f32 D_i6_801A67B8[] = { 0.0f, 0.0f, 0.0f };

void Andross_8018DBF0(Boss* boss) {
    s32 i;
    s32 frameCountMask;
    Vec3f spD0[100];
    f32 xDisplacement;
    f32 yDisplacement;
    f32 zDisplacement;
    Effect* effect;
    PlayerShot* playerShot;
    Boss* boss1;
    Player* player;
    f32 yaw;
    f32 pitch;
    s16 limbCount;
    s32 initialstate;
    s32 pad;

    player = &gPlayer[0];
    gBossFrameCount++;

    initialstate = boss->state;

    Andross_801876FC();
    gAmbientR = 10;
    gAmbientG = 0;
    gAmbientB = 20;
    D_ctx_8017812C = 0;
    boss->fwork[19] += 5.0f;
    if (boss->swork[9] != 0) {
        boss->swork[9]--;
        Math_SmoothStepToF(&boss->fwork[17], 1.5f, 0.7f, 0.4f, 0);
    } else {
        Math_SmoothStepToF(&boss->fwork[17], 1.0f, 0.2f, 0.3f, 0);
    }

    boss->fwork[18] = boss->fwork[17];
    if (boss->swork[10] != 0) {
        boss->swork[10]--;
        if (boss->swork[10] < 20) {
            frameCountMask = 0x1F;
        } else if (boss->swork[10] < 30) {
            frameCountMask = 7;
        } else if (boss->swork[10] < 40) {
            frameCountMask = 1;
        } else {
            frameCountMask = 0;
        }
        if (!(gGameFrameCount & frameCountMask)) {
            Andross_8018CA50(boss->vwork[6].x, boss->vwork[6].y, boss->vwork[6].z, 0.0f, -30.0f, 0.0f, 30.0f);
            Andross_8018CA50(boss->vwork[7].x, boss->vwork[7].y, boss->vwork[7].z, 0.0f, -30.0f, 0.0f, 30.0f);
            Andross_8018CA50(boss->vwork[8].x, boss->vwork[8].y, boss->vwork[8].z, -30.0f, 0.0f, 0.0f, 30.0f);
            Andross_8018CA50(boss->vwork[9].x, boss->vwork[9].y, boss->vwork[9].z, 30.0f, 0.0f, 0.0f, 30.0f);
        }
    }
    Math_SmoothStepToF(&boss->fwork[20], 0.0f, 1.0f, 0.1f, 0.01f);
    Math_SmoothStepToF(&boss->fwork[21], 0.0f, 1.0f, 0.05f, 0.001f);
    Andross_8018D2B0(boss);
    boss->swork[7] = 0;
    boss->fwork[14] = boss->fwork[15] = 0.0f;
    if (boss->state >= 2) {
        gBlurAlpha = 128;
    }

    for (i = 0; i < 4; i++) {
        if (boss->swork[i] > 0) {
            boss->swork[i]--;
        }
    }
    Math_SmoothStepToF(&boss->obj.pos.z, gPlayer[0].pos.z + boss->fwork[6], boss->fwork[8], boss->fwork[7], 0);
    Math_SmoothStepToF(&boss->obj.pos.x, boss->fwork[0], boss->fwork[2], boss->fwork[1], 0);
    Math_SmoothStepToF(&boss->obj.pos.y, boss->fwork[3], boss->fwork[5], boss->fwork[4], 0);
    Math_SmoothStepToF(&boss->fwork[11], 0.0f, 0.1f, 2.0f, 0);
    Math_SmoothStepToF(&boss->fwork[12], 0.0f, 0.1f, 2.0f, 0);
    Math_SmoothStepToF(&boss->fwork[13], 0.0f, 0.1f, 2.0f, 0);
    if (player->unk_234 != 0) {
        xDisplacement = gPlayer[0].pos.x - boss->vwork[2].x;
        yDisplacement = gPlayer[0].pos.y - boss->vwork[2].y;
        zDisplacement = gPlayer[0].unk_138 - boss->vwork[2].z;
        yaw = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
        pitch = Math_RadToDeg(Math_Atan2F(yDisplacement, sqrtf(SQ(xDisplacement) + SQ(zDisplacement))));

        if ((yaw > 30.0f) && (yaw < 180.0f)) {
            yaw = 30.0f;
        }
        if ((yaw < 330.0f) && (yaw > 180.0f)) {
            yaw = 330.0f;
        }
        if ((pitch > 30.0f) && (pitch < 180.0f)) {
            pitch = 30.0f;
        }
        if ((pitch < 330.0f) && (pitch > 180.0f)) {
            pitch = 330.0f;
        }
    } else {
        yaw = 0.0f;
        pitch = 345.0f;
    }
    Math_SmoothStepToAngle(&boss->vwork[4].x, pitch, 0.5f, 5.0f, 0);
    Math_SmoothStepToAngle(&boss->vwork[4].y, yaw, 0.5f, 5.0f, 0);
    if (player->unk_234 != 0) {
        xDisplacement = gPlayer[0].pos.x - boss->vwork[3].x;
        yDisplacement = gPlayer[0].pos.y - boss->vwork[3].y;
        zDisplacement = gPlayer[0].unk_138 - boss->vwork[3].z;
        yaw = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
        pitch = Math_RadToDeg(Math_Atan2F(yDisplacement, sqrtf(SQ(xDisplacement) + SQ(zDisplacement))));
        if ((yaw > 30.0f) && (yaw < 180.0f)) {
            yaw = 30.0f;
        }
        if ((yaw < 330.0f) && (yaw > 180.0f)) {
            yaw = 330.0f;
        }
        if ((pitch > 30.0f) && (pitch < 180.0f)) {
            pitch = 30.0f;
        }
        if ((pitch < 330.0f) && (pitch > 180.0f)) {
            pitch = 330.0f;
        }
    } else {
        yaw = 0.0f;
        pitch = 345.0f;
    }
    Math_SmoothStepToAngle(&boss->vwork[5].x, pitch, 0.5f, 5.0f, 0);
    Math_SmoothStepToAngle(&boss->vwork[5].y, yaw, 0.5f, 5.0f, 0);
    switch (boss->state) {
        case 0:
            boss->fwork[8] = 0.1f;
            boss->fwork[7] = 50.0f;
            boss->state = 1;
            boss->timer_050 = 60;
            boss->timer_052 = 80;
            boss->timer_054 = 150;
            boss->fwork[9] = 1.0f;
            /* fallthrough */
        case 1:
            boss->timer_05A = 100;
            if (boss->timer_054 == 65) {
                AUDIO_PLAY_SFX(0x1940306E, boss->sfxSource, 4);
            }
            if (boss->timer_050 != 0) {
                boss->fwork[6] = -3000.0f;
            } else {
                boss->fwork[6] = -1000.0f;
                Math_SmoothStepToF(&D_i6_801A7F5C, gLight1R, 1.0f, 4.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F64, gLight1G, 1.0f, 3.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F6C, gLight1B, 1.0f, 3.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F74, gAmbientR, 1.0f, 2.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F7C, gAmbientG, 1.0f, 2.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A8430, gAmbientB, 1.0f, 2.0f, 0.0f);
            }
            Math_SmoothStepToF(&D_bg_800C9C30, 32.0f, 1.0f, 0.5f, 0.0f);
            Math_SmoothStepToF(&player->unk_034, 0.0f, 0.2f, 3.0f, 0);
            boss->fwork[8] = 0.1f;
            Math_SmoothStepToF(&boss->fwork[7], 200.0f, 1.0f, 10.0f, 0);
            if (boss->timer_052 == 0) {
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C002B08)) {
                    boss->unk_04C = 0;
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C002B08, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            } else {
                if (boss->timer_052 < 16) {
                    boss->unk_04C++;
                    if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C033D98)) {
                        boss->unk_04C = Animation_GetFrameCount(&D_ANDROSS_C033D98) - 1;
                    }
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C033D98, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
                if (boss->timer_052 == 1) {
                    boss->unk_04C = 0;
                }
            }
            Math_SmoothStepToF(&boss->fwork[9], 0.2f, 1.0f, 0.01f, 0);
            if (boss->timer_054 == 0) {
                boss->state = 2;
                boss->unk_04C = 0;
                boss->fwork[7] = boss->fwork[9] = 0.0f;
                boss->vel.z = -20.0f;
            }
            break;
        case 2:
            boss->fwork[6] = -4000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 30.0f, 1.0f, 5.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[2] = 0.05f;
            boss->fwork[3] = 0.0f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 10.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 10.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&boss->fwork[9], 0.7f, 1.0f, 0.005f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C033780)) {
                Andross_8018D9C0(boss);
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C033780, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            break;
        case 3:
            if (boss->swork[4] < 0) {
                Andross_8018D9C0(boss);
            } else {
                boss->fwork[0] = player->pos.x;
                boss->fwork[3] = player->pos.y + 1000.0f;
                if (boss->unk_04C == 60) {
                    AUDIO_PLAY_SFX(0x1940306A, boss->sfxSource, 4);
                }
                if (boss->unk_04C > 60) {
                    if (boss->unk_04C == 76) {
                        boss->fwork[7] = 0.0f;
                    }
                    if (boss->unk_04C > 76) {
                        boss->fwork[6] = -2500.0f;
                        boss->fwork[8] = 0.1f;
                        Math_SmoothStepToF(&boss->fwork[7], 100.0f, 1.0f, 10.0f, 0);
                    } else {
                        boss->fwork[6] = -1500.0f;
                        boss->fwork[8] = 0.3f;
                        Math_SmoothStepToF(&boss->fwork[7], 200.0f, 1.0f, 40.0f, 0);
                    }
                    boss->fwork[2] = 0.05f;
                    boss->fwork[5] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[1], 2.0f, 1.0f, 0.5f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 2.0f, 1.0f, 0.5f, 0);
                    boss->swork[7] = 1;
                    boss->fwork[14] = -100.0f;
                    boss->fwork[15] = -50.0f;
                } else {
                    boss->fwork[6] = -4000.0f;
                    boss->fwork[8] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[7], 30.0f, 1.0f, 2.0f, 0);
                    boss->fwork[2] = 0.1f;
                    boss->fwork[5] = 0.1f;
                    boss->fwork[14] = 50.0f;
                    Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 20.0f, 1.0f, 1.0f, 0);
                }
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C029F74)) {
                    Andross_8018D9C0(boss);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C029F74, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 4:
            if (boss->swork[4] < 0) {
                Andross_8018D9C0(boss);
            } else {
                boss->fwork[0] = player->pos.x;
                boss->fwork[3] = player->pos.y;
                if (boss->unk_04C == 55) {
                    AUDIO_PLAY_SFX(0x1940306A, boss->sfxSource, 4);
                }
                if (boss->unk_04C > 55) {
                    boss->fwork[6] = -1500.0f;
                    boss->fwork[8] = 0.3f;
                    Math_SmoothStepToF(&boss->fwork[7], 200.0f, 1.0f, 40.0f, 0);
                    boss->swork[7] = 1;
                    boss->fwork[2] = 0.05f;
                    boss->fwork[5] = 0.05f;
                    boss->fwork[14] = -100.0f;
                    Math_SmoothStepToF(&boss->fwork[1], 2.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 2.0f, 1.0f, 1.0f, 0);
                } else {
                    boss->fwork[6] = -4000.0f;
                    boss->fwork[8] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[7], 30.0f, 1.0f, 2.0f, 0);
                    boss->fwork[2] = 0.1f;
                    boss->fwork[5] = 0.1f;
                    boss->fwork[14] = 50.0f;
                    Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 1.0f, 0);
                }
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C02E494)) {
                    Andross_8018D9C0(boss);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C02E494, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 5:
            if (boss->swork[5] < 0) {
                Andross_8018D9C0(boss);
            } else {
                boss->fwork[0] = player->pos.x;
                boss->fwork[3] = player->pos.y + 500.0f;
                if (boss->timer_050 != 0) {
                    boss->fwork[6] = -4000.0f;
                    boss->fwork[8] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[7], 30.0f, 1.0f, 5.0f, 0);
                    boss->fwork[2] = 0.1f;
                    boss->fwork[5] = 0.1f;
                    Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 2.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 2.0f, 0);
                } else {
                    boss->unk_04C++;
                    boss->fwork[6] = -1400.0f;
                    boss->fwork[8] = 0.2f;
                    Math_SmoothStepToF(&boss->fwork[7], 200.0f, 1.0f, 40.0f, 0);
                    boss->fwork[2] = 0.05f;
                    boss->fwork[5] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[1], 2.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 2.0f, 1.0f, 1.0f, 0);
                    if (boss->unk_04C == 5) {
                        AUDIO_PLAY_SFX(0x1940306B, boss->sfxSource, 4);
                    }
                    boss->swork[7] = 1;
                    boss->fwork[14] = 100.0f;
                }
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C030244)) {
                    Andross_8018D9C0(boss);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C030244, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 6:
            if ((boss->swork[4] < 0) || (boss->swork[5] < 0)) {
                Andross_8018D9C0(boss);
            } else {
                if (boss->timer_050 == 1) {
                    AUDIO_PLAY_SFX(0x1940306C, boss->sfxSource, 4);
                }
                if (boss->timer_050 != 0) {
                    boss->fwork[6] = -4000.0f;
                    boss->fwork[8] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[7], 40.0f, 1.0f, 3.0f, 0);
                    boss->fwork[2] = 0.05f;
                    boss->fwork[5] = 0.05f;
                    Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 1.0f, 0);
                    boss->fwork[0] = player->pos.x;
                    boss->fwork[3] = player->pos.y + 300.0f;
                } else {
                    boss->unk_04C++;
                    boss->fwork[6] = -2000.0f;
                    boss->fwork[8] = 0.2f;
                    Math_SmoothStepToF(&boss->fwork[7], 50.0f, 1.0f, 10.0f, 0);
                    boss->fwork[2] = 0.1f;
                    boss->fwork[5] = 0.1f;
                    Math_SmoothStepToF(&boss->fwork[1], 10.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&boss->fwork[4], 10.0f, 1.0f, 1.0f, 0);
                    boss->swork[7] = 1;
                    if (boss->unk_04C > 18) {
                        Math_SmoothStepToF(&boss->fwork[11], 110.0f, 1.0f, 18.0f, 0);
                        Math_SmoothStepToF(&boss->fwork[12], 20.0f, 1.0f, 3.6f, 0);
                        Math_SmoothStepToF(&boss->fwork[13], 80.0f, 1.0f, 15.0f, 0);
                    }
                    if (boss->unk_04C == 25) {
                        AUDIO_PLAY_SFX(0x09008015, D_i6_801A67B8, 4);
                    }
                }
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C02EDA0)) {
                    Andross_8018D9C0(boss);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C02EDA0, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 7:
            if (boss->swork[5] < 0) {
                Andross_8018D9C0(boss);
            } else {
                if (boss->unk_04C == 48) {
                    AUDIO_PLAY_SFX(0x3103108B, boss->sfxSource, 4);
                }
                if (boss->unk_04C > 48) {
                    Andross_8018D0D8(boss);
                }
                if (boss->unk_04C > 45) {
                    Math_SmoothStepToF(&boss->fwork[20], 1.0f, 1.0f, 0.2f, 0.01f);
                    Math_SmoothStepToF(&boss->fwork[21], 1.0f, 0.5f, 0.15f, 0.01f);
                    if (((gGameFrameCount % 2) == 0)) {
                        gAmbientR = 200;
                        gAmbientG = 90;
                        gAmbientB = 255;
                    } else {
                        gAmbientR = 100;
                        gAmbientG = 45;
                        gAmbientB = 127;
                    }
                } else {
                    Math_SmoothStepToF(&boss->fwork[20], 0.15f, 1.0f, 0.15f, 0.01f);
                    Math_SmoothStepToF(&boss->fwork[21], 0.5f, 1.0f, 0.11f, 0.001f);
                }
                boss->fwork[0] = player->pos.x + 500.0f;
                boss->fwork[3] = player->pos.y + 750.0f;
                boss->fwork[6] = -5000.0f;
                boss->fwork[8] = 0.05f;
                Math_SmoothStepToF(&boss->fwork[7], 60.0f, 1.0f, 5.0f, 0);
                boss->fwork[2] = 0.05f;
                boss->fwork[5] = 0.05f;
                Math_SmoothStepToF(&boss->fwork[1], 5.0f, 1.0f, 2.0f, 0);
                Math_SmoothStepToF(&boss->fwork[4], 5.0f, 1.0f, 2.0f, 0);
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C018BC4)) {
                    boss->unk_04C = Animation_GetFrameCount(&D_ANDROSS_C018BC4) - 1;
                    if (boss->timer_050 == 0) {
                        Andross_8018D9C0(boss);
                    }
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C018BC4, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 12:
            if ((boss->swork[4] < 0) || (boss->swork[5] < 0)) {
                boss->state = 14;
                boss->unk_04C = 0;
                boss->fwork[9] = 0.0f;
            } else {
                boss->fwork[6] = -3000.0f;
                boss->fwork[8] = 0.05f;
                Math_SmoothStepToF(&boss->fwork[7], 40.0f, 1.0f, 2.0f, 0);
                boss->fwork[2] = 0.05f;
                boss->fwork[5] = 0.05f;
                Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
                Math_SmoothStepToF(&boss->fwork[4], 20.0f, 1.0f, 1.0f, 0);
                boss->fwork[0] = player->pos.x;
                boss->fwork[3] = player->pos.y;
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C025C00)) {
                    boss->unk_04C = Animation_GetFrameCount(&D_ANDROSS_C025C00) - 1;
                    if (boss->timer_050 == 0) {
                        Andross_8018D9C0(boss);
                    }
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C025C00, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 13:
            if ((boss->swork[4] < 0) || (boss->swork[5] < 0)) {
                boss->state = 14;
                boss->unk_04C = 0;
                boss->fwork[9] = 0.0f;
            } else {
                boss->fwork[6] = -3000.0f;
                boss->fwork[8] = 0.05f;
                Math_SmoothStepToF(&boss->fwork[7], 20.0f, 1.0f, 2.0f, 0);
                boss->fwork[2] = 0.05f;
                boss->fwork[5] = 0.05f;
                Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
                Math_SmoothStepToF(&boss->fwork[4], 20.0f, 1.0f, 1.0f, 0);
                boss->fwork[0] = player->pos.x;
                boss->fwork[3] = player->pos.y;
                Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C006F08)) {
                    boss->unk_04C = Animation_GetFrameCount(&D_ANDROSS_C006F08) - 1;
                    if (boss->timer_050 == 0) {
                        Andross_8018D9C0(boss);
                    }
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C006F08, boss->unk_04C, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 14:
            boss->fwork[6] = -3000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 20.0f, 1.0f, 2.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 20.0f, 1.0f, 1.0f, 0);
            boss->fwork[0] = player->pos.x;
            boss->fwork[3] = player->pos.y;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C002654)) {
                boss->unk_04C = 0;
                if (boss->timer_050 == 0) {
                    Andross_8018D9C0(boss);
                }
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C002654, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            break;
        case 15:
            if (boss->swork[8] == 1) {
                boss->fwork[6] = 100.0f;
            } else {
                boss->fwork[6] = -3000.0f;
            }
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 60.0f, 1.0f, 5.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 20.0f, 1.0f, 1.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[3] = 0.0f;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
            if (boss->unk_04C == 15) {
                AUDIO_PLAY_SFX(0x29022088, boss->sfxSource, 4);
            }
            if ((boss->unk_04C > 35) && (boss->unk_04C < 150) && ((boss->unk_04C % 32) == 0)) {
                AUDIO_PLAY_SFX(0x29022089, boss->sfxSource, 4);
                if (player->state_1C8 == PLAYERSTATE_1C8_11) {
                    D_Timer_80177BD0[0] = 10;
                }
            }
            if ((boss->unk_04C == 20) && (player->state_1C8 == PLAYERSTATE_1C8_11)) {
                player->unk_234 = 0;
                for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                    if (gEffects[i].obj.id == OBJ_EFFECT_396) {
                        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                    }
                }
            }
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C00DE48)) {
                boss->unk_04C = Animation_GetFrameCount(&D_ANDROSS_C00DE48) - 1;
                if (boss->timer_050 == 0) {
                    boss->state = 16;
                    boss->unk_04C = 0;
                    boss->timer_050 = 30;
                    boss->fwork[9] = 0.0f;
                }
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C00DE48, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            if ((boss->unk_04C == 45) && (boss->swork[8] == 2)) {
                boss->state = 18;
                boss->unk_04C = 0;
                boss->unk_044 = 0;
                boss->timer_050 = 40;
                boss->fwork[9] = 0.0f;
            }
            break;
        case 16:
            if (boss->swork[8] == 1) {
                boss->fwork[6] = 100.0f;
            } else {
                boss->fwork[6] = -3000.0f;
            }
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 50.0f, 1.0f, 2.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 20.0f, 1.0f, 1.0f, 0);
            boss->fwork[0] = player->pos.x;
            boss->fwork[3] = player->pos.y + 100.0f;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
            if (boss->timer_050 == 0) {
                boss->unk_04C++;
                if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C023B54)) {
                    boss->unk_04C = Animation_GetFrameCount(&D_ANDROSS_C023B54) - 1;
                    Andross_8018D9C0(boss);
                }
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C023B54, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            if (boss->unk_04C == 10) {
                AUDIO_PLAY_SFX(0x3140208A, boss->sfxSource, 4);
            }
            if ((boss->unk_04C == 13) && (player->state_1C8 == PLAYERSTATE_1C8_11)) {
                player->unk_234 = 1;
                player->unk_1D0 = 1;
                player->timer_1F8 = 60;
                player->timer_498 = 50;
                boss->swork[8] = 0;
                D_Timer_80177BD0[0] = 30;
                if (player->wings.rightState == 2) {
                    gRightWingHealth[0] = 0;
                    player->wings.rightState = 1;
                    Andross_8018C8D4(boss->obj.pos.x, boss->obj.pos.y - 200.0f, boss->obj.pos.z,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f), 10.0f, 8);
                }
                if (player->wings.leftState == 2) {
                    gLeftWingHealth[0] = 0;
                    player->wings.leftState = 1;
                    Andross_8018C8D4(boss->obj.pos.x, boss->obj.pos.y - 200.0f, boss->obj.pos.z,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f), 10.0f, 9);
                }
            }
            if (boss->unk_04C >= 10 && boss->unk_04C < 20) {
                for (i = 0; i < 10; i++) {
                    Andross_8018C8D4(boss->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                                     (boss->obj.pos.y - 200.0f) + RAND_FLOAT_CENTERED(100.0f), boss->obj.pos.z,
                                     RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT(5.0f) + 5.0f,
                                     RAND_INT(7.9));
                }
            }
            break;
        case 17:
            // FAKE!!
            if (1) {}
            if (1) {}
            if (1) {}
            if (1) {}
            Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 50.0f, 1.0f, 1.8f, 0.0f);
            boss->timer_056 = 50;

            if ((boss->timer_050 > 70) && (boss->timer_050 < 1000) && ((gGameFrameCount % 4) == 0)) {
                Andross_8018C734(gPlayer[0].camEye.x + RAND_FLOAT_CENTERED(3000.0f),
                                 gPlayer[0].camEye.y + RAND_FLOAT_CENTERED(3000.0f),
                                 gPlayer[0].camEye.z - D_ctx_80177D20, RAND_INT(7.9));
            }
            if (boss->timer_050 > 0) {
                playerShot = gPlayerShots;
                effect = gEffects;
                for (i = 0; i < 16; i++, playerShot++) {
                    Math_SmoothStepToF(&playerShot->obj.pos.x, boss->obj.pos.x, 0.5f, boss->fwork[16], 0);
                    Math_SmoothStepToF(&playerShot->obj.pos.y, boss->obj.pos.y - 100.0f, 0.5f, boss->fwork[16], 0);
                    Math_SmoothStepToF(&playerShot->vel.x, 0.0f, 0.9f, 5.0f, 0);
                    Math_SmoothStepToF(&playerShot->vel.y, 0.0f, 0.9f, 5.0f, 0);
                    if ((playerShot->obj.id == PLAYERSHOT_3) && (playerShot->obj.status == 1) &&
                        (playerShot->unk_5C == 0) && (fabsf(playerShot->obj.pos.x - boss->obj.pos.x) < 200.0f) &&
                        (fabsf(playerShot->obj.pos.y - (boss->obj.pos.y - 100.0f)) < 200.0f) &&
                        (fabsf(playerShot->obj.pos.z - (boss->obj.pos.z - 200.0f)) < 100.0f)) {
                        Object_Kill(&playerShot->obj, playerShot->sfxSource);
                        boss->state = 15;
                        boss->fwork[9] = 0.2f;
                        boss->unk_04C = 0;
                        boss->swork[8] = 2;
                        AUDIO_PLAY_SFX(0x1940306D, boss->sfxSource, 4);
                        break;
                    }
                }
                for (i = 0; i < ARRAY_COUNT(gEffects); i++, effect++) {
                    if ((effect->obj.status != OBJ_FREE) && (effect->obj.id != OBJ_EFFECT_396)) {
                        Math_SmoothStepToF(&effect->obj.pos.x, boss->obj.pos.x, 0.5f, boss->fwork[16], 0);
                        Math_SmoothStepToF(&effect->obj.pos.y, boss->obj.pos.y - 100.0f, 0.5f, boss->fwork[16], 0);
                        Math_SmoothStepToF(&effect->obj.pos.z, boss->obj.pos.z - 200.0f, 0.5f, boss->fwork[16], 0);
                        Math_SmoothStepToF(&effect->vel.x, 0.0f, 0.9f, 5.0f, 0);
                        Math_SmoothStepToF(&effect->vel.y, 0.0f, 0.9f, 5.0f, 0);
                        Math_SmoothStepToF(&effect->vel.z, 0.0f, 0.9f, 10.0f, 0);
                        if ((fabsf(effect->obj.pos.x - boss->obj.pos.x) < 200.0f) &&
                            (fabsf(effect->obj.pos.y - (boss->obj.pos.y - 100.0f)) < 200.0f) &&
                            (fabsf(effect->obj.pos.z - (boss->obj.pos.z - 200.0f)) < 100.0f)) {
                            Object_Kill(&effect->obj, effect->sfxSource);
                        }
                    }
                }
                Math_SmoothStepToF(&player->pos.x, boss->obj.pos.x, 0.1f, boss->fwork[16], 0);
                Math_SmoothStepToF(&player->pos.y, boss->obj.pos.y - 150.0f, 0.1f, boss->fwork[16], 0);
                Math_SmoothStepToF(&boss->fwork[16], 35.0f, 1.0f, 0.5f, 0);
                if (fabsf(player->unk_138 - boss->obj.pos.z) < 200.0f) {
                    boss->state = 15;
                    boss->swork[8] = 1;
                    boss->fwork[9] = 0.2f;
                    boss->unk_04C = 0;
                    if (player->state_1C8 == PLAYERSTATE_1C8_3) {
                        player->state_1C8 = PLAYERSTATE_1C8_11;
                        player->unk_1D0 = 0;
                    }
                    break;
                }
            }
            boss->fwork[8] = 0.1f;
            boss->fwork[2] = 0.1f;
            boss->fwork[5] = 0.1f;
            boss->fwork[6] = -300.0f;
            Math_SmoothStepToF(&boss->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 1.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[3] = 150.0f;
            Math_SmoothStepToF(&boss->fwork[7], 20.0f, 0.1f, 0.1f, 0);
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.01f, 0);
            if (boss->unk_04C == 10) {
                AUDIO_PLAY_SFX(0x31022087, boss->sfxSource, 4);
            }
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C0240D0)) {
                boss->unk_04C = 0;
                if (boss->timer_050 == 0) {
                    boss->state = 15;
                    boss->swork[8] = 0;
                    boss->fwork[9] = 0.0f;
                }
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C0240D0, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);

            break;
        case 18:
            boss->fwork[6] = -3000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 70.0f, 1.0f, 7.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 3.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[3] = 0.0f;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.05f, 0);
            switch (boss->unk_044) {
                case 0:
                    if (boss->timer_050 != 0) {
                        limbCount = Animation_GetFrameData(&D_ANDROSS_C00DE48, 45, spD0);
                        Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
                    } else {
                        boss->unk_044 = 1;
                        boss->timer_050 = 30;
                        boss->swork[9] = 20;
                        boss->fwork[9] = 0.0f;
                        func_8001CE28(0, boss->sfxSource);
                        boss->timer_05C = 50;
                    }
                    break;
                case 1:
                    if (boss->timer_050 != 0) {
                        limbCount = Animation_GetFrameData(&D_ANDROSS_C017430, 0, spD0);
                        Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
                    } else {
                        boss->unk_044 = 2;
                        boss->timer_050 = 70;
                        boss->fwork[9] = 0.0f;
                        AUDIO_PLAY_SFX(0x1940307C, boss->sfxSource, 4);
                    }
                    if (boss->timer_050 == 15) {
                        boss->swork[10] = 80;
                    }
                    break;
                case 2:
                    if (boss->timer_050 == 0) {
                        Andross_8018D9C0(boss);
                    }
                    boss->unk_04C++;
                    if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C00E598)) {
                        boss->unk_04C = 0;
                    }
                    limbCount = Animation_GetFrameData(&D_ANDROSS_C00E598, boss->unk_04C, spD0);
                    Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
                    break;
            }
            break;
        case 20:
            boss->fwork[6] = -3000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 70.0f, 1.0f, 7.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 50.0f, 1.0f, 5.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 50.0f, 1.0f, 5.0f, 0);
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C017050)) {
                Andross_8018D9C0(boss);
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C017050, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            break;
        case 30:
            boss->fwork[6] = -3000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 70.0f, 1.0f, 7.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 3.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[3] = 0.0f;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C017050)) {
                boss->unk_04C = 0;
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C017050, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007C484(boss->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     boss->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), boss->obj.pos.z, 0.0f, 0.0f,
                                     boss->vel.z, RAND_FLOAT(0.2f) + 0.2f, 0);
            }
            if (gCsFrameCount > 50) {
                func_effect_8007D0E0(boss->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     boss->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), boss->obj.pos.z,
                                     RAND_FLOAT(3.0f) + 3.0f);
            }

            gCsFrameCount++;

            switch (gCsFrameCount) {
                case 60:
                    boss->swork[17] = 1;
                    Andross_8018DA94(boss, &boss->vwork[19]);
                    break;
                case 70:
                    boss->swork[19] = 1;
                    Andross_8018DA94(boss, &boss->vwork[21]);
                    break;
                case 80:
                    boss->swork[11] = 1;
                    Andross_8018DA94(boss, &boss->vwork[13]);
                    break;
                case 90:
                    boss->swork[12] = 1;
                    Andross_8018DA94(boss, &boss->vwork[14]);
                    break;
                case 100:
                    boss->swork[22] = 1;
                    Andross_8018DA94(boss, &boss->vwork[24]);
                    break;
                case 110:
                    boss->swork[23] = 1;
                    Andross_8018DA94(boss, &boss->vwork[25]);
                    break;
                case 120:
                    boss->swork[18] = 1;
                    Andross_8018DA94(boss, &boss->vwork[19]);
                    boss->state = 9;
                    boss->health = 100;
                    boss->timer_050 = 50;
                    boss->fwork[9] = 0.0f;
                    AUDIO_PLAY_SFX(0x11030073, boss->sfxSource, 4);
                    AUDIO_PLAY_BGM(SEQ_ID_AND_BOSS | SEQ_FLAG);
                    break;
            }
            break;
        case 9:
            boss->fwork[6] = -3000.0f;
            if (boss->timer_050 == 0) {
                boss->state = 10;
                boss->timer_050 = 100;
            }
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 60.0f, 1.0f, 3.0f, 0);
            boss->fwork[0] = player->pos.x;
            boss->fwork[3] = player->pos.y;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C00208C)) {
                boss->unk_04C = 0;
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C00208C, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);

            func_effect_8007C484(boss->obj.pos.x + RAND_FLOAT_CENTERED(700.0f),
                                 boss->obj.pos.y + RAND_FLOAT_CENTERED(700.0f), boss->obj.pos.z, 0.0f, 0.0f,
                                 gPlayer[0].vel.z, RAND_FLOAT(0.15f) + 0.15f, 0);
            break;
        case 10:
            boss->fwork[6] = 0.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 60.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C00208C)) {
                boss->unk_04C = 0;
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C00208C, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);

            func_effect_8007C484(boss->obj.pos.x + RAND_FLOAT_CENTERED(700.0f),
                                 boss->obj.pos.y + RAND_FLOAT_CENTERED(700.0f), boss->obj.pos.z, 0.0f, 0.0f,
                                 gPlayer[0].vel.z, RAND_FLOAT(0.15f) + 0.15f, 0);
            if (boss->timer_050 == 0) {
                boss->state = 9;
                boss->timer_050 = 130;
            }
            break;
        case 31:
            boss->obj.rot.x += 1.0f;
            boss->obj.rot.y += 0.3f;
            boss->obj.rot.z += 0.7f;
            boss->fwork[6] = -3000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 70.0f, 1.0f, 7.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 3.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[3] = 0.0f;
            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007C484(boss->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     boss->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), boss->obj.pos.z, 0.0f, 0.0f,
                                     boss->vel.z, RAND_FLOAT(0.2f) + 0.2f, 0);
            }
            func_effect_8007D0E0(boss->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                 boss->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), boss->obj.pos.z,
                                 RAND_FLOAT(5.0f) + 5.0f);
            break;
        case 32:
            boss->fwork[6] = -3000.0f;
            boss->fwork[8] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[7], 70.0f, 1.0f, 7.0f, 0);
            boss->fwork[2] = 0.05f;
            boss->fwork[5] = 0.05f;
            Math_SmoothStepToF(&boss->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&boss->fwork[4], 30.0f, 1.0f, 3.0f, 0);
            boss->fwork[0] = 0.0f;
            boss->fwork[3] = 0.0f;
            Math_SmoothStepToF(&boss->fwork[9], 1.0f, 1.0f, 0.05f, 0);
            boss->unk_04C++;
            if (boss->unk_04C >= Animation_GetFrameCount(&D_ANDROSS_C017050)) {
                boss->unk_04C = 0;
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C017050, boss->unk_04C, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, boss->fwork[9], 100.0f, 0.0f);
            if (((gGameFrameCount % 2) == 0)) {
                func_effect_8007C484(boss->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     boss->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), boss->obj.pos.z, 0.0f, 0.0f,
                                     boss->vel.z, RAND_FLOAT(0.2f) + 0.2f, 0);
            }

            if (gCsFrameCount > 50) {
                func_effect_8007D0E0(boss->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     boss->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), boss->obj.pos.z,
                                     RAND_FLOAT(3.0f) + 3.0f);
            }

            gCsFrameCount++;

            switch (gCsFrameCount) {
                case 60:
                    boss->swork[17] = 2;
                    Andross_8018DA94(boss, &boss->vwork[19]);
                    break;
                case 70:
                    boss->swork[19] = 2;
                    Andross_8018DA94(boss, &boss->vwork[21]);
                    break;
                case 80:
                    boss->swork[14] = 2;
                    Andross_8018DA94(boss, &boss->vwork[16]);
                    break;
                case 90:
                    boss->swork[13] = 2;
                    Andross_8018DA94(boss, &boss->vwork[15]);
                    break;
                case 100:
                    Andross_8018DA94(boss, &boss->vwork[13]);
                    break;
                case 110:
                    Andross_8018DA94(boss, &boss->vwork[14]);
                    break;
                case 120:
                    boss->swork[20] = 2;
                    Andross_8018DA94(boss, &boss->vwork[22]);
                    break;
                case 130:
                    boss->swork[21] = 2;
                    Andross_8018DA94(boss, &boss->vwork[23]);
                    break;
                case 140:
                    boss->swork[22] = 2;
                    Andross_8018DA94(boss, &boss->vwork[24]);
                    break;
                case 150:
                    boss->swork[23] = 2;
                    Andross_8018DA94(boss, &boss->vwork[25]);
                    break;
                case 160:
                    boss->swork[16] = 1;
                    Andross_8018DA94(boss, &boss->vwork[18]);
                    break;
                case 170:
                    boss->swork[15] = 1;
                    Andross_8018DA94(boss, &boss->vwork[17]);
                    break;
                case 173:
                    func_effect_8007A6F0(&boss->obj.pos, 0x2940C00A);
                    func_effect_8007B344(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 100.0f, 4);
                    break;
                case 180:
                    boss1 = &gBosses[1];
                    Boss_Initialize(boss1);
                    boss1->obj.status = OBJ_INIT;
                    boss1->obj.id = OBJ_BOSS_321;
                    boss1->obj.pos.x = boss->obj.pos.x;
                    boss1->obj.pos.y = boss->obj.pos.y;
                    boss1->obj.pos.z = boss->obj.pos.z;
                    boss1->swork[1] = 100;
                    boss1->state = 10;
                    boss1->timer_050 = 180;
                    boss1->unk_3F8 = 5.0f;
                    Object_SetInfo(&boss1->info, boss1->obj.id);
                    Object_Kill(&boss->obj, boss->sfxSource);
                    D_ctx_80177AB0 = 3;
                    Andross_80189098(boss);
                    Radio_PlayMessage(gMsg_ID_19330, RCID_ANDROSS_RED);
                    break;
            }
            Math_SmoothStepToF(&D_bg_800C9C30, 0.0f, 1.0f, 0.3f, 0.0f);
            break;
    }
    if (boss->swork[4] >= 0) {
        boss->info.hitbox[13] = boss->vwork[0].z - boss->obj.pos.z;
        boss->info.hitbox[15] = boss->vwork[0].y - boss->obj.pos.y;
        boss->info.hitbox[17] = boss->vwork[0].x - boss->obj.pos.x;
        if (boss->swork[7] != 0) {
            boss->info.hitbox[14] = 280.0f;
            boss->info.hitbox[16] = 200.0f;
            boss->info.hitbox[18] = 200.0f;
        } else {
            boss->info.hitbox[14] = 100.0f;
            boss->info.hitbox[16] = 100.0f;
            boss->info.hitbox[18] = 100.0f;
        }
    } else {
        boss->info.hitbox[16] = 0.0f;
    }
    if (boss->swork[5] >= 0) {
        boss->info.hitbox[19] = boss->vwork[1].z - boss->obj.pos.z;
        boss->info.hitbox[21] = boss->vwork[1].y - boss->obj.pos.y;
        boss->info.hitbox[23] = boss->vwork[1].x - boss->obj.pos.x;
        if (boss->swork[7] != 0) {
            boss->info.hitbox[20] = 280.0f;
            boss->info.hitbox[22] = 200.0f;
            boss->info.hitbox[24] = 200.0f;
        } else {
            boss->info.hitbox[20] = 100.0f;
            boss->info.hitbox[22] = 100.0f;
            boss->info.hitbox[24] = 100.0f;
        }
    } else {
        boss->info.hitbox[22] = 0.0f;
    }
    boss->info.hitbox[1] = boss->vwork[2].z - boss->obj.pos.z;
    boss->info.hitbox[3] = boss->vwork[2].y - boss->obj.pos.y;
    boss->info.hitbox[5] = boss->vwork[2].x - boss->obj.pos.x;
    boss->info.hitbox[7] = boss->vwork[3].z - boss->obj.pos.z;
    boss->info.hitbox[9] = boss->vwork[3].y - boss->obj.pos.y;
    boss->info.hitbox[11] = boss->vwork[3].x - boss->obj.pos.x;
    if ((initialstate == 17) && (boss->state != 17)) {
        Audio_KillSfxBySourceAndId(boss->sfxSource, 0x31022087);
    }
    if ((initialstate == 7) && (boss->state != 7)) {
        Audio_KillSfxBySourceAndId(boss->sfxSource, 0x3103108B);
    }
}

static Vec3f D_i6_801A67C4 = { 40.0f, 0.0f, -10.0f };
static f32 D_i6_801A67D0 = 180.0f;
static f32 D_i6_801A67D4 = 0.0f;
static f32 D_i6_801A67D8 = 0.0f;
static Vec3f D_i6_801A67DC = { 40.0f, 0.0f, 10.0f };
static f32 D_i6_801A67E8 = 0.0f;
static f32 D_i6_801A67EC = 0.0f;
static f32 D_i6_801A67F0 = 0.0f;
static Vec3f D_i6_801A67F4 = { 0.0f, 0.0f, 0.0f };

bool Andross_801917F0(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Vec3f sp94;
    Vec3f sp88;
    f32 scale;
    Boss* boss = (Boss*) data;

    sp94 = D_i6_801A67F4;
    scale = 1.0f;
    if ((limbIndex >= 13) && (limbIndex <= 50)) {
        if (boss->state < 2) {
            *dList = NULL;
        } else {
            RCP_SetupDL(&gMasterDisp, 0x1D);
            gSPTexture(gMasterDisp++, 6600, 6600, 0, G_TX_RENDERTILE, G_ON);
            gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
            if (((limbIndex >= 23) && (limbIndex <= 32)) || (limbIndex == 50)) {
                if (boss->swork[5] < 0) {
                    *dList = NULL;
                } else if ((boss->swork[3] % 2) != 0) {
                    RCP_SetupDL(&gMasterDisp, 0x1B);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            } else if (boss->swork[4] < 0) {
                *dList = NULL;
            } else if ((boss->swork[2] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, 0x1B);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
        }
    } else if ((boss->timer_05C % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, 0x1D);
    } else {
        RCP_SetupDL(&gMasterDisp, 0x1B);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    switch (limbIndex) {
        case 59:
            if (boss->swork[18] == 1) {
                *dList = D_ANDROSS_C004860;
            }
            if (boss->swork[18] == 2) {
                *dList = NULL;
            }
            break;
        case 3:
            rot->z -= boss->vwork[4].x;
            rot->y -= boss->vwork[4].y;
            if ((boss->swork[0] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, 0x1B);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (boss->swork[11] != 0) {
                *dList = D_ANDROSS_C0043D0;
                RCP_SetupDL(&gMasterDisp, 0x15);
            }
            scale = boss->fwork[17];
            break;
        case 4:
            rot->z -= boss->vwork[5].x;
            rot->y -= boss->vwork[5].y;
            if ((boss->swork[1] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, 0x1B);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
            if (boss->swork[12] != 0) {
                *dList = D_ANDROSS_C015740;
                RCP_SetupDL(&gMasterDisp, 0x15);
            }
            scale = boss->fwork[17];
            break;
        case 5:
            if (boss->swork[17] == 1) {
                *dList = D_ANDROSS_C002B20;
            }
            if (boss->swork[17] == 2) {
                *dList = NULL;
            }
            scale = boss->fwork[17];
            break;
        case 6:
            if (boss->swork[19] == 1) {
                *dList = D_ANDROSS_C002F00;
            }
            if (boss->swork[19] == 2) {
                *dList = NULL;
            }
            scale = boss->fwork[17];
            break;
        case 1:
            if (boss->swork[14] != 0) {
                *dList = NULL;
            }
            break;
        case 2:
            if (boss->swork[13] != 0) {
                *dList = NULL;
            }
            break;
        case 7:
            if (boss->swork[20] != 0) {
                *dList = NULL;
            }
            scale = boss->fwork[18];
            break;
        case 8:
            if (boss->swork[21] != 0) {
                *dList = NULL;
            }
            scale = boss->fwork[18];
            break;
        case 9:
            if (boss->swork[23] != 0) {
                *dList = NULL;
            }
            scale = boss->fwork[18];
            break;
        case 10:
            if (boss->swork[22] != 0) {
                *dList = NULL;
            }
            scale = boss->fwork[18];
            break;
        case 11:
            if (boss->swork[16] != 0) {
                *dList = NULL;
            }
            break;
        case 12:
            if (boss->swork[15] != 0) {
                *dList = NULL;
            }
            break;
        case 49:
            pos->x -= boss->fwork[11];
            pos->y += boss->fwork[12];
            pos->z += boss->fwork[13];
            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, 1);
            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, 1);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, 1);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, 1);
            if (*dList != NULL) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Push(&gCalcMatrix);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);
                RCP_SetupDL(&gMasterDisp, 0x29);
                switch (gGameFrameCount % 4U) {
                    case 0:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                        break;
                    case 1:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 0, 255);
                        break;
                    case 2:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 255, 255);
                        break;
                    case 3:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                        break;
                }
                Matrix_Translate(gGfxMatrix, D_i6_801A67DC.x, D_i6_801A67DC.y, D_i6_801A67DC.z, 1);
                Matrix_RotateZ(gGfxMatrix, D_i6_801A67F0 * M_DTOR, 1);
                Matrix_RotateY(gGfxMatrix, D_i6_801A67EC * M_DTOR, 1);
                Matrix_RotateX(gGfxMatrix, D_i6_801A67E8 * M_DTOR, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ANDROSS_C022520);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gCalcMatrix);
            }
            return true;
        case 50:
            pos->x -= boss->fwork[11];
            pos->y += boss->fwork[12];
            pos->z -= boss->fwork[13];
            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, 1);
            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, 1);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, 1);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, 1);
            if (*dList != NULL) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Push(&gCalcMatrix);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);
                RCP_SetupDL(&gMasterDisp, 0x29);
                switch (gGameFrameCount % 4U) {
                    case 0:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                        break;
                    case 1:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 255, 0, 255);
                        break;
                    case 2:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 255, 255);
                        break;
                    case 3:
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
                        break;
                }
                Matrix_Translate(gGfxMatrix, D_i6_801A67C4.x, D_i6_801A67C4.y, D_i6_801A67C4.z, 1);
                Matrix_RotateZ(gGfxMatrix, D_i6_801A67D8 * M_DTOR, 1);
                Matrix_RotateY(gGfxMatrix, D_i6_801A67D4 * M_DTOR, 1);
                Matrix_RotateX(gGfxMatrix, D_i6_801A67D0 * M_DTOR, 1);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ANDROSS_C022520);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gCalcMatrix);
            }
            return true;
        default:
            break;
    }

    Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, 1);
    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, 1);
    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, 1);
    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, 1);
    Matrix_Push(&gCalcMatrix);
    Matrix_Scale(gCalcMatrix, scale, scale, scale, 1);
    if (*dList != NULL) {
        Matrix_MultVec3f(gCalcMatrix, &sp94, &sp88);
        func_edisplay_8005F670(&sp88);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, *dList);
    }
    Matrix_Pop(&gCalcMatrix);
    return true;
}

void Andross_801924B4(s32 limbIndex, Vec3f* rot, void* data) {
    Vec3f sp94 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp88 = { 33.0f, 0.0f, 0.0f };
    Vec3f sp7C = { 20.0f, 0.0f, 0.0f };
    Vec3f sp70 = { -16.0f, 8.0f, 20.0f };
    Vec3f sp64 = { -16.0f, -8.0f, -20.0f };
    Vec3f sp58 = { 40.0f, -22.0f, 4.0f };
    Vec3f sp4C = { 40.0f, -22.0f, -4.0f };
    Vec3f sp40 = { 10.0f, -2.0f, 2.0f };
    Vec3f sp34 = { 10.0f, -2.0f, 2.0f };
    Vec3f sp28 = { -80.0f, 0.0f, 0.0f };
    Boss* boss = (Boss*) data;

    switch (limbIndex) {
        case 3:
            Matrix_MultVec3f(gCalcMatrix, &sp7C, &boss->vwork[2]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &sp7C, &boss->vwork[3]);
            break;
        case 5:
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &boss->vwork[6]);
            Matrix_MultVec3f(gCalcMatrix, &sp58, &boss->vwork[7]);
            break;
        case 12:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &boss->vwork[9]);
            break;
        case 11:
            Matrix_MultVec3f(gCalcMatrix, &sp40, &boss->vwork[8]);
            break;
        case 20:
            Matrix_MultVec3f(gCalcMatrix, &sp70, &boss->vwork[0]);
            break;
        case 28:
            Matrix_MultVec3f(gCalcMatrix, &sp64, &boss->vwork[1]);
            break;
        case 25:
            Matrix_MultVec3f(gCalcMatrix, &sp88, &boss->vwork[10]);
            break;
    }
    if (boss->state >= 30) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[16]);
                return;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[15]);
                return;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[13]);
                return;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[14]);
                return;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[19]);
                return;
            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[21]);
                return;
            case 7:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[22]);
                return;
            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[23]);
                return;
            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[25]);
                return;
            case 10:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &boss->vwork[24]);
                return;
            case 11:
                Matrix_MultVec3f(gCalcMatrix, &sp28, &boss->vwork[18]);
                return;
            case 12:
                Matrix_MultVec3f(gCalcMatrix, &sp28, &boss->vwork[17]);
                break;
        }
    }
}

void Andross_801928C8(Boss* boss) {

    if (boss->timer_058 == 0) {
        // FAKE
        if (1) {}
        PRINTF("Enm->count %d\n");
        if (boss->state < 2) {
            Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, D_i6_801A7F5C, D_i6_801A7F64, D_i6_801A7F6C,
                               D_i6_801A7F74, D_i6_801A7F7C, D_i6_801A8430);
        }
        Matrix_Scale(gCalcMatrix, 10.0f, 10.0f, 10.0f, 1);
        Animation_DrawSkeleton(2, D_ANDROSS_C01CC3C, D_i6_801A7F80, Andross_801917F0, Andross_801924B4, boss,
                               gCalcMatrix);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        if (boss->fwork[20] > 0.05f) {
            Matrix_Translate(gGfxMatrix, boss->vwork[10].x, boss->vwork[10].y, boss->vwork[10].z + D_ctx_80177D20, 1);
            if (boss->fwork[21] > 0.05f) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL(&gMasterDisp, 0x43);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
                gDPSetEnvColor(gMasterDisp++, 255, 0, 128, 192);
                Matrix_Scale(gGfxMatrix, boss->fwork[21] * 7.0f, boss->fwork[21] * 7.0f, boss->fwork[21] * 7.0f, 1);
                if ((gGameFrameCount % 2) != 0) {
                    Matrix_Scale(gGfxMatrix, 1.1f, 1.1f, 1.1f, 1);
                }
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_1024AC0);
                Matrix_Pop(&gGfxMatrix);
            }
            Matrix_Scale(gGfxMatrix, boss->fwork[20] * 10.0f, boss->fwork[20] * 10.0f, boss->fwork[20] * 10.0f, 1);
            Matrix_RotateZ(gGfxMatrix, boss->fwork[19] * M_DTOR, 1);
            RCP_SetupDL(&gMasterDisp, 0x40);
            if ((gGameFrameCount % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 30);
            }
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, 0.0f, 1);
            Matrix_RotateX(gGfxMatrix, 15.0f * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 200.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, 120.0f * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, 15.0f * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 200.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, 240.0f * M_DTOR, 1);
            Matrix_RotateX(gGfxMatrix, 15.0f * M_DTOR, 1);
            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, 1);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 200.0f, 1);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
            Matrix_Pop(&gGfxMatrix);
        }
        Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR,
                           gAmbientG, gAmbientB);
    }
}

void Andross_80192E94(Actor* actor) {
    Actor* otherActor;
    s32 i;

    switch (actor->state) {
        case 0:
            if (actor->obj.pos.x >= 0.0f) {
                actor->state = 1;
            } else {
                actor->state = 2;
            }
            actor->vwork[0].x = actor->obj.pos.x;
            actor->vwork[0].y = actor->obj.pos.y - 300.0f;
            actor->vwork[0].z = actor->obj.pos.z;
            actor->health = 30;
            actor->unk_0F4.z = actor->obj.rot.z;
            AUDIO_PLAY_SFX(0x11000028, actor->sfxSource, 0);
            break;
        case 1:
            otherActor = gActors;
            for (i = 0; i < 60; i++, otherActor++) {
                if ((i != actor->index) && (otherActor->obj.status == OBJ_ACTIVE) &&
                    (otherActor->obj.id == OBJ_ACTOR_285) &&
                    (fabsf(otherActor->obj.pos.z - actor->obj.pos.z) < 200.0f)) {
                    actor->timer_0BC = 5;
                    otherActor->timer_0BC = 5;
                    gTexturedLines[actor->index].mode = 50;
                    gTexturedLines[actor->index].unk_28 = 1.0f;
                    gTexturedLines[actor->index].unk_04.x = actor->obj.pos.x;
                    gTexturedLines[actor->index].unk_04.y = actor->obj.pos.y;
                    gTexturedLines[actor->index].unk_04.z = actor->obj.pos.z;
                    gTexturedLines[actor->index].unk_10.x = otherActor->obj.pos.x;
                    gTexturedLines[actor->index].unk_10.y = otherActor->obj.pos.y;
                    gTexturedLines[actor->index].unk_10.z = otherActor->obj.pos.z;
                    gTexturedLines[actor->index].timer = 3;
                    break;
                }
            }
            /* fallthrough */
        case 2:
            actor->obj.rot.z = actor->unk_0F4.z + D_Andross_801A7F68;
            Matrix_RotateZ(gCalcMatrix, M_DTOR * D_Andross_801A7F68, 0);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, actor->vwork, &actor->obj.pos);
            actor->obj.pos.y += 300.0f;
            break;
    }

    if (actor->unk_0D0 != 0) {
        actor->unk_0D0 = 0;
        actor->health -= actor->damage;
        if (actor->health <= 0) {
            func_effect_8007D0E0(actor->obj.pos.x, actor->obj.pos.y, actor->obj.pos.z, 5.0f);
            for (i = 0; i < 7; i++) {
                func_effect_80079618(RAND_FLOAT_CENTERED(10.0f) + actor->obj.pos.x,
                                     RAND_FLOAT_CENTERED(10.0f) + actor->obj.pos.y, actor->obj.pos.z,
                                     RAND_FLOAT(0.5f) + 0.5f);
            }
            func_effect_8007A6F0(&actor->obj.pos, 0x2903A008);
            Object_Kill(&actor->obj, actor->sfxSource);
        }
    }
}

void Andross_80193244(Actor* actor) {

    gSPDisplayList(gMasterDisp++, D_VE2_6007E20);
    if (actor->timer_0BC != 0) {
        f32 scale;
        u8 alpha;

        scale = 2.5f;
        alpha = 16;
        if ((gGameFrameCount % 2) != 0) {
            alpha = 64;
            scale *= 1.2f;
        }
        Matrix_Scale(gGfxMatrix, scale, scale, scale, 1);
        Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, 0x43);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, alpha);
        gDPSetEnvColor(gMasterDisp++, 255, 128, 128, alpha);
        gSPDisplayList(gMasterDisp++, D_1024AC0);
    }
}

void Andross_80193380(Object_80* obj80) {

    switch (obj80->state) {
        case 0:
            if (fabsf(obj80->obj.pos.z - gPlayer[0].unk_138) < 1800.0f) {
                obj80->state = 1;
                obj80->info.hitbox = LOAD_ASSET(D_ANDROSS_C038AC4);
            }
            break;
        case 1:
            obj80->info.hitbox[7] = -130.0f - (obj80->unk_44 * 1.6f);
            obj80->info.hitbox[17] = -130.0f - (obj80->unk_44 * 1.6f);
            obj80->info.hitbox[27] = -130.0f - (obj80->unk_44 * 1.6f);
            obj80->unk_44 += 2;
            if (obj80->unk_44 >= Animation_GetFrameCount(&D_VE2_6014658)) {
                obj80->unk_44 = Animation_GetFrameCount(&D_VE2_6014658) - 1;
            }
            break;
    }
    obj80->obj.rot.z = D_Andross_801A7F68;
}

bool Andross_801934EC(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex == 13) {
        *dList = NULL;
    }
    return false;
}

void Andross_8019350C(Object_80* obj80) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&D_VE2_6014658, obj80->unk_44, frameTable);
    Animation_DrawSkeleton(1, D_VE2_6014844, frameTable, Andross_801934EC, NULL, NULL, &gIdentityMatrix);
}

void Andross_8019356C(Object_80* obj80) {
    obj80->obj.rot.z = D_Andross_801A7F68;
    obj80->obj.pos.z += obj80->unk_60;
    if (obj80->timer_4C == 1) {
        Object_Kill(&obj80->obj, obj80->sfxSource);
    }
}

bool Andross_801935B4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    if (limbIndex != 13) {
        *dList = NULL;
    }
    return false;
}

void Andross_801935D4(Object_80* obj80) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&D_VE2_6014658, obj80->unk_44, frameTable);
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    Animation_DrawSkeleton(1, D_VE2_6014844, frameTable, Andross_801935B4, NULL, NULL, &gIdentityMatrix);
}

void Andross_80193668(Object_80* obj80, f32 xPos, f32 yPos, f32 zPos, s32 arg4) {
    Object_80_Initialize(obj80);
    obj80->obj.status = OBJ_ACTIVE;
    obj80->obj.id = OBJ_80_131;
    obj80->obj.pos.x = xPos;
    obj80->obj.pos.y = yPos;
    obj80->obj.pos.z = zPos;
    obj80->unk_60 = -40.0f;
    Object_SetInfo(&obj80->info, obj80->obj.id);
    obj80->timer_4C = (arg4 * 50) + 100;
    obj80->info.unk_10 = 100000.0f;
}

void Andross_80193710(void) {
    Actor* actor;
    Object_58* obj58;
    Boss* boss;
    s32 i;

    gLevelObjects = LOAD_ASSET(gLevelObjectInits[gCurrentLevel]);

    for (obj58 = gObjects58, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if (gLevelObjects[i].id <= OBJ_80_160) {
            Object_58_Initialize(obj58);
            obj58->obj.status = OBJ_ACTIVE;
            obj58->obj.id = gLevelObjects[i].id;
            obj58->sfxSource[0] = obj58->obj.pos.x = gLevelObjects[i].xPos;
            obj58->sfxSource[1] = obj58->obj.pos.y = gLevelObjects[i].yPos;
            obj58->sfxSource[2] = obj58->obj.pos.z = -gLevelObjects[i].zPos1;
            obj58->unk_54 = obj58->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&obj58->info, obj58->obj.id);
            obj58++;
        }
    }

    for (actor = &gActors[30], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id < 0) {
            break;
        }

        if ((gLevelObjects[i].id >= OBJ_ACTOR_176) && (gLevelObjects[i].id <= OBJ_ACTOR_SUPPLIES)) {
            Actor_Initialize(actor);
            actor->obj.status = OBJ_INIT;
            actor->obj.id = gLevelObjects[i].id;
            actor->fwork[10] = actor->obj.pos.x = gLevelObjects[i].xPos;
            actor->fwork[11] = actor->obj.pos.y = gLevelObjects[i].yPos;
            actor->fwork[12] = actor->obj.pos.z = -gLevelObjects[i].zPos1;
            actor->fwork[13] = actor->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&actor->info, actor->obj.id);
            actor++;
        }
    }

    boss = &gBosses[0];
    Boss_Initialize(boss);
    boss->obj.status = OBJ_INIT;
    boss->obj.id = OBJ_BOSS_312;
    Object_SetInfo(&boss->info, boss->obj.id);
}

void Andross_801939A0(s32 actorIndex) {
    Actor* actor = &gActors[actorIndex];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = gPlayer[0].camAt.y;
    actor->obj.pos.z = 0.0f;
    actor->iwork[11] = 1;
    actor->unk_0F4.x = 90.0f;
    actor->fwork[0] = 50.0f;
    actor->fwork[1] = 6.5f;
    if (actorIndex == 10) {
        actor->iwork[14] = 1;
    }
    if (actorIndex == 1) {
        actor->state = 1;
        actor->unk_046 = 255;
        actor->unk_0B6 = 1000;
    }
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
    AUDIO_PLAY_SFX(0x09000002, actor->sfxSource, 0);
}

static Vec3f D_i6_801A6878[4] = {
    { 1500.0f, 15000.0f, 0.0f },
    { 0.0f, 15000.0f, -600.0f },
    { -400.0f, 14950.0f, 0.0f },
    { 500.0f, 14930.0f, -300.0f },
};

void Andross_80193AE4(s32 actorIndex) {
    Actor* actor = &gActors[actorIndex];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_195;
    actor->obj.pos.x = D_i6_801A6878[actorIndex].x;
    actor->obj.pos.y = D_i6_801A6878[actorIndex].y;
    actor->obj.pos.z = D_i6_801A6878[actorIndex].z;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (actorIndex == 0) {
        actor->state = 200;
        actor->unk_0B6 = 1;
        AUDIO_PLAY_SFX(0x11030010, actor->sfxSource, 0);
        return;
    }
    actor->iwork[11] = 1;
    actor->fwork[7] = RAND_FLOAT(360.0f);
    actor->fwork[8] = RAND_FLOAT(360.0f);
    actor->state = 100;
    AUDIO_PLAY_SFX(0x3100000C, actor->sfxSource, 4);
}

//! @bug This references a variable in another overlay, causing undefined behavior.
//! In US v1.1, that address contains the store instruction for player->vel.y = vel.y; in Venom2_80196BF8. Setting this
//! to nop is harmless, as the overlay will be unloaded next frame.
extern s32 D_ending_80196D00;

f32 D_i6_801A7F40;
f32 D_i6_801A7F44;
f32 D_i6_801A7F48;
f32 D_i6_801A7F4C;
f32 D_i6_801A7F50;
f32 D_i6_801A7F54;

void Andross_80193C4C(Player* player) {
    s32 i;
    s32 sp90;
    f32 sp8C;
    Boss* boss = &gBosses[0];
    f32 sp84;
    f32 sp80;
    Vec3f sp74;
    Vec3f sp68;
    s32 temp_v0_2;

    Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 1.0f, 0.01f, 0.0f);
    player->wings.unk_04 = player->wings.unk_08 = player->wings.unk_0C = player->wings.unk_10 = 0.0f;
    switch (player->unk_1D0) {
        case 0:
            gCsFrameCount = 0;
            player->wings.unk_2C = 1;
            D_ctx_80177A48[0] = 0.0f;
            if (player->unk_4D8 > 180.0f) {
                player->unk_4D8 -= 360.0f;
            }
            player->unk_1D0++;
            player->timer_1F8 = 50;
            player->vel.z = -40.0f;
            /* fallthrough */
        case 1:
            Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&boss->vel.z, -40.0f, 1.0f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_0E8, 0.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&player->vel.x, 0.0f, 1.0f, 3.0f, 0.0f);
            Math_SmoothStepToF(&player->vel.y, 0.0f, 1.0f, 3.0f, 0.0f);
            Math_SmoothStepToF(&player->camEye.x, player->pos.x, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->camEye.y, player->pos.y + 30.0f, 0.1f, 15.0f, 0.0f);
            if (player->timer_1F8 == 0) {
                player->pos.y += SIN_DEG(player->unk_0E4) * 15.0f;
                Math_SmoothStepToF(&player->unk_0E4, 180.0f, 0.1f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->vel.z, 40.0f, 1.0f, 2.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->unk_08C, 0.0f, 1.0f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->unk_0E4, 0.0f, 0.1f, 10.0f, 0.0f);
            }
            player->camEye.z += player->vel.z * 0.5f;
            switch (gCsFrameCount) {
                case 80:
                    func_effect_8007A568(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f);
                    func_effect_8007A6F0(&boss->obj.pos, 0x2940C00A);
                    /* fallthrough */
                case 85:
                case 90:
                    func_effect_8007B344(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 250.0f, 6);
                    break;
                case 86:
                    Object_Kill(&boss->obj, boss->sfxSource);
                    D_ctx_80177AB0 = 0;
                    break;
                case 111:
                    player->unk_1D0 = 2;
                    AUDIO_PLAY_SFX(0x09000002, player->sfxSource, 0);
                    player->unk_190 = player->unk_194 = 7.0f;
                    D_ctx_80177A48[0] = 0.0f;
                    D_ctx_80177A48[1] = 0.0f;
                    D_ctx_80177A48[2] = 0.5f;
                    D_ctx_80177A48[3] = 1000.0f;
                    D_ctx_80177A48[4] = D_ctx_80177A48[5] = D_ctx_80177A48[6] = D_ctx_80177A48[7] = 0.0f;
                    D_ctx_80177A48[8] = 1.5f;
                    gCsFrameCount = 0;
                    break;
            }
            gCsCamAtX = gBosses[0].obj.pos.x;
            gCsCamAtY = gBosses[0].obj.pos.y;
            gCsCamAtZ = gBosses[0].obj.pos.z + D_ctx_80177D20;
            Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 3.0f, 0.0f);
            break;
        case 2:
            player->unk_190 = D_ctx_80177A48[8];
            sp90 = 0;
            sp68.x = RAND_FLOAT_CENTERED(150.0f);
            sp68.y = RAND_FLOAT_CENTERED(150.0f);
            sp68.z = 0.0f;
            if (gCsFrameCount == 50) {
                AUDIO_PLAY_SFX(0x11403071, player->sfxSource, 0);
                Audio_SetBaseSfxReverb(0);
            }
            if (gCsFrameCount > 40) {
                sp90 = 1;
            }
            if (gCsFrameCount < 30) {
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.5f, 1.0f, 0.05f, 0.0f);
            } else if (gCsFrameCount <= 150) {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 300.0f, 0.1f, D_ctx_80177A48[5], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.95f, 1.0f, 0.05f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 300.0f, 0.1f, 5.0f, 0.0f);
                if (gCsFrameCount == 150) {
                    D_ctx_80177A48[5] = 0.0f;
                }
            } else {
                Math_SmoothStepToF(&D_ctx_80177A48[1], 0.0f, 0.1f, D_ctx_80177A48[5], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[2], 0.85f, 1.0f, 0.01f, 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[3], 200.0f, 0.1f, 5.0f, 0.0f);
                D_ctx_80177A48[4] += 4.5f;
                D_ctx_80177AB0 = 2;
                Matrix_RotateZ(gCalcMatrix, 2.0f * RAND_FLOAT(M_PI), 0);
                sp74.x = RAND_FLOAT(50.0f) + 120.0f;
                sp74.y = 0.0f;
                sp74.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
            }
            Math_SmoothStepToF(&D_ctx_80177A48[5], 3.0f, 1.0f, 0.05f, 0.0f);
            player->camEye.z += player->vel.z * D_ctx_80177A48[2];
            if (gCsFrameCount > 230) {
                player->unk_08C -= 7.0f;
            }
            if (gCsFrameCount > 230) {
                Math_SmoothStepToF(&D_ctx_80177A48[7], 3.0f, 1.0f, 0.1f, 0.0f);
                player->unk_034 -= D_ctx_80177A48[7];
            }

            for (i = 0; i < sp90; i++) {
                func_effect_8007797C(player->pos.x + sp68.x, player->pos.y + sp68.y,
                                     player->pos.z - (D_ctx_80177A48[3] + D_ctx_80177A48[4]), 0.0f, 0.0f, 50.0f,
                                     RAND_FLOAT(2.5f) + 2.5f);
            }

            Math_SmoothStepToF(&player->camEye.x, D_ctx_80177A48[1] + player->pos.x, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->camEye.y, player->pos.y + 30.0f, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->unk_0EC, -180.0f, 0.02f, D_ctx_80177A48[6], 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[6], 3.0f, 1.0f, 0.05f, 0.0f);
            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->unk_138 + D_ctx_80177D20;
            if (gCsFrameCount > 200) {
                player->unk_25C += 0.03f;
                if (player->unk_25C > 0.6f) {
                    player->unk_25C = 0.6f;
                }
                Math_SmoothStepToF(&player->unk_034, 3.0f, 0.5f, 0.1f, 0.0f);
                Math_SmoothStepToF(D_ctx_801779A8, 70.0f, 1.0f, 2.0f, 0.0f);
            }

            switch (gCsFrameCount) {
                case 60:
                    for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                        if ((gEffects[i].obj.id == OBJ_EFFECT_383) && (gEffects[i].obj.status == OBJ_ACTIVE)) {
                            Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                            break;
                        }
                    }
                    break;
                case 25:
                    for (i = 0; i < 12; i++) {
                        Andross_80193668(&gObjects80[i], player->pos.x, player->pos.y,
                                         (player->camEye.z - D_ctx_80177D20) + (2195.0f * i), i);
                    }
                    break;
                case 150:
                    AUDIO_PLAY_SFX(0x1900602A, gDefaultSfxSource, 0);
                    break;
                case 340:
                    Audio_KillSfxBySourceAndId(player->sfxSource, 0x11403071);
                    Audio_SetBaseSfxReverb(0);
                    D_play_800D2F68 = 0;
                    gBlurAlpha = 255;
                    gCurrentLevel = LEVEL_VENOM_2;
                    gLevelStage = 1;
                    gLevelMode = LEVELMODE_ALL_RANGE;
                    player->unk_1D0 = 3;
                    player->unk_144 = D_ctx_80177D20 = 0.0f;
                    D_ctx_80177AB0 = D_ctx_80177A98 = 1;
                    player->camEye.x = 1200.0f;
                    player->camEye.z = 1200.0f;
                    player->camEye.y = 1800.0f;
                    gCsCamAtX = 0.0f;
                    gCsCamAtY = 620.0f;
                    gCsCamAtZ = 0.0f;
                    player->unk_034 = 0.0f;
                    player->unk_234 = 0;
                    D_ctx_80177A48[0] = 1.0f;
                    func_play_800A6148();
                    gObjects58 = Memory_Allocate(200 * sizeof(Object_58));
                    for (i = 0; i < 200; i++) {
                        gObjects58[i].obj.status = OBJ_FREE;
                    }
                    Andross_80193710();
                    D_ctx_8017782C = 1;
                    func_play_800A594C();
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                    player->timer_1F8 = 2;
                    gCsFrameCount = 0;
                    D_ctx_80177A48[1] = 0.0f;
                    break;
            }
            break;
        case 3:
            if (player->timer_1F8 == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            } else {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            }

            if ((gCsFrameCount == 20) && (D_play_800D2F68 != 0)) {
                Andross_801939A0(1);
            }
            if (gCsFrameCount == 40) {
                Andross_801939A0(10);
                AUDIO_PLAY_SFX(0x2940F026, boss->sfxSource, 4);
                gCameraShake = 30;
                gOverlayStage = 1;
                D_Timer_80177BD0[0] = 30;
            }
            if (gCsFrameCount > 40) {
                for (i = 0; i < 3; i++) {
                    func_effect_8007797C(boss->obj.pos.x + RAND_FLOAT_CENTERED(150.0f), boss->obj.pos.y + 500.0f,
                                         boss->obj.pos.z + RAND_FLOAT_CENTERED(150.0f), RAND_FLOAT_CENTERED(10.0f),
                                         60.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.5f) + 5.5f);
                }
                Math_SmoothStepToF(&gCsCamAtY, gActors[10].obj.pos.y, 1.0f, D_ctx_80177A48[1], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], 1000.0f, 1.0f, 5.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->camEye.z, 1640.0f, 0.05f, 50.0f, 0.0f);
                Math_SmoothStepToF(&player->camEye.y, 110.0f, 0.05f, 50.0f, 0.0f);
                Math_SmoothStepToF(&player->camEye.x, 0.0f, 0.05f, 50.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, 630.0f, 0.05f, 50.0f, 0.0f);
            }

            if (gCsFrameCount == 70) {
                AUDIO_PLAY_BGM(SEQ_ID_VE_CLEAR | SEQ_FLAG);
            }
            if (gCsFrameCount == 150) {
                player->unk_1D0++;
                D_ctx_80177A48[0] = 1.0f;
                D_ctx_80177A48[1] = 1000.0f;
                D_ctx_80177A48[2] = 0;
                D_ctx_80177A48[3] = 1.0f;
                gActors[10].obj.pos.y = 1500.0f;
                gActors[10].unk_0F4.z = 180.0f;
                D_ctx_80177AB0 = 0;
                gFogFar = 1030;
                D_i6_801A7F40 = gLight1R;
                D_i6_801A7F44 = gLight1G;
                D_i6_801A7F48 = gLight1B;
                D_i6_801A7F4C = gAmbientR;
                D_i6_801A7F50 = gAmbientG;
                D_i6_801A7F54 = gAmbientB;
                D_ctx_801784D4 = -50.0f;
                gNextPlanetPath = 1;
                for (i = 0; i < 200; i++) {
                    gObjects58[i].obj.status = OBJ_FREE;
                }
            }
            break;
        case 4:
            player->unk_034 += D_ctx_80177A48[3];
            if (gCsFrameCount > 190) {
                Math_SmoothStepToF(&D_ctx_80177A48[3], 0.3f, 0.05f, 0.02f, 0.0f);
            }
            if (gCsFrameCount > 205) {
                Math_SmoothStepToF(&D_i6_801A7F40, 130.0f, 1.0f, 10.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F44, 160.0f, 1.0f, 10.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F48, 80.0f, 1.0f, 10.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F4C, 10.0f, 1.0f, 5.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F50, 10.0f, 1.0f, 5.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F54, 10.0f, 1.0f, 5.0f, 0.0f);
            }
            gLight1R = D_i6_801A7F40;
            gLight1G = D_i6_801A7F44;
            gLight1B = D_i6_801A7F48;
            gAmbientR = D_i6_801A7F4C;
            gAmbientG = D_i6_801A7F50;
            gAmbientB = D_i6_801A7F54;
            Math_SmoothStepToF(&D_ctx_80177A48[1], -5000.0f, 0.05f, 15.0f, 0.0f);
            player->camEye.x = gActors[10].obj.pos.x + 50.0f;
            player->camEye.y = gActors[10].obj.pos.y + D_ctx_80177A48[1];
            player->camEye.z = gActors[10].obj.pos.z;
            gCsCamAtX = gActors[10].obj.pos.x;
            gCsCamAtY = gActors[10].obj.pos.y + 50.0f;
            gCsCamAtZ = gActors[10].obj.pos.z;
            if (((gGameFrameCount % 4) == 0) && (gCsFrameCount < 215)) {
                func_effect_8007797C(boss->obj.pos.x + RAND_FLOAT_CENTERED(350.0f), boss->obj.pos.y + 500.0f,
                                     boss->obj.pos.z + RAND_FLOAT_CENTERED(350.0f), RAND_FLOAT_CENTERED(10.0f), 60.0f,
                                     RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.5f) + 15.5f);
            }
            sp80 = RAND_FLOAT(40.0f);
            for (i = 0; i < 36; i += 4) {
                sp8C = __sinf((i * 10.0f * M_DTOR) + sp80) * D_ctx_80177A48[2];
                sp84 = __cosf((i * 10.0f * M_DTOR) + sp80) * D_ctx_80177A48[2];
                func_effect_8007797C(sp8C, 300.0f, sp84, 0.0f, 0.0f, 0.0f, RAND_FLOAT(5.5f) + 15.5f);
            }
            Math_SmoothStepToF(&D_ctx_80177A48[2], 10000.0f, 0.05f, 20.0f, 0.0f);
            if (gCsFrameCount == 220) {
                Andross_80193AE4(0);
                if (gTeamShields[TEAM_ID_FALCO] > 0) {
                    Andross_80193AE4(1);
                }
                if (gTeamShields[TEAM_ID_SLIPPY] > 0) {
                    Andross_80193AE4(2);
                }
                if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                    Andross_80193AE4(3);
                }
            }

            if (gCsFrameCount == 190) {
                func_play_800A5D6C();
                D_ctx_80178410 = 1000;
                player->unk_204 = 0;
            }
            if (gCsFrameCount == 360) {
                gCsFrameCount = 340;
                player->unk_1D0++;
                D_ctx_80177A48[0] = 1.0f;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;
                D_ctx_80177A48[3] = 0.0f;
                D_ctx_80177A48[4] = 0.0f;
                player->camEye.x = gCsCamEyeX = 100.0f;
                player->camEye.y = gCsCamEyeY = 14800.0f;
                player->camEye.z = gCsCamEyeZ = -1500.0f;
                gCsCamAtX = 0.0f;
                gCsCamAtY = 15000.0f;
                gCsCamAtZ = 0;
                player->unk_034 = 0.0f;
                gActors[10].state = 101;
                gActors[10].fwork[0] = 0.0f;
                gActors[10].obj.pos.y = 14500.0f;
                gActors[10].unk_0F4.z = 70.0f;
                gActors[10].unk_0F4.x = gActors[10].unk_0F4.y = 0.0f;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                player->timer_1F8 = 3;
                D_ctx_80178410 = 500;
            }
            if (gCsFrameCount == 250) {
                gLevelClearScreenTimer = 100;
            }
            break;
        case 5:
            if (player->timer_1F8 == 1) {
                gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            }
            if (D_play_800D2F68 != 0) {
                if (gCsFrameCount >= 1000) {
                    gCsCamAtX += D_ctx_80177A48[4] * 0.15f;
                    gCsCamEyeZ += D_ctx_80177A48[4];
                    Math_SmoothStepToF(&D_ctx_80177A48[4], 20.0f, 1.0f, 0.1f, 0.0f);
                } else {
                    gCsCamEyeZ = gActors[10].obj.pos.z - 20.0f;
                }
                if ((gCsFrameCount >= 920) && (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                    if (gCsFrameCount == 920) {
                        player->timer_1F8 = 25;
                    }
                    gActors[10].fwork[19] = SIN_DEG(player->timer_1F8 * 40.0f) * 5.0f;
                } else {
                    if (gCsFrameCount < 850) {
                        switch (gCsFrameCount) {
                            case 600:
                                D_ctx_80177A48[2] = 80.0f;
                                D_ctx_80177A48[3] = -45.0f;
                                break;
                            case 650:
                                D_ctx_80177A48[2] = 0.0f;
                                break;
                            case 680:
                                D_ctx_80177A48[2] = 45.0f;
                                D_ctx_80177A48[3] = -20.0f;
                                break;
                            case 750:
                                D_ctx_80177A48[2] = 90.0f;
                                D_ctx_80177A48[3] = -30.0f;
                                break;
                            case 780:
                                D_ctx_80177A48[2] = 30.0f;
                                D_ctx_80177A48[3] = -45.0f;
                                break;
                            case 830:
                                D_ctx_80177A48[2] = -20.0f;
                                D_ctx_80177A48[3] = -25.0f;
                                break;
                            default:
                                // D_ctx_80177A48[2] = 0.0f;
                                break;
                        }
                    }
                    if (gCsFrameCount > 880) {
                        Math_SmoothStepToF(&gActors[10].fwork[19], 0.0f, 0.2f, 2.0f, 0.0f);
                        Math_SmoothStepToF(&gActors[10].fwork[20], 0.0f, 0.2f, 2.0f, 0.0f);
                    } else {
                        Math_SmoothStepToF(&gActors[10].fwork[19], D_ctx_80177A48[2], 0.2f, 2.0f, 0.0f);
                        Math_SmoothStepToF(&gActors[10].fwork[20], D_ctx_80177A48[3], 0.2f, 2.0f, 0.0f);
                    }
                }
                D_ctx_80177A48[0] = 0.01f;
                Math_SmoothStepToF(&D_ctx_80177A48[1], 10.0f, 1.0f, 0.1f, 0.0f);
                Math_SmoothStepToF(&player->camEye.x, gActors[10].obj.pos.x - 50.0f, D_ctx_80177A48[0],
                                   D_ctx_80177A48[1], 0);
                Math_SmoothStepToF(&player->camEye.y, gActors[10].obj.pos.y + 10.0f, D_ctx_80177A48[0],
                                   D_ctx_80177A48[1], 0);
                Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], D_ctx_80177A48[1], 0);
                gCsCamAtY = SIN_DEG(gGameFrameCount * 5.5f) + 15000.0f;
            } else {
                gCsCamEyeX -= 1.0f;
                gCsCamEyeY += 0.3f;
                gCsCamEyeZ += 4.0f;
                gCsCamAtY = (SIN_DEG(gGameFrameCount * 1.5f) * 10.0f) + 15000.0f;
                Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
                Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
                Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
            }
            if (D_play_800D2F68 != 0) {
                switch (gCsFrameCount) {
                    case 400:
                        Radio_PlayMessage(gMsg_ID_19400, RCID_PEPPY);
                        break;
                    case 500:
                        Radio_PlayMessage(gMsg_ID_19410, RCID_SLIPPY);
                        break;
                    case 600:
                        Radio_PlayMessage(gMsg_ID_19420, RCID_FALCO);
                        break;
                    case 800:
                        Radio_PlayMessage(gMsg_ID_19430, RCID_PEPPY);
                        break;
                    case 900:
                        if (gTeamShields[TEAM_ID_PEPPY] > 0) {
                            Radio_PlayMessage(gMsg_ID_19440, RCID_FOX);
                        }
                        break;
                    case 1050:
                        D_ctx_80177830 = 1;
                        break;
                    case 1250:
                        D_ctx_80177830 = 0;
                        break;
                }
                if (gCsFrameCount > 1300) {
                    D_ctx_80178288[109] += 1.0f;
                    D_ctx_80178290[109] += 0.5f;
                    temp_v0_2 = RAND_INT(100.0f);
                    D_ctx_80178298[109] = FILL_COLOR(D_bg_800C9C3C[temp_v0_2 % 16U]);
                }
            } else {
                switch (gCsFrameCount) {
                    case 400:
                        Radio_PlayMessage(gMsg_ID_8300, RCID_PEPPY);
                        break;
                    case 500:
                        Radio_PlayMessage(gMsg_ID_8310, RCID_SLIPPY);
                        break;
                    case 600:
                        Radio_PlayMessage(gMsg_ID_8320, RCID_FALCO);
                        gCsFrameCount += 230;
                        break;
                    case 1050:
                        D_ctx_80177830 = 1;
                        break;
                    case 1250:
                        D_ctx_80177830 = 0;
                        break;
                }
            }
            if (gCsFrameCount == 1400) {
                Audio_FadeOutAll(40);
            }
            if (gCsFrameCount > 1400) {
                gFillScreenAlphaStep = 4;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlphaTarget = 255;
                if (gFillScreenAlpha == 255) {
                    gNextGameState = GSTATE_ENDING;
                    D_ending_80196D00 = 0;
                    D_play_800D3180[LEVEL_VENOM_ANDROSS] = Play_CheckMedalStatus(200) + 1;
                    Audio_SetAudioSpec(0, 0x1B);
                }
            }
            break;
        case 100:
            gPlayerFillScreenAlphas[0] -= 4;
            if (gPlayerFillScreenAlphas[0] > 255) {
                gPlayerFillScreenAlphas[0] = 0;
            }
            Matrix_RotateY(gCalcMatrix, (player->unk_114 + player->unk_0E8 + 180.0f) * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, -((player->unk_120 + player->unk_0E4 + player->unk_4D8) * M_DTOR), 1);
            sp74.x = 0.0f;
            sp74.y = 0.0f;
            sp74.z = player->unk_0D0;
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
            player->vel.x = sp68.x;
            player->vel.z = sp68.z;
            player->vel.y = sp68.y;
            if (player->timer_1F8 == 0) {
                player->state_1C8 = PLAYERSTATE_1C8_3;
                player->unk_014 = 0.2f;
                player->unk_018 = 0.0f;
                player->unk_01C = 0.05f;
                D_ctx_80177AB0 = 6;
                D_game_80161A44 = 12800.0f;
            }
            D_ctx_80177A48[0] = 1.0f;
            gCsCamAtX = (2.0f * SIN_DEG(gGameFrameCount * 40.0f)) + player->pos.x;
            gCsCamAtY = (2.0f * SIN_DEG(gGameFrameCount * 30.0f)) + player->pos.y;
            gCsCamAtZ = (2.0f * SIN_DEG(gGameFrameCount * 50.0f)) + player->pos.z;
            sp74.x = 0.0f;
            sp74.y = 0.0f;
            sp74.z = D_ctx_80177A48[5];
            Math_SmoothStepToF(&D_ctx_80177A48[5], -400.0f, 0.05f, 5.0f, 0.0f);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
            gCsCamEyeX = player->pos.x + sp68.x;
            gCsCamEyeY = player->pos.y + sp68.y;
            gCsCamEyeZ = player->pos.z + sp68.z;
            Math_SmoothStepToF(&player->camEye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
            Math_SmoothStepToF(&player->camEye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
            Math_SmoothStepToF(&player->camEye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
            Math_SmoothStepToF(&player->unk_12C, 0.0f, 0.1f, 0.7f, 0.0f);
            Math_SmoothStepToF(&player->unk_034, 0.0f, 0.1f, 0.4f, 0.0f);
            break;
    }
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->unk_138 = player->pos.z + player->unk_08C;
    player->unk_0F8 = player->unk_0EC + player->unk_12C + player->unk_130;
    Math_SmoothStepToF(&player->unk_130, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToAngle(&player->unk_4D8, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->camAt.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camAt.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->camAt.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
}

void Andross_80195E44(Actor* actor) {
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;

    sp34 = 0.0f;

    switch (actor->state) {
        case 0:
            actor->unk_0F4.z += actor->fwork[1];
            if (gCsFrameCount > 250) {
                Math_SmoothStepToF(&actor->fwork[1], 0.5f, 0.1f, 0.04f, 0.0f);
            } else {
                Math_SmoothStepToF(&actor->fwork[1], -2.0f, 0.1f, 0.04f, 0.0f);
            }
            break;
        case 1:
            actor->unk_0F4.z += actor->fwork[1];
            Math_SmoothStepToF(&actor->fwork[1], -2.0f, 0.1f, 0.04f, 0.0f);
            if (gCsFrameCount == 55) {
                actor->state++;
            }
            break;
        case 2:
            Math_SmoothStepToF(&actor->unk_0F4.x, 180.0f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&actor->unk_0F4.y, 200.0f, 0.1f, 1.0f, 0.0f);
            actor->unk_046 -= 5;
            if (actor->unk_046 < 0) {
                actor->unk_046 = 0;
                Object_Kill(&actor->obj, actor->sfxSource);
            }
            break;
        case 101:
            Math_SmoothStepToF(&actor->unk_0F4.z, 0.0f, 0.03f, 0.5f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.x, 0.0f, 0.03f, 5.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.y, 15000.0f, 0.03f, 5.0f, 0.0f);
            Math_SmoothStepToF(&actor->obj.pos.z, 0.0f, 0.03f, 5.0f, 0.0f);
            break;
        case 100:
            actor->fwork[7] += 3.0f;
            actor->unk_0F4.z = SIN_DEG(actor->fwork[7]) * 1.5f;
            actor->fwork[8] += 2.0f;
            sp34 = SIN_DEG(actor->fwork[8]) * 0.5f;
            break;
        case 200:
            break;
    }
    Matrix_RotateY(gCalcMatrix, (actor->unk_0F4.y + 180.0f) * M_DTOR, 0U);
    Matrix_RotateX(gCalcMatrix, -(actor->unk_0F4.x * M_DTOR), 1U);
    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = actor->fwork[0];
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);
    actor->vel.x = sp38.x;
    actor->vel.y = sp38.y + sp34;
    actor->vel.z = sp38.z;
    actor->obj.rot.x = -actor->unk_0F4.x;
    actor->obj.rot.y = actor->unk_0F4.y + 180.0f;
    actor->obj.rot.z = -actor->unk_0F4.z;
}

void Andross_801961AC(void) {
    Boss* boss = &gBosses[0];

    Boss_Initialize(boss);
    boss->obj.status = OBJ_ACTIVE;
    boss->state = 21;
    boss->obj.id = OBJ_BOSS_321;
    Object_SetInfo(&boss->info, boss->obj.id);
    gCsFrameCount = 599;
}
