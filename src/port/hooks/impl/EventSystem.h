#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef uint32_t EventID;
typedef uint32_t ListenerID;

typedef enum {
    EVENT_PRIORITY_LOW,
    EVENT_PRIORITY_NORMAL,
    EVENT_PRIORITY_HIGH,
} EventPriority;

typedef struct {
    bool cancelled;
} IEvent;

typedef void (*EventCallback)(IEvent*);

typedef struct {
    EventPriority priority;
    EventCallback function;
} EventListener;

#ifdef INIT_EVENT_IDS
#define DECLARE_EVENT(eventName) \
    uint32_t eventName##ID = -1;
#else
#define DECLARE_EVENT(eventName) \
    extern uint32_t eventName##ID;
#endif

#define DEFINE_EVENT(eventName, ...) \
    typedef struct { \
        IEvent event; \
        __VA_ARGS__ \
    } eventName; \
    \
    DECLARE_EVENT(eventName)

#define CALL_EVENT(eventType, ...) \
    eventType eventType##_ = { {false}, __VA_ARGS__ }; \
    EventSystem_CallEvent(eventType##ID, &eventType##_);

#define CALL_CANCELLABLE_EVENT(eventType, ...) \
    eventType eventType##_ = { {false}, __VA_ARGS__ }; \
    EventSystem_CallEvent(eventType##ID, &eventType##_); \
    if (!eventType##_.event.cancelled)

#define CHECK_IF_NOT_CANCELLED(eventType) \
    if (!eventType##_.event.cancelled)

#define CALL_CANCELLABLE_RETURN_EVENT(eventType, ...) \
    eventType eventType##_ = { {false}, __VA_ARGS__ }; \
    EventSystem_CallEvent(eventType##ID, &eventType##_); \
    if (eventType##_.event.cancelled) { \
        return; \
    }

#define REGISTER_EVENT(eventType) \
    eventType##ID = EventSystem_RegisterEvent();

#define REGISTER_LISTENER(eventType, callback, priority) \
    EventSystem_RegisterListener(eventType##ID, callback, priority);

#ifdef __cplusplus
#include <array>
#include <vector>
#include <unordered_map>

class EventSystem {
public:
    static EventSystem* Instance;
    EventID RegisterEvent();
    ListenerID RegisterListener(EventID id, EventCallback callback, EventPriority priority = EVENT_PRIORITY_NORMAL);
    void UnregisterListener(EventID ev, ListenerID id);
    void CallEvent(EventID id, IEvent* event);
private:
    std::unordered_map<EventID, std::vector<EventListener>> mEventListeners;
    EventID mInternalEventID = 0;
};
#else
extern EventID EventSystem_RegisterEvent();
extern ListenerID EventSystem_RegisterListener(EventID id, EventCallback callback, EventPriority priority);
extern void EventSystem_UnregisterListener(EventID ev, ListenerID id);
extern void EventSystem_CallEvent(EventID id, void* event);
#endif