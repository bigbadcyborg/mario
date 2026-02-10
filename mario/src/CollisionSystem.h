#ifndef COLLISION_SYSTEM_H
#define COLLISION_SYSTEM_H

#include "GameTypes.h"

class CollisionSystem {
public:
    void process(GameWorld& world, GameState& state) const;
};

#endif
