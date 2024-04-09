#include "sys.h"
#include "sf64audio_external.h"

#include <functions.h>

s32 sGammaMode = 1;

SPTask* gCurrentTask;
SPTask* sAudioTasks[1];
SPTask* sGfxTasks[2];
SPTask* sNewAudioTasks[1];
SPTask* sNewGfxTasks[2];
u32 gSegments[16];          // 800E1FD0
OSMesgQueue gPiMgrCmdQueue; // 800E2010
OSMesg sPiMgrCmdBuff[50];   // 800E2028

OSMesgQueue gDmaMsgQueue;
void* sDmaMsgBuff[1];
OSIoMesg gDmaIOMsg;
OSMesgQueue gSerialEventQueue;
void* sSerialEventBuff[1];
OSMesgQueue gMainThreadMsgQueue;
void* sMainThreadMsgBuff[32];
OSMesgQueue gTaskMsgQueue;
void* sTaskMsgBuff[16];
OSMesgQueue gAudioVImsgQueue;
void* sAudioVImsgBuff[1];
OSMesgQueue gAudioTaskMsgQueue;
void* sAudioTaskMsgBuff[1];
OSMesgQueue gGfxVImsgQueue;
void* sGfxVImsgBuff[4];
OSMesgQueue gGfxTaskMsgQueue;
void* sGfxTaskMsgBuff[2];
OSMesgQueue gSerialThreadMsgQueue;
void* sSerialThreadMsgBuff[8];
OSMesgQueue gControllerMsgQueue;
void* sControllerMsgBuff[1];
OSMesgQueue gSaveMsgQueue;
void* sSaveMsgBuff[1];
OSMesgQueue gTimerTaskMsgQueue;
void* sTimerTaskMsgBuff[16];
OSMesgQueue gTimerWaitMsgQueue;
void* sTimerWaitMsgBuff[1];

GfxPool gGfxPools[2];

GfxPool* gGfxPool;
SPTask* gGfxTask;
Vp* gViewport;
Mtx* gGfxMtx;
Gfx* gUnkDisp1;
Gfx* gMasterDisp;
Gfx* gUnkDisp2;
Lightsn* gLight;
FrameBuffer* gFrameBuffer;
u16* gTextureRender;

u8 D_80137E78;
u32 gSysFrameCount;
u8 gStartNMI;
u8 gStopTasks;
u8 D_80137E84[4];
u16 gFillScreenColor;
u16 gFillScreen;

u8 gUnusedStack[0x1000];
OSThread sIdleThread;            // 80138E90
u8 sIdleThreadStack[0x1000];     // 801390A0
OSThread gMainThread;            // 8013A040
u8 sMainThreadStack[0x1000];     // 8013A1F0
OSThread gAudioThread;           // 8013B1F0
u8 gAudioThreadStack[0x1000];    // 800DDAA0
OSThread gGraphicsThread;        // 800DEAA0
u8 gGraphicsThreadStack[0x1000]; // 800DEC50
OSThread gTimerThread;           // 800DFC50
u8 gTimerThreadStack[0x1000];    // 800DFE00
OSThread gSerialThread;          // 800E0E00
u8 gSerialThreadStack[0x1000];   // 800E0FB0

void Main_Initialize(void) {
    u8 i;

    D_80137E78 = 0;
    gSysFrameCount = 0;
    gStartNMI = false;
    gStopTasks = false;
    gFillScreenColor = 0;
    gFillScreen = false;
    gCurrentTask = NULL;

    for (i = 0; i < ARRAY_COUNT(sAudioTasks); i += 1) {
        sAudioTasks[i] = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(sGfxTasks); i += 1) {
        sGfxTasks[i] = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(sNewAudioTasks); i += 1) {
        sNewAudioTasks[i] = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(sNewGfxTasks); i += 1) {
        sNewGfxTasks[i] = NULL;
    }
}

void Audio_ThreadEntry(void* arg0) {
    SPTask* task;

    AudioLoad_Init();
    Audio_InitSounds();
    task = AudioThread_CreateTask();
    if (task != NULL) {
        task->msgQueue = &gAudioTaskMsgQueue;
        task->msg = OS_MESG_32(TASK_MESG_1);
        osWritebackDCacheAll();
        osSendMesg(&gTaskMsgQueue, OS_MESG_PTR(task), OS_MESG_PRI_NORMAL);
    }
    while (1) {
        task = AudioThread_CreateTask();
        if (task != NULL) {
            task->msgQueue = &gAudioTaskMsgQueue;
            task->msg = OS_MESG_32(TASK_MESG_1);
            osWritebackDCacheAll();
        }
        osRecvMesg(&gAudioTaskMsgQueue, NULL, OS_MESG_NOBLOCK);
        if (task != NULL) {
            osSendMesg(&gTaskMsgQueue, OS_MESG_PTR(task), OS_MESG_PRI_NORMAL);
        }
        osRecvMesg(&gAudioVImsgQueue, NULL, OS_MESG_BLOCK);
    }
}

void Graphics_SetTask(void) {
    // gGfxTask->msgQueue = &gGfxTaskMsgQueue;
    // gGfxTask->msg = (OSMesg) TASK_MESG_2;
    // gGfxTask->task.t.type = M_GFXTASK;
    // gGfxTask->task.t.flags = 0;
    // gGfxTask->task.t.ucode_boot = rspbootTextStart;
    // gGfxTask->task.t.ucode_boot_size = (uintptr_t) rspbootTextEnd - (uintptr_t) rspbootTextStart;
    // gGfxTask->task.t.ucode = gspF3DEX_fifoTextStart;
    // gGfxTask->task.t.ucode_size = SP_UCODE_SIZE;
    // gGfxTask->task.t.ucode_data = (u64*) &gspF3DEX_fifoDataStart;
    // gGfxTask->task.t.ucode_data_size = SP_UCODE_DATA_SIZE;
    // gGfxTask->task.t.dram_stack = gDramStack;
    // gGfxTask->task.t.dram_stack_size = SP_DRAM_STACK_SIZE8;
    // gGfxTask->task.t.output_buff = (u64*) gTaskOutputBuffer;
    // gGfxTask->task.t.output_buff_size = (u64*) gAudioHeap;
    // gGfxTask->task.t.data_ptr = (u64*) gGfxPool->masterDL;
    // gGfxTask->task.t.data_size = (gMasterDisp - gGfxPool->masterDL) * sizeof(Gfx);
    // gGfxTask->task.t.yield_data_ptr = (u64*) &gOSYieldData;
    // gGfxTask->task.t.yield_data_size = OS_YIELD_DATA_SIZE;
    // osWritebackDCacheAll();
    // osSendMesg(&gTaskMsgQueue, gGfxTask, OS_MESG_PRI_NORMAL);
}

void Graphics_InitializeTask(u32 frameCount) {
    gGfxPool = &gGfxPools[frameCount % 2];

    gGfxTask = &gGfxPool->task;
    gViewport = gGfxPool->viewports;
    gGfxMtx = gGfxPool->mtx;
    gUnkDisp1 = gGfxPool->unkDL1;
    gMasterDisp = gGfxPool->masterDL;
    gUnkDisp2 = gGfxPool->unkDL2;
    gLight = gGfxPool->lights;

    gFrameBuffer = &gFrameBuffers[frameCount % 3];
    gTextureRender = &gTextureRenderBuffer[0];

    gGfxMatrix = &sGfxMatrixStack[0];
    gCalcMatrix = &sCalcMatrixStack[0];

    D_80178710 = &D_80178580[0];
}

void Main_SetVIMode(void) {
    if ((gControllerHold[0].button & D_JPAD) && (gControllerHold[0].button & L_TRIG) &&
        (gControllerHold[0].button & R_TRIG) && (gControllerHold[0].button & Z_TRIG)) {
        sGammaMode = 1 - sGammaMode;
    }
    // switch (osTvType) {
    //     case OS_TV_PAL:
    //         osViSetMode(&osViModePalLan1);
    //         break;
    //     case OS_TV_MPAL:
    //         osViSetMode(&osViModeMpalLan1);
    //         break;
    //     default:
    //     case OS_TV_NTSC:
    //         osViSetMode(&osViModeNtscLan1);
    //         break;
    // }
    if (sGammaMode != 0) {
        osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_DIVOT_OFF | OS_VI_GAMMA_ON | OS_VI_GAMMA_DITHER_ON);
    } else {
        osViSetSpecialFeatures(OS_VI_DITHER_FILTER_ON | OS_VI_DIVOT_OFF | OS_VI_GAMMA_OFF | OS_VI_GAMMA_DITHER_OFF);
    }
}

void SerialInterface_ThreadUpdate() {
    OSMesg sp34;

    switch (sp34.data32) {
        case SI_READ_SAVE:
            Save_ReadData();
            break;
        case SI_WRITE_SAVE:
            Save_WriteData();
            break;
    }
}

void Timer_ThreadEntry(void* arg0) {
    OSMesg sp24;

    while (1) {
        osRecvMesg(&gTimerTaskMsgQueue, &sp24, OS_MESG_BLOCK);
        // Timer_CompleteTask(sp24.ptr);
    }
}

extern void Graphics_PushFrame(Gfx* masterDL);

void Graphics_ThreadEntry(void* arg0) {
    u8 i;
    u8 var_v1;
    u8 var_v2;

    Game_Initialize();
    osSendMesg(&gSerialThreadMsgQueue, OS_MESG_32(SI_READ_CONTROLLER), OS_MESG_PRI_NORMAL);
    Graphics_InitializeTask(gSysFrameCount);
    {
        gSPSegment(gUnkDisp1++, 0, 0);
        gSPDisplayList(gMasterDisp++, gGfxPool->unkDL1);
        Game_Update();
        gSPEndDisplayList(gUnkDisp1++);
        gSPEndDisplayList(gUnkDisp2++);
        gSPDisplayList(gMasterDisp++, gGfxPool->unkDL2);
        gDPFullSync(gMasterDisp++);
        gSPEndDisplayList(gMasterDisp++);
    }
    Graphics_SetTask();
    // while (1) {

    // }
}

void Graphics_ThreadUpdate() {

    if (GfxDebuggerIsDebugging()) {
        Graphics_PushFrame(gGfxPool->masterDL);
        return;
    }

    gSysFrameCount++;
    Graphics_InitializeTask(gSysFrameCount);
    osRecvMesg(&gControllerMsgQueue, NULL, OS_MESG_NOBLOCK);
    osSendMesg(&gSerialThreadMsgQueue, OS_MESG_32(SI_RUMBLE), OS_MESG_PRI_NORMAL);
    Controller_UpdateInput();
    Controller_ReadData();
    Controller_Rumble();
    osSendMesg(&gSerialThreadMsgQueue, OS_MESG_32(SI_READ_CONTROLLER), OS_MESG_PRI_NORMAL);
    Main_SetVIMode();
    {
        gSPSegment(gUnkDisp1++, 0, 0);
        gSPDisplayList(gMasterDisp++, gGfxPool->unkDL1);
        Game_Update();
        if (gStartNMI == 1) {
            Graphics_NMIWipe();
        }
        gSPEndDisplayList(gUnkDisp1++);
        gSPEndDisplayList(gUnkDisp2++);
        gSPDisplayList(gMasterDisp++, gGfxPool->unkDL2);
        gDPFullSync(gMasterDisp++);
        gSPEndDisplayList(gMasterDisp++);
    }
    osRecvMesg(&gGfxTaskMsgQueue, NULL, OS_MESG_BLOCK);
    Graphics_SetTask();

    if (GfxDebuggerIsDebuggingRequested()) {
        GfxDebuggerDebugDisplayList(gGfxPool->masterDL);
    }

    Graphics_PushFrame(gGfxPool->masterDL);

    if (gFillScreen == 0) {
        osViSwapBuffer(&gFrameBuffers[(gSysFrameCount - 1) % 3]);
    }

    // LTODO: FAULT_CRASH
    // func_80007FE4(&gFrameBuffers[(gSysFrameCount - 1) % 3], SCREEN_WIDTH, 16);

    // LTODO: Figure out what this is
    // var_v1 = MIN(D_80137E78, 4);
    // var_v2 = MAX(var_v1, gGfxVImsgQueue.validCount + 1);
    // for (i = 0; i < var_v2; i += 1) { // Can't be ++
    //     osRecvMesg(&gGfxVImsgQueue, NULL, OS_MESG_BLOCK);
    // }

    // LTODO: There is no audio for now :P
    // Audio_Update();
}

void Main_InitMesgQueues(void) {
    osCreateMesgQueue(&gDmaMsgQueue, sDmaMsgBuff, ARRAY_COUNT(sDmaMsgBuff));
    osCreateMesgQueue(&gTaskMsgQueue, sTaskMsgBuff, ARRAY_COUNT(sTaskMsgBuff));
    osCreateMesgQueue(&gAudioVImsgQueue, sAudioVImsgBuff, ARRAY_COUNT(sAudioVImsgBuff));
    osCreateMesgQueue(&gAudioTaskMsgQueue, sAudioTaskMsgBuff, ARRAY_COUNT(sAudioTaskMsgBuff));
    osCreateMesgQueue(&gGfxVImsgQueue, sGfxVImsgBuff, ARRAY_COUNT(sGfxVImsgBuff));
    osCreateMesgQueue(&gGfxTaskMsgQueue, sGfxTaskMsgBuff, ARRAY_COUNT(sGfxTaskMsgBuff));
    osCreateMesgQueue(&gSerialEventQueue, sSerialEventBuff, ARRAY_COUNT(sSerialEventBuff));
    osSetEventMesg(OS_EVENT_SI, &gSerialEventQueue, OS_MESG_PTR(NULL));
    osCreateMesgQueue(&gMainThreadMsgQueue, sMainThreadMsgBuff, ARRAY_COUNT(sMainThreadMsgBuff));
    osViSetEvent(&gMainThreadMsgQueue, OS_MESG_32(EVENT_MESG_VI), 1);
    osSetEventMesg(OS_EVENT_SP, &gMainThreadMsgQueue, OS_MESG_32(EVENT_MESG_SP));
    osSetEventMesg(OS_EVENT_DP, &gMainThreadMsgQueue, OS_MESG_32(EVENT_MESG_DP));
    osSetEventMesg(OS_EVENT_PRENMI, &gMainThreadMsgQueue, OS_MESG_32(EVENT_MESG_PRENMI));
    osCreateMesgQueue(&gTimerTaskMsgQueue, sTimerTaskMsgBuff, ARRAY_COUNT(sTimerTaskMsgBuff));
    osCreateMesgQueue(&gTimerWaitMsgQueue, sTimerWaitMsgBuff, ARRAY_COUNT(sTimerWaitMsgBuff));
    osCreateMesgQueue(&gSerialThreadMsgQueue, sSerialThreadMsgBuff, ARRAY_COUNT(sSerialThreadMsgBuff));
    osCreateMesgQueue(&gControllerMsgQueue, sControllerMsgBuff, ARRAY_COUNT(sControllerMsgBuff));
    osCreateMesgQueue(&gSaveMsgQueue, sSaveMsgBuff, ARRAY_COUNT(sSaveMsgBuff));
}

void Main_HandleRDP(void) {
    SPTask** var_v1 = sGfxTasks;
    u8 i;

    if ((*var_v1)->msgQueue != NULL) {
        osSendMesg((*var_v1)->msgQueue, (*var_v1)->msg, OS_MESG_PRI_NORMAL);
    }
    (*var_v1)->state = SPTASK_STATE_FINISHED_DP;
    for (i = 0; i < ARRAY_COUNT(sGfxTasks) - 1; i += 1, var_v1++) {
        *var_v1 = *(var_v1 + 1);
    }
    *var_v1 = NULL;
}

void Main_HandleRSP(void) {
    // SPTask* task = gCurrentTask;
    //
    // gCurrentTask = NULL;
    // if (task->state == SPTASK_STATE_INTERRUPTED) {
    //     if (osSpTaskYielded(&task->task) == 0) {
    //         task->state = SPTASK_STATE_FINISHED;
    //     }
    // } else {
    //     task->state = SPTASK_STATE_FINISHED;
    //     if (task->task.t.type == M_AUDTASK) {
    //         if (task->msgQueue != NULL) {
    //             osSendMesg(task->msgQueue, task->msg, OS_MESG_PRI_NORMAL);
    //         }
    //         sAudioTasks[0] = NULL;
    //     }
    // }
}

void Main_GetNewTasks(void) {
    u8 i;
    SPTask** var_a0;
    SPTask** var_a1;
    SPTask** var_s0_2;
    SPTask** var_s1_2;
    OSMesg sp40;
    SPTask* sp3C;

    var_s0_2 = sNewAudioTasks;
    var_s1_2 = sNewGfxTasks;
    for (i = 0; i < ARRAY_COUNT(sNewAudioTasks); i += 1) {
        *(var_s0_2++) = NULL;
    }
    for (i = 0; i < ARRAY_COUNT(sNewGfxTasks); i += 1) {
        *(var_s1_2++) = NULL;
    }

    var_s0_2 = sNewAudioTasks;
    var_s1_2 = sNewGfxTasks;
    while (osRecvMesg(&gTaskMsgQueue, &sp40, OS_MESG_NOBLOCK) != MSG_QUEUE_EMPTY) {
        sp3C = (SPTask*) sp40.ptr;
        sp3C->state = SPTASK_STATE_NOT_STARTED;

        switch (sp3C->task.t.type) {
            case M_AUDTASK:
                *(var_s0_2++) = sp3C;
                break;
            case M_GFXTASK:
                *(var_s1_2++) = sp3C;
                break;
        }
    }
    var_s0_2 = sNewAudioTasks;
    var_s1_2 = sNewGfxTasks;
    var_a0 = sAudioTasks;
    var_a1 = sGfxTasks;

    for (i = 0; i < ARRAY_COUNT(sAudioTasks); i += 1, var_a0++) {
        if (*var_a0 == NULL) {
            break;
        }
    }
    for (i; i < ARRAY_COUNT(sAudioTasks); i += 1) {
        *(var_a0++) = *(var_s0_2++);
    }

    for (i = 0; i < ARRAY_COUNT(sGfxTasks); i += 1, var_a1++) {
        if (*var_a1 == NULL) {
            break;
        }
    }
    for (i; i < ARRAY_COUNT(sGfxTasks); i += 1) {
        *(var_a1++) = *(var_s1_2++);
    }
}

void Main_StartNextTask(void) {
    if (sAudioTasks[0] != NULL) {
        if (gCurrentTask != NULL) {
            if (gCurrentTask->task.t.type == M_GFXTASK) {
                gCurrentTask->state = SPTASK_STATE_INTERRUPTED;
                // osSpTaskYield();
            }
        } else {
            gCurrentTask = sAudioTasks[0];
            // osSpTaskLoad(&gCurrentTask->task);
            // osSpTaskStartGo(&gCurrentTask->task);
            gCurrentTask->state = SPTASK_STATE_RUNNING;
        }
    } else if ((gCurrentTask == NULL) && (sGfxTasks[0] != NULL) && (sGfxTasks[0]->state != SPTASK_STATE_FINISHED)) {
        gCurrentTask = sGfxTasks[0];
        // osDpSetStatus(DPC_CLR_TMEM_CTR | DPC_CLR_PIPE_CTR | DPC_CLR_CMD_CTR | DPC_CLR_CLOCK_CTR);
        // osSpTaskLoad(&gCurrentTask->task);
        // osSpTaskStartGo(&gCurrentTask->task);
        gCurrentTask->state = SPTASK_STATE_RUNNING;
    }
}

void Main_ThreadEntry(void* arg0) {
    OSMesg ogMsg;
    u32 mesg;

    // LTODO: Implement audio
    // Audio_ThreadEntry(NULL);
    Graphics_ThreadEntry(NULL);
    Controller_Init();

    // LTODO: Implement timers
    // Timer_ThreadEntry(NULL);

    // N64 Stuff should not be needed
    // Main_InitMesgQueues();
    // while (true) {
    //     osRecvMesg(&gMainThreadMsgQueue, &ogMsg, OS_MESG_BLOCK);
    //     mesg = ogMsg.data32;

    //     switch (mesg) {
    //         case EVENT_MESG_VI:
    //             osSendMesg(&gAudioVImsgQueue, OS_MESG_32(EVENT_MESG_VI), OS_MESG_PRI_NORMAL);
    //             osSendMesg(&gGfxVImsgQueue, OS_MESG_32(EVENT_MESG_VI), OS_MESG_PRI_NORMAL);
    //             Main_GetNewTasks();
    //             break;
    //         case EVENT_MESG_SP:
    //             Main_HandleRSP();
    //             break;
    //         case EVENT_MESG_DP:
    //             Main_HandleRDP();
    //             break;
    //         case EVENT_MESG_PRENMI:
    //             gStartNMI = 1;
    //             break;
    //     }
    //     if (gStopTasks == 0) {
    //         Main_StartNextTask();
    //     }
    // }
}

void Idle_ThreadEntry(void* arg0) {
    // TODO: Implement idle thread
    // osCreateViManager(OS_PRIORITY_VIMGR);
    // Main_SetVIMode();
    // Lib_FillScreen(1);
    // osCreatePiManager(OS_PRIORITY_PIMGR, &gPiMgrCmdQueue, sPiMgrCmdBuff, ARRAY_COUNT(sPiMgrCmdBuff));
    // osCreateThread(&gMainThread, THREAD_ID_MAIN, &Main_ThreadEntry, arg0, sMainThreadStack +
    // sizeof(sMainThreadStack),
    //                100);
    // osStartThread(&gMainThread);
    // Fault_Init();
    // osSetThreadPri(NULL, OS_PRIORITY_IDLE);
    // loop_1:
    //     goto loop_1;
}

void bootproc(void) {
    // RdRam_CheckIPL3();
    // osInitialize();
    Main_Initialize();
    // osCreateThread(&sIdleThread, THREAD_ID_IDLE, &Idle_ThreadEntry, NULL, sIdleThreadStack +
    // sizeof(sIdleThreadStack),
    //                255);
    // osStartThread(&sIdleThread);
}
