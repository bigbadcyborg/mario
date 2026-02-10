#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include "GameTypes.h"

class RenderSystem {
public:
    void renderFrame(SDL_Plotter& plotter, GameWorld& world, const GameState& state, GameAssets& assets) const;
};

#endif
