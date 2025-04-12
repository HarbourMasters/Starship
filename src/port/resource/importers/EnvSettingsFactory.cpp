#include "EnvSettingsFactory.h"

#include "Context.h"
#include "resourcebridge.h"
#include "../type/EnvSettings.h"

namespace SF64 {

std::shared_ptr<Ship::IResource> ResourceFactoryBinaryEnvSettingsV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                  std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto env = std::make_shared<EnvSettings>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    env->mSettings.type = reader->ReadInt32();
    env->mSettings.unk_04 = reader->ReadInt32();
    env->mSettings.bgColor = reader->ReadUInt16();
    env->mSettings.seqId = reader->ReadUInt16();
    env->mSettings.fogR = reader->ReadInt32();
    env->mSettings.fogG = reader->ReadInt32();
    env->mSettings.fogB = reader->ReadInt32();
    env->mSettings.fogN = reader->ReadInt32();
    env->mSettings.fogF = reader->ReadInt32();
    env->mSettings.unk_20.x = reader->ReadFloat();
    env->mSettings.unk_20.y = reader->ReadFloat();
    env->mSettings.unk_20.z = reader->ReadFloat();
    env->mSettings.lightR = reader->ReadInt32();
    env->mSettings.lightG = reader->ReadInt32();
    env->mSettings.lightB = reader->ReadInt32();
    env->mSettings.ambR = reader->ReadInt32();
    env->mSettings.ambG = reader->ReadInt32();
    env->mSettings.ambB = reader->ReadInt32();

    return env;
}
} // namespace LUS
