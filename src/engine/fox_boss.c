#include "global.h"

s32 gBossFrameCount;

s32 D_boss_800C9E90[] = {
    SEQ_ID_CO_BOSS_1 | SEQ_FLAG, SEQ_ID_ME_BOSS | SEQ_FLAG, SEQ_ID_SX_BOSS | SEQ_FLAG,   SEQ_ID_A6_BOSS | SEQ_FLAG,
    SEQ_ID_A6_BOSS | SEQ_FLAG,   SEQ_ID_SY_BOSS | SEQ_FLAG, SEQ_ID_VE_BOSS | SEQ_FLAG,   SEQ_ID_SO_BOSS | SEQ_FLAG,
    SEQ_ID_ZO_BOSS | SEQ_FLAG,   SEQ_ID_VE_BOSS | SEQ_FLAG, SEQ_ID_CO_BOSS_1 | SEQ_FLAG, SEQ_ID_MA_BOSS | SEQ_FLAG,
    SEQ_ID_TI_BOSS | SEQ_FLAG,   SEQ_ID_AQ_BOSS | SEQ_FLAG,
};

s32 PAD_boss_C9EC4[14] = { 0 };

const f32 D_boss_800D55D0[] = { 6000.0f, 18000.0f, -6000.0f, -18000.0f };

void func_boss_80042EC0(Boss* boss) {
    s32 bonus;
    f32 yOffset;

    if (gBossFrameCount < 3840) {
        bonus = 10;
    } else if (gBossFrameCount < 5760) {
        bonus = 5;
    } else if (gBossFrameCount < 7680) {
        bonus = 2;
    } else if (gBossFrameCount < 9600) {
        bonus = 1;
    } else {
        bonus = 0;
    }
    if (bonus != 0) {
        yOffset = 0.0f;
        if (boss->obj.id == OBJ_BOSS_292) {
            yOffset = 300.0f;
        } else if (boss->obj.id == OBJ_BOSS_306) {
            yOffset = 200.0f;
        }
        BonusText_Display(boss->obj.pos.x, boss->obj.pos.y + yOffset, boss->obj.pos.z, bonus);
    }
    gHitCount += bonus + 1;
    D_ctx_80177850 = 15;
}

void Boss299_Init(Boss299* this) {
}

void Boss299_Update(Boss299* this) {
}

void Boss299_Draw(Boss299* this) {
}

void Boss300_Init(Boss300* this) {
}

void Boss300_Update(Boss300* this) {
}

void Boss300_Draw(Boss300* this) {
}

void func_boss_80042FF4(Actor* actor, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                        f32 arg9, f32 argA, s32 argB, s32 argC) {
    Actor_Initialize(actor);
    actor->obj.status = OBJ_INIT;
    actor->obj.id = OBJ_ACTOR_189;
    actor->state = argB;
    actor->obj.pos.x = arg1;
    actor->obj.pos.y = arg2;
    actor->obj.pos.z = arg3;
    actor->obj.rot.x = arg4;
    actor->obj.rot.y = arg5;
    actor->obj.rot.z = arg6;
    actor->vel.x = arg7;
    actor->vel.y = arg8;
    actor->vel.z = arg9;
    actor->scale = argA;
    actor->timer_0BC = argC;
    actor->timer_0BE = 20;
    Object_SetInfo(&actor->info, actor->obj.id);
    if (gLevelType == LEVELTYPE_PLANET) {
        actor->gravity = 0.5f;
    }
}

void func_boss_800430DC(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                        f32 arg9, s32 argA, s32 argB) {
    s32 i;

    for (i = 59; i >= 0; i--) {
        if (gActors[i].obj.status == OBJ_FREE) {
            func_boss_80042FF4(&gActors[i], arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, argB);
            return;
        }
    }
}

void func_boss_80043188(Boss* boss) {
    boss->info.unk_10 = 30000.0f;
}

void func_boss_8004319C(Player* player, f32 arg1, f32 arg2, f32 arg3) {
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 80);
    SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 80);

    gCsFrameCount = 0;
    D_ctx_80178448 = arg3 + D_ctx_80177D20;
    D_ctx_80178440 = arg1;
    D_ctx_80178444 = arg2;

    player->state_1C8 = PLAYERSTATE_1C8_7;
    player->unk_1D0 = 10;
    player->timer_1F8 = 50;
    player->timer_1FC = 50;
    player->unk_000 = 0.0f;
    player->unk_004 = 1.0f;
    if (player->pos.x < player->unk_0AC) {
        player->unk_004 = -1.0f;
    }
    gPlayer[0].vel.x = 0.0f;
}
