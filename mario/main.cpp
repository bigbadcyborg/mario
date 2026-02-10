/*
Authors: Sully, Lauren, Sam, Riley, Cole
Assignment Title: Mario Brothers
Assignment Description: Re-create the video game mario bros
Due Date: 11/30/18
Date Created: 11/11/18
Date Last Modified: 11/30/18
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "SDL_Plotter.h"
#include "functions.h"
#include "src/GameTypes.h"
#include "src/InputSystem.h"
#include "src/PhysicsSystem.h"
#include "src/CollisionSystem.h"
#include "src/RenderSystem.h"
#include "src/GameRulesSystem.h"

using namespace std;

namespace {

void loadHud(GameAssets& assets) {
    ifstream infile("foo.txt");
    if (!infile) {
        cout << "Error";
        return;
    }

    for (int i = 0; i < ROW; i++) {
        for (int k = 0; k < COL; k += 3) {
            infile >> assets.hudPic[i][k].r;
            infile >> assets.hudPic[i][k].g;
            infile >> assets.hudPic[i][k].b;

            assets.hudPic[i][k + 1] = assets.hudPic[i][k];
            assets.hudPic[i][k + 2] = assets.hudPic[i][k];
        }
    }
}

void loadSpritePixels(const char* fileName, int pixels[40][40], int width, int height) {
    ifstream infile(fileName);
    if (!infile) {
        cout << "Error";
        return;
    }

    infile.ignore(100, '\n');
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < height; row++) {
            infile >> pixels[col][row];
        }
    }
}

void loadPowPixels(GameAssets& assets, const Block& pow) {
    ifstream infile("powBlock.txt");
    if (!infile) {
        cout << "ERROR";
        return;
    }

    infile.ignore(100, '\n');
    for (int col = 0; col < pow.getWidth(); col++) {
        for (int row = 0; row < pow.getHeight(); row++) {
            infile >> assets.blockPixel[col][row];
        }
    }
}

void loadScoreboard(GameAssets& assets) {
    ifstream scoreBoard("scoreBoard.txt");
    if (!scoreBoard) {
        cout << "ERROR";
        return;
    }

    int scoreDig;
    for (int i = 0; i < 18; i += 2) {
        for (int p = 0; p < 22; p += 2) {
            scoreBoard >> scoreDig;
            int color = scoreDig == 1 ? 255 : 0;
            assets.scoreVis[i][p].r = assets.scoreVis[i + 1][p + 1].r = assets.scoreVis[i + 1][p].r = assets.scoreVis[i][p + 1].r = color;
            assets.scoreVis[i][p].g = assets.scoreVis[i + 1][p + 1].g = assets.scoreVis[i + 1][p].g = assets.scoreVis[i][p + 1].g = color;
            assets.scoreVis[i][p].b = assets.scoreVis[i + 1][p + 1].b = assets.scoreVis[i + 1][p].b = assets.scoreVis[i][p + 1].b = color;

            assets.livesVis[i][p].r = assets.livesVis[i + 1][p + 1].r = assets.livesVis[i + 1][p].r = assets.livesVis[i][p + 1].r = color;
            assets.livesVis[i][p].g = assets.livesVis[i + 1][p + 1].g = assets.livesVis[i + 1][p].g = assets.livesVis[i][p + 1].g = color;
            assets.livesVis[i][p].b = assets.livesVis[i + 1][p + 1].b = assets.livesVis[i + 1][p].b = assets.livesVis[i][p + 1].b = color;
        }
    }
}

GameWorld buildWorld() {
    GameWorld world = {
        Sprite(),
        {
            Sprite(rand() % (WINDOW_WIDTH - 40), 0, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 199, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 500, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 399, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 125, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 399, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 500, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 0, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 0, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 0, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 0, 40, 40, 60, 60, 60),
            Sprite(rand() % (WINDOW_WIDTH - 40), 0, 40, 40, 60, 60, 60)
        },
        {
            Sprite(800, 10, 40, 40, 255, 255, 0),
            Sprite(rand() % WINDOW_WIDTH, 0, 40, 40, 255, 255, 0),
            Sprite(rand() % WINDOW_WIDTH, 0, 40, 40, 255, 255, 0),
            Sprite(rand() % WINDOW_WIDTH, 0, 40, 40, 255, 255, 0),
            Sprite(480, 0, 40, 40, 255, 255, 0),
            Sprite(275, 0, 40, 40, 255, 255, 0),
            Sprite(300, 0, 40, 40, 255, 255, 0),
            Sprite(455, 0, 40, 40, 255, 255, 0),
            Sprite(240, 0, 40, 40, 255, 255, 0),
            Sprite(40, 0, 40, 40, 255, 255, 0),
            Sprite(20, 0, 40, 40, 255, 255, 0),
            Sprite(900, 0, 40, 40, 255, 255, 0),
            Sprite(600, 0, 40, 40, 255, 255, 0),
            Sprite(700, 0, 40, 40, 255, 255, 0),
            Sprite(800, 0, 40, 40, 255, 255, 0)
        },
        {
            Obstacle(25, 350, 0, 425),
            Obstacle(25, 350, 650, 425),
            Obstacle(25, 500, 250, 280),
            Obstacle(25, 350, 0, 125),
            Obstacle(25, 350, 650, 125),
            Obstacle(25, WINDOW_WIDTH, 0, WINDOW_HEIGHT - 25)
        },
        Obstacle(75, 25, 0, 50),
        Obstacle(25, 50, 0, 50),
        Obstacle(75, 25, 975, 50),
        Obstacle(25, 50, 945, 50),
        Block(36, 36, 482, 350)
    };

    return world;
}

}

int main(int argc, char** argv) {
    srand(time(0));

    SDL_Plotter plotter(WINDOW_HEIGHT, WINDOW_WIDTH);

    GameState state;
    GameWorld world = buildWorld();
    GameAssets assets;

    loadHud(assets);
    loadSpritePixels("marioStill.txt", assets.marioPixelStill, world.mario.getWidth(), world.mario.getHeight());
    loadSpritePixels("marioJump.txt", assets.marioPixelJump, world.mario.getWidth(), world.mario.getHeight());
    loadSpritePixels("enemyPixel.txt", assets.enemyPixel, world.enemies[0].getWidth(), world.enemies[0].getHeight());
    loadSpritePixels("coinToken.txt", assets.coinPixel, world.coins[0].getWidth(), world.coins[0].getHeight());
    loadPowPixels(assets, world.pow);
    loadScoreboard(assets);

    InputSystem inputSystem;
    PhysicsSystem physicsSystem;
    CollisionSystem collisionSystem;
    RenderSystem renderSystem;
    GameRulesSystem gameRulesSystem;

    while (!plotter.getQuit()) {
        inputSystem.process(plotter, world, state);
        physicsSystem.update(world, state);
        collisionSystem.process(world, state);
        gameRulesSystem.apply(world, state, plotter);
        renderSystem.renderFrame(plotter, world, state, assets);

        if (plotter.kbhit()) {
            plotter.getKey();
        }
        plotter.update();
    }

    return 0;
}
