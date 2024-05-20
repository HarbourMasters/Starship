#include "sf64dma.h"

DmaEntry gDmaTable[101] = {
    DMA_ENTRY(makerom),
    DMA_ENTRY(main),
    DMA_ENTRY(dma_table),
    DMA_ENTRY(audio_seq),
    DMA_ENTRY(audio_bank),
    DMA_ENTRY(audio_table),
    DMA_ENTRY(ast_common),
    DMA_ENTRY(ast_bg_space),
    DMA_ENTRY(ast_bg_planet),
    DMA_ENTRY(ast_arwing),
    DMA_ENTRY(ast_landmaster),
    DMA_ENTRY(ast_blue_marine),
    DMA_ENTRY(ast_versus),
    DMA_ENTRY(ast_enmy_planet),
    DMA_ENTRY(ast_enmy_space),
    DMA_ENTRY(ast_great_fox),
    DMA_ENTRY(ast_star_wolf),
    DMA_ENTRY(ast_allies),
    DMA_ENTRY(ast_corneria),
    DMA_ENTRY(ast_meteo),
    DMA_ENTRY(ast_titania),
    DMA_ENTRY(ast_7_ti_2),
    DMA_ENTRY(ast_8_ti),
    DMA_ENTRY(ast_9_ti),
    DMA_ENTRY(ast_A_ti),
    DMA_ENTRY(ast_7_ti_1),
    DMA_ENTRY(ast_sector_x),
    DMA_ENTRY(ast_sector_z),
    DMA_ENTRY(ast_aquas),
    DMA_ENTRY(ast_area_6),
    DMA_ENTRY(ast_venom_1),
    DMA_ENTRY(ast_venom_2),
    DMA_ENTRY(ast_ve1_boss),
    DMA_ENTRY(ast_bolse),
    DMA_ENTRY(ast_fortuna),
    DMA_ENTRY(ast_sector_y),
    DMA_ENTRY(ast_solar),
    DMA_ENTRY(ast_zoness),
    DMA_ENTRY(ast_katina),
    DMA_ENTRY(ast_macbeth),
    DMA_ENTRY(ast_warp_zone),
    DMA_ENTRY(ast_title),
    DMA_ENTRY(ast_map),
    DMA_ENTRY(ast_map_en),
    DMA_ENTRY(ast_map_fr),
    DMA_ENTRY(ast_map_de),
    DMA_ENTRY(ast_option),
    DMA_ENTRY(ast_option_en),
    DMA_ENTRY(ast_option_fr),
    DMA_ENTRY(ast_option_de),
    DMA_ENTRY(ast_vs_menu),
    DMA_ENTRY(ast_vs_menu_en),
    DMA_ENTRY(ast_vs_menu_fr),
    DMA_ENTRY(ast_vs_menu_de),
    DMA_ENTRY(ast_text),
    DMA_ENTRY(ast_font_3d),
    DMA_ENTRY(ast_andross),
    DMA_ENTRY(ast_logo),
    DMA_ENTRY(ast_ending),
    DMA_ENTRY(ast_ending_award_front),
    DMA_ENTRY(ast_ending_award_back),
    DMA_ENTRY(ast_ending_expert),
    DMA_ENTRY(ast_training),
    DMA_ENTRY(ast_radio_de),
    DMA_ENTRY(ovl_i1),
    DMA_ENTRY(ovl_i2),
    DMA_ENTRY(ovl_i3),
    DMA_ENTRY(ovl_i4),
    DMA_ENTRY(ovl_i5),
    DMA_ENTRY(ovl_i6),
    DMA_ENTRY(ovl_menu),
    DMA_ENTRY(ovl_ending),
    DMA_ENTRY(ovl_unused),
    DMA_ENTRY(ast_radio_en),
    DMA_ENTRY(ast_radio_fr),
};
