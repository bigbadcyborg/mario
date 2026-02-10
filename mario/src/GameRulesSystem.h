#ifndef GAME_RULES_SYSTEM_H
#define GAME_RULES_SYSTEM_H

#include "GameTypes.h"

class GameRulesSystem {
public:
    void apply(GameWorld& world, GameState& state, SDL_Plotter& plotter) const;
};

#endif
