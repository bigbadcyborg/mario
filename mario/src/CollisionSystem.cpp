#include "CollisionSystem.h"
#include <iostream>

using namespace std;

void CollisionSystem::process(GameWorld& world, GameState& state) const {
    for (int i = 0; i < state.numEnemies; i++) {
        if (world.mario.isTouchingTopOf(world.enemies[i]) && state.doneKilling) {
            kill(world.enemies[i]);
            state.deadEnemies++;
            state.score += 1;
            world.mario.setGravity(false);
            world.mario.addPosY(-10);
            cout << "\nEnemy killed! " << state.numEnemies - state.deadEnemies << " remaining.\n";
            state.doneKilling = false;
        } else if (world.mario.collidesWith(world.enemies[i])
                   && world.mario.getPosY() + world.mario.getHeight() > world.enemies[i].getPosY()
                   && !world.enemies[i].getDead()) {
            world.mario.setPosX(WINDOW_WIDTH / 2);
            world.mario.setPosY(30);
            state.marioLives -= 1;
            cout << "\nYou have died! " << state.marioLives << " lives remaining.\n";
        }
    }

    for (int i = 0; i < state.numCoins; i++) {
        if (world.mario.collidesWith(world.coins[i]) && !world.coins[i].getDead()) {
            state.score += 1;
            kill(world.coins[i]);
            cout << "\nYou got a coin" << endl;
        }
    }

    for (int i = 0; i < 6; i++) {
        if (world.mario.isTouchingTopOf(world.platforms[i])) {
            world.mario.setGravity(false);
            state.positionIncrement = 0;
            state.doneJumping = false;
        }
    }

    if (world.mario.collidesWith(world.pow)) {
        world.mario.setPosX(50);
        world.mario.setPosY(50);
    }

    for (int i = 0; i < state.numEnemies; i++) {
        if (collided(world.enemies[i], world.platforms, 6)) {
            world.enemies[i].setGravity(false);
        } else {
            world.enemies[i].setGravity(true);
        }
    }

    for (int i = 0; i < state.numCoins; i++) {
        if (collided(world.coins[i], world.platforms, 6)) {
            world.coins[i].setGravity(false);
        } else {
            world.coins[i].setGravity(true);
        }
    }

    if (collided(world.mario, world.platforms, 6)) {
        world.mario.setGravity(false);
        state.positionIncrement = 0;
        state.doneJumping = false;
        state.doneKilling = true;
    } else {
        world.mario.setGravity(true);
    }
}
