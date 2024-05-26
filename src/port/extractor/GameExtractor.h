#pragma once

#include "Companion.h"
#include <filesystem>
#include <vector>
#include <cstdint>

struct GameEntry {
    std::string name;
    bool isCompressed;
};

class GameExtractor {
public:
    std::optional<GameEntry> ValidateChecksum() const;
    bool SelectGameFromUI();
    void DecompressGame() const;
    bool GenerateOTR() const;
private:
    fs::path mGamePath;
    std::vector<uint8_t> mGameData;
};