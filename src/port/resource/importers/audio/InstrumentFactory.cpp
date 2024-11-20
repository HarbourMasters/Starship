#include "InstrumentFactory.h"
#include "../ResourceUtil.h"
#include "port/resource/type/audio/Instrument.h"

namespace SF64 {
std::shared_ptr<Ship::IResource> ResourceFactoryBinaryInstrumentV0::ReadResource(std::shared_ptr<Ship::File> file) {
    if (!FileHasValidFormatAndReader(file)) {
        return nullptr;
    }

    auto instrument = std::make_shared<Instrument>(file->InitData);
    auto reader = std::get<std::shared_ptr<Ship::BinaryReader>>(file->Reader);

    instrument->mInstrument.isRelocated = reader->ReadUByte();
    instrument->mInstrument.normalRangeLo = reader->ReadUByte();
    instrument->mInstrument.normalRangeHi = reader->ReadUByte();
    instrument->mInstrument.adsrDecayIndex = reader->ReadUByte();
    instrument->mInstrument.envelope = LoadChild<EnvelopePointData*>(reader->ReadUInt64());
    instrument->mInstrument.lowPitchTunedSample.sample = LoadChild<SampleData*>(reader->ReadUInt64());
    instrument->mInstrument.lowPitchTunedSample.tuning = reader->ReadFloat();
    instrument->mInstrument.normalPitchTunedSample.sample = LoadChild<SampleData*>(reader->ReadUInt64());
    instrument->mInstrument.normalPitchTunedSample.tuning = reader->ReadFloat();
    instrument->mInstrument.highPitchTunedSample.sample = LoadChild<SampleData*>(reader->ReadUInt64());
    instrument->mInstrument.highPitchTunedSample.tuning = reader->ReadFloat();
    instrument->mInstrument.isRelocated = 1;

    return instrument;
}
} // namespace LUS
