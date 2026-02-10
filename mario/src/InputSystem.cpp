#include "InputSystem.h"

void InputSystem::process(SDL_Plotter& plotter, GameWorld& world, GameState& state) const {
    if (!plotter.getKey()) {
        return;
    }

    const char keyStroke = plotter.getKey();
    if (keyStroke == ' ' && !state.doneJumping && world.mario.getPosY() >= 10) {
        world.mario.addPosY(-6);
        state.positionIncrement += 1;
        if (state.positionIncrement >= 50) {
            state.doneJumping = true;
        }
        return;
    }

    world.mario.move(keyStroke, WINDOW_HEIGHT, WINDOW_WIDTH);
    if (keyStroke == RIGHT_ARROW) {
        state.facingRight = true;
    } else if (keyStroke == LEFT_ARROW) {
        state.facingRight = false;
    }
}
