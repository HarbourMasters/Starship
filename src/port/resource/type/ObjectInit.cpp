#include "ObjectInit.h"

namespace SF64 {
ObjectInitData* ObjectInitResource::GetPointer() {
    return mObjects.data();
}

size_t ObjectInitResource::GetPointerSize() {
    return sizeof(ObjectInitData) * mObjects.size();
}
}