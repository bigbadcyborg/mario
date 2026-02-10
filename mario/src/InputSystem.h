#ifndef INPUT_SYSTEM_H
#define INPUT_SYSTEM_H

#include "GameTypes.h"

class InputSystem {
public:
    void process(SDL_Plotter& plotter, GameWorld& world, GameState& state) const;
};

#endif
