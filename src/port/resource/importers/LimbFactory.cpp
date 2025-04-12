#include "LimbFactory.h"

#include "Context.h"
#include "resourcebridge.h"
#include "../type/Limb.h"
#include "ResourceUtil.h"

namespace SF64 {

std::shared_ptr<Ship::IResource> ResourceFactoryBinaryLimbV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                           std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto limb = std::make_shared<Limb>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);
       
    uint64_t dlist = reader->ReadUInt64();
    limb->mData.dList = LoadChild<Gfx*>(dlist);
    limb->mData.trans.x = reader->ReadFloat();
    limb->mData.trans.y = reader->ReadFloat();
    limb->mData.trans.z = reader->ReadFloat();

    limb->mData.rot.x = reader->ReadInt16();
    limb->mData.rot.y = reader->ReadInt16();
    limb->mData.rot.z = reader->ReadInt16();

    limb->mData.sibling = LoadChild<LimbData*>(reader->ReadUInt64());
    limb->mData.child = LoadChild<LimbData*>(reader->ReadUInt64());

    return limb;
}
} // namespace LUS
