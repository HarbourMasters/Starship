#include "AudioLoader.h"
#include "utils/binarytools/BinaryReader.h"
#include "assets/ast_audio.h"
#include "BitConverter.h"
#include "port/Engine.h"
#include <vector>
#include <fstream>
#include <filesystem>

#ifdef OTR_AUDIO
extern "C" SoundFont* Audio_LoadFont(AudioTableEntry entry, uint32_t fontId) {
    auto crc = (uint64_t) gSoundFontTable->entries[fontId].romAddr;
    auto path = ResourceGetNameByCrc(crc);
    printf("Font: %s\n", path);
  
    return (SoundFont*) ResourceGetDataByCrc(crc);
}
#else
namespace fs = std::filesystem;

std::unordered_map<uint32_t, void*> gAudioCache;

void* StoreOnCache(uint32_t addr){
    if(gAudioCache.contains(addr)){
        return gAudioCache[addr];
    }
}

Ship::BinaryReader Audio_MakeReader(const char* resource, u32 offset){
    auto data = (char*)ResourceGetDataByName(resource);
    auto size = ResourceGetSizeByName(resource);

    Ship::BinaryReader reader(data, size);
    reader.SetEndianness(Ship::Endianness::Big);
    reader.Seek(offset, Ship::SeekOffsetType::Start);

    return reader;
}

char* Audio_LoadBlob(const char* resource, u32 offset){
    auto data = (char*)ResourceGetDataByName(resource);

    return data + offset;
}

EnvelopePoint* Audio_LoadEnvelope(uint32_t addr) {
    auto reader = Audio_MakeReader(gAudioBank, addr);

    std::vector<EnvelopePoint> temp;
    while(true) {
        int16_t delay = BSWAP16(reader.ReadInt16());
        int16_t arg   = BSWAP16(reader.ReadInt16());

        temp.push_back({delay, arg});

        if (1 <= (-delay) % (1 << 16) && (-delay) % (1 << 16) <= 3){
            break;
        }
    }

    EnvelopePoint* envelopes = memallocn(EnvelopePoint, temp.size());
    memcpy(envelopes, temp.data(), sizeof(EnvelopePoint) * temp.size());

    return envelopes;
}

extern "C" SoundFont* Audio_LoadFont(AudioTableEntry entry, uint32_t fontId) {
    auto reader = Audio_MakeReader(gAudioBank, entry.romAddr);

    if(gAudioCache.contains(entry.romAddr)){
        return (SoundFont*) gAudioCache[entry.romAddr];
    }

    SoundFont* font = memalloc(SoundFont);

    font->numInstruments = (entry.shortData2 >> 8) & 0xFFu;
    font->numDrums = entry.shortData2 & 0xFFu;
    font->sampleBankId1 = (entry.shortData1 >> 8) & 0xFFu;
    font->sampleBankId2 = entry.shortData1 & 0xFFu;
    font->instruments = memallocn(Instrument*, font->numInstruments);
    font->drums = memallocn(Drum*, font->numDrums);

    uint32_t drumBaseAddr = reader.ReadUInt32();
    uint32_t instBaseAddr = 4;

    if(font->drums != nullptr && drumBaseAddr != 0){
        reader.Seek(entry.romAddr + drumBaseAddr, Ship::SeekOffsetType::Start);
        for(size_t i = 0; i < font->numDrums; i++){
            font->drums[i] = Audio_LoadDrum(reader.ReadUInt32(), entry, font->sampleBankId1);
        }
    }

    if(font->instruments != nullptr){
        reader.Seek(entry.romAddr + instBaseAddr, Ship::SeekOffsetType::Start);
        for(size_t i = 0; i < font->numInstruments; i++){
            u32 instAddr = reader.ReadUInt32();
            font->instruments[i] = Audio_LoadInstrument(instAddr, entry, font->sampleBankId1);
        }
    }

    gSampleFontLoadStatus[font->sampleBankId1] = LOAD_STATUS_COMPLETE;

    gAudioCache[entry.romAddr] = font;
    return font;
}

extern "C" AdpcmLoop* Audio_LoadLoop(uint32_t addr) {
    auto reader = Audio_MakeReader(gAudioBank, addr);
    AdpcmLoop* loop = memalloc(AdpcmLoop);

    loop->start = reader.ReadInt32();
    loop->end = reader.ReadUInt32();
    loop->count = reader.ReadUInt32();
    
    if(loop->count != 0){
        for(size_t i = 0; i < 16; i++){
            loop->predictorState[i] = reader.ReadInt16();
        }
    }

    return loop;
}

extern "C" AdpcmBook* Audio_LoadBook(uint32_t addr) {
    auto reader = Audio_MakeReader(gAudioBank, addr);

    AdpcmBook* book = memalloc(AdpcmBook);
    book->order = reader.ReadInt32();
    book->numPredictors = reader.ReadInt32();
    
    size_t length = 8 * book->order * book->numPredictors;
    book->book = memallocn(int16_t, length);

    if(length > 0x40){
        return nullptr;
    }

    for(size_t i = 0; i < length; i++){
        book->book[i] = reader.ReadInt16();
    }

    return book;
}

Sample* Audio_LoadSample(uint32_t sampleAddr, AudioTableEntry entry, uint32_t sampleBankID) {
    auto reader = Audio_MakeReader(gAudioBank, entry.romAddr + sampleAddr);

    Sample* sample = memalloc(Sample);
    uint32_t flags = reader.ReadUInt32();
    uint32_t addr = reader.ReadUInt32();

    sample->codec = (flags >> 28) & 0x0F;
    sample->medium = (flags >> 24) & 0x03;
    sample->unk_bit26 = (flags >> 22) & 0x01;
    sample->size = flags;
    sample->loop = Audio_LoadLoop(entry.romAddr + reader.ReadUInt32());
    sample->book = Audio_LoadBook(entry.romAddr + reader.ReadUInt32());
    sample->sampleAddr = (uint8_t*) Audio_LoadBlob(gAudioTable, gSampleBankTable->entries[sampleBankID].romAddr + addr);

    sample->isRelocated = 1;
    sample->medium = MEDIUM_RAM;

    gUsedSamples[gNumUsedSamples++] = sample;
    return sample;
}

TunedSample Audio_LoadTunedSample(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID) {
    auto reader = Audio_MakeReader(gAudioBank, entry.romAddr + addr);
    auto sampleAddr = reader.ReadUInt32();
    auto tuning = reader.ReadFloat();

    if(sampleAddr == 0){
        assert(tuning == 0.0f);
        return { nullptr, 0.0f };
    }

    return {
        .sample = Audio_LoadSample(sampleAddr, entry, sampleBankID),
        .tuning = tuning
    };
}

extern "C" Instrument* Audio_LoadInstrument(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID) {
    if (addr == 0) {
        return nullptr;
    }

    auto reader = Audio_MakeReader(gAudioBank, entry.romAddr + addr);

    Instrument* instrument = memalloc(Instrument);
    instrument->isRelocated = reader.ReadUByte();
    instrument->normalRangeLo = reader.ReadUByte();
    instrument->normalRangeHi = reader.ReadUByte();
    instrument->adsrDecayIndex = reader.ReadUByte();
    instrument->envelope = Audio_LoadEnvelope(entry.romAddr + reader.ReadUInt32());
    instrument->lowPitchTunedSample = Audio_LoadTunedSample(addr + 8, entry, sampleBankID);
    instrument->normalPitchTunedSample = Audio_LoadTunedSample(addr + 16, entry, sampleBankID);
    instrument->highPitchTunedSample = Audio_LoadTunedSample(addr + 24, entry, sampleBankID);
    instrument->isRelocated = 1;

    return instrument;
}

extern "C" Drum* Audio_LoadDrum(uint32_t addr, AudioTableEntry entry, uint32_t sampleBankID) {
    if(addr == 0){
        return nullptr;
    }

    auto reader = Audio_MakeReader(gAudioBank, entry.romAddr + addr);
    Drum* drum = memalloc(Drum);

    drum->adsrDecayIndex = reader.ReadInt8();
    drum->pan = reader.ReadInt8();
    drum->isRelocated = reader.ReadUByte();
    reader.ReadUByte();
    drum->isRelocated = 1;

    drum->tunedSample = Audio_LoadTunedSample(addr + 4, entry, sampleBankID);
    reader.Seek(0x8, Ship::SeekOffsetType::Current);
    drum->envelope = Audio_LoadEnvelope(entry.romAddr + reader.ReadUInt32());

    return drum;
}
#endif