/*
 * File: fox_tr.c
 * System: Training
 * Description: Level: Training - On Rails
 */

#include "global.h"
#include "assets/ast_training.h"

void Training_801988E0(void) {
    if (gRingPassCount != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_83);
        gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 255, 255);
        func_hud_800869A0(250.0f, 50.0f, gRingPassCount, 1.0f, 0, 999);
    }
}

void Training_ItemRing_Update(ItemTrainingRing* this) {
    f32 var_fv0;

    switch (this->state) {
        case 0:
            this->obj.rot.z += 1.0f;
            Math_SmoothStepToF(&this->width, 1.0f, 1.0f, 0.05f, 0.0f);

            if ((this->unk_44 == 0) && !gPlayer[0].somersault) {
                if (this->obj.rot.y == 0.0f) {
                    var_fv0 = 550.0f;
                } else {
                    var_fv0 = 1000.0f;
                }

                if (this->obj.pos.z > (gPlayer[0].trueZpos + var_fv0)) {
                    this->unk_44 = 1;
                    PRINTF("♪:リング未通過音\n"); // Ring not passed sound
                    AUDIO_PLAY_SFX(NA_SE_RING_MISS, gDefaultSfxSource, 4);
                    gRingPassCount = 0;
                }
            }

            if (this->collected) {
                this->state = 1;
                this->timer_48 = 50;
                this->info.cullDistance = 10000.0f;

                PRINTF("♪:リング通過音\n"); // Ring passing sound
                AUDIO_PLAY_SFX(NA_SE_RING_PASS, gDefaultSfxSource, 4);

                gRingPassCount++;

                if ((this->obj.rot.x != 0.0f) && (gRingPassCount >= 100)) {
                    Radio_PlayMessage(gMsg_ID_20330, RCID_ROB64);
                }
            }
            break;

        case 1:
            this->obj.pos.x += ((gPlayer[this->playerNum].pos.x - this->obj.pos.x) * 0.05f);
            this->obj.pos.y += ((gPlayer[this->playerNum].pos.y - this->obj.pos.y) * 0.05f);

            if (gPlayer[0].alternateView) {
                this->obj.pos.z += (gPlayer[this->playerNum].trueZpos - 300.0f - this->obj.pos.z) * 0.05f;
            } else {
                this->obj.pos.z += ((gPlayer[this->playerNum].trueZpos - this->obj.pos.z) * 0.05f);
            }

            this->obj.rot.z += 22.0f;

            Math_SmoothStepToAngle(&this->obj.rot.y, Math_RadToDeg(-gPlayer[this->playerNum].camYaw), 0.2f, 10.0f,
                                   0.0f);

            if (this->timer_48 == 0) {
                Object_Kill(&this->obj, this->sfxSource);
            }
            break;
    }
}
