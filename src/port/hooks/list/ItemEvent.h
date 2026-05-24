#pragma once

#include "gfx.h"
#include "sf64object.h"

// ────────────────────────────────────────────────────────────────────────────
// Item events — game thread
// ────────────────────────────────────────────────────────────────────────────

// Fires when an item is about to be spawned as a world drop.
// Cancellable — cancel to suppress the spawn entirely (e.g. to replace the
// drop with a custom item, or to remove drops in a no-item game mode).
// Fires in multiple contexts: enemy death drops, scripted demo drops, and
// forced drops from the enemy manager.
//   item — pointer to the Item struct that was just populated; the item has
//          been configured (type, position, etc.) but not yet added to the
//          active item list — modifying fields here takes effect immediately
DEFINE_EVENT(ItemDropEvent,
    Item* item;
);
