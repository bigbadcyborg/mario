#include "PhysicsSystem.h"

void PhysicsSystem::update(GameWorld& world, const GameState& state) const {
    if (world.mario.getGravityStatus()) {
        world.mario.gravity(WINDOW_HEIGHT, WINDOW_WIDTH);
    }

    for (int i = 0; i < state.numEnemies; i++) {
        if (!world.enemies[i].getDead()) {
            if (i % 2 == 0) {
                world.enemies[i].autoMove();
            } else {
                world.enemies[i].autoMove1();
            }
        } else {
            world.enemies[i].setPosY(0);
        }
    }
    grav(world.enemies, state.numEnemies);

    for (int i = 0; i < state.numCoins; i++) {
        if (!world.coins[i].getDead()) {
            if (i % 2 == 0) {
                world.coins[i].autoMove2();
            } else {
                world.coins[i].autoMove3();
            }
        } else {
            world.coins[i].setPosY(0);
        }
    }
    grav(world.coins, state.numCoins);

    if (world.mario.getPosX() == 0) {
        world.mario.setPosX(960);
    } else if (world.mario.getPosX() + world.mario.getWidth() == WINDOW_WIDTH) {
        world.mario.setPosX(0);
    }

    checkPos(world.enemies, state.numEnemies);
    checkPos(world.coins, state.numCoins);
}
