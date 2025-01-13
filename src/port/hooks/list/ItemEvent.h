#pragma once

#include "gfx.h"
#include "sf64object.h"
#include "port/hooks/impl/EventSystem.h"

DEFINE_EVENT(ItemDropEvent,
    Item* item;
);