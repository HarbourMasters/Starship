#include "SampleFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/Sample.h"
#include "sf64audio_provisional.h"
#define DR_WAV_IMPLEMENTATION
#include <dr_wav.h>
#include <tinyxml2.h>
#define DR_MP3_IMPLEMENTATION
#include <dr_mp3.h>

#include "vorbis/vorbisfile.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinarySampleV1::ReadResource(std::shared_ptr<Ship::File> file,
                                                                             std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto sample = std::make_shared<Sample>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    sample->mSample.codec = reader->ReadUByte();
    sample->mSample.medium = reader->ReadUByte();
    sample->mSample.unk = reader->ReadUByte();
    sample->mSample.size = reader->ReadUInt32();
    sample->mSample.loop = LoadChild<AdpcmLoopData*>(reader->ReadUInt64());
    sample->mSample.book = LoadChild<AdpcmBookData*>(reader->ReadUInt64());
    sample->mSample.sampleAddr = new uint8_t[sample->mSample.size];
    reader->Read((char*) sample->mSample.sampleAddr, sample->mSample.size);

    if(sample->mSample.codec == 2){
        sample->mSample.medium = 2;
        for(size_t i = 0; i < sample->mSample.size / 2; i++){
            auto sampleData = (int16_t*) sample->mSample.sampleAddr;
            sampleData[i] = BSWAP16(sampleData[i]);
        }
    } else {
        sample->mSample.medium = 0;
    }

    sample->mSample.isRelocated = 1;

    return sample;
}

static size_t VorbisReadCallback(void* out, size_t size, size_t elems, void* src) {
    OggFileData* data = static_cast<OggFileData*>(src);
    size_t toRead = size * elems;

    if (toRead > data->size - data->pos) {
        toRead = data->size - data->pos;
    }

    memcpy(out, static_cast<uint8_t*>(data->data) + data->pos, toRead);
    data->pos += toRead;

    return toRead / size;
}

static int VorbisSeekCallback(void* src, ogg_int64_t pos, int whence) {
    OggFileData* data = static_cast<OggFileData*>(src);
    size_t newPos;

    switch (whence) {
        case SEEK_SET:
            newPos = pos;
            break;
        case SEEK_CUR:
            newPos = data->pos + pos;
            break;
        case SEEK_END:
            newPos = data->size + pos;
            break;
        default:
            return -1;
    }
    if (newPos > data->size) {
        return -1;
    }
    data->pos = newPos;
    return 0;
}

static int VorbisCloseCallback([[maybe_unused]] void* src) {
    return 0;
}

static long VorbisTellCallback(void* src) {
    OggFileData* data = static_cast<OggFileData*>(src);
    return data->pos;
}

static const ov_callbacks vorbisCallbacks = {
    VorbisReadCallback,
    VorbisSeekCallback,
    VorbisCloseCallback,
    VorbisTellCallback,
};

static void Mp3DecoderWorker(std::shared_ptr<Sample> sample, std::shared_ptr<Ship::File> sampleFile) {
    drmp3 mp3;
    drwav_uint64 numFrames;
    drmp3_bool32 ret =
        drmp3_init_memory(&mp3, sampleFile->Buffer->data(), sampleFile->Buffer->size(), nullptr);
    numFrames = drmp3_get_pcm_frame_count(&mp3);
    drwav_uint64 channels = mp3.channels;
    drwav_uint64 sampleRate = mp3.sampleRate;

    sample->mSample.tuning = (float)(sampleRate * channels) / 32000.0f;
    sample->mSample.size = numFrames * channels * 2;
    sample->mSample.sampleAddr = new uint8_t[sample->mSample.size];
    drmp3_read_pcm_frames_s16(&mp3, numFrames, (int16_t*)sample->mSample.sampleAddr);
}

static void OggDecoderWorker(std::shared_ptr<Sample> sample, std::shared_ptr<Ship::File> sampleFile) {
    OggVorbis_File vf;
    char dataBuff[4096];
    long read = 0;
    size_t pos = 0;

    OggFileData fileData = {
        .data = sampleFile->Buffer.get()->data(),
        .pos = 0,
        .size = sampleFile->Buffer.get()->size(),
    };
    int ret = ov_open_callbacks(&fileData, &vf, nullptr, 0, vorbisCallbacks);

    vorbis_info* vi = ov_info(&vf, -1);

    uint64_t numFrames = ov_pcm_total(&vf, -1);
    uint64_t sampleRate = vi->rate;
    uint64_t numChannels = vi->channels;
    int bitStream = 0;
    size_t toRead = numFrames * numChannels * 2;
    sample->mSample.sampleAddr = new uint8_t[toRead];
    sample->mSample.tuning = (float)(sampleRate * numChannels) / 32000.0f;
    do {
        read = ov_read(&vf, dataBuff, 4096, 0, 2, 1, &bitStream);
        memcpy(sample->mSample.sampleAddr + pos, dataBuff, read);
        pos += read;
    } while (read != 0);
    ov_clear(&vf);
}

std::shared_ptr<Ship::IResource> ResourceFactoryXMLSampleV0::ReadResource(std::shared_ptr<Ship::File> file,
                                                                           std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto sample = std::make_shared<Sample>(initData);
    auto child = std::get<std::shared_ptr<tinyxml2::XMLDocument>>(file->Reader)->FirstChildElement();
    const char* customFormatStr = child->Attribute("CustomFormat");
    memset(&sample->mSample, 0, sizeof(sample->mSample));
    sample->mSample.isRelocated = 0;
    sample->mSample.codec = CodecStrToInt(child->Attribute("Codec"), initData->Path.c_str());
    sample->mSample.medium = MediumStrToInt(child->Attribute("Medium"));
    sample->mSample.unk = child->IntAttribute("bit26");

    tinyxml2::XMLElement* loopRoot = child->FirstChildElement("ADPCMLoop");
    if (loopRoot != nullptr) {
        size_t i = 0;
        sample->mSample.loop = new AdpcmLoopData();
        sample->mSample.loop->start = loopRoot->UnsignedAttribute("Start");
        sample->mSample.loop->end = loopRoot->UnsignedAttribute("End");
        sample->mSample.loop->count = loopRoot->UnsignedAttribute("Count");
        tinyxml2::XMLElement* predictor = loopRoot->FirstChildElement("Predictor");
        while (predictor != nullptr) {
            sample->mSample.loop->predictorState[i++] = predictor->IntAttribute("State");
            predictor = predictor->NextSiblingElement();
        }
    }

    tinyxml2::XMLElement* bookRoot = child->FirstChildElement("ADPCMBook");
    if (bookRoot != nullptr) {
        size_t i = 0;
        sample->mSample.book = new AdpcmBookData();
        sample->mSample.book->numPredictors = bookRoot->IntAttribute("Npredictors");
        sample->mSample.book->order = bookRoot->IntAttribute("Order");
        tinyxml2::XMLElement* book = bookRoot->FirstChildElement("Book");
        size_t numBooks = sample->mSample.book->numPredictors * sample->mSample.book->order * 8;
        sample->mSample.book->book = new int16_t[numBooks];
        while (book != nullptr) {
            sample->mSample.book->book[i++] = book->IntAttribute("Page");
            book = book->NextSiblingElement();
        }
    }

    size_t size = child->Int64Attribute("Size");
    sample->mSample.size = size;

    const char* path = child->Attribute("Path");
    auto sampleFile = Ship::Context::GetInstance()->GetResourceManager()->GetArchiveManager()->LoadFile(path);
    if (customFormatStr != nullptr) {
        // Compressed files can take a really long time to decode (~250ms per).
        // This worked when we tested it (09/04/2024) (Works on my machine)
        if (strcmp(customFormatStr, "wav") == 0) {
            drwav wav;
            drwav_uint64 numFrames;

            drwav_bool32 ret =
                drwav_init_memory(&wav, sampleFile->Buffer->data(), sampleFile->Buffer->size(), nullptr);

            drwav_get_length_in_pcm_frames(&wav, &numFrames);

            sample->mSample.tuning = (float)(wav.sampleRate * wav.channels) / 32000.0f;
            sample->mSample.size = numFrames * wav.channels * 2;
            sample->mSample.sampleAddr = new uint8_t[sample->mSample.size];

            drwav_read_pcm_frames_s16(&wav, numFrames, (int16_t*)sample->mSample.sampleAddr);
            return sample;
        } else if (strcmp(customFormatStr, "ogg") == 0) {
            std::thread fileDecoderThread = std::thread(OggDecoderWorker, sample, sampleFile);
            fileDecoderThread.detach();
            return sample;
        } else if (strcmp(customFormatStr, "mp3") == 0) {
            std::thread fileDecoderThread = std::thread(Mp3DecoderWorker, sample, sampleFile);
            fileDecoderThread.detach();
            return sample;
        }
    }
    // Not a normal streamed sample. Fallback to the original ADPCM sample to be decoded by the audio engine.
    sample->mSample.sampleAddr = new uint8_t[size];
    // Can't use memcpy due to endianness issues.
    for (uint32_t i = 0; i < size; i++) {
        sample->mSample.sampleAddr[i] = (*sampleFile->Buffer)[i];
    }

    sample->mSample.isRelocated = 1;

    return sample;
}

uint8_t ResourceFactoryXMLSampleV0::CodecStrToInt(const char* str, const char* file) {
    if (strcmp("ADPCM", str) == 0) {
        return CODEC_ADPCM;
    } else if (strcmp("S8", str) == 0) {
        return CODEC_S8;
    } else if (strcmp("S16MEM", str) == 0) {
        return CODEC_S16_INMEMORY;
    } else if (strcmp("ADPCMSMALL", str) == 0) {
        return CODEC_SMALL_ADPCM;
    } else if (strcmp("REVERB", str) == 0) {
        return CODEC_REVERB;
    } else if (strcmp("S16", str) == 0) {
        return CODEC_S16;
    } else {
        char buff[2048];
        snprintf(buff, 2048,
                 "Invalid codec in %s. Got %s, expected ADPCM, S8, S16MEM, ADPCMSMALL, REVERB, S16, UNK6, UNK7.", file,
                 str);
        throw std::runtime_error(buff);
    }
}

uint32_t ResourceFactoryXMLSampleV0::MediumStrToInt(const char* str) {
    if (!strcmp("Ram", str)) {
        return 0;
    } else if (!strcmp("Unk", str)) {
        return 1;
    } else if (!strcmp("Cart", str)) {
        return 2;
    } else if (!strcmp("Disk", str)) {
        return 3;
        // 4 is skipped
    } else if (!strcmp("RamUnloaded", str)) {
        return 5;
    } else {
        char buff[2048];
        snprintf(buff, 2048,
                 "Bad medium value. Got %s, expected Ram, Unk, Cart, or Disk.", str);
        throw std::runtime_error(buff);
    }
}
} // namespace LUS
