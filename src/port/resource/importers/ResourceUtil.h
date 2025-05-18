#pragma once

#include "resourcebridge.h"
#include "ResourceManager.h"
#include "Context.h"

namespace SF64 {
template <typename T> T LoadChild(uint64_t crc) {
    if (crc == 0) {
        return nullptr;
    }
    auto path = ResourceGetNameByCrc(crc);
    if (path == nullptr) {
        return nullptr;
    }
    auto asset = Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(path);
    return asset != nullptr ? static_cast<T>(asset->GetRawPointer()) : nullptr;
}
}