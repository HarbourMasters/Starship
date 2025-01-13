#include "global.h"

SaveFile gSaveFile;

// clang-format off

Save gDefaultSave = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // PlanetData

    0x01, 0x02, 0x03, 0x04, // pad10

    SOUNDMODE_STEREO,
    99, // musicVolume
    99, // voiceVolume
    99, // sfxVolume
    
    // rankNameEntry
    'F', 'O', 'X', 
    'P', 'E', 'P', 
    'S', 'L', 'P', 
    'F', 'A', 'L', 
    'W', 'L', 'F', 
    'L', 'O', 'N', 
    'P', 'I', 'G', 
    'A', 'N', 'R', 
    'B', 'I', 'L', 
    'K', 'A', 'T', 

    // rankingRoute
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1,

    // rankingLives
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    // rankingMedal
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

    // stats
    PLANET_STATS(100, PLANET_CORNERIA, false, false, false), 
    PLANET_STATS(9, PLANET_SECTOR_Y, true, true, true), 
    PLANET_STATS(9, PLANET_AQUAS, true, true, true), 
    PLANET_STATS(9, PLANET_ZONESS, true, true, true), 
    PLANET_STATS(9, PLANET_SECTOR_Z, true, true, true), 
    PLANET_STATS(9, PLANET_AREA_6, true, true, true), 
    PLANET_STATS(9, SAVE_SLOT_VENOM_2, true, true, true), 

    PLANET_STATS(90, PLANET_CORNERIA, false, false, false), 
    PLANET_STATS(9, PLANET_SECTOR_Y, true, false, false), 
    PLANET_STATS(9, PLANET_KATINA, true, false, false), 
    PLANET_STATS(9, PLANET_VENOM, true, false, false), 
    PLANET_STATS(9, PLANET_MACBETH, true, false, false), 
    PLANET_STATS(9, PLANET_AREA_6, true, false, false), 
    PLANET_STATS(9, SAVE_SLOT_VENOM_2, true, false, false), 

    PLANET_STATS(80, PLANET_CORNERIA, false, false, false),
    PLANET_STATS(9, PLANET_METEO, false, true, false),
    PLANET_STATS(9, PLANET_FORTUNA, false, true, false),
    PLANET_STATS(9, PLANET_SECTOR_X, false, true, false),
    PLANET_STATS(9, PLANET_TITANIA, false, true, false),
    PLANET_STATS(9, PLANET_BOLSE, false, true, false),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, false, true, false),

    PLANET_STATS(70, PLANET_CORNERIA, false, false, false), 
    PLANET_STATS(9, PLANET_METEO, false, false, true),
    PLANET_STATS(9, PLANET_FORTUNA, false, false, true),
    PLANET_STATS(9, PLANET_SECTOR_X, false, false, true),
    PLANET_STATS(9, PLANET_TITANIA, false, false, true),
    PLANET_STATS(9, PLANET_BOLSE, false, false, true),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, false, false, true),

    PLANET_STATS(60, PLANET_CORNERIA, false, false, false), 
    PLANET_STATS(9, PLANET_METEO, true, false, true),
    PLANET_STATS(9, PLANET_FORTUNA, true, false, true),
    PLANET_STATS(9, PLANET_SECTOR_X, true, false, true),
    PLANET_STATS(9, PLANET_TITANIA, true, false, true),
    PLANET_STATS(9, PLANET_BOLSE, true, false, true),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, true, false, true),

    PLANET_STATS(50, PLANET_CORNERIA, false, false, false), 
    PLANET_STATS(4, PLANET_METEO, false, true, true),
    PLANET_STATS(9, PLANET_FORTUNA, false, true, true),
    PLANET_STATS(9, PLANET_SECTOR_X, false, true, true),
    PLANET_STATS(9, PLANET_TITANIA, false, true, true),
    PLANET_STATS(9, PLANET_BOLSE, false, true, true),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, false, true, true),

    PLANET_STATS(40, PLANET_CORNERIA, false, false, false), 
    PLANET_STATS(1, PLANET_METEO, true, true, false),
    PLANET_STATS(2, PLANET_FORTUNA, true, true, false),
    PLANET_STATS(9, PLANET_SECTOR_X, true, true, false),
    PLANET_STATS(9, PLANET_TITANIA, true, true, false),
    PLANET_STATS(9, PLANET_BOLSE, true, true, false),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, true, true, false),

    PLANET_STATS(30, PLANET_CORNERIA, false, false, false),
    PLANET_STATS(1, PLANET_METEO, false, true, false),
    PLANET_STATS(1, PLANET_FORTUNA, true, false, false),
    PLANET_STATS(1, PLANET_SECTOR_X, true, true, true),
    PLANET_STATS(8, PLANET_TITANIA, true, false, true),
    PLANET_STATS(9, PLANET_BOLSE, false, true, true),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, true, true, false),

    PLANET_STATS(20, PLANET_CORNERIA, false, false, false),
    PLANET_STATS(1, PLANET_METEO, false, true, true),
    PLANET_STATS(1, PLANET_FORTUNA, true, false, true),
    PLANET_STATS(1, PLANET_SECTOR_X, true, true, true),
    PLANET_STATS(1, PLANET_TITANIA, true, false, false),
    PLANET_STATS(6, PLANET_BOLSE, false, true, false),
    PLANET_STATS(9, SAVE_SLOT_VENOM_1, false, false, true),

    PLANET_STATS(10, PLANET_CORNERIA, false, false, false),
    PLANET_STATS(1, PLANET_METEO, true, true, true),
    PLANET_STATS(1, PLANET_FORTUNA, true, false, false),
    PLANET_STATS(1, PLANET_SECTOR_X, true, false, false),
    PLANET_STATS(1, PLANET_TITANIA, false, true, false),
    PLANET_STATS(1, PLANET_BOLSE, false, false, true),
    PLANET_STATS(4, SAVE_SLOT_VENOM_1, true, false, true),
    
    // unk_EA
    0xFF,

    // padding
    0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09,
};
// clang-format on

u16 Save_Checksum(Save* arg0) {
    u16 var_v1;
    s32 i;

    for (i = 0, var_v1 = 0; i < sizeof(SaveData); i++) {
        var_v1 ^= arg0->raw[i];
        var_v1 <<= 1;
        var_v1 = (var_v1 & 0xFE) | ((var_v1 >> 8) & 1);
    }

    var_v1 = (var_v1 & 0xFF) | 0x9500;

    return var_v1;
}

s32 Save_Write(void) {
    OSMesg sp1C;

    gSaveFile.save.checksum = Save_Checksum(&gSaveFile.save);
    gSaveFile.backup = gSaveFile.save;
    gSaveIOBuffer = gSaveFile;
    return Save_WriteData();
}

s32 Save_Read(void) {
    OSMesg* sp24;
    s32 i;

    //if(!Save_ReadData()) {
    //    return 0;
    //}

    Save_ReadData();

    gSaveFile = gSaveIOBuffer;

    if (gSaveFile.save.checksum == Save_Checksum(&gSaveFile.save)) {
        PRINTF("ＥＥＰＲＯＭ ＲＯＭ［０］ 正常\n");
        return 0;
    }
#ifdef AVOID_UB
    for (i = 0; i < sizeof(SaveData); i++) {
#else
    for (i = 0; i <= sizeof(SaveData); i++) { // should be <, but gets overwritten immediately.
#endif
        gSaveFile.save.raw[i] = gSaveFile.backup.raw[i];
    }
    gSaveFile.save.checksum = gSaveFile.backup.checksum;

    if (gSaveFile.save.checksum == Save_Checksum(&gSaveFile.save)) {
        PRINTF("ＥＥＰＲＯＭ ＲＯＭ［1］ 正常\n");
        return 0;
    } else {
        PRINTF("ＥＥＰＲＯＭ ＲＯＭ［０］ ＆ ＲＯＭ［1］ 異常\n");
        return -1;
    }
}
