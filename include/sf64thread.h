#ifndef SF64_THREAD
#define SF64_THREAD

#include <libultraship.h>
#include "gfx.h"

typedef enum {
    /*   0 */ GSTATE_NONE,
    /*   1 */ GSTATE_INIT,
    /*   2 */ GSTATE_TITLE,
    /*   3 */ GSTATE_MENU,
    /*   4 */ GSTATE_MAP,
    /*   5 */ GSTATE_GAME_OVER,
    /*   6 */ GSTATE_VS_INIT,
    /*   7 */ GSTATE_PLAY,
    /*   8 */ GSTATE_ENDING,
    /* 100 */ GSTATE_BOOT = 100,
    /* 101 */ GSTATE_BOOT_WAIT,
    /* 102 */ GSTATE_SHOW_LOGO,
    /* 103 */ GSTATE_CHECK_SAVE,
    /* 104 */ GSTATE_LOGO_WAIT,
    /* 105 */ GSTATE_START,
} GameState;

typedef enum PlayState {
    /*   0 */ PLAY_STANDBY,
    /*   1 */ PLAY_INIT,
    /*   2 */ PLAY_UPDATE,
    /* 100 */ PLAY_PAUSE=100,
} PlayState;

typedef void (*TimerAction)(s32*, s32);

typedef struct {
    /* 0x00 */ u8 active;
    /* 0x08 */ OSTimer timer;
    /* 0x28 */ TimerAction action;
    /* 0x2C */ uintptr_t address;
    /* 0x30 */ s32 value;
} TimerTask; // size = 0x38, 0x8 aligned

typedef struct {
    /* 0x000 */ OSThread thread;
    /* 0x1B0 */ char stack[0x800];
    /* 0x9B0 */ OSMesgQueue mesgQueue;
    /* 0x9C8 */ OSMesg msg;
    /* 0x9CC */ FrameBuffer* fb;
    /* 0x9D0 */ u16 width;
    /* 0x9D2 */ u16 height;
} FaultMgr; // size = 0x9D8, 0x8 aligned

typedef enum {
    /* 0 */ SPTASK_STATE_NOT_STARTED,
    /* 1 */ SPTASK_STATE_RUNNING,
    /* 2 */ SPTASK_STATE_INTERRUPTED,
    /* 3 */ SPTASK_STATE_FINISHED,
    /* 4 */ SPTASK_STATE_FINISHED_DP
} SpTaskState;

typedef struct {
    /* 0x00 */ OSTask task;
    /* 0x40 */ OSMesgQueue* mesgQueue;
    /* 0x44 */ OSMesg msg;
    /* 0x48 */ SpTaskState state;
} SPTask; // size = 0x50, 0x8 aligned

typedef struct {
    /* 0x00000 */ SPTask task;
    /* 0x00050 */ Vp viewports[0x10 * 4];
    /* 0x00150 */ Mtx mtx[0x480 * 4];
    /* 0x12150 */ Gfx unkDL1[0x180 * 4];
    /* 0x12D50 */ Gfx masterDL[0x1380 * 4];
    /* 0x1C950 */ Gfx unkDL2[0xD80 * 4];
    /* 0x23550 */ Lightsn lights[0x100 * 4];
} GfxPool; // size = 0x2AD50, 0x8 aligned

void Controller_Init(void);
void Controller_UpdateInput(void);
void Controller_ReadData(void);
void Controller_Rumble(void);

s32 Timer_CreateTask(u64, TimerAction, s32*, s32);
void Timer_Increment(s32* address, s32 value);
void Timer_SetValue(s32* address, s32 value);
void Timer_CompleteTask(TimerTask*);
void Timer_Wait(u64);

void Fault_ThreadEntry(OSMesg);
void Fault_SetFrameBuffer(FrameBuffer*, u16, u16);
void Fault_Init(void);

typedef enum {
    /* 10 */ SI_READ_CONTROLLER = 10,
    /* 11 */ SI_READ_SAVE,
    /* 12 */ SI_WRITE_SAVE,
    /* 13 */ SI_RUMBLE,
    /* 14 */ SI_SAVE_FAILED,
    /* 15 */ SI_SAVE_SUCCESS,
    /* 16 */ SI_CONT_READ_DONE,
} SerialMesg;

extern_s OSContPad gControllerHold[4];
extern_s OSContPad gControllerPress[4];
extern_s u8 gControllerPlugged[4];
extern_s u32 gControllerLock;
extern_s u8 gControllerRumbleEnabled[4];
extern_s OSContPad sNextController[4];    //
extern_s OSContPad sPrevController[4];    //
extern_s OSContStatus sControllerStatus[4]; //
extern_s OSPfs sControllerMotor[4];        //

extern_s u8 gAudioThreadStack[0x1000];  // 800DDAA0
extern_s OSThread gGraphicsThread;        // 800DEAA0
extern_s u8 gGraphicsThreadStack[0x1000]; // 800DEC50
extern_s OSThread gTimerThread;        // 800DFC50
extern_s u8 gTimerThreadStack[0x1000]; // 800DFE00
extern_s OSThread gSerialThread;        // 800E0E00
extern_s u8 gSerialThreadStack[0x1000]; // 800E0FB0

extern_s SPTask* gCurrentTask;
extern_s SPTask* sAudioTasks[1];
extern_s SPTask* sGfxTasks[2];
#ifdef AVOID_UB
extern_s SPTask* sNewAudioTasks[2];
#else
extern_s SPTask* sNewAudioTasks[1];
#endif
extern_s SPTask* sNewGfxTasks[2];
extern_s u32 gSegments[16]; // 800E1FD0
extern_s OSMesgQueue gPiMgrCmdQueue; // 800E2010
extern_s OSMesg sPiMgrCmdBuff[50]; // 800E2028

extern_s OSMesgQueue gDmaMesgQueue;
extern_s OSMesg sDmaMsgBuff[1];
extern_s OSIoMesg gDmaIOMsg;
extern_s OSMesgQueue gSerialEventQueue;
extern_s OSMesg sSerialEventBuff[1];
extern_s OSMesgQueue gMainThreadMesgQueue;
extern_s OSMesg sMainThreadMsgBuff[32];
extern_s OSMesgQueue gTaskMesgQueue;
extern_s OSMesg sTaskMsgBuff[16];
extern_s OSMesgQueue gAudioVImesgQueue;
extern_s OSMesg sAudioVImsgBuff[1];
extern_s OSMesgQueue gAudioTaskMesgQueue;
extern_s OSMesg sAudioTaskMsgBuff[1];
extern_s OSMesgQueue gGfxVImesgQueue;
extern_s OSMesg sGfxVImsgBuff[4];
extern_s OSMesgQueue gGfxTaskMesgQueue;
extern_s OSMesg sGfxTaskMsgBuff[2];
extern_s OSMesgQueue gSerialThreadMesgQueue;
extern_s OSMesg sSerialThreadMsgBuff[8];
extern_s OSMesgQueue gControllerMesgQueue;
extern_s OSMesg sControllerMsgBuff[1];
extern_s OSMesgQueue gSaveMesgQueue;
extern_s OSMesg sSaveMsgBuff[1];
extern_s OSMesgQueue gTimerTaskMesgQueue;
extern_s OSMesg sTimerTaskMsgBuff[16];
extern_s OSMesgQueue gTimerWaitMesgQueue;
extern_s OSMesg sTimerWaitMsgBuff[1];

extern_s GfxPool gGfxPools[2]; // 800E23B0

extern_s GfxPool* gGfxPool;
extern_s SPTask* gGfxTask;
extern_s Vp* gViewport;
extern_s Mtx* gGfxMtx;
extern_s Gfx* gUnkDisp1;
extern_s Gfx* gMasterDisp;
extern_s Gfx* gUnkDisp2;
extern_s Lightsn* gLight;
extern_s FrameBuffer* gFrameBuffer;
extern_s u16* gTextureRender;

extern_s u8 gVIsPerFrame;
extern_s u32 gSysFrameCount;
extern_s u8 gStartNMI;
extern_s u8 gStopTasks;
extern_s u8 gControllerRumbleFlags[4];
extern_s u16 gFillScreenColor;
extern_s u16 gFillScreen;

extern_s u8 gUnusedStack[0x1000];
extern_s OSThread sIdleThread; // 80138E90
extern_s u8 sIdleThreadStack[0x1000]; // 801390A0
extern_s OSThread gMainThread; // 8013A040
extern_s u8 sMainThreadStack[0x1000]; // 8013A1F0
extern_s OSThread gAudioThread; //8013B1F0

#define MESG_QUEUE_EMPTY -1

#define MQ_GET_MESG(mq, mesg) (osRecvMesg((mq), (OSMesg*) (mesg), OS_MESG_NOBLOCK) != -1)
#define MQ_WAIT_FOR_MESG(mq, mesg) osRecvMesg((mq), (OSMesg*) (mesg), OS_MESG_BLOCK)
#define MQ_CLEAR_QUEUE(mq) do {s32 m1 = -1; s32 mesg; do {} while(osRecvMesg((mq), (OSMesg*) &(mesg), OS_MESG_NOBLOCK) != m1);} while(0)

#define FAULT_MESG_BREAK 1
#define FAULT_MESG_FAULT 2

#define TASK_MESG_1 1
#define TASK_MESG_2 2

#define EVENT_MESG_SP 1
#define EVENT_MESG_DP 2
#define EVENT_MESG_VI 3
#define EVENT_MESG_PRENMI 4

typedef enum {
    /* 0 */ THREAD_ID_SYSTEM,
    /* 1 */ THREAD_ID_IDLE,
    /* 2 */ THREAD_ID_FAULT,
    /* 3 */ THREAD_ID_MAIN,
    /* 4 */ THREAD_ID_4,
    /* 5 */ THREAD_ID_AUDIO,
    /* 6 */ THREAD_ID_GRAPHICS,
    /* 7 */ THREAD_ID_TIMER,
    /* 8 */ THREAD_ID_SERIAL,
} ThreadID;

#endif
