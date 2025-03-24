#include "EventSystem.h"
#include <stdexcept>
#include <algorithm>
#include "port/hooks/Events.h"
#include "port/notification/notification.h"

EventSystem* EventSystem::Instance = new EventSystem();

EventID EventSystem::RegisterEvent() {
    return this->mInternalEventID++;
}

ListenerID EventSystem::RegisterListener(EventID id, const SmartFunctionCallback& callback, EventPriority priority) {
    if(id == -1) {
        throw std::runtime_error("Trying to register listener for unregistered event");
    }

    auto& listeners = this->mEventListeners[id];

    if(std::find_if(listeners.begin(), listeners.end(), [callback](const EventListener& listener) {
        return listener.function == callback;
    }) != listeners.end()) {
        throw std::runtime_error("Listener already registered");
    }

    listeners.push_back(EventListener{ priority, callback });

    // Sort by priority
    std::sort(listeners.begin(), listeners.end(), [](const EventListener& a, const EventListener& b) {
        return a.priority < b.priority;
    });

    return listeners.size() - 1;
}

void EventSystem::UnregisterListener(EventID id, ListenerID listenerId) {
    auto& listeners = this->mEventListeners[id];

    listeners.erase(listeners.begin() + listenerId);
}

void EventSystem::CallEvent(EventID id, IEvent* event) {
    auto& listeners = this->mEventListeners[id];

    for (auto& listener : listeners) {
        if(is_type(listener.function, EventCallback)){
            std::get<EventCallback>(listener.function)(event);
        }

        if(is_type(listener.function, sol::protected_function)){
            #undef DEFINE_EVENT
            #define DEFINE_EVENT(eventName, ...) \
                if(id == eventName##ID) { \
                    auto result = std::get<sol::protected_function>(listener.function)((eventName*)event); \
                    if(!result.valid()) { \
                        sol::error err = result; \
                        SPDLOG_ERROR(std::string(err.what())); \
                        Notification::Emit({ .message = "Mod error, check log for details", .messageColor = ImVec4(1.0f, 0.5f, 0.5f, 1.0f), .remainingTime = 7.0f }); \
                    } \
                }
            #define __LUA__
            #include "port/hooks/EventList.h"
            #undef __LUA__
            {
                // throw std::runtime_error("Unknown event type");
            }
        }
    }
}

extern "C" EventID EventSystem_RegisterEvent() {
    return EventSystem::Instance->RegisterEvent();
}

extern "C" ListenerID EventSystem_RegisterListener(EventID id, EventCallback callback, EventPriority priority) {
    return EventSystem::Instance->RegisterListener(id, callback, priority);
}

extern "C" void EventSystem_UnregisterListener(EventID ev, ListenerID id) {
    EventSystem::Instance->UnregisterListener(ev, id);
}

extern "C" void EventSystem_CallEvent(EventID id, void* event) {
    EventSystem::Instance->CallEvent(id, static_cast<IEvent*>(event));
}