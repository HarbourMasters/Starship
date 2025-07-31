#include "ObjectInitFactory.h"

#include "Context.h"
#include "resourcebridge.h"
#include "../type/ObjectInit.h"

namespace SF64 {

std::shared_ptr<Ship::IResource> ResourceFactoryBinaryObjectInitV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                 std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto obj = std::make_shared<ObjectInitResource>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);
    auto count = reader->ReadUInt32();

    for(size_t i = 0; i < count; i++) {
        ObjectInitData data;
        data.zPos1 = reader->ReadFloat();
        data.zPos2 = reader->ReadInt16();
        data.xPos = reader->ReadInt16();
        data.yPos = reader->ReadInt16();
        data.rot.x = reader->ReadInt16();
        data.rot.y = reader->ReadInt16();
        data.rot.z = reader->ReadInt16();
        data.id = reader->ReadInt16();
        obj->mObjects.push_back(data);
    }

    return obj;
}
} // namespace LUS
