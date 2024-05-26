#include "GameExtractor.h"

#include <fstream>

#include "Context.h"
#include "spdlog/spdlog.h"
#include "portable-file-dialogs.h"

std::unordered_map<std::string, GameEntry> mGameList = {
    { "f7475fb11e7e6830f82883412638e8390791ab87", { "Star Fox 64 (U) (V1.1)", false } },
    { "09f0d105f476b00efa5303a3ebc42e60a7753b7a", { "Star Fox 64 (U) (V1.1)", true } }
};

bool GameExtractor::SelectGameFromUI() {
#if !defined(__IOS__) || !defined(__ANDROID__) || !defined(__SWITCH__)
    auto selection = pfd::open_file("Select a file", ".", { "N64 Roms", "*.z64 *.n64 *.v64" }).result();

    if (selection.empty()) {
        return false;
    }

    this->mGamePath = selection[0];
#else
    this->mGamePath = Ship::Context::GetPathRelativeToAppDirectory("baserom.z64");
#endif

    std::ifstream file(this->mGamePath, std::ios::binary);
    this->mGameData = std::vector<uint8_t>( std::istreambuf_iterator( file ), {} );
    file.close();
    return true;
}

std::optional<GameEntry> GameExtractor::ValidateChecksum() const {
    const auto rom = new N64::Cartridge(this->mGameData);
    rom->Initialize();
    return mGameList[rom->GetHash()];
}

void GameExtractor::DecompressGame() const {
    auto game = this->ValidateChecksum();
    if (!game.has_value()) {
        return;
    }

    if (game->isCompressed) {
        throw std::runtime_error("Compressed games are not supported yet.");
    }
}

bool GameExtractor::GenerateOTR() const {
    Companion::Instance = new Companion(this->mGameData, true, false);

    try {
        Companion::Instance->Init(ExportType::Binary);
    } catch (const std::exception& e) {
        SPDLOG_ERROR("Failed to generate OTR: {}", e.what());
        exit(1);
    }

    return true;
}