#pragma once

#include "sf64player.h"
#include "port/hooks/impl/EventSystem.h"

DEFINE_EVENT(PlayerActionBoostEvent, Player* player;);

DEFINE_EVENT(PlayerActionBrakeEvent, Player* player;);

DEFINE_EVENT(PlayerActionPreShootEvent, Player* player; LaserStrength laser;);
DEFINE_EVENT(PlayerActionPostShootEvent, Player* player; PlayerShot* shot;);

DEFINE_EVENT(PlayerActionPreShootChargedEvent, Player* player;);
DEFINE_EVENT(PlayerActionPostShootChargedEvent, Player* player;);

DEFINE_EVENT(PlayerActionPreBombEvent, Player* player;);
DEFINE_EVENT(PlayerActionPostBombEvent, Player* player;);