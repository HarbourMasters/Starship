#pragma once

#include <cstdint>
#include <string>
#include <vector>

enum class CompType {
    UNCOMPRESSED,
    COMPRESSED,
    UNKNOWN
};

class CompTool {
public:
    static std::vector<uint8_t> Decompress(std::vector<uint8_t> rom);
private:
    static uint32_t FindFileTable(std::vector<uint8_t>& rom);
};