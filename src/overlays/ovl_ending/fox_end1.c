#include "global.h"
#include "assets/ast_title.h"
#include "assets/ast_ending_award_front.h"
#include "assets/ast_ending_award_back.h"
#include "assets/ast_allies.h"
#include "assets/ast_great_fox.h"
#include "assets/ast_ending.h"

void Ending_8018CE20(s32);
void Ending_801926D4(void);
extern u32 D_ending_80192E70;

bool Ending_80189C64(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data);
void Ending_8018ABE8(void);
void Ending_8018B3D8(void);
bool Ending_8018BCB0(void);
void Ending_8018C21C(void);

typedef struct {
    Animation* anim;
    Limb** skeleton;
    s16 setupDL;
    Vec3f pos;
    Vec3f rot;
    Vec3f scale;
    f32 unk_30;
    s32 unk_34;
    s32 unk_38;
    struct {
        u8 r, g, b, a;
    } prim;
} UnkStruct_196D08;

s32 D_ending_80196D00;
s32 D_ending_80196D04;
UnkStruct_196D08 D_ending_80196D08[10];
s32 D_ending_80196F88;
u32 D_ending_80196F8C;
s32 D_ending_80196F90;
s32 D_ending_80196F94;
s32 D_ending_80196F98;
f32 D_ending_80196F9C;
Vec3f D_ending_80196FA0[4][50];
Vec3f D_ending_80197900[4][50];
s32 D_ending_80198260[4][50];
f32 D_ending_80198580;
bool D_ending_80198584;
s32 D_ending_80198588;
s32 D_ending_8019858C;

const char str1[] = "fogR= %d, fogG= %d, fogB= %d\n";
const char str2[] = "ligR= %d, ligG= %d, ligB= %d\n";
const char str3[] = "kanR= %d, kanG= %d, kanB= %d\n";
const char str4[] = "ligX= %f, ligY= %f, ligZ= %f\n";
const char str5[] = "ligXp=%d, ligYp=%d, ligZp=%d\n\n";
const char str6[] = "fogS1= %d, fogS2= %d\n";
const char str7[] = "eyeX= %f, eyeY= %f, eyeZ= %f\n";
const char str8[] = "wayX= %f, wayY= %f, wayZ= %f\n";
const char str9[] = "[G-Fox-> %d]\n";
const char str10[] = "xp= %f, yp= %f, zp= %f\n";
const char str11[] = "xa= %f, ya= %f, za= %f\n";
const char str12[] = "sz= %f\n";
const char str13[] = "[Bill--> %d]\n";
const char str14[] = "xp= %f, yp= %f, zp= %f\n";
const char str15[] = "xa= %f, ya= %f, za= %f\n";
const char str16[] = "sz= %f\n";
const char str17[] = "[Base--> %d]\n";
const char str18[] = "xp= %f, yp= %f, zp= %f\n";
const char str19[] = "xa= %f, ya= %f, za= %f\n";
const char str20[] = "sz= %f\n";
const char str21[] = "[Ship--> %d]\n";
const char str22[] = "xp= %f, yp= %f, zp= %f\n";
const char str23[] = "xa= %f, ya= %f, za= %f\n";
const char str24[] = "sz= %f\n";

void Ending_80187520(s32 arg0) {
    s32 i;
    s32 j;

    RCP_SetupDL(&gMasterDisp, 0x4C);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

    switch (arg0) {
        case 0:
            for (j = 0, i = 0; i < 67; j += 316 * 4, i++) {
                TextureRect_16bRGBA(&gMasterDisp, gEndingAwardBack + j, 316, 4, 0.0f, 4 * i, 1.0f, 1.0f);
            }
            TextureRect_16bRGBA(&gMasterDisp, gEndingAwardBack + j, 316, 3, 0.0f, 4 * i, 1.0f, 1.0f);
            break;

        case 1:
            for (j = 0, i = 0; i < 60; j += 316 * 4, i++) {
                TextureRect_16bRGBA(&gMasterDisp, gEndingAwardFront + j, 316, 4, 0.0f, 4 * i, 1.0f, 1.0f);
            }
            break;
    }
}

void Ending_801876A4(void) {
    s32 i;

    for (i = 0; i < 4; i++) {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, 0x3E);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 240);
        Matrix_Translate(gGfxMatrix, D_ending_80196D08[i].pos.x, D_ending_80196D08[i].pos.y, D_ending_80196D08[i].pos.z,
                         1);
        Matrix_Scale(gGfxMatrix, D_ending_80196D08[i].scale.x + 4.0f, D_ending_80196D08[i].scale.y + 4.0f,
                     D_ending_80196D08[i].scale.z + 4.0f, 1);
        Matrix_RotateY(gGfxMatrix, D_ending_80196D08[i].rot.y * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, (D_ending_80196D08[i].rot.x + 5.0f) * M_DTOR, 1);
        Matrix_RotateZ(gGfxMatrix, D_ending_80196D08[i].rot.z * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_TITLE_6041070);
        Matrix_Pop(&gGfxMatrix);
    }
}

#ifdef NON_MATCHING
// regswaps before the matrix translates https://decomp.me/scratch/nweXT
void Ending_80187860(s32 arg0, s32 arg1) {
    Vec3f sp88[50];
    s32 i;
    s32 sp80;
    Animation* sp70[4] = { &D_TITLE_60246F8, &D_TITLE_60338DC, &D_TITLE_6036278, &D_TITLE_603531C };

    for (i = arg0; i < D_ending_80196F88; i++) {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, D_ending_80196D08[i].setupDL);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_ending_80196D08[i].prim.r, D_ending_80196D08[i].prim.g,
                        D_ending_80196D08[i].prim.b, D_ending_80196D08[i].prim.a);
        if ((i == 1) || (i == 2)) {
            Matrix_Translate(gGfxMatrix, D_ending_80196D08[i].pos.x, D_ending_80196D08[i].pos.y - 10.0f,
                             D_ending_80196D08[i].pos.z, 1);
        } else {
            Matrix_Translate(gGfxMatrix, D_ending_80196D08[i].pos.x, D_ending_80196D08[i].pos.y,
                             D_ending_80196D08[i].pos.z, 1);
        }
        Matrix_Scale(gGfxMatrix, D_ending_80196D08[i].scale.x, D_ending_80196D08[i].scale.y,
                     D_ending_80196D08[i].scale.z, 1);
        Matrix_RotateY(gGfxMatrix, D_ending_80196D08[i].rot.y * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, D_ending_80196D08[i].rot.x * M_DTOR, 1);
        Matrix_RotateZ(gGfxMatrix, D_ending_80196D08[i].rot.z * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        if ((arg1 != 0) && (gCsFrameCount >= 394)) {
            switch (i) {
                case 0:
                    sp80 = Animation_GetFrameData(&D_TITLE_60246F8, 0, sp88);
                    break;
                case 1:
                    sp80 = Animation_GetFrameData(&D_TITLE_60338DC, 0, sp88);
                    break;
                case 2:
                    sp80 = Animation_GetFrameData(&D_TITLE_6036278, 0, sp88);
                    break;
                case 3:
                    sp80 = Animation_GetFrameData(&D_TITLE_603531C, 0, sp88);
                    break;
            }
            Math_SmoothStepToVec3fArray(sp88, D_ending_80197900[i], 1, sp80, 0.1f, 100.0f, 0.01f);
        } else {
            Animation_GetFrameData(D_ending_80196D08[i].anim,
                                   (u32) (D_ending_80196D08[i].unk_34 * D_ending_80196D08[i].unk_30) %
                                       Animation_GetFrameCount(D_ending_80196D08[i].anim),
                                   D_ending_80197900[i]);
        }
        Animation_DrawSkeleton(0, D_ending_80196D08[i].skeleton, D_ending_80197900[i], Ending_80189C64, NULL, &i,
                               &gIdentityMatrix);
        Matrix_Pop(&gGfxMatrix);
    }
}
#else
Animation* D_ending_80192820[4] = { &D_TITLE_60246F8, &D_TITLE_60338DC, &D_TITLE_6036278, &D_TITLE_603531C };
void Ending_80187860(s32, s32);
#pragma GLOBAL_ASM("asm/us/nonmatchings/overlays/ovl_ending/fox_end1/Ending_80187860.s")
#endif

void Ending_80187D3C(s32 arg0) {
    s32 i;
    s32 j;
    Vec3f sp23C = { 0.0f, 0.0f, 0.0f };
    UnkStruct_196D08 sp13C[4] = {
        { &D_TITLE_602A710,
          D_TITLE_602FBAC,
          23,
          { 110.0f, -520.0f, -1390.0f },
          { -20.0f, 0.0f, 0.0f },
          { 1.37f, 1.37f, 1.37f },
          1.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_601E424,
          D_TITLE_603088C,
          23,
          { 380.0f, -670.0f, -1840.0f },
          { -20.0f, 0.0f, 0.0f },
          { 1.37f, 1.37f, 1.37f },
          1.0f,
          30,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_6020058,
          D_TITLE_60313AC,
          23,
          { -100.0f, -590.0f, -1630.0f },
          { -20.0f, 0.0f, 0.0f },
          { 1.37f, 1.37f, 1.37f },
          1.0f,
          20,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_6029BE4,
          D_TITLE_6032084,
          23,
          { -330.0f, -660.0f, -1840.0f },
          { -20.0f, 0.0f, 0.0f },
          { 1.37f, 1.37f, 1.37f },
          1.0f,
          10,
          0,
          { 0, 0, 0, 0 } },
    };
    UnkStruct_196D08 sp3C[4] = {
        { &D_TITLE_602A710,
          D_TITLE_602FBAC,
          23,
          { -80.0f, -400.0f, -50.0f },
          { 0.0f, 180.0f, 0.0f },
          { 0.86f, 0.86f, 0.86f },
          1.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_601E424,
          D_TITLE_603088C,
          23,
          { -160.0f, -400.0f, 350.0f },
          { 0.0f, 180.0f, 0.0f },
          { 0.86f, 0.86f, 0.86f },
          1.0f,
          30,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_6020058,
          D_TITLE_60313AC,
          23,
          { 60.0f, -400.0f, 150.0f },
          { 0.0f, 180.0f, 0.0f },
          { 0.86f, 0.86f, 0.86f },
          1.0f,
          20,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_6029BE4,
          D_TITLE_6032084,
          23,
          { 160.0f, -400.0f, 350.0f },
          { 350.0f, 180.0f, 0.0f },
          { 0.86f, 0.86f, 0.86f },
          1.0f,
          10,
          0,
          { 0, 0, 0, 0 } },
    };

    D_ending_80196F88 = 4;

    switch (arg0) {
        case 0:
            for (i = 0; i < D_ending_80196F88; i++) {
                D_ending_80196D08[i] = sp13C[i];
            }
            D_ending_80196F9C = 0.004f;
            break;
        case 1:
            for (i = 0; i < D_ending_80196F88; i++) {
                D_ending_80196D08[i] = sp3C[i];
            }
            D_ending_80196F9C = 0.003f;
            break;
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 50; j++) {
            D_ending_80198260[i][j] = 0;
            D_ending_80196FA0[i][j] = sp23C;
        }
    }
}

void Ending_80188030(s32 arg0) {
    s32 i;
    f32 sp30;
    f32 sp2C;

    switch (arg0) {
        case 0:
            sp2C = D_ending_80196F9C * fabsf(-900.0f);
            sp2C *= -1.0f;
            sp30 = D_ending_80196F9C * fabsf(-320.0f);
            break;
        case 1:
            sp2C = fabsf(1970.0f) * D_ending_80196F9C;
            sp30 = 0.0f;
            break;
    }

    if ((arg0 == 1) && (gCsFrameCount >= 394)) {
        Math_SmoothStepToF(&D_ending_80196F9C, 0.0f, 0.1f, 1.0f, 0.0001f);
    }

    for (i = 0; i < D_ending_80196F88; i++) {
        D_ending_80196D08[i].pos.z -= sp2C;
        D_ending_80196D08[i].pos.y += sp30;
        if ((arg0 != 1) || (gCsFrameCount < 394)) {
            D_ending_80196D08[i].unk_34 += 1;
        }
    }

    if (((gCsFrameCount >= 150) && (gCsFrameCount < 171)) || ((gCsFrameCount >= 280) && (gCsFrameCount <= 300)) ||
        ((gCsFrameCount >= 340) && (gCsFrameCount < 361))) {
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].x, 40.0f, 0.2f, 1000.0f, 0.1f);
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, 10.0f, 0.2f, 1000.0f, 0.1f);
        Math_SmoothStepToF(&D_ending_80196FA0[2][6].y, 0.0f, 0.2f, 1000.0f, 0.1f);
    } else if ((arg0 == 1) && (gCsFrameCount >= 200) && (gCsFrameCount < 261)) {
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].x, 60.0f, 0.1f, 1000.0f, 0.1f);
    } else if (((arg0 == 1) && (gCsFrameCount >= 170) && (gCsFrameCount < 191)) ||
               ((gCsFrameCount >= 300) && (gCsFrameCount < 321))) {
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].x, -40.0f, 0.2f, 1000.0f, 0.1f);
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, 10.0f, 0.2f, 1000.0f, 0.1f);
        Math_SmoothStepToF(&D_ending_80196FA0[2][6].y, 0.0f, 0.2f, 1000.0f, 0.1f);
    } else {
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].x, 0.0f, 0.2f, 1000.0f, 0.1f);
        Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, 0.0f, 0.2f, 1000.0f, 0.1f);
        Math_SmoothStepToF(&D_ending_80196FA0[2][6].y, 0.0f, 0.2f, 1000.0f, 0.1f);
    }
}

s32 Ending_80188394(void) {
    s32 i;
    UnkStruct_196D08 sp14[2] = {
        { (void*) D_END_70143C0,
          NULL,
          17,
          { 0.0f, -3830.0f, -7000.0f },
          { 0.0f, 0.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          1.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_END_7018708,
          D_END_70187B4,
          23,
          { 0.0f, -310.0f, -370.0f },
          { 0.0f, 0.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          4.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
    };

    for (D_ending_80196F88 = 2, i = 0; i < D_ending_80196F88; i++) {
        D_ending_80196D08[i] = sp14[i];
    }
}

#ifdef NON_MATCHING
// stupid loop thing https://decomp.me/scratch/cyOva
void Ending_8018845C(void) {
    s32 var_a2;
    u32 temp_a3;

    for (var_a2 = 0; var_a2 < 2; var_a2++) {
        if (var_a2 != D_ending_8019858C) {}
    }

    D_ctx_80178300 = 1;

    switch (gCsFrameCount) {
        case 10:
            Radio_PlayMessage(gMsg_ID_21010, RCID_GEN_PEPPER_TITLE);
            break;
        case 110:
            Radio_PlayMessage(gMsg_ID_21020, RCID_GEN_PEPPER_TITLE);
            break;
    }

    temp_a3 = (u32) (D_ending_80196D08[1].unk_34 * D_ending_80196D08[var_a2].unk_30) %
              Animation_GetFrameCount(D_ending_80196D08[1].anim);

    if (((gCsFrameCount >= 20) && (gCsFrameCount < 31)) || ((gCsFrameCount >= 50) && (gCsFrameCount < 71)) ||
        ((gCsFrameCount >= 110) && (gCsFrameCount < 141)) || ((gCsFrameCount >= 160) && (gCsFrameCount < 191))) {
        D_ending_80196D08[1].unk_34++;
    } else if (temp_a3 != 0) {
        D_ending_80196D08[1].unk_34++;
    }
}
#else
void Ending_8018845C(void);
#pragma GLOBAL_ASM("asm/us/nonmatchings/overlays/ovl_ending/fox_end1/Ending_8018845C.s")
#endif

s32 Ending_80188634(void) {
    if (gCallTimer != 0) {
        if ((D_ending_80196F90 % 14) == 0) {
            AUDIO_PLAY_SFX(0x49002018, gDefaultSfxSource, 4);
        }
        D_ending_80196F90++;
        gCallTimer--;
        if (gCallTimer == 0) {
            Audio_KillSfxById(0x49002018);
        }
    } else {
        D_ending_80196F90 = 0;
    }
    return 0;
}

void Ending_801886F4(void) {
    f32 temp = 142.0f;

    if (gCallTimer == 0) {
        return;
    }

    RCP_SetupDL(&gMasterDisp, 0x4E);
    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 255);

    switch ((D_ending_80196F90 % 8) / 2) {
        case 3:
            TextureRect_4bCI(&gMasterDisp, D_END_70110E0, D_END_70111B0, 16, 26, temp + 31.0f, 18.0f, 1.0f, 1.0f);
            /* fallthrough */
        case 2:
            TextureRect_4bCI(&gMasterDisp, D_END_7010FF0, D_END_70110C0, 16, 26, temp + 24.0f, 18.0f, 1.0f, 1.0f);
            /* fallthrough */
        case 1:
            TextureRect_4bCI(&gMasterDisp, D_END_7010F00, D_END_7010FD0, 16, 26, temp + 18.0f, 18.0f, 1.0f, 1.0f);
            /* fallthrough */
        case 0:
            TextureRect_4bCI(&gMasterDisp, D_END_7010E10, D_END_7010EE0, 16, 26, temp, 18.0f, 1.0f, 1.0f);
    }
}

void Ending_801888F4(void) {
    s32 sp29C = 4;
    s32 temp_s0_5;
    s32 sp294;
    Vec3f sp3C[50];

    Matrix_Push(&gGfxMatrix);
    RCP_SetupDL(&gMasterDisp, D_ending_80196D08[sp29C].setupDL);
    Matrix_Translate(gGfxMatrix, D_ending_80196D08[sp29C].pos.x, D_ending_80196D08[sp29C].pos.y,
                     D_ending_80196D08[sp29C].pos.z, 1);
    Matrix_Scale(gGfxMatrix, D_ending_80196D08[sp29C].scale.x, D_ending_80196D08[sp29C].scale.y,
                 D_ending_80196D08[sp29C].scale.z, 1);
    Matrix_RotateY(gGfxMatrix, D_ending_80196D08[sp29C].rot.y * M_DTOR, 1);
    Matrix_RotateX(gGfxMatrix, D_ending_80196D08[sp29C].rot.x * M_DTOR, 1);
    Matrix_SetGfxMtx(&gMasterDisp);

    switch (D_ending_80196D08[sp29C].unk_38) {
        case 0:
            sp294 = (u32) (D_ending_80196D08[sp29C].unk_34 * D_ending_80196D08[sp29C].unk_30) %
                    Animation_GetFrameCount(D_ending_80196D08[sp29C].anim);
            Animation_GetFrameData(D_ending_80196D08[sp29C].anim, sp294, D_ending_80197900[0]);
            break;

        case 1:
            sp294 = D_ending_80196D08[sp29C].unk_34 * D_ending_80196D08[sp29C].unk_30;
            if (sp294 >= Animation_GetFrameCount(&D_TITLE_601F8E0)) {
                sp294 = Animation_GetFrameCount(&D_TITLE_601F8E0) - 1;
            }
            Math_SmoothStepToVec3fArray(sp3C, D_ending_80197900[0], 1,
                                        Animation_GetFrameData(&D_TITLE_601F8E0, sp294, sp3C), 0.2f, 100.0f, 0.01f);
            break;

        case 2:
            sp294 = (u32) (D_ending_80196D08[sp29C].unk_34 * D_ending_80196D08[sp29C].unk_30) %
                    Animation_GetFrameCount(D_ending_80196D08[sp29C].anim);
            temp_s0_5 = Animation_GetFrameData(&D_TITLE_60246F8, sp294, sp3C);
            Math_SmoothStepToF(&D_ending_80198580, 1.0f, 0.01f, 1.0f, 0.05f);
            Math_SmoothStepToVec3fArray(sp3C, D_ending_80197900[0], 1, temp_s0_5, D_ending_80198580, 100.0f, 0.01f);
            break;
    }

    Animation_DrawSkeleton(0, D_ending_80196D08[sp29C].skeleton, D_ending_80197900[0], Ending_80189C64, NULL, &sp29C,
                           &gIdentityMatrix);
    Matrix_Pop(&gGfxMatrix);
}

void Ending_80188DB4(void) {
    s32 i;
    s32 j;
    Vec3f sp1B4 = { 0.0f, 0.0f, 0.0f };
    UnkStruct_196D08 sp74[5] = {
        { (void*) D_END_70111D0,
          NULL,
          17,
          { 0.0f, -2960.0f, -6600.0f },
          { 0.0f, 0.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          1.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_60338DC,
          D_TITLE_603088C,
          23,
          { 230.0f, -370.0f, -620.0f },
          { 350.0f, 0.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          2.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_6036278,
          D_TITLE_60313AC,
          23,
          { -120.0f, -350.0f, -600.0f },
          { 350.0f, 10.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          2.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_603531C,
          D_TITLE_6032084,
          23,
          { -260.0f, -350.0f, -710.0f },
          { 350.0f, 10.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          2.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
        { &D_TITLE_60246F8,
          D_TITLE_602FBAC,
          23,
          { 30.0f, -330.0f, -320.0f },
          { 350.0f, 0.0f, 0.0f },
          { 1.0f, 1.0f, 1.0f },
          2.0f,
          0,
          0,
          { 0, 0, 0, 0 } },
    };

    for (D_ending_80196F88 = 5, i = 0; i < D_ending_80196F88; i++) {
        D_ending_80196D08[i] = sp74[i];
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 50; j++) {
            D_ending_80197900[i][j] = sp1B4;
            D_ending_80198260[i][j] = 0;
            D_ending_80196FA0[i][j] = sp1B4;
        }
    }

    gCallTimer = 0;
    D_ending_80196F94 = 0;
    D_ending_80196F98 = 0;
    D_ending_80198580 = 0.0f;
    D_ending_80196F88 = 4;
}

void Ending_80189108(void) {
    u32 temp_a0;

    switch (D_ending_80196D08[4].unk_38) {
        case 0:
            D_ctx_80178300 = 1;
            switch (gCsFrameCount) {
                case 30:
                    Radio_PlayMessage(gMsg_ID_21030, RCID_FOX);
                    break;
                case 60:
                    D_ending_80196F94 = 20;
                    break;
                case 100:
                    D_ending_80196F94 = 20;
                    break;
                case 120:
                    D_ending_80196F98 = 30;
                    break;
                case 130:
                    D_ending_80196F94 = 20;
                    break;
                case 170:
                    D_ending_80196F94 = 20;
                    break;
            }

            if ((D_ending_80196D08[4].unk_38 == 0) && (gCsFrameCount == 180)) {
                gCallTimer = 120;
                gRadioState = 0;
            }

            if (Ending_80188634() || (gCsFrameCount == 230)) {
                D_ending_80196D08[4].unk_34 = 0;
                D_ending_80196D08[4].unk_38 = 1;
                gCsFrameCount = 0;
                Audio_KillSfxById(0x49002018);
                D_ending_80196F90 = 0;
                gCallTimer = 0;
            }

            temp_a0 = (u32) (D_ending_80196D08[4].unk_34 * D_ending_80196D08[4].unk_30) %
                      Animation_GetFrameCount(D_ending_80196D08[4].anim);

            if (((gCsFrameCount >= 30) && (gCsFrameCount < 41)) || ((gCsFrameCount >= 60) && (gCsFrameCount < 111))) {
                D_ending_80196D08[4].unk_34 += 1;
            } else if (temp_a0 != 0) {
                D_ending_80196D08[4].unk_34 += 1;
            }
            break;

        case 1:
            D_ctx_80178300 = 0;
            if (gCsFrameCount == 20) {
                Radio_PlayMessage(gMsg_ID_21050, RCID_ROB64_TITLE);
            }
            if (gCsFrameCount == 130) {
                D_ending_80196D08[4].unk_34 = 0;
                D_ending_80196D08[4].unk_38 = 2;
                gCsFrameCount = 0;
            }
            D_ending_80196D08[4].unk_34++;
            break;

        case 2:
            D_ctx_80178300 = 1;
            switch (gCsFrameCount) {
                case 20:
                    Radio_PlayMessage(gMsg_ID_21060, RCID_FOX);
                    break;
                case 80:
                    gFillScreenAlphaTarget = 255;
                    break;
            }

            temp_a0 = (u32) (D_ending_80196D08[4].unk_34 * D_ending_80196D08[4].unk_30) %
                      Animation_GetFrameCount(D_ending_80196D08[4].anim);

            if ((gCsFrameCount >= 20) && (gCsFrameCount < 51)) {
                D_ending_80196D08[4].unk_34 += 1;
            } else if (temp_a0 != 0) {
                D_ending_80196D08[4].unk_34 += 1;
            }
            break;
    }

    if (D_ending_80196F94 != 0) {
        D_ending_80196F94--;
    }
    if (D_ending_80196F98 != 0) {
        D_ending_80196F98--;
    }

    if ((gCallTimer == 0) && (D_ending_80196F94 != 0)) {
        if (D_ending_80198260[1][1] == 0) {
            D_ending_80196FA0[1][1].x -= 2.4f;
            D_ending_80196FA0[1][1].z -= 12.0f;
            if (D_ending_80196FA0[1][1].x <= -6.0f) {
                D_ending_80198260[1][1] = 1;
            }
        } else {
            D_ending_80196FA0[1][1].x += 2.4f;
            D_ending_80196FA0[1][1].z += 12.0f;
            if (D_ending_80196FA0[1][1].x >= 0.0f) {
                D_ending_80198260[1][1] = 0;
            }
        }
    }

    if ((gCallTimer == 0) && (D_ending_80196F98 != 0)) {
        if (D_ending_80198260[2][0] == 0) {
            Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, -10.0f, 0.4f, 100.0f, 0.1f);
            if (D_ending_80196FA0[2][0].y <= -10.0f) {
                D_ending_80198260[2][0] = 1;
            }
        } else {
            Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, 10.0f, 0.4f, 100.0f, 0.1f);
            if (D_ending_80196FA0[2][0].y >= 10.0f) {
                D_ending_80198260[2][0] = 0;
            }
        }
        D_ending_80196D08[3].unk_34 += 2;
    }

    if ((D_ending_80196F98 == 0) && (D_ending_80196D08[4].unk_38 != 2)) {
        temp_a0 = (u32) (D_ending_80196D08[3].unk_34 * D_ending_80196D08[3].unk_30) %
                  Animation_GetFrameCount(D_ending_80196D08[3].anim);
        if (temp_a0 != 0) {
            D_ending_80196D08[3].unk_34 += 2;
        }
    }

    if (D_ending_80196D08[4].unk_38 != 2) {
        if ((gCallTimer != 0) && (gCallTimer < 121)) {
            Math_SmoothStepToF(&D_ending_80196FA0[1][0].x, -50.0f, 0.2f, 1000.0f, 0.01f);
            Math_SmoothStepToF(&D_ending_80196FA0[1][0].z, 18.0f, 0.2f, 1000.0f, 0.01f);
        }
        if ((gCallTimer != 0) && (gCallTimer < 116)) {
            Math_SmoothStepToF(&D_ending_80196FA0[3][0].x, 20.0f, 0.2f, 1000.0f, 0.01f);
        }
        if ((gCallTimer != 0) && (gCallTimer < 111)) {
            Math_SmoothStepToF(&D_ending_80196FA0[2][0].x, 20.0f, 0.2f, 1000.0f, 0.01f);
            Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, 20.0f, 0.2f, 1000.0f, 0.01f);
        }
        if ((D_ending_80196F94 == 0) && (gCallTimer == 0)) {
            Math_SmoothStepToF(&D_ending_80196FA0[1][0].x, 0.0f, 0.2f, 1000.0f, 0.01f);
            Math_SmoothStepToF(&D_ending_80196FA0[1][0].z, 0.0f, 0.2f, 1000.0f, 0.01f);
        }
        if ((D_ending_80196F98 == 0) && (gCallTimer == 0)) {
            Math_SmoothStepToF(&D_ending_80196FA0[3][0].x, 0.0f, 0.2f, 1000.0f, 0.01f);
            Math_SmoothStepToF(&D_ending_80196FA0[2][0].x, 0.0f, 0.2f, 1000.0f, 0.01f);
            Math_SmoothStepToF(&D_ending_80196FA0[2][0].y, 0.0f, 0.2f, 1000.0f, 0.01f);
        }
    }

    D_ending_80196FA0[2][2].z = -6.0f;
    D_ending_80196FA0[2][0].z = 6.0f;

    if ((D_ending_80196D08[4].unk_38 == 2) && (gCsFrameCount >= 60)) {
        Math_SmoothStepToF(&D_ending_80196FA0[1][0].x, -40.0f, 0.2f, 1000.0f, 0.01f);
        Math_SmoothStepToF(&D_ending_80196FA0[1][0].z, 18.0f, 0.2f, 1000.0f, 0.01f);
        Math_SmoothStepToF(&D_ending_80196FA0[1][5].x, -12.0f, 0.2f, 1000.0f, 0.01f);
        Math_SmoothStepToF(&D_ending_80196FA0[1][5].z, -6.0f, 0.2f, 1000.0f, 0.01f);
        if (gCsFrameCount < 91) {
            D_ending_80196D08[3].unk_34 += 2;
        } else {
            temp_a0 = ((u32) (D_ending_80196D08[3].unk_34 * D_ending_80196D08[3].unk_30) %
                       Animation_GetFrameCount(D_ending_80196D08[3].anim));
            if (temp_a0 != 0) {
                D_ending_80196D08[3].unk_34 += 2;
            }
        }
        Math_SmoothStepToF(&D_ending_80196FA0[3][0].x, 0.0f, 0.2f, 1000.0f, 0.01f);
    }
}

bool Ending_80189C64(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* data) {
    s32 temp_v0 = *(s32*) data;

    if (temp_v0 == 3) {
        gSPSetGeometryMode(gMasterDisp++, G_CULL_BACK);
    }

    switch (limbIndex) {
        case 1:
            if (temp_v0 == 2) {
                rot->x += D_ending_80196FA0[temp_v0][2].x;
                rot->y += D_ending_80196FA0[temp_v0][2].y;
                rot->z += D_ending_80196FA0[temp_v0][2].z;
            }
            break;

        case 2:
            if (temp_v0 == 1) {
                rot->x += D_ending_80196FA0[temp_v0][1].x;
                rot->y += D_ending_80196FA0[temp_v0][1].y;
                rot->z += D_ending_80196FA0[temp_v0][1].z;
            }
            break;

        case 6:
            if (temp_v0 == 2) {
                rot->x += D_ending_80196FA0[temp_v0][3].x;
                rot->y += D_ending_80196FA0[temp_v0][3].y;
                rot->z += D_ending_80196FA0[temp_v0][3].z;
            }
            break;

        case 9:
            if (temp_v0 == 2) {
                rot->x += D_ending_80196FA0[temp_v0][4].x;
                rot->y += D_ending_80196FA0[temp_v0][4].y;
                rot->z += D_ending_80196FA0[temp_v0][4].z;
            }
            break;

        case 17:
            if (temp_v0 == 2) {
                rot->x += D_ending_80196FA0[temp_v0][0].x;
                rot->y += D_ending_80196FA0[temp_v0][0].y;
                rot->z += D_ending_80196FA0[temp_v0][0].z;
            }
            break;

        case 19:
            if ((temp_v0 == 1) || (temp_v0 == 3) || (temp_v0 == 0)) {
                rot->x += D_ending_80196FA0[temp_v0][0].x;
                rot->y += D_ending_80196FA0[temp_v0][0].y;
                rot->z += D_ending_80196FA0[temp_v0][0].z;
            }
            if (temp_v0 == 2) {
                rot->x += D_ending_80196FA0[temp_v0][6].x;
                rot->y += D_ending_80196FA0[temp_v0][6].y;
                rot->z += D_ending_80196FA0[temp_v0][6].z;
            }
            break;

        case 20:
            if (temp_v0 == 3) {
                gSPClearGeometryMode(gMasterDisp++, G_CULL_BACK);
            }
            if (temp_v0 == 1) {
                rot->x += D_ending_80196FA0[temp_v0][5].x;
                rot->y += D_ending_80196FA0[temp_v0][5].y;
                rot->z += D_ending_80196FA0[temp_v0][5].z;
            }
            break;
    }
    return false;
}

void Ending_8018A024(void) {
    Vec3f src;
    Vec3f dest;

    src.x = src.y = 0.0f;
    src.z = -100.0f;
    Matrix_RotateX(gCalcMatrix, D_ctx_801784D0 * M_DTOR, 0);
    Matrix_RotateY(gCalcMatrix, D_ctx_801784D4 * M_DTOR, 1);
    Matrix_RotateZ(gCalcMatrix, D_ctx_801784D8 * M_DTOR, 1);
    Matrix_MultVec3fNoTranslate(gCalcMatrix, &src, &dest);
    gLight1x = dest.x;
    gLight1y = dest.y;
    gLight1z = dest.z;
}

void Ending_8018A124(s32 arg0) {
    f32 sp2C[3] = { 0.0f, 0.0f, 0.0f };
    f32 sp20[3] = { 0.0f, 0.0f, -100.0f };
    s32 sp14[3] = { 110, 80, 40 };
    s32 sp8[3] = { 0, 0, 0 };
    f32 sp0[2] = { -22.0f, 204.0f };

    // not fake, but weird.
    gCsCamEyeX = (&sp2C)[arg0][0];
    gCsCamEyeY = (&sp2C)[arg0][1];
    gCsCamEyeZ = (&sp2C)[arg0][2];
    gCsCamAtX = (&sp20)[arg0][0];
    gCsCamAtY = (&sp20)[arg0][1];
    gCsCamAtZ = (&sp20)[arg0][2];

    gLight1R = (&sp14)[arg0][0];
    gLight1G = (&sp14)[arg0][1];
    gLight1B = (&sp14)[arg0][2];

    gAmbientR = (&sp8)[arg0][0];
    gAmbientG = (&sp8)[arg0][1];
    gAmbientB = (&sp8)[arg0][2];

    D_ctx_801784D0 = (&sp0)[arg0][0];
    D_ctx_801784D4 = (&sp0)[arg0][1];
}

void Ending_8018A2A8(void) {
    s32 i;
    Vec3f sp6C[50];

    for (i = 0; i < D_ending_80196F88; i++) {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, D_ending_80196D08[i].setupDL);
        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, D_ending_80196D08[i].prim.r, D_ending_80196D08[i].prim.g,
                        D_ending_80196D08[i].prim.b, D_ending_80196D08[i].prim.a);
        Matrix_Translate(gGfxMatrix, D_ending_80196D08[i].pos.x, D_ending_80196D08[i].pos.y, D_ending_80196D08[i].pos.z,
                         1);
        Matrix_Scale(gGfxMatrix, D_ending_80196D08[i].scale.x, D_ending_80196D08[i].scale.y,
                     D_ending_80196D08[i].scale.z, 1);
        Matrix_RotateY(gGfxMatrix, D_ending_80196D08[i].rot.y * M_DTOR, 1);
        Matrix_RotateX(gGfxMatrix, D_ending_80196D08[i].rot.x * M_DTOR, 1);
        Matrix_RotateZ(gGfxMatrix, D_ending_80196D08[i].rot.z * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);

        if (D_ending_80196D08[i].skeleton == NULL) {
            gSPDisplayList(gMasterDisp++, D_ending_80196D08[i].anim);
        } else {
            Animation_GetFrameData(D_ending_80196D08[i].anim,
                                   (u32) (D_ending_80196D08[i].unk_34 * D_ending_80196D08[i].unk_30) %
                                       Animation_GetFrameCount(D_ending_80196D08[i].anim),
                                   sp6C);
            Animation_DrawSkeleton(0, D_ending_80196D08[i].skeleton, sp6C, NULL, NULL, NULL, &gIdentityMatrix);
        }
        Matrix_Pop(&gGfxMatrix);
    }
}

void Ending_8018A570(void) {
    Ending_8018A024();

    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);

    switch (D_ending_80196F8C) {
        case 2:
            if (gCsFrameCount == 200) {
                D_ending_80196F8C = 3;
            }
            break;

        case 4:
            if (gCsFrameCount == 435) {
                D_ending_80196F8C = 5;
            }
            break;

        case 6:
            if (gCsFrameCount == 180) {
                D_ending_80196F8C = 7;
            }
            break;

        case 8:
            if ((D_ending_80196D08[4].unk_38 == 2) && (gCsFrameCount >= 108)) {
                D_ending_80196F8C = 9;
            }
            break;
    }

    switch (D_ending_80196F8C) {
        case 0:
            Ending_8018A124(0);
            /* fallthrough */
        case 1:
            Ending_80187D3C(0);
            gFillScreenAlphaTarget = 0;
            D_ending_8019858C = 0;
            D_ending_80196F8C = 2;
            gCsFrameCount = 0;
            /* fallthrough */
        case 2:
            Ending_80188030(0);
            break;

        case 3:
            Ending_80187D3C(1);
            gFillScreenAlphaTarget = 0;
            D_ending_8019858C = 0;
            D_ending_80196F8C = 4;
            gCsFrameCount = 0;
            gOverlayStage = 1;
            break;

        case 4:
            Ending_80188030(1);
            break;

        case 5:
            Ending_80188394();
            gFillScreenAlphaTarget = 0;
            D_ending_8019858C = 0;
            D_ending_80196F8C = 6;
            gCsFrameCount = 0;
            gOverlayStage = 4;
            break;

        case 6:
            Ending_8018845C();
            break;

        case 7:
            Ending_80188DB4();
            gFillScreenAlphaTarget = 0;
            D_ending_8019858C = 0;
            D_ending_80196F8C = 8;
            gCsFrameCount = 0;
            /* fallthrough */
        case 8:
            Ending_80189108();
            break;

        case 9:
            gFillScreenAlphaTarget = 0;
            gCsFrameCount = 0;
            D_ending_80196D00 = 7;
            break;
    }
}

void Ending_8018A828(void) {
    switch (D_ending_80196F8C) {
        case 2:
            Ending_80187520(0);
            Ending_801876A4();
            Ending_80187860(0, 0);
            break;

        case 4:
            Ending_80187520(1);
            Ending_801876A4();
            Ending_80187860(0, 1);
            break;

        case 6:
            Ending_8018A2A8();
            break;

        case 7:
        case 8:
            D_ending_80196F88 = 1;
            Ending_8018A2A8();
            D_ending_80196F88 = 4;
            Ending_80187860(1, 0);
            Ending_801888F4();
            Ending_801886F4();
            break;
    }
}

void Ending_8018A8FC(void) {
    if (gFillScreenAlpha != gFillScreenAlphaTarget) {
        if (gFillScreenAlpha < gFillScreenAlphaTarget) {
            gFillScreenAlpha += gFillScreenAlphaStep;
            if (gFillScreenAlpha >= gFillScreenAlphaTarget) {
                gFillScreenAlpha = gFillScreenAlphaTarget;
            }
        } else {
            gFillScreenAlpha -= gFillScreenAlphaStep;
            if (gFillScreenAlpha <= gFillScreenAlphaTarget) {
                gFillScreenAlpha = gFillScreenAlphaTarget;
            }
        }
    }
    gFillScreenAlphaStep = 16;
}

void Ending_8018A96C(void) {
    gCsFrameCount++;
    gGameFrameCount++;

    switch (D_ending_80196D00) {
        case 0:
            gRadioState = 0;
            gGameFrameCount = 0;
            gOverlayStage = 0;
            gCsCamEyeX = gCsCamEyeY = gCsCamEyeZ = 0.0f;
            gCsCamAtX = gCsCamAtY = 0.0f;
            gCsCamAtZ = -100.0f;
            D_ending_80196D00 = 1;
            break;

        case 1:
            if (D_ending_80192E70 < 2800) {
                break;
            }
        case 2:
            D_ending_80196D00 = 3;
            gCsFrameCount = 0;

        case 3:
            if (Ending_8018BCB0() == 0) {
                break;
            }
        case 4:
            gOverlayStage = 2;
            D_ending_80196D00 = 5;
            break;

        case 5:
            D_ending_80196F8C = 0;
            D_ending_80196D00 = 6;

        case 6:
            Ending_8018A570();
            break;

        case 7:
            break;
    }
    Ending_8018A8FC();
    Ending_8018B3D8();
    Ending_8018ABE8();
}

void Ending_8018AAC4(void) {
    Matrix_Push(&gGfxMatrix);
    Matrix_LookAt(gGfxMatrix, gCsCamEyeX, gCsCamEyeY, gCsCamEyeZ, gCsCamAtX, gCsCamAtY, gCsCamAtZ, 0.0f, 100.0f, 0.0f,
                  0);

    switch (D_ending_80196D00) {
        case 1:
            Ending_801926D4();
            break;

        case 3:
            Ending_8018C21C();
            break;

        case 6:
            Ending_8018A828();
            break;

        case 7:
            Ending_801926D4();
            break;
    }

    Ending_8018CE20(D_ending_80196D04);
    D_ending_80196D04++;
    func_radio_800BB5D0();
    Matrix_Pop(&gGfxMatrix);
}

void Ending_8018ABE8(void) {
    if (gControllerPress[3].button & Z_TRIG) {
        D_ending_80198584 ^= 1;
    }

    if (!D_ending_80198584) {
        return;
    }

    if (gControllerPress[3].button & R_TRIG) {
        D_ending_80198588++;
        if (D_ending_80198588 > 4) {
            D_ending_80198588 = 0;
        }
    }

    switch (D_ending_80198588) {
        case 0:
            if (gControllerHold[3].button & B_BUTTON) {
                gFogRed++;
                if (gFogRed > 255) {
                    gFogRed = 255;
                }
            }
            if (gControllerHold[3].button & A_BUTTON) {
                gFogRed--;
                if (gFogRed < 0) {
                    gFogRed = 0;
                }
            }
            if (gControllerHold[3].button & L_CBUTTONS) {
                gFogGreen++;
                if (gFogGreen > 255) {
                    gFogGreen = 255;
                }
            }
            if (gControllerHold[3].button & D_CBUTTONS) {
                gFogGreen--;
                if (gFogGreen < 0) {
                    gFogGreen = 0;
                }
            }
            if (gControllerHold[3].button & U_CBUTTONS) {
                gFogBlue++;
                if (gFogBlue > 255) {
                    gFogBlue = 255;
                }
            }
            if (gControllerHold[3].button & R_CBUTTONS) {
                gFogBlue--;
                if (gFogBlue < 0) {
                    gFogBlue = 0;
                }
            }
            break;

        case 1:
            if (gControllerHold[3].button & B_BUTTON) {
                gLight1R++;
                if (gLight1R > 255) {
                    gLight1R = 255;
                }
            }
            if (gControllerHold[3].button & A_BUTTON) {
                gLight1R--;
                if (gLight1R < 0) {
                    gLight1R = 0;
                }
            }
            if (gControllerHold[3].button & L_CBUTTONS) {
                gLight1G++;
                if (gLight1G > 255) {
                    gLight1G = 255;
                }
            }
            if (gControllerHold[3].button & D_CBUTTONS) {
                gLight1G--;
                if (gLight1G < 0) {
                    gLight1G = 0;
                }
            }
            if (gControllerHold[3].button & U_CBUTTONS) {
                gLight1B++;
                if (gLight1B > 255) {
                    gLight1B = 255;
                }
            }
            if (gControllerHold[3].button & R_CBUTTONS) {
                gLight1B--;
                if (gLight1B < 0) {
                    gLight1B = 0;
                }
            }
            break;

        case 2:
            if (gControllerHold[3].button & B_BUTTON) {
                gAmbientR++;
                if (gAmbientR > 255) {
                    gAmbientR = 255;
                }
            }
            if (gControllerHold[3].button & A_BUTTON) {
                gAmbientR--;
                if (gAmbientR < 0) {
                    gAmbientR = 0;
                }
            }
            if (gControllerHold[3].button & L_CBUTTONS) {
                gAmbientG++;
                if (gAmbientG > 255) {
                    gAmbientG = 255;
                }
            }
            if (gControllerHold[3].button & D_CBUTTONS) {
                gAmbientG--;
                if (gAmbientG < 0) {
                    gAmbientG = 0;
                }
            }
            if (gControllerHold[3].button & U_CBUTTONS) {
                gAmbientB++;
                if (gAmbientB > 255) {
                    gAmbientB = 255;
                }
            }
            if (gControllerHold[3].button & R_CBUTTONS) {
                gAmbientB--;
                if (gAmbientB < 0) {
                    gAmbientB = 0;
                }
            }
            break;

        case 3:
            if (gControllerHold[3].button & B_BUTTON) {
                D_ctx_801784D0 += 1.0f;
                if (D_ctx_801784D0 > 360.0f) {
                    D_ctx_801784D0 = 0.0f;
                }
            }
            if (gControllerHold[3].button & A_BUTTON) {
                D_ctx_801784D0 -= 1.0f;
                if (D_ctx_801784D0 < -360.0f) {
                    D_ctx_801784D0 = 0.0f;
                }
            }
            if (gControllerHold[3].button & L_CBUTTONS) {
                D_ctx_801784D4 += 1.0f;
                if (D_ctx_801784D4 > 360.0f) {
                    D_ctx_801784D4 = 0.0f;
                }
            }
            if (gControllerHold[3].button & D_CBUTTONS) {
                D_ctx_801784D4 -= 1.0f;
                if (D_ctx_801784D4 < -360.0f) {
                    D_ctx_801784D4 = 0.0f;
                }
            }
            if (gControllerHold[3].button & U_CBUTTONS) {
                D_ctx_801784D8 += 1.0f;
                if (D_ctx_801784D8 > 360.0f) {
                    D_ctx_801784D8 = 0.0f;
                }
            }
            if (gControllerHold[3].button & R_CBUTTONS) {
                D_ctx_801784D8 -= 1.0f;
                if (D_ctx_801784D8 < -360.0f) {
                    D_ctx_801784D8 = 0.0f;
                }
            }
            break;

        case 4:
            if (gControllerPress[3].button & B_BUTTON) {
                gFogNear++;
                if (gFogNear >= gFogFar) {
                    gFogNear = gFogFar - 1;
                }
            }
            if (gControllerPress[3].button & A_BUTTON) {
                gFogNear--;
            }
            if (gControllerPress[3].button & L_CBUTTONS) {
                gFogFar++;
            }
            if (gControllerPress[3].button & D_CBUTTONS) {
                gFogFar--;
            }
            break;
    }
}

void Ending_8018B16C(void) {
}

void Ending_8018B174(Vec3f* arg0, Vec3f* arg1, f32* arg2) {
    f32 sp4C;
    f32 var_fv0 = 0.0f;
    f32 var_fv1 = 0.0f;
    f32 var_fa0 = 0.0f;
    f32 var_fa1 = 0.0f;
    f32 var_ft4 = 0.0f;
    f32 var_ft5 = 0.0f;
    Vec3f sp28 = *arg0;
    Vec3f sp1C = *arg1;
    sp4C = *arg2;

    if (gControllerHold[2].button & Z_TRIG) {
        if (gControllerHold[2].button & R_CBUTTONS) {
            var_fa1 += 100.0f;
        }
        if (gControllerHold[2].button & L_CBUTTONS) {
            var_fa1 -= 100.0f;
        }
    } else {
        if (gControllerHold[2].button & R_CBUTTONS) {
            var_fa1 += 10.0f;
        }
        if (gControllerHold[2].button & L_CBUTTONS) {
            var_fa1 -= 10.0f;
        }
    }

    if (gControllerHold[2].button & Z_TRIG) {
        if (gControllerHold[2].button & U_CBUTTONS) {
            var_fa0 += 100.0f;
        }
        if (gControllerHold[2].button & D_CBUTTONS) {
            var_fa0 -= 100.0f;
        }
    } else {
        if (gControllerHold[2].button & U_CBUTTONS) {
            var_fa0 += 10.0f;
        }
        if (gControllerHold[2].button & D_CBUTTONS) {
            var_fa0 -= 10.0f;
        }
    }

    if (gControllerHold[2].button & Z_TRIG) {
        var_fv1 = gControllerPress[2].stick_y;
    } else {
        var_ft5 = gControllerPress[2].stick_y / 10.0f;
        var_ft4 = gControllerPress[2].stick_x / 10.0f;
    }

    if (gControllerHold[2].button & B_BUTTON) {
        var_fv0 += 0.01f;
    }

    if (gControllerHold[2].button & A_BUTTON) {
        var_fv0 -= 0.01f;
    }

    sp4C += var_fv0;
    if (sp4C < 0.01f) {
        sp4C = 0.01f;
    }

    sp28.x += var_fa1;
    sp28.y += var_fa0;
    sp28.z -= var_fv1;
    sp1C.x += var_ft5;
    sp1C.y += var_ft4;

    *arg0 = sp28;
    *arg1 = sp1C;
    *arg2 = sp4C;
}

void Ending_8018B3D8(void) {
}

void Ending_8018B3E0(void) {
}

void Ending_8018B3E8(Actor* arg0, s32 arg1) {
    Vec3f sp38[2] = {
        { 2880.0f, 860.0f, -1440.0f },
        { -6000.0f, 3400.0f, 3600.0f },
    };
    Vec3f sp20[2] = {
        { 0.0f, 90.0f, 0.0f },
        { 0.0f, 290.0f, 0.0f },
    };

    Actor_Initialize(arg0);
    arg0->obj.status = OBJ_ACTIVE;
    arg0->obj.id = 0;
    arg0->state = arg1;
    arg0->unk_0F4.x = sp20[arg1].x;
    arg0->unk_0F4.y = sp20[arg1].y;
    arg0->unk_0F4.z = sp20[arg1].z;
    arg0->obj.pos = sp38[arg1];

    if (arg1 == 0) {
        arg0->obj.pos.x -= 600.0f;
        arg0->obj.pos.y += 150.0f;
        arg0->fwork[0] = 6.0f;
    }
    arg0->scale = 1.0f;
}

void Ending_8018B52C(Actor* arg0, s32 arg1) {
    Vec3f sp44[3] = {
        { -230.0f, -750.0f, -1300.0f },
        { 230.0f, -240.0f, -1150.0f },
        { 230.0f, -240.0f, -1450.0f },
    };
    Vec3f sp20[3] = {
        { 0.0f, 180.0f, 0.0f },
        { 180.0f, 0.0f, 0.0f },
        { 180.0f, 0.0f, 0.0f },
    };

    Actor_Initialize(arg0);
    arg0->obj.status = OBJ_ACTIVE;
    arg0->obj.id = 1;
    arg0->obj.pos = sp44[arg1];
    arg0->unk_0F4.x = sp20[arg1].x;
    arg0->unk_0F4.y = sp20[arg1].y;
    arg0->unk_0F4.z = sp20[arg1].z;
    arg0->scale = 1.0f;
}

void Ending_8018B624(Actor* arg0) {
    Vec3f sp24 = { -40.0f, -560.0f, 400.0f };
    Vec3f sp18 = { 0.0f, 290.0f, 0.0f };

    Actor_Initialize(arg0);
    arg0->obj.status = 2;
    arg0->obj.id = 2;
    arg0->obj.pos = sp24;
    arg0->unk_0F4.x = sp18.x;
    arg0->unk_0F4.y = sp18.y;
    arg0->unk_0F4.z = sp18.z;
    arg0->scale = 1.0f;
}

void Ending_8018B6D8(Actor* arg0, s32 arg1) {
    Vec3f sp80[6] = {
        { -400.0f, 500.0f, -1200.0f }, { -160.0f, 500.0f, -1400.0f }, { 80.0f, 500.0f, -1600.0f },
        { 320.0f, 500.0f, -1800.0f },  { 560.0f, 500.0f, -2000.0f },  { 800.0f, 500.0f, -2200.0f },
    };
    Vec3f sp38[6] = {
        { 0.0f, 90.0f, 0.0f }, { 0.0f, 90.0f, 0.0f }, { 0.0f, 90.0f, 0.0f },
        { 0.0f, 90.0f, 0.0f }, { 0.0f, 90.0f, 0.0f }, { 0.0f, 90.0f, 0.0f },
    };
    s32 sp20[6] = { 150, 157, 164, 171, 178, 185 };

    Actor_Initialize(arg0);
    arg0->obj.status = OBJ_ACTIVE;
    arg0->obj.id = 3;
    arg0->obj.pos = sp80[arg1];
    arg0->unk_0F4.x = sp38[arg1].x;
    arg0->unk_0F4.y = sp38[arg1].y;
    arg0->unk_0F4.z = sp38[arg1].z;
    arg0->obj.pos.x += 3200.0f;
    arg0->obj.pos.z -= 200.0f;
    arg0->scale = 1.0f;
    arg0->fwork[1] = 1.0f;
    arg0->iwork[1] = 100;
    arg0->fwork[0] = 30.0f;
    arg0->iwork[0] = sp20[arg1];
    arg0->unk_046 = arg1;
}

void Ending_8018B860(void) {
    Vec3f sp4C = { 0.0f, -830.0f, -933.0f };
    Vec3f sp40 = { 0.0f, -550.0f, -1280.0f };
    s32 sp34[3] = { 240, 180, 54 };
    s32 sp28[3] = { 32, 32, 32 };
    s32 sp1C[3] = { 5, 5, 8 };

    gCsCamEyeX = sp4C.x;
    gCsCamEyeY = sp4C.y;
    gCsCamEyeZ = sp4C.z;

    gCsCamAtX = sp40.x;
    gCsCamAtY = sp40.y;
    gCsCamAtZ = sp40.z;

    gLight1R = sp28[0];
    gLight1G = sp28[1];
    gLight1B = sp28[2];

    D_ctx_801784D0 = sp34[0];
    D_ctx_801784D4 = sp34[1];
    D_ctx_801784D8 = sp34[2];

    gAmbientR = sp1C[0];
    gAmbientG = sp1C[1];
    gAmbientB = sp1C[2];

    func_play_800A6148();

    Ending_8018B3E8(&gActors[0], 0);
    Ending_8018B52C(&gActors[1], 0);
    Ending_8018B52C(&gActors[2], 1);
    Ending_8018B52C(&gActors[3], 2);
    Ending_8018B6D8(&gActors[4], 0);
    Ending_8018B6D8(&gActors[5], 1);
    Ending_8018B6D8(&gActors[6], 2);
    Ending_8018B6D8(&gActors[7], 3);
    Ending_8018B6D8(&gActors[8], 4);
    Ending_8018B6D8(&gActors[9], 5);

    D_ctx_80177A48[0] = gCsCamAtX;
    D_ctx_80177A10[0] = 0;
    D_ending_8019858C = 0;
    gBgColor = 0x4AE5; // 72, 88, 144
    D_ctx_80178410 = 0;
}

void Ending_8018BAD0(void) {
    Vec3f sp4C = { 240.0f, -110.0f, -200.0f };
    Vec3f sp40 = { 0.0f, 0.0f, 100.0f };
    s32 sp34[3] = { 240, 250, 0 };
    s32 sp28[3] = { 32, 32, 32 };
    s32 sp1C[3] = { 5, 5, 8 };

    gCsCamEyeX = sp4C.x;
    gCsCamEyeY = sp4C.y;
    gCsCamEyeZ = sp4C.z;

    gCsCamAtX = sp40.x;
    gCsCamAtY = sp40.y;
    gCsCamAtZ = sp40.z;

    gLight1R = sp28[0];
    gLight1G = sp28[1];
    gLight1B = sp28[2];

    D_ctx_801784D0 = sp34[0];
    D_ctx_801784D4 = sp34[1];
    D_ctx_801784D8 = sp34[2];

    gAmbientR = sp1C[0];
    gAmbientG = sp1C[1];
    gAmbientB = sp1C[2];

    func_play_800A6148();
    Ending_8018B3E8(&gActors[0], 1);
    Ending_8018B624(&gActors[1]);

    D_ctx_80177A10[0] = 1;
    D_ending_8019858C = 0;
    gBgColor = 0x4AE5; // 72, 88, 144
    D_ctx_80178410 = 0;
}

f32 D_ending_80192DF0[8] = {
    80.0f, 0.0f, 40.0f, 90.0f, 0.0f, 0.1f, 0.1f, 50.0f,
};

bool Ending_8018BCB0(void) {
    s32 i;
    Vec3f sp78;
    Vec3f sp6C;
    s32 pad68;
    s32 pad64; // Vec3f?
    s32 pad60;
    s32 sp5C = false;
    s32 pad58;

    switch (gCsFrameCount) {
        case 0:
            gFillScreenAlphaTarget = 0;
            Ending_8018B860();
            break;

        case 780:
            Ending_8018BAD0();
            break;

        case 1010:
            sp5C = true;
            func_play_800A6148();
            break;
    }

    Ending_8018A024();
    Lights_SetOneLight(&gMasterDisp, gLight1x, gLight1y, gLight1z, gLight1R, gLight1G, gLight1B, gAmbientR, gAmbientG,
                       gAmbientB);

    for (i = 59; i >= 0; i--) {
        if (gActors[i].obj.status != OBJ_FREE) {
            switch (gActors[i].obj.id) {
                case 0:
                    switch (gActors[i].state) {
                        case 0:
                            if (gActors[i].obj.pos.x < -4000.0f) {
                                gActors[i].obj.status = OBJ_FREE;
                            }
                            break;

                        case 1:
                            if (gCsFrameCount >= 780) {
                                gActors[i].obj.pos.x += 8.7f;
                                gActors[i].obj.pos.y += -6.3f;
                                gActors[i].obj.pos.z += -3.3f;
                            }
                            break;
                    }

                    if (i == D_ending_8019858C) {
                        Ending_8018B174(&gActors[i].obj.pos, &gActors[i].obj.rot, &gActors[i].scale);
                    }
                    break;

                case 1:
                    if (i == D_ending_8019858C) {
                        Ending_8018B174(&gActors[i].obj.pos, &gActors[i].obj.rot, &gActors[i].scale);
                    }
                    break;

                case 2:
                    if (i == D_ending_8019858C) {
                        Ending_8018B174(&gActors[i].obj.pos, &gActors[i].obj.rot, &gActors[i].scale);
                    }
                    break;

                case 3:
                    if (gActors[i].iwork[0] > 0) {
                        gActors[i].iwork[0]--;
                    } else {
                        gActors[i].iwork[1]--;
                        if (gActors[i].iwork[1] <= 0) {
                            gActors[i].iwork[1] = 0;
                            gActors[i].obj.status = OBJ_FREE;
                        }
                        Math_SmoothStepToF(&gActors[i].fwork[0], 1.0f, 0.05f, 1000.0f, 0.001f);
                    }

                    if (i == D_ending_8019858C) {
                        Ending_8018B174(&gActors[i].obj.pos, &gActors[i].obj.rot, &gActors[i].scale);
                    }
                    break;
            }

            Matrix_RotateY(gCalcMatrix, (gActors[i].unk_0F4.y + 180.0f) * M_DTOR, 0);
            Matrix_RotateX(gCalcMatrix, -(gActors[i].unk_0F4.x * M_DTOR), 1);

            sp78.x = 0.0f;
            sp78.y = 0.0f;
            sp78.z = gActors[i].fwork[0];

            Matrix_MultVec3fNoTranslate(gCalcMatrix, &sp78, &sp6C);

            gActors[i].vel.x = sp6C.x;
            gActors[i].vel.y = sp6C.y;
            gActors[i].vel.z = sp6C.z;

            if (0) {} // some sort of vec_set macro?

            gActors[i].obj.rot.x = -gActors[i].unk_0F4.x;
            gActors[i].obj.rot.y = gActors[i].unk_0F4.y + 180.0f;
            gActors[i].obj.rot.z = -gActors[i].unk_0F4.z;

            gActors[i].obj.pos.x += gActors[i].vel.x;
            gActors[i].obj.pos.y += gActors[i].vel.y;
            gActors[i].obj.pos.z += gActors[i].vel.z;

            gActors[i].vel.y -= gActors[i].gravity;
        }
    }

    if (D_ctx_80177A10[0] == 0) {
        if ((gActors[0].obj.pos.x <= gCsCamAtX) && (gActors[0].obj.pos.x > -400.0f)) {
            D_ctx_80177A48[0] = gActors[0].obj.pos.x;
        }
        if (gCsFrameCount >= 30) {
            Math_SmoothStepToF(&gCsCamAtX, D_ctx_80177A48[0], 0.004f, 1000.0f, 0.0001f);
            Math_SmoothStepToF(&gCsCamAtY, 156.0f, 0.002f, 1000.0f, 0.0001f);
        }
    } else {
        gCsCamAtX = gActors[0].obj.pos.x;
        gCsCamAtY = gActors[0].obj.pos.y;
        gCsCamAtZ = gActors[0].obj.pos.z;
    }

    if ((gCsFrameCount < 548) && (gCsFrameCount >= 240)) {
        D_ctx_801784D0 -= 0.2f;
        if (D_ctx_801784D0 < 180.0f) {
            D_ctx_801784D0 = 180.0f;
        }
    }

    if (gCsFrameCount >= 549) {
        D_ctx_801784D0 += 0.2f;
        if (D_ctx_801784D0 > 240.0f) {
            D_ctx_801784D0 = 240.0f;
        }
    }

    if ((gCsFrameCount == 760) || (gCsFrameCount == 994)) {
        gFillScreenAlphaTarget = 255;
    }

    if (gCsFrameCount == 780) {
        gFillScreenAlphaTarget = 0;
    }

    return sp5C;
}

void Ending_8018C21C(void) {
    Vec3f sp124[3] = {
        { 0.0f, 40.0f, -2530.0f },
        { 335.0f, -92.0f, -1529.0f },
        { -335.0f, -92.0f, -1529.0f },
    };
    Vec3f sp10C[2] = {
        { 4.0f, 1.0f, 10.0f },
        { 4.4f, 1.0f, 11.0f },
    };
    Vec3f spF4[2] = {
        { 5.1f, 1.0f, 15.0f },
        { 5.6f, 1.0f, 16.5f },
    };
    s32 i2;
    Vec3f* scale;
    Vec3f* var_s1;
    f32 spE4;
    s32 i;

    if (gCsFrameCount < 780) {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, 0x11);
        Matrix_Translate(gGfxMatrix, 0.0f, -1200.0f, -6000.0f, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_END_700C8B0);
        Matrix_Pop(&gGfxMatrix);
    } else {
        Matrix_Push(&gGfxMatrix);
        RCP_SetupDL(&gMasterDisp, 0x11);
        Matrix_Translate(gGfxMatrix, -2000.0f, -3000.0f, 3000.0f, 1);
        Matrix_RotateY(gGfxMatrix, 110.0f * M_DTOR, 1);
        Matrix_SetGfxMtx(&gMasterDisp);
        gSPDisplayList(gMasterDisp++, D_END_700C8B0);
        Matrix_Pop(&gGfxMatrix);
    }

    Matrix_Push(&gGfxMatrix);

    for (i = 59; i >= 0; i--) {
        if (gActors[i].obj.status != OBJ_FREE) {
            Matrix_Push(&gGfxMatrix);
            switch (gActors[i].obj.id) {
                case 0:
                    if (gActors[i].state == 0) {
                        RCP_SetupDL(&gMasterDisp, 0x17);
                        Matrix_Translate(gGfxMatrix, gActors[i].obj.pos.x, gActors[i].obj.pos.y, gActors[i].obj.pos.z,
                                         1);
                        Matrix_Scale(gGfxMatrix, gActors[i].scale, gActors[i].scale, gActors[i].scale, 1);
                        Matrix_RotateY(gGfxMatrix, gActors[i].obj.rot.y * M_DTOR, 1);
                        Matrix_RotateX(gGfxMatrix, gActors[i].obj.rot.x * M_DTOR, 1);
                        Matrix_RotateZ(gGfxMatrix, gActors[i].obj.rot.z * M_DTOR, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);

                        if (gGreatFoxIntact) {
                            gSPDisplayList(gMasterDisp++, D_GREAT_FOX_E000000);
                        }

                        if (!gGreatFoxIntact) {
                            gSPDisplayList(gMasterDisp++, D_GREAT_FOX_E003AB0);
                        }

                        RCP_SetupDL(&gMasterDisp, 0x31);
                        gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 64);
                        gDPSetEnvColor(gMasterDisp++, 255, 255, 0, 64);

                        for (i2 = 0, var_s1 = sp124; i2 < 3; i2++, var_s1++) {
                            Matrix_Push(&gGfxMatrix);
                            scale = &sp10C[gGameFrameCount % 2];
                            Matrix_Push(&gGfxMatrix);
                            Matrix_Translate(gGfxMatrix, var_s1->x, var_s1->y, var_s1->z, 1);
                            Matrix_Scale(gGfxMatrix, scale->x, scale->y, scale->z, 1);
                            Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_END_7010970);
                            Matrix_Pop(&gGfxMatrix);
                            Matrix_Push(&gGfxMatrix);
                            scale = &spF4[gGameFrameCount % 2];
                            Matrix_Translate(gGfxMatrix, var_s1->x, var_s1->y, var_s1->z - 60.0f, 1);
                            Matrix_Scale(gGfxMatrix, scale->x, scale->y, scale->z, 1);
                            Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
                            Matrix_SetGfxMtx(&gMasterDisp);
                            gSPDisplayList(gMasterDisp++, D_END_7010970);
                            Matrix_Pop(&gGfxMatrix);
                        }
                    } else {
                        RCP_SetupDL(&gMasterDisp, 0x17);
                        Matrix_Translate(gGfxMatrix, gActors[i].obj.pos.x, gActors[i].obj.pos.y, gActors[i].obj.pos.z,
                                         1);
                        Matrix_Scale(gGfxMatrix, gActors[i].scale, gActors[i].scale, gActors[i].scale, 1);
                        Matrix_RotateY(gGfxMatrix, gActors[i].obj.rot.y * M_DTOR, 1);
                        Matrix_RotateX(gGfxMatrix, gActors[i].obj.rot.x * M_DTOR, 1);
                        Matrix_RotateZ(gGfxMatrix, gActors[i].obj.rot.z * M_DTOR, 1);
                        Matrix_SetGfxMtx(&gMasterDisp);
                        func_demo_800515C4();
                    }
                    break;

                case 1:
                    RCP_SetupDL(&gMasterDisp, 0x17);
                    Matrix_Translate(gGfxMatrix, gActors[i].obj.pos.x, gActors[i].obj.pos.y, gActors[i].obj.pos.z, 1);
                    Matrix_Scale(gGfxMatrix, gActors[i].scale, gActors[i].scale, gActors[i].scale, 1);
                    Matrix_RotateY(gGfxMatrix, gActors[i].obj.rot.y * M_DTOR, 1);
                    Matrix_RotateX(gGfxMatrix, gActors[i].obj.rot.x * M_DTOR, 1);
                    Matrix_RotateZ(gGfxMatrix, gActors[i].obj.rot.z * M_DTOR, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_END_700F240);
                    break;

                case 2:
                    RCP_SetupDL(&gMasterDisp, 0x17);
                    Matrix_Translate(gGfxMatrix, gActors[i].obj.pos.x, gActors[i].obj.pos.y, gActors[i].obj.pos.z, 1);
                    Matrix_Scale(gGfxMatrix, gActors[i].scale, gActors[i].scale, gActors[i].scale, 1);
                    Matrix_RotateY(gGfxMatrix, gActors[i].obj.rot.y * M_DTOR, 1);
                    Matrix_RotateX(gGfxMatrix, gActors[i].obj.rot.x * M_DTOR, 1);
                    Matrix_RotateZ(gGfxMatrix, gActors[i].obj.rot.z * M_DTOR, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_END_700F320);
                    break;

                case 3:
                    RCP_SetupDL(&gMasterDisp, 0x17);
                    Matrix_Translate(gGfxMatrix, gActors[i].obj.pos.x, gActors[i].obj.pos.y, gActors[i].obj.pos.z, 1);
                    Matrix_Scale(gGfxMatrix, gActors[i].scale, gActors[i].scale, gActors[i].scale, 1);
                    Matrix_RotateY(gGfxMatrix, gActors[i].obj.rot.y * M_DTOR, 1);
                    Matrix_RotateX(gGfxMatrix, gActors[i].obj.rot.x * M_DTOR, 1);
                    Matrix_RotateZ(gGfxMatrix, gActors[i].obj.rot.z * M_DTOR, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_D00B880);
                    Matrix_Push(&gGfxMatrix);
                    RCP_SetupDL(&gMasterDisp, 0x31);
                    gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 255, 255, 255, 64);
                    gDPSetEnvColor(gMasterDisp++, 0, 255, 0, 64);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -66.0f, 1);
                    Matrix_Scale(gGfxMatrix, 1.0f, 1.0f, 1.0f, 1);
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_END_7010970);
                    Matrix_Pop(&gGfxMatrix);
                    spE4 = gActors[i].fwork[1];
                    RCP_SetupDL(&gMasterDisp, 0x29);

                    switch (gActors[i].unk_046) {
                        case 0:
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 200, 0, 0, gActors[i].iwork[1]);
                            break;
                        case 1:
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 200, 0, gActors[i].iwork[1]);
                            break;
                        case 2:
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 0, 0, 200, gActors[i].iwork[1]);
                            break;
                        case 3:
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 200, 200, 0, gActors[i].iwork[1]);
                            break;
                        case 4:
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 200, 0, 200, gActors[i].iwork[1]);
                            break;
                        case 5:
                            gDPSetPrimColor(gMasterDisp++, 0x00, 0x00, 200, 200, 200, gActors[i].iwork[1]);
                            break;
                    }
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, 70.0f, 0.0f, -100.0f, 1);
                    Matrix_Scale(gGfxMatrix, spE4, 1.0f, 200.0f, 1);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, 1);
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_END_700C620);
                    Matrix_Pop(&gGfxMatrix);
                    Matrix_Push(&gGfxMatrix);
                    Matrix_Translate(gGfxMatrix, -70.0f, 0.0f, -100.0f, 1);
                    Matrix_Scale(gGfxMatrix, spE4, 1.0f, 200.0f, 1);
                    Matrix_Translate(gGfxMatrix, 0.0f, 0.0f, -17.5f, 1);
                    Matrix_RotateX(gGfxMatrix, M_PI / 2, 1);
                    Matrix_SetGfxMtx(&gMasterDisp);
                    gSPDisplayList(gMasterDisp++, D_END_700C620);
                    Matrix_Pop(&gGfxMatrix);
                    break;
            }
            Matrix_Pop(&gGfxMatrix);
        }
    }
}
