/*
 * File: fox_edisplay.c
 * Description: Object Draw routines
 */

#include "prevent_bss_reordering.h"
#include "global.h"
#include "sf64object.h"
#include "assets/ast_katina.h"
#include "assets/ast_venom_1.h"
#include "assets/ast_venom_2.h"
#include "assets/ast_fortuna.h"
#include "assets/ast_corneria.h"
#include "assets/ast_meteo.h"
#include "assets/ast_solar.h"
#include "assets/ast_sector_x.h"
#include "assets/ast_sector_y.h"
#include "assets/ast_aquas.h"
#include "assets/ast_macbeth.h"
#include "assets/ast_7_ti_1.h"
#include "assets/ast_andross.h"
#include "assets/ast_star_wolf.h"
#include "assets/ast_arwing.h"
#include "assets/ast_blue_marine.h"
#include "assets/ast_versus.h"
#include "assets/ast_enmy_space.h"
#include "assets/ast_enmy_planet.h"
#include "assets/ast_ve1_boss.h"
#include "assets/ast_zoness.h"
#include "port/interpolation/FrameInterpolation.h"
#include "port/hooks/Events.h"

Vec3f D_edisplay_801615D0;
Vec3f sViewPos;
bool sDrewActor;
Matrix D_edisplay_801615F0;
ArwingInfo gActorTeamArwing;

char D_edisplay_800CF970[] = "$Id: fox_edisplay.c,v 1.196 1997/05/08 08:31:50 morita Exp $";

void Object_ApplyWaterDistortion(void) {
    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 13.0f * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.02f, 0.98f, 1.0f, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, -(f32) gGameFrameCount * 13.0f * M_DTOR, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, 1.02f, 0.98f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
}

void Object_SetCullDirection(s32 cullDirection) {
    if (cullDirection < 0) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_FRONT);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    }
}

void Graphics_SetScaleMtx(f32 scale) {
    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
}

void Sprite168_Draw(Sprite168* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_64);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 60);
    // Missing DList
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
}

void Object_dummy_800598DC(s32 arg0) {
}

void MeteoBall_Draw(MeteoBall* this) {
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gSPDisplayList(gMasterDisp++, aMeMeteoBallDL);
    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
}

void MeHopBot_PostLimbDraw(s32 limbIndex, Vec3f* rot, void* index) {
    Vec3f sp24;
    Vec3f sp18;

    if (limbIndex == 1) {
        sp24.x = 0.0f;
        sp24.y = 0.0f;
        sp24.z = 0.0f;
        Matrix_MultVec3f(gCalcMatrix, &sp24, &sp18);
        gActors[*((s32*) index)].fwork[0] = sp18.y;
    }
}

f32 D_edisplay_800CF9B0[] = {
    -12.324226f, -12.008495f, -11.083107f, -9.56147f,  -7.440754f, -4.713318f,  -1.393303f,  2.48587f,
    6.872662f,   11.668991f,  16.752102f,  21.98127f,  27.193024f, 32.21534f,   36.875694f,  41.007812f,
    44.462303f,  47.094223f,  48.761005f,  49.345966f, 47.6453f,   42.988186f,  36.062622f,  27.662722f,
    18.646473f,  9.883305f,   2.113918f,   -4.157948f, -8.673706f, -11.395222f, -12.324226f,
};
f32 D_edisplay_800CFA2C[] = {
    1.0f, 1.0f, 0.95f, 0.9f, 0.85f, 0.8f, 0.75f, 0.7f, 0.65f, 0.6f,
};

void MeHopBot_Draw(MeHopBot* this) {
    Vec3f sp30[30];
    f32 yTrans = D_edisplay_800CF9B0[this->animFrame] - 114.0f;

    Matrix_Translate(gGfxMatrix, 0.f, -yTrans, 0.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    Animation_GetFrameData(&aMeHopBotAnim, this->animFrame, sp30);
    Animation_DrawSkeleton(1, aMeHopBotSkel, sp30, NULL, MeHopBot_PostLimbDraw, &this->index, &gIdentityMatrix);
}

void MeteoTunnel_Draw(MeTunnel* this) {
    gSPDisplayList(gMasterDisp++, aMeMeteoTunnelDL);
}

void Scenery_DrawTitaniaBones(Scenery* this) {
    if (this->obj.id == OBJ_SCENERY_TI_SKULL) {
        gSPDisplayList(gMasterDisp++, D_TI1_7007350);
    } else {
        Graphics_SetScaleMtx(D_edisplay_800CFA2C[this->obj.id - 29]);
        gSPDisplayList(gMasterDisp++, D_TI1_700BB10);
    }
}

void func_edisplay_80059BB0(void* arg0) {
}

void CoIBeam_Draw(CoIBeam* this) {
    gSPDisplayList(gMasterDisp++, aCoIBeamDL);
}

void CoMoleMissile_Draw(CoMoleMissile* this) {
    if (this->animFrame != 0) {
        gSPDisplayList(gMasterDisp++, CoMoleMissileDL);
    }
}

void func_edisplay_80059C28(void* arg0) {
}

void Sprite167_Draw(Sprite167* this) {
    /* Unimplemented */
}

void FogShadow_Draw(FogShadow* this) {
    RCP_SetupDL_47(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 180);

    switch (this->sceneryId) {
        case OBJ_SCENERY_CO_STONE_ARCH:
            Matrix_Scale(gGfxMatrix, 2.0f, 1.0f, 0.7f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;

        case OBJ_SCENERY_CO_ARCH_2:
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.7f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;

        case OBJ_SCENERY_CO_HIGHWAY_1:
        case OBJ_SCENERY_CO_HIGHWAY_2:
            Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 10.55f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoHighwayShadowDL);
            break;

        case OBJ_SCENERY_CO_DOORS:
            Matrix_Scale(gGfxMatrix, 1.6f, 1.0f, 1.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;

        case OBJ_SCENERY_CO_ARCH_1:
            Matrix_Scale(gGfxMatrix, 1.2f, 1.0f, 1.3f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;

        case OBJ_SCENERY_CO_ARCH_3:
            Matrix_Scale(gGfxMatrix, 2.2f, 1.0f, 1.4f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;
    }
    RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
}

void CoBuilding9_Draw(CoBuilding9* this) {
    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -95.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aCoBuilding9DL);
}

void CoBuilding10_Draw(CoBuilding10* this) {
    gSPDisplayList(gMasterDisp++, aCoBuilding9DL);
}

// repurposed into OBJ_SCENERY_CO_BUILDING_6
void func_edisplay_8005A010(Sprite* this) {
    if (!this->toLeft) {
        Matrix_RotateY(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aCoBuilding6DL);
    }
}

void func_edisplay_8005A07C(void* arg0) {
}

void func_edisplay_8005A088(void* arg0) {
}

Gfx* D_edisplay_800CFA54[] = {
    D_SY_6027960, D_SY_60273A0, D_SY_60183B0, D_SY_60121E0, D_SY_602A2E0, D_SY_602A720, D_SY_602B8F0,
    D_SY_602A8C0, D_SY_6028E70, D_SY_602E0A0, D_SY_602DE70, D_SY_602DC40, D_SY_602D830, D_SY_602D340,
    D_CO_6031280, D_CO_6031130, D_CO_6030850, D_CO_6030FD0, D_CO_602DD40, D_CO_6033AF0, D_CO_60186E0,
    D_CO_6024160, D_CO_6033290, D_CO_6017F10, D_FO_60074E0, D_FO_6007590, D_FO_6007730, D_FO_6005CC0,
};
Gfx* D_edisplay_800CFAC4[] = {
    D_ZO_60176D0, D_ZO_6017810, D_ZO_6017770, D_ZO_6016D90, D_ZO_6016E30, D_ZO_60178B0,
};
Gfx* D_edisplay_800CFADC[] = {
    D_ZO_6023690, D_ZO_6021BB0, D_ZO_6021C50, D_ZO_6021CE0, D_ZO_6021D80, D_ZO_6016350,
    D_ZO_6021E20, D_ZO_60222A0, D_ZO_6022BE0, D_ZO_6022D70, D_ZO_6022F00,
};
Gfx* D_edisplay_800CFB08[] = { D_ZO_6020F10, D_ZO_6021100, D_ZO_60214B0 };
Gfx* D_edisplay_800CFB14[] = { D_ZO_60163E0, D_ZO_60165D0, D_ZO_6016880, D_ZO_6016B50, D_ZO_6000C40 };
Gfx* D_edisplay_800CFB28[] = { D_ZO_6018E80, D_ZO_601F620, D_ZO_601F420, D_ZO_6018C80, D_ZO_601F940, D_ZO_601F260 };
Gfx* D_edisplay_800CFB40[] = {
    D_SO_6014DB0, D_SO_60146D0, D_SO_6014B80, D_SO_6014470, D_SO_6014930,
    D_SO_60138A0, D_SO_60151A0, D_SO_600F750, D_SO_6015810,
};
Gfx* D_edisplay_800CFB64[] = {
    D_AQ_600D4A0, D_AQ_600D720, D_AQ_600D810, D_AQ_600CFF0, D_AQ_600BD20,
    D_AQ_600D390, D_AQ_600E150, D_AQ_6007160, D_AQ_600D900,
};
Gfx* D_edisplay_800CFB88[] = {
    D_AQ_600A8E0, D_AQ_600A840, D_AQ_600A480, D_AQ_600A720, D_AQ_600A970, D_AQ_6007D70, D_AQ_600A520, D_AQ_6009990,
};
Gfx* D_edisplay_800CFBA8[] = {
    D_AQ_6026460, D_AQ_60266B0, D_AQ_6026950, D_AQ_60276F0, D_AQ_6027810, D_AQ_6027330, D_AQ_60273C0, D_AQ_6026E30,
    D_AQ_6026EC0, D_AQ_6026DA0, D_AQ_6026D10, D_AQ_6026C80, D_AQ_6026BF0, D_AQ_6027460, D_AQ_6026F60,
};
Gfx* D_edisplay_800CFBE4[] = { D_AQ_60040F0, D_AQ_6027C90, D_AQ_6027FA0, D_AQ_6003350, D_AQ_6028240,
                               D_AQ_6028550, D_AQ_6004DB0, D_AQ_6027930, D_AQ_600F030, D_AQ_60050F0 };
Gfx* D_edisplay_800CFC0C[] = {
    D_AQ_60294A0, D_AQ_60291B0, D_AQ_60287F0, D_AQ_6029330, D_AQ_6029240, D_AQ_6029790, D_AQ_6029900,
    D_AQ_6028F50, D_AQ_60290C0, D_AQ_6029530, D_AQ_60296A0, D_AQ_6028A80, D_AQ_6028910,
};
Gfx* D_edisplay_800CFC40[] = { aAqBoulderDL, aAqBoulderDL, aAqBoulderDL, aAqBoulderDL };
Gfx* D_edisplay_800CFC50[] = { D_AQ_601EDE0, D_AQ_601F2F0, D_AQ_601F830, D_AQ_601FD70, D_AQ_601D110 };
Gfx* D_edisplay_800CFC64[] = { D_AQ_6023940, D_AQ_6023D70, D_AQ_60249C0, D_AQ_6023EB0, D_AQ_60249C0, D_AQ_6023B80 };
Gfx* D_edisplay_800CFC7C[] = { D_ZO_601B570, D_ZO_601B710, D_ZO_60209B0, D_ZO_6020B70, D_ZO_6020D50,
                               D_ZO_601B8F0, D_ZO_601B3B0, D_ZO_601B1C0, D_ZO_6011660 };

void ActorDebris_Draw(ActorDebris* this) {
    switch (this->state) {
        case 0:
            Matrix_Translate(gGfxMatrix, 18.0f, 15.0f, -15.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aAwLeftWingDL);
            break;

        case 1:
            Matrix_Translate(gGfxMatrix, -18.0f, 15.0f, -15.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aAwRightWingDL);
            break;

        case 2:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, aAwFlap1DL);
            break;

        case 3:
            gSPDisplayList(gMasterDisp++, aAwLaserGun1DL);
            break;

        case 4:
            Graphics_SetScaleMtx(this->scale);
            if ((this->index % 2) != 0) {
                gSPDisplayList(gMasterDisp++, D_10194C0);
            } else {
                gSPDisplayList(gMasterDisp++, D_1024290);
            }
            break;

        case 39:
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFAC4[this->work_048]);
            break;

        case 40:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
            switch (this->work_048) {
                case 0:
                    break;
                case 1:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_61);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;
                case 2:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_57);
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                    break;
                case 3:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_33);
                    break;
            }

            if (gCurrentLevel != LEVEL_SOLAR) {
                gSPDisplayList(gMasterDisp++, D_TI_801B769C[this->work_046]);
            } else {
                if (gBosses[0].fwork[3] < 4800.0f) {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                    gDPSetFogColor(gMasterDisp++, 64, 32, 32, gFogAlpha);
                    gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);
                } else {
                    RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                    gDPSetFogColor(gMasterDisp++, 16, 16, 16, gFogAlpha);
                    gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);
                }
                Graphics_SetScaleMtx(this->scale);
                gSPDisplayList(gMasterDisp++, D_edisplay_800CFB40[this->work_046]);
            }
            break;

        case 41:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFADC[this->work_048]);
            break;

        case 42:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFB08[this->work_048]);
            break;

        case 43:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFB14[this->work_048]);
            break;

        case 44:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFB28[this->work_048]);
            break;

        case 45:
            gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
            break;

        case 46:
            if ((this->work_048 == 2) || (this->work_048 == 3) || (this->work_048 == 4)) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_33);
            }
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            gSPDisplayList(gMasterDisp++, D_TI_801B7584[this->work_048]);
            break;

        case 47:
            gSPDisplayList(gMasterDisp++, D_TI_801B7608[this->work_048]);
            break;

        case 48:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFB64[this->work_048]);
            break;

        case 49:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFB88[this->work_048]);
            break;

        case 50:
            Graphics_SetScaleMtx(0.7f);

            if (this->iwork[1] == 1) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
            } else if (this->iwork[1] == 2) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_30);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                Graphics_SetScaleMtx(0.7f);
            }

            switch (this->iwork[0]) {
                case 0:
                    gSPDisplayList(gMasterDisp++, D_VE1_90234D0);
                    break;
                case 1:
                    gSPDisplayList(gMasterDisp++, D_VE1_9023290);
                    break;
                case 2:
                    gSPDisplayList(gMasterDisp++, D_VE1_900D180);
                    break;
                case 3:
                    gSPDisplayList(gMasterDisp++, D_VE1_9010FD0);
                    break;
            }

            if (this->iwork[1] != 0) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_29);
                Graphics_SetScaleMtx(0.7f);
            }
            break;

        case 51:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFBA8[this->work_048]);
            break;

        case 52:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFBE4[this->work_048]);
            break;

        case 53:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFC0C[this->work_048]);
            break;

        case 54:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFC40[this->work_048]);
            break;

        case 55:
            Graphics_SetScaleMtx(this->scale);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFC50[this->work_048]);
            break;

        case 56:
            Graphics_SetScaleMtx(this->scale);
            RCP_SetupDL(&gMasterDisp, SETUPDL_41);
            Matrix_SetGfxMtx(&gMasterDisp);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 191, 255, 223, 255);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFC64[this->work_048]);
            break;

        case 58:
            Graphics_SetScaleMtx(this->scale);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_AQ_60148B0);
            break;

        case 59:
            Graphics_SetScaleMtx(this->scale);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, D_edisplay_800CFC7C[this->work_048]);
            break;

        case 70:
            gSPDisplayList(gMasterDisp++, aActorSuppliesDL);
            break;

        case 57:
            gSPDisplayList(gMasterDisp++, D_VE1_8019A008[this->work_048]);
            break;

        default:
            if (this->state >= 10) {
                if (this->state == 36) {
                    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
                }
                gSPDisplayList(gMasterDisp++, D_edisplay_800CFA54[this->state - 10]);
            }
            break;
    }
}

void Actor_DrawEngineAndContrails(Actor* this) {
    f32 sp5C;
    f32 temp1;
    f32 sp54;
    s32 pad[5];

    if ((this->iwork[11] != 0) && (this->obj.status == OBJ_ACTIVE)) {
        temp1 = 652.5f * 0.001f; // 0.65250003f;
        if (this->iwork[11] >= 2) {
            temp1 = 1.3050001f;
        }

        Math_SmoothStepToF(&this->fwork[29], temp1, 0.3f, 5.0f, 0.0f);

        sp5C = this->fwork[29];
        if ((gGameFrameCount % 2) != 0) {
            sp5C *= 1.111f;
        }
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, sp5C, sp5C * 0.7f, sp5C, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, -this->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -this->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -this->obj.rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Display_DrawEngineGlow(gLevelType);
        Matrix_Pop(&gGfxMatrix);
    }

    sp5C = this->fwork[21];
    if ((sp5C != 0.0f) && (gLevelType == LEVELTYPE_PLANET)) {
        sp54 = 0.0f;
        if ((gGameFrameCount % 2) != 0) {
            sp54 = 180.0f;
        }
        RCP_SetupDL_64_2();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 100);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, 70.0f, -10.0f, -100.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, sp5C, 1.0f, 50.0f, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_DTOR * sp54, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aBallDL);
        Matrix_Pop(&gGfxMatrix);
        Matrix_Push(&gGfxMatrix);
        Matrix_Translate(gGfxMatrix, -70.0f, -10.0f, -100.0f, MTXF_APPLY);
        Matrix_Scale(gGfxMatrix, sp5C, 1.0f, 50.0f, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, M_DTOR * sp54, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aBallDL);
        Matrix_Pop(&gGfxMatrix);
    }
}

f32 D_edisplay_800CFCA0[] = {
    1.7f, 1.8f, 2.0f, 3.0f, 3.0f, 3.0f, 3.0f, 3.0f,
};

void Actor_DrawEngineGlow(Actor* actor, EngineGlowColor color) {
    f32 scale;

    if ((actor->iwork[11] != 0) && (actor->obj.status == OBJ_ACTIVE)) {
        scale = 0.63f;
        if (actor->iwork[11] >= 2) {
            scale = D_edisplay_800CFCA0[actor->iwork[11] - 2] * 0.45f;
        }
        if ((gGameFrameCount % 2) != 0) {
            scale *= 1.2f;
        }
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, -actor->obj.rot.z * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, -actor->obj.rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -actor->obj.rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -gPlayer[gPlayerNum].camYaw, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        Display_DrawEngineGlow(color);
        Matrix_Pop(&gGfxMatrix);
    }
}

void ActorTeamArwing_Draw(ActorTeamArwing* this) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;

    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    if (((/*(fabsf(dest.z) < 3000.0f) && (fabsf(dest.x) < 3000.0f) &&*/ !gBossActive) ||
         (gPlayer[0].state == PLAYERSTATE_STANDBY) || (gCurrentLevel == LEVEL_VENOM_ANDROSS) ||
         (gCurrentLevel == LEVEL_VENOM_2) || (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE)) &&
        (gCurrentLevel != LEVEL_MACBETH) && (gCurrentLevel != LEVEL_TITANIA)) {
        if (this->obj.id == OBJ_ACTOR_CUTSCENE) {
            if (((gCurrentLevel == LEVEL_VENOM_2) && (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) &&
                 (this->index == 10)) ||
                ((gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) && (gPlayer[0].csState >= 100) &&
                 (gCurrentLevel == LEVEL_KATINA) && (this->index == 1)) ||
                ((gCurrentLevel == LEVEL_SECTOR_Y) && (gPlayer[0].state == PLAYERSTATE_STANDBY) &&
                 (this->state == 5))) {
                gActorTeamArwing.rightWingState = gPlayer[0].arwing.rightWingState;
                gActorTeamArwing.leftWingState = gPlayer[0].arwing.leftWingState;
            } else {
                gActorTeamArwing.rightWingState = gActorTeamArwing.leftWingState = WINGSTATE_INTACT;
            }
        } else {
            gActorTeamArwing.rightWingState = gActorTeamArwing.leftWingState = WINGSTATE_INTACT;
        }

        gActorTeamArwing.upperRightFlapYrot = this->fwork[15];
        gActorTeamArwing.upperLeftFlapYrot = this->fwork[16];
        gActorTeamArwing.bottomRightFlapYrot = this->fwork[26];
        gActorTeamArwing.bottomLeftFlapYrot = this->fwork[27];
        gActorTeamArwing.laserGunsYpos = gActorTeamArwing.laserGunsXpos = gActorTeamArwing.wingsXrot =
            gActorTeamArwing.wingsYrot = gActorTeamArwing.cockpitGlassXrot = gActorTeamArwing.wingsZrot = 0.0f;
        gActorTeamArwing.unk_28 = this->fwork[17];
        gActorTeamArwing.drawFace = this->iwork[TEAM_FACE];
        gActorTeamArwing.teamFaceXrot = this->fwork[20];
        gActorTeamArwing.teamFaceYrot = this->fwork[19];

        if (gLevelType == LEVELTYPE_SPACE) {
            gActorTeamArwing.upperRightFlapYrot = gActorTeamArwing.bottomRightFlapYrot =
                gActorTeamArwing.upperLeftFlapYrot = gActorTeamArwing.bottomLeftFlapYrot = 0.0f;
        }
        Display_ArwingWings(&gActorTeamArwing);
    } else if (gLevelType == LEVELTYPE_PLANET) {
        gSPDisplayList(gMasterDisp++, D_ENMY_PLANET_40018A0);
    } else if (gPlayer[0].wingPosition == 2) {
        gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_4003BD0);
    } else {
        gSPDisplayList(gMasterDisp++, D_ENMY_SPACE_4007870);
    }
    Actor_DrawEngineAndContrails(this);
}

void MeMolarRock_Draw(MeMolarRock* this) {
    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aMeMolarRockDL);
}

void MeMeteor2_Draw(MeMeteor2* this) {
    RCP_SetupDL_29(this->work_046, gFogGreen, gFogBlue, gFogAlpha, this->work_048, gFogFar);
    Matrix_Scale(gGfxMatrix, 0.5f, 0.5f, 0.5f, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);
    gSPDisplayList(gMasterDisp++, aMeMeteor1DL);
}

void MeLaserCannon1_Draw(MeLaserCannon1* this) {
    RCP_SetupDL_29(this->work_046, gFogGreen, gFogBlue, gFogAlpha, this->work_048, gFogFar);
    gSPDisplayList(gMasterDisp++, aMeLaserCannon1DL);
}

void ActorMissileSeek_Draw(Actor* missile) {
    f32 scale;

    switch (missile->eventType) {
        case 0:
            gSPDisplayList(gMasterDisp++, D_1028230);
            break;

        case 1:
            if (gCurrentLevel == LEVEL_AREA_6) {
                gSPDisplayList(gMasterDisp++, aAttacker3DL);
            } else {
                gSPDisplayList(gMasterDisp++, aGrangaFighter2DL);
            }
            break;
    }

    scale = 2.0f;
    if ((gGameFrameCount % 2) != 0) {
        scale = 1.7f;
    }

    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -60.0f, MTXF_APPLY);
    missile->iwork[11] = 1;
    Matrix_Scale(gGfxMatrix, scale, scale, scale, MTXF_APPLY);
    Actor_DrawEngineGlow(missile, EG_GREEN);
}

void CoSkibot_Draw(CoSkibot* this) {
    Matrix_Translate(gGfxMatrix, 0.0f, -124.0f, 0.0f, MTXF_APPLY);
    Animation_GetFrameData(&aCoSkibotAnim, this->animFrame, this->vwork);
    Animation_DrawSkeleton(1, aCoSkibotSkel, this->vwork, NULL, NULL, this, &gIdentityMatrix);
}

void CoRadar_Draw(CoRadar* this) {
    if (this->timer_0BC != 0) {
        RCP_SetupDL_27();
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
    }
    gSPDisplayList(gMasterDisp++, aCoRadarDL);
}

void func_edisplay_8005BAAC(void) {
}

f32 D_edisplay_800CFCCC[] = {
    0.0f, 0.05f, 0.03f, 0.02f, 0.01f, 0.05f, 0.0f, 0.02f,
};

void Object_SetShadowDL(ObjectId objId, s32 index) {
    f32 temp_fv0;
    f32 temp1;
    f32 temp2;

    switch (objId) {
        case OBJ_EFFECT_374:
            if (gEffects[index].state == 0) {
                Matrix_Scale(gGfxMatrix, 1.2f, 0.0f, 1.2f, MTXF_APPLY);
                Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                Matrix_SetGfxMtx(&gMasterDisp);
                gSPDisplayList(gMasterDisp++, aBallDL);
            }
            RCP_SetupDL(&gMasterDisp, SETUPDL_64);
            break;
        case OBJ_ACTOR_CUTSCENE:
        case OBJ_ACTOR_TEAM_BOSS:
        case OBJ_ACTOR_EVENT:
            switch (gActors[index].eventType) {
                case EVID_SPY_EYE:
                    Matrix_Scale(gGfxMatrix, 2.3f, 0.0f, 2.3f, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_102A010);
                    break;

                case EVID_VE1_BLOCKER:
                    RCP_SetupDL(&gMasterDisp, SETUPDL_48);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
                    gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 255);
                    temp_fv0 = gActors[index].fwork[15] * 3.0f;
                    Matrix_Scale(gGfxMatrix, temp_fv0, temp_fv0, temp_fv0, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, aOrbDL);
                    break;

                default:
                    temp1 = D_edisplay_800CFCCC[gGameFrameCount % 8U];
                    temp2 = D_edisplay_800CFCCC[(gGameFrameCount + 4) % 8U];
                    Matrix_Scale(gGfxMatrix, 1.4f + temp1, 0.0f, 1.4f + temp2, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 30.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
                    gSPDisplayList(gMasterDisp++, aArwingShadowDL);
                    break;
            }
            break;

        case OBJ_BOSS_CO_GRANGA:
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;

        case OBJ_BOSS_KA_SAUCERER:
            if (gPlayer[0].state == PLAYERSTATE_STANDBY) {
                RCP_SetupDL(&gMasterDisp, SETUPDL_64);
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 200);
            }
            Matrix_RotateX(gGfxMatrix, M_PI / 2, MTXF_APPLY);
            Graphics_SetScaleMtx(150.0f);
            gSPDisplayList(gMasterDisp++, aBallDL);
            break;

        case OBJ_BOSS_CO_CARRIER:
        case OBJ_BOSS_CO_CARRIER_LEFT:
        case OBJ_BOSS_CO_CARRIER_UPPER:
        case OBJ_BOSS_CO_CARRIER_BOTTOM:
            COS_DEG(gBosses[index].obj.rot.z);
            if (gGroundSurface == SURFACE_WATER) {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 90);
            } else {
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 150);
            }

            switch (objId) {
                case OBJ_BOSS_CO_CARRIER:
                    gSPDisplayList(gMasterDisp++, D_CO_6036840);
                    break;
                case OBJ_BOSS_CO_CARRIER_LEFT:
                    gSPDisplayList(gMasterDisp++, D_CO_6036CD0);
                    break;
                case OBJ_BOSS_CO_CARRIER_UPPER:
                case OBJ_BOSS_CO_CARRIER_BOTTOM:
                    gSPDisplayList(gMasterDisp++, D_CO_60363B0);
                    break;
            }
            break;

        case OBJ_ACTOR_CO_SKIBOT:
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 150);
            Matrix_Scale(gGfxMatrix, 0.4f, 0.4f, gActors[index].scale, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aCoShadow1DL);
            break;

        case OBJ_ACTOR_TI_BOULDER:
            RCP_SetupDL_48();
            RCP_SetupDL(&gMasterDisp, SETUPDL_69);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_RotateX(gGfxMatrix, gActors[index].fwork[0], MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, gActors[index].fwork[2], MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, gActors[index].scale, 1.0f, gActors[index].scale, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case OBJ_ACTOR_TI_DESERT_CRAWLER:
            RCP_SetupDL(&gMasterDisp, SETUPDL_68);
            gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 120.0f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, gActors[index].fwork[1] * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, gActors[index].fwork[2] * M_DTOR, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, gActors[index].obj.rot.y * M_DTOR, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 6.0f, 1.0f, 7.5f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case OBJ_ACTOR_TI_BOMB:
            RCP_SetupDL(&gMasterDisp, SETUPDL_69);
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 0);
            Matrix_RotateX(gGfxMatrix, gActors[index].fwork[1], MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, gActors[index].fwork[2], MTXF_APPLY);
            Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 0.0f, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, 1.2f, 1.0f, 1.2f, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, -M_PI / 2, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case OBJ_ACTOR_MA_BOULDER:
            RCP_SetupDL_48();
            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 255);
            gDPSetEnvColor(gMasterDisp++, 0, 0, 0, 255);
            Matrix_Scale(gGfxMatrix, 4.0f, 4.0f, 4.0f, MTXF_APPLY);
            Matrix_SetGfxMtx(&gMasterDisp);
            gSPDisplayList(gMasterDisp++, aOrbDL);
            break;

        case OBJ_BOSS_VE1_GOLEMECH:
            Venom1_Ve1Golemech_SetShadow(&gBosses[index]);
            break;
    }
}

void ItemCheckpoint_Draw(ItemCheckpoint* this) {
    s32 i;

    if (((gGameFrameCount & 0x18) != 0) && (this->state == 0)) {
        FrameInterpolation_RecordOpenChild(this, 0);
        FrameInterpolation_RecordMarker(__FILE__, __LINE__);
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, SETUPDL_64);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 0, 255);
        Matrix_Scale(gGfxMatrix, 3.2f, 3.2f, 3.2f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gDPSetTextureFilter(gMasterDisp++, G_TF_POINT);
        gSPDisplayList(gMasterDisp++, D_1023C80);
        gDPSetTextureFilter(gMasterDisp++, G_TF_BILERP);
        Matrix_Pop(&gGfxMatrix);
        FrameInterpolation_RecordCloseChild();
    }
    FrameInterpolation_RecordOpenChild(this, 1);
    FrameInterpolation_RecordMarker(__FILE__, __LINE__);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPTexture(gMasterDisp++, 2000, 2000, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    Matrix_RotateZ(gGfxMatrix, this->unk_58 * M_DTOR, MTXF_APPLY);

    for (i = 0; i < 8; i++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateZ(gGfxMatrix, i * 45.0f * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 2.0f * this->width, 0.0f, 0.0f, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, (gGameFrameCount + (i * 110.0f)) * M_DTOR * 7.2f * this->unk_54, MTXF_APPLY);
        Graphics_SetScaleMtx(2.0f * this->unk_50);
        gSPDisplayList(gMasterDisp++, D_101CAE0);
        Matrix_Pop(&gGfxMatrix);
    }
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    FrameInterpolation_RecordCloseChild();
}

void ItemSilverRing_Draw(ItemSilverRing* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPTexture(gMasterDisp++, 3000, 0, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
    Graphics_SetScaleMtx(this->width);
    gSPDisplayList(gMasterDisp++, D_101A570);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
}

void ItemSilverStar_Draw(ItemSilverStar* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPTexture(gMasterDisp++, 3000, 0, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
    Graphics_SetScaleMtx(this->width);
    gSPDisplayList(gMasterDisp++, D_1019CA0);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
}

void ItemGoldRing_Draw(ItemGoldRing* this) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPTexture(gMasterDisp++, 1900, 1700, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
    Graphics_SetScaleMtx(this->width);
    gSPDisplayList(gMasterDisp++, D_1016870);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR);
}

void ItemBomb_Draw(ItemBomb* this) {
    if (gCurrentLevel == LEVEL_AQUAS) {
        Graphics_SetScaleMtx(this->width);
        gSPDisplayList(gMasterDisp++, D_blue_marine_3005980);
    } else {
        Graphics_SetScaleMtx(this->width * 0.1f);
        RCP_SetupDL(&gMasterDisp, SETUPDL_29);
        gSPTexture(gMasterDisp++, 2000, 2000, 0, G_TX_RENDERTILE, G_ON);
        gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
        gSPDisplayList(gMasterDisp++, D_10231A0);
        gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
        RCP_SetupDL(&gMasterDisp, SETUPDL_27);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
        gSPDisplayList(gMasterDisp++, D_1022E80);
    }
}

void ItemLasers_Draw(ItemLasers* this) {
    Graphics_SetScaleMtx(this->width * 0.1f);
    RCP_SetupDL(&gMasterDisp, SETUPDL_29);
    gSPTexture(gMasterDisp++, 2000, 2000, 0, G_TX_RENDERTILE, G_ON);
    gSPSetGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    gSPDisplayList(gMasterDisp++, D_1019820);
    gSPClearGeometryMode(gMasterDisp++, G_TEXTURE_GEN);
    RCP_SetupDL(&gMasterDisp, SETUPDL_27);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);
    gSPDisplayList(gMasterDisp++, D_101A8E0);
}

void ItemMeteoWarp_Draw(ItemMeteoWarp* this) {
    s32 i;

    this->obj.rot.y = (Math_Atan2F(gPlayer[gPlayerNum].cam.eye.x - this->obj.pos.x,
                                   gPlayer[gPlayerNum].cam.eye.z - (this->obj.pos.z + gPathProgress)) *
                       180.0f) /
                      M_PI;
    if (this->state != 0) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_41);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, this->unk_44);
    } else {
        RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
    }

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK | G_LIGHTING);

    for (i = 0; i < 7; i++) {
        Matrix_Push(&gGfxMatrix);
        Matrix_RotateZ(gGfxMatrix, (i * 360.0f / 7.0f) * M_DTOR, MTXF_APPLY);
        Matrix_Translate(gGfxMatrix, 0.0f, this->width, 0.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_102FE80);
        Matrix_Pop(&gGfxMatrix);
    }

    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK | G_LIGHTING);
}

void Object_SetMatrix(Object* obj, s32 drawType) {
    bool isBanned = (obj->id >= OBJ_SCENERY_CO_BUILDING_5 && 
        obj->id <= OBJ_SCENERY_CO_BUILDING_8 || obj->id == OBJ_SCENERY_CO_BUILDING_10);
    bool skipRot = false;

    if(isBanned){
        f32 prevRot = obj->rot.y;
        if (gPlayer[0].cam.eye.x < obj->pos.x) {
            obj->rot.y = 271.0f;
        } else {
            obj->rot.y = 0.0f;
        }

        skipRot = prevRot != obj->rot.y;
    }

    if (drawType == 2) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, gPathProgress, MTXF_APPLY);
        Matrix_Translate(gCalcMatrix, obj->pos.x, obj->pos.y, obj->pos.z, MTXF_NEW);
        Matrix_Push(&gGfxMatrix);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_Copy(&D_edisplay_801615F0, gGfxMatrix);
        Matrix_Pop(&gGfxMatrix);
        if(isBanned && skipRot){
            FrameInterpolation_ShouldInterpolateFrame(false);
        }
        Matrix_RotateY(gCalcMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, obj->pos.x, obj->pos.y, obj->pos.z + gPathProgress, MTXF_APPLY);
        Matrix_Copy(&D_edisplay_801615F0, gGfxMatrix);
        if(isBanned && skipRot){
            FrameInterpolation_ShouldInterpolateFrame(false);
        }
        Matrix_RotateY(gGfxMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
    }

   if(isBanned && skipRot){
        FrameInterpolation_ShouldInterpolateFrame(true);
    }
}

void Boss_SetMatrix(Object* obj, s32 drawType) {
    if (drawType == 2) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, gPathProgress, MTXF_APPLY);
        Matrix_Translate(gCalcMatrix, obj->pos.x, obj->pos.y, obj->pos.z, MTXF_NEW);
        Matrix_Push(&gGfxMatrix);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_Copy(&D_edisplay_801615F0, gGfxMatrix);
        Matrix_Pop(&gGfxMatrix);
        Matrix_RotateY(gCalcMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, obj->pos.x, obj->pos.y, obj->pos.z + gPathProgress, MTXF_APPLY);
        Matrix_Copy(&D_edisplay_801615F0, gGfxMatrix);
        Matrix_RotateY(gGfxMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
    }
}

// Used for EVID_A6_UMBRA_STATION, OBJ_EFFECT_ENEMY_LASER_1 and OBJ_EFFECT_369
void ObjSpecial_SetMatrix(Object* obj, f32 xRot, f32 yRot, f32 zRot, s32 drawType) {
    if (drawType == 2) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, gPathProgress, MTXF_APPLY);
        Matrix_Translate(gCalcMatrix, obj->pos.x, obj->pos.y, obj->pos.z, MTXF_NEW);
        Matrix_Push(&gGfxMatrix);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_Copy(&D_edisplay_801615F0, gGfxMatrix);
        Matrix_Pop(&gGfxMatrix);
        Matrix_RotateY(gCalcMatrix, M_DTOR * yRot, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, M_DTOR * xRot, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, M_DTOR * zRot, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gCalcMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, obj->pos.x, obj->pos.y, obj->pos.z + gPathProgress, MTXF_APPLY);
        Matrix_Copy(&D_edisplay_801615F0, gGfxMatrix);
        Matrix_RotateY(gGfxMatrix, M_DTOR * yRot, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, M_DTOR * xRot, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, M_DTOR * zRot, MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
    }
}

void Scenery_Draw(Scenery* this, s32 cullDirection) {
    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_SCENERY, this);
    this->obj.pos.y += gCameraShakeY;
    Object_SetMatrix(&this->obj, this->info.drawType);
    this->obj.pos.y -= gCameraShakeY;

    if (this->info.drawType == 0) {
        if ((this->obj.id == OBJ_SCENERY_CO_TOWER) || (this->obj.id == OBJ_SCENERY_CO_ROCKWALL) ||
            (this->obj.id == OBJ_SCENERY_CO_HIGHWAY_4) || (this->obj.id == OBJ_SCENERY_VE1_WALL_3)) {
            RCP_SetupDL_57(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);

            if (cullDirection < 0) {
                Object_ApplyWaterDistortion();
            }

            CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_SCENERY, this){
                gSPDisplayList(gMasterDisp++, this->info.dList);
            }

            RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        } else {
            if (this->obj.id == OBJ_SCENERY_CO_HIGHWAY_3) {
                if (cullDirection < 0) {
                    return; // weird control flow
                }
                RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }

            Object_SetCullDirection(cullDirection);

            if (cullDirection < 0) {
                Object_ApplyWaterDistortion();
            }

            CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_SCENERY, this){
                gSPDisplayList(gMasterDisp++, this->info.dList);
            }

            if (this->obj.id == OBJ_SCENERY_CO_HIGHWAY_3) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }
        }
    } else if (this->info.draw != NULL) {
        Object_SetCullDirection(cullDirection);
        CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_SCENERY, this){
            this->info.draw(&this->obj);
        }
    }
}

void Sprite_Draw(Sprite* this, s32 arg1) {
    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_SPRITE, this);
    if (arg1 >= 0) {
        this->obj.pos.y += gCameraShakeY;
        Object_SetMatrix(&this->obj, 0);
        this->obj.pos.y -= gCameraShakeY;

        CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_SPRITE, this){
            if (this->info.drawType == 0) {
                gSPDisplayList(gMasterDisp++, this->info.dList);
            } else if (this->info.draw != NULL) {
                this->info.draw(&this->obj);
            }
        }
    }
}

void Actor_DrawOnRails(Actor* this) {
    Vec3f sp34 = { 0.0f, 0.0f, 0.0f };

    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_ACTOR, this);

    if (this->info.draw != NULL) {
        switch (this->obj.id) {
            case OBJ_ACTOR_ME_MORA:
                MeMora_Draw(this);
                return;
            case OBJ_ACTOR_ZO_DODORA:
                Zoness_ZoDodora_Draw(this);
                return;
        }

        if ((this->obj.id == OBJ_ACTOR_EVENT) && (this->eventType == EVID_200)) {
            MeMora_Draw(this);
        } else {
            if (this->info.unk_19 != 0) {
                this->obj.pos.y += gCameraShakeY;
                Object_SetMatrix(&this->obj, this->info.drawType);
                this->obj.pos.y -= gCameraShakeY;
            } else if ((this->obj.id == OBJ_ACTOR_EVENT) && (this->eventType != EVID_A6_UMBRA_STATION)) {
                ObjSpecial_SetMatrix(&this->obj, this->vwork[29].x, this->vwork[29].y,
                                     this->vwork[29].z + this->rot_0F4.z, this->info.drawType);
            } else {
                Object_SetMatrix(&this->obj, this->info.drawType);
            }

            if (this->info.drawType == 0) {
                CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_ACTOR, this){
                    gSPDisplayList(gMasterDisp++, this->info.dList);
                }
                Object_UpdateSfxSource(this->sfxSource);
            } else {
                CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_ACTOR, this){
                    this->info.draw(&this->obj);
                }
                Object_UpdateSfxSource(this->sfxSource);
                if (((this->obj.id == OBJ_ACTOR_TEAM_BOSS) ||
                     ((this->obj.id == OBJ_ACTOR_SX_SLIPPY) && (this->animFrame > 0))) &&
                    (gReflectY > 0)) {
                    Matrix_MultVec3f(gGfxMatrix, &sp34, &gTeamArrowsViewPos[this->aiType]);
                }
            }
            if ((this->lockOnTimers[TEAM_ID_FOX] != 0) && (gReflectY > 0)) {
                sp34.y += this->info.targetOffset;
                Matrix_MultVec3f(gGfxMatrix, &sp34, &gLockOnTargetViewPos[TEAM_ID_FOX]);
                if (gLockOnTargetViewPos[TEAM_ID_FOX].z > -200.0f) {
                    this->lockOnTimers[TEAM_ID_FOX] = 0;
                }
            }
        }
    }
}

void Actor_DrawAllRange(Actor* this) {
    s32 playerNum;
    Vec3f srcViewPos = { 0.0f, 0.0f, 0.0f };
    f32 var_fa1;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;

    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_ACTOR, this);

    sDrewActor = false;

    if (this->info.drawType == 2) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, gPathProgress, MTXF_APPLY);
        Matrix_Translate(gCalcMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, MTXF_NEW);
        Matrix_Push(&gGfxMatrix);
        Matrix_Mult(gGfxMatrix, gCalcMatrix, MTXF_APPLY);
        Matrix_MultVec3f(gGfxMatrix, &srcViewPos, &sViewPos);
        Matrix_Pop(&gGfxMatrix);

        var_fv0 = 0.0f;
        var_fv1 = -12000.0f;
        if ((this->obj.id == OBJ_ACTOR_ALLRANGE) && (this->aiType >= AI360_GREAT_FOX)) {
            var_fv0 = 1000.0f;
            var_fv1 = -25000.0f;
        }

        // @port draw no matter what
        goto render;

        if ((var_fv0 > sViewPos.z) && (sViewPos.z > var_fv1)) {
            if (fabsf(sViewPos.x) < (fabsf(sViewPos.z * 0.5f) + 500.0f)) {
                if (fabsf(sViewPos.y) < (fabsf(sViewPos.z * 0.5f) + 500.0f)) {
                render:
                    Matrix_RotateY(gCalcMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gCalcMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gCalcMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_ACTOR, this){
                        this->info.draw(&this->obj);
                    }
                    sDrewActor = true;
                    if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) && (this->obj.id == OBJ_ACTOR_ALLRANGE) &&
                        (this->aiType == AI360_MISSILE)) {
                        gTeamArrowsViewPos[0] = sViewPos;
                    }
                }
            }
        }
    } else {
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, MTXF_APPLY);
        Matrix_MultVec3f(gGfxMatrix, &srcViewPos, &sViewPos);

        if ((gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) || (gPlayer[0].state == PLAYERSTATE_STANDBY) ||
            ((this->obj.id == OBJ_ACTOR_ALLRANGE) && (this->aiType >= AI360_GREAT_FOX)) ||
            ((this->obj.id == OBJ_ACTOR_CUTSCENE) && (this->info.bonus != 0))) {
            var_ft5 = var_fv0 = 3000.0f;
            var_fv1 = -29000.0f;
            var_fa1 = 0.7f;
        } else {
            var_ft5 = 500.0f;
            var_fv0 = 0.0f;
            var_fv1 = -20000.0f;
            var_fa1 = 0.5f;
        }

        // @port draw no matter what
        goto render2;

        if ((var_fv0 > sViewPos.z) && (sViewPos.z > var_fv1)) {
            if (fabsf(sViewPos.x) < (fabsf(sViewPos.z * var_fa1) + var_ft5)) {
                if (fabsf(sViewPos.y) < (fabsf(sViewPos.z * var_fa1) + var_ft5)) {
                render2:
                    if (this->info.draw != NULL) {
                        Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                        Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                        Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_ACTOR, this){
                            this->info.draw(&this->obj);
                        }
                        sDrewActor = true;
                        if ((gPlayer[0].state == PLAYERSTATE_ACTIVE) &&
                            (((this->obj.id == OBJ_ACTOR_ALLRANGE) &&
                              ((this->aiType <= AI360_PEPPY) || (this->aiType == AI360_KATT) ||
                               (this->aiType == AI360_BILL))) ||
                             (this->obj.id == OBJ_ACTOR_TEAM_BOSS))) {
                            gTeamArrowsViewPos[this->aiType] = sViewPos;
                        }
                    }
                }
            }
        }
    }

    if (!sDrewActor) {
        this->lockOnTimers[gPlayerNum] = 0;
        if ((this->obj.id == OBJ_ACTOR_DEBRIS) || (this->obj.id == OBJ_ACTOR_AND_BRAIN_WASTE)) {
            Object_Kill(&this->obj, this->sfxSource);
        }
    }

    for (playerNum = 0; playerNum < gCamCount; playerNum++) {
        if (this->lockOnTimers[playerNum] != 0) {
            gLockOnTargetViewPos[playerNum] = sViewPos;
            gLockOnTargetViewPos[playerNum].y += this->info.targetOffset;
            if ((playerNum == gPlayerNum) && (gLockOnTargetViewPos[playerNum].z > -300.0f)) {
                this->lockOnTimers[playerNum] = 0;
            }
        }
    }

    Object_SetSfxSourceToView(this->sfxSource, &sViewPos);
    this->iwork[24] = sDrewActor;
}

void Boss_Draw(Boss* this, s32 arg1) {
    f32 var_fa1;
    f32 var_ft5;
    f32 var_fv0;
    f32 var_fv1;
    f32 sp3C;
    Vec3f origin = { 0.0f, 0.0f, 0.0f };

    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_BOSS, this);

    if (this->info.unk_19 != 0) {
        this->obj.pos.y += this->yOffset + gCameraShakeY;
        Boss_SetMatrix(&this->obj, this->info.drawType);
        this->obj.pos.y -= this->yOffset + gCameraShakeY;
    } else {
        Boss_SetMatrix(&this->obj, this->info.drawType);
    }

    Matrix_MultVec3f(&D_edisplay_801615F0, &origin, &D_edisplay_801615D0);
    Object_SetSfxSourceToView(this->sfxSource, &D_edisplay_801615D0);

    if ((this->obj.id == OBJ_BOSS_KA_SAUCERER) || (this->obj.id == OBJ_BOSS_KA_FLBASE)) {
        var_fa1 = 6000.0f;
        var_fv0 = 6000.0f;
        var_ft5 = 0.9f;
        var_fv1 = -20000.0f;

    } else if (this->obj.id == OBJ_BOSS_SZ_GREAT_FOX) {
        var_fv1 = -25000.0f;
        var_ft5 = 0.7f;
        var_fa1 = 3000.0f;
        var_fv0 = 2000.0f;
    } else {
        var_ft5 = 0.5f;
        var_fa1 = 2000.0f;
        var_fv0 = 1000.0f;
        var_fv1 = -15000.0f;
    }

    sp3C = -1.0f;

    // @port draw no matter what
    if ((gCurrentLevel != LEVEL_KATINA) && (gCurrentLevel != LEVEL_SECTOR_Y)) { // Excepting Katina because of KaSaucerer's bug
        goto render;
    }

    if ((D_edisplay_801615D0.z < var_fv0) && (var_fv1 < D_edisplay_801615D0.z)) {
        if (fabsf(D_edisplay_801615D0.x) < (fabsf(D_edisplay_801615D0.z * var_ft5) + var_fa1)) {
            if (fabsf(D_edisplay_801615D0.y) < (fabsf(D_edisplay_801615D0.z * var_ft5) + var_fa1)) {
            render:
                sp3C = 1.0f;
                if (this->obj.id != OBJ_BOSS_BO_BASE) {
                    if (this->obj.id != OBJ_BOSS_KA_SAUCERER) {
                        Display_SetSecondLight(&this->obj.pos);
                    }
                    if (this->info.drawType != 2) {
                        Matrix_SetGfxMtx(&gMasterDisp);
                    }
                    if (arg1 < 0) {
                        Object_ApplyWaterDistortion();
                    }
                    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_BOSS, this){
                        this->info.draw(&this->obj);
                    }
                }
            }
        }
    }
    D_edisplay_801615D0.y = sp3C;

    if (this->obj.id == OBJ_BOSS_BO_BASE) {
        this->vwork[30] = D_edisplay_801615D0;
        Display_SetSecondLight(&this->obj.pos);
        Matrix_SetGfxMtx(&gMasterDisp);
        CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_BOSS, this){
            this->info.draw(&this->obj);
        }
    }
}

void Effect_DrawOnRails(Effect* this, s32 arg1) {
    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_EFFECT, this);

    if ((arg1 < 0) && (this->obj.pos.y < 7.0f)) {
        return;
    }

    if ((this->obj.id == OBJ_EFFECT_ENEMY_LASER_1) || (this->obj.id == OBJ_EFFECT_369)) {
        ObjSpecial_SetMatrix(&this->obj, this->unk_60.x, this->unk_60.y, this->unk_60.z, 0);
    } else if (this->info.unk_14 == -1) {
        this->obj.pos.y += gCameraShakeY;
        Object_SetMatrix(&this->obj, 0);
        this->obj.pos.y -= gCameraShakeY;
    } else {
        Object_SetMatrix(&this->obj, 0);
    }

    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_EFFECT, this){
        if (this->info.draw != NULL) {
            this->info.draw(&this->obj);
        }
    }
}

void Effect_DrawAllRange(Effect* this) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;
    f32 minZ;
    u8 drawn = false;
    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_EFFECT, this);

    if (this->info.unk_14 == -1) {
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y + gCameraShakeY, this->obj.pos.z + gPathProgress,
                         MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + gPathProgress, MTXF_APPLY);
    }

    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    if ((gCurrentLevel == LEVEL_SECTOR_Z) || (gCurrentLevel == LEVEL_BOLSE)) {
        minZ = -20000.0f;
    } else {
        minZ = -10000.0f;
    }

    if ((dest.z < 0.0f) && (minZ < dest.z)) {
        // @port: Extend draw distance up to 32/9
        if (fabsf(dest.x) < (fabsf(dest.z * /* 0.5f */ 1.5f) + 500.0f)) {
            if (fabsf(dest.y) < (fabsf(dest.z * 0.5f) + 500.0f)) {
                if (this->info.draw != NULL) {
                    Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_EFFECT, this){
                        this->info.draw(&this->obj);
                    }
                }
                drawn = true;
            }
        }
    }

    Object_SetSfxSourceToView(this->sfxSource, &dest);

    if (!drawn && (this->obj.id != OBJ_EFFECT_CLOUDS) && (this->obj.id != OBJ_EFFECT_TIMED_SFX) && (!gVersusMode)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void Item_Draw(Item* this, s32 arg1) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;
    u8 drawn;

    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_ITEM, this);

    Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z + gPathProgress, MTXF_APPLY);
    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    drawn = false;

    if ((dest.z < 0.0f) && (dest.z > -12000.0f)) {
        // @port: Extend draw distance up to 32/9
        if (fabsf(dest.x) < (fabsf(dest.z * /* 0.5f */ 1.5f) + 500.0f)) {
            if (fabsf(dest.y) < (fabsf(dest.z * 0.5f) + 500.0f)) {
                if (this->info.draw != NULL) {
                    Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_ITEM, this){
                        if (this->info.drawType == 0) {
                            gSPDisplayList(gMasterDisp++, this->info.dList);
                        } else {
                            this->info.draw(&this->obj);
                        }
                    }
                }
                drawn = true;
            }
        }
    }

    Object_SetSfxSourceToView(this->sfxSource, &dest);

    if (!drawn && (gLevelMode == LEVELMODE_ALL_RANGE) && (gCamCount == 1) && (this->obj.id < OBJ_ITEM_GOLD_RING) &&
        (gCurrentLevel != LEVEL_VENOM_ANDROSS)) {
        Object_Kill(&this->obj, this->sfxSource);
    }
}

void ActorAllRange_DrawShadow(ActorAllRange* this) {
    Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->fwork[25] + 3.0f, this->obj.pos.z, MTXF_APPLY);

    if (gCurrentLevel == LEVEL_FORTUNA) {
        Matrix_RotateY(gGfxMatrix, this->fwork[27], MTXF_APPLY);
        Matrix_RotateX(gGfxMatrix, this->fwork[26], MTXF_APPLY);
        Matrix_RotateZ(gGfxMatrix, this->fwork[28], MTXF_APPLY);
        Matrix_RotateY(gGfxMatrix, -this->fwork[27], MTXF_APPLY);
    }

    Matrix_Scale(gGfxMatrix, 1.4f, 0.0f, 1.4f, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, (this->obj.rot.y + 180.0f) * M_DTOR, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    if (this->aiType <= AI360_PEPPY) {
        Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, 30.0f, MTXF_APPLY);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, aArwingShadowDL);
    } else if (gCurrentLevel == LEVEL_KATINA) {
        if ((this->animFrame == 1) || (this->animFrame == 2)) {
            gSPDisplayList(gMasterDisp++, aKaCornerianFighterShadowDL);
        } else {
            gSPDisplayList(gMasterDisp++, aKaEnemyShadowDL);
        }
    } else if ((this->aiType <= AI360_ANDREW) || (gCurrentLevel != LEVEL_FORTUNA)) {
        gSPDisplayList(gMasterDisp++, aStarWolfShadowDL);
    } else if (gCurrentLevel == LEVEL_FORTUNA) {
        gSPDisplayList(gMasterDisp++, aFoEnemyShadowDL);
    } else {
        gSPDisplayList(gMasterDisp++, aStarWolfShadowDL);
    }
}

void Object_DrawShadow(s32 index, Object* obj) {
    RCP_SetupDL(&gMasterDisp, SETUPDL_66);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 0, 180);

    if (obj->id == OBJ_ACTOR_ALLRANGE) {
        ActorAllRange_DrawShadow(&gActors[index]);
    } else {
        switch (obj->id) {
            case OBJ_ACTOR_TI_BOULDER:
                Matrix_Translate(gGfxMatrix, obj->pos.x, gGroundHeight + 2.0f + gActors[index].fwork[1],
                                 obj->pos.z + gPathProgress, MTXF_APPLY);
                break;

            case OBJ_ACTOR_TI_DESERT_CRAWLER:
            case OBJ_ACTOR_TI_BOMB:
                Matrix_Translate(gGfxMatrix, obj->pos.x, gGroundHeight + 2.0f + gActors[index].fwork[0],
                                 obj->pos.z + gPathProgress, MTXF_APPLY);
                break;

            case OBJ_BOSS_KA_SAUCERER:
                Matrix_Translate(gGfxMatrix, obj->pos.x, gGroundHeight + 2.0f + gCameraShakeY, obj->pos.z, MTXF_APPLY);
                break;

            default:
                Matrix_Translate(gGfxMatrix, obj->pos.x, gGroundHeight + 2.0f, obj->pos.z + gPathProgress, MTXF_APPLY);
                break;
        }
        if ((gGroundType != 4) || (obj->id == OBJ_ACTOR_EVENT) || (obj->id == OBJ_ACTOR_CUTSCENE) ||
            (obj->id == OBJ_ACTOR_TEAM_BOSS)) {
            Matrix_Scale(gGfxMatrix, 1.0f, 0.0f, 1.0f, MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, obj->rot.y * M_DTOR, MTXF_APPLY);
        }

        if ((obj->id < OBJ_ACTOR_MAX) && (obj->id != OBJ_ACTOR_TI_BOULDER) &&
            (obj->id != OBJ_ACTOR_TI_DESERT_CRAWLER) && (obj->id != OBJ_ACTOR_TI_BOMB)) {
            Matrix_RotateX(gGfxMatrix, obj->rot.x * M_DTOR, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, obj->rot.z * M_DTOR, MTXF_APPLY);
        }
        Matrix_SetGfxMtx(&gMasterDisp);
        Object_SetShadowDL(obj->id, index);
    }
}

void Object_ClampSfxSource(f32* sfxSrc) {
    if (sfxSrc[0] > 5000.0f) {
        sfxSrc[0] = 5000.0f;
    }
    if (sfxSrc[0] < -5000.0f) {
        sfxSrc[0] = -5000.0f;
    }
    if (sfxSrc[1] > 2000.0f) {
        sfxSrc[1] = 2000.0f;
    }
    if (sfxSrc[1] < -2000.0f) {
        sfxSrc[1] = -2000.0f;
    }
    if (sfxSrc[2] > 5000.0f) {
        sfxSrc[2] = 5000.0f;
    }
    if (sfxSrc[2] < -5000.0f) {
        sfxSrc[2] = -5000.0f;
    }
}

void Object_SetSfxSourceToPos(f32* sfxSrc, Vec3f* pos) {
    Vec3f src;
    Vec3f dest;

    if (gCamCount != 1) {
        sfxSrc[0] = sfxSrc[1] = sfxSrc[2] = 0.0f;
    } else {
        Matrix_RotateY(gCalcMatrix, gPlayer[0].camYaw, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, gPlayer[0].camPitch, MTXF_APPLY);
        src.x = pos->x - gPlayCamEye.x;
        src.y = pos->y - gPlayCamEye.y;
        src.z = pos->z + gPathProgress - gPlayCamEye.z;
        Matrix_MultVec3f(gCalcMatrix, &src, &dest);
        sfxSrc[0] = dest.x;
        sfxSrc[1] = dest.y;
        sfxSrc[2] = dest.z;
    }
    Object_ClampSfxSource(sfxSrc);
}

void Object_UpdateSfxSource(f32* sfxSrc) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;
    s32 pad;

    if (gCamCount != 1) {
        sfxSrc[0] = sfxSrc[1] = sfxSrc[2] = 0.0f;
    } else {
        Matrix_MultVec3f(&D_edisplay_801615F0, &src, &dest);
        sfxSrc[0] = dest.x;
        sfxSrc[1] = dest.y;
        sfxSrc[2] = dest.z;
    }
    Object_ClampSfxSource(sfxSrc);
}

void Object_SetSfxSourceToView(f32* sfxSrc, Vec3f* viewPos) {
    if (gCamCount != 1) {
        sfxSrc[0] = sfxSrc[1] = sfxSrc[2] = 0.0f;
    } else {
        sfxSrc[0] = viewPos->x;
        sfxSrc[1] = viewPos->y;
        sfxSrc[2] = viewPos->z;
    }
    Object_ClampSfxSource(sfxSrc);
}

void Scenery360_Draw(Scenery360* this) {
    Vec3f src = { 0.0f, 0.0f, 0.0f };
    Vec3f dest;

    CALL_CANCELLABLE_RETURN_EVENT(ObjectDrawPreSetupEvent, OBJECT_TYPE_SCENERY360, this);

    f32 behindZdist = 1000.0f;
    f32 frontZdist = -12000.0f;
    f32 xyOffsetBounds = 2000.0f + 1000.0f;
    f32 xyObjDistBoundMod = 0.5f;

    if (this->obj.id == OBJ_SCENERY_SY_SHOGUN_SHIP) {
        behindZdist = 4000.0f;
        frontZdist = -13000.0f;
        xyOffsetBounds = 4500.0f;
    } else if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
        frontZdist = -20000.0f;
        xyObjDistBoundMod = 0.4f;
    } else if (this->obj.id == OBJ_SCENERY_VS_KA_FLBASE) {
        behindZdist = 6000.0f;
        frontZdist = -20000.0f;
        xyOffsetBounds = 6000.0f;
        xyObjDistBoundMod = 0.9f;
    }

    if ((gLevelType == LEVELTYPE_PLANET) || (gCurrentLevel == LEVEL_BOLSE)) {
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y + gCameraShakeY, this->obj.pos.z, MTXF_APPLY);
    } else {
        Matrix_Translate(gGfxMatrix, this->obj.pos.x, this->obj.pos.y, this->obj.pos.z, MTXF_APPLY);
    }

    Matrix_MultVec3f(gGfxMatrix, &src, &dest);

    if (gCurrentLevel == LEVEL_SECTOR_Z) {
        behindZdist = 6000.0f;
        frontZdist = -20000.0f * 2;
        xyOffsetBounds = 6000.0f * 2;
        xyObjDistBoundMod = 0.9f;
        goto check;
    }

    if ((gCurrentLevel != LEVEL_SECTOR_Y) && (gCurrentLevel != LEVEL_VENOM_ANDROSS)) {
        goto render;
    }

check:
    if ((dest.z < behindZdist) && (frontZdist < dest.z)) {
        if (fabsf(dest.y) < (fabsf(dest.z * xyObjDistBoundMod) + xyOffsetBounds)) {
            if (fabsf(dest.x) < (fabsf(dest.z * xyObjDistBoundMod) + xyOffsetBounds)) {
            render:
                Display_SetSecondLight(&this->obj.pos);
                if (this->obj.id == OBJ_SCENERY_AND_PASSAGE) {
                    Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                    Matrix_RotateX(gGfxMatrix, this->obj.rot.x * M_DTOR, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, this->obj.rot.z * M_DTOR, MTXF_APPLY);
                    Matrix_RotateY(gGfxMatrix, M_PI / 2, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, -551.0f, 0.0f, 0.0f, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_SCENERY360, this){
                        gSPDisplayList(gMasterDisp++, D_VE2_6007650);
                    }
                } else {
                    Matrix_RotateY(gGfxMatrix, this->obj.rot.y * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    CALL_CANCELLABLE_EVENT(ObjectDrawPostSetupEvent, OBJECT_TYPE_SCENERY360, this){
                        gSPDisplayList(gMasterDisp++, this->info.dList);
                    }
                }

            }
        }
    }
}

void Display_SetSecondLight(Vec3f* pos) {
    Vec3f sp9C;
    f32 sp98;
    f32 sp94;
    f32 lightDist;
    Vec3f sp84;
    f32 temp1;
    f32 temp2;
    f32 lightFade;
    Vec3f sp6C;
    f32 temp3;
    f32 pad;

    if (gLight3Brightness > 0.01f) {
        sp9C.x = pos->x - gLight3x;
        sp9C.y = pos->y - gLight3y;
        sp9C.z = pos->z - gLight3z;
        lightDist = VEC3F_MAG(&sp9C);
        if (gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) {
            lightFade = 700.0f / lightDist;
        } else {
            lightFade = 200.0f / lightDist;
        }

        if (lightFade > 1.0f) {
            lightFade = 1.0f;
        }

        if (gGroundClipMode == 2) {
            lightFade = 1.0f;
        }

        sp94 = Math_Atan2F(sp9C.x, sp9C.z);
        sp98 = -Math_Atan2F(sp9C.y, sqrtf(SQ(sp9C.x) + SQ(sp9C.z)));

        Matrix_Push(&gCalcMatrix);
        Matrix_RotateZ(gCalcMatrix, gPlayer[gPlayerNum].camRoll * D_ctx_80177950 * M_DTOR, MTXF_NEW);
        Matrix_RotateX(gCalcMatrix, -gPlayer[gPlayerNum].camPitch, MTXF_APPLY);
        Matrix_RotateY(gCalcMatrix, gPlayer[gPlayerNum].camYaw + sp94, MTXF_APPLY);
        Matrix_RotateX(gCalcMatrix, sp98, MTXF_APPLY);
        sp6C.x = 0.0f;
        sp6C.y = 0.0f;
        sp6C.z = -100.0f;

        Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp6C, &sp84);

        Matrix_Pop(&gCalcMatrix);

        temp1 = gLight3R * gLight3Brightness * lightFade;
        temp2 = gLight3G * gLight3Brightness * lightFade;
        temp3 = gLight3B * gLight3Brightness * lightFade;

        Lights_SetTwoLights(&gMasterDisp, gLight1x, gLight1y, gLight1z, sp84.x, sp84.y, sp84.z, gLight1R, gLight1G,
                            gLight1B, temp1, temp2, temp3, gAmbientR, gAmbientG, gAmbientB);
    }
}

bool func_edisplay_8005F9DC(Vec3f* arg0) {
    Vec3f src;
    Vec3f dest;

    Matrix_RotateY(gCalcMatrix, gPlayer[gPlayerNum].camYaw, MTXF_NEW);
    Matrix_RotateX(gCalcMatrix, gPlayer[gPlayerNum].camPitch, MTXF_APPLY);

    src.x = arg0->x - gPlayer[gPlayerNum].cam.eye.x;
    src.y = arg0->y - gPlayer[gPlayerNum].cam.eye.y;
    src.z = arg0->z - gPlayer[gPlayerNum].cam.eye.z;

    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);

    if ((dest.z < 1000.0f) && (dest.z > -13000.0f)) {
        if (fabsf(dest.x) < (fabsf(dest.z * 0.4f) + 2000.0f)) {
            if (fabsf(dest.y) < (fabsf(dest.y * 0.4f) + 2000.0f)) {
                return true;
            }
        }
    }

    return false;
}

void Object_DrawAll(s32 cullDirection) {
    Vec3f spAC;
    s32 i;
    s32 pad[5]; // probably separate iterators for each loop
    Actor* actor;
    Boss* boss;
    Sprite* sprite;
    Scenery360* scenery360;
    Item* item;
    Scenery* scenery;

    if ((gLevelMode == LEVELMODE_ALL_RANGE) && (gCurrentLevel != LEVEL_KATINA)) {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);

        if (gDrawBackdrop == 5) {
            gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
        }

        for (i = 0, scenery360 = gScenery360; i < 200; i++, scenery360++) {
            FrameInterpolation_RecordOpenChild(scenery360, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            if ((scenery360->obj.status == OBJ_ACTIVE) && (scenery360->obj.id != OBJ_SCENERY_LEVEL_OBJECTS)) {
                if (gCurrentLevel == LEVEL_BOLSE) {
                    spAC.x = scenery360->sfxSource[0];
                    spAC.y = scenery360->sfxSource[1];
                    spAC.z = scenery360->sfxSource[2];
                    Matrix_MultVec3fNoTranslate(&D_BO_8019EE80, &spAC, &scenery360->obj.pos);
                    scenery360->obj.rot.y = scenery360->unk_54 + gBosses->obj.rot.y;
                }
                Matrix_Push(&gGfxMatrix);
                Scenery360_Draw(scenery360);
                Matrix_Pop(&gGfxMatrix);
            }
            FrameInterpolation_RecordCloseChild();
        }
    } else {
        RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
        for (i = 0, scenery = gScenery; i < ARRAY_COUNT(gScenery); i++, scenery++) {
            if (scenery->obj.status >= OBJ_ACTIVE) {
                FrameInterpolation_RecordOpenChild(scenery, i);
                FrameInterpolation_RecordMarker(__FILE__, __LINE__);
                if (cullDirection > 0) {
                    Display_SetSecondLight(&scenery->obj.pos);
                }
                Matrix_Push(&gGfxMatrix);
                Scenery_Draw(scenery, cullDirection);
                Matrix_Pop(&gGfxMatrix);
                Object_UpdateSfxSource(scenery->sfxSource);
                FrameInterpolation_RecordCloseChild();
            }
        }
    }

    for (i = 0, boss = &gBosses[0]; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status >= OBJ_ACTIVE) && (boss->obj.id != OBJ_BOSS_BO_BASE_SHIELD)) {
            FrameInterpolation_RecordOpenChild(boss, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            if ((boss->timer_05C % 2) == 0) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 64, 64, 255, 255);
            }

            Object_SetCullDirection(cullDirection);
            Matrix_Push(&gGfxMatrix);
            Boss_Draw(boss, cullDirection);
            Matrix_Pop(&gGfxMatrix);
            if (boss->drawShadow && (D_edisplay_801615D0.y > 0.0f)) {
                Matrix_Push(&gGfxMatrix);
                Object_DrawShadow(i, &boss->obj);
                Matrix_Pop(&gGfxMatrix);
            }
            FrameInterpolation_RecordCloseChild();
        }
    }

    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);

    for (i = 0, sprite = &gSprites[0]; i < ARRAY_COUNT(gSprites); i++, sprite++) {
        if ((sprite->obj.status >= OBJ_ACTIVE) && func_enmy_80060FE4(&sprite->obj.pos, -12000.0f)) {
            FrameInterpolation_RecordOpenChild(sprite, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            Matrix_Push(&gGfxMatrix);

            if ((sprite->obj.id == OBJ_SPRITE_CO_RUIN1) || (sprite->obj.id == OBJ_SPRITE_CO_RUIN2)) {
                RCP_SetupDL_57(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_60(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            }

            Sprite_Draw(sprite, cullDirection);
            Matrix_Pop(&gGfxMatrix);
            FrameInterpolation_RecordCloseChild();
        }
    }

    for (i = 0, actor = &gActors[0]; i < ARRAY_COUNT(gActors); i++, actor++) {
        if (actor->obj.status >= OBJ_ACTIVE) {
            FrameInterpolation_RecordOpenChild(actor, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            if ((actor->timer_0C6 % 2) == 0) {
                if (gCurrentLevel == LEVEL_UNK_15) {
                    RCP_SetupDL_23();
                } else {
                    RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
                }
            } else {
                RCP_SetupDL_27();

                if (actor->scale >= 0.0f) {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 0, 0, 255);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 64, 64, 255, 255);
                }
            }

            switch (gLevelMode) {
                case LEVELMODE_ON_RAILS:
                case LEVELMODE_TURRET:
                    Matrix_Push(&gGfxMatrix);

                    if ((gPlayer[0].state == PLAYERSTATE_LEVEL_INTRO) ||
                        (gPlayer[0].state == PLAYERSTATE_LEVEL_COMPLETE) || (gCurrentLevel == LEVEL_AQUAS)) {
                        Display_SetSecondLight(&actor->obj.pos);
                    }

                    Object_SetCullDirection(cullDirection);
                    Actor_DrawOnRails(actor);
                    Matrix_Pop(&gGfxMatrix);

                    if (actor->drawShadow) {
                        Matrix_Push(&gGfxMatrix);
                        Object_DrawShadow(i, &actor->obj);
                        Matrix_Pop(&gGfxMatrix);
                    }
                    break;

                case LEVELMODE_ALL_RANGE:
                    Matrix_Push(&gGfxMatrix);
                    Actor_DrawAllRange(actor);
                    Matrix_Pop(&gGfxMatrix);
                    if (actor->drawShadow && sDrewActor &&
                        ((sViewPos.z > -4000.0f) || (gCurrentLevel != LEVEL_KATINA))) {
                        Matrix_Push(&gGfxMatrix);
                        Object_DrawShadow(i, &actor->obj);
                        Matrix_Pop(&gGfxMatrix);
                    }
                    break;
            }
            FrameInterpolation_RecordCloseChild();  
        }
    }

    gDPSetFogColor(gMasterDisp++, gFogRed, gFogGreen, gFogBlue, gFogAlpha);
    gSPFogPosition(gMasterDisp++, gFogNear, gFogFar);

    Lights_SetOneLight(&gMasterDisp, -60, -60, 60, 150, 150, 150, 20, 20, 20);

    for (i = 0, item = &gItems[0]; i < ARRAY_COUNT(gItems); i++, item++) {
        if (item->obj.status >= OBJ_ACTIVE) {
            FrameInterpolation_RecordOpenChild(item, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            Matrix_Push(&gGfxMatrix);
            RCP_SetupDL(&gMasterDisp, SETUPDL_29);
            Object_SetCullDirection(cullDirection);
            Item_Draw(item, cullDirection);
            Matrix_Pop(&gGfxMatrix);
            FrameInterpolation_RecordCloseChild();
        }
    }

    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);
}

void Effect_DrawAll(s32 arg0) {
    s32 i;
    Boss* boss;
    Effect* effect;

    RCP_SetupDL(&gMasterDisp, SETUPDL_64);

    for (i = 0, effect = &gEffects[0]; i < ARRAY_COUNT(gEffects); i++, effect++) {
        if (effect->obj.status >= OBJ_ACTIVE) {
            FrameInterpolation_RecordOpenChild(effect, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            if (effect->info.unk_14 == 1) {
                effect->obj.rot.y = RAD_TO_DEG(-gPlayer[gPlayerNum].camYaw);
                effect->obj.rot.x = RAD_TO_DEG(gPlayer[gPlayerNum].camPitch);
            }

            if (gLevelMode == LEVELMODE_ALL_RANGE) {
                Matrix_Push(&gGfxMatrix);
                Effect_DrawAllRange(effect);
                Matrix_Pop(&gGfxMatrix);
            } else {
                Matrix_Push(&gGfxMatrix);
                Effect_DrawOnRails(effect, arg0);
                Matrix_Pop(&gGfxMatrix);
                Object_UpdateSfxSource(effect->sfxSource);
                if (effect->obj.id == OBJ_EFFECT_374) {
                    Matrix_Push(&gGfxMatrix);
                    Object_DrawShadow(i, &effect->obj);
                    Matrix_Pop(&gGfxMatrix);
                }
            }
            FrameInterpolation_RecordCloseChild();
        }
    }

    for (i = 0, boss = &gBosses[0]; i < ARRAY_COUNT(gBosses); i++, boss++) {
        if ((boss->obj.status >= OBJ_ACTIVE) && (boss->obj.id == OBJ_BOSS_BO_BASE_SHIELD)) {
            FrameInterpolation_RecordOpenChild(boss, i);
            FrameInterpolation_RecordMarker(__FILE__, __LINE__);
            if ((boss->timer_05C % 2) == 0) {
                RCP_SetupDL_29(gFogRed, gFogGreen, gFogBlue, gFogAlpha, gFogNear, gFogFar);
            } else {
                RCP_SetupDL_27();
                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 64, 64, 255, 255);
            }
            Matrix_Push(&gGfxMatrix);
            Boss_Draw(boss, arg0);
            Matrix_Pop(&gGfxMatrix);
            FrameInterpolation_RecordCloseChild();
        }
    }
}

void Object_Draw(s32 arg0) {
    gReflectY = 1;
    Object_DrawAll(1);

    if ((gGroundSurface == SURFACE_WATER) && (gPlayer[0].state != PLAYERSTATE_LEVEL_INTRO)) {
        gReflectY = -1;
        Lights_SetOneLight(&gMasterDisp, gLight1x, -1 * gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR,
                           gAmbientG, gAmbientB);
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, MTXF_APPLY);
        Object_DrawAll(-1);
        Matrix_Pop(&gGfxMatrix);
        Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR,
                           gAmbientG, gAmbientB);
    }
}

void Effect_Draw(u8 arg0) {
    if (arg0 == 0) {
        gReflectY = 1;
        Effect_DrawAll(1);
    } else if ((gGroundSurface == SURFACE_WATER) && (gPlayer[0].state != PLAYERSTATE_LEVEL_INTRO)) {
        gReflectY = -1;
        Matrix_Push(&gGfxMatrix);
        Matrix_Scale(gGfxMatrix, 1.0f, -1.0f, 1.0f, MTXF_APPLY);
        Effect_DrawAll(-1);
        Matrix_Pop(&gGfxMatrix);
    }
    gReflectY = 1;
}

Vtx D_edisplay_800CFD40[] = {
    VTX(1, 0, 0, 0, 0, 255, 255, 255, 255),
    VTX(-1, 0, 0, 0, 0, 255, 255, 255, 255),
    VTX(-1, 0, -1, 0, 0, 255, 255, 255, 255),
    VTX(1, 0, -1, 0, 0, 255, 255, 255, 255),
};
Gfx D_edisplay_800CFD80[] = {
    gsSPVertex(D_edisplay_800CFD40, 4, 0),
    gsSP1Quadrangle(1, 2, 3, 0, 0),
    gsSPEndDisplayList(),
};

void TexturedLine_Draw(void) {
    s32 i;

    if (gCurrentLevel == LEVEL_MACBETH) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_33);
        gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    } else if ((gCurrentLevel == LEVEL_AQUAS) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_41);
    } else {
        RCP_SetupDL_14();
    }

    for (i = 0; i < ARRAY_COUNT(gTexturedLines); i++) {
        TexturedLine* texLine = &gTexturedLines[i];
        FrameInterpolation_RecordOpenChild(texLine, i);
        FrameInterpolation_RecordMarker(__FILE__, __LINE__);

        if (gTexturedLines[i].mode != 0) {
            Matrix_Push(&gGfxMatrix);
            Matrix_Translate(gGfxMatrix, texLine->posAA.x, texLine->posAA.y, texLine->posAA.z + gPathProgress,
                             MTXF_APPLY);
            Matrix_RotateY(gGfxMatrix, texLine->yRot, MTXF_APPLY);
            Matrix_RotateX(gGfxMatrix, texLine->xRot, MTXF_APPLY);
            Matrix_RotateZ(gGfxMatrix, texLine->yRot, MTXF_APPLY);
            Matrix_Scale(gGfxMatrix, texLine->xyScale, texLine->xyScale, texLine->zScale, MTXF_APPLY);

            if ((gCurrentLevel == LEVEL_AQUAS) || (gCurrentLevel == LEVEL_VENOM_ANDROSS)) {
                s32 alpha = ((gGameFrameCount % 2) != 0) ? 180 : 50;

                gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, alpha);
                if (gCurrentLevel == LEVEL_AQUAS) {
                    Matrix_Scale(gGfxMatrix, 0.01f, 0.3f, 0.0025f, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -200.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 5.0f * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_AQ_60119A0);
                } else if (gCurrentLevel == LEVEL_VENOM_ANDROSS) {
                    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 0.0025f, MTXF_APPLY);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -200.0f, MTXF_APPLY);
                    Matrix_RotateZ(gGfxMatrix, gGameFrameCount * 25.0f * M_DTOR, MTXF_APPLY);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_ANDROSS_C017440);
                }
            } else {
                Matrix_SetGfxMtx(&gMasterDisp);
                if (gCurrentLevel == LEVEL_MACBETH) {
                    gSPDisplayList(gMasterDisp++, D_MA_6012C00);
                } else {
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, texLine->prim.r, texLine->prim.g, texLine->prim.b,
                                    texLine->prim.a);
                    gSPDisplayList(gMasterDisp++, D_edisplay_800CFD80);
                }
            }
            Matrix_Pop(&gGfxMatrix);
        }
        FrameInterpolation_RecordCloseChild();
    }
}

void TexturedLine_DrawPath(s32 index) {
    TexturedLine* texLine = &gTexturedLines[index];

    if (texLine->prim.a == 255) {
        RCP_SetupDL(&gMasterDisp, SETUPDL_5);
    } else {
        RCP_SetupDL(&gMasterDisp, SETUPDL_14);
    }

    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, texLine->prim.r, texLine->prim.g, texLine->prim.b, texLine->prim.a);

    Matrix_Push(&gGfxMatrix);
    Matrix_Translate(gGfxMatrix, texLine->posAA.x, texLine->posAA.y, texLine->posAA.z, MTXF_APPLY);
    Matrix_RotateY(gGfxMatrix, texLine->yRot, MTXF_APPLY);
    Matrix_RotateX(gGfxMatrix, texLine->xRot, MTXF_APPLY);
    Matrix_RotateZ(gGfxMatrix, texLine->xRot, MTXF_APPLY);
    Matrix_Scale(gGfxMatrix, texLine->xyScale, 1.0f, texLine->zScale, MTXF_APPLY);
    Matrix_SetGfxMtx(&gMasterDisp);

    gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
    gSPDisplayList(gMasterDisp++, D_edisplay_800CFD80);
    gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);

    Matrix_Pop(&gGfxMatrix);
}
