#include "ScriptCommandFactory.h"
#include "../type/Script.h"
#include "spdlog/spdlog.h"
#include "ResourceUtil.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryScriptCMDV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto cmds = std::make_shared<ScriptCMDs>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    auto size = reader->ReadUInt32();

    for (uint32_t i = 0; i < size * 2; i++) {
        cmds->mCommands.push_back(reader->ReadUInt16());
    }

    return cmds;
}
} // namespace LUS
