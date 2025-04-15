#include <libultraship.h>

#include "Engine.h"
#include "DisplayList.h"

extern "C" void gSPDisplayList(Gfx* pkt, Gfx* dl) {
    char* imgData = (char*)dl;

    if (GameEngine_OTRSigCheck(imgData) == 1) {
        auto resource = Ship::Context::GetInstance()->GetResourceManager()->LoadResource(imgData);
        auto res = std::static_pointer_cast<Fast::DisplayList>(resource);
        dl = &res->Instructions[0];
        // dl->words.trace.file = imgData;
        // dl->words.trace.idx = 0;
        // dl->words.trace.valid = true;
    }

    __gSPDisplayList(pkt, dl);
}

extern "C" void gDPSetTileSizeInterp(Gfx* pkt, int t, float uls, float ult, float lrs, float lrt) 
{
	__gDPSetTileSizeInterp(pkt++, t, 0, 0, 0, 0);
	memcpy(&pkt[0].words.w0, &uls, sizeof(float));
	memcpy(&pkt[0].words.w1, &ult, sizeof(float));
	memcpy(&pkt[1].words.w0, &lrs, sizeof(float));
	memcpy(&pkt[1].words.w1, &lrt, sizeof(float));
}

extern "C" void gSPVertex(Gfx* pkt, uintptr_t v, int n, int v0) {

    if (GameEngine_OTRSigCheck((char*)v) == 1) {
        v = (uintptr_t) ResourceGetDataByName((char *) v);
    }

    __gSPVertex(pkt, v, n, v0);
}

extern "C" void gSPInvalidateTexCache(Gfx* pkt, uintptr_t texAddr) {
    char* imgData = (char*)texAddr;

    if (texAddr != 0 && GameEngine_OTRSigCheck(imgData) == 1) {
        auto res = Ship::Context::GetInstance()->GetResourceManager()->LoadResource(imgData);

        if (res->GetInitData()->Type == (uint32_t) Fast::ResourceType::DisplayList)
            texAddr = (uintptr_t)&((std::static_pointer_cast<Fast::DisplayList>(res))->Instructions[0]);
        else {
            texAddr = (uintptr_t) res->GetRawPointer();
        }
    }
   __gSPInvalidateTexCache(pkt, texAddr);
}