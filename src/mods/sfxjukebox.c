#include "global.h"
#include "fox_map.h"
#include "fox_option.h"

extern s32 spectrumAnalizerMode;
extern bool D_menu_801B9320;
extern s32 D_menu_801B9244;
extern OptionId D_menu_801B9124;
extern s32 D_menu_801B912C;

u32 prevSfx = 0;
u32 sfx = 0x09000000;
s32 sfxId = 0;
s32 sfxBank = 0;
int holdTimer = 0;

void decimalToHex(int num, char* hexString, size_t hexStringLength) {
    int i;
    // Define hexadecimal digits
    char hexDigits[] = "0123456789ABCDEF";
    // Check for null pointer or insufficient buffer size
    if (hexString == NULL || hexStringLength < 9) {
        // You might need to adjust the buffer size based on the maximum expected length
        return;
    }

    // Ensure the buffer is null-terminated
    hexString[8] = '\0';

    // Iterate through each hex digit
    for (i = 7; i >= 0; --i) {
        // Extract the 4 bits representing one hex digit
        int hexValue = (num >> (i * 4)) & 0xF;

        // Convert the 4-bit value to its corresponding hex character
        hexString[7 - i] = hexDigits[hexValue];
    }
}

void Option_JukeboxSoundUpdate(void) {
    char hexString[9]; // Buffer to store the hexadecimal string

    if ((gControllerPress[gMainController].button & R_TRIG) && (sfxBank < 4)) {
        sfxBank++;
    } else if ((gControllerPress[gMainController].button & L_TRIG) && (sfxBank > 0)) {
        sfxBank--;
    }
    sfx &= 0x0FFFFFFF;
    sfx |= (sfxBank << 28);

    if (gControllerHold[gMainController].button & (U_JPAD | D_JPAD)) {
        holdTimer++;
    } else {
        holdTimer = 0;
    }

    if (((gControllerHold[gMainController].button & U_JPAD) && (holdTimer > 15)) ||
        (gControllerPress[gMainController].button & U_JPAD)) {
        sfxId++;
    } else if (((gControllerHold[gMainController].button & D_JPAD) && (holdTimer > 15)) ||
               (gControllerPress[gMainController].button & D_JPAD)) {
        sfxId--;
    } else if (gControllerPress[gMainController].button & L_JPAD) {
        sfxId -= 0x10;
    } else if (gControllerPress[gMainController].button & R_JPAD) {
        sfxId += 0x10;
    }

    if (((sfxBank == 0) || (sfxBank == 4)) && (sfxId > 0x3F)) {
        sfxId = 0x3F;
    } else if (((sfxBank == 2) || (sfxBank == 3)) && (sfxId > 0xA7)) {
        sfxId = 0xA7;
    } else if ((sfxBank == 1) && (sfxId > 0x8F)) {
        sfxId = 0x8F;
    } else if (sfxId < 0) {
        sfxId = 0;
    }
    sfx &= 0xFFFFFF00;
    sfx |= sfxId & 0xFF;

    if (prevSfx != sfx) {
        AUDIO_PLAY_SFX(0x49000002, gDefaultSfxSource, 4);
        prevSfx = sfx;
    }

    decimalToHex(sfx, hexString, sizeof(hexString));

    if (gControllerPress[gMainController].button & A_BUTTON) {
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
        SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
        AUDIO_PLAY_SFX(sfx, gDefaultSfxSource, 4);
        D_menu_801B9320 = true;
    }

    if (gControllerPress[gMainController].button & B_BUTTON) {
        if (!D_menu_801B9320) {
            AUDIO_PLAY_BGM(SEQ_ID_MENU);
            gDrawMode = DRAW_NONE;
            D_menu_801B9124 = 1000;
            D_menu_801B912C = 0;
            D_menu_801B9244 = 1;
        } else {
            AUDIO_PLAY_SFX(0x4900101D, gDefaultSfxSource, 4);
            Audio_KillSfxBySource(gDefaultSfxSource);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_BGM, 1);
            SEQCMD_STOP_SEQUENCE(SEQ_PLAYER_FANFARE, 1);
            D_menu_801B9320 = false;
        }
    }

    // Spectrum Analizer mode selector
    if (gControllerPress[gMainController].button & R_CBUTTONS) {
        spectrumAnalizerMode++;
        if (spectrumAnalizerMode > 2) {
            spectrumAnalizerMode = 0;
        }
    }

    /* Draw */

    RCP_SetupDL(&gMasterDisp, 0x53);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);

    Graphics_DisplaySmallText(20, 50, 1.0f, 1.0f, "SFX ID:");
    Graphics_DisplaySmallText(80, 50, 1.0f, 1.0f, hexString);
}
