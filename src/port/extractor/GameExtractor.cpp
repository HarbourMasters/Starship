#include "GameExtractor.h"

#include <fstream>

#include "Context.h"
#include "spdlog/spdlog.h"
#include <port/Engine.h>
#if !defined(__IOS__) && !defined(__ANDROID__) && !defined(__SWITCH__)
#include "portable-file-dialogs.h"
#endif

std::unordered_map<std::string, std::string> mGameList = {
    { "d8b1088520f7c5f81433292a9258c1184afa1457", "Star Fox 64 (U) (V1.0)" },
    { "63b69f0ef36306257481afc250f9bc304c7162b2", "Star Fox 64 (U) (V1.0) (Uncompressed)" },
    { "09f0d105f476b00efa5303a3ebc42e60a7753b7a", "Star Fox 64 (U) (V1.1)" },
    { "f7475fb11e7e6830f82883412638e8390791ab87", "Star Fox 64 (U) (V1.1) (Uncompressed)" },
    { "9bd71afbecf4d0a43146e4e7a893395e19bf3220", "Star Fox 64 (J) (V1.0)" },
    { "d064229a32cc05ab85e2381ce07744eb3ffaf530", "Star Fox 64 (J) (V1.0) (Uncompressed)" },
    { "05b307b8804f992af1a1e2fbafbd588501fdf799", "Star Fox 64 (E) (V1.0)" },
    { "09f5d5c14219fc77a36c5a6ad5e63f7abd8b3385", "Star Fox 64 (E) (V1.0) (Uncompressed)" },
    { "c8a10699dea52f4bb2e2311935c1376dfb352e7a", "Star Fox 64 (C) (V1.1)" },
    { "3a05aba5549fa71e8b16a0c6e2c8481b070818a9", "Star Fox 64 (C) (V1.1) (Uncompressed)" },
};

bool GameExtractor::SelectGameFromUI() {
#if !defined(__IOS__) && !defined(__ANDROID__) && !defined(__SWITCH__)
    auto selection = pfd::open_file("Select a file", ".", { "N64 Roms", "*.z64" }).result();

    if (selection.empty()) {
        return false;
    }

    this->mGamePath = selection[0];
#else
    this->mGamePath = Ship::Context::GetPathRelativeToAppDirectory("baserom.us.rev1.z64");
#endif

    std::ifstream file(this->mGamePath, std::ios::binary);
    this->mGameData = std::vector<uint8_t>( std::istreambuf_iterator( file ), {} );
    file.close();
    return true;
}

std::optional<std::string> GameExtractor::ValidateChecksum() const {
    const auto rom = new N64::Cartridge(this->mGameData);
    rom->Initialize();
    auto hash = rom->GetHash();
    
    if (mGameList.find(hash) == mGameList.end()) {
        return std::nullopt;
    }

    return mGameList[hash];
}

bool GameExtractor::GenerateOTR() const {
    const std::string assets_path = Ship::Context::GetAppBundlePath();
    const std::string game_path = Ship::Context::GetAppDirectoryPath();

    Companion::Instance = new Companion(this->mGameData, ArchiveType::O2R, false, assets_path, game_path);

    try {
        Companion::Instance->Init(ExportType::Binary);
    } catch (const std::exception& e) {
        return false;
    }

    return true;
}
