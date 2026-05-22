#include "SequenceFactory.h"
#include "spdlog/spdlog.h"
#include <tinyxml2.h>
#include <cstring>
#include "Context.h"
#include "resource/ResourceManager.h"
#include "utils/binarytools/BinaryWriter.h"
#include "port/audio/AudioDebug.h"

namespace SF64 {

// ---------------------------------------------------------------------------
// Binary V2 reader — mirrors NSequenceBinaryExporter / Shipwright V2 layout:
//   u32  seqDataSize
//   u8[] seqData[seqDataSize]
//   u8   seqNumber
//   u8   medium
//   u8   cachePolicy
//   u32  numFonts
//   u8   fonts[16]  (always present; numFonts entries are valid)
// ---------------------------------------------------------------------------
std::shared_ptr<Ship::IResource>
ResourceFactoryBinarySequenceV2::ReadResource(std::shared_ptr<Ship::File> file,
                                              std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto seq = std::make_shared<Sequence>(initData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    seq->mSequence.seqDataSize = reader->ReadUInt32();
    seq->mBuffer.resize(seq->mSequence.seqDataSize);
    for (uint32_t i = 0; i < seq->mSequence.seqDataSize; i++) {
        seq->mBuffer[i] = reader->ReadChar();
    }
    seq->mSequence.seqData = seq->mBuffer.data();

    seq->mSequence.seqNumber    = reader->ReadUByte();
    seq->mSequence.medium       = reader->ReadUByte();
    seq->mSequence.cachePolicy  = reader->ReadUByte();
    seq->mSequence.numFonts     = reader->ReadUInt32();

    memset(seq->mSequence.fonts, 0, sizeof(seq->mSequence.fonts));
    for (int i = 0; i < 16; i++) {
        seq->mSequence.fonts[i] = reader->ReadUByte();
    }

    SF64::AudioDebug_RegisterSequence(seq->mSequence.seqNumber, initData->Path);
    return seq;
}

// ---------------------------------------------------------------------------
// Helpers for bytecode generation (mirrors Shipwright's XML streamed path)
// ---------------------------------------------------------------------------

static void WriteInsnNoArg(Ship::BinaryWriter* w, uint8_t op) {
    w->Write(op);
}

template<typename T>
static void WriteInsnOneArg(Ship::BinaryWriter* w, uint8_t op, T arg) {
    w->Write(op);
    w->Write(arg);
}

template<typename T1, typename T2, typename T3>
static void WriteInsnThreeArg(Ship::BinaryWriter* w, uint8_t op, T1 a, T2 b, T3 c) {
    w->Write(op);
    w->Write(a);
    w->Write(b);
    w->Write(c);
}

static void WriteMuteBhv(Ship::BinaryWriter* w, uint8_t a)     { WriteInsnOneArg(w, 0xD3, a); }
static void WriteMuteScale(Ship::BinaryWriter* w, uint8_t a)   { WriteInsnOneArg(w, 0xD5, a); }
static void WriteInitchan(Ship::BinaryWriter* w, uint16_t ch)  { WriteInsnOneArg(w, 0xD7, ch); }
static void WriteLdchan(Ship::BinaryWriter* w, uint8_t ch, uint16_t off) {
    WriteInsnOneArg(w, (uint8_t)(0x90 | ch), off);
}
static void WriteVolSHeader(Ship::BinaryWriter* w, uint8_t v)  { WriteInsnOneArg(w, 0xDB, v); }
static void WriteVolCHeader(Ship::BinaryWriter* w, uint8_t v)  { WriteInsnOneArg(w, 0xDF, v); }
static void WriteTempo(Ship::BinaryWriter* w, uint8_t t)       { WriteInsnOneArg(w, 0xDD, t); }
static void WriteJump(Ship::BinaryWriter* w, uint16_t off)     { WriteInsnOneArg(w, 0xFB, off); }
static void WriteDisablecan(Ship::BinaryWriter* w, uint16_t ch){ WriteInsnOneArg(w, 0xD6, ch); }
static void WriteNoshort(Ship::BinaryWriter* w)                { WriteInsnNoArg(w, 0xC4); }
static void WriteLdlayer(Ship::BinaryWriter* w, uint8_t l, uint16_t off) {
    WriteInsnOneArg(w, (uint8_t)(0x90 | l), off);
}
static void WritePan(Ship::BinaryWriter* w, uint8_t p)         { WriteInsnOneArg(w, 0xDD, p); }
static void WriteBend(Ship::BinaryWriter* w, uint8_t b)        { WriteInsnOneArg(w, 0xD3, b); }
static void WriteInstrument(Ship::BinaryWriter* w, uint8_t i)  { WriteInsnOneArg(w, 0xC1, i); }
static void WriteLegato(Ship::BinaryWriter* w)                 { WriteInsnNoArg(w, 0xC4); }
static void WriteDelay(Ship::BinaryWriter* w, uint16_t delay) {
    if (delay > 0x7F) {
        WriteInsnOneArg(w, 0xFD, (uint16_t)(delay | 0x8000));
    } else {
        WriteInsnOneArg(w, 0xFD, (uint8_t)delay);
    }
}
static void WriteNotedvg(Ship::BinaryWriter* w, uint8_t note, uint16_t delay, uint8_t vel, uint8_t gate) {
    if (delay > 0x7F) {
        WriteInsnThreeArg(w, note, (uint16_t)(delay | 0x8000), vel, gate);
    } else {
        WriteInsnThreeArg(w, note, (uint8_t)delay, vel, gate);
    }
}

static void WriteMonoSingleSeq(Ship::BinaryWriter* w, uint16_t delay, uint8_t tempo, bool looped) {
    if (looped) delay = 0x7FFF;

    WriteMuteBhv(w, 0x20);
    WriteMuteScale(w, 0x32);
    WriteInitchan(w, 0b11);

    uint16_t channelPlaceholderOff = w->GetBaseAddress();
    uint16_t loopPoint = w->GetBaseAddress();
    WriteLdchan(w, 0, 0);
    WriteVolSHeader(w, 127);
    WriteTempo(w, tempo);
    WriteDelay(w, delay);
    if (looped) WriteJump(w, loopPoint);
    WriteDisablecan(w, 0b11);
    w->Write((uint8_t)0xFF);

    uint16_t channelStart = w->GetBaseAddress();
    w->Seek(channelPlaceholderOff, Ship::SeekOffsetType::Start);
    WriteLdchan(w, 0, channelStart);
    w->Seek(channelStart, Ship::SeekOffsetType::Start);

    WriteNoshort(w);
    uint16_t layerPlaceholderOff = w->GetBaseAddress();
    WriteLdlayer(w, 0, 0);
    WritePan(w, 64);
    WriteVolCHeader(w, 127);
    WriteBend(w, 0);
    WriteInstrument(w, 0);
    WriteDelay(w, delay);
    w->Write((uint8_t)0xFF);

    uint16_t layerStart = w->GetBaseAddress();
    w->Seek(layerPlaceholderOff, Ship::SeekOffsetType::Start);
    WriteLdlayer(w, 0, layerStart);
    w->Seek(layerStart, Ship::SeekOffsetType::Start);

    WriteLegato(w);
    WriteNotedvg(w, 39, 0x7FFF - 1, 0x7F, 1);
    w->Write((uint8_t)0xFF);
}

static void WriteStereoSingleSeq(Ship::BinaryWriter* w, uint16_t delay, uint8_t tempo, bool looped) {
    if (looped) delay = 0x7FFF;

    WriteMuteBhv(w, 0x20);
    WriteMuteScale(w, 0x32);
    WriteInitchan(w, 0b11);

    uint16_t channelPlaceholderOff = w->GetBaseAddress();
    uint16_t loopPoint = w->GetBaseAddress();
    WriteLdchan(w, 0, 0);
    WriteLdchan(w, 1, 0);
    WriteVolSHeader(w, 127);
    WriteTempo(w, tempo);
    WriteDelay(w, delay);
    if (looped) WriteJump(w, loopPoint);
    WriteDisablecan(w, 0b11);
    w->Write((uint8_t)0xFF);

    uint16_t lChannelStart = w->GetBaseAddress();
    WriteNoshort(w);
    uint16_t lLayerPlaceholderOff = w->GetBaseAddress();
    WriteLdlayer(w, 0, 0);
    WritePan(w, 0);
    WriteVolCHeader(w, 127);
    WriteBend(w, 0);
    WriteInstrument(w, 0);
    WriteDelay(w, delay);
    w->Write((uint8_t)0xFF);

    uint16_t rChannelStart = w->GetBaseAddress();
    WriteNoshort(w);
    uint16_t rLayerPlaceholderOff = w->GetBaseAddress();
    WriteLdlayer(w, 1, 0);
    WritePan(w, 127);
    WriteVolCHeader(w, 127);
    WriteBend(w, 0);
    WriteInstrument(w, 1);
    WriteDelay(w, delay);
    w->Write((uint8_t)0xFF);

    uint16_t placeholder = w->GetBaseAddress();
    w->Seek(channelPlaceholderOff, Ship::SeekOffsetType::Start);
    WriteLdchan(w, 0, lChannelStart);
    WriteLdchan(w, 1, rChannelStart);
    w->Seek(placeholder, Ship::SeekOffsetType::Start);

    uint16_t lLayerOffset = w->GetBaseAddress();
    WriteLegato(w);
    WriteNotedvg(w, 39, 0x7FFF - 1, 0x7F, 1);
    w->Write((uint8_t)0xFF);

    uint16_t rLayerOffset = w->GetBaseAddress();
    WriteLegato(w);
    WriteNotedvg(w, 39, 0x7FFF - 1, 0x7F, 1);
    w->Write((uint8_t)0xFF);

    w->Seek(lLayerPlaceholderOff, Ship::SeekOffsetType::Start);
    WriteLdlayer(w, 0, lLayerOffset);
    w->Seek(rLayerPlaceholderOff, Ship::SeekOffsetType::Start);
    WriteLdlayer(w, 1, rLayerOffset);
}

// ---------------------------------------------------------------------------
// XML V0 reader — mirrors Shipwright's ResourceFactoryXMLAudioSequenceV0
// ---------------------------------------------------------------------------
std::shared_ptr<Ship::IResource>
ResourceFactoryXMLSequenceV0::ReadResource(std::shared_ptr<Ship::File> file,
                                           std::shared_ptr<Ship::ResourceInitData> initData) {
    if (!FileHasValidFormatAndReader(file, initData)) {
        return nullptr;
    }

    auto seq = std::make_shared<Sequence>(initData);
    auto child = std::get<std::shared_ptr<tinyxml2::XMLDocument>>(file->Reader)->FirstChildElement();

    seq->mSequence.medium       = ResourceFactoryXMLSoundFontV0::MediumStrToInt(child->Attribute("Medium"));
    seq->mSequence.cachePolicy  = ResourceFactoryXMLSoundFontV0::CachePolicyToInt(child->Attribute("CachePolicy"));
    seq->mSequence.seqDataSize  = child->IntAttribute("Size");
    seq->mSequence.seqNumber    = (uint8_t)child->IntAttribute("Index");
    bool streamed               = child->BoolAttribute("Streamed");

    memset(seq->mSequence.fonts, 0, sizeof(seq->mSequence.fonts));

    unsigned int i = 0;
    tinyxml2::XMLElement* fontsElement = child->FirstChildElement();
    if (fontsElement != nullptr) {
        tinyxml2::XMLElement* fontElement = fontsElement->FirstChildElement();
        while (fontElement != nullptr) {
            seq->mSequence.fonts[i] = fontElement->IntAttribute("FontIdx");
            fontElement = fontElement->NextSiblingElement();
            i++;
        }
    }
    seq->mSequence.numFonts = i;

    const char* path = child->Attribute("Path");
    std::shared_ptr<Ship::File> seqFile;
    if (path != nullptr) {
        seqFile = Ship::Context::GetInstance()
                      ->GetResourceManager()
                      ->GetArchiveManager()
                      ->LoadFile(path);
    }

    if (!streamed) {
        if (!seqFile || !seqFile->Buffer || seqFile->Buffer->empty()) {
            SPDLOG_ERROR("[SequenceFactory] Could not load sequence file '{}' for '{}'",
                         path ? path : "(null)", initData->Path);
            return nullptr;
        }
        seq->mSequence.seqDataSize = seqFile->Buffer->size();
        seq->mBuffer.resize(seq->mSequence.seqDataSize);
        memcpy(seq->mBuffer.data(), seqFile->Buffer->data(), seq->mSequence.seqDataSize);
        seq->mSequence.seqData = seq->mBuffer.data();
    } else {
        // Streamed: numFonts = -1 signals the audio engine that fonts[] holds a CRC64
        seq->mSequence.numFonts = (uint32_t)-1;

        if (path != nullptr && seqFile && seqFile->Buffer && !seqFile->Buffer->empty()) {
            seq->mSequence.seqDataSize = seqFile->Buffer->size();
            seq->mBuffer.resize(seq->mSequence.seqDataSize);
            memcpy(seq->mBuffer.data(), seqFile->Buffer->data(), seq->mSequence.seqDataSize);
            seq->mSequence.seqData = seq->mBuffer.data();
        } else {
            // Generate synthetic bytecode from Length/Looped/Stereo attributes
            unsigned int length = child->UnsignedAttribute("Length");
            bool looped = child->BoolAttribute("Looped", true);
            bool stereo = child->BoolAttribute("Stereo", false);

            constexpr uint8_t TEMPO = 1;
            constexpr float TEMPO_F = TEMPO;
            float delayF = (float)length / (60.0f / (TEMPO_F * 48.0f));
            uint16_t delay = (delayF >= 65535.0f) ? 0x7FFF : (uint16_t)delayF;

            Ship::BinaryWriter writer;
            writer.SetEndianness(Ship::Endianness::Big);
            if (stereo) {
                WriteStereoSingleSeq(&writer, delay, TEMPO, looped);
            } else {
                WriteMonoSingleSeq(&writer, delay, TEMPO, looped);
            }

            auto vec = writer.ToVector();
            seq->mSequence.seqDataSize = vec.size();
            seq->mBuffer.resize(vec.size());
            memcpy(seq->mBuffer.data(), vec.data(), vec.size());
            seq->mSequence.seqData = seq->mBuffer.data();
        }
    }

    SF64::AudioDebug_RegisterSequence(seq->mSequence.seqNumber, initData->Path);
    return seq;
}

} // namespace SF64
