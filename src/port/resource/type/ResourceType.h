#pragma once

namespace SF64 {
enum class ResourceType {
    // SF64
    AnimData = 0x414E494D,     // ANIM
    ColPoly = 0x43504C59,      // CPLY
    Environment = 0x454E5653,  // ENVS
    Limb = 0x4C494D42,         // LIMB
    Message = 0x4D534720,      // MSG
    MessageTable = 0x4D534754, // MSGT
    Skeleton = 0x534B454C,     // SKEL
    Script = 0x53435250,       // SCRP
    ScriptCmd = 0x53434D44,    // SCMD
    Hitbox = 0x48544258,       // HTBX
    ObjectInit = 0x4F42494E,   // OBIN
    Vec3f = 0x56433346,        // VC3F
    Vec3s = 0x56433353,        // VC3S
    GenericArray = 0x47415252, // GARR

    // NAudio v0
    Bank = 0x42414E4B,         // BANK
    Sample = 0x41554643,       // AIFC
    Sequence = 0x53455143,     // SEQC

    // NAudio v1
    SoundFont = 0x53464E54,    // SFNT
    Drum = 0x4452554D,         // DRUM
    Instrument = 0x494E5354,   // INST
    AdpcmLoop = 0x4150434C,    // APCL
    AdpcmBook = 0x41504342,    // APCB
    Envelope = 0x45564C50,     // EVLP
    AudioTable = 0x4154424C    // ATBL
};
} // namespace SOH
