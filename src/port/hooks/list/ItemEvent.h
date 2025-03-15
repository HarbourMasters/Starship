#ifndef __LUA__
#include "gfx.h"
#include "sf64object.h"
#include "port/hooks/impl/EventSystem.h"
#endif

DEFINE_EVENT(ItemDropEvent,
    Item* item;
);