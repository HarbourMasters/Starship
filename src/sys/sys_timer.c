#include "sys.h"

TimerTask sTimerTasks[16];

TimerTask* Timer_AllocateTask(void) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(sTimerTasks); i++) {
        if (!sTimerTasks[i].active) {
            return &sTimerTasks[i];
        }
    }
    return NULL;
}

int32_t Timer_CreateTask(uint64_t time, TimerAction action, s32* address, s32 value) {
    TimerTask* task = Timer_AllocateTask();

    if (task == NULL) {
        return -1;
    }
    task->active = true;
    task->action = action;
    task->address = address;
    task->value = value;
    return osSetTimer(&task->timer, time, 0, &gTimerTaskMsgQueue, OS_MESG_PTR(task));
}

void Timer_Increment(s32* address, s32 value) {
    *address += value;
}

void Timer_SetValue(s32* address, s32 value) {
    *address = value;
}

void Timer_CompleteTask(TimerTask* task) {
    if (task->action != NULL) {
        task->action(task->address, task->value);
    }
    task->active = false;
}
