#include "GameRulesSystem.h"
#include <iostream>

using namespace std;

void GameRulesSystem::apply(GameWorld& world, GameState& state, SDL_Plotter& plotter) const {
    if (state.marioLives == 0) {
        plotter.setQuit(true);
    }

    if (state.deadEnemies == state.numEnemies) {
        state.level++;
        reviveAll(world.enemies, state.numEnemies);
        state.numEnemies += 2;
        world.coins[0].setDead(true);
        if (state.level < 6) {
            cout << "\nLevel beat! Approaching level " << state.level;
            cout << "\nNow spawning " << state.numEnemies << " enemies ... ";
            state.deadEnemies = 0;
        }
    }

    if (state.level == 6) {
        cout << "You won" << endl;
        plotter.setQuit(true);
    }
}
