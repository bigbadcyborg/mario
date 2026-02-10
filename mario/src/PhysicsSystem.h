#ifndef PHYSICS_SYSTEM_H
#define PHYSICS_SYSTEM_H

#include "GameTypes.h"

class PhysicsSystem {
public:
    void update(GameWorld& world, const GameState& state) const;
};

#endif
