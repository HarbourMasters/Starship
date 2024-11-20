#include "DisplayListPatch.h"
#include <libultraship.h>

std::unordered_map<const char*, std::vector<std::pair<uint32_t, Gfx>>> patches = {
    // { ast_corneria_seg6_gfx_23420, {
    //     { 23, gsDPSetTileSize(G_TX_RENDERTILE, 0, 0, 0x003C, 0x003C) }
    // }}
};

void DisplayListPatch::Run() {
    SPDLOG_INFO("Applying display list patches");

    for(auto& entry : patches){
        auto data = (Gfx*) ResourceGetDataByName(entry.first);
        for(auto& patch : entry.second){
            data[patch.first] = patch.second;
        }

        SPDLOG_INFO("{} patched successfully!", entry.first);
    }
}