/*
Authors: Sully, Lauren, Sam, Riley, Cole
Assignment Title: Mario Brothers
Assignment Description: Re-create the video game mario bros
Due Date: 11/30/18
Date Created: 11/11/18
Date Last Modified: 11/30/18
*/
#include <iostream>
#include "SDL_Plotter.h"
#include "functions.h"
#include "LevelLoader.h"
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;
const int ROW = 40;
const int COL = 60;

int main(int argc, char ** argv)
{
    //random number seed
    srand(time(0));

    int positionIncrement = 0; //for jumping
    bool doneJumping = false; //for jumping
    int score = 0;


    int marioLives = 10; //mario's lives

    LevelLoader levelLoader;
    LevelData levelData = levelLoader.load("assets/levels/level1.json");

    int level = levelData.progression.startLevel;
    int numEnemies = levelData.progression.initialEnemyCount;
    int deadEnemies = 0;
    int numCoins = levelData.progression.initialCoinCount;

    const int WINDOW_HEIGHT = 600; // GAME HEIGHT
    const int WINDOW_WIDTH = 1000; //WINDOW WIDTH
    SDL_Plotter g(WINDOW_HEIGHT,WINDOW_WIDTH); //the window class

    char keyStroke; // used to determine what key is hit
    Sprite mario;
    vector<EntityRecord> enemyRecords = levelData.recordsByType("enemy");
    vector<EntityRecord> coinRecords = levelData.recordsByType("coin");
    vector<EntityRecord> platformRecords = levelData.recordsByType("platform");
    vector<EntityRecord> tubeRecords = levelData.recordsByType("tube");
    vector<EntityRecord> powRecords = levelData.recordsByType("pow");

    vector<Sprite> enemies;
    enemies.reserve(enemyRecords.size());
    for (int i = 0; i < enemyRecords.size(); i++) {
        enemies.push_back(Sprite(enemyRecords[i].x, enemyRecords[i].y,
                                 enemyRecords[i].height, enemyRecords[i].width,
                                 60, 60, 60));
    }

    vector<Sprite> coins;
    coins.reserve(coinRecords.size());
    for (int i = 0; i < coinRecords.size(); i++) {
        coins.push_back(Sprite(coinRecords[i].x, coinRecords[i].y,
                               coinRecords[i].height, coinRecords[i].width,
                               255, 255, 0));
    }

    //reads in file for score and lives
    ifstream infile;
    infile.open("foo.txt");
    if(!infile)
        cout << "Error";
    pixel pic[ROW][COL];
    for (int i =0; i<ROW; i++)
    {
        for(int k =0; k<COL; k+=3)
        {
            infile>>pic[i][k].r;
            infile>>pic[i][k].g;
            infile>>pic[i][k].b;

            pic[i][k+1].r = pic[i][k].r;
            pic[i][k+1].g = pic[i][k].g;
            pic[i][k+1].b = pic[i][k].b;

            pic[i][k+2].r = pic[i][k+1].r;
            pic[i][k+2].g = pic[i][k+1].g;
            pic[i][k+2].b = pic[i][k+1].b;
        }
    }
    infile.close();

    //Sam's New stuff
    int marioPixelStill[40][40];
    int a;
    infile.open("marioStill.txt");
    if(!infile)
        cout << "Error";
    infile.ignore(100, '\n');
    for (int col = 0; col < mario.getWidth(); col++){
        for (int row = 0; row < mario.getHeight(); row++){
            infile >> marioPixelStill[col][row];
        }
    }
    infile.close();

    int marioPixelJump[40][40];
    infile.open("marioJump.txt");
    if(!infile)
        cout << "Error";
    infile.ignore(100, '\n');
    for (int col = 0; col < mario.getWidth(); col++){
        for (int row = 0; row < mario.getHeight(); row++){
            infile >> marioPixelJump[col][row];
        }
    }
    infile.close();

    int enemyPixel[40][40];
    infile.open("enemyPixel.txt");
    if(!infile)
        cout << "Error";
    infile.ignore(100, '\n');
    for (int col = 0; col < 40; col++){
        for (int row = 0; row < 40; row++){
            infile >> enemyPixel[col][row];
        }
    }
    infile.close();

    int coinPixel[40][40];
    infile.open("coinToken.txt");
    infile.ignore(100, '\n');
    for (int col = 0; col < 40; col++){
        for (int row = 0; row < 40; row++){
            infile >> coinPixel[col][row];
        }
    }
    infile.close();

    ifstream scoreBoard;
    scoreBoard.open("scoreBoard.txt");
    if(!scoreBoard)
        cout << "ERROR";
    int scoreDig;
    pixel scoreVis[18][22];
    pixel livesVis[18][22];

    // set the array pixels for both the score and lives
    for(int i = 0; i < 18; i+=2)
    {
        for(int p = 0; p < 22; p+=2)
        {
            scoreBoard >> scoreDig;
            if(scoreDig == 1)
            {
                scoreVis[i][p].r = scoreVis[i+1][p+1].r = scoreVis[i+1][p].r = scoreVis[i][p+1].r = 255;
                scoreVis[i][p].g = scoreVis[i+1][p+1].g = scoreVis[i+1][p].g = scoreVis[i][p+1].g = 255;
                scoreVis[i][p].b = scoreVis[i+1][p+1].b = scoreVis[i+1][p].b = scoreVis[i][p+1].b = 255;

                livesVis[i][p].r = livesVis[i+1][p+1].r = livesVis[i+1][p].r = livesVis[i][p+1].r = 255;
                livesVis[i][p].g = livesVis[i+1][p+1].g = livesVis[i+1][p].g = livesVis[i][p+1].g = 255;
                livesVis[i][p].b = livesVis[i+1][p+1].b = livesVis[i+1][p].b = livesVis[i][p+1].b = 255;
            }

            if(scoreDig == 0)
            {
                scoreVis[i][p].r = scoreVis[i+1][p+1].r = scoreVis[i+1][p].r = scoreVis[i][p+1].r = 0;
                scoreVis[i][p].g = scoreVis[i+1][p+1].g = scoreVis[i+1][p].g = scoreVis[i][p+1].g = 0;
                scoreVis[i][p].b = scoreVis[i+1][p+1].b = scoreVis[i+1][p].b = scoreVis[i][p+1].b = 0;

                livesVis[i][p].r = livesVis[i+1][p+1].r = livesVis[i+1][p].r = livesVis[i][p+1].r = 0;
                livesVis[i][p].g = livesVis[i+1][p+1].g = livesVis[i+1][p].g = livesVis[i][p+1].g = 0;
                livesVis[i][p].b = livesVis[i+1][p+1].b = livesVis[i+1][p].b = livesVis[i][p+1].b = 0;
            }
        }
    }
    scoreBoard.close();



    // Platform Obstacles loaded from level data
    Obstacle platforms[6];
    for (int i = 0; i < 6; i++) {
        platforms[i] = Obstacle(platformRecords[i].height, platformRecords[i].width,
                                platformRecords[i].x, platformRecords[i].y);
    }

    Obstacle tubes[4];
    for (int i = 0; i < 4; i++) {
        tubes[i] = Obstacle(tubeRecords[i].height, tubeRecords[i].width,
                            tubeRecords[i].x, tubeRecords[i].y);
    }

    Block pow(powRecords[0].height, powRecords[0].width, powRecords[0].x, powRecords[0].y);
    int blockPixel[36][36];
    infile.open("powBlock.txt");
    if(!infile){
        cout << "ERROR";
    }
    infile.ignore(100, '\n');
    for (int col = 0; col < pow.getWidth(); col++){
        for (int row = 0; row < pow.getHeight(); row++){
            infile >> blockPixel[col][row];
        }
    }
    infile.close();
    //cout<<bottomPlat.getPosY()<<endl;

    bool doneKilling = true;

    bool facingRight = true; //if mario is facing right

    while (!g.getQuit()) // ONE FRAME OF THE LOOP
    {

            //draw background
            for (int col = 0; col < WINDOW_WIDTH; col++)
                for (int row = 0; row < WINDOW_HEIGHT; row++) {
                    g.plotPixel(col, row, 0, 0, 0);
                }

            //draws score and lives
            for (int xd = 0; xd < ROW; xd++) {
                for (int yd = 0; yd < COL; yd++) {

                    g.plotPixel(yd, xd, pic[xd][yd].r, pic[xd][yd].g, pic[xd][yd].b);
                }
            }
            //draw platforms
            for (int i = 0; i < 6; i++) {
                platforms[i].drawObstacle(g,255,255,255,0,0,0);
            }
            for (int i = 0; i < 4; i++) {
                tubes[i].drawObstacle(g, 102, 204, 0);
            }
            pow.drawObstacle(g, blockPixel); //SS this is changed plz upload

            // draw mario at the beginning of each frame
            //mario.draw(g);


        /*//coin gravity
        for(int i = 0; i < numCoins; i++)
            if (coins[i].getGravityStatus()) {
                coins[i].gravity(WINDOW_HEIGHT, WINDOW_WIDTH);
            }*/



        mario.drawMarioPixelArt(g, marioPixelStill, facingRight); //SS all new


        //MARIO MOVEMENTS
            if (g.getKey()) {
                {
                    keyStroke = g.getKey();
                    //jump if space bar hit, not jumping, ALSO cant go through ceiling
                    if (keyStroke == ' ' && !doneJumping && mario.getPosY() >= 10) {
                        // mario.setColors(0, 0, 0); //color black
                        mario.addPosY(-6); //move y up
                        mario.drawMarioPixelArt(g, marioPixelJump, facingRight); //draw
                        //mario.setColors(255, 255, 255); //color
                        positionIncrement += 1; //accumulate
                        if (positionIncrement >= 50) {
                            doneJumping = true;
                        }

                    } else {
                        mario.move(keyStroke, WINDOW_HEIGHT, WINDOW_WIDTH); //otherwise move
                        if (keyStroke == RIGHT_ARROW){
                            facingRight = true;
                        } else if (keyStroke == LEFT_ARROW){
                            facingRight = false;
                        }
                    }
                }
            }

        //activate gravity
        if (mario.getGravityStatus()) {
            mario.gravity(WINDOW_HEIGHT, WINDOW_WIDTH);
            mario.drawMarioPixelArt(g, marioPixelJump, facingRight);
        }





        //if mario's bottom touches top of enemy, kill enemy
        //else if mario touches enemy kill mario
        for (int i = 0; i < numEnemies; i++) {
            if (mario.isTouchingTopOf(enemies[i]) & doneKilling) {
                kill(enemies[i]);
                deadEnemies++ ;
                score += 1;
                mario.setGravity(false);
                mario.addPosY(-100);
                mario.drawMarioPixelArt(g, marioPixelJump, facingRight);
                cout << "\nEnemy killed! " << numEnemies - deadEnemies << " remaining.\n";
                doneKilling = false;

            }
                //kill mario
            else if (mario.collidesWith(enemies[i]) && !enemies[i].getDead()) {
                mario.setPosX(WINDOW_WIDTH / 2);
                mario.setPosY(30);
                marioLives -= 1;
                cout << "\nYou have died! " << marioLives << " lives remaining.\n";
            }
        }


        //dont remove
        if(mario.getGravityStatus())
        mario.gravity(WINDOW_HEIGHT,WINDOW_WIDTH);

        //if mario's bottom touches top of enemy, kill enemy
        //else if mario touches enemy kill mario
        for (int i = 0; i < numEnemies; i++) {
            if (mario.isTouchingTopOf(enemies[i]) & doneKilling) {
                kill(enemies[i]);
                deadEnemies++ ;
                score += 1;
                mario.setGravity(false);
                mario.addPosY(-10);
                cout << "\nEnemy killed! " << numEnemies - deadEnemies << " remaining.\n";
                doneKilling = false;

            }
                //kill mario
            else if (mario.collidesWith(enemies[i]) && mario.getPosY()+mario.getHeight() > enemies[i].getPosY() && !enemies[i].getDead()) {
                mario.setPosX(WINDOW_WIDTH / 2);
                mario.setPosY(30);
                marioLives -= 1;
                cout << "\nYou have died! " << marioLives << " lives remaining.\n";
            }
        }

        //if enemy not dead draw and move
        // drawEnemies(g, enemies, numEnemies);
        //turn on gravity for enemies
        //Draw enemies and automove
        for (int i = 0; i < numEnemies; i++) {
            if (!enemies[i].getDead()) {


                if (i % 2 == 0) {
                    enemies[i].autoMove();
                }
                //move other way
                if (i % 2 != 0) {
                    enemies[i].autoMove1();
                }

                enemies[i].drawMarioPixelArt(g, enemyPixel, facingRight);
            }
            else
                enemies[i].setPosY(0);
        }
        grav(&enemies[0], numEnemies);

        //draw coins if theyre not dead
        for (int i = 0; i < numCoins; i++) {
            if (!coins[i].getDead()) {
                if (i % 2 == 0) {
                    coins[i].autoMove2();
                }
                //move other way
                if (i % 2 != 0) {
                    coins[i].autoMove3();
                }
                coins[i].drawCoinPixelArt(g, coinPixel);
            }
            else
                coins[i].setPosY(0);
        }
        grav(&coins[0], numCoins);









            //S on reaching side of window, teleports to opposite side
            if (mario.getPosX() == 0) {
                mario.setPosX(960);
            } else if (mario.getPosX() + mario.getWidth() == 1000) {
                mario.setPosX(0);
            }

            //teleport enemies to opposite side
            checkPos(&enemies[0], numEnemies);

            //coin teleport
            if (coins[0].getPosX() == 0 && coins[0].getPosY() + coins[0].getWidth() > 10) { //S
                coins[0].setPosX(960);
            } else if (coins[0].getPosX() + coins[0].getWidth() == 1000) {
                coins[0].setPosX(0);
            }

            //==============================COLLISIONS===============================

        //mario to coin
        for(int i =0; i<numCoins; i++)
        {
            if (mario.collidesWith(coins[i]) && !coins[i].getDead()) {
                score += 1;
                kill(coins[i]);
                cout<<"\nYou got a coin"<<endl;
            }
        }


        //if sprite collides with any obstacle,
            //set positionIncrement to zero(for jumping)

             //mario to platform collision
            for (int i = 0; i < 6; i++)
                if (mario.isTouchingTopOf(platforms[i])) {
                    mario.setGravity(false);
                    positionIncrement = 0;
                    doneJumping = false;
                }

                    //mario to power button
            if (mario.collidesWith(pow)) {
                //mario.setGravity(false);
                mario.setPosX(50);
                mario.setPosY(50);
                //mario.setColors(0, 0, 0);

            }



            //ENEMIES TO PLATFORM COLLISION
            for (int i = 0; i < numEnemies; i++) {
                if (collided(enemies[i], platforms, 6)) {
                    enemies[i].setGravity(false);
                    //positionIncrement = 0;
                } else {
                    enemies[i].setGravity(true);
                }
            }

//COIN TO PLATFORM COLLISION
        for(int i = 0; i < numCoins; i++){
            if (collided(coins[i], platforms, 6)) {
                coins[i].setGravity(false);
                //cout << "COIN COLLIDED!!!";
            } else {
                coins[i].setGravity(true);
                grav(&coins[0], numCoins);
            }
    }
    checkPos(&coins[0], numCoins);
    //checkPos(enemies, numEnemies - deadEnemies);

            //=================================================================================




            //recheck mario collision and set gravity accordingly
            if (collided(mario, platforms, 6)) {
                mario.setGravity(false);
                positionIncrement = 0;
                doneJumping = false;
                doneKilling = true;
            } else
                mario.setGravity(true);


            if (marioLives == 0) //mario runs out of lives, quit game
                g.setQuit(true);

//all enemies killed, next level
            if (deadEnemies == numEnemies) {
                level++;
                //bring all enemies back to life
                reviveAll(&enemies[0], numEnemies);
                numEnemies += levelData.progression.enemyIncrementPerLevel;
                if (numEnemies > enemies.size()) {
                    numEnemies = enemies.size();
                }
                coins[0].setDead(true);
                if (level < levelData.progression.maxLevel) {
                    cout << "\nLevel beat! Approaching level " << level;
                    cout << "\nNow spawning " << numEnemies << " enemies ... ";
                    deadEnemies = 0;
                }
            }

            //Print score and lives to screen
            numDisplay(g, scoreVis, marioLives, 65, 0);
            numDisplay(g, livesVis, score,  65, 20);

        if(level == levelData.progression.maxLevel)
        {
            cout<<"You won"<<endl;
            g.setQuit(true);
        }


        if (g.kbhit()) {
            g.getKey();
        }
        g.update();
    }
}

