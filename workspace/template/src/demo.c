#include "mod.h"

#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#include "cimgui.h"

#include "port/hooks/Events.h"
#include "port/api/UIWidgets_Bridge.h"
#include <stdio.h>

ListenerID gFrameUpdateListenerID;
ListenerID gUIRenderListenerID;

void OnFrameUpdate(IEvent* event) {
    gHitCount = 99;

    RCP_SetupDL(&gMasterDisp, SETUPDL_83);
    gDPSetPrimColor(gMasterDisp++, 0, 0, 255, 255, 0, 255);
    Graphics_DisplayLargeText(20, 20, 1.0f, 1.0f, "MOD HELLO");
}

void OnUIRender(IEvent* event) {
    if(UIWidgets_BeginMenu("Demo Menu", 10, 10, 200, 100)) {
        UIWidgets_WrappedText("Test text", 1);
        igEndMenu();
    }
}

MOD_INIT() {
    gUIRenderListenerID = REGISTER_LISTENER(EngineRenderModsEvent, EVENT_PRIORITY_NORMAL, OnUIRender);
    gFrameUpdateListenerID = REGISTER_LISTENER(GamePostUpdateEvent, EVENT_PRIORITY_NORMAL, OnFrameUpdate);
}

MOD_EXIT() {
    UNREGISTER_LISTENER(GamePostUpdateEvent, gFrameUpdateListenerID);
}