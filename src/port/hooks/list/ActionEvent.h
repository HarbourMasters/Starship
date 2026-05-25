#pragma once

#include "sf64player.h"

// ────────────────────────────────────────────────────────────────────────────
// Player action events — game thread
// All events in this file fire on the game thread during player input
// processing. Cancellable events block the corresponding default action when
// event->Event.Cancelled is set to true by a listener.
// ────────────────────────────────────────────────────────────────────────────

// Fires when the player activates boost. Cancellable.
// Cancel to suppress the boost input (e.g. to implement a custom boost system
// or to disable boost in a specific game mode).
//   player — the player who triggered the boost
DEFINE_EVENT(PlayerActionBoostEvent,
    Player* player;
);

// Fires when the player activates brake. Cancellable.
// Cancel to suppress the brake input.
//   player — the player who triggered the brake
DEFINE_EVENT(PlayerActionBrakeEvent,
    Player* player;
);

// Fires before a laser shot is created. Cancellable.
// Cancel to suppress the shot entirely (no ProjectileShot is spawned).
// Fires for both single and twin-laser modes.
//   player — the player who is shooting
//   laser  — the laser strength / type being fired (LASER_SINGLE, LASER_TWIN, …)
DEFINE_EVENT(PlayerActionPreShootEvent,
    Player*       player;
    LaserStrength laser;
);

// Fires after a laser shot has been created and added to the shot pool.
// Not cancellable — the shot already exists at this point.
//   player — the player who fired
//   shot   — pointer to the newly created PlayerShot in the shot pool
DEFINE_EVENT(PlayerActionPostShootEvent,
    Player*     player;
    PlayerShot* shot;
);

// Fires before a charged shot is released. Cancellable.
// Cancel to suppress the charged shot (charge energy is still consumed).
//   player — the player releasing the charged shot
DEFINE_EVENT(PlayerActionPreShootChargedEvent,
    Player* player;
);

// Fires after a charged shot has been created and added to the shot pool.
// Not cancellable.
//   player — the player who released the charged shot
DEFINE_EVENT(PlayerActionPostShootChargedEvent,
    Player* player;
);

// Fires before a bomb is deployed. Cancellable.
// Cancel to suppress the bomb launch (the bomb count is not decremented).
// Fires for Arwing, Landmaster, and Blue Marine bomb types.
//   player — the player deploying the bomb
DEFINE_EVENT(PlayerActionPreBombEvent,
    Player* player;
);

// Fires after a bomb has been successfully deployed.
// Not cancellable — the bomb entity already exists at this point.
//   player — the player who deployed the bomb
DEFINE_EVENT(PlayerActionPostBombEvent,
    Player* player;
);
