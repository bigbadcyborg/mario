#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#include "../functions.h"

const int ROW = 40;
const int COL = 60;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 1000;

struct GameState {
    int positionIncrement = 0;
    bool doneJumping = false;
    int score = 0;
    int marioLives = 10;
    int level = 1;
    int numEnemies = 4;
    int deadEnemies = 0;
    int numCoins = 1;
    bool doneKilling = true;
    bool facingRight = true;
};

struct GameAssets {
    pixel hudPic[ROW][COL];
    int marioPixelStill[40][40];
    int marioPixelJump[40][40];
    int enemyPixel[40][40];
    int coinPixel[40][40];
    pixel scoreVis[18][22];
    pixel livesVis[18][22];
    int blockPixel[36][36];
};

struct GameWorld {
    Sprite mario;
    Sprite enemies[12];
    Sprite coins[15];
    Obstacle platforms[6];
    Obstacle tubeSide1;
    Obstacle tubeTop1;
    Obstacle tubeSide2;
    Obstacle tubeTop2;
    Block pow;
};

#endif
