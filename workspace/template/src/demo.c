#include "mod.h"

#include "port/hooks/Events.h"
#include <stdio.h>

ListenerID gFrameUpdateListenerID;

void OnFrameUpdate(IEvent* event) {
    gHitCount = 99;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplayLargeText(20, 20, 1.0f, 1.0f, "MOD HELLO");
}

MOD_INIT() {
    gFrameUpdateListenerID = REGISTER_LISTENER(GamePostUpdateEvent, EVENT_PRIORITY_NORMAL, OnFrameUpdate);
}

MOD_EXIT() {
    UNREGISTER_LISTENER(GamePostUpdateEvent, gFrameUpdateListenerID);
}