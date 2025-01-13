#ifndef GFX_H
#define GFX_H

#include <libultraship.h>
#include "sf64math.h"
#include "libc/stdbool.h"

#define SCREEN_WIDTH  320
#define SCREEN_HEIGHT 240

#define FILL_COLOR(rgba) (((rgba) << 0x10) | (rgba))
#define RGBA16_RED(color16) (((color16) >> 0xB) & 0x1F)
#define RGBA16_GRN(color16) (((color16) >> 6) & 0x1F)
#define RGBA16_BLU(color16) (((color16) >> 1) & 0x1F)

#define gDPSetTileCustom(pkt, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                    \
    do {                                                                                                               \
        gDPPipeSync(pkt);                                                                                              \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, \
                   masks, shifts);                                                                                     \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,  \
                   cms, masks, shifts);                                                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    } while (0)

#define gDPSetupTile(pkt, fmt, siz, width, height, dw, dh,           \
                     cms, cmt, masks, maskt, shifts, shiftt)         \
{                                                                    \
    gDPTileSync(pkt);                                                \
    gDPSetTile(pkt, fmt, siz, (((width) * siz##_LINE_BYTES)+7)>>3, 0,\
        G_TX_RENDERTILE, 0, cmt, maskt, shiftt, cms, masks, shifts); \
    gDPSetTileSize(pkt, G_TX_RENDERTILE, dw, dh,                     \
        ((width)-1) << G_TEXTURE_IMAGE_FRAC,                         \
        ((height)-1) << G_TEXTURE_IMAGE_FRAC);                       \
}

#define gsDPSetupTile(fmt, siz, width, height, dw, dh,               \
                      cms, cmt, masks, maskt, shifts, shiftt)        \
    gsDPTileSync(),                                                  \
    gsDPSetTile(fmt, siz, (((width) * siz##_LINE_BYTES)+7)>>3, 0,    \
        G_TX_RENDERTILE, 0, cmt, maskt, shiftt, cms, masks, shifts), \
    gsDPSetTileSize(G_TX_RENDERTILE, dw, dh,                         \
        ((width)-1) << G_TEXTURE_IMAGE_FRAC,                         \
        ((height)-1) << G_TEXTURE_IMAGE_FRAC)

#define gDPLoadTileTexture(pkt, timg, fmt, siz, width, height)         \
{                                                                      \
    gDPSetTextureImage(pkt, fmt, siz##_LOAD_BLOCK, 1, timg);           \
    gDPTileSync(pkt);                                                  \
    gDPSetTile(pkt, fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,        \
                0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, \
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);   \
    gDPLoadSync(pkt);                                                  \
    gDPLoadBlock(pkt, G_TX_LOADTILE, 0, 0,                             \
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT) -1,           \
        CALC_DXT(width, siz##_BYTES));                                 \
}

#define gsDPLoadTileTexture(timg, fmt, siz, width, height)             \
    gsDPSetTextureImage(fmt, siz##_LOAD_BLOCK, 1, timg),               \
    gsDPTileSync(),                                                    \
    gsDPSetTile(fmt, siz##_LOAD_BLOCK, 0, 0, G_TX_LOADTILE,            \
                0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD, \
                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD),   \
    gsDPLoadSync(),                                                    \
    gsDPLoadBlock(G_TX_LOADTILE, 0, 0,                                 \
        (((width)*(height) + siz##_INCR) >> siz##_SHIFT) -1,           \
        CALC_DXT(width, siz##_BYTES))

#define gSPSetOtherModeHi(pkt, settings) gSPSetOtherMode(pkt, G_SETOTHERMODE_H, G_MDSFT_BLENDMASK, 24, settings)
#define gsSPSetOtherModeHi(settings) gsSPSetOtherMode(G_SETOTHERMODE_H, G_MDSFT_BLENDMASK, 24, settings)

#define VTX(x,y,z,s,t,crnx,cgny,cbnz,a) { { { x, y, z }, 0, { s, t }, { crnx, cgny, cbnz, a } } }

#define VTX_T(x,y,z,s,t,cr,cg,cb,a) { { x, y, z }, 0, { s, t }, { cr, cg, cb, a } }

typedef enum WipeMode {
    WIPE_CIRCULAR,
    WIPE_HORIZONTAL,
    WIPE_VERTICAL,
} WipeMode;

typedef struct Color_RGBA32 {
    u8 r, g, b, a;
} Color_RGBA32; // size = 0x4

typedef union {
    u16 data[SCREEN_HEIGHT * SCREEN_WIDTH];
    u16 array[SCREEN_HEIGHT][SCREEN_WIDTH];
} FrameBuffer; // size = 0x25800

typedef bool (*OverrideLimbDraw)(s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3f* rot, void* thisx);
typedef void (*PostLimbDraw)(s32, Vec3f*, void*);

typedef struct {
    /* 0x0 */ u16 xLen;
    /* 0x2 */ u16 x;
    /* 0x4 */ u16 yLen;
    /* 0x6 */ u16 y;
    /* 0x8 */ u16 zLen;
    /* 0xA */ u16 z;
} JointKey; // size = 0xC

typedef struct {
    /* 0x00 */ s16 frameCount;
    /* 0x02 */ s16 limbCount;
    /* 0x04 */ u16* frameData;
    /* 0x08 */ JointKey* jointKey;
} Animation; // size = 0xC

typedef struct Limb {
    /* 0x000 */ Gfx* dList;
    /* 0x004 */ Vec3f trans;
    /* 0x010 */ Vec3s rot;
    /* 0x018 */ struct Limb* sibling;
    /* 0x01C */ struct Limb* child;
} Limb; // size = 0x20

void Graphics_NMIWipe(void);

void Lights_SetOneLight(Gfx** dList, s32 dirX, s32 dirY, s32 dirZ, s32 colR, s32 colG, s32 colB, s32 ambR, s32 ambG, s32 ambB);
void Lights_SetTwoLights(Gfx** dList, s32 dir1x, s32 dir1y, s32 dir1z, s32 dir2x, s32 dir2y, s32 dir2z, s32 col1r, s32 col1g,
                   s32 col1b, s32 col2r, s32 col2g, s32 col2b, s32 ambR, s32 ambG, s32 ambB);

char* Graphics_ClearPrintBuffer(char *buf, s32 fill, s32 len);
s32 Graphics_Printf(const char *fmt, ...);
void Lib_Texture_Scroll(u16 *texture, s32 width, s32 height, u8 mode);
void Lib_Texture_Mottle(u16 *dst, u16 *src, u8 mode);    
s32 Animation_GetLimbIndex(Limb* limb, Limb** skeleton);
void Animation_DrawLimb(s32 mode, Limb* limb, Limb* *skeleton, Vec3f* jointTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* data);
void Animation_DrawSkeleton(s32 mode, Limb** skeletonSegment, Vec3f* jointTable, OverrideLimbDraw overrideLimbDraw, PostLimbDraw postLimbDraw, void* data, Matrix* transform);
s16 Animation_GetFrameData(Animation *animationSegmemt, s32 frame, Vec3f *frameTable);
s32 Animation_GetFrameCount(Animation *animationSegment);
void Animation_FindBoundingBox(Gfx* dList, s32 len, Vec3f *min, Vec3f *max, s32 *vtxFound, s32 *vtxCount, Vtx* *vtxList);
void Animation_GetDListBoundingBox(Gfx *dList, s32 len, Vec3f *min, Vec3f *max);
void Animation_GetSkeletonBoundingBox(Limb** skeletonSegment, Animation *animationSegment, s32 frame, Vec3f *min, Vec3f* max);
void Lib_TextureRect_CI4(Gfx **gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_CI4_Flip(Gfx **gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_CI4_MirX(Gfx **gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_CI4_MirY(Gfx **gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_CI8(Gfx **gfxPtr, u8* texture, u16* palette, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_RGBA16(Gfx **gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_RGBA16_MirX(Gfx **gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA8(Gfx **gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA8_FlipMirX(Gfx **gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA8_FlipMirY(Gfx **gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA8_MirX(Gfx **gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA8_MirY(Gfx **gfxPtr, u8* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA16(Gfx **gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA16_MirX(Gfx **gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA16_MirY(Gfx **gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_IA16_MirXY(Gfx **gfxPtr, u16* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Lib_TextureRect_RGBA32(Gfx **gfxPtr, u32* texture, u32 width, u32 height, f32 xPos, f32 yPos, f32 xScale, f32 yScale);
void Graphics_FillRectangle(Gfx **gfxPtr, s32 ulx, s32 uly, s32 lrx, s32 lry, u8 r, u8 g, u8 b, u8 a);
u16*  Graphics_SetupTextureRender(Gfx **gfxPtr, u8 width, u8 height);
void Graphics_DisplayHUDNumber(s32 xPos, s32 yPos, s32 number);
void Graphics_DisplaySmallNumber(s32 xPos, s32 yPos, s32 number);
void Graphics_DisplayLargeText(s32 xPos, s32 yPos, f32 xScale, f32 yScale, char *text);
s32 Graphics_GetLargeTextWidth(char *text);
void Graphics_DisplayLargeNumber(s32 xPos, s32 yPos, s32 number);
void Graphics_DisplaySmallText(s32 xPos, s32 yPos, f32 xScale, f32 yScale, char *text);
s32 Graphics_GetSmallTextWidth(char *text);
void func_800A1540(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void Texture_BlendRGBA16(f32 weight, u16 size, u16 *src1, u16 *src2, u16 *dst);

void RCP_SetupDL(Gfx** gfxP, s16 i);
void RCP_SetFog(Gfx** gfxP, s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_0(void);
void RCP_SetupDL_1(void);
void RCP_SetupDL_11(void);
void RCP_SetupDL_12(void);
void RCP_SetupDL_2(void);
void RCP_SetupDL_3(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_4(void);
void RCP_SetupDL_7(void);
void RCP_SetupDL_9(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_8(void);
void RCP_SetupDL_13(void);
void RCP_SetupDL_14(void);
void RCP_SetupDL_17(void);
void RCP_SetupDL_36(void);
void RCP_SetupDL_52(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_62(void);
void RCP_SetupDL_37(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_18(void);
void RCP_SetupDL_20(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_19(void);
void RCP_SetupDL_21(void);
void RCP_SetupDL_33(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_34(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_40(void);
void RCP_SetupDL_42(void);
void RCP_SetupDL_43(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_60(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_47(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_66(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_55(void);
void RCP_SetupDL_57(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_45(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_46(void);
void RCP_SetupDL_41(void);
void RCP_SetupDL_64(void);
void RCP_SetupDL_64_2(void);
void RCP_SetupDL_23(void);
void RCP_SetupDL_29(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_30(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);
void RCP_SetupDL_27(void);
void RCP_SetupDL_32(void);
void RCP_SetupDL_73(void);
void RCP_SetupDL_76(void);
void RCP_SetupDL_74(void);
void RCP_SetupDL_78(void);
void RCP_SetupDL_81(void);
void RCP_SetupDL_48(void);
void RCP_SetupDL_68(void);
void RCP_SetupDL_49(void);
void RCP_SetupDL_44(void);
void RCP_SetupDL_50(void);
void RCP_SetupDL_61(s32 r, s32 g, s32 b, s32 a, s32 near, s32 far);

typedef enum SetupDL {
    /* 0x00 */ SETUPDL_0,
    /* 0x01 */ SETUPDL_1,
    /* 0x02 */ SETUPDL_2,
    /* 0x03 */ SETUPDL_3,
    /* 0x04 */ SETUPDL_4,
    /* 0x05 */ SETUPDL_5,
    /* 0x06 */ SETUPDL_6,
    /* 0x07 */ SETUPDL_7,
    /* 0x08 */ SETUPDL_8,
    /* 0x09 */ SETUPDL_9,
    /* 0x0A */ SETUPDL_10,
    /* 0x0B */ SETUPDL_11,
    /* 0x0C */ SETUPDL_12,
    /* 0x0D */ SETUPDL_13,
    /* 0x0E */ SETUPDL_14,
    /* 0x0F */ SETUPDL_15,
    /* 0x10 */ SETUPDL_16,
    /* 0x11 */ SETUPDL_17,
    /* 0x12 */ SETUPDL_18,
    /* 0x13 */ SETUPDL_19,
    /* 0x14 */ SETUPDL_20,
    /* 0x15 */ SETUPDL_21,
    /* 0x16 */ SETUPDL_22,
    /* 0x17 */ SETUPDL_23,
    /* 0x18 */ SETUPDL_24,
    /* 0x19 */ SETUPDL_25,
    /* 0x1A */ SETUPDL_26,
    /* 0x1B */ SETUPDL_27,
    /* 0x1C */ SETUPDL_28,
    /* 0x1D */ SETUPDL_29,
    /* 0x1E */ SETUPDL_30,
    /* 0x1F */ SETUPDL_31,
    /* 0x20 */ SETUPDL_32,
    /* 0x21 */ SETUPDL_33,
    /* 0x22 */ SETUPDL_34,
    /* 0x23 */ SETUPDL_35,
    /* 0x24 */ SETUPDL_36,
    /* 0x25 */ SETUPDL_37,
    /* 0x26 */ SETUPDL_38,
    /* 0x27 */ SETUPDL_39,
    /* 0x28 */ SETUPDL_40,
    /* 0x29 */ SETUPDL_41,
    /* 0x2A */ SETUPDL_42,
    /* 0x2B */ SETUPDL_43,
    /* 0x2C */ SETUPDL_44,
    /* 0x2D */ SETUPDL_45,
    /* 0x2E */ SETUPDL_46,
    /* 0x2F */ SETUPDL_47,
    /* 0x30 */ SETUPDL_48,
    /* 0x31 */ SETUPDL_49,
    /* 0x32 */ SETUPDL_50,
    /* 0x33 */ SETUPDL_51,
    /* 0x34 */ SETUPDL_52,
    /* 0x35 */ SETUPDL_53,
    /* 0x36 */ SETUPDL_54,
    /* 0x37 */ SETUPDL_55,
    /* 0x38 */ SETUPDL_56,
    /* 0x39 */ SETUPDL_57,
    /* 0x3A */ SETUPDL_58,
    /* 0x3B */ SETUPDL_59,
    /* 0x3C */ SETUPDL_60,
    /* 0x3D */ SETUPDL_61,
    /* 0x3E */ SETUPDL_62,
    /* 0x3F */ SETUPDL_63,
    /* 0x40 */ SETUPDL_64,
    /* 0x41 */ SETUPDL_65,
    /* 0x42 */ SETUPDL_66,
    /* 0x43 */ SETUPDL_67,
    /* 0x44 */ SETUPDL_68,
    /* 0x45 */ SETUPDL_69,
    /* 0x46 */ SETUPDL_70,
    /* 0x47 */ SETUPDL_71,
    /* 0x48 */ SETUPDL_72,
    /* 0x49 */ SETUPDL_73,
    /* 0x4A */ SETUPDL_74,
    /* 0x4B */ SETUPDL_75,
    /* 0x4C */ SETUPDL_76,
    /* 0x4D */ SETUPDL_77,
    /* 0x4E */ SETUPDL_78,
    /* 0x4F */ SETUPDL_79,
    /* 0x50 */ SETUPDL_80,
    /* 0x51 */ SETUPDL_81,
    /* 0x52 */ SETUPDL_82,
    /* 0x53 */ SETUPDL_83,
    /* 0x54 */ SETUPDL_84,
    /* 0x55 */ SETUPDL_85,
    /* 0x56 */ SETUPDL_86,
    /* 0x57 */ SETUPDL_87,
    SETUPDL_29_POINT,
    SETUPDL_36_POINT, 
    SETUPDL_62_POINT,
    SETUPDL_63_POINT, 
    SETUPDL_67_POINT, 
    SETUPDL_75_POINT, 
    SETUPDL_76_POINT, 
    SETUPDL_77_POINT, 
    SETUPDL_78_POINT, 
    SETUPDL_81_POINT, 
    SETUPDL_83_POINT,
    SETUPDL_85_POINT
} SetupDL;

extern Gfx gRcpSetupDLs[][9]; // 0x800D31B0
extern u8 D_80178580[];
extern void* D_80178710;

#endif
