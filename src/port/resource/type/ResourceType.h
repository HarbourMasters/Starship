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
};
} // namespace SOH
