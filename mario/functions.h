/*
Authors: Sully, Lauren, Sam, Riley, Cole
Assignment Title: Mario Brothers
Assignment Description: Re-create the video game mario bros
Due Date: 11/30/18
Date Created: 11/11/18
Date Last Modified: 11/29/18
*/
#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "SDL_Plotter.h"

using namespace std;

//=============================================================================

class Obstacle //for making obstacles
{
private:
    int height;
    int width;
    int posX;
    int posY;

public:

    //obstacle default constructor
    Obstacle();
    //constructor that takes in width, height, and (x,y) coordinate
    Obstacle(int, int, int, int);
    /*
    PreCondition: plotter
    PostCondition: obstacle is drawn
    ReturnType: none/draws obstacle
    Description: will take in plotter then plots pixels to form the sprite
    */
    void drawObstacle(SDL_Plotter &x, int R, int G, int B, int r, int g, int b);
    /*
    PreCondition: height
    PostCondition: gets height
    ReturnType: int
    Description: will retrieve the height of the obstacle
    */

    void drawObstacle(SDL_Plotter &x, int R, int G, int B);

    int getHeight();
    /*
    PreCondition: width
    PostCondition: gets width
    ReturnType: int
    Description: will retrieve the width of the obstacle
    */
    int getWidth();
    /*
    PreCondition: posX
    PostCondition: gets x coordinate
    ReturnType: int
    Description: will retrieve the x coordinate
    */
    int getPosX();
    /*
    PreCondition: posY
    PostCondition: gets y coordinate
    ReturnType: int
    Description: will retrieve y coordinate
    */
    int getPosY();
};

//=============================================================================

class Block {
private:
    int height;
    int width;
    int posX;
    int posY;
public:
    //obstacle constructor
    Block();
    //constructor takes in width, height, and (x,y) coordinate of where to be drawn
    Block(int, int, int, int);
    /*
    PreCondition: plotter
    PostCondition: obstacle is drawn
    ReturnType: none/draws obstacle
    Description: will take in plotter then plots pixels to form the sprite
    */
    void drawObstacle(SDL_Plotter &, int[36][36]); //S changed this
    /*
    PreCondition: height
    PostCondition: gets height
    ReturnType: int
    Description: will retrieve the height of the obstacle
    */
    int getHeight() const;
    /*
    PreCondition: width
    PostCondition: gets width
    ReturnType: int
    Description: will retrieve the width of the obstacle
    */
    int getWidth() const;
    /*
    PreCondition: posX
    PostCondition: gets x coordinate
    ReturnType: int
    Description: will retrieve the x coordinate
    */
    int getPosX() const;
    /*
    PreCondition: posY
    PostCondition: gets y coordinate
    ReturnType: int
    Description: will retrieve y coordinate
    */
    int getPosY() const;
};

//=============================================================================

// Sprite Object
class Sprite {
private:
    int posX;  //our rectangle variables
    int posY;
    int height;
    int width;
    int R; //red green and blue variables we use when
    int G; //plotting pixel (line 90)
    int B;

    int gVelocity = 1; //units moved down each frame
    int mVelocity = 2;//units moved each frame (when moved)
    int eVelocity = 1; //enemy velocity
    bool stopped = false; //flag for collision detection
    bool gravityOn = true;
    bool dead = false; //flag for death detection (doesnt draw if dead = true)

public:

    // default constructor
    Sprite();
     // and constructor that defines ALL variables (x,y,height,width,RGB)
    Sprite(int, int, int, int, int, int, int);
    /*
    PreCondition: if stopped
    PostCondition: stop?
    ReturnType: none
    Description: takes in a boolean value to see if the sprite is stopped
    */
    void setStopped(bool);
    /*
    PreCondition: takes in three integers
    PostCondition: makes them into a color
    ReturnType: none
    Description: takes in three integers and assigns them to the r g b
    values of a color for that sprite
    */
    void setColors(int, int, int);
    /*
    PreCondition: plotter
    PostCondition: sprite is drawn
    ReturnType: none/draws sprite
    Description: will take in plotter then plots pixels to form the sprite
    */
    void draw(SDL_Plotter &);

    /*
    PreCondition: is sprite moving
    PostCondition: is there collision
    ReturnType: none
    Description: will move the sprite left and right as long as no collision
    is detected with obstacles and other objects
    */
    void move(char, const int &, const int &);
    /*
    PreCondition: jumps
    PostCondition: will jump if no obstacle
    ReturnType: none
    Description: will jump as long as there is not a obstacle in its way if there
    is an obstacle sprite falls back down
    */
    void jump(const int &, const int &, int &);
    /*
    PreCondition: movement
    PostCondition: if on platform keep walking if not fall
    ReturnType: none
    Description: if sprite moves off a platform it will fall to the next one
    */
    void gravity(const int &, const int &);
    /*
    PreCondition: sprite is on a platform
    PostCondition: sprite stays on platform
    ReturnType: bool
    Description: will detect if a sprite is colliding with an obstacle either through
    running, jumping, or falling and will keep sprite from going through obstacle
    */
    bool collidesWith(Obstacle &);
    /*
    PreCondition: sprite is jumping for block
    PostCondition: sprite hits block
    ReturnType: bool
    Description: will see if sprite makes contact with block
    */
    bool collidesWith(Sprite &);
    /*
    PreCondition: sprite is jumping for block
    PostCondition: sprite hits block
    ReturnType: bool
    Description: will see if sprite makes contact with block
    */
    bool collidesWith(Block &p);
    /*
    PreCondition: gravity
    PostCondition: off or on
    ReturnType: none
    Description: will activate or deactivate gravity
    */
    void setGravity(bool);
    /*
    PreCondition: gravity
    PostCondition: on or off?
    ReturnType: bool
    Description: will reutrn if gravity is on or off
    */
    bool getGravityStatus();
    /*
    PreCondition: sprite moving
    PostCondition: is sprite going
    ReturnType: bool
    Description: is sprite moving or not
    */
    bool getStoppedStatus();
    /*
    PreCondition: width
    PostCondition: gets width
    ReturnType: int
    Description: will retrieve width
    */

    int getWidth()
    { return width; }
    /*
    PreCondition: height
    PostCondition: gets height
    ReturnType: int
    Description: will retrieve height
    */
    int getHeight()
    { return height; }
    /*
    PreCondition: posY
    PostCondition: gets y position
    ReturnType: int
    Description: will retrieve y coordinate
    */
    int getPosY()
    { return posY; }
    /*
    PreCondition: posX
    PostCondition: gets x position
    ReturnType: int
    Description: will retrieve x coordinate
    */
    int getPosX()
    { return posX; }
    /*
    PreCondition: x coordinate
    PostCondition: will change the x coordinate by x
    ReturnType: none
    Description: will add input to x coordinate and move it
    */
    void addPosX(int x)
    { posX += x; }
    /*
    PreCondition: y coordinate
    PostCondition: will change the y coordinate by y
    ReturnType: none
    Description: will add input to the y coordinate and move it
    */
    void addPosY(int y)
    { posY += y;}
    /*
    PreCondition: posX
    PostCondition: x coordinate
    ReturnType: none
    Description: sets x coordinate to input
    */
    void setPosX(int x)
    { posX = x; }
    /*
    PreCondition: posY
    PostCondition: y coordinate
    ReturnType: none
    Description: sets y coordinate to input
    */
    void setPosY(int y)
    { posY = y;}
    /*
    PreCondition: enemy and mario
    PostCondition: is mario on top of enemy
    ReturnType: bool
    Description: false if no collision true if touching
    */
    bool isTouchingTopOf(Sprite & x);
    /*
    PreCondition: move
    PostCondition: moves without keys
    Return Type: none
    Description: used for enemy and coin movement which is not based on user input
    */
    void autoMove();
    /*
    PreCondition: move without keys
    PostCondition: posX+1
    ReturnType: none
    Description: moves x coordinate over without keys
    */
    void autoMove1();
    /*
    PreCondition: is enemy dead
    PostCondition: enemy dead?
    Return Type: bool
    Description: will return dead or now which is used to detect if coin or enemy has been hit
    */
    void autoMove2();
    /*
    PreCondition: move without keys
    PostCondition: posX+2
    ReturnType: none
    Description: moves x coordinate over without keys
    */
    void autoMove3();
    /*
    PreCondition: is enemy dead
    PostCondition: enemy dead?
    Return Type: bool
    Description: will return dead or now which is used to detect if coin or enemy has been hit
    */

    bool getDead()
    { return dead; }
    /*
    PreCondition: is enemy hit
    PostCondition: enemy hit
    Return Type: bool
    Description: if coin or enemy is hit will change to dead which removes it from screen
    */
    bool setDead(bool x)
    { dead = x; }

    void drawMarioPixelArt(SDL_Plotter &, int[40][40], bool);

    bool touchesBottomOf(Obstacle & x);

    bool touchesTopOf(Obstacle & x);

    bool isTouchingTopOf(Obstacle & x);

    void drawCoinPixelArt(SDL_Plotter & g, int a[40][40]);

    int getEVelocity()
    { return  eVelocity; }

    void setEVelocity(int v)
    { eVelocity = v; }

};

class DeterministicRandom {
private:
    unsigned int state;

public:
    explicit DeterministicRandom(unsigned int seed = 1U);
    void reseed(unsigned int seed);
    unsigned int next();
    int nextInt(int exclusiveMax);
};

//=============================================================================

//=============================================================================
//needed for graphic printing
struct pixel{
    int r;
    int g;
    int b;
};

//=============================================================================

/*
PreCondition: sprite collision, obstacles
PostCondition: is sprite colliding with obstacle
Return Type: bool
Description: will see if a sprite is colliding with any obstacles in the array
*/
bool collided(Sprite & x, Obstacle list[], int size);//return true if sprite collides with any obstacle

//=============================================================================

/*
PreCondition: sprite collision, obstacles
PostCondition: is sprite colliding with bottom obstacle?
Return Type: bool
Description: will see if a sprite is colliding with bottom obstacle
*/
bool collidedBottomObstacle(Sprite & x, Obstacle list[], int size);

//=============================================================================

/*
PreCondition: sprite collision, obstacles
PostCondition: is sprite colliding with top obstacle?
Return Type: bool
Description: will see if a sprite is colliding with top obstacle
*/
bool collidedTopObstacle(Sprite & x, Obstacle list[], int size);

/*
PreCondition: is enemy hit
PostCondition: enemy hit
Return Type: none
Description: if coin or enemy is hit will change to dead which removes it from screen
*/
void kill(Sprite & x);



//=============================================================================
/*
PreCondition: sprite list and size
PostCondition: gets gravity
Return Type: none
Description: will turn on gravity for elements in array
*/
void grav(Sprite list[], int size);
/*
PreCondition: sprite list and size and plot
PostCondition: draws and starts moving sprites in array
Return Type: none
Description: will draw and turn on movement for elements in array
*/
void drawEnemies(SDL_Plotter &x,Sprite list[], int size);
/*
PreCondition: sprite list and size
PostCondition: will go from bottom corners up to opposite top corners
Return Type: none
Description: will change x and y coordinates from bottom to top
*/
void checkPos(Sprite list[],int size);
/*
PreCondition: sprite list and size and sprite
PostCondition: if sprite hits one of sprite in the array it will kill the enemy it hit
Return Type: none
Description: will kill an enemy if hit
*/
void killEnemy(Sprite list[], int size,Sprite &);

void numDisplay(SDL_Plotter &, pixel [][22], int, int, int);

void reviveAll(Sprite list[], int size); //brings all enemies back to life




#endif // FUNCTIONS_H_INCLUDED
