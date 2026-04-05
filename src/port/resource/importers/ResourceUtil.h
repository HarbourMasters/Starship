#pragma once

#include <bridge/resourcebridge.h>
#include <ship/resource/ResourceManager.h>
#include <ship/Context.h>

template <typename T> T LoadChild(uint64_t crc) {
    auto path = ResourceGetNameByCrc(crc);
    if (path == nullptr) {
        return nullptr;
    }
    auto asset = Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(path);
    return asset ? static_cast<T>(asset->GetRawPointer()) : nullptr;
}
template <typename T> T LoadChild(const char* path) {
    if (path == nullptr) {
        return nullptr;
    }
    auto asset = Ship::Context::GetInstance()->GetResourceManager()->LoadResourceProcess(path);
    return asset ? static_cast<T>(asset->GetRawPointer()) : nullptr;
}