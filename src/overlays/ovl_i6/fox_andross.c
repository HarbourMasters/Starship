
// #include "prevent_bss_reordering.h"
#include "global.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_andross.h"
#include "assets/ast_arwing.h"
#include "assets/ast_bg_planet.h"
#include "prevent_bss_reordering.h"
#include "prevent_bss_reordering2.h"
#include "port/hooks/Events.h"

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

f32* D_i6_801A6760[12] = {
    D_ANDROSS_C037FCC, D_ANDROSS_C0380C0, D_ANDROSS_C0381B4, D_ANDROSS_C0382A8, D_ANDROSS_C03839C, D_ANDROSS_C038490,
    D_ANDROSS_C038584, D_ANDROSS_C038678, D_ANDROSS_C03876C, D_ANDROSS_C038860, D_ANDROSS_C038954, D_ANDROSS_C038954,
};

void Andross_80193710(void);

void Andross_80187530(ActorEvent* this) {
    s32 index;

    switch (this->work_048) {
        case 0:
            break;

        case 1:
            this->animFrame += (s32) this->fwork[22];
            if (this->animFrame >= Animation_GetFrameCount(&aVe2AndrossGateAnim)) {
                this->animFrame = Animation_GetFrameCount(&aVe2AndrossGateAnim) - 1;
            }
            break;

        case 2:
            this->animFrame -= (s32) this->fwork[22];
            if (this->animFrame <= 0) {
                this->animFrame = 0;
            }
            break;

        default:
            break;
    }

    index = this->animFrame / 18.0f;
    this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_i6_801A6760[index]);
    this->obj.rot.z = D_Andross_801A7F68;
}

bool Andross_Gate_OverrideLimbDraw(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    if (limbIndex == 13) {
        *dList = NULL;
    }
    return 0;
}

void Andross_Gate_Draw(ActorEvent* this) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&aVe2AndrossGateAnim, this->animFrame, frameTable);
    Animation_DrawSkeleton(1, aVe2AndrossGateSkel, frameTable, Andross_Gate_OverrideLimbDraw, NULL, NULL,
                           &gIdentityMatrix);
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
    Scenery360* scenery360;
    s32 i;

    gLevelObjects = SEGMENTED_TO_VIRTUAL(&D_ANDROSS_C0356CC);

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->obj.pos.z += gLevelObjects[i].zPos2;
            scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            if (scenery360->obj.id == OBJ_SCENERY_AND_PASSAGE) {
                scenery360->info.hitbox = SEGMENTED_TO_VIRTUAL(&D_ANDROSS_C038CCC);
            }
            scenery360++;
        }
    }

    for (actor = &gActors[1], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if ((gLevelObjects[i].id < OBJ_ACTOR_MAX) && (gLevelObjects[i].id >= OBJ_ACTOR_START)) {
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

    for (item = &gItems[0], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }
        if ((gLevelObjects[i].id < OBJ_ITEM_MAX) && (gLevelObjects[i].id >= OBJ_ITEM_START)) {
            Item_Initialize(item);
            item->obj.status = OBJ_ACTIVE;
            item->obj.id = gLevelObjects[i].id;
            item->obj.pos.x = gLevelObjects[i].xPos;
            item->obj.pos.z = -gLevelObjects[i].zPos1;
            item->obj.pos.z += gLevelObjects[i].zPos2;
            item->obj.pos.y = gLevelObjects[i].yPos;
            CALL_CANCELLABLE_EVENT(ItemDropEvent, item) {
                Object_SetInfo(&item->info, item->obj.id);
            }
            item++;
        }
    }
}

void Andross_80187C5C(void) {
    Actor* actor;
    Item* item;
    Scenery360* scenery360;
    s32 i;

    switch (RAND_INT(2.9f)) {
        case 0:
            gLevelObjects = SEGMENTED_TO_VIRTUAL(&D_ANDROSS_C036310);
            break;
        case 1:
            gLevelObjects = SEGMENTED_TO_VIRTUAL(&D_ANDROSS_C036B6C);
            break;
        default:
        case 2:
            gLevelObjects = SEGMENTED_TO_VIRTUAL(&D_ANDROSS_C03733C);
            break;
    }

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->obj.pos.z += gLevelObjects[i].zPos2;
            scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            if (scenery360->obj.id == OBJ_SCENERY_LEVEL_OBJECTS) {
                scenery360->pathIndex = gLevelObjects[i].rot.z;
            }
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            if (scenery360->obj.id == OBJ_SCENERY_AND_PASSAGE) {
                scenery360->info.hitbox = SEGMENTED_TO_VIRTUAL(&D_ANDROSS_C038CCC);
            }
            scenery360++;
        }
    }

    for (actor = &gActors[1], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if ((gLevelObjects[i].id < OBJ_ACTOR_MAX) && (gLevelObjects[i].id >= OBJ_ACTOR_START)) {
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

    for (item = &gItems[0], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }
        if ((gLevelObjects[i].id < OBJ_ITEM_MAX) && (gLevelObjects[i].id >= OBJ_ITEM_START)) {
            Item_Initialize(item);
            item->obj.status = OBJ_ACTIVE;
            item->obj.id = gLevelObjects[i].id;
            item->obj.pos.x = gLevelObjects[i].xPos;
            item->obj.pos.z = -gLevelObjects[i].zPos1;
            item->obj.pos.z += gLevelObjects[i].zPos2;
            item->obj.pos.y = gLevelObjects[i].yPos;
            CALL_CANCELLABLE_EVENT(ItemDropEvent, item) {
                Object_SetInfo(&item->info, item->obj.id);
            }
            item++;
        }
    }
}

void Andross_ActorTeamArwing_Update(ActorTeamArwing* this) {
    s32 i;
    f32 xDisplacement;
    f32 yDisplacement;
    f32 zDisplacement;
    Scenery360* scenery360;
    f32 yaw;
    f32 var_fv0;
    Vec3f sp48;
    Vec3f vel;
    f32 temp_fv1;

    for (scenery360 = gScenery360, i = 0; i < 200; i++, scenery360++) {
        if ((scenery360->obj.id == OBJ_SCENERY_LEVEL_OBJECTS) && (scenery360->pathIndex == (u8) this->counter_04E)) {
            this->fwork[3] = scenery360->obj.pos.x;
            this->fwork[4] = scenery360->obj.pos.y;
            this->fwork[5] = scenery360->obj.pos.z;
            break;
        }
    }

    this->fwork[2] = 3.0f;

    xDisplacement = this->fwork[3] - this->obj.pos.x;
    yDisplacement = this->fwork[4] - this->obj.pos.y;
    zDisplacement = this->fwork[5] - this->obj.pos.z;

    if ((fabsf(xDisplacement) < 300.0f) && (fabsf(yDisplacement) < 300.0f) && (fabsf(zDisplacement) < 300.0f)) {
        this->counter_04E++;
    }

    if ((gGameFrameCount % 32) == 0) {
        this->iwork[11] = 1;
        this->fwork[1] = 47.0f;
        if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 1000.0f) &&
            (fabsf(this->obj.pos.y - gPlayer[0].pos.y) < 500.0f) &&
            (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 1000.0f)) {
            this->iwork[11] = 2;
            this->fwork[1] = 65.0f;
        }
    }

    Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.2f, 3.0f, 0.00001f);

    yaw = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));

    Math_SmoothStepToAngle(&this->rot_0F4.x,
                           Math_RadToDeg(Math_Atan2F(yDisplacement, sqrtf(SQ(xDisplacement) + SQ(zDisplacement)))),
                           0.1f, this->fwork[2], 0.0f);

    temp_fv1 = Math_SmoothStepToAngle(&this->rot_0F4.y, yaw, 0.1f, this->fwork[2], 0.0001f) * 40.0f;
    if (temp_fv1 < 0.0f) {
        var_fv0 = temp_fv1 * -1.0f;
    } else {
        var_fv0 = 360.0f - temp_fv1;
    }
    Math_SmoothStepToAngle(&this->obj.rot.z, var_fv0, 0.1f, 3.0f, 0.01f);

    this->obj.rot.y = this->rot_0F4.y;
    this->obj.rot.x = -this->rot_0F4.x;

    Matrix_RotateY(gCalcMatrix, this->rot_0F4.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -this->rot_0F4.x * M_DTOR, MTXF_APPLY);

    sp48.x = 0;
    sp48.y = 0;
    sp48.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp48, &vel);

    this->vel.x = vel.x;
    this->vel.y = vel.y;
    this->vel.z = vel.z;
}

void Andross_ActorTeamArwing_Draw(ActorTeamArwing* this) {
    ActorTeamArwing_Draw(this);
}

void Andross_80188468(void) {
    Actor* actor = &gActors[0];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.pos.x = -23180.0f;
    actor->obj.pos.y = 300.0f;
    actor->obj.pos.z = -11959.0f;
    actor->iwork[11] = 1;
    actor->iwork[TEAM_FACE] = FACE_FOX;
    actor->obj.id = OBJ_ACTOR_TEAM_ARWING;
    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
}

void Andross_AndBrainWaste_Update(AndBrainWaste* this) {
    Math_SmoothStepToF(&this->vel.x, 0.0f, 0.2f, 0.5f, 0.0f);
    Math_SmoothStepToF(&this->vel.y, 0.0f, 0.2f, 0.5f, 0.0f);
    Math_SmoothStepToF(&this->vel.z, 0.0f, 0.2f, 0.5f, 0.0f);

    if (this->dmgType != DMG_NONE) {
        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
        Object_Kill(&this->obj, this->sfxSource);
        Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 3.0f, 5);
    } else if (this->timer_0BC == 0) {
        Object_Kill(&this->obj, this->sfxSource);
    }

    this->obj.rot.y = RAD_TO_DEG(-gPlayer[0].camYaw);
    this->obj.rot.x = RAD_TO_DEG(gPlayer[0].camPitch);
    this->rot_0F4.z += this->fwork[0];
}

void Andross_AndBrainWaste_Draw(AndBrainWaste* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_61);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    Matrix_RotateZ(gGfxMatrix, this->rot_0F4.z * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.1f, 0.9f, 1.0f, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, -this->rot_0F4.z * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.1f, 0.9f, 1.0f, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 3.0f, 3.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aAndBrainWasteDL);
}

void Andross_AndBrainWaste_Setup(AndBrainWaste* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    Actor_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_ACTOR_AND_BRAIN_WASTE;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;

    if (Rand_ZeroOne() < 0.5f) {
        this->fwork[0] = 10.0f;
    } else {
        this->fwork[0] = -10.0f;
    }

    this->timer_0BC = 300;
    Object_SetInfo(&this->info, this->obj.id);
}

void Andross_AndBrainWaste_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gActors); i++) {
        if (gActors[i].obj.status == OBJ_FREE) {
            Andross_AndBrainWaste_Setup(&gActors[i], xPos, yPos, zPos, xVel, yVel, zVel);
            break;
        }
    }
}

void Andross_801888F4(ActorAllRange* this) {
    s32 i;

    this->obj.rot.z -= 8.0f;
    if ((this->timer_0BC % 2U) == 1) {
        func_effect_8007D2C8(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f);
    }
    if ((this->timer_0BC == 0) || (this->dmgType != DMG_NONE)) {
        Effect386_Spawn1(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, this->vel.x, this->vel.y, this->vel.z, 7.0f,
                         20);
        Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f, 5);

        for (i = 0; i < 6; i++) {
            Effect_Effect357_Spawn50(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 1.0f);
        }

        Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_M);
        Object_Kill(&this->obj, this->sfxSource);
        BonusText_Display(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5);
        gHitCount += 6;
        D_ctx_80177850 = 15;
    }
}

void Andross_80188A4C(AndBrain* this) {

    if (this->damage > 20) {
        this->damage = 20;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;

        if (this->state < 10 && !(this->fwork[21] < 250.0f)) {
            switch (this->dmgPart) {
                case 0:
                    this->swork[1] = 15;
                    this->swork[7] = 30;
                    break;

                case 1:
                case 2:
                    if (this->swork[4] == 0) {
                        this->swork[2] = 10;
                        this->swork[3] = 15;

                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);

                        this->health -= this->damage;
                        if ((this->health != 0) && (this->health <= 0)) {
                            gScreenFlashTimer = 8;
                            AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                            Boss_AwardBonus(this);
                            gPlayer[0].state = PLAYERSTATE_STANDBY;
                            this->state = 20;
                            this->swork[1] = 1000;
                            this->swork[2] = 1000;
                            this->swork[6] = 1;
                            D_ctx_80177A48[0] = 0.0f;
                            D_ctx_80177A48[1] = 0.1f;
                            gCsFrameCount = 0;
                            Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ANDROSS_BRAIN);
                            Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ANDROSS_CATCH);
                            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
                        }
                    }
                    break;

                default:
                    if (this->swork[4] == 0) {
                        this->swork[8]++;
                        if (this->swork[8] >= 6) {
                            this->swork[8] = 0;
                            this->state = 12;
                            this->timer_050 = 50;
                            this->fwork[3] = gPlayer[0].pos.x;
                            this->fwork[5] = gPlayer[0].trueZpos;
                            AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_WARP, this->sfxSource, 4);
                        }
                    }
                    break;
            }
        }
    }
}

void Andross_80188CB8(AndBrain* this) {
    s32 i;
    Vec3f sp50;
    Vec3f sp44;

    this->animFrame++;
    if (this->animFrame >= Animation_GetFrameCount(&D_VE2_600C038)) {
        this->animFrame = 0;
    }
    Animation_GetFrameData(&D_VE2_600C038, this->animFrame, this->vwork);

    if (this->swork[3] != 0) {
        this->swork[3]--;
    }

    if (this->swork[2] != 0) {
        this->swork[2]--;
        Math_SmoothStepToF(&this->fwork[15], -15.0f, 0.8f, 5.0f, 0.0f);
        Math_SmoothStepToF(&this->fwork[16], 0.05f, 0.8f, 0.02f, 0.0f);
    } else {
        Math_SmoothStepToF(&this->fwork[15], 4.0f, 0.05f, 0.2f, 0.0f);
        Math_SmoothStepToF(&this->fwork[16], 0.03f, 0.05f, 0.001f, 0.0f);
    }

    Math_SmoothStepToF(&this->fwork[10], this->fwork[11], this->fwork[12], this->fwork[13], 0.0f);

    if (this->swork[1] != 0) {
        this->swork[1]--;
        this->fwork[11] = 30.0f;
        this->fwork[12] = 0.8f;
        this->fwork[13] = 3.0f;
    } else {
        this->fwork[11] = 8.0f;
        this->fwork[12] = 0.05f;
        this->fwork[13] = 0.5f;
    }

    if (this->swork[7] != 0) {
        this->swork[7]--;
        if ((gGameFrameCount % 2) == 0) {
            Andross_AndBrainWaste_Spawn(RAND_FLOAT_CENTERED(100.0f) + this->obj.pos.x,
                                        RAND_FLOAT_CENTERED(300.0f) + (this->obj.pos.y - 250.0f),
                                        RAND_FLOAT_CENTERED(100.0f) + this->obj.pos.z, RAND_FLOAT_CENTERED(50.0f),
                                        RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(50.0f));
        }
    }

    this->fwork[14] += this->fwork[15];

    Matrix_RotateY(gCalcMatrix, -gPlayer[0].camYaw, MTXF_NEW);

    sp50.x = this->vel.z * 0.25f;
    sp50.y = 0.0f;
    sp50.z = this->vel.x * 0.25f;

    Matrix_MultVec3f(gCalcMatrix, &sp50, &sp44);

    this->fwork[18] = -sp44.z;
    this->fwork[17] = sp44.x;
    this->swork[4] = 0;
    this->fwork[19] = -26.0f;

    for (i = 10; i < 12; i++) {
        if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_ALLRANGE)) {
            gTexturedLines[i].mode = 50;
            gTexturedLines[i].xyScale = 1.0f;
            gTexturedLines[i].posAA.x = this->obj.pos.x;
            gTexturedLines[i].posAA.y = this->obj.pos.y - 200.0f;
            gTexturedLines[i].posAA.z = this->obj.pos.z;
            gTexturedLines[i].timer = 3;
            gTexturedLines[i].posBB.x = gActors[i].obj.pos.x;
            gTexturedLines[i].posBB.y = gActors[i].obj.pos.y;
            gTexturedLines[i].posBB.z = gActors[i].obj.pos.z;
            this->swork[4] = 1;
        }
    }
}

void Andross_80189098(AndBrain* this) {
    ActorAllRange* actor = &gActors[10];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = AI360_ENEMY;
    actor->aiIndex = AI360_FOX;
    actor->health = 200;
    actor->obj.pos.x = 200.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = this->obj.pos.z;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.hitbox = SEGMENTED_TO_VIRTUAL(&gCubeHitbox150);

    actor++;

    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_ALLRANGE;
    actor->aiType = AI360_ENEMY;
    actor->aiIndex = AI360_FOX;
    actor->health = 200;
    actor->obj.pos.x = -200.0f;
    actor->obj.pos.y = 0.0f;
    actor->obj.pos.z = this->obj.pos.z;
    Object_SetInfo(&actor->info, actor->obj.id);
    actor->info.hitbox = SEGMENTED_TO_VIRTUAL(&gCubeHitbox150);

    gActors[0].state = 2;
}

void Andross_80189214(void) {
    s32 i;
    Player* player = &gPlayer[0];

    Play_ClearObjectData();

    for (i = 0; i < 200; i++) {
        gScenery360[i].obj.status = OBJ_FREE;
    }

    gLevelMode = LEVELMODE_ON_RAILS;
    player->wingPosition = 0;
    gPlayer[0].pos.x = 0.0f;
    player->cam.eye.z = 400.0f;
    player->cam.at.z = player->cam.eye.z - 1000.0f;
    player->unk_148 = player->unk_14C = 0.74f;
    player->cam.eye.y = player->pos.y * player->unk_14C + 10.0f;
    player->cam.eye.x = player->pos.x * player->unk_148;
    gObjectLoadIndex = 0;
    // FAKE
    if (1) {}
    player->cam.at.x = 0.0f;
    player->cam.at.y = 0.0f;
    player->yRot_114 = 0.0f;
    player->zPath = 0.0f;
    gPathProgress = 0.0f;
    player->unk_018 = player->unk_014 = 1.0f;
    player->pos.z = player->trueZpos = -player->zPath;
    Camera_UpdateArwingOnRails(player);
}

void Andross_AndBossTimer_Update(AndBossTimer* this) {
    PRINTF("FO_Game_Sw %d\n");
    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 1000.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 1000.0f)) {
        gStartAndrossFightTimer = 50;
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Andross_AndRadio_Update(AndRadio* this) {
    if (gAllRangeCheckpoint == 0) {
        this->counter_04E++;
        switch (this->counter_04E) {
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

void Andross_AndJamesTrigger_Update(AndJamesTrigger* this) {
    s32 i;
    Player* player = &gPlayer[0];

    if ((gDrawBackdrop != 7) && (gPlayer[0].state == PLAYERSTATE_ACTIVE) &&
        (fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 9000.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 9000.0f)) {
        gDrawBackdrop = 7;
        Radio_PlayMessage(gMsg_ID_19370, RCID_JAMES);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 20);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 20);
    }

    if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) && (fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 500.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 500.0f)) {
        Audio_KillSfxById(NA_SE_OB_ROUTE_EXPLOSION1);
        Audio_SetEnvSfxReverb(0);
        gCurrentLevel = LEVEL_VENOM_2;
        gLevelPhase = 1;
        gVenomHardClear = 1;
        player->state = PLAYERSTATE_LEVEL_COMPLETE;
        player->csState = 3;
        player->zPath = gPathProgress = 0.0f;
        gDrawBackdrop = gDrawGround = true;
        player->cam.eye.x = 1200.0f;
        player->cam.eye.z = 1200.0f;
        player->cam.eye.y = 1800.0f;
        gCsCamAtX = 0.0f;
        gCsCamAtY = 620.0f;
        gCsCamAtZ = 0.0f;
        player->draw = false;
        player->camRoll = 0.0f;
        D_ctx_80177A48[0] = 1.0f;
        Play_ClearObjectData();

        for (i = 0; i < 200; i++) {
            gScenery360[i].obj.status = OBJ_FREE;
        }

        Andross_80193710();
        D_ctx_8017782C = true;
        Play_InitEnvironment();
        gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
        gFillScreenAlpha = gFillScreenAlphaTarget = 255;
        player->csTimer = 2;
        gCsFrameCount = 0;
        D_ctx_80177A48[1] = 0.0f;
    }
}

void Andross_AndExplosion_Update(AndExplosion* this) {
    s32 i;
    Vec3f vec;
    Vec3f displacement;
    Vec3f vel;

    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 2000.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 2000.0f)) {
        Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_NEW);
        vec.x = 0.0f;
        vec.y = 0.0f;
        vec.z = -30.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &vel);
        Matrix_RotateZ(gCalcMatrix, 2.0f * RAND_FLOAT(M_PI), MTXF_APPLY);
        vec.x = RAND_FLOAT(300.0f);
        vec.y = 0.0f;
        vec.z = 0.0f;
        Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &displacement);

        this->vel.x = vel.x * 0.2f;
        this->vel.y = vel.y * 0.2f;
        this->vel.z = vel.z * 0.2f;
        for (i = 0; i < 1; i++) {
            Effect_FireSmoke_Spawn2(this->obj.pos.x + displacement.x, this->obj.pos.y + displacement.y,
                                    this->obj.pos.z + displacement.z, vel.x, vel.y, vel.z, RAND_FLOAT(2.5f) + 15.5f);
        }
    }

    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 500.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 500.0f)) {
        if ((gPlayer[0].state == PLAYERSTATE_ACTIVE || gPlayer[0].state == PLAYERSTATE_U_TURN)) {
            gPlayer[0].shields = 0;
            gRightWingHealth[0] = gLeftWingHealth[0] = 0;
            Player_ApplyDamage(&gPlayer[0], 1, 60);
            Player_ApplyDamage(&gPlayer[0], 2, 60);
            this->timer_0BC = 10;
            gPlayer[0].radioDamageTimer = 200;
        }
    }
    if (this->timer_0BC == 1) {
        Cutscene_KillPlayer(&gPlayer[0]);
    }
}

void Andross_Effect357_Setup(Effect357* this, f32 xPos, f32 yPos, f32 zPos, f32 scale2, u8 arg5) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_357;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->unk_4C = arg5;
    this->scale2 = (RAND_FLOAT(0.8f) + 0.3f) * scale2;
    this->timer_50 = 100;
    this->obj.rot.x = RAND_FLOAT(360.0f);
    this->unk_60.x = RAND_FLOAT_CENTERED(30.0f);
    this->unk_60.y = RAND_FLOAT_CENTERED(30.0f);
    this->unk_60.z = RAND_FLOAT_CENTERED(30.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Andross_Effect357_Spawn(f32 xPos, f32 yPos, f32 zPos, f32 scale2) {
    s32 i;

    for (i = 50; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_Effect357_Setup(&gEffects[i], xPos, yPos, zPos, scale2, 0);
            break;
        }
    }
}

void Andross_AndBrain_Update(AndBrain* this) {
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

    Andross_80188A4C(this);
    Andross_80188CB8(this);

    this->info.hitbox = SEGMENTED_TO_VIRTUAL(&aAndBrainHitbox);

    Math_SmoothStepToF(&gAndrossUnkAlpha, 255.0f, 1.0f, 4.0f, 0);
    Math_SmoothStepToF(&this->scale, 10.0f, 0.2f, 0.2f, 0);

    if ((gGameFrameCount & 0x10) == 0) {
        Math_SmoothStepToF(&this->fwork[25], 255.0f, 1.0f, 10.0f, 0);
    } else {
        Math_SmoothStepToF(&this->fwork[25], 100.0f, 1.0f, 10.0f, 0);
    }

    if ((fabsf(this->obj.pos.x - gPlayer[0].pos.x) < 300.0f) &&
        (fabsf(this->obj.pos.y - 300.0f - gPlayer[0].pos.y) < 300.0f) &&
        (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 300.0f) && (this->state < 11) && (this->timer_05A == 0)) {
        this->state = 11;
        this->timer_050 = 150;
        AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_CATCH, this->sfxSource, 4);
    }

    switch (this->state) {
        case 0:
            this->health = 200;
            gDrawBackdrop = 3;
            this->fwork[19] = -26.0f;
            this->fwork[10] = 8.0f;
            Andross_80189098(this);
            this->swork[5] = 300;
            this->state++;
            AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_BRAIN, this->sfxSource, 4);
            this->fwork[21] = 255.0f;
            this->fwork[22] = 255.0f;
            this->fwork[23] = 0.0f;
            this->fwork[24] = 0.0f;
            break;

        case 10:
            this->fwork[23] = 0.0f;
            this->fwork[24] = 0.0f;
            this->fwork[21] = 255.0f;
            this->fwork[22] = 255.0f;
            this->fwork[1] = 10.0f;
            this->fwork[2] = 2.0f;
            this->fwork[3] = 0.0f;
            this->fwork[4] = 0.0f;
            this->fwork[5] = gPlayer[0].pos.z - 3000.0f;
            this->fwork[19] = -26.0f;
            this->swork[5] = 100;

            if (this->timer_050 == 0) {
                gPlayer[0].state = PLAYERSTATE_START_360;
                gPlayer[0].csState = 0;
                this->state = 1;
                gPlayer[0].hideShadow = true;
            }
            break;

        case 1:
            if ((gPlayer[0].state != PLAYERSTATE_START_360) && (this->timer_050 == 0)) {
                this->fwork[2] = 1.6f;
                this->timer_050 = RAND_INT(1.0f) * 50.0f + 50;
                this->fwork[3] = RAND_FLOAT_CENTERED(10000.0f);
                this->fwork[4] = RAND_FLOAT_CENTERED(1000.0f);
                this->fwork[5] = RAND_FLOAT_CENTERED(10000.0f);

                if (Rand_ZeroOne() < 0.3f) {
                    this->state = 2;
                    this->timer_050 = RAND_INT(1.0f) * 100.0f + 50;
                    this->fwork[1] = 0.0f;
                }
            }
            break;

        case 2:
            if (this->timer_050 == 0) {
                this->state = 1;
                this->timer_050 = RAND_INT(1.0f) * 50.0f + 50;
                this->fwork[1] = 50.0f;
            }
            break;

        case 11:
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(&gNoHitbox);
            if (this->timer_050 < 120) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 255;
                gFillScreenAlphaTarget = 80;
                gFillScreenAlphaStep = 1;
                gPlayer[0].dmgEffectTimer = gGameFrameCount % 8U;
                gPlayer[0].radioDamageTimer = 3;

                Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 40.0f, 1.0f, 3.0f, 0.0f);

                if (((gGameFrameCount % 32) == 0) && (gPlayer[0].state == PLAYERSTATE_ACTIVE)) {
                    Player_ApplyDamage(&gPlayer[0], 3, 10);
                }
            }

            Math_SmoothStepToF(&gPlayer[0].baseSpeed, 0.0f, 2.0f, 2.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].pos.x, this->obj.pos.x, 0.8f, 50.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].pos.y, this->obj.pos.y - 300.0f, 0.8f, 50.0f, 0.0f);
            Math_SmoothStepToF(&gPlayer[0].pos.z, this->obj.pos.z, 0.8f, 50.0f, 0.0f);

            this->fwork[11] = 45.0f;
            this->fwork[12] = 0.8f;
            this->fwork[13] = 1.0f;
            this->fwork[19] = 23.0f;
            this->fwork[1] = 0.0f;

            gPlayer[0].alternateView = true;

            Math_SmoothStepToF(&gCamDistortion, 0.15f, 0.2f, 0.004f, 0.0f);

            if (this->timer_050 == 120) {
                AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_LAUGH, this->sfxSource, 4);
            }
            if (this->timer_050 == 0) {
                gPlayer[0].baseSpeed = gArwingSpeed;
                gPlayer[0].alternateView = false;

                gFillScreenAlphaTarget = 0;

                this->timer_05A = 50;

                if (this->swork[4] != 0) {
                    this->state = 1;
                    this->timer_050 = RAND_INT(1.0f) * 50.0f + 50;
                    this->fwork[1] = 50.0f;
                } else {
                    this->state = 3;
                }
                Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ANDROSS_CATCH);
            }
            break;

        case 3:
            this->fwork[1] = 42.0f;
            this->fwork[2] = 1.3f;
            this->fwork[3] = gPlayer[0].pos.x;
            this->fwork[4] = gPlayer[0].pos.y;
            this->fwork[5] = gPlayer[0].trueZpos;
            break;

        case 12:
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(&gNoHitbox);
            this->fwork[1] = 0;
            this->fwork[24] = 0.2f;
            this->fwork[22] = 0.0f;

            if ((this->fwork[22] < 1.0f) && (this->timer_050 == 0)) {
                xDisplacement = this->fwork[3] - this->obj.pos.x;
                zDisplacement = this->fwork[5] - this->obj.pos.z;
                Matrix_RotateY(gCalcMatrix, Math_Atan2F(xDisplacement, zDisplacement), MTXF_NEW);
                vec.x = 0.0f;
                vec.y = 0.0f;
                vec.z = 4000.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);
                this->obj.pos.x = this->fwork[3] + sp64.x;
                this->obj.pos.z = this->fwork[5] + sp64.z;
                this->rot_078.y = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));
                this->state = 13;
                AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_LAUGH, this->sfxSource, 4);
                this->timer_054 = 90;
            }
            break;

        case 13:
            this->info.hitbox = SEGMENTED_TO_VIRTUAL(&gNoHitbox);
            this->fwork[24] = 0.0f;
            this->fwork[22] = 255.0f;
            if (250.0f < this->fwork[22]) {
                this->state = 3;
            }
            break;

        case 20:
            gCsFrameCount++;

            this->fwork[0] = 0.0f;
            this->fwork[1] = 0.0f;

            this->obj.rot.z += 0.2f;
            this->obj.rot.x += 0.1f;
            this->obj.pos.y -= 3.0f;

            Matrix_RotateY(gCalcMatrix, -gPlayer[0].camYaw, 0U);

            vec.x = RAND_FLOAT_CENTERED(700.0f);
            vec.y = RAND_FLOAT_CENTERED(300.0f);
            vec.z = 500.0f;

            Matrix_MultVec3f(gCalcMatrix, &vec, &sp64);

            Effect_FireSmoke_Spawn2(this->obj.pos.x + sp64.x, this->obj.pos.y + sp64.y, this->obj.pos.z + sp64.z, 0.0f,
                                    0.0f, 0.0f, RAND_FLOAT(5.0f) + 7.0f);
            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect389_Spawn(RAND_FLOAT_CENTERED(600.0f) + this->obj.pos.x,
                                       RAND_FLOAT(100.0f) + (this->obj.pos.y + 100.0f), this->obj.pos.z, 0.0f, 0.0f,
                                       0.0f, RAND_FLOAT(0.3f) + 0.5f, 0);
            }

            vec.x = 0.0f;
            vec.y = 0.0f;
            vec.z = 2000.0f;

            Matrix_MultVec3f(gCalcMatrix, &vec, &sp64);

            Math_SmoothStepToF(&D_ctx_80177A48[0], 100.0f, 1.0f, 2.0f, 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[1], 100.0f, 1.0f, 10.0f, 0.0f);

            Math_SmoothStepToF(&gPlayer[0].cam.eye.x, this->obj.pos.x + sp64.x, 0.02f, D_ctx_80177A48[0], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.y, this->obj.pos.y + sp64.y, 0.02f, D_ctx_80177A48[0], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.eye.z, this->obj.pos.z + sp64.z, 0.02f, D_ctx_80177A48[0], 0.0f);

            Math_SmoothStepToF(&gPlayer[0].cam.at.x, this->obj.pos.x, 0.05f, D_ctx_80177A48[1], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.y, this->obj.pos.y, 0.05f, D_ctx_80177A48[1], 0.0f);
            Math_SmoothStepToF(&gPlayer[0].cam.at.z, this->obj.pos.z, 0.05f, D_ctx_80177A48[1], 0.0f);

            Math_SmoothStepToF(&gPlayer[0].camRoll, 0.0f, 0.5f, 0.5f, 0.0f);

            if (gCsFrameCount == 50) {
                Radio_PlayMessage(gMsg_ID_19335, RCID_ANDROSS_RED);
            }
            if (gCsFrameCount == 200) {
                gBossActive = false;
                gPlayer[0].baseSpeed = gArwingSpeed;
                Audio_StopPlayerNoise(0);
                this->state = 21;
                Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 60.0f, 5);
                Effect_Effect383_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 40.0f);

                for (i = 0; i < ARRAY_COUNT(gActors); i++) {
                    if ((gActors[i].obj.status == OBJ_ACTIVE) && (gActors[i].obj.id == OBJ_ACTOR_AND_BRAIN_WASTE)) {
                        Object_Kill(&gActors[i].obj, gActors[i].sfxSource);
                    }
                }
                gDrawBackdrop = 4;
                gCsFrameCount = 0;
            }
            break;

        case 21:
            Andross_801876FC();
            gCsFrameCount++;
            gCameraShake = 10;
            if (gCsFrameCount < 200) {
                gPlayerGlareAlphas[0] += 4;
                if (gPlayerGlareAlphas[0] >= 255) {
                    gPlayerGlareAlphas[0] = 255;
                }
                gPlayerGlareReds[0] = gPlayerGlareGreens[0] = gPlayerGlareBlues[0] = 255;
                Math_SmoothStepToF(&gCamDistortion, 0.15f, 0.2f, 0.004f, 0.0f);
                Math_SmoothStepToF(&D_ctx_801779A8[gMainController], 70.0f, 1.0f, 4.0f, 0.0f);
            }

            switch (gCsFrameCount) {
                case 30:
                    gRadioState = 0;
                    Radio_PlayMessage(gMsg_ID_20318, RCID_FOX);
                    gPlayer[0].radioDamageTimer = 200;
                    break;

                case 350:
                    Radio_PlayMessage(gMsg_ID_19468, RCID_JAMES);
                    break;

                case 500:
                    Radio_PlayMessage(gMsg_ID_19350, RCID_FOX);
                    gAllRangeCheckpoint = 1;
                    break;

                case 600:
                    gDrawBackdrop = 5;
                    gFogRed = 129;
                    gFogGreen = 27;
                    gFogBlue = 0;
                    gFogNear = 996;
                    gFogFar = 1007;
                    gBgColor = 0x4081; // 64, 16, 0
                    gProjectFar = 30000.0f;
                    gGroundHeight = -50.0f;
                    gPlayer[0].pos.x = -25995.0f;
                    gPlayer[0].pos.y = 300.0f;
                    gPlayer[0].pos.z = -11140.0f;
                    gPlayer[0].camDist = 0.0f;
                    gPlayer[0].yRot_114 = 271.0f;
                    gPlayer[0].boostSpeed = gPlayer[0].aerobaticPitch = gPlayer[0].rot.y = gPlayer[0].rot.x =
                        gPlayer[0].rot.z = 0.0f;
                    gPlayer[0].zRotBank = 150.0f;
                    gPlayer[0].camRoll = -90.0f;
                    gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                    gPlayer[0].csState = 100;
                    gPlayer[0].csTimer = 240;
                    gPlayer[0].draw = true;
                    D_ctx_80177A48[5] = -1200.0f;

                    Andross_80188468();
                    Andross_80187C5C();
                    gPlayer[0].unk_014 = 1.0f;
                    Camera_Update360(gPlayer, true);
                    Audio_StartPlayerNoise(0);
                    AUDIO_PLAY_BGM(gBossBgms[gCurrentLevel]);
                    AUDIO_PLAY_SFX(NA_SE_OB_ROUTE_EXPLOSION1, gDefaultSfxSource, 0);

                    D_ctx_80177CA4 = gHitCount;
                    break;

                case 800:
                    Radio_PlayMessage(gMsg_ID_19340, RCID_JAMES);
                    break;

                case 1000:
                    Audio_SetEnvSfxReverb(0);
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
            this->obj.pos.y = 10000.0f;

            if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) && ((gGameFrameCount % 4) == 0)) {
                Matrix_RotateY(gCalcMatrix, (gPlayer[0].yRot_114 + gPlayer[0].rot.y) * M_DTOR, 0U);
                vec.x = RAND_FLOAT_CENTERED(800.0f);
                vec.y = 600.0f;
                vec.z = RAND_FLOAT(1000.0f) + -3000.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);
                Andross_Effect357_Spawn(gPlayer[0].pos.x + sp64.x, sp64.y, gPlayer[0].trueZpos + sp64.z, 1.2f);
            }
            if (gPlayer[0].state != PLAYERSTATE_STANDBY) {
                Matrix_RotateY(gCalcMatrix, -gPlayer[0].camYaw, MTXF_NEW);

                vec.x = 0.0f;
                vec.y = 0.0f;
                vec.z = -50.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp58);
                Matrix_RotateZ(gCalcMatrix, 2.0f * RAND_FLOAT(M_PI), MTXF_APPLY);
                vec.x = RAND_FLOAT(50.0f) + 120.0f;
                vec.y = 0.0f;
                vec.z = 0.0f;

                Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);

                if (gCsFrameCount < 1000) {
                    frameCountMask = 2 - 1;
                } else if (gCsFrameCount < 1500) {
                    frameCountMask = 4 - 1;
                } else if (gCsFrameCount < 2000) {
                    frameCountMask = 2 - 1;
                } else {
                    frameCountMask = 2 - 1;
                }

                sp98 = 1;
                if ((gGameFrameCount & frameCountMask) == 0) {
                    for (i = 0; i < sp98; i++) {
                        Effect_FireSmoke_Spawn2(gPlayer[0].cam.eye.x + sp64.x, gPlayer[0].cam.eye.y + sp64.y,
                                                gPlayer[0].cam.eye.z + sp64.z, sp58.x, sp58.y, sp58.z,
                                                RAND_FLOAT(2.5f) + 2.5f);
                    }
                }
            }
            break;
    }

    xDisplacement = this->fwork[3] - this->obj.pos.x;
    yDisplacement = this->fwork[4] - this->obj.pos.y;
    zDisplacement = this->fwork[5] - this->obj.pos.z;

    yaw = Math_RadToDeg(Math_Atan2F(xDisplacement, zDisplacement));

    Math_SmoothStepToAngle(&this->rot_078.x,
                           Math_RadToDeg(Math_Atan2F(yDisplacement, sqrtf(SQ(xDisplacement) + SQ(zDisplacement)))),
                           0.1f, this->fwork[2], 0.0f);
    Math_SmoothStepToAngle(&this->rot_078.y, yaw, 0.1f, this->fwork[2], 0.0f);

    if (this->swork[4] != 0) {
        Math_SmoothStepToAngle(&this->obj.rot.y, Math_RadToDeg(-gPlayer[0].camYaw), 0.3f, 5.0f, 0.0f);
    } else if (this->timer_054 == 0) {
        Math_SmoothStepToAngle(&this->obj.rot.y, Math_RadToDeg(-gPlayer[0].camYaw), 0.3f, 1.5f, 0.0f);
    }

    Math_SmoothStepToF(&this->fwork[0], this->fwork[1], 0.2f, 1.0f, 0.00001f);

    Matrix_RotateY(gCalcMatrix, this->rot_078.y * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -this->rot_078.x * M_DTOR, MTXF_APPLY);

    vec.x = 0.0f;
    vec.y = 0.0f;
    vec.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &vec, &sp64);

    this->vel.x = sp64.x;
    this->vel.y = sp64.y;
    this->vel.z = sp64.z - gPathVelZ;

    if (this->state < 20) {
        gRadarMarks[59].enabled = true;
        gRadarMarks[59].type = 102;
        gRadarMarks[59].pos.x = this->obj.pos.x;
        gRadarMarks[59].pos.y = this->obj.pos.y;
        gRadarMarks[59].pos.z = this->obj.pos.z;
        gRadarMarks[59].yRot = this->rot_078.y + 180.0f;
    }

    gActors[10].info.targetOffset = 1.0f;
    gActors[11].info.targetOffset = 1.0f;

    if (this->swork[5] != 0) {
        this->swork[5]--;
        if (this->swork[5] == 0) {
            AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_EYE, gActors[10].sfxSource, 4);
            AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_EYE, gActors[11].sfxSource, 4);
            AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_SPARK, gActors[10].sfxSource, 4);
            AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_SPARK, gActors[11].sfxSource, 4);
        }
        gActors[10].obj.pos.x = this->obj.pos.x + 200.0f;
        gActors[10].obj.pos.y = this->obj.pos.y - 200.0f;
        gActors[10].obj.pos.z = this->obj.pos.z + 200.0f;
        gActors[10].state = 0;
        gActors[10].timer_0C2 = 20;
        gActors[10].info.targetOffset = 0.0f;
        gActors[11].obj.pos.x = this->obj.pos.x - 200.0f;
        gActors[11].obj.pos.y = this->obj.pos.y - 200.0f;
        gActors[11].obj.pos.z = this->obj.pos.z + 200.0f;
        gActors[11].state = 0;
        gActors[11].timer_0C2 = 20;
        gActors[11].info.targetOffset = 0.0f;
    }
    Math_SmoothStepToF(&this->fwork[21], this->fwork[22], 1.0f, 6.0f, 0);
    Math_SmoothStepToF(&this->fwork[23], this->fwork[24], 0.3f, 0.01f, 0);
}

bool Andross_8018B47C(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    Boss* this = (Boss*) thisx;

    if (this->fwork[21] >= 254.0f) {
        if (limbIndex == 2) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_22);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, (s32) this->fwork[25], 255, 255, 255);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_23);
        }
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_51);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, (s32) this->fwork[21]);
    }

    if ((limbIndex == 2) && (this->swork[6] != 0)) {
        *dList = NULL;
        return false;
    }

    if ((limbIndex == 1) || (limbIndex == 2)) {
        Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);
        if (*dList != NULL) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Push(&gCalcMatrix);
            Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);

            if (limbIndex == 1) {
                Matrix_RotateY(gGfxMatrix, -this->fwork[14] * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, this->fwork[16] + 1.0f, 1.0f, 1.0f - this->fwork[16], MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, this->fwork[14] * M_DTOR, MTXF_APPLY);
            } else {
                Matrix_RotateY(gGfxMatrix, this->fwork[14] * 1.5f * M_DTOR, MTXF_APPLY);
                Matrix_Scale(gGfxMatrix, 2.0f * this->fwork[16] + 1.0f, 1.0f, 1.0f - 2.0f * this->fwork[16],
                             MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, -this->fwork[14] * 1.5f * M_DTOR, MTXF_APPLY);
            }

            Matrix_SetGfxMtx(&gMasterDisp);

            if (((this->swork[3] % 2) != 0) && (this->fwork[21] >= 254.0f)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_27);
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

void Andross_AndBrain_Draw(AndBrain* this) {
    s32 j;
    s32 i;
    f32 temp;
    s32 pad;
    Vec3f spAC;
    Vec3f spA0;

    if (this->state != 21) {
        Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 20.0f * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, this->fwork[23] + 1.0f, 1.0f - this->fwork[23], 1.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 20.0f * M_DTOR, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, this->fwork[23] + 1.0f, 1.0f - this->fwork[23], 1.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, this->scale, this->scale, this->scale, MTXF_APPLY);
        Animation_DrawSkeleton(0, D_VE2_600C0A4, this->vwork, Andross_8018B47C, NULL, this, &gIdentityMatrix);
        if (this->fwork[21] >= 254) {
            RCP_SetupDL(&gMasterDisp, SETUPDL_54);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 64, 64, 255);
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_70);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 64, 64, (s32) this->fwork[21]);
        }
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        Matrix_Translate(gGfxMatrix, 0.0f, -16.0f, 0.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, 0.3f, 0.6f, 0.3f, MTXF_APPLY);

        for (i = 0; i < 30; i++) {
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateY(gCalcMatrix, i * 50.0f * M_DTOR, 0U);
            spAC.x = 0.0f;
            spAC.y = 0.0f;
            spAC.z = i * 0.8f;
            Matrix_MultVec3f(gCalcMatrix, &spAC, &spA0);
            Matrix_Translate(gGfxMatrix, spA0.x, 10.0f, spA0.z, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_DTOR * -this->obj.rot.y - gPlayer[0].camYaw, MTXF_APPLY);

            for (j = 0; j < 10; j++) {
                Matrix_Translate(gGfxMatrix, 0.0f, -10.0f, 0.0f, MTXF_APPLY);
                temp = SIN_DEG((s32) this->fwork[19] * (i * 10 + j) + (gGameFrameCount * 5)) * this->fwork[10];
                Matrix_RotateZ(gGfxMatrix, (this->fwork[18] + temp) * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, this->fwork[17] * M_DTOR, MTXF_APPLY);
                Matrix_Push(&gGfxMatrix);
                // @port: Tag the transform.
                FrameInterpolation_RecordOpenChild("Andross_AndBrain_Draw", i);

                Matrix_Translate(gGfxMatrix, 0.0f, -5.0f, 0.0f, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                if (j == 9) {
                    gSPDisplayList(gMasterDisp++, D_VE2_600C2D0);
                } else {
                    gSPDisplayList(gMasterDisp++, D_VE2_600C560);
                }
                Matrix_Pop(&gGfxMatrix);

                // @port Pop the transform id.
                FrameInterpolation_RecordCloseChild();
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

    if (gBossActive) {
        Math_SmoothStepToF(&D_Andross_801A7F58, 0.0f, 1.0f, 10.0f, 0.0f);
    } else {
        Math_SmoothStepToF(&D_Andross_801A7F58, D_Andross_801A7F60, 1.0f, 1.0f, 0.0f);
    }

    D_Andross_801A7F68 += D_Andross_801A7F70;
    Math_SmoothStepToF(&D_Andross_801A7F70, D_Andross_801A7F78, 1.0f, 0.1f, 0.0f);
}

void Andross_8018C390(Player* player) {
    player->boostCooldown = 1;
    player->barrelRollAlpha = 0;

    switch (player->csState) {
        case 0:
            Math_SmoothStepToF(&player->pos.x, gBosses[0].obj.pos.x, 0.5f, 30.0f, 0);
            Math_SmoothStepToF(&player->pos.y, gBosses[0].obj.pos.y - 150.0f, 0.5f, 30.0f, 0);
            Math_SmoothStepToF(&player->pos.z, gBosses[0].obj.pos.z - 100.0f, 0.5f, 60.0f, 0);

            gPathProgress = player->zPath = -player->pos.z;

            Math_SmoothStepToF(&player->cam.eye.z, 2000.0f, 0.05f, 20.0f, 0);
            Math_SmoothStepToF(&player->cam.eye.x, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->cam.eye.y, 0.0f, 0.05f, 10.0f, 0);

            Math_SmoothStepToF(&player->cam.at.x, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->cam.at.y, 0.0f, 0.05f, 10.0f, 0);
            Math_SmoothStepToF(&player->cam.at.z, 100.0f, 0.05f, 10.0f, 0.0f);
            break;

        case 1:
            player->rot.x += 15.0f;
            if (player->rot.x > 180.0f) {
                player->rot.x -= 360.0f;
            }

            player->rot.y += 9.0f;
            if (player->rot.y > 180.0f) {
                player->rot.y -= 360.0f;
            }

            Math_SmoothStepToF(&player->cam.eye.z, 400.0f, 0.05f, 20.0f, 0.0f);

            if (player->csTimer != 0) {
                if (gControllerPress[gMainController].button != 0) {
                    player->csTimer--;
                }
            }
            if (player->csTimer == 0) {
                player->state = PLAYERSTATE_ACTIVE;
                player->unk_014 = 0.0f;
                player->unk_018 = 0.0f;
            }
            break;

        case 2:
        case 3:
            break;
    }
    player->trueZpos = player->pos.z + player->camDist;
    Player_DamageEffects(player);
}

void Andross_Effect396_Setup1(Effect* this, f32 xPos, f32 yPos, f32 zPos, s32 arg4) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_396;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->unk_4C = arg4;
    this->scale2 = RAND_FLOAT(2.5f) + 5.0f;
    this->unk_60.x = RAND_FLOAT_CENTERED(20.0f);
    this->unk_60.y = RAND_FLOAT_CENTERED(20.0f);
    Object_SetInfo(&this->info, this->obj.id);
}

void Andross_Effect396_Spawn1(f32 xPos, f32 yPos, f32 zPos, s32 arg3) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_Effect396_Setup1(&gEffects[i], xPos, yPos, zPos, arg3);
            break;
        }
    }
}

void Andross_Effect396_Setup2(Effect396* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 arg7) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_396;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->state = 1;
    this->unk_4C = arg7;

    if (arg7 < 8) {
        this->scale2 = RAND_FLOAT(2.5f) + 5.0f;
    }

    this->obj.rot.x = RAND_FLOAT(360.0f);
    this->obj.rot.y = RAND_FLOAT(360.0f);
    this->unk_60.x = RAND_FLOAT(10.0f) + 10.0f;
    this->unk_60.y = RAND_FLOAT(10.0f) + 10.0f;
    Object_SetInfo(&this->info, this->obj.id);
    this->info.cullDistance = 100.0f;
}

void Andross_Effect396_Spawn2(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, s32 arg6) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_Effect396_Setup2(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, arg6);
            break;
        }
    }
}

void Andross_Effect396_Setup3(Effect396* this, f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    Effect_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_EFFECT_396;
    this->state = 10;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->vel.x = xVel;
    this->vel.y = yVel;
    this->vel.z = zVel;
    this->scale1 = scale;
    this->scale2 = scale * 0.1f;
    this->unk_44 = 100;
    this->obj.rot.z = RAND_FLOAT(360.0f);
    this->unk_60.z = RAND_FLOAT_CENTERED(20.0f);
    Object_SetInfo(&this->info, this->obj.id);
    this->info.unk_14 = 1;
    this->info.cullDistance = 100.0f;
}

void Andross_Effect396_Spawn3(f32 xPos, f32 yPos, f32 zPos, f32 xVel, f32 yVel, f32 zVel, f32 scale) {
    s32 i;

    for (i = ARRAY_COUNT(gEffects) - 1; i >= 0; i--) {
        if (gEffects[i].obj.status == OBJ_FREE) {
            Andross_Effect396_Setup3(&gEffects[i], xPos, yPos, zPos, xVel, yVel, zVel, scale);
            break;
        }
    }
}

void Andross_Effect396_Update(Effect396* this) {
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

    this->obj.rot.x += this->unk_60.x;
    this->obj.rot.y += this->unk_60.y;

    switch (this->state) {
        case 0:
            if (gBosses[0].state == 17) {
                Math_SmoothStepToF(&this->obj.pos.x, gBosses[0].obj.pos.x, 0.03f, 10.0f, 0);
                Math_SmoothStepToF(&this->obj.pos.y, gBosses[0].obj.pos.y - 200.0f, 0.03f, 10.0f, 0);

                effectXpos = this->obj.pos.x;
                effectYpos = this->obj.pos.y;
                effectZpos = this->obj.pos.z;

                sp3C = gBosses[0].obj.pos.x;
                sp38 = gBosses[0].obj.pos.y - 150.0f;
                sp34 = gBosses[0].obj.pos.z - 100.0f;

                yaw = Math_Atan2F(sp3C - effectXpos, sp34 - effectZpos);
                sp40 = sqrtf(SQ(sp3C - effectXpos) + SQ(sp34 - effectZpos));
                pitch = -Math_Atan2F(sp38 - effectYpos, sp40);

                Matrix_RotateY(gCalcMatrix, yaw, MTXF_NEW);
                Matrix_RotateX(gCalcMatrix, pitch, MTXF_APPLY);

                vec.x = 0.0f;
                vec.y = 0.0f;
                vec.z = 30.0f;

                Matrix_MultVec3f(gCalcMatrix, &vec, &vel);

                this->vel.x = vel.x;
                this->vel.y = vel.y;
                this->vel.z = vel.z - gPathVelZ;

                if ((fabsf(this->obj.pos.x - gBosses[0].obj.pos.x) <= 100.0f) &&
                    (fabsf(this->obj.pos.z - (gBosses[0].obj.pos.z - 100.0f)) <= 100.0f)) {
                    Object_Kill(&this->obj, this->sfxSource);
                }
            } else {
                this->info.cullDistance = 100.0f;
                Math_SmoothStepToF(&this->vel.x, 0.0f, 0.05f, 1.0f, 0);
                Math_SmoothStepToF(&this->vel.y, 0.0f, 0.05f, 1.0f, 0);
                Math_SmoothStepToF(&this->vel.z, 70.0f, 0.05f, 2.0f, 0);

                func_effect_8007A774(&gPlayer[0], this, 100.0f);

                if (this->unk_44 != 0) {
                    func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                    Object_Kill(&this->obj, this->sfxSource);
                }
            }
            this->unk_44 = 0;
            break;

        case 1:
            func_effect_8007A774(&gPlayer[0], this, 100.0f);
            if (this->unk_44 != 0) {
                func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 10.0f);
                Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
                Object_Kill(&this->obj, this->sfxSource);
                if (Rand_ZeroOne() < 0.1f) {
                    item = &gItems[0];
                    for (i = 0; i < ARRAY_COUNT(gItems); i++, item++) {
                        if (item->obj.status == OBJ_FREE) {
                            Item_Initialize(item);
                            item->obj.status = OBJ_INIT;
                            if (Rand_ZeroOne() < 0.5f) {
                                item->obj.id = OBJ_ITEM_SILVER_RING;
                            } else {
                                item->obj.id = OBJ_ITEM_BOMB;
                            }
                            item->obj.pos.x = this->obj.pos.x;
                            item->obj.pos.y = this->obj.pos.y;
                            item->obj.pos.z = this->obj.pos.z;
                            item->timer_4A = 8;
                            item->unk_50 = 90.0f;
                            CALL_CANCELLABLE_EVENT(ItemDropEvent, item) {
                                Object_SetInfo(&item->info, item->obj.id);
                            }
                            break;
                        }
                    }
                }
            }
            break;

        case 10:
            this->obj.rot.z += this->unk_60.z;

            Math_SmoothStepToF(&this->scale2, this->scale1, 0.05f, 0.3f, 0);
            Math_SmoothStepToF(&this->vel.y, 0.0f, 0.05f, 0.5f, 0.0f);
            Math_SmoothStepToF(&this->vel.x, 0.0f, 0.05f, 0.5f, 0.0f);

            this->unk_44 -= 10;
            if (this->unk_44 < 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}

Gfx* D_i6_801A6790[10] = {
    D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880,
    D_ANDROSS_C001880, D_ANDROSS_C001880, D_ANDROSS_C001880, aAwLeftWingDL,     aAwRightWingDL,
};

void Andross_Effect396_Draw(Effect396* this) {
    if (this->state == 10) {
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, this->unk_44);
        Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_BG_PLANET_2010A30);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
        if (this->unk_4C < 8) {
            Matrix_Scale(gGfxMatrix, this->scale2, this->scale2, this->scale2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
        }
        gSPDisplayList(gMasterDisp++, D_i6_801A6790[this->unk_4C]);
        RCP_SetupDL(&gMasterDisp, SETUPDL_64);
    }
}

void Andross_8018D0D8(AndAndross* this) {
    if ((gPlayer[0].mercyTimer == 0) && (gPlayer[0].state == PLAYERSTATE_ACTIVE) &&
        (fabsf(this->vwork[10].x - gPlayer[0].pos.x) < 700.0f) &&
        (fabsf(this->vwork[10].y - gPlayer[0].pos.y) < 700.0f)) {
        Player_ApplyDamage(&gPlayer[0], 0, 40);
    }
}

void Andross_AndAndross_Init(AndAndross* this) {
    Audio_SetEnvSfxReverb(24);
    D_i6_801A7F5C = D_i6_801A7F64 = D_i6_801A7F6C = D_i6_801A7F74 = D_i6_801A7F7C = D_i6_801A8430 = 0.0f;
    gAndrossUnkAlpha = 0.0f;
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
    gBossActive = true;
    gDrawBackdrop = 1;
    this->info.hitbox[16] = 200.0f;
    this->info.hitbox[22] = 200.0f;
    Audio_PlaySequence(SEQ_PLAYER_BGM, NA_BGM_BOSS_ANDROSS, 0, 0);
}

void Andross_8018D2B0(AndAndross* this) {
    s32 i;
    Vec3f sp68;

    if ((this->swork[5] < 0) && (this->swork[4] < 0)) {
        if ((this->dmgType != DMG_NONE) && (this->dmgPart == 0 || this->dmgPart == 1)) {
            this->dmgType = DMG_NONE;
            if (this->state < 12) {
                this->health -= this->damage;
                this->timer_05C = 20;
                if ((this->state == 9) || (this->state == 10)) {
                    if (this->health <= 0) {
                        gScreenFlashTimer = 8;

                        AUDIO_PLAY_SFX(NA_SE_EN_DOWN_IMPACT, this->sfxSource, 4);
                        AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_EXPLOSION, this->sfxSource, 4);
                        AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_DEATH, this->sfxSource, 4);

                        Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ANDROSS_ROBOT);

                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);

                        this->state = 31;
                        this->timer_050 = 200;
                        gPlayer[0].state = PLAYERSTATE_LEVEL_COMPLETE;
                        gPlayer[0].csState = 0;
                    } else if (this->health < 50) {
                        AUDIO_PLAY_SFX(NA_SE_EN_KNOCK_DOWN, this->sfxSource, 4);
                    } else {
                        AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                    }
                } else if (this->health <= 0) {
                    AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_DEATH, this->sfxSource, 4);

                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
                    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);

                    if (gLevelPhase == 0) {
                        this->state = 30;
                    } else {
                        this->state = 32;
                    }
                    this->fwork[9] = 0.0f;
                    this->animFrame = 0;
                    gCsFrameCount = 0;
                    this->timer_05C = 100;
                } else {
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                }
            }
        }
    } else if (this->dmgType != DMG_NONE) {
        switch (this->dmgPart) {
            case 0:
                if (this->state < 11) {
                    this->swork[6] -= this->damage;
                    this->swork[0] = 30;
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                    if (this->swork[6] <= 0) {
                        this->swork[6] = 100;
                        this->state = 12;
                        this->timer_050 = 120;
                        this->animFrame = 0;
                        this->fwork[9] = 0.0f;
                        AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_GROAN, this->sfxSource, 4);
                    }
                }
                break;

            case 1:
                if (this->state < 12) {
                    this->swork[6] -= this->damage;
                    this->swork[1] = 30;
                    AUDIO_PLAY_SFX(NA_SE_OB_DAMAGE_M, this->sfxSource, 4);
                    if (this->swork[6] <= 0) {
                        this->swork[6] = 100;
                        this->state = 13;
                        this->timer_050 = 120;
                        this->animFrame = 0;
                        this->fwork[9] = 0.0f;
                        AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_GROAN, this->sfxSource, 4);
                    }
                }
                break;

            case 2:
            case 3:
                if (this->swork[7] == 0) {
                    this->swork[this->dmgPart] = 30;
                    if (this->dmgPart == 2) {
                        sp68.x = this->vwork[0].x;
                        sp68.y = this->vwork[0].y;
                        sp68.z = this->vwork[0].z;

                        this->swork[4] -= this->damage;

                        if (this->swork[4] < 0) {
                            this->info.hitbox[16] = 0.0f;
                            Effect386_Spawn1(this->vwork[0].x, this->vwork[0].y, this->vwork[0].z, 0.0f, 0.0f, 0.0f,
                                             20.0f, 15);

                            for (i = 0; i < 30; i++) {
                                Effect_Effect357_Spawn50(this->vwork[0].x + RAND_FLOAT_CENTERED(500.0f),
                                                         this->vwork[0].y + RAND_FLOAT_CENTERED(500.0f),
                                                         this->vwork[0].z, RAND_FLOAT(1.0f) + 1.0f);
                            }
                            Effect_Effect384_Spawn(this->vwork[0].x, this->vwork[0].y, this->vwork[0].z, 20.0f, 5);
                            Effect_SpawnTimedSfxAtPos(&sp68, NA_SE_EN_EXPLOSION_M);
                        } else {
                            Effect_SpawnTimedSfxAtPos(&sp68, NA_SE_OB_DAMAGE_M);
                        }
                    } else {
                        sp68.x = this->vwork[1].x;
                        sp68.y = this->vwork[1].y;
                        sp68.z = this->vwork[1].z;

                        this->swork[5] -= this->damage;

                        if (this->swork[5] < 0) {
                            this->info.hitbox[22] = 0.0f;
                            Effect386_Spawn1(this->vwork[1].x, this->vwork[1].y, this->vwork[1].z, 0.0f, 0.0f, 0.0f,
                                             20.0f, 15);

                            for (i = 0; i < 30; i++) {
                                Effect_Effect357_Spawn50(this->vwork[1].x + RAND_FLOAT_CENTERED(500.0f),
                                                         this->vwork[1].y + RAND_FLOAT_CENTERED(500.0f),
                                                         this->vwork[1].z, RAND_FLOAT(1.0f) + 1.0f);
                            }
                            Effect_Effect384_Spawn(this->vwork[1].x, this->vwork[1].y, this->vwork[1].z, 20.0f, 5);
                            Effect_SpawnTimedSfxAtPos(&sp68, NA_SE_EN_EXPLOSION_M);
                        } else {
                            Effect_SpawnTimedSfxAtPos(&sp68, NA_SE_OB_DAMAGE_M);
                        }
                    }
                }
                break;
        }
        this->dmgType = DMG_NONE;
    }
}

void Andross_8018D9C0(AndAndross* this) {
    switch (this->state) {
        case 2:
            this->state = 3;
            break;

        case 3:
            this->state = 4;
            break;

        case 4:
            this->state = 5;
            this->timer_050 = 30;
            break;

        case 5:
            this->state = 6;
            this->timer_050 = 40;
            break;

        case 6:
            this->state = 17;
            this->timer_050 = 180;
            this->fwork[16] = 0.0f;
            break;

        case 12:
        case 13:
        case 14:
            this->state = 7;
            this->timer_050 = 150;
            break;

        default:
            this->state = 2;
            break;
    }
    this->fwork[9] = 0.0f;
    this->animFrame = 0;
    this->fwork[1] = 0.0f;
    this->fwork[4] = 0.0f;
    this->fwork[7] = 0.0f;
}

void Andross_8018DA94(AndAndross* this, Vec3f* arg1) {
    s32 i;

    Effect386_Spawn1(arg1->x, arg1->y, arg1->z, 0.0f, 0.0f, 0.0f, 10.0f, 10);
    for (i = 0; i < 7; i++) {
        Effect_Effect357_Spawn50(RAND_FLOAT_CENTERED(200.0f) + arg1->x, RAND_FLOAT_CENTERED(200.0f) + arg1->y, arg1->z,
                                 RAND_FLOAT(0.5f) + 1.0f);
    }
    Effect_Effect384_Spawn(arg1->x, arg1->y, arg1->z, 10.0f, 5);
    AUDIO_PLAY_SFX(NA_SE_EN_EXPLOSION_M, this->sfxSource, 4);
}

f32 D_i6_801A67B8[] = { 0.0f, 0.0f, 0.0f };

void Andross_AndAndross_Update(AndAndross* this) {
    s32 i;
    s32 frameCountMask;
    Vec3f spD0[100];
    f32 xDisplacement;
    f32 yDisplacement;
    f32 zDisplacement;
    Effect* effect;
    PlayerShot* playerShot;
    Boss* boss1;
    Player* player = &gPlayer[0];
    f32 yaw;
    f32 pitch;
    s16 limbCount;
    s32 initialstate;
    s32 pad;

    gBossFrameCount++;

    initialstate = this->state;

    Andross_801876FC();

    gAmbientR = 10;
    gAmbientG = 0;
    gAmbientB = 20;
    gGroundClipMode = 0;

    this->fwork[19] += 5.0f;

    if (this->swork[9] != 0) {
        this->swork[9]--;
        Math_SmoothStepToF(&this->fwork[17], 1.5f, 0.7f, 0.4f, 0);
    } else {
        Math_SmoothStepToF(&this->fwork[17], 1.0f, 0.2f, 0.3f, 0);
    }

    this->fwork[18] = this->fwork[17];

    if (this->swork[10] != 0) {
        this->swork[10]--;
        if (this->swork[10] < 20) {
            frameCountMask = 32 - 1;
        } else if (this->swork[10] < 30) {
            frameCountMask = 8 - 1;
        } else if (this->swork[10] < 40) {
            frameCountMask = 2 - 1;
        } else {
            frameCountMask = 1 - 1;
        }

        if ((gGameFrameCount & frameCountMask) == 0) {
            Andross_Effect396_Spawn3(this->vwork[6].x, this->vwork[6].y, this->vwork[6].z, 0.0f, -30.0f, 0.0f, 30.0f);
            Andross_Effect396_Spawn3(this->vwork[7].x, this->vwork[7].y, this->vwork[7].z, 0.0f, -30.0f, 0.0f, 30.0f);
            Andross_Effect396_Spawn3(this->vwork[8].x, this->vwork[8].y, this->vwork[8].z, -30.0f, 0.0f, 0.0f, 30.0f);
            Andross_Effect396_Spawn3(this->vwork[9].x, this->vwork[9].y, this->vwork[9].z, 30.0f, 0.0f, 0.0f, 30.0f);
        }
    }

    Math_SmoothStepToF(&this->fwork[20], 0.0f, 1.0f, 0.1f, 0.01f);
    Math_SmoothStepToF(&this->fwork[21], 0.0f, 1.0f, 0.05f, 0.001f);

    Andross_8018D2B0(this);

    this->swork[7] = 0;
    this->fwork[14] = this->fwork[15] = 0.0f;

    if (this->state >= 2) {
        gBlurAlpha = 128;
    }

    for (i = 0; i < 4; i++) {
        if (this->swork[i] > 0) {
            this->swork[i]--;
        }
    }

    Math_SmoothStepToF(&this->obj.pos.z, gPlayer[0].pos.z + this->fwork[6], this->fwork[8], this->fwork[7], 0);
    Math_SmoothStepToF(&this->obj.pos.x, this->fwork[0], this->fwork[2], this->fwork[1], 0);
    Math_SmoothStepToF(&this->obj.pos.y, this->fwork[3], this->fwork[5], this->fwork[4], 0);

    Math_SmoothStepToF(&this->fwork[11], 0.0f, 0.1f, 2.0f, 0);
    Math_SmoothStepToF(&this->fwork[12], 0.0f, 0.1f, 2.0f, 0);
    Math_SmoothStepToF(&this->fwork[13], 0.0f, 0.1f, 2.0f, 0);

    if (player->draw) {
        xDisplacement = gPlayer[0].pos.x - this->vwork[2].x;
        yDisplacement = gPlayer[0].pos.y - this->vwork[2].y;
        zDisplacement = gPlayer[0].trueZpos - this->vwork[2].z;
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

    Math_SmoothStepToAngle(&this->vwork[4].x, pitch, 0.5f, 5.0f, 0);
    Math_SmoothStepToAngle(&this->vwork[4].y, yaw, 0.5f, 5.0f, 0);

    if (player->draw) {
        xDisplacement = gPlayer[0].pos.x - this->vwork[3].x;
        yDisplacement = gPlayer[0].pos.y - this->vwork[3].y;
        zDisplacement = gPlayer[0].trueZpos - this->vwork[3].z;

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

    Math_SmoothStepToAngle(&this->vwork[5].x, pitch, 0.5f, 5.0f, 0);
    Math_SmoothStepToAngle(&this->vwork[5].y, yaw, 0.5f, 5.0f, 0);

    switch (this->state) {
        case 0:
            this->fwork[8] = 0.1f;
            this->fwork[7] = 50.0f;
            this->state = 1;
            this->timer_050 = 60;
            this->timer_052 = 80;
            this->timer_054 = 150;
            this->fwork[9] = 1.0f;
            /* fallthrough */
        case 1:
            this->timer_05A = 100;
            if (this->timer_054 == 65) {
                AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_LAUGH, this->sfxSource, 4);
            }

            if (this->timer_050 != 0) {
                this->fwork[6] = -3000.0f;
            } else {
                this->fwork[6] = -1000.0f;
                Math_SmoothStepToF(&D_i6_801A7F5C, gLight1R, 1.0f, 4.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F64, gLight1G, 1.0f, 3.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F6C, gLight1B, 1.0f, 3.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F74, gAmbientR, 1.0f, 2.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A7F7C, gAmbientG, 1.0f, 2.0f, 0.0f);
                Math_SmoothStepToF(&D_i6_801A8430, gAmbientB, 1.0f, 2.0f, 0.0f);
            }

            Math_SmoothStepToF(&gAndrossUnkAlpha, 32.0f, 1.0f, 0.5f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.2f, 3.0f, 0);

            this->fwork[8] = 0.1f;

            Math_SmoothStepToF(&this->fwork[7], 200.0f, 1.0f, 10.0f, 0);

            if (this->timer_052 == 0) {
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C002B08)) {
                    this->animFrame = 0;
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C002B08, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            } else {
                if (this->timer_052 < 16) {
                    this->animFrame++;
                    if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C033D98)) {
                        this->animFrame = Animation_GetFrameCount(&D_ANDROSS_C033D98) - 1;
                    }
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C033D98, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
                if (this->timer_052 == 1) {
                    this->animFrame = 0;
                }
            }

            Math_SmoothStepToF(&this->fwork[9], 0.2f, 1.0f, 0.01f, 0);

            if (this->timer_054 == 0) {
                this->state = 2;
                this->animFrame = 0;
                this->fwork[7] = this->fwork[9] = 0.0f;
                this->vel.z = -20.0f;
            }
            break;

        case 2:
            this->fwork[6] = -4000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 30.0f, 1.0f, 5.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[2] = 0.05f;
            this->fwork[3] = 0.0f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 10.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&this->fwork[4], 10.0f, 1.0f, 0.5f, 0);
            Math_SmoothStepToF(&this->fwork[9], 0.7f, 1.0f, 0.005f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C033780)) {
                Andross_8018D9C0(this);
            }
            limbCount = Animation_GetFrameData(&D_ANDROSS_C033780, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            break;

        case 3:
            if (this->swork[4] < 0) {
                Andross_8018D9C0(this);
            } else {
                this->fwork[0] = player->pos.x;
                this->fwork[3] = player->pos.y + 1000.0f;

                if (this->animFrame == 60) {
                    AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_PUNCH, this->sfxSource, 4);
                }
                if (this->animFrame > 60) {
                    if (this->animFrame == 76) {
                        this->fwork[7] = 0.0f;
                    }
                    if (this->animFrame > 76) {
                        this->fwork[6] = -2500.0f;
                        this->fwork[8] = 0.1f;
                        Math_SmoothStepToF(&this->fwork[7], 100.0f, 1.0f, 10.0f, 0);
                    } else {
                        this->fwork[6] = -1500.0f;
                        this->fwork[8] = 0.3f;
                        Math_SmoothStepToF(&this->fwork[7], 200.0f, 1.0f, 40.0f, 0);
                    }

                    this->fwork[2] = 0.05f;
                    this->fwork[5] = 0.05f;

                    Math_SmoothStepToF(&this->fwork[1], 2.0f, 1.0f, 0.5f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 2.0f, 1.0f, 0.5f, 0);

                    this->swork[7] = 1;
                    this->fwork[14] = -100.0f;
                    this->fwork[15] = -50.0f;
                } else {
                    this->fwork[6] = -4000.0f;
                    this->fwork[8] = 0.05f;

                    Math_SmoothStepToF(&this->fwork[7], 30.0f, 1.0f, 2.0f, 0);

                    this->fwork[2] = 0.1f;
                    this->fwork[5] = 0.1f;
                    this->fwork[14] = 50.0f;

                    Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 20.0f, 1.0f, 1.0f, 0);
                }

                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C029F74)) {
                    Andross_8018D9C0(this);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C029F74, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;

        case 4:
            if (this->swork[4] < 0) {
                Andross_8018D9C0(this);
            } else {
                this->fwork[0] = player->pos.x;
                this->fwork[3] = player->pos.y;

                if (this->animFrame == 55) {
                    AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_PUNCH, this->sfxSource, 4);
                }
                if (this->animFrame > 55) {
                    this->fwork[6] = -1500.0f;
                    this->fwork[8] = 0.3f;
                    Math_SmoothStepToF(&this->fwork[7], 200.0f, 1.0f, 40.0f, 0);
                    this->swork[7] = 1;
                    this->fwork[2] = 0.05f;
                    this->fwork[5] = 0.05f;
                    this->fwork[14] = -100.0f;
                    Math_SmoothStepToF(&this->fwork[1], 2.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 2.0f, 1.0f, 1.0f, 0);
                } else {
                    this->fwork[6] = -4000.0f;
                    this->fwork[8] = 0.05f;
                    Math_SmoothStepToF(&this->fwork[7], 30.0f, 1.0f, 2.0f, 0);
                    this->fwork[2] = 0.1f;
                    this->fwork[5] = 0.1f;
                    this->fwork[14] = 50.0f;
                    Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 1.0f, 0);
                }

                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C02E494)) {
                    Andross_8018D9C0(this);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C02E494, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;

        case 5:
            if (this->swork[5] < 0) {
                Andross_8018D9C0(this);
            } else {
                this->fwork[0] = player->pos.x;
                this->fwork[3] = player->pos.y + 500.0f;
                if (this->timer_050 != 0) {
                    this->fwork[6] = -4000.0f;
                    this->fwork[8] = 0.05f;

                    Math_SmoothStepToF(&this->fwork[7], 30.0f, 1.0f, 5.0f, 0);

                    this->fwork[2] = 0.1f;
                    this->fwork[5] = 0.1f;

                    Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 2.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 2.0f, 0);
                } else {
                    this->animFrame++;

                    this->fwork[6] = -1400.0f;
                    this->fwork[8] = 0.2f;

                    Math_SmoothStepToF(&this->fwork[7], 200.0f, 1.0f, 40.0f, 0);

                    this->fwork[2] = 0.05f;
                    this->fwork[5] = 0.05f;

                    Math_SmoothStepToF(&this->fwork[1], 2.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 2.0f, 1.0f, 1.0f, 0);

                    if (this->animFrame == 5) {
                        AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_SLAP, this->sfxSource, 4);
                    }
                    this->swork[7] = 1;
                    this->fwork[14] = 100.0f;
                }
                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C030244)) {
                    Andross_8018D9C0(this);
                }

                limbCount = Animation_GetFrameData(&D_ANDROSS_C030244, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 6:
            if ((this->swork[4] < 0) || (this->swork[5] < 0)) {
                Andross_8018D9C0(this);
            } else {
                if (this->timer_050 == 1) {
                    AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_WHAND, this->sfxSource, 4);
                }
                if (this->timer_050 != 0) {
                    this->fwork[6] = -4000.0f;
                    this->fwork[8] = 0.05f;

                    Math_SmoothStepToF(&this->fwork[7], 40.0f, 1.0f, 3.0f, 0);

                    this->fwork[2] = 0.05f;
                    this->fwork[5] = 0.05f;

                    Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 1.0f, 0);

                    this->fwork[0] = player->pos.x;
                    this->fwork[3] = player->pos.y + 300.0f;
                } else {
                    this->animFrame++;

                    this->fwork[6] = -2000.0f;
                    this->fwork[8] = 0.2f;

                    Math_SmoothStepToF(&this->fwork[7], 50.0f, 1.0f, 10.0f, 0);

                    this->fwork[2] = 0.1f;
                    this->fwork[5] = 0.1f;

                    Math_SmoothStepToF(&this->fwork[1], 10.0f, 1.0f, 1.0f, 0);
                    Math_SmoothStepToF(&this->fwork[4], 10.0f, 1.0f, 1.0f, 0);

                    this->swork[7] = 1;

                    if (this->animFrame > 18) {
                        Math_SmoothStepToF(&this->fwork[11], 110.0f, 1.0f, 18.0f, 0);
                        Math_SmoothStepToF(&this->fwork[12], 20.0f, 1.0f, 3.6f, 0);
                        Math_SmoothStepToF(&this->fwork[13], 80.0f, 1.0f, 15.0f, 0);
                    }
                    if (this->animFrame == 25) {
                        // Why tank?
                        AUDIO_PLAY_SFX(NA_SE_TANK_BOUND, D_i6_801A67B8, 4);
                    }
                }
                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C02EDA0)) {
                    Andross_8018D9C0(this);
                }
                limbCount = Animation_GetFrameData(&D_ANDROSS_C02EDA0, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;

        case 7:
            if (this->swork[5] < 0) {
                Andross_8018D9C0(this);
            } else {
                if (this->animFrame == 48) {
                    AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_SPARK, this->sfxSource, 4);
                }
                if (this->animFrame > 48) {
                    Andross_8018D0D8(this);
                }
                if (this->animFrame > 45) {
                    Math_SmoothStepToF(&this->fwork[20], 1.0f, 1.0f, 0.2f, 0.01f);
                    Math_SmoothStepToF(&this->fwork[21], 1.0f, 0.5f, 0.15f, 0.01f);
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
                    Math_SmoothStepToF(&this->fwork[20], 0.15f, 1.0f, 0.15f, 0.01f);
                    Math_SmoothStepToF(&this->fwork[21], 0.5f, 1.0f, 0.11f, 0.001f);
                }

                this->fwork[0] = player->pos.x + 500.0f;
                this->fwork[3] = player->pos.y + 750.0f;
                this->fwork[6] = -5000.0f;
                this->fwork[8] = 0.05f;

                Math_SmoothStepToF(&this->fwork[7], 60.0f, 1.0f, 5.0f, 0);

                this->fwork[2] = 0.05f;
                this->fwork[5] = 0.05f;

                Math_SmoothStepToF(&this->fwork[1], 5.0f, 1.0f, 2.0f, 0);
                Math_SmoothStepToF(&this->fwork[4], 5.0f, 1.0f, 2.0f, 0);
                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C018BC4)) {
                    this->animFrame = Animation_GetFrameCount(&D_ANDROSS_C018BC4) - 1;
                    if (this->timer_050 == 0) {
                        Andross_8018D9C0(this);
                    }
                }

                limbCount = Animation_GetFrameData(&D_ANDROSS_C018BC4, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;

        case 12:
            if ((this->swork[4] < 0) || (this->swork[5] < 0)) {
                this->state = 14;
                this->animFrame = 0;
                this->fwork[9] = 0.0f;
            } else {
                this->fwork[6] = -3000.0f;
                this->fwork[8] = 0.05f;

                Math_SmoothStepToF(&this->fwork[7], 40.0f, 1.0f, 2.0f, 0);

                this->fwork[2] = 0.05f;
                this->fwork[5] = 0.05f;

                Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
                Math_SmoothStepToF(&this->fwork[4], 20.0f, 1.0f, 1.0f, 0);

                this->fwork[0] = player->pos.x;
                this->fwork[3] = player->pos.y;

                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C025C00)) {
                    this->animFrame = Animation_GetFrameCount(&D_ANDROSS_C025C00) - 1;
                    if (this->timer_050 == 0) {
                        Andross_8018D9C0(this);
                    }
                }

                limbCount = Animation_GetFrameData(&D_ANDROSS_C025C00, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;
        case 13:
            if ((this->swork[4] < 0) || (this->swork[5] < 0)) {
                this->state = 14;
                this->animFrame = 0;
                this->fwork[9] = 0.0f;
            } else {
                this->fwork[6] = -3000.0f;
                this->fwork[8] = 0.05f;

                Math_SmoothStepToF(&this->fwork[7], 20.0f, 1.0f, 2.0f, 0);

                this->fwork[2] = 0.05f;
                this->fwork[5] = 0.05f;

                Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
                Math_SmoothStepToF(&this->fwork[4], 20.0f, 1.0f, 1.0f, 0);

                this->fwork[0] = player->pos.x;
                this->fwork[3] = player->pos.y;

                Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C006F08)) {
                    this->animFrame = Animation_GetFrameCount(&D_ANDROSS_C006F08) - 1;
                    if (this->timer_050 == 0) {
                        Andross_8018D9C0(this);
                    }
                }

                limbCount = Animation_GetFrameData(&D_ANDROSS_C006F08, this->animFrame, spD0);
                Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            }
            break;

        case 14:
            this->fwork[6] = -3000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 20.0f, 1.0f, 2.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 20.0f, 1.0f, 1.0f, 0);

            this->fwork[0] = player->pos.x;
            this->fwork[3] = player->pos.y;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C002654)) {
                this->animFrame = 0;
                if (this->timer_050 == 0) {
                    Andross_8018D9C0(this);
                }
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C002654, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            break;

        case 15:
            if (this->swork[8] == 1) {
                this->fwork[6] = 100.0f;
            } else {
                this->fwork[6] = -3000.0f;
            }
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 60.0f, 1.0f, 5.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 20.0f, 1.0f, 1.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[3] = 0.0f;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

            if (this->animFrame == 15) {
                AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_BITE0, this->sfxSource, 4);
            }
            if ((this->animFrame > 35) && (this->animFrame < 150) && ((this->animFrame % 32) == 0)) {
                AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_BITE1, this->sfxSource, 4);
                if (player->state == PLAYERSTATE_ANDROSS_MOUTH) {
                    gControllerRumbleTimers[0] = 10;
                }
            }
            if ((this->animFrame == 20) && (player->state == PLAYERSTATE_ANDROSS_MOUTH)) {
                player->draw = false;
                for (i = 0; i < ARRAY_COUNT(gEffects); i++) {
                    if (gEffects[i].obj.id == OBJ_EFFECT_396) {
                        Object_Kill(&gEffects[i].obj, gEffects[i].sfxSource);
                    }
                }
            }

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C00DE48)) {
                this->animFrame = Animation_GetFrameCount(&D_ANDROSS_C00DE48) - 1;
                if (this->timer_050 == 0) {
                    this->state = 16;
                    this->animFrame = 0;
                    this->timer_050 = 30;
                    this->fwork[9] = 0.0f;
                }
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C00DE48, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);

            if ((this->animFrame == 45) && (this->swork[8] == 2)) {
                this->state = 18;
                this->animFrame = 0;
                this->work_044 = 0;
                this->timer_050 = 40;
                this->fwork[9] = 0.0f;
            }
            break;

        case 16:
            if (this->swork[8] == 1) {
                this->fwork[6] = 100.0f;
            } else {
                this->fwork[6] = -3000.0f;
            }
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 50.0f, 1.0f, 2.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 20.0f, 1.0f, 1.0f, 0);

            this->fwork[0] = player->pos.x;
            this->fwork[3] = player->pos.y + 100.0f;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

            if (this->timer_050 == 0) {
                this->animFrame++;
                if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C023B54)) {
                    this->animFrame = Animation_GetFrameCount(&D_ANDROSS_C023B54) - 1;
                    Andross_8018D9C0(this);
                }
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C023B54, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);

            if (this->animFrame == 10) {
                AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_VOMIT, this->sfxSource, 4);
            }

            if ((this->animFrame == 13) && (player->state == PLAYERSTATE_ANDROSS_MOUTH)) {
                player->draw = true;
                player->csState = 1;
                player->csTimer = 60;
                player->mercyTimer = 50;
                this->swork[8] = 0;
                gControllerRumbleTimers[0] = 30;

                if (player->arwing.rightWingState == 2) {
                    gRightWingHealth[0] = 0;
                    player->arwing.rightWingState = 1;
                    Andross_Effect396_Spawn2(this->obj.pos.x, this->obj.pos.y - 200.0f, this->obj.pos.z,
                                             RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f), 10.0f, 8);
                }
                if (player->arwing.leftWingState == 2) {
                    gLeftWingHealth[0] = 0;
                    player->arwing.leftWingState = 1;
                    Andross_Effect396_Spawn2(this->obj.pos.x, this->obj.pos.y - 200.0f, this->obj.pos.z,
                                             RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT_CENTERED(10.0f), 10.0f, 9);
                }
            }
            if ((this->animFrame >= 10) && (this->animFrame < 20)) {
                for (i = 0; i < 10; i++) {
                    Andross_Effect396_Spawn2(this->obj.pos.x + RAND_FLOAT_CENTERED(100.0f),
                                             (this->obj.pos.y - 200.0f) + RAND_FLOAT_CENTERED(100.0f), this->obj.pos.z,
                                             RAND_FLOAT_CENTERED(50.0f), RAND_FLOAT_CENTERED(50.0f),
                                             RAND_FLOAT(5.0f) + 5.0f, RAND_INT(7.9));
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
            this->timer_056 = 50;

            if ((this->timer_050 > 70) && (this->timer_050 < 1000) && ((gGameFrameCount % 4) == 0)) {
                Andross_Effect396_Spawn1(gPlayer[0].cam.eye.x + RAND_FLOAT_CENTERED(3000.0f),
                                         gPlayer[0].cam.eye.y + RAND_FLOAT_CENTERED(3000.0f),
                                         gPlayer[0].cam.eye.z - gPathProgress, RAND_INT(7.9));
            }
            if (this->timer_050 > 0) {
                playerShot = gPlayerShots;
                effect = gEffects;
                for (i = 0; i < ARRAY_COUNT(gPlayerShots); i++, playerShot++) {
                    Math_SmoothStepToF(&playerShot->obj.pos.x, this->obj.pos.x, 0.5f, this->fwork[16], 0);
                    Math_SmoothStepToF(&playerShot->obj.pos.y, this->obj.pos.y - 100.0f, 0.5f, this->fwork[16], 0);

                    Math_SmoothStepToF(&playerShot->vel.x, 0.0f, 0.9f, 5.0f, 0);
                    Math_SmoothStepToF(&playerShot->vel.y, 0.0f, 0.9f, 5.0f, 0);

                    if ((playerShot->obj.id == PLAYERSHOT_BOMB) && (playerShot->obj.status == 1) &&
                        (playerShot->unk_5C == 0) && (fabsf(playerShot->obj.pos.x - this->obj.pos.x) < 200.0f) &&
                        (fabsf(playerShot->obj.pos.y - (this->obj.pos.y - 100.0f)) < 200.0f) &&
                        (fabsf(playerShot->obj.pos.z - (this->obj.pos.z - 200.0f)) < 100.0f)) {
                        Object_Kill(&playerShot->obj, playerShot->sfxSource);
                        this->state = 15;
                        this->fwork[9] = 0.2f;
                        this->animFrame = 0;
                        this->swork[8] = 2;
                        AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_CHOKE, this->sfxSource, 4);
                        break;
                    }
                }

                for (i = 0; i < ARRAY_COUNT(gEffects); i++, effect++) {
                    if ((effect->obj.status != OBJ_FREE) && (effect->obj.id != OBJ_EFFECT_396)) {
                        Math_SmoothStepToF(&effect->obj.pos.x, this->obj.pos.x, 0.5f, this->fwork[16], 0);
                        Math_SmoothStepToF(&effect->obj.pos.y, this->obj.pos.y - 100.0f, 0.5f, this->fwork[16], 0);
                        Math_SmoothStepToF(&effect->obj.pos.z, this->obj.pos.z - 200.0f, 0.5f, this->fwork[16], 0);

                        Math_SmoothStepToF(&effect->vel.x, 0.0f, 0.9f, 5.0f, 0);
                        Math_SmoothStepToF(&effect->vel.y, 0.0f, 0.9f, 5.0f, 0);
                        Math_SmoothStepToF(&effect->vel.z, 0.0f, 0.9f, 10.0f, 0);

                        if ((fabsf(effect->obj.pos.x - this->obj.pos.x) < 200.0f) &&
                            (fabsf(effect->obj.pos.y - (this->obj.pos.y - 100.0f)) < 200.0f) &&
                            (fabsf(effect->obj.pos.z - (this->obj.pos.z - 200.0f)) < 100.0f)) {
                            Object_Kill(&effect->obj, effect->sfxSource);
                        }
                    }
                }

                Math_SmoothStepToF(&player->pos.x, this->obj.pos.x, 0.1f, this->fwork[16], 0);
                Math_SmoothStepToF(&player->pos.y, this->obj.pos.y - 150.0f, 0.1f, this->fwork[16], 0);
                Math_SmoothStepToF(&this->fwork[16], 35.0f, 1.0f, 0.5f, 0);

                if (fabsf(player->trueZpos - this->obj.pos.z) < 200.0f) {
                    this->state = 15;
                    this->swork[8] = 1;
                    this->fwork[9] = 0.2f;
                    this->animFrame = 0;
                    if (player->state == PLAYERSTATE_ACTIVE) {
                        player->state = PLAYERSTATE_ANDROSS_MOUTH;
                        player->csState = 0;
                    }
                    break;
                }
            }

            this->fwork[8] = 0.1f;
            this->fwork[2] = 0.1f;
            this->fwork[5] = 0.1f;
            this->fwork[6] = -300.0f;

            Math_SmoothStepToF(&this->fwork[1], 20.0f, 1.0f, 1.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 1.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[3] = 150.0f;

            Math_SmoothStepToF(&this->fwork[7], 20.0f, 0.1f, 0.1f, 0);
            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.01f, 0);

            if (this->animFrame == 10) {
                AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_BREATH, this->sfxSource, 4);
            }

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C0240D0)) {
                this->animFrame = 0;
                if (this->timer_050 == 0) {
                    this->state = 15;
                    this->swork[8] = 0;
                    this->fwork[9] = 0.0f;
                }
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C0240D0, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            break;

        case 18:
            this->fwork[6] = -3000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 70.0f, 1.0f, 7.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 3.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[3] = 0.0f;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.05f, 0);

            switch (this->work_044) {
                case 0:
                    if (this->timer_050 != 0) {
                        limbCount = Animation_GetFrameData(&D_ANDROSS_C00DE48, 45, spD0);
                        Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
                    } else {
                        this->work_044 = 1;
                        this->timer_050 = 30;
                        this->swork[9] = 20;
                        this->fwork[9] = 0.0f;
                        Audio_PlayBombExplodeSfx(0, this->sfxSource);
                        this->timer_05C = 50;
                    }
                    break;

                case 1:
                    if (this->timer_050 != 0) {
                        limbCount = Animation_GetFrameData(&D_ANDROSS_C017430, 0, spD0);
                        Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
                    } else {
                        this->work_044 = 2;
                        this->timer_050 = 70;
                        this->fwork[9] = 0.0f;
                        AUDIO_PLAY_SFX(NA_SE_VO_ANDROSS_EXCITE, this->sfxSource, 4);
                    }
                    if (this->timer_050 == 15) {
                        this->swork[10] = 80;
                    }
                    break;

                case 2:
                    if (this->timer_050 == 0) {
                        Andross_8018D9C0(this);
                    }

                    this->animFrame++;
                    if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C00E598)) {
                        this->animFrame = 0;
                    }

                    limbCount = Animation_GetFrameData(&D_ANDROSS_C00E598, this->animFrame, spD0);
                    Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
                    break;
            }
            break;

        case 20:
            this->fwork[6] = -3000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 70.0f, 1.0f, 7.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 50.0f, 1.0f, 5.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 50.0f, 1.0f, 5.0f, 0);
            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C017050)) {
                Andross_8018D9C0(this);
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C017050, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);
            break;

        case 30:
            this->fwork[6] = -3000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 70.0f, 1.0f, 7.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 3.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[3] = 0.0f;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C017050)) {
                this->animFrame = 0;
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C017050, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);

            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect389_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                       this->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), this->obj.pos.z, 0.0f, 0.0f,
                                       this->vel.z, RAND_FLOAT(0.2f) + 0.2f, 0);
            }
            if (gCsFrameCount > 50) {
                func_effect_8007D0E0(this->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     this->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), this->obj.pos.z,
                                     RAND_FLOAT(3.0f) + 3.0f);
            }

            gCsFrameCount++;

            switch (gCsFrameCount) {
                case 60:
                    this->swork[17] = 1;
                    Andross_8018DA94(this, &this->vwork[19]);
                    break;
                case 70:
                    this->swork[19] = 1;
                    Andross_8018DA94(this, &this->vwork[21]);
                    break;
                case 80:
                    this->swork[11] = 1;
                    Andross_8018DA94(this, &this->vwork[13]);
                    break;
                case 90:
                    this->swork[12] = 1;
                    Andross_8018DA94(this, &this->vwork[14]);
                    break;
                case 100:
                    this->swork[22] = 1;
                    Andross_8018DA94(this, &this->vwork[24]);
                    break;
                case 110:
                    this->swork[23] = 1;
                    Andross_8018DA94(this, &this->vwork[25]);
                    break;
                case 120:
                    this->swork[18] = 1;
                    Andross_8018DA94(this, &this->vwork[19]);
                    this->state = 9;
                    this->health = 100;
                    this->timer_050 = 50;
                    this->fwork[9] = 0.0f;
                    AUDIO_PLAY_SFX(NA_SE_EN_ANDROSS_ROBOT, this->sfxSource, 4);
                    AUDIO_PLAY_BGM(NA_BGM_BOSS_ANDROSS);
                    break;
            }
            break;

        case 9:
            this->fwork[6] = -3000.0f;
            if (this->timer_050 == 0) {
                this->state = 10;
                this->timer_050 = 100;
            }
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 60.0f, 1.0f, 3.0f, 0);

            this->fwork[0] = player->pos.x;
            this->fwork[3] = player->pos.y;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C00208C)) {
                this->animFrame = 0;
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C00208C, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);

            Effect_Effect389_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(700.0f),
                                   this->obj.pos.y + RAND_FLOAT_CENTERED(700.0f), this->obj.pos.z, 0.0f, 0.0f,
                                   gPlayer[0].vel.z, RAND_FLOAT(0.15f) + 0.15f, 0);
            break;

        case 10:
            this->fwork[6] = 0.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 60.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C00208C)) {
                this->animFrame = 0;
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C00208C, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);

            Effect_Effect389_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(700.0f),
                                   this->obj.pos.y + RAND_FLOAT_CENTERED(700.0f), this->obj.pos.z, 0.0f, 0.0f,
                                   gPlayer[0].vel.z, RAND_FLOAT(0.15f) + 0.15f, 0);
            if (this->timer_050 == 0) {
                this->state = 9;
                this->timer_050 = 130;
            }
            break;

        case 31:
            this->obj.rot.x += 1.0f;
            this->obj.rot.y += 0.3f;
            this->obj.rot.z += 0.7f;

            this->fwork[6] = -3000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 70.0f, 1.0f, 7.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 3.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[3] = 0.0f;

            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect389_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                       this->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), this->obj.pos.z, 0.0f, 0.0f,
                                       this->vel.z, RAND_FLOAT(0.2f) + 0.2f, 0);
            }
            func_effect_8007D0E0(this->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                 this->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), this->obj.pos.z,
                                 RAND_FLOAT(5.0f) + 5.0f);
            break;

        case 32:
            this->fwork[6] = -3000.0f;
            this->fwork[8] = 0.05f;

            Math_SmoothStepToF(&this->fwork[7], 70.0f, 1.0f, 7.0f, 0);

            this->fwork[2] = 0.05f;
            this->fwork[5] = 0.05f;

            Math_SmoothStepToF(&this->fwork[1], 30.0f, 1.0f, 3.0f, 0);
            Math_SmoothStepToF(&this->fwork[4], 30.0f, 1.0f, 3.0f, 0);

            this->fwork[0] = 0.0f;
            this->fwork[3] = 0.0f;

            Math_SmoothStepToF(&this->fwork[9], 1.0f, 1.0f, 0.05f, 0);

            this->animFrame++;
            if (this->animFrame >= Animation_GetFrameCount(&D_ANDROSS_C017050)) {
                this->animFrame = 0;
            }

            limbCount = Animation_GetFrameData(&D_ANDROSS_C017050, this->animFrame, spD0);
            Math_SmoothStepToVec3fArray(spD0, D_i6_801A7F80, 1, limbCount, this->fwork[9], 100.0f, 0.0f);

            if ((gGameFrameCount % 2) == 0) {
                Effect_Effect389_Spawn(this->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                       this->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), this->obj.pos.z, 0.0f, 0.0f,
                                       this->vel.z, RAND_FLOAT(0.2f) + 0.2f, 0);
            }

            if (gCsFrameCount > 50) {
                func_effect_8007D0E0(this->obj.pos.x + RAND_FLOAT_CENTERED(1000.0f),
                                     this->obj.pos.y + RAND_FLOAT_CENTERED(1000.0f), this->obj.pos.z,
                                     RAND_FLOAT(3.0f) + 3.0f);
            }

            gCsFrameCount++;

            switch (gCsFrameCount) {
                case 60:
                    this->swork[17] = 2;
                    Andross_8018DA94(this, &this->vwork[19]);
                    break;
                case 70:
                    this->swork[19] = 2;
                    Andross_8018DA94(this, &this->vwork[21]);
                    break;
                case 80:
                    this->swork[14] = 2;
                    Andross_8018DA94(this, &this->vwork[16]);
                    break;
                case 90:
                    this->swork[13] = 2;
                    Andross_8018DA94(this, &this->vwork[15]);
                    break;
                case 100:
                    Andross_8018DA94(this, &this->vwork[13]);
                    break;
                case 110:
                    Andross_8018DA94(this, &this->vwork[14]);
                    break;
                case 120:
                    this->swork[20] = 2;
                    Andross_8018DA94(this, &this->vwork[22]);
                    break;
                case 130:
                    this->swork[21] = 2;
                    Andross_8018DA94(this, &this->vwork[23]);
                    break;
                case 140:
                    this->swork[22] = 2;
                    Andross_8018DA94(this, &this->vwork[24]);
                    break;
                case 150:
                    this->swork[23] = 2;
                    Andross_8018DA94(this, &this->vwork[25]);
                    break;
                case 160:
                    this->swork[16] = 1;
                    Andross_8018DA94(this, &this->vwork[18]);
                    break;
                case 170:
                    this->swork[15] = 1;
                    Andross_8018DA94(this, &this->vwork[17]);
                    break;
                case 173:
                    Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_L);
                    Effect_Effect384_Spawn(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 100.0f, 4);
                    break;

                case 180:
                    boss1 = &gBosses[1];
                    Boss_Initialize(boss1);
                    boss1->obj.status = OBJ_INIT;
                    boss1->obj.id = OBJ_BOSS_AND_BRAIN;
                    boss1->obj.pos.x = this->obj.pos.x;
                    boss1->obj.pos.y = this->obj.pos.y;
                    boss1->obj.pos.z = this->obj.pos.z;
                    boss1->swork[1] = 100;
                    boss1->state = 10;
                    boss1->timer_050 = 180;
                    boss1->scale = 5.0f;
                    Object_SetInfo(&boss1->info, boss1->obj.id);
                    Object_Kill(&this->obj, this->sfxSource);
                    gDrawBackdrop = 3;
                    Andross_80189098(this);
                    Radio_PlayMessage(gMsg_ID_19330, RCID_ANDROSS_RED);
                    break;
            }
            Math_SmoothStepToF(&gAndrossUnkAlpha, 0.0f, 1.0f, 0.3f, 0.0f);
            break;
    }

    if (this->swork[4] >= 0) {
        this->info.hitbox[13] = this->vwork[0].z - this->obj.pos.z;
        this->info.hitbox[15] = this->vwork[0].y - this->obj.pos.y;
        this->info.hitbox[17] = this->vwork[0].x - this->obj.pos.x;
        if (this->swork[7] != 0) {
            this->info.hitbox[14] = 280.0f;
            this->info.hitbox[16] = 200.0f;
            this->info.hitbox[18] = 200.0f;
        } else {
            this->info.hitbox[14] = 100.0f;
            this->info.hitbox[16] = 100.0f;
            this->info.hitbox[18] = 100.0f;
        }
    } else {
        this->info.hitbox[16] = 0.0f;
    }

    if (this->swork[5] >= 0) {
        this->info.hitbox[19] = this->vwork[1].z - this->obj.pos.z;
        this->info.hitbox[21] = this->vwork[1].y - this->obj.pos.y;
        this->info.hitbox[23] = this->vwork[1].x - this->obj.pos.x;
        if (this->swork[7] != 0) {
            this->info.hitbox[20] = 280.0f;
            this->info.hitbox[22] = 200.0f;
            this->info.hitbox[24] = 200.0f;
        } else {
            this->info.hitbox[20] = 100.0f;
            this->info.hitbox[22] = 100.0f;
            this->info.hitbox[24] = 100.0f;
        }
    } else {
        this->info.hitbox[22] = 0.0f;
    }

    this->info.hitbox[1] = this->vwork[2].z - this->obj.pos.z;
    this->info.hitbox[3] = this->vwork[2].y - this->obj.pos.y;
    this->info.hitbox[5] = this->vwork[2].x - this->obj.pos.x;
    this->info.hitbox[7] = this->vwork[3].z - this->obj.pos.z;
    this->info.hitbox[9] = this->vwork[3].y - this->obj.pos.y;
    this->info.hitbox[11] = this->vwork[3].x - this->obj.pos.x;

    if ((initialstate == 17) && (this->state != 17)) {
        Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ANDROSS_BREATH);
    }
    if ((initialstate == 7) && (this->state != 7)) {
        Audio_KillSfxBySourceAndId(this->sfxSource, NA_SE_EN_ANDROSS_SPARK);
    }
}

Vec3f D_i6_801A67C4 = { 40.0f, 0.0f, -10.0f };
f32 D_i6_801A67D0 = 180.0f;
f32 D_i6_801A67D4 = 0.0f;
f32 D_i6_801A67D8 = 0.0f;
Vec3f D_i6_801A67DC = { 40.0f, 0.0f, 10.0f };
f32 D_i6_801A67E8 = 0.0f;
f32 D_i6_801A67EC = 0.0f;
f32 D_i6_801A67F0 = 0.0f;
Vec3f D_i6_801A67F4 = { 0.0f, 0.0f, 0.0f };

bool Andross_801917F0(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    Vec3f sp94;
    Vec3f sp88;
    f32 scale;
    Boss* this = (Boss*) data;

    sp94 = D_i6_801A67F4;
    scale = 1.0f;

    if ((limbIndex >= 13) && (limbIndex <= 50)) {
        if (this->state < 2) {
            *dList = NULL;
        } else {
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            gSPTexture(gMasterDisp++, 6600, 6600, 0, G_TX_RENDERTILE, G_ON);
            gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
            if (((limbIndex >= 23) && (limbIndex <= 32)) || (limbIndex == 50)) {
                if (this->swork[5] < 0) {
                    *dList = NULL;
                } else if ((this->swork[3] % 2) != 0) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_27);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                }
            } else if (this->swork[4] < 0) {
                *dList = NULL;
            } else if ((this->swork[2] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_27);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }
        }
    } else if ((this->timer_05C % 2) == 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_27);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }

    switch (limbIndex) {
        case 59:
            if (this->swork[18] == 1) {
                *dList = D_ANDROSS_C004860;
            }
            if (this->swork[18] == 2) {
                *dList = NULL;
            }
            break;

        case 3:
            rot->z -= this->vwork[4].x;
            rot->y -= this->vwork[4].y;

            if ((this->swork[0] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_27);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }

            if (this->swork[11] != 0) {
                *dList = D_ANDROSS_C0043D0;
                RCP_SetupDL(&gMasterDisp, SETUPDL_21);
            }
            scale = this->fwork[17];
            break;

        case 4:
            rot->z -= this->vwork[5].x;
            rot->y -= this->vwork[5].y;

            if ((this->swork[1] % 2) != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_27);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            }

            if (this->swork[12] != 0) {
                *dList = D_ANDROSS_C015740;
                RCP_SetupDL(&gMasterDisp, SETUPDL_21);
            }
            scale = this->fwork[17];
            break;

        case 5:
            if (this->swork[17] == 1) {
                *dList = D_ANDROSS_C002B20;
            }
            if (this->swork[17] == 2) {
                *dList = NULL;
            }
            scale = this->fwork[17];
            break;

        case 6:
            if (this->swork[19] == 1) {
                *dList = D_ANDROSS_C002F00;
            }
            if (this->swork[19] == 2) {
                *dList = NULL;
            }
            scale = this->fwork[17];
            break;

        case 1:
            if (this->swork[14] != 0) {
                *dList = NULL;
            }
            break;

        case 2:
            if (this->swork[13] != 0) {
                *dList = NULL;
            }
            break;

        case 7:
            if (this->swork[20] != 0) {
                *dList = NULL;
            }
            scale = this->fwork[18];
            break;

        case 8:
            if (this->swork[21] != 0) {
                *dList = NULL;
            }
            scale = this->fwork[18];
            break;

        case 9:
            if (this->swork[23] != 0) {
                *dList = NULL;
            }
            scale = this->fwork[18];
            break;

        case 10:
            if (this->swork[22] != 0) {
                *dList = NULL;
            }
            scale = this->fwork[18];
            break;

        case 11:
            if (this->swork[16] != 0) {
                *dList = NULL;
            }
            break;

        case 12:
            if (this->swork[15] != 0) {
                *dList = NULL;
            }
            break;

        case 49:
            pos->x -= this->fwork[11];
            pos->y += this->fwork[12];
            pos->z += this->fwork[13];

            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);

            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);

            if (*dList != NULL) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Push(&gCalcMatrix);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);
                RCP_SetupDL(&gMasterDisp, SETUPDL_41);
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
                Matrix_Translate(gGfxMatrix, D_i6_801A67DC.x, D_i6_801A67DC.y, D_i6_801A67DC.z, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, D_i6_801A67F0 * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, D_i6_801A67EC * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, D_i6_801A67E8 * M_DTOR, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ANDROSS_C022520);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gCalcMatrix);
            }
            return true;

        case 50:
            pos->x -= this->fwork[11];
            pos->y += this->fwork[12];
            pos->z -= this->fwork[13];

            Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);

            Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);

            if (*dList != NULL) {
                Matrix_Push(&gGfxMatrix);
                Matrix_Push(&gCalcMatrix);
                Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, *dList);
                RCP_SetupDL(&gMasterDisp, SETUPDL_41);
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
                Matrix_Translate(gGfxMatrix, D_i6_801A67C4.x, D_i6_801A67C4.y, D_i6_801A67C4.z, MTXF_APPLY);
                Matrix_RotateZ(gGfxMatrix, D_i6_801A67D8 * M_DTOR, MTXF_APPLY);
                Matrix_RotateY(gGfxMatrix, D_i6_801A67D4 * M_DTOR, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, D_i6_801A67D0 * M_DTOR, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, D_ANDROSS_C022520);
                Matrix_Pop(&gGfxMatrix);
                Matrix_Pop(&gCalcMatrix);
            }
            return true;

        default:
            break;
    }

    Matrix_Translate(gCalcMatrix, pos->x, pos->y, pos->z, MTXF_APPLY);

    Matrix_RotateZ(gCalcMatrix, rot->z * M_DTOR, MTXF_APPLY);
    Matrix_RotateY(gCalcMatrix, rot->y * M_DTOR, MTXF_APPLY);
    Matrix_RotateX(gCalcMatrix, rot->x * M_DTOR, MTXF_APPLY);

    Matrix_Push(&gCalcMatrix);
    Matrix_Scale(gCalcMatrix, scale, scale, scale, MTXF_APPLY);

    if (*dList != NULL) {
        Matrix_MultVec3f(gCalcMatrix, &sp94, &sp88);
        Display_SetSecondLight(&sp88);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, *dList);
    }
    Matrix_Pop(&gCalcMatrix);
    return true;
}

void Andross_801924B4(s32 limbIndex, Vec3f* rot, void* thisx) {
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
    Boss* this = (Boss*) thisx;

    switch (limbIndex) {
        case 3:
            Matrix_MultVec3f(gCalcMatrix, &sp7C, &this->vwork[2]);
            break;
        case 4:
            Matrix_MultVec3f(gCalcMatrix, &sp7C, &this->vwork[3]);
            break;
        case 5:
            Matrix_MultVec3f(gCalcMatrix, &sp4C, &this->vwork[6]);
            Matrix_MultVec3f(gCalcMatrix, &sp58, &this->vwork[7]);
            break;
        case 12:
            Matrix_MultVec3f(gCalcMatrix, &sp34, &this->vwork[9]);
            break;
        case 11:
            Matrix_MultVec3f(gCalcMatrix, &sp40, &this->vwork[8]);
            break;
        case 20:
            Matrix_MultVec3f(gCalcMatrix, &sp70, &this->vwork[0]);
            break;
        case 28:
            Matrix_MultVec3f(gCalcMatrix, &sp64, &this->vwork[1]);
            break;
        case 25:
            Matrix_MultVec3f(gCalcMatrix, &sp88, &this->vwork[10]);
            break;
    }

    if (this->state >= 30) {
        switch (limbIndex) {
            case 1:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[16]);
                return;
            case 2:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[15]);
                return;
            case 3:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[13]);
                return;
            case 4:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[14]);
                return;
            case 5:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[19]);
                return;
            case 6:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[21]);
                return;
            case 7:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[22]);
                return;
            case 8:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[23]);
                return;
            case 9:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[25]);
                return;
            case 10:
                Matrix_MultVec3f(gCalcMatrix, &sp94, &this->vwork[24]);
                return;
            case 11:
                Matrix_MultVec3f(gCalcMatrix, &sp28, &this->vwork[18]);
                return;
            case 12:
                Matrix_MultVec3f(gCalcMatrix, &sp28, &this->vwork[17]);
                break;
        }
    }
}

void Andross_AndAndross_Draw(AndAndross* this) {
    if (this->timer_058 == 0) {
        if (1) {} //! FAKE

        PRINTF("Enm->count %d\n");

        if (this->state < 2) {
            Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, D_i6_801A7F5C, D_i6_801A7F64, D_i6_801A7F6C,
                               D_i6_801A7F74, D_i6_801A7F7C, D_i6_801A8430);
        }

        Matrix_Scale(gCalcMatrix, 10.0f, 10.0f, 10.0f, MTXF_APPLY);
        Animation_DrawSkeleton(2, D_ANDROSS_C01CC3C, D_i6_801A7F80, Andross_801917F0, Andross_801924B4, this,
                               gCalcMatrix);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);

        if (this->fwork[20] > 0.05f) {
            Matrix_Translate(gGfxMatrix, this->vwork[10].x, this->vwork[10].y, this->vwork[10].z + gPathProgress,
                             MTXF_APPLY);
            if (this->fwork[21] > 0.05f) {
                Matrix_Push(&gGfxMatrix);
                RCP_SetupDL(&gMasterDisp, SETUPDL_67);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 192);
                gDPSetEnvColor(gMasterDisp++, 255, 0, 128, 192);
                Matrix_Scale(gGfxMatrix, this->fwork[21] * 7.0f, this->fwork[21] * 7.0f, this->fwork[21] * 7.0f,
                             MTXF_APPLY);
                if ((gGameFrameCount % 2) != 0) {
                    Matrix_Scale(gGfxMatrix, 1.1f, 1.1f, 1.1f, MTXF_APPLY);
                }
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aOrbDL);
                Matrix_Pop(&gGfxMatrix);
            }

            Matrix_Scale(gGfxMatrix, this->fwork[20] * 10.0f, this->fwork[20] * 10.0f, this->fwork[20] * 10.0f,
                         MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, this->fwork[19] * M_DTOR, MTXF_APPLY);
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);

            if ((gGameFrameCount % 2) != 0) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 128);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 30);
            }

            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, 0.0f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, 15.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 200.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, 120.0f * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, 15.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 200.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
            Matrix_Pop(&gGfxMatrix);
            Matrix_Push(&gGfxMatrix);
            Matrix_RotateZ(gGfxMatrix, 240.0f * M_DTOR, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, 15.0f * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 0.3f, 1.0f, 1.0f, MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 200.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
            Matrix_Pop(&gGfxMatrix);
        }
        Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR,
                           gAmbientG, gAmbientB);
    }
}

void Andross_AndLaserEmitter_Update(AndLaserEmitter* this) {
    Actor* otherActor;
    s32 i;

    switch (this->state) {
        case 0:
            if (this->obj.pos.x >= 0.0f) {
                this->state = 1;
            } else {
                this->state = 2;
            }
            this->vwork[0].x = this->obj.pos.x;
            this->vwork[0].y = this->obj.pos.y - 300.0f;
            this->vwork[0].z = this->obj.pos.z;
            this->health = 30;
            this->rot_0F4.z = this->obj.rot.z;
            AUDIO_PLAY_SFX(NA_SE_OB_SPARK_BEAM, this->sfxSource, 0);
            break;

        case 1:
            otherActor = &gActors[0];
            for (i = 0; i < ARRAY_COUNT(gActors); i++, otherActor++) {
                if ((i != this->index) && (otherActor->obj.status == OBJ_ACTIVE) &&
                    (otherActor->obj.id == OBJ_ACTOR_AND_LASER_EMITTER) &&
                    (fabsf(otherActor->obj.pos.z - this->obj.pos.z) < 200.0f)) {
                    this->timer_0BC = 5;
                    otherActor->timer_0BC = 5;
                    gTexturedLines[this->index].mode = 50;
                    gTexturedLines[this->index].xyScale = 1.0f;
                    gTexturedLines[this->index].posAA.x = this->obj.pos.x;
                    gTexturedLines[this->index].posAA.y = this->obj.pos.y;
                    gTexturedLines[this->index].posAA.z = this->obj.pos.z;
                    gTexturedLines[this->index].posBB.x = otherActor->obj.pos.x;
                    gTexturedLines[this->index].posBB.y = otherActor->obj.pos.y;
                    gTexturedLines[this->index].posBB.z = otherActor->obj.pos.z;
                    gTexturedLines[this->index].timer = 3;
                    break;
                }
            }
            /* fallthrough */
        case 2:
            this->obj.rot.z = this->rot_0F4.z + D_Andross_801A7F68;
            Matrix_RotateZ(gCalcMatrix, M_DTOR * D_Andross_801A7F68, MTXF_NEW);
            Matrix_MultVec3fNoTranslate(gCalcMatrix, this->vwork, &this->obj.pos);
            this->obj.pos.y += 300.0f;
            break;
    }

    if (this->dmgType != DMG_NONE) {
        this->dmgType = DMG_NONE;
        this->health -= this->damage;
        if (this->health <= 0) {
            func_effect_8007D0E0(this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, 5.0f);
            for (i = 0; i < 7; i++) {
                func_effect_80079618(RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.x,
                                     RAND_FLOAT_CENTERED(10.0f) + this->obj.pos.y, this->obj.pos.z,
                                     RAND_FLOAT(0.5f) + 0.5f);
            }
            Effect_SpawnTimedSfxAtPos(&this->obj.pos, NA_SE_EN_EXPLOSION_S);
            Object_Kill(&this->obj, this->sfxSource);
        }
    }
}

void Andross_AndLaserEmitter_Draw(AndLaserEmitter* this) {
    gSPDisplayList(gMasterDisp++, aAndLaserEmitterDL);

    if (this->timer_0BC != 0) {
        f32 scale = 2.5f;
        u8 alpha = 16;

        if ((gGameFrameCount % 2) != 0) {
            alpha = 64;
            scale *= 1.2f;
        }
        Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        RCP_SetupDL(&gMasterDisp, SETUPDL_67);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, alpha);
        gDPSetEnvColor(gMasterDisp++, 255, 128, 128, alpha);
        gSPDisplayList(gMasterDisp++, aOrbDL);
    }
}

void Andross_AndDoor_Update(AndDoor* this) {
    switch (this->state) {
        case 0:
            if (fabsf(this->obj.pos.z - gPlayer[0].trueZpos) < 1800.0f) {
                this->state = 1;
                this->info.hitbox = SEGMENTED_TO_VIRTUAL(D_ANDROSS_C038AC4);
            }
            break;

        case 1:
            this->info.hitbox[7] = -130.0f - (this->unk_44 * 1.6f);
            this->info.hitbox[17] = -130.0f - (this->unk_44 * 1.6f);
            this->info.hitbox[27] = -130.0f - (this->unk_44 * 1.6f);
            this->unk_44 += 2;
            if (this->unk_44 >= Animation_GetFrameCount(&aVe2AndrossGateAnim)) {
                this->unk_44 = Animation_GetFrameCount(&aVe2AndrossGateAnim) - 1;
            }
            break;
    }
    this->obj.rot.z = D_Andross_801A7F68;
}

bool Andross_801934EC(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    if (limbIndex == 13) {
        *dList = NULL;
    }
    return false;
}

void Andross_AndDoor_Draw(AndDoor* this) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&aVe2AndrossGateAnim, this->unk_44, frameTable);
    Animation_DrawSkeleton(1, aVe2AndrossGateSkel, frameTable, Andross_801934EC, NULL, NULL, &gIdentityMatrix);
}

void Andross_AndPassage_Update(AndPassage* this) {
    this->obj.rot.z = D_Andross_801A7F68;
    this->obj.pos.z += this->effectVel.z;
    if (this->timer_4C == 1) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

bool Andross_801935B4(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx) {
    if (limbIndex != 13) {
        *dList = NULL;
    }
    return false;
}

void Andross_AndPassage_Draw(AndPassage* this) {
    Vec3f frameTable[20];

    Animation_GetFrameData(&aVe2AndrossGateAnim, this->unk_44, frameTable);
    if (gLevelMode == LEVELMODE_ALL_RANGE) {
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
    Animation_DrawSkeleton(1, aVe2AndrossGateSkel, frameTable, Andross_801935B4, NULL, NULL, &gIdentityMatrix);
}

void Andross_AndPassage_Setup(AndPassage* this, f32 xPos, f32 yPos, f32 zPos, s32 arg4) {
    Scenery_Initialize(this);
    this->obj.status = OBJ_ACTIVE;
    this->obj.id = OBJ_SCENERY_AND_PASSAGE;
    this->obj.pos.x = xPos;
    this->obj.pos.y = yPos;
    this->obj.pos.z = zPos;
    this->effectVel.z = -40.0f;
    Object_SetInfo(&this->info, this->obj.id);
    this->timer_4C = (arg4 * 50) + 100;
    this->info.cullDistance = 100000.0f;
}

void Andross_80193710(void) {
    Actor* actor;
    Scenery360* scenery360;
    Boss* boss;
    s32 i;

    gLevelObjects = SEGMENTED_TO_VIRTUAL(gLevelObjectInits[gCurrentLevel]);

    for (scenery360 = gScenery360, i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if (gLevelObjects[i].id < OBJ_SCENERY_MAX) {
            Scenery360_Initialize(scenery360);
            scenery360->obj.status = OBJ_ACTIVE;
            scenery360->obj.id = gLevelObjects[i].id;
            scenery360->sfxSource[0] = scenery360->obj.pos.x = gLevelObjects[i].xPos;
            scenery360->sfxSource[1] = scenery360->obj.pos.y = gLevelObjects[i].yPos;
            scenery360->sfxSource[2] = scenery360->obj.pos.z = -gLevelObjects[i].zPos1;
            scenery360->unk_54 = scenery360->obj.rot.y = gLevelObjects[i].rot.y;
            Object_SetInfo(&scenery360->info, scenery360->obj.id);
            scenery360++;
        }
    }

    for (actor = &gActors[30], i = 0; i < 1000; i++) {
        if (gLevelObjects[i].id <= OBJ_INVALID) {
            break;
        }

        if ((gLevelObjects[i].id >= OBJ_ACTOR_START) && (gLevelObjects[i].id < OBJ_ACTOR_MAX)) {
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
    boss->obj.id = OBJ_BOSS_VE2_BASE;
    Object_SetInfo(&boss->info, boss->obj.id);
}

void Andross_801939A0(s32 actorIdx) {
    Actor* actor = &gActors[actorIdx];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = 0.0f;
    actor->obj.pos.y = gPlayer[0].cam.at.y;
    actor->obj.pos.z = 0.0f;
    actor->iwork[11] = 1;
    actor->rot_0F4.x = 90.0f;
    actor->fwork[0] = 50.0f;
    actor->fwork[1] = 6.5f;

    if (actorIdx == 10) {
        actor->iwork[TEAM_FACE] = FACE_FOX;
    }
    if (actorIdx == 1) {
        actor->state = 1;
        actor->work_046 = 255;
        actor->animFrame = ACTOR_CS_JAMES_ARWING;
    }

    Object_SetInfo(&actor->info, actor->obj.id);
    AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, actor->sfxSource, 0);
}

Vec3f D_i6_801A6878[4] = {
    { 1500.0f, 15000.0f, 0.0f },
    { 0.0f, 15000.0f, -600.0f },
    { -400.0f, 14950.0f, 0.0f },
    { 500.0f, 14930.0f, -300.0f },
};

void Andross_80193AE4(s32 actorIndex) {
    Actor* actor = &gActors[actorIndex];

    Actor_Initialize(actor);
    actor->obj.status = OBJ_ACTIVE;
    actor->obj.id = OBJ_ACTOR_CUTSCENE;
    actor->obj.pos.x = D_i6_801A6878[actorIndex].x;
    actor->obj.pos.y = D_i6_801A6878[actorIndex].y;
    actor->obj.pos.z = D_i6_801A6878[actorIndex].z;

    Object_SetInfo(&actor->info, actor->obj.id);

    if (actorIndex == 0) {
        actor->state = 200;
        actor->animFrame = ACTOR_CS_GREAT_FOX;
        AUDIO_PLAY_SFX(NA_SE_GREATFOX_ENGINE, actor->sfxSource, 0);
    } else {
        actor->iwork[11] = 1;
        actor->fwork[7] = RAND_FLOAT(360.0f);
        actor->fwork[8] = RAND_FLOAT(360.0f);
        actor->state = 100;
        AUDIO_PLAY_SFX(NA_SE_ARWING_ENGINE_FG, actor->sfxSource, 4);
    }
}

//! @bug This references a variable in another overlay, causing undefined behavior.
//! In US v1.1, that address contains the store instruction for player->vel.y = vel.y; in Venom2_LevelStart. Setting
//! this to nop is harmless, as the overlay will be unloaded next frame.
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
    s32 rnd;

    Math_SmoothStepToF(D_ctx_80177A48, 1.0f, 1.0f, 0.01f, 0.0f);

    player->arwing.upperRightFlapYrot = player->arwing.bottomRightFlapYrot = player->arwing.upperLeftFlapYrot =
        player->arwing.bottomLeftFlapYrot = 0.0f;

    switch (player->csState) {
        case 0:
            gCsFrameCount = 0;
            player->arwing.drawFace = true;
            D_ctx_80177A48[0] = 0.0f;
            if (player->aerobaticPitch > 180.0f) {
                player->aerobaticPitch -= 360.0f;
            }
            player->csState++;
            player->csTimer = 50;
            player->vel.z = -40.0f;
            /* fallthrough */
        case 1:
            Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&boss->vel.z, -40.0f, 1.0f, 1.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.y, 0.0f, 0.1f, 10.0f, 0.0f);
            Math_SmoothStepToF(&player->vel.x, 0.0f, 1.0f, 3.0f, 0.0f);
            Math_SmoothStepToF(&player->vel.y, 0.0f, 1.0f, 3.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.x, player->pos.x, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.y, player->pos.y + 30.0f, 0.1f, 15.0f, 0.0f);
            if (player->csTimer == 0) {
                player->pos.y += SIN_DEG(player->rot.x) * 15.0f;
                Math_SmoothStepToF(&player->rot.x, 180.0f, 0.1f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->vel.z, 40.0f, 1.0f, 2.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->camDist, 0.0f, 1.0f, 5.0f, 0.0f);
                Math_SmoothStepToF(&player->rot.x, 0.0f, 0.1f, 10.0f, 0.0f);
            }
            player->cam.eye.z += player->vel.z * 0.5f;

            switch (gCsFrameCount) {
                case 80:
                    Effect_Effect383_Spawn(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 40.0f);
                    Effect_SpawnTimedSfxAtPos(&boss->obj.pos, NA_SE_EN_EXPLOSION_L);
                    /* fallthrough */
                case 85:
                case 90:
                    Effect_Effect384_Spawn(boss->obj.pos.x, boss->obj.pos.y, boss->obj.pos.z, 250.0f, 6);
                    break;

                case 86:
                    Object_Kill(&boss->obj, boss->sfxSource);
                    gDrawBackdrop = 0;
                    break;

                case 111:
                    player->csState = 2;
                    AUDIO_PLAY_SFX(NA_SE_ARWING_BOOST, player->sfxSource, 0);
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
            gCsCamAtZ = gBosses[0].obj.pos.z + gPathProgress;
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 3.0f, 0.0f);
            break;

        case 2:
            player->unk_190 = D_ctx_80177A48[8];
            sp90 = 0;
            sp68.x = RAND_FLOAT_CENTERED(150.0f);
            sp68.y = RAND_FLOAT_CENTERED(150.0f);
            sp68.z = 0.0f;

            if (gCsFrameCount == 50) {
                AUDIO_PLAY_SFX(NA_SE_OB_ROUTE_EXPLOSION0, player->sfxSource, 0);
                Audio_SetEnvSfxReverb(0);
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
                gDrawBackdrop = 2;
                Matrix_RotateZ(gCalcMatrix, 2.0f * RAND_FLOAT(M_PI), MTXF_NEW);
                sp74.x = RAND_FLOAT(50.0f) + 120.0f;
                sp74.y = 0.0f;
                sp74.z = 0.0f;
                Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);
            }

            Math_SmoothStepToF(&D_ctx_80177A48[5], 3.0f, 1.0f, 0.05f, 0.0f);
            player->cam.eye.z += player->vel.z * D_ctx_80177A48[2];
            if (gCsFrameCount > 230) {
                player->camDist -= 7.0f;
            }
            if (gCsFrameCount > 230) {
                Math_SmoothStepToF(&D_ctx_80177A48[7], 3.0f, 1.0f, 0.1f, 0.0f);
                player->camRoll -= D_ctx_80177A48[7];
            }

            for (i = 0; i < sp90; i++) {
                Effect_FireSmoke_Spawn2(player->pos.x + sp68.x, player->pos.y + sp68.y,
                                        player->pos.z - (D_ctx_80177A48[3] + D_ctx_80177A48[4]), 0.0f, 0.0f, 50.0f,
                                        RAND_FLOAT(2.5f) + 2.5f);
            }

            Math_SmoothStepToF(&player->cam.eye.x, D_ctx_80177A48[1] + player->pos.x, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->cam.eye.y, player->pos.y + 30.0f, 0.1f, 15.0f, 0.0f);
            Math_SmoothStepToF(&player->rot.z, -180.0f, 0.02f, D_ctx_80177A48[6], 0.0f);
            Math_SmoothStepToF(&D_ctx_80177A48[6], 3.0f, 1.0f, 0.05f, 0.0f);

            gCsCamAtX = player->pos.x;
            gCsCamAtY = player->pos.y;
            gCsCamAtZ = player->trueZpos + gPathProgress;
            if (gCsFrameCount > 200) {
                player->contrailScale += 0.03f;
                if (player->contrailScale > 0.6f) {
                    player->contrailScale = 0.6f;
                }
                Math_SmoothStepToF(&player->camRoll, 3.0f, 0.5f, 0.1f, 0.0f);
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
                        Andross_AndPassage_Setup(&gScenery[i], player->pos.x, player->pos.y,
                                                 player->cam.eye.z - gPathProgress + (2195.0f * i), i);
                    }
                    break;

                case 150:
                    AUDIO_PLAY_SFX(NA_SE_WARP_HOLE, gDefaultSfxSource, 0);
                    break;

                case 340:
                    Audio_KillSfxBySourceAndId(player->sfxSource, NA_SE_OB_ROUTE_EXPLOSION0);
                    Audio_SetEnvSfxReverb(0);
                    gVenomHardClear = 0;
                    gBlurAlpha = 255;
                    gCurrentLevel = LEVEL_VENOM_2;
                    gLevelPhase = 1;
                    gLevelMode = LEVELMODE_ALL_RANGE;
                    player->csState = 3;
                    player->zPath = gPathProgress = 0.0f;
                    gDrawBackdrop = gDrawGround = true;
                    player->cam.eye.x = 1200.0f;
                    player->cam.eye.z = 1200.0f;
                    player->cam.eye.y = 1800.0f;
                    gCsCamAtX = 0.0f;
                    gCsCamAtY = 620.0f;
                    gCsCamAtZ = 0.0f;
                    player->camRoll = 0.0f;
                    player->draw = false;
                    D_ctx_80177A48[0] = 1.0f;
                    Play_ClearObjectData();

                    gScenery360 = Memory_Allocate(200 * sizeof(Scenery360));
                    for (i = 0; i < 200; i++) {
                        gScenery360[i].obj.status = OBJ_FREE;
                    }

                    Andross_80193710();
                    D_ctx_8017782C = true;
                    Play_InitEnvironment();
                    gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                    gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                    player->csTimer = 2;
                    gCsFrameCount = 0;
                    D_ctx_80177A48[1] = 0.0f;
                    break;
            }
            break;

        case 3:
            if (player->csTimer == 0) {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            } else {
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
            }

            if ((gCsFrameCount == 20) && (gVenomHardClear != 0)) {
                Andross_801939A0(1);
            }
            if (gCsFrameCount == 40) {
                Andross_801939A0(10);
                AUDIO_PLAY_SFX(NA_SE_EN_STAR_EXPLOSION, boss->sfxSource, 4);
                gCameraShake = 30;
                gSceneSetup = 1;
                gControllerRumbleTimers[0] = 30;
            }
            if (gCsFrameCount > 40) {
                for (i = 0; i < 3; i++) {
                    Effect_FireSmoke_Spawn2(boss->obj.pos.x + RAND_FLOAT_CENTERED(150.0f), boss->obj.pos.y + 500.0f,
                                            boss->obj.pos.z + RAND_FLOAT_CENTERED(150.0f), RAND_FLOAT_CENTERED(10.0f),
                                            60.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.5f) + 5.5f);
                }
                Math_SmoothStepToF(&gCsCamAtY, gActors[10].obj.pos.y, 1.0f, D_ctx_80177A48[1], 0.0f);
                Math_SmoothStepToF(&D_ctx_80177A48[1], 1000.0f, 1.0f, 5.0f, 0.0f);
            } else {
                Math_SmoothStepToF(&player->cam.eye.z, 1640.0f, 0.05f, 50.0f, 0.0f);
                Math_SmoothStepToF(&player->cam.eye.y, 110.0f, 0.05f, 50.0f, 0.0f);
                Math_SmoothStepToF(&player->cam.eye.x, 0.0f, 0.05f, 50.0f, 0.0f);
                Math_SmoothStepToF(&gCsCamAtY, 630.0f, 0.05f, 50.0f, 0.0f);
            }

            if (gCsFrameCount == 70) {
                AUDIO_PLAY_BGM(NA_BGM_ALL_CLEAR);
            }
            if (gCsFrameCount == 150) {
                player->csState++;
                D_ctx_80177A48[0] = 1.0f;
                D_ctx_80177A48[1] = 1000.0f;
                D_ctx_80177A48[2] = 0;
                D_ctx_80177A48[3] = 1.0f;
                gActors[10].obj.pos.y = 1500.0f;
                gActors[10].rot_0F4.z = 180.0f;
                gDrawBackdrop = 0;
                gFogFar = 1030;
                D_i6_801A7F40 = gLight1R;
                D_i6_801A7F44 = gLight1G;
                D_i6_801A7F48 = gLight1B;
                D_i6_801A7F4C = gAmbientR;
                D_i6_801A7F50 = gAmbientG;
                D_i6_801A7F54 = gAmbientB;
                gEnvLightyRot = -50.0f;
                gMissionStatus = MISSION_ACCOMPLISHED;
                for (i = 0; i < 200; i++) {
                    gScenery360[i].obj.status = OBJ_FREE;
                }
            }
            break;

        case 4:
            player->camRoll += D_ctx_80177A48[3];
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

            player->cam.eye.x = gActors[10].obj.pos.x + 50.0f;
            player->cam.eye.y = gActors[10].obj.pos.y + D_ctx_80177A48[1];
            player->cam.eye.z = gActors[10].obj.pos.z;

            gCsCamAtX = gActors[10].obj.pos.x;
            gCsCamAtY = gActors[10].obj.pos.y + 50.0f;
            gCsCamAtZ = gActors[10].obj.pos.z;

            if (((gGameFrameCount % 4) == 0) && (gCsFrameCount < 215)) {
                Effect_FireSmoke_Spawn2(boss->obj.pos.x + RAND_FLOAT_CENTERED(350.0f), boss->obj.pos.y + 500.0f,
                                        boss->obj.pos.z + RAND_FLOAT_CENTERED(350.0f), RAND_FLOAT_CENTERED(10.0f),
                                        60.0f, RAND_FLOAT_CENTERED(10.0f), RAND_FLOAT(5.5f) + 15.5f);
            }
            sp80 = RAND_FLOAT(40.0f);
            for (i = 0; i < 36; i += 4) {
                sp8C = __sinf((i * 10.0f * M_DTOR) + sp80) * D_ctx_80177A48[2];
                sp84 = __cosf((i * 10.0f * M_DTOR) + sp80) * D_ctx_80177A48[2];
                Effect_FireSmoke_Spawn2(sp8C, 300.0f, sp84, 0.0f, 0.0f, 0.0f, RAND_FLOAT(5.5f) + 15.5f);
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
                Play_GenerateStarfield();
                gStarCount = 1000;
                player->wingPosition = 0;
            }
            if (gCsFrameCount == 360) {
                gCsFrameCount = 340;
                player->csState++;
                D_ctx_80177A48[0] = 1.0f;
                D_ctx_80177A48[1] = 0.0f;
                D_ctx_80177A48[2] = 0.0f;
                D_ctx_80177A48[3] = 0.0f;
                D_ctx_80177A48[4] = 0.0f;
                player->cam.eye.x = gCsCamEyeX = 100.0f;
                player->cam.eye.y = gCsCamEyeY = 14800.0f;
                player->cam.eye.z = gCsCamEyeZ = -1500.0f;
                gCsCamAtX = 0.0f;
                gCsCamAtY = 15000.0f;
                gCsCamAtZ = 0;
                player->camRoll = 0.0f;
                gActors[10].state = 101;
                gActors[10].fwork[0] = 0.0f;
                gActors[10].obj.pos.y = 14500.0f;
                gActors[10].rot_0F4.z = 70.0f;
                gActors[10].rot_0F4.x = gActors[10].rot_0F4.y = 0.0f;
                gFillScreenAlpha = gFillScreenAlphaTarget = 255;
                gFillScreenRed = gFillScreenGreen = gFillScreenBlue = 0;
                player->csTimer = 3;
                gStarCount = 500;
            }
            if (gCsFrameCount == 250) {
                gLevelClearScreenTimer = 100;
            }
            break;

        case 5:
            if (player->csTimer == 1) {
                gFillScreenAlpha = gFillScreenAlphaTarget = 0;
            }
            if (gVenomHardClear != 0) {
                if (gCsFrameCount >= 1000) {
                    gCsCamAtX += D_ctx_80177A48[4] * 0.15f;
                    gCsCamEyeZ += D_ctx_80177A48[4];
                    Math_SmoothStepToF(&D_ctx_80177A48[4], 20.0f, 1.0f, 0.1f, 0.0f);
                } else {
                    gCsCamEyeZ = gActors[10].obj.pos.z - 20.0f;
                }
                if ((gCsFrameCount >= 920) && (gTeamShields[TEAM_ID_PEPPY] > 0)) {
                    if (gCsFrameCount == 920) {
                        player->csTimer = 25;
                    }
                    gActors[10].fwork[19] = SIN_DEG(player->csTimer * 40.0f) * 5.0f;
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
                Math_SmoothStepToF(&player->cam.eye.x, gActors[10].obj.pos.x - 50.0f, D_ctx_80177A48[0],
                                   D_ctx_80177A48[1], 0);
                Math_SmoothStepToF(&player->cam.eye.y, gActors[10].obj.pos.y + 10.0f, D_ctx_80177A48[0],
                                   D_ctx_80177A48[1], 0);
                Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], D_ctx_80177A48[1], 0);
                gCsCamAtY = SIN_DEG(gGameFrameCount * 5.5f) + 15000.0f;
            } else {
                gCsCamEyeX -= 1.0f;
                gCsCamEyeY += 0.3f;
                gCsCamEyeZ += 4.0f;
                gCsCamAtY = (SIN_DEG(gGameFrameCount * 1.5f) * 10.0f) + 15000.0f;
                Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
                Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
                Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
            }
            if (gVenomHardClear != 0) {
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
                        gShowLevelClearStatusScreen = true;
                        break;
                    case 1250:
                        gShowLevelClearStatusScreen = false;
                        break;
                }
                // Shooting Star. James? Is that you?
                if (gCsFrameCount > 1300) {
                    rnd = RAND_INT(100.0f);
                    gStarFillColors[1155] = FILL_COLOR(gStarColors[rnd % 16U]);
                    gStarOffsetsX[1155] += 1.0f * 2.0f;
                    gStarOffsetsY[1155] += 0.5f * 2.0f;
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
                        gShowLevelClearStatusScreen = true;
                        break;
                    case 1250:
                        gShowLevelClearStatusScreen = false;
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
                    gLeveLClearStatus[LEVEL_VENOM_ANDROSS] = Play_CheckMedalStatus(200) + 1;
                    AUDIO_SET_SPEC(SFXCHAN_0, AUDIOSPEC_27);
                }
            }
            break;

        case 100:
            gPlayerGlareAlphas[0] -= 4;
            if (gPlayerGlareAlphas[0] > 255) {
                gPlayerGlareAlphas[0] = 0;
            }
            Matrix_RotateY(gCalcMatrix, (player->yRot_114 + player->rot.y + 180.0f) * M_DTOR, MTXF_NEW);
            Matrix_RotateX(gCalcMatrix, -((player->xRot_120 + player->rot.x + player->aerobaticPitch) * M_DTOR),
                           MTXF_APPLY);

            sp74.x = 0.0f;
            sp74.y = 0.0f;
            sp74.z = player->baseSpeed;

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp74, &sp68);

            player->vel.x = sp68.x;
            player->vel.z = sp68.z;
            player->vel.y = sp68.y;
            if (player->csTimer == 0) {
                player->state = PLAYERSTATE_ACTIVE;
                player->unk_014 = 0.2f;
                player->unk_018 = 0.0f;
                player->unk_01C = 0.05f;
                gDrawBackdrop = 6;
                gProjectFar = 12800.0f;
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
            Math_SmoothStepToF(&player->cam.eye.x, gCsCamEyeX, D_ctx_80177A48[0], 50000.0f, 0);
            Math_SmoothStepToF(&player->cam.eye.y, gCsCamEyeY, D_ctx_80177A48[0], 50000.0f, 0);
            Math_SmoothStepToF(&player->cam.eye.z, gCsCamEyeZ, D_ctx_80177A48[0], 50000.0f, 0);
            Math_SmoothStepToF(&player->zRotBank, 0.0f, 0.1f, 0.7f, 0.0f);
            Math_SmoothStepToF(&player->camRoll, 0.0f, 0.1f, 0.4f, 0.0f);
            break;
    }
    player->pos.x += player->vel.x;
    player->pos.y += player->vel.y;
    player->pos.z += player->vel.z;
    player->trueZpos = player->pos.z + player->camDist;
    player->bankAngle = player->rot.z + player->zRotBank + player->zRotBarrelRoll;
    Math_SmoothStepToF(&player->zRotBarrelRoll, 0.0f, 0.1f, 15.0f, 0.0f);
    Math_SmoothStepToAngle(&player->aerobaticPitch, 0.0f, 0.1f, 20.0f, 0.0f);
    Math_SmoothStepToF(&player->cam.at.x, gCsCamAtX, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.y, gCsCamAtY, D_ctx_80177A48[0], 50000.0f, 0);
    Math_SmoothStepToF(&player->cam.at.z, gCsCamAtZ, D_ctx_80177A48[0], 50000.0f, 0);
}

void Andross_80195E44(ActorCutscene* this) {
    Vec3f sp44;
    Vec3f sp38;
    f32 sp34;

    sp34 = 0.0f;

    switch (this->state) {
        case 0:
            this->rot_0F4.z += this->fwork[1];
            if (gCsFrameCount > 250) {
                Math_SmoothStepToF(&this->fwork[1], 0.5f, 0.1f, 0.04f, 0.0f);
            } else {
                Math_SmoothStepToF(&this->fwork[1], -2.0f, 0.1f, 0.04f, 0.0f);
            }
            break;

        case 1:
            this->rot_0F4.z += this->fwork[1];
            Math_SmoothStepToF(&this->fwork[1], -2.0f, 0.1f, 0.04f, 0.0f);
            if (gCsFrameCount == 55) {
                this->state++;
            }
            break;

        case 2:
            Math_SmoothStepToF(&this->rot_0F4.x, 180.0f, 0.1f, 1.0f, 0.0f);
            Math_SmoothStepToF(&this->rot_0F4.y, 200.0f, 0.1f, 1.0f, 0.0f);
            this->work_046 -= 5;
            if (this->work_046 < 0) {
                this->work_046 = 0;
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;

        case 101:
            Math_SmoothStepToF(&this->rot_0F4.z, 0.0f, 0.03f, 0.5f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.x, 0.0f, 0.03f, 5.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.y, 15000.0f, 0.03f, 5.0f, 0.0f);
            Math_SmoothStepToF(&this->obj.pos.z, 0.0f, 0.03f, 5.0f, 0.0f);
            break;

        case 100:
            this->fwork[7] += 3.0f;
            this->rot_0F4.z = SIN_DEG(this->fwork[7]) * 1.5f;
            this->fwork[8] += 2.0f;
            sp34 = SIN_DEG(this->fwork[8]) * 0.5f;
            break;

        case 200:
            break;
    }

    Matrix_RotateY(gCalcMatrix, (this->rot_0F4.y + 180.0f) * M_DTOR, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, -(this->rot_0F4.x * M_DTOR), MTXF_APPLY);

    sp44.x = 0.0f;
    sp44.y = 0.0f;
    sp44.z = this->fwork[0];

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp44, &sp38);

    this->vel.x = sp38.x;
    this->vel.y = sp38.y + sp34;
    this->vel.z = sp38.z;

    this->obj.rot.x = -this->rot_0F4.x;
    this->obj.rot.y = this->rot_0F4.y + 180.0f;
    this->obj.rot.z = -this->rot_0F4.z;
}

void Andross_801961AC(void) {
    Boss* boss = &gBosses[0];

    Boss_Initialize(boss);
    boss->obj.status = OBJ_ACTIVE;
    boss->state = 21;
    boss->obj.id = OBJ_BOSS_AND_BRAIN;
    Object_SetInfo(&boss->info, boss->obj.id);
    gCsFrameCount = 599;
}
