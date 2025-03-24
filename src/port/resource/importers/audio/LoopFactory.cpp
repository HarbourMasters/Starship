#include "LoopFactory.h"
#include "port/resource/type/audio/AdpcmLoop.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryAdpcmLoopV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto loop = std::make_shared<AdpcmLoop>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    loop->mLoop.start = reader->ReadUInt32();
    loop->mLoop.end = reader->ReadUInt32();
    loop->mLoop.count = reader->ReadUInt32();
    if(loop->mLoop.count != 0){
        for(size_t i = 0; i < 16; i++){
            loop->mLoop.predictorState[i] = reader->ReadInt16();
        }
    }

    return loop;
}
} // namespace LUS
