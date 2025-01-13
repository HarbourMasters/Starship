#ifndef SF64_MESG
#define SF64_MESG

#include <libultraship.h>
#include "stdbool.h"

typedef struct {
    s32 msgId;
    u16* msgPtr;
    const char* path;
} MsgLookup;

u16* Message_PtrFromId(u16 msgId);
u16 Message_IdFromPtr(u16*);
s32 Message_GetWidth(u16* msgPtr);
s32 Message_GetCharCount(u16* msgPtr);
void Message_DisplayChar(Gfx** gfxPtr, u16 msgChar, s32 xpos, s32 ypos);
bool Message_DisplayText(Gfx** gfxPtr, u16* msgPtr, s32 xPos, s32 yPos, s32 len);
void Message_DisplayScrollingText(Gfx** gfxPtr, u16* msgPtr, s32 xPos, s32 yPos, s32 yRangeHi, s32 yRangeLo, s32 len);
bool Message_IsPrintingChar(u16* msgPtr, s32 charPos);

 // Id + 1 gives the other frame of the animation
typedef enum RadioCharacterId {
    RCID_FOX = 0,
    RCID_STATIC = 2,
    RCID_FOX_RED = 5,
    RCID_FALCO = 10,
    RCID_FALCO_RED = 15,
    RCID_SLIPPY = 20,
    RCID_SLIPPY_RED = 25,
    RCID_PEPPY = 30,
    RCID_PEPPY_RED = 35,
    RCID_KATT = 40,
    RCID_ANDROSS = 50,
    RCID_ANDROSS_RED = 55,
    RCID_JAMES = 60,
    RCID_GEN_PEPPER = 70,
    RCID_BOSS_CORNERIA = 80,
    RCID_ROB64 = 90,
    RCID_ROB64_RED = 95,
    RCID_BOSS_METEO = 100,
    RCID_BOSS_CORNERIA2 = 110,
    RCID_BOSS_AREA6 = 120,
    RCID_BOSS_ZONESS = 130,
    RCID_ROB64_2 = 140,
    RCID_BOSS_SECTORX = 150,
    RCID_BOSS_SECTORY = 160,
    RCID_BILL = 170,
    RCID_CAIMAN_AREA6 = 180,
    RCID_BOSS_MACBETH = 190,
    RCID_WOLF = 200,
    RCID_PIGMA = 210,
    RCID_LEON = 220,
    RCID_ANDREW = 230,
    RCID_WOLF_2 = 240,
    RCID_PIGMA_2 = 250,
    RCID_LEON_2 = 260,
    RCID_ANDREW_2 = 270,
    RCID_ROB64_TITLE = 300,
    RCID_GEN_PEPPER_TITLE = 310,
    RCID_TR = 350,
    RCID_FOX_EXPERT = 400,
    RCID_1000 = 1000,
} RadioCharacterId;

void Radio_PlayMessage(u16*, RadioCharacterId);
void Radio_CalculatePositions();
void func_radio_800BB388(void);
void Radio_Draw(void);

typedef enum MsgCharCode {
    // Non-printing and whitespace
    /*  0 */ MSGCHAR_END,       // End message
    /*  1 */ MSGCHAR_NWL,       // New line
    /*  2 */ MSGCHAR_NP2,       // No effect
    /*  3 */ MSGCHAR_NP3,       // No effect
    /*  4 */ MSGCHAR_NP4,       // No effect
    /*  5 */ MSGCHAR_NP5,       // No effect
    /*  6 */ MSGCHAR_NP6,       // No effect
    /*  7 */ MSGCHAR_NP7,       // No effect
    /*  8 */ MSGCHAR_PRI0,      // Set message priority
    /*  9 */ MSGCHAR_PRI1,      // Set message priority
    /* 10 */ MSGCHAR_PRI2,      // Set message priority
    /* 11 */ MSGCHAR_PRI3,      // Set message priority
    /* 12 */ MSGCHAR_SPC,       // Space
    /* 13 */ MSGCHAR_QSP,       // Quarter space
    /* 14 */ MSGCHAR_HSP,       // Half Space
    /* 15 */ MSGCHAR_NXT,       // Next text box

    // printing characters
    /* 16 */ MSGCHAR_CLF,       // C-Left
    /* 17 */ MSGCHAR_CUP,       // C-Up
    /* 18 */ MSGCHAR_CRT,       // C-Right
    /* 19 */ MSGCHAR_CDN,       // C-Down
    /* 20 */ MSGCHAR_AUP,       // Up arrow
    /* 21 */ MSGCHAR_ALF,       // Left arrow
    /* 22 */ MSGCHAR_ADN,       // Down arrow
    /* 23 */ MSGCHAR_ART,       // Right arrow
    /* 24 */ MSGCHAR_A,         // A
    /* 25 */ MSGCHAR_B,         // B
    /* 26 */ MSGCHAR_C,         // C
    /* 27 */ MSGCHAR_D,         // D
    /* 28 */ MSGCHAR_E,         // E
    /* 29 */ MSGCHAR_F,         // F
    /* 30 */ MSGCHAR_G,         // G
    /* 31 */ MSGCHAR_H,         // H
    /* 32 */ MSGCHAR_I,         // I
    /* 33 */ MSGCHAR_J,         // J
    /* 34 */ MSGCHAR_K,         // K
    /* 35 */ MSGCHAR_L,         // L
    /* 36 */ MSGCHAR_M,         // M
    /* 37 */ MSGCHAR_N,         // N
    /* 38 */ MSGCHAR_O,         // O
    /* 39 */ MSGCHAR_P,         // P
    /* 40 */ MSGCHAR_Q,         // Q
    /* 41 */ MSGCHAR_R,         // R
    /* 42 */ MSGCHAR_S,         // S
    /* 43 */ MSGCHAR_T,         // T
    /* 44 */ MSGCHAR_U,         // U
    /* 45 */ MSGCHAR_V,         // V
    /* 46 */ MSGCHAR_W,         // W
    /* 47 */ MSGCHAR_X,         // X
    /* 48 */ MSGCHAR_Y,         // Y
    /* 49 */ MSGCHAR_Z,         // Z
    /* 50 */ MSGCHAR_a,         // a
    /* 51 */ MSGCHAR_b,         // b
    /* 52 */ MSGCHAR_c,         // c
    /* 53 */ MSGCHAR_d,         // d
    /* 54 */ MSGCHAR_e,         // e
    /* 55 */ MSGCHAR_f,         // f
    /* 56 */ MSGCHAR_g,         // g
    /* 57 */ MSGCHAR_h,         // h
    /* 58 */ MSGCHAR_i,         // i
    /* 59 */ MSGCHAR_j,         // j
    /* 60 */ MSGCHAR_k,         // k
    /* 61 */ MSGCHAR_l,         // l
    /* 62 */ MSGCHAR_m,         // m
    /* 63 */ MSGCHAR_n,         // n
    /* 64 */ MSGCHAR_o,         // o
    /* 65 */ MSGCHAR_p,         // p
    /* 66 */ MSGCHAR_q,         // q
    /* 67 */ MSGCHAR_r,         // r
    /* 68 */ MSGCHAR_s,         // s
    /* 69 */ MSGCHAR_t,         // t
    /* 70 */ MSGCHAR_u,         // u
    /* 71 */ MSGCHAR_v,         // v
    /* 72 */ MSGCHAR_w,         // w
    /* 73 */ MSGCHAR_x,         // x
    /* 74 */ MSGCHAR_y,         // y
    /* 75 */ MSGCHAR_z,         // z
    /* 76 */ MSGCHAR_EXM,       // !
    /* 77 */ MSGCHAR_QST,       // ?
    /* 78 */ MSGCHAR_DSH,       // -
    /* 79 */ MSGCHAR_CMA,       // ,
    /* 80 */ MSGCHAR_PRD,       // .
    /* 81 */ MSGCHAR_0,         // 0
    /* 82 */ MSGCHAR_1,         // 1
    /* 83 */ MSGCHAR_2,         // 2
    /* 84 */ MSGCHAR_3,         // 3
    /* 85 */ MSGCHAR_4,         // 4
    /* 86 */ MSGCHAR_5,         // 5
    /* 87 */ MSGCHAR_6,         // 6
    /* 88 */ MSGCHAR_7,         // 7
    /* 89 */ MSGCHAR_8,         // 8
    /* 90 */ MSGCHAR_9,         // 9
    /* 91 */ MSGCHAR_APS,       // '
    /* 92 */ MSGCHAR_LPR,       // (
    /* 93 */ MSGCHAR_RPR,       // )
    /* 94 */ MSGCHAR_CLN,       // :

    // PAL exclusive characters
    /* 95 */ MSGCHAR_e_grave,   // è, placeholder in US
    /* 96 */ MSGCHAR_e_acute,   // é
    /* 97 */ MSGCHAR_a_grave,   // à
    /* 98 */ MSGCHAR_e_hat,     // ê
    /* 99 */ MSGCHAR_i_hat,     // î
    /*100 */ MSGCHAR_o_hat,     // ô
    /*101 */ MSGCHAR_i_umlaut,  // ï
    /*102 */ MSGCHAR_u_hat,     // û
    /*103 */ MSGCHAR_c_cedilla, // ç
    /*104 */ MSGCHAR_a_hat,     // â
    /*105 */ MSGCHAR_u_grave,   // ú
    /*106 */ MSGCHAR_u_umlaut,  // ü
    /*107 */ MSGCHAR_o_umlaut,  // ö
    /*108 */ MSGCHAR_a_umlaut,  // ä
    /*109 */ MSGCHAR_eszett,    // ß
    /*110 */ MSGCHAR_U_UMLAUT,  // Ü

    // PAL placeholder textures
    /*111 */ MSGCHAR_111,
    /*112 */ MSGCHAR_112,
    /*113 */ MSGCHAR_113,
    /*114 */ MSGCHAR_114,
    /*115 */ MSGCHAR_115,
    /*116 */ MSGCHAR_116,
    /*117 */ MSGCHAR_117,
    /*118 */ MSGCHAR_118,
    /*119 */ MSGCHAR_119,
    /*120 */ MSGCHAR_120,
    /*121 */ MSGCHAR_121,
    /*122 */ MSGCHAR_122,
    /*123 */ MSGCHAR_123,
    /*124 */ MSGCHAR_124,
    /*125 */ MSGCHAR_125,
    /*126 */ MSGCHAR_126,
    /*127 */ MSGCHAR_127,
} MsgCharCode;

typedef enum MsgMojiCode {
    // Non-printing and whitespace
    /*   0 */ MSGMOJI_0,
    /*   1 */ MSGMOJI_1,
    /*   2 */ MSGMOJI_2,
    /*   3 */ MSGMOJI_3,
    /*   4 */ MSGMOJI_4,
    /*   5 */ MSGMOJI_5,
    /*   6 */ MSGMOJI_6,
    /*   7 */ MSGMOJI_7,
    /*   8 */ MSGMOJI_8,
    /*   9 */ MSGMOJI_9,
    /*  10 */ MSGMOJI_10,
    /*  11 */ MSGMOJI_11,
    /*  12 */ MSGMOJI_12,
    /*  13 */ MSGMOJI_13,
    /*  14 */ MSGMOJI_14,
    /*  15 */ MSGMOJI_15,

    // Hiragana
    /*  16 */ MSGMOJI_16, // a
    /*  17 */ MSGMOJI_17, // A
    /*  18 */ MSGMOJI_18, // i
    /*  19 */ MSGMOJI_19, // I
    /*  20 */ MSGMOJI_20, // u
    /*  21 */ MSGMOJI_21, // U
    /*  22 */ MSGMOJI_22, // e
    /*  23 */ MSGMOJI_23, // E
    /*  24 */ MSGMOJI_24, // o
    /*  25 */ MSGMOJI_25, // O
    /*  26 */ MSGMOJI_26, // ga
    /*  27 */ MSGMOJI_27, // ka
    /*  28 */ MSGMOJI_28, // gi
    /*  29 */ MSGMOJI_29, // ki
    /*  30 */ MSGMOJI_30, // gu
    /*  31 */ MSGMOJI_31, // ku
    /*  32 */ MSGMOJI_32, // ge
    /*  33 */ MSGMOJI_33, // ke
    /*  34 */ MSGMOJI_34, // go
    /*  35 */ MSGMOJI_35, // ko
    /*  36 */ MSGMOJI_36, // za
    /*  37 */ MSGMOJI_37, // sa
    /*  38 */ MSGMOJI_38, // ji
    /*  39 */ MSGMOJI_39, // shi
    /*  40 */ MSGMOJI_40, // zu
    /*  41 */ MSGMOJI_41, // su
    /*  42 */ MSGMOJI_42, // ze
    /*  43 */ MSGMOJI_43, // se
    /*  44 */ MSGMOJI_44, // zo
    /*  45 */ MSGMOJI_45, // so
    /*  46 */ MSGMOJI_46, // da
    /*  47 */ MSGMOJI_47, // ta
    /*  48 */ MSGMOJI_48, // ji
    /*  49 */ MSGMOJI_49, // chi
    /*  50 */ MSGMOJI_50, // sokuon
    /*  51 */ MSGMOJI_51, // zu
    /*  52 */ MSGMOJI_52, // tsu
    /*  53 */ MSGMOJI_53, // de
    /*  54 */ MSGMOJI_54, // te
    /*  55 */ MSGMOJI_55, // do
    /*  56 */ MSGMOJI_56, // to
    /*  57 */ MSGMOJI_57, // na
    /*  58 */ MSGMOJI_58, // ni
    /*  59 */ MSGMOJI_59, // nu
    /*  60 */ MSGMOJI_60, // ne
    /*  61 */ MSGMOJI_61, // no
    /*  62 */ MSGMOJI_62, // ba
    /*  63 */ MSGMOJI_63, // pa
    /*  64 */ MSGMOJI_64, // ha
    /*  65 */ MSGMOJI_65, // bi
    /*  66 */ MSGMOJI_66, // pi
    /*  67 */ MSGMOJI_67, // hi
    /*  68 */ MSGMOJI_68, // bu
    /*  69 */ MSGMOJI_69, // pu
    /*  70 */ MSGMOJI_70, // fu
    /*  71 */ MSGMOJI_71, // be
    /*  72 */ MSGMOJI_72, // pe
    /*  73 */ MSGMOJI_73, // he
    /*  74 */ MSGMOJI_74, // bo
    /*  75 */ MSGMOJI_75, // po
    /*  76 */ MSGMOJI_76, // ho
    /*  77 */ MSGMOJI_77, // ma
    /*  78 */ MSGMOJI_78, // mi
    /*  79 */ MSGMOJI_79, // mu
    /*  80 */ MSGMOJI_80, // me
    /*  81 */ MSGMOJI_81, // mo
    /*  82 */ MSGMOJI_82, // ya
    /*  83 */ MSGMOJI_83, // Ya
    /*  84 */ MSGMOJI_84, // yu
    /*  85 */ MSGMOJI_85, // Yu
    /*  86 */ MSGMOJI_86, // yo
    /*  87 */ MSGMOJI_87, // Yo
    /*  88 */ MSGMOJI_88, // ra
    /*  89 */ MSGMOJI_89, // ri
    /*  90 */ MSGMOJI_90, // ru
    /*  91 */ MSGMOJI_91, // re
    /*  92 */ MSGMOJI_92, // ro
    /*  93 */ MSGMOJI_93, // wa
    /*  94 */ MSGMOJI_94, // wo
    /*  95 */ MSGMOJI_95, // n

    // Katakana
    /*  96 */ MSGMOJI_96,  // a
    /*  97 */ MSGMOJI_97,  // A
    /*  98 */ MSGMOJI_98,  // i
    /*  99 */ MSGMOJI_99,  // I
    /* 100 */ MSGMOJI_100, // u
    /* 101 */ MSGMOJI_101, // U
    /* 102 */ MSGMOJI_102, // e
    /* 103 */ MSGMOJI_103, // E
    /* 104 */ MSGMOJI_104, // o
    /* 105 */ MSGMOJI_105, // O
    /* 106 */ MSGMOJI_106, // ga
    /* 107 */ MSGMOJI_107, // ka
    /* 108 */ MSGMOJI_108, // gi
    /* 109 */ MSGMOJI_109, // ki
    /* 110 */ MSGMOJI_110, // gu
    /* 111 */ MSGMOJI_111, // ku
    /* 112 */ MSGMOJI_112, // ge
    /* 113 */ MSGMOJI_113, // ke
    /* 114 */ MSGMOJI_114, // go
    /* 115 */ MSGMOJI_115, // ko
    /* 116 */ MSGMOJI_116, // za
    /* 117 */ MSGMOJI_117, // sa
    /* 118 */ MSGMOJI_118, // ji
    /* 119 */ MSGMOJI_119, // shi
    /* 120 */ MSGMOJI_120, // zu
    /* 121 */ MSGMOJI_121, // su
    /* 122 */ MSGMOJI_122, // ze
    /* 123 */ MSGMOJI_123, // se
    /* 124 */ MSGMOJI_124, // zo
    /* 125 */ MSGMOJI_125, // so
    /* 126 */ MSGMOJI_126, // da
    /* 127 */ MSGMOJI_127, // ta
    /* 128 */ MSGMOJI_128, // dji
    /* 129 */ MSGMOJI_129, // chi
    /* 130 */ MSGMOJI_130, // sokuon
    /* 131 */ MSGMOJI_131, // dzu
    /* 132 */ MSGMOJI_132, // tsu
    /* 133 */ MSGMOJI_133, // de
    /* 134 */ MSGMOJI_134, // te
    /* 135 */ MSGMOJI_135, // do
    /* 136 */ MSGMOJI_136, // to
    /* 137 */ MSGMOJI_137, // na
    /* 138 */ MSGMOJI_138, // ni
    /* 139 */ MSGMOJI_139, // nu
    /* 140 */ MSGMOJI_140, // ne
    /* 141 */ MSGMOJI_141, // no
    /* 142 */ MSGMOJI_142, // ba
    /* 143 */ MSGMOJI_143, // pa
    /* 144 */ MSGMOJI_144, // ha
    /* 145 */ MSGMOJI_145, // bi
    /* 146 */ MSGMOJI_146, // pi
    /* 147 */ MSGMOJI_147, // hi
    /* 148 */ MSGMOJI_148, // bu
    /* 149 */ MSGMOJI_149, // pu
    /* 150 */ MSGMOJI_150, // fu
    /* 151 */ MSGMOJI_151, // be
    /* 152 */ MSGMOJI_152, // pe
    /* 153 */ MSGMOJI_153, // he
    /* 154 */ MSGMOJI_154, // bo
    /* 155 */ MSGMOJI_155, // po
    /* 156 */ MSGMOJI_156, // ho
    /* 157 */ MSGMOJI_157, // ma
    /* 158 */ MSGMOJI_158, // mi
    /* 159 */ MSGMOJI_159, // mu
    /* 160 */ MSGMOJI_160, // me
    /* 161 */ MSGMOJI_161, // mo
    /* 162 */ MSGMOJI_162, // ya
    /* 163 */ MSGMOJI_163, // Ya
    /* 164 */ MSGMOJI_164, // yu
    /* 165 */ MSGMOJI_165, // Yu
    /* 166 */ MSGMOJI_166, // yo
    /* 167 */ MSGMOJI_167, // Yo
    /* 168 */ MSGMOJI_168, // ra
    /* 169 */ MSGMOJI_169, // ri
    /* 170 */ MSGMOJI_170, // ru
    /* 171 */ MSGMOJI_171, // re
    /* 172 */ MSGMOJI_172, // ro
    /* 173 */ MSGMOJI_173, // wa
    /* 174 */ MSGMOJI_174, // wo
    /* 175 */ MSGMOJI_175, // n
    /* 176 */ MSGMOJI_176, // choonpu

    // Kanji and other symbols

    /* 177 */ MSGMOJI_177, // C-Left
    /* 178 */ MSGMOJI_178, // C-Right
    /* 179 */ MSGMOJI_179, // C-Down
    /* 180 */ MSGMOJI_180, // C-Up
    /* 181 */ MSGMOJI_181,
    /* 182 */ MSGMOJI_182,
    /* 183 */ MSGMOJI_183, // Numeral 4
    /* 184 */ MSGMOJI_184,
    /* 185 */ MSGMOJI_185,
    /* 186 */ MSGMOJI_186, // Center dot
    /* 187 */ MSGMOJI_187,
    /* 188 */ MSGMOJI_188,
    /* 189 */ MSGMOJI_189,
    /* 190 */ MSGMOJI_190,
    /* 191 */ MSGMOJI_191,
    /* 192 */ MSGMOJI_192,
    /* 193 */ MSGMOJI_193,
    /* 194 */ MSGMOJI_194,
    /* 195 */ MSGMOJI_195, // Latin D
    /* 196 */ MSGMOJI_196, // Latin r
    /* 197 */ MSGMOJI_197, // Period
    /* 198 */ MSGMOJI_198,
    /* 199 */ MSGMOJI_199,
    /* 200 */ MSGMOJI_200,
    /* 201 */ MSGMOJI_201,
    /* 202 */ MSGMOJI_202,
    /* 203 */ MSGMOJI_203,
    /* 204 */ MSGMOJI_204,
    /* 205 */ MSGMOJI_205,
    /* 206 */ MSGMOJI_206,
    /* 207 */ MSGMOJI_207,
    /* 208 */ MSGMOJI_208,
    /* 209 */ MSGMOJI_209,
    /* 210 */ MSGMOJI_210,
    /* 211 */ MSGMOJI_211,
    /* 212 */ MSGMOJI_212,
    /* 213 */ MSGMOJI_213,
    /* 214 */ MSGMOJI_214,
    /* 215 */ MSGMOJI_215,
    /* 216 */ MSGMOJI_216,
    /* 217 */ MSGMOJI_217, // Numeral 5
    /* 218 */ MSGMOJI_218,
    /* 219 */ MSGMOJI_219,
    /* 220 */ MSGMOJI_220,
    /* 221 */ MSGMOJI_221,
    /* 222 */ MSGMOJI_222,
    /* 223 */ MSGMOJI_223,
    /* 224 */ MSGMOJI_224,
    /* 225 */ MSGMOJI_225,
    /* 226 */ MSGMOJI_226, // Numeral 3
    /* 227 */ MSGMOJI_227,
    /* 228 */ MSGMOJI_228,
    /* 229 */ MSGMOJI_229,
    /* 230 */ MSGMOJI_230,
    /* 231 */ MSGMOJI_231,
    /* 232 */ MSGMOJI_232,
    /* 233 */ MSGMOJI_233,
    /* 234 */ MSGMOJI_234,
    /* 235 */ MSGMOJI_235,
    /* 236 */ MSGMOJI_236,
    /* 237 */ MSGMOJI_237,
    /* 238 */ MSGMOJI_238,
    /* 239 */ MSGMOJI_239,
    /* 240 */ MSGMOJI_240,
    /* 241 */ MSGMOJI_241,
    /* 242 */ MSGMOJI_242,
    /* 243 */ MSGMOJI_243,
    /* 244 */ MSGMOJI_244,
    /* 245 */ MSGMOJI_245,
    /* 246 */ MSGMOJI_246,
    /* 247 */ MSGMOJI_247,
    /* 248 */ MSGMOJI_248,
    /* 249 */ MSGMOJI_249,
    /* 250 */ MSGMOJI_250,
    /* 251 */ MSGMOJI_251,
    /* 252 */ MSGMOJI_252,
    /* 253 */ MSGMOJI_253,
    /* 254 */ MSGMOJI_254,
    /* 255 */ MSGMOJI_255,
    /* 256 */ MSGMOJI_256,
    /* 257 */ MSGMOJI_257,
    /* 258 */ MSGMOJI_258,
    /* 259 */ MSGMOJI_259,
    /* 260 */ MSGMOJI_260,
    /* 261 */ MSGMOJI_261,
    /* 262 */ MSGMOJI_262,
    /* 263 */ MSGMOJI_263,
    /* 264 */ MSGMOJI_264,
    /* 265 */ MSGMOJI_265,
    /* 266 */ MSGMOJI_266,
    /* 267 */ MSGMOJI_267, // !
    /* 268 */ MSGMOJI_268,
    /* 269 */ MSGMOJI_269,
    /* 270 */ MSGMOJI_270,
    /* 271 */ MSGMOJI_271,
    /* 272 */ MSGMOJI_272,
    /* 273 */ MSGMOJI_273,
    /* 274 */ MSGMOJI_274,
    /* 275 */ MSGMOJI_275,
    /* 276 */ MSGMOJI_276,
    /* 277 */ MSGMOJI_277,
    /* 278 */ MSGMOJI_278,
    /* 279 */ MSGMOJI_279,
    /* 280 */ MSGMOJI_280,
    /* 281 */ MSGMOJI_281,
    /* 282 */ MSGMOJI_282,
    /* 283 */ MSGMOJI_283,
    /* 284 */ MSGMOJI_284,
    /* 285 */ MSGMOJI_285,
    /* 286 */ MSGMOJI_286,
    /* 287 */ MSGMOJI_287,
    /* 288 */ MSGMOJI_288,
    /* 289 */ MSGMOJI_289,
    /* 290 */ MSGMOJI_290,
    /* 291 */ MSGMOJI_291,
    /* 292 */ MSGMOJI_292, // ?
    /* 293 */ MSGMOJI_293,
    /* 294 */ MSGMOJI_294,
    /* 295 */ MSGMOJI_295,
    /* 296 */ MSGMOJI_296,
    /* 297 */ MSGMOJI_297,
    /* 298 */ MSGMOJI_298,
    /* 299 */ MSGMOJI_299,
    /* 300 */ MSGMOJI_300,
    /* 301 */ MSGMOJI_301,
    /* 302 */ MSGMOJI_302,
    /* 303 */ MSGMOJI_303,
    /* 304 */ MSGMOJI_304,
    /* 305 */ MSGMOJI_305,
    /* 306 */ MSGMOJI_306,
    /* 307 */ MSGMOJI_307,
    /* 308 */ MSGMOJI_308,
    /* 309 */ MSGMOJI_309,
    /* 310 */ MSGMOJI_310,
    /* 311 */ MSGMOJI_311,
    /* 312 */ MSGMOJI_312,
    /* 313 */ MSGMOJI_313,
    /* 314 */ MSGMOJI_314,
    /* 315 */ MSGMOJI_315,
    /* 316 */ MSGMOJI_316,
    /* 317 */ MSGMOJI_317,
    /* 318 */ MSGMOJI_318,
    /* 319 */ MSGMOJI_319,
    /* 320 */ MSGMOJI_320,
    /* 321 */ MSGMOJI_321,
    /* 322 */ MSGMOJI_322,
    /* 323 */ MSGMOJI_323,
    /* 324 */ MSGMOJI_324,
    /* 325 */ MSGMOJI_325,
    /* 326 */ MSGMOJI_326,
    /* 327 */ MSGMOJI_327,
    /* 328 */ MSGMOJI_328,
    /* 329 */ MSGMOJI_329,
    /* 330 */ MSGMOJI_330,
    /* 331 */ MSGMOJI_331,
    /* 332 */ MSGMOJI_332,
    /* 333 */ MSGMOJI_333,
    /* 334 */ MSGMOJI_334,
    /* 335 */ MSGMOJI_335,
    /* 336 */ MSGMOJI_336,
    /* 337 */ MSGMOJI_337,
    /* 338 */ MSGMOJI_338,
    /* 339 */ MSGMOJI_339,
    /* 340 */ MSGMOJI_340,
    /* 341 */ MSGMOJI_341,
    /* 342 */ MSGMOJI_342,
    /* 343 */ MSGMOJI_343, // Latin Y
    /* 344 */ MSGMOJI_344,
    /* 345 */ MSGMOJI_345,
    /* 346 */ MSGMOJI_346,
    /* 347 */ MSGMOJI_347,
    /* 348 */ MSGMOJI_348,
    /* 349 */ MSGMOJI_349,
    /* 350 */ MSGMOJI_350,
    /* 351 */ MSGMOJI_351,
    /* 352 */ MSGMOJI_352,
    /* 353 */ MSGMOJI_353,
    /* 354 */ MSGMOJI_354,
    /* 355 */ MSGMOJI_355,
    /* 356 */ MSGMOJI_356,
    /* 357 */ MSGMOJI_357,
    /* 358 */ MSGMOJI_358,
    /* 359 */ MSGMOJI_359,
    /* 360 */ MSGMOJI_360, // Latin G
    /* 361 */ MSGMOJI_361,
    /* 362 */ MSGMOJI_362,
    /* 363 */ MSGMOJI_363,
    /* 364 */ MSGMOJI_364,
    /* 365 */ MSGMOJI_365, // Latin O
    /* 366 */ MSGMOJI_366, // Latin K
    /* 367 */ MSGMOJI_367, 
    /* 368 */ MSGMOJI_368,
    /* 369 */ MSGMOJI_369,
    /* 370 */ MSGMOJI_370,
    /* 371 */ MSGMOJI_371, // ~
    /* 372 */ MSGMOJI_372,
    /* 373 */ MSGMOJI_373,
    /* 374 */ MSGMOJI_374,
    /* 375 */ MSGMOJI_375, // Latin Z
    /* 376 */ MSGMOJI_376, // Latin R
    /* 377 */ MSGMOJI_377, // Numeral 2
    /* 378 */ MSGMOJI_378,
    /* 379 */ MSGMOJI_379,
    /* 380 */ MSGMOJI_380,
    /* 381 */ MSGMOJI_381, // Latin C
    /* 382 */ MSGMOJI_382,
    /* 383 */ MSGMOJI_383,
    /* 384 */ MSGMOJI_384,
    /* 385 */ MSGMOJI_385,
    /* 386 */ MSGMOJI_386,
    /* 387 */ MSGMOJI_387,
    /* 388 */ MSGMOJI_388,
    /* 389 */ MSGMOJI_389,
    /* 390 */ MSGMOJI_390,
    /* 391 */ MSGMOJI_391,
    /* 392 */ MSGMOJI_392,
    /* 393 */ MSGMOJI_393,
    /* 394 */ MSGMOJI_394,
    /* 395 */ MSGMOJI_395,
    /* 396 */ MSGMOJI_396,
    /* 397 */ MSGMOJI_397,
    /* 398 */ MSGMOJI_398,
    /* 399 */ MSGMOJI_399,
    /* 400 */ MSGMOJI_400,
    /* 401 */ MSGMOJI_401,
    /* 402 */ MSGMOJI_402,
    /* 403 */ MSGMOJI_403,
    /* 404 */ MSGMOJI_404,
    /* 405 */ MSGMOJI_405,
    /* 406 */ MSGMOJI_406,
    /* 407 */ MSGMOJI_407,
    /* 408 */ MSGMOJI_408,
    /* 409 */ MSGMOJI_409,
    /* 410 */ MSGMOJI_410,
    /* 411 */ MSGMOJI_411,
    /* 412 */ MSGMOJI_412,
    /* 413 */ MSGMOJI_413,
    /* 414 */ MSGMOJI_414,
    /* 415 */ MSGMOJI_415,
    /* 416 */ MSGMOJI_416,
    /* 417 */ MSGMOJI_417,
    /* 418 */ MSGMOJI_418,
    /* 419 */ MSGMOJI_419,
    /* 420 */ MSGMOJI_420,
    /* 421 */ MSGMOJI_421,
    /* 422 */ MSGMOJI_422,
    /* 423 */ MSGMOJI_423,
    /* 424 */ MSGMOJI_424,
    /* 425 */ MSGMOJI_425,
    /* 426 */ MSGMOJI_426,
    /* 427 */ MSGMOJI_427,
    /* 428 */ MSGMOJI_428,
    /* 429 */ MSGMOJI_429,
    /* 430 */ MSGMOJI_430,
    /* 431 */ MSGMOJI_431,
    /* 432 */ MSGMOJI_432,
    /* 433 */ MSGMOJI_433,
    /* 434 */ MSGMOJI_434,
    /* 435 */ MSGMOJI_435,
    /* 436 */ MSGMOJI_436, // Numeral 1
    /* 437 */ MSGMOJI_437,
    /* 438 */ MSGMOJI_438,
    /* 439 */ MSGMOJI_439,
    /* 440 */ MSGMOJI_440,
    /* 441 */ MSGMOJI_441,
    /* 442 */ MSGMOJI_442,
    /* 443 */ MSGMOJI_443,
    /* 444 */ MSGMOJI_444,
    /* 445 */ MSGMOJI_445,
    /* 446 */ MSGMOJI_446,
    /* 447 */ MSGMOJI_447,
    /* 448 */ MSGMOJI_448,
    /* 449 */ MSGMOJI_449,
    /* 450 */ MSGMOJI_450,
    /* 451 */ MSGMOJI_451,
    /* 452 */ MSGMOJI_452,
    /* 453 */ MSGMOJI_453,
    /* 454 */ MSGMOJI_454,
    /* 455 */ MSGMOJI_455,
    /* 456 */ MSGMOJI_456,
    /* 457 */ MSGMOJI_457,
    /* 458 */ MSGMOJI_458,
    /* 459 */ MSGMOJI_459,
    /* 460 */ MSGMOJI_460,
    /* 461 */ MSGMOJI_461,
    /* 462 */ MSGMOJI_462,
    /* 463 */ MSGMOJI_463,
    /* 464 */ MSGMOJI_464,
    /* 465 */ MSGMOJI_465,
    /* 466 */ MSGMOJI_466,
    /* 467 */ MSGMOJI_467,
    /* 468 */ MSGMOJI_468,
    /* 469 */ MSGMOJI_469,
    /* 470 */ MSGMOJI_470,
    /* 471 */ MSGMOJI_471,
    /* 472 */ MSGMOJI_472,
    /* 473 */ MSGMOJI_473,
    /* 474 */ MSGMOJI_474,
    /* 475 */ MSGMOJI_475,
    /* 476 */ MSGMOJI_476,
    /* 477 */ MSGMOJI_477,
    /* 478 */ MSGMOJI_478,
    /* 479 */ MSGMOJI_479,
    /* 480 */ MSGMOJI_480,
    /* 481 */ MSGMOJI_481,
    /* 482 */ MSGMOJI_482,
    /* 483 */ MSGMOJI_483,
    /* 484 */ MSGMOJI_484,
    /* 485 */ MSGMOJI_485,
    /* 486 */ MSGMOJI_486,
    /* 487 */ MSGMOJI_487,
    /* 488 */ MSGMOJI_488,
    /* 489 */ MSGMOJI_489,
    /* 490 */ MSGMOJI_490,
    /* 491 */ MSGMOJI_491,
    /* 492 */ MSGMOJI_492,
    /* 493 */ MSGMOJI_493,
    /* 494 */ MSGMOJI_494,
    /* 495 */ MSGMOJI_495,
    /* 496 */ MSGMOJI_496,
    /* 497 */ MSGMOJI_497,
    /* 498 */ MSGMOJI_498,
    /* 499 */ MSGMOJI_499,
    /* 500 */ MSGMOJI_500,
    /* 501 */ MSGMOJI_501,
    /* 502 */ MSGMOJI_502,
    /* 503 */ MSGMOJI_503,
    /* 504 */ MSGMOJI_504,
    /* 505 */ MSGMOJI_505,
    /* 506 */ MSGMOJI_506,
    /* 507 */ MSGMOJI_507,
    /* 508 */ MSGMOJI_508,
    /* 509 */ MSGMOJI_509,
    /* 510 */ MSGMOJI_510,
    /* 511 */ MSGMOJI_511,
    /* 512 */ MSGMOJI_512,
    /* 513 */ MSGMOJI_513,
    /* 514 */ MSGMOJI_514,
    /* 515 */ MSGMOJI_515,
    /* 516 */ MSGMOJI_516,
    /* 517 */ MSGMOJI_517,
    /* 518 */ MSGMOJI_518,
    /* 519 */ MSGMOJI_519,
    /* 520 */ MSGMOJI_520,
    /* 521 */ MSGMOJI_521,
    /* 522 */ MSGMOJI_522,
    /* 523 */ MSGMOJI_523,
    /* 524 */ MSGMOJI_524, // Numeral 0
    /* 525 */ MSGMOJI_525,
    /* 526 */ MSGMOJI_526,
    /* 527 */ MSGMOJI_527,
    /* 528 */ MSGMOJI_528,
    /* 529 */ MSGMOJI_529,
    /* 530 */ MSGMOJI_530,
    /* 531 */ MSGMOJI_531,
    /* 532 */ MSGMOJI_532,
    /* 533 */ MSGMOJI_533,
    /* 534 */ MSGMOJI_534,
    /* 535 */ MSGMOJI_535,
    /* 536 */ MSGMOJI_536,
    /* 537 */ MSGMOJI_537,
    /* 538 */ MSGMOJI_538,
    /* 539 */ MSGMOJI_539,
    /* 540 */ MSGMOJI_540,
    /* 541 */ MSGMOJI_541,
    /* 542 */ MSGMOJI_542,
    /* 543 */ MSGMOJI_543,
    /* 544 */ MSGMOJI_544,
    /* 545 */ MSGMOJI_545,
    /* 546 */ MSGMOJI_546,
    /* 547 */ MSGMOJI_547,
    /* 548 */ MSGMOJI_548,
    /* 549 */ MSGMOJI_549,
    /* 550 */ MSGMOJI_550,
    /* 551 */ MSGMOJI_551,
    /* 552 */ MSGMOJI_552,
    /* 553 */ MSGMOJI_553,
    /* 554 */ MSGMOJI_554,
    /* 555 */ MSGMOJI_555,
    /* 556 */ MSGMOJI_556,
    /* 557 */ MSGMOJI_557,
    /* 558 */ MSGMOJI_558,
    /* 559 */ MSGMOJI_559,
    /* 560 */ MSGMOJI_560,
    /* 561 */ MSGMOJI_561,
    /* 562 */ MSGMOJI_562,
    /* 563 */ MSGMOJI_563,
    /* 564 */ MSGMOJI_564,
    /* 565 */ MSGMOJI_565,
    /* 566 */ MSGMOJI_566,
    /* 567 */ MSGMOJI_567,
    /* 568 */ MSGMOJI_568,
    /* 569 */ MSGMOJI_569,
    /* 570 */ MSGMOJI_570,
    /* 571 */ MSGMOJI_571,
    /* 572 */ MSGMOJI_572,
    /* 573 */ MSGMOJI_573,
    /* 574 */ MSGMOJI_574,
    /* 575 */ MSGMOJI_575,
    /* 576 */ MSGMOJI_576,
    /* 577 */ MSGMOJI_577,
    /* 578 */ MSGMOJI_578,
    /* 579 */ MSGMOJI_579,
    /* 580 */ MSGMOJI_580,
    /* 581 */ MSGMOJI_581,
    /* 582 */ MSGMOJI_582,
    /* 583 */ MSGMOJI_583,
    /* 584 */ MSGMOJI_584,
    /* 585 */ MSGMOJI_585,
    /* 586 */ MSGMOJI_586,
    /* 587 */ MSGMOJI_587,
    /* 588 */ MSGMOJI_588,
    /* 589 */ MSGMOJI_589,
    /* 590 */ MSGMOJI_590,
    /* 591 */ MSGMOJI_591,
    /* 592 */ MSGMOJI_592,
    /* 593 */ MSGMOJI_593,
    /* 594 */ MSGMOJI_594,
    /* 595 */ MSGMOJI_595,
    /* 596 */ MSGMOJI_596,
    /* 597 */ MSGMOJI_597,
    /* 598 */ MSGMOJI_598,
    /* 599 */ MSGMOJI_599,
    /* 600 */ MSGMOJI_600,
    /* 601 */ MSGMOJI_601,
    /* 602 */ MSGMOJI_602,
    /* 603 */ MSGMOJI_603, // Numeral 9
    /* 604 */ MSGMOJI_604,
    /* 605 */ MSGMOJI_605,
    /* 606 */ MSGMOJI_606,
    /* 607 */ MSGMOJI_607, // Numeral 6
    /* 608 */ MSGMOJI_608,
    /* 609 */ MSGMOJI_609, // Numeral 8
    /* 610 */ MSGMOJI_610,
    /* 611 */ MSGMOJI_611,
    /* 612 */ MSGMOJI_612,
    /* 613 */ MSGMOJI_613,
    /* 614 */ MSGMOJI_614,
    /* 615 */ MSGMOJI_615,
    /* 616 */ MSGMOJI_616,
    /* 617 */ MSGMOJI_617,
    /* 618 */ MSGMOJI_618,
    /* 619 */ MSGMOJI_619,
    /* 620 */ MSGMOJI_620,
    /* 621 */ MSGMOJI_621,
    /* 622 */ MSGMOJI_622,
    /* 623 */ MSGMOJI_623,
    /* 624 */ MSGMOJI_624,
    /* 625 */ MSGMOJI_625,
    /* 626 */ MSGMOJI_626,
    /* 627 */ MSGMOJI_627,
    /* 628 */ MSGMOJI_628,
    /* 629 */ MSGMOJI_629,
    /* 630 */ MSGMOJI_630,
    /* 631 */ MSGMOJI_631,
    /* 632 */ MSGMOJI_632,
    /* 633 */ MSGMOJI_633,
    /* 634 */ MSGMOJI_634,
    /* 635 */ MSGMOJI_635,
    /* 636 */ MSGMOJI_636,
    /* 637 */ MSGMOJI_637,
    /* 638 */ MSGMOJI_638,
    /* 639 */ MSGMOJI_639,
    /* 640 */ MSGMOJI_640,
    /* 641 */ MSGMOJI_641,
    /* 642 */ MSGMOJI_642,
    /* 643 */ MSGMOJI_643,
    /* 644 */ MSGMOJI_644,
    /* 645 */ MSGMOJI_645,
    /* 646 */ MSGMOJI_646,
    /* 647 */ MSGMOJI_647,
    /* 648 */ MSGMOJI_648,
    /* 649 */ MSGMOJI_649,
    /* 650 */ MSGMOJI_650,
    /* 651 */ MSGMOJI_651,
    /* 652 */ MSGMOJI_652,
    /* 653 */ MSGMOJI_653,
    /* 654 */ MSGMOJI_654,
    /* 655 */ MSGMOJI_655,
    /* 656 */ MSGMOJI_656,
    /* 657 */ MSGMOJI_657,
    /* 658 */ MSGMOJI_658,
    /* 659 */ MSGMOJI_659,
    /* 660 */ MSGMOJI_660,
    /* 661 */ MSGMOJI_661,
    /* 662 */ MSGMOJI_662,
    /* 663 */ MSGMOJI_663,
    /* 664 */ MSGMOJI_664,
    /* 665 */ MSGMOJI_665,
    /* 666 */ MSGMOJI_666,
    /* 667 */ MSGMOJI_667,
    /* 668 */ MSGMOJI_668,
    /* 669 */ MSGMOJI_669,
    /* 670 */ MSGMOJI_670,
    /* 671 */ MSGMOJI_671,
    /* 672 */ MSGMOJI_672,
    /* 673 */ MSGMOJI_673,
    /* 674 */ MSGMOJI_674,
    /* 675 */ MSGMOJI_675,
    /* 676 */ MSGMOJI_676,
    /* 677 */ MSGMOJI_677,
    /* 678 */ MSGMOJI_678,
    /* 679 */ MSGMOJI_679,
    /* 680 */ MSGMOJI_680,
    /* 681 */ MSGMOJI_681,
    /* 682 */ MSGMOJI_682,
    /* 683 */ MSGMOJI_683,
    /* 684 */ MSGMOJI_684,
    /* 685 */ MSGMOJI_685,
    /* 686 */ MSGMOJI_686,
    /* 687 */ MSGMOJI_687,
    /* 688 */ MSGMOJI_688,
    /* 689 */ MSGMOJI_689,
    /* 690 */ MSGMOJI_690,
    /* 691 */ MSGMOJI_691, // Latin B
    /* 692 */ MSGMOJI_692,
    /* 693 */ MSGMOJI_693,
    /* 694 */ MSGMOJI_694,
    /* 695 */ MSGMOJI_695,
    /* 696 */ MSGMOJI_696,
    /* 697 */ MSGMOJI_697,
    /* 698 */ MSGMOJI_698,
    /* 699 */ MSGMOJI_699,
    /* 700 */ MSGMOJI_700, // Latin A
    /* 701 */ MSGMOJI_701,
    /* 702 */ MSGMOJI_702,
    /* 703 */ MSGMOJI_703,
    /* 704 */ MSGMOJI_704,
    /* 705 */ MSGMOJI_705,
    /* 706 */ MSGMOJI_706,
    /* 707 */ MSGMOJI_707,
    /* 708 */ MSGMOJI_708,
    /* 709 */ MSGMOJI_709,
    /* 710 */ MSGMOJI_710,
    /* 711 */ MSGMOJI_711,
    /* 712 */ MSGMOJI_712,
    /* 713 */ MSGMOJI_713,
    /* 714 */ MSGMOJI_714,
    /* 715 */ MSGMOJI_715, // Latin U
    /* 716 */ MSGMOJI_716,
    /* 717 */ MSGMOJI_717,
    /* 718 */ MSGMOJI_718,
    /* 719 */ MSGMOJI_719,
    /* 720 */ MSGMOJI_720,
    /* 721 */ MSGMOJI_721,
    /* 722 */ MSGMOJI_722,
    /* 723 */ MSGMOJI_723,
    /* 724 */ MSGMOJI_724, // Latin P
    /* 725 */ MSGMOJI_725,
    /* 726 */ MSGMOJI_726,

    // Blank textures
    /* 727 */ MSGMOJI_727,
    /* 728 */ MSGMOJI_728,
    /* 729 */ MSGMOJI_729,
    /* 730 */ MSGMOJI_730,
    /* 731 */ MSGMOJI_731,
    /* 732 */ MSGMOJI_732,
    /* 733 */ MSGMOJI_733,
    /* 734 */ MSGMOJI_734,
    /* 735 */ MSGMOJI_735,
} MsgMojiCode;

#endif
