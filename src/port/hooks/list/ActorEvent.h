#pragma once

#include "gfx.h"
#include "sf64object.h"

// ────────────────────────────────────────────────────────────────────────────
// Object type discriminator
// Passed as the `type` field on every object event so listeners can quickly
// filter for the entity category they care about without casting `object`.
// ────────────────────────────────────────────────────────────────────────────

typedef enum {
    OBJECT_TYPE_ACTOR,       // standard enemy / NPC actor (Actor*)
    OBJECT_TYPE_ACTOR_EVENT, // scripted event actor (ActorEvent* / similar)
    OBJECT_TYPE_BOSS,        // boss entity (Boss*)
    OBJECT_TYPE_SCENERY,     // static scenery object (Scenery*)
    OBJECT_TYPE_SCENERY360,  // 360-mode scenery (Scenery360*)
    OBJECT_TYPE_SPRITE,      // billboard sprite (Sprite*)
    OBJECT_TYPE_ITEM,        // collectable item (Item*)
    OBJECT_TYPE_EFFECT,      // visual effect (Effect*)
} ObjectEventType;

// ────────────────────────────────────────────────────────────────────────────
// Object lifecycle events — game thread
// All events fire on the game thread inside the main entity update loop.
// `object` is always cast to void* to avoid forcing a dependency on every
// entity header; cast to the concrete type using `type` as the discriminator.
// Cancellable events block the corresponding default engine behaviour when
// event->Event.Cancelled is set to true by a listener.
// ────────────────────────────────────────────────────────────────────────────

// Fires when an object is initialised for the first time (spawned / allocated).
// Cancellable — cancel to suppress the default initialisation routine and take
// full control of the object's state from the listener.
//   type   — category of the object (use to select the correct cast)
//   object — void* pointer to the entity; cast based on `type`
DEFINE_EVENT(ObjectInitEvent,
    ObjectEventType type;
    void*           object;
);

// Fires each game frame when an object's update function runs.
// Cancellable — cancel to suppress the default update logic for this frame,
// allowing a listener to fully replace or pause object behaviour.
//   type   — category of the object
//   object — void* pointer to the entity; cast based on `type`
DEFINE_EVENT(ObjectUpdateEvent,
    ObjectEventType type;
    void*           object;
);

// Fires before an object's display-list setup (matrix push, material bind, etc.).
// Cancellable — cancel to suppress the default draw setup and draw call,
// allowing a listener to render a custom mesh or skip rendering entirely.
//   type   — category of the object
//   object — void* pointer to the entity; cast based on `type`
DEFINE_EVENT(ObjectDrawPreSetupEvent,
    ObjectEventType type;
    void*           object;
);

// Fires immediately after an object's display-list setup has completed and
// the default draw call has been issued. Not cancellable — use this to append
// additional draw calls (overlays, outlines, debug shapes) to the same matrix
// context before it is popped.
//   type   — category of the object
//   object — void* pointer to the entity; cast based on `type`
DEFINE_EVENT(ObjectDrawPostSetupEvent,
    ObjectEventType type;
    void*           object;
);

// Fires when an object is destroyed / removed from the active object pool.
// Cancellable — cancel to suppress the default destruction logic (e.g. to
// keep the object alive or to handle cleanup yourself).
//   type   — category of the object
//   object — void* pointer to the entity; cast based on `type`
DEFINE_EVENT(ObjectDestroyEvent,
    ObjectEventType type;
    void*           object;
);
