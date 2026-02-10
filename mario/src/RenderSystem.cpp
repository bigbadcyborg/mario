#include "RenderSystem.h"

void RenderSystem::renderFrame(SDL_Plotter& plotter, GameWorld& world, const GameState& state, GameAssets& assets) const {
    for (int col = 0; col < WINDOW_WIDTH; col++) {
        for (int row = 0; row < WINDOW_HEIGHT; row++) {
            plotter.plotPixel(col, row, 0, 0, 0);
        }
    }

    for (int xd = 0; xd < ROW; xd++) {
        for (int yd = 0; yd < COL; yd++) {
            plotter.plotPixel(yd, xd, assets.hudPic[xd][yd].r, assets.hudPic[xd][yd].g, assets.hudPic[xd][yd].b);
        }
    }

    for (int i = 0; i < 6; i++) {
        world.platforms[i].drawObstacle(plotter, 255, 255, 255, 0, 0, 0);
    }

    world.tubeSide1.drawObstacle(plotter, 102, 204, 0);
    world.tubeTop1.drawObstacle(plotter, 102, 204, 0);
    world.tubeSide2.drawObstacle(plotter, 102, 204, 0);
    world.tubeTop2.drawObstacle(plotter, 102, 204, 0);
    world.pow.drawObstacle(plotter, assets.blockPixel);

    world.mario.drawMarioPixelArt(plotter,
        world.mario.getGravityStatus() ? assets.marioPixelJump : assets.marioPixelStill,
        state.facingRight);

    for (int i = 0; i < state.numEnemies; i++) {
        if (!world.enemies[i].getDead()) {
            world.enemies[i].drawMarioPixelArt(plotter, assets.enemyPixel, state.facingRight);
        }
    }

    for (int i = 0; i < state.numCoins; i++) {
        if (!world.coins[i].getDead()) {
            world.coins[i].drawCoinPixelArt(plotter, assets.coinPixel);
        }
    }

    numDisplay(plotter, assets.scoreVis, state.marioLives, 65, 0);
    numDisplay(plotter, assets.livesVis, state.score, 65, 20);
}
