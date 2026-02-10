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
#include <fstream>
#include <cstdlib>
#include <ctime>

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

    int level = 1;
    int numEnemies = 4;
    int deadEnemies = 0;
    int numCoins = 1;

    const int WINDOW_HEIGHT = 600; // GAME HEIGHT
    const int WINDOW_WIDTH = 1000; //WINDOW WIDTH
    SDL_Plotter g(WINDOW_HEIGHT,WINDOW_WIDTH); //the window class

    char keyStroke; // used to determine what key is hit
    Player mario;
    Enemy enemy(rand() % (WINDOW_WIDTH-40),0,40,40,60,60,60); //SSS
    Enemy enemy1(rand() % (WINDOW_WIDTH-40),199,40,40,60,60,60);
    Enemy enemy2(rand() % (WINDOW_WIDTH-40),500,40,40,60,60,60);
    Enemy enemy3(rand() % (WINDOW_WIDTH-40),399,40,40,60,60,60);
    Enemy enemy4(rand() % (WINDOW_WIDTH-40), 125,40,40,60,60,60);
    Enemy enemy5(rand() % (WINDOW_WIDTH-40),399,40,40,60,60,60);
    Enemy enemy6(rand() % (WINDOW_WIDTH-40),500,40,40,60,60,60);
    Enemy enemy7(rand() % (WINDOW_WIDTH-40),0,40,40,60,60,60);
    Enemy enemy8(rand() % (WINDOW_WIDTH-40),0,40,40,60,60,60);
    Enemy enemy9(rand() % (WINDOW_WIDTH-40),0,40,40,60,60,60);
    Enemy enemy10(rand() % (WINDOW_WIDTH-40),0,40,40,60,60,60);
    Enemy enemy11(rand() % (WINDOW_WIDTH-40),0,40,40,60,60,60);

    Coin coin1 (800,10,40,40,255,255,0);
    Coin coin2 (rand() % WINDOW_WIDTH,0,40,40,255,255,0);
    Coin coin3 (rand() % WINDOW_WIDTH,0,40,40,255,255,0);
    Coin coin4 (rand() % WINDOW_WIDTH,0,40,40,255,255,0);
    Coin coin5 (480,0,40,40,255,255,0);
    Coin coin6 (275,0,40,40,255,255,0);
    Coin coin7 (300,0,40,40,255,255,0);
    Coin coin8 (455,0,40,40,255,255,0);
    Coin coin9 (240,0,40,40,255,255,0);
    Coin coin10 (40,0,40,40,255,255,0);
    Coin coin11 (20,0,40,40,255,255,0);
    Coin coin12 (900,0,40,40,255,255,0);
    Coin coin13 (600,0,40,40,255,255,0);
    Coin coin14 (700,0,40,40,255,255,0);
    Coin coin15 (800,0,40,40,255,255,0);

    Enemy enemies[12] = {enemy, enemy1, enemy2, enemy3, enemy4, enemy5,
                            enemy6, enemy7, enemy8, enemy9, enemy10, enemy11}; //enemies array
    Coin coins[15]= {coin1, coin2, coin3, coin4, coin5, coin6, coin7, coin8, coin9, coin10,
                       coin11, coin12, coin13, coin14, coin15};

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
    for (int col = 0; col < enemy.getWidth(); col++){
        for (int row = 0; row < enemy.getHeight(); row++){
            infile >> enemyPixel[col][row];
        }
    }
    infile.close();

    int coinPixel[40][40];
    infile.open("coinToken.txt");
    infile.ignore(100, '\n');
    for (int col = 0; col < coin1.getWidth(); col++){
        for (int row = 0; row < coin1.getHeight(); row++){
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



    // Platform Obstacles
    Platform leftPlat1(25, 350, 0, 425); //left platform
    Platform rightPlat1(25, 350, 650, 425); // right platform
    Platform midPlat(25, 500, 250, 280); //middle platform
    Platform topLeft(25, 350, 0, 125); //top left platform
    Platform topRight(25, 350, 650, 125); //top right platform
    Platform bottomPlat(25, WINDOW_WIDTH, 0, WINDOW_HEIGHT - 25); //floor
    Platform tubeSide1(75,25,0,50);//tube on left side of screen for enemies and coins
    Platform tubeTop1(25,50,0,50);//tube on left side of screen for enemies and coins
    Platform tubeSide2(75,25,975,50);//tube on right side of screen for enemies and coins
    Platform tubeTop2(25,50,945,50);//tube on right side of screen for enemies and coins
    PowerBlock pow(36,36,482,350); //Sam changed this
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

    //obstacle array
    Platform platforms[6] = {leftPlat1,rightPlat1,midPlat,topLeft,topRight,bottomPlat};


    Entity* platformEntities[6] = {&platforms[0], &platforms[1], &platforms[2], &platforms[3], &platforms[4], &platforms[5]};
    Entity* enemyEntities[12] = {&enemies[0], &enemies[1], &enemies[2], &enemies[3], &enemies[4], &enemies[5],
                                &enemies[6], &enemies[7], &enemies[8], &enemies[9], &enemies[10], &enemies[11]};
    Entity* coinEntities[15] = {&coins[0], &coins[1], &coins[2], &coins[3], &coins[4], &coins[5], &coins[6], &coins[7],
                               &coins[8], &coins[9], &coins[10], &coins[11], &coins[12], &coins[13], &coins[14]};

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
            tubeSide1.drawObstacle(g, 102, 204, 0);
            tubeTop1.drawObstacle(g, 102, 204, 0);

            tubeSide2.drawObstacle(g, 102, 204, 0);
            tubeTop2.drawObstacle(g, 102, 204, 0);
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
        grav(enemyEntities, numEnemies);

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
        grav(coinEntities, numCoins);









            //S on reaching side of window, teleports to opposite side
            if (mario.getPosX() == 0) {
                mario.setPosX(960);
            } else if (mario.getPosX() + mario.getWidth() == 1000) {
                mario.setPosX(0);
            }

            //teleport enemies to opposite side
            checkPos(enemyEntities, numEnemies);

            //coin teleport
            if (coin1.getPosX() == 0 && coin1.getPosY() + coin1.getWidth() > 10) { //S
                coin1.setPosX(960);
            } else if (coin1.getPosX() + coin1.getWidth() == 1000) {
                coin1.setPosX(0);
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
                if (collided(enemies[i], platformEntities, 6)) {
                    enemies[i].setGravity(false);
                    //positionIncrement = 0;
                } else {
                    enemies[i].setGravity(true);
                }
            }

//COIN TO PLATFORM COLLISION
        for(int i = 0; i < numCoins; i++){
            if (collided(coins[i], platformEntities, 6)) {
                coins[i].setGravity(false);
                //cout << "COIN COLLIDED!!!";
            } else {
                coins[i].setGravity(true);
                grav(coinEntities, numCoins);
            }
    }
    checkPos(coinEntities, numCoins);
    //checkPos(enemies, numEnemies - deadEnemies);

            //=================================================================================




            //recheck mario collision and set gravity accordingly
            if (collided(mario, platformEntities, 6)) {
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
                reviveAll(enemyEntities, numEnemies);
                numEnemies += 2;
                coin1.setDead(true);
                if (level < 6) {
                    cout << "\nLevel beat! Approaching level " << level;
                    cout << "\nNow spawning " << numEnemies << " enemies ... ";
                    deadEnemies = 0;
                }
            }

            //Print score and lives to screen
            numDisplay(g, scoreVis, marioLives, 65, 0);
            numDisplay(g, livesVis, score,  65, 20);

        if(level == 6)
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

