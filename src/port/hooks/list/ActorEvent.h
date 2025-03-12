#ifndef __LUA__
#include "gfx.h"
#include "sf64object.h"
#include "port/hooks/impl/EventSystem.h"

typedef enum ObjectEventType {
    OBJECT_TYPE_ACTOR,
    OBJECT_TYPE_ACTOR_EVENT,
    OBJECT_TYPE_BOSS,
    OBJECT_TYPE_SCENERY,
    OBJECT_TYPE_SCENERY360,
    OBJECT_TYPE_SPRITE,
    OBJECT_TYPE_ITEM,
    OBJECT_TYPE_EFFECT,
} ObjectEventType;
#endif

DEFINE_EVENT(ObjectInitEvent,
    ObjectEventType type;
    Object* object;
);

DEFINE_EVENT(ObjectUpdateEvent,
    ObjectEventType type;
    Object* object;
);

DEFINE_EVENT(ObjectDrawPreSetupEvent,
    ObjectEventType type;
    Object* object;
);

DEFINE_EVENT(ObjectDrawPostSetupEvent,
    ObjectEventType type;
    Object* object;
);

DEFINE_EVENT(ObjectDestroyEvent,
    ObjectEventType type;
    Object* object;
);