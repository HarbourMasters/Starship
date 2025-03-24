#include "BookFactory.h"
#include "port/resource/type/audio/AdpcmBook.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryAdpcmBookV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                                std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto book = std::make_shared<AdpcmBook>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    book->mBook.order = reader->ReadUInt32();
    book->mBook.numPredictors = reader->ReadUInt32();
    uint32_t count = reader->ReadUInt32();

    for(size_t i = 0; i < count; i++){
        book->mPages.push_back(reader->ReadInt16());
    }

    book->mBook.book = book->mPages.data();
    return book;
}
} // namespace LUS
