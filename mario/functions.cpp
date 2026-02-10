/*
Authors: Sully, Lauren, Sam, Riley, Cole
Assignment Title: Mario Brothers
Assignment Description: Re-create the video game mario bros
Due Date: 11/30/18
Date Created: 11/11/18
Date Last Modified: 11/29/18
*/
#include <iostream>
#include <algorithm>
#include "SDL_Plotter.h"
#include "functions.h"
using namespace std;

//***************************************************************************//
// Function declarations for the functions.h header file                     //
//***************************************************************************//
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 1000;

DeterministicRandom::DeterministicRandom(unsigned int seed) : state(seed)
{
    if (state == 0U) {
        state = 1U;
    }
}

void DeterministicRandom::reseed(unsigned int seed)
{
    state = (seed == 0U) ? 1U : seed;
}

unsigned int DeterministicRandom::next()
{
    state = state * 1664525U + 1013904223U;
    return state;
}

int DeterministicRandom::nextInt(int exclusiveMax)
{
    if (exclusiveMax <= 0) {
        return 0;
    }
    return static_cast<int>(next() % static_cast<unsigned int>(exclusiveMax));
}

//=============================================================================
// OBSTACLE CLASS
//-----------------------------------------------------------------------------

//obstacles destruct constructors
Obstacle::Obstacle()
{
    height = 10;
    width = 10;
    posX = 50;
    posY = 50;
}

//-----------------------------------------------------------------------------

//obstacles custom constructor
Obstacle::Obstacle(int h, int w, int pX, int pY)
{
    height = h;
    width = w;
    posX = pX;
    posY = pY;
}

//-----------------------------------------------------------------------------

// draws an obstacle (Sam slightly changed
void Obstacle::drawObstacle(SDL_Plotter &x, int R, int G, int B, int r, int g, int b)
{
    for (int c = posX; c < posX + width; c++ )
    {
        for(int d = posY; d <  posY + height; d++)
        {
            if (d % 2 == 0)
                x.plotPixel(c, d, R, G, B);
            else
                x.plotPixel(c, d, r, g, b);
        }
    }
}

void Obstacle::drawObstacle(SDL_Plotter &x, int R, int G, int B)
{
    for (int c = posX; c < posX + width; c++ )
    {
        for(int d = posY; d <  posY + height; d++)
        {
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 1000;

Entity::Entity(int x, int y, int h, int w) : posX(x), posY(y), height(h), width(w), alive(true) {}

Bounds Entity::getBounds() const { return {posX, posY, width, height}; }

bool Entity::intersects(const Entity &other) const {
    Bounds a = getBounds();
    Bounds b = other.getBounds();
    return !((a.x + a.width <= b.x) || (a.y + a.height <= b.y)
             || (a.x >= b.x + b.width) || (a.y >= b.y + b.height));
}

int Entity::getWidth() const { return width; }
int Entity::getHeight() const { return height; }
int Entity::getPosX() const { return posX; }
int Entity::getPosY() const { return posY; }
void Entity::addPosX(int x) { posX += x; }
void Entity::addPosY(int y) { posY += y; }
void Entity::setPosX(int x) { posX = x; }
void Entity::setPosY(int y) { posY = y; }
bool Entity::isAlive() const { return alive; }
bool Entity::isDead() const { return !alive; }
void Entity::setAlive(bool state) { alive = state; }
bool Entity::setDead(bool state) { alive = !state; return state; }

StaticEntity::StaticEntity(int x, int y, int h, int w) : Entity(x, y, h, w) {}
void StaticEntity::update() {}

Obstacle::Obstacle() : StaticEntity(50, 50, 10, 10) {}
Obstacle::Obstacle(int h, int w, int pX, int pY) : StaticEntity(pX, pY, h, w) {}

void Obstacle::drawObstacle(SDL_Plotter &x, int R, int G, int B, int r, int g, int b) {
    for (int c = posX; c < posX + width; c++ ) {
        for(int d = posY; d <  posY + height; d++) {
            if (d % 2 == 0) x.plotPixel(c, d, R, G, B);
            else x.plotPixel(c, d, r, g, b);
        }
    }
}

void Obstacle::drawObstacle(SDL_Plotter &x, int R, int G, int B) {
    for (int c = posX; c < posX + width; c++ ) {
        for(int d = posY; d <  posY + height; d++) {
            x.plotPixel(c, d, R, G, B);
        }
    }
}


//-----------------------------------------------------------------------------

//returns height of the obstacle
int Obstacle::getHeight()
{
    return height;
}

//-----------------------------------------------------------------------------

//returns width of the obstacle
int Obstacle::getWidth()
{
    return width;
}

//-----------------------------------------------------------------------------

// returns the x position of the obstacle
int Obstacle::getPosX()
{
    return posX;
}

//-----------------------------------------------------------------------------

// returns the y position of the obstacle
int Obstacle::getPosY()
{
    return posY;
}

//-----------------------------------------------------------------------------

//=============================================================================




//=============================================================================
// BLOCK CLASS

//-----------------------------------------------------------------------------

Block::Block()
{
    height = 10;
    width = 10;
    posX = 50;
    posY = 50;
}

//-----------------------------------------------------------------------------

//obstacles custom constructor
Block::Block(int h, int w, int pX, int pY)
{
    height = h;
    width = w;
    posX = pX;
    posY = pY;
}

//-----------------------------------------------------------------------------

// draws an obstacle
void Block::drawObstacle(SDL_Plotter &x, int a[36][36]) //SSS this is changed plz upload
{
    int r, g, b;
    for (int col = 0; col <  width; col++){
        for (int row = 0; row < height; row++){
            {
                if (a[row][col] == 0){
                    r = 0;
                    g = 0;
                    b = 0;//Black
                }
                else if (a[row][col] == 1){
                    r = 102;
                    g = 178;
                    b = 255; //Light blue
                }
                else if (a[row][col] == 2){
                    r = 0;
                    g = 102;
                    b = 204; //Blue
                }
                else if (a[row][col] == 3){
                    r = 255;
                    g = 255;
                    b = 255;
                }
                x.plotPixel(col + posX, row + posY, r, g, b);
            }
        }
    }
}
//-----------------------------------------------------------------------------

//returns height of the obstacle
int Block::getHeight() const
{
    return height;
}

//-----------------------------------------------------------------------------

//returns width of the obstacle
int Block::getWidth() const
{
    return width;
}

//-----------------------------------------------------------------------------

// returns the x position of the obstacle
int Block::getPosX() const
{
    return posX;
}

//-----------------------------------------------------------------------------

// returns the y position of the obstacle
int Block::getPosY() const
{
    return posY;
}

//-----------------------------------------------------------------------------

//=============================================================================





//=============================================================================
// SPRITE CLASS

//-----------------------------------------------------------------------------

// sprite default constructor
Sprite::Sprite() {
    posX = 10;
    posY = 10;
    width = 40;
    height = 40;
}

//-----------------------------------------------------------------------------

// sprite custom constructor
Sprite::Sprite(int x, int y, int h, int w, int r, int g, int b) {
    posX = x;
    posY = y;
    height = h;
    width = w;
    R=r;
    G=g;
    B=b;
}

//-----------------------------------------------------------------------------

// mutator function
void Sprite::setStopped(bool x) {
    stopped = x;
}

//-----------------------------------------------------------------------------

// mutator function that sets the sprite's color
void Sprite::setColors(int r, int g, int b)
{
    R = r;
    G = g;
    B = b;
}

//-----------------------------------------------------------------------------

// draws the sprite
void Sprite::draw(SDL_Plotter &x) {
    for (int col = posX; col < width + posX; col++){
        for (int row = posY; row < height + posY; row++){
            x.plotPixel(col, row, R, G, B);
        }
    }
}

//-----------------------------------------------------------------------------

//moves the sprite to the left or to the right
void Sprite::move(char key,const int& WINDOW_HEIGHT,const int& WINDOW_WIDTH) {
    if (key == LEFT_ARROW || key == 'A') {
            posX -= mVelocity;
        }
    else if (key == RIGHT_ARROW || key == 'D') {
            posX += mVelocity;
    }
}

//-----------------------------------------------------------------------------

void Sprite::jump(const int &WINDOW_HEIGHT, const int &WINDOW_WIDTH, int &y){
    if(stopped){
        posY -= gVelocity;
    } else {
        posY = min(posY - y, WINDOW_HEIGHT - 25);
    }
}

//-----------------------------------------------------------------------------

// if the sprite is not standing on the platform it will fall to the next one
void Sprite::gravity(const int &WINDOW_HEIGHT, const int &WINDOW_WIDTH){
        posY = min(posY + gVelocity, WINDOW_HEIGHT - height - 25);
}

//-----------------------------------------------------------------------------

// returns true or false if the sprite collides with an obstacle
bool Sprite::collidesWith(Obstacle &p)
{
    bool flag = true;
    if((posX+width < p.getPosX()) || (posY+height < p.getPosY())
       || (posX > p.getPosX()+ p.getWidth()) || (posY > p.getPosY()+ p.getHeight())){
        return false;
       }
       else
           return true;
}

//-----------------------------------------------------------------------------

// detects collision with a block
bool Sprite::collidesWith(Block &p)
{
    if((posX+width <= p.getPosX()) || (posY+height <= p.getPosY())
       || (posX >= p.getPosX()+ p.getWidth()) || (posY >= p.getPosY()+ p.getHeight())){
        return false;
    }
    else
        return true;
}

//-----------------------------------------------------------------------------

// mutator function that activates gravity
void Sprite::setGravity(bool x) {
    gravityOn = x;
}

//-----------------------------------------------------------------------------

// function that returns the current status of gravity
bool Sprite::getGravityStatus() {
    return gravityOn;
}

//-----------------------------------------------------------------------------

bool Sprite::getStoppedStatus() {
    return stopped;
}

void Sprite::autoMove() { //SS allows enemy to move on its own
    posX -= eVelocity;
}
void Sprite::autoMove1() { //SS allows enemy to move on its own
    posX += eVelocity;
}
void Sprite::autoMove2() { //SS allows enemy to move on its own
    posX -= mVelocity;
}
void Sprite::autoMove3() { //SS allows enemy to move on its own
    posX += mVelocity;
}

bool Sprite::collidesWith(Sprite & x)
{
    if((posX+width <= x.getPosX()) || (posY+height <= x.getPosY())
       || (posX >= x.getPosX() + x.getWidth()) || (posY >= x.getPosY()+ x.getHeight())){
        return false;
    }
    else
        return true;
}

//return true if sprite's bottom touches top of another sprite
bool Sprite::isTouchingTopOf(Sprite & x)
{
    if(((posY + height) == x.posY) && (posX + width >= x.posX)
            && (posX <= x.posX + x.width))
    {
        return true;
    }
    else
        return false;
}

bool Sprite::isTouchingTopOf(Obstacle & x)
{
    if(((posY + height) == x.getPosY()) && (posX + width >= x.getPosX())
       && (posX <= x.getPosX() + x.getWidth()))
    {
        return true;
    }
    else
        return false;
}

//draws the proper sprite for Mario, whether still or jumping
void Sprite::drawMarioPixelArt(SDL_Plotter &x, int a[40][40], bool f){ //S original function
    if (f){
        for (int col = 0; col <  width; col++){
            for (int row = 0; row < height; row++){
                if (a[row][col] == 1){
                    x.plotPixel(col + posX, row + posY, 255, 0, 0); //Red
                }  else if (a[row][col] == 2){
                    x.plotPixel(col + posX, row + posY, 229, 255, 204); //Tan
                } else if (a[row][col] == 0){
                    x.plotPixel(col + posX, row + posY, 0, 0, 0); //Black
                }
            }
        }
    } else if (!f){
        for (int col = 0; col < width; col++){
            for (int row = 0; row < height; row++){
                if (a[row][40 - col] == 1){
                    x.plotPixel(col + posX, row + posY, 255, 0, 0); //Red
                }  else if (a[row][40 - col] == 2){
                    x.plotPixel(col + posX, row + posY, 229, 255, 204); //Tan
                } else if (a[row][40 - col] == 0){
                    x.plotPixel(col + posX, row + posY, 0, 0, 0); //Black
                }
            }
        }
    }
}

bool Sprite::touchesBottomOf(Obstacle & x)
{
    if ((posY == (x.getPosY() + x.getHeight()) + 1) && ((posX + width >  x.getPosX())
            || posX < x.getPosX() + x.getWidth())) {
        return true;
    }
    else
        return false;
}

bool Sprite::touchesTopOf(Obstacle & x)
{
    if(((posY + height) == x.getPosY() +  1) && (posX + width >= x.getPosX())
       && (posX <= x.getPosX() + x.getWidth()))
    {
        return true;
    }
    else
        return false;
void Obstacle::render(SDL_Plotter &x) { drawObstacle(x, 255, 255, 255); }
int Obstacle::getHeight() const { return height; }
int Obstacle::getWidth() const { return width; }
int Obstacle::getPosX() const { return posX; }
int Obstacle::getPosY() const { return posY; }

Block::Block() : StaticEntity(50, 50, 10, 10) {}
Block::Block(int h, int w, int pX, int pY) : StaticEntity(pX, pY, h, w) {}

void Block::drawObstacle(SDL_Plotter &x, int a[36][36]) {
    int r, g, b;
    for (int col = 0; col <  width; col++){
        for (int row = 0; row < height; row++){
            if (a[row][col] == 0){ r = 0; g = 0; b = 0; }
            else if (a[row][col] == 1){ r = 102; g = 178; b = 255; }
            else if (a[row][col] == 2){ r = 0; g = 102; b = 204; }
            else { r = 255; g = 255; b = 255; }
            x.plotPixel(col + posX, row + posY, r, g, b);
        }
    }
}

void Block::render(SDL_Plotter &x) {
    int empty[36][36] = {{0}};
    drawObstacle(x, empty);
}

int Block::getHeight() const { return height; }
int Block::getWidth() const { return width; }
int Block::getPosX() const { return posX; }
int Block::getPosY() const { return posY; }

Sprite::Sprite() : Entity(10, 10, 40, 40), R(0), G(0), B(0) {}
Sprite::Sprite(int x, int y, int h, int w, int r, int g, int b)
    : Entity(x, y, h, w), R(r), G(g), B(b) {}

void Sprite::setStopped(bool x) { stopped = x; }
void Sprite::setColors(int r, int g, int b) { R = r; G = g; B = b; }

void Sprite::draw(SDL_Plotter &x) {
    for (int col = posX; col < width + posX; col++){
        for (int row = posY; row < height + posY; row++) x.plotPixel(col, row, R, G, B);
    }
}

void Sprite::render(SDL_Plotter &x) { if (isAlive()) draw(x); }
void Sprite::update() {}

void Sprite::move(char key,const int& WINDOW_HEIGHT,const int& WINDOW_WIDTH) {
    (void) WINDOW_HEIGHT; (void) WINDOW_WIDTH;
    if (key == LEFT_ARROW || key == 'A') posX -= mVelocity;
    else if (key == RIGHT_ARROW || key == 'D') posX += mVelocity;
}

void Sprite::jump(const int &WINDOW_HEIGHT, const int &WINDOW_WIDTH, int &y){
    (void) WINDOW_WIDTH;
    if(stopped) posY -= gVelocity;
    else posY = min(posY - y, WINDOW_HEIGHT - 25);
}

void Sprite::gravity(const int &WINDOW_HEIGHT, const int &WINDOW_WIDTH){
    (void) WINDOW_WIDTH;
    posY = min(posY + gVelocity, WINDOW_HEIGHT - height - 25);
}

bool Sprite::collidesWith(const Entity &p) const { return intersects(p); }
bool Sprite::collidesWith(Sprite &x) const { return collidesWith(static_cast<const Entity&>(x)); }
bool Sprite::collidesWith(Obstacle &x) const { return collidesWith(static_cast<const Entity&>(x)); }
bool Sprite::collidesWith(Block &x) const { return collidesWith(static_cast<const Entity&>(x)); }

void Sprite::setGravity(bool x) { gravityOn = x; }
bool Sprite::getGravityStatus() { return gravityOn; }
bool Sprite::getStoppedStatus() { return stopped; }

void Sprite::autoMove() { posX -= eVelocity; }
void Sprite::autoMove1() { posX += eVelocity; }
void Sprite::autoMove2() { posX -= mVelocity; }
void Sprite::autoMove3() { posX += mVelocity; }

bool Sprite::isTouchingTopOf(Sprite &x) {
    return ((posY + height) == x.posY) && (posX + width >= x.posX) && (posX <= x.posX + x.width);
}

bool Sprite::isTouchingTopOf(Obstacle &x) {
    return ((posY + height) == x.getPosY()) && (posX + width >= x.getPosX()) && (posX <= x.getPosX() + x.getWidth());
}

void Sprite::drawMarioPixelArt(SDL_Plotter &x, int a[40][40], bool f){
    if (f){
        for (int col = 0; col <  width; col++){
            for (int row = 0; row < height; row++){
                if (a[row][col] == 1) x.plotPixel(col + posX, row + posY, 255, 0, 0);
                else if (a[row][col] == 2) x.plotPixel(col + posX, row + posY, 229, 255, 204);
                else if (a[row][col] == 0) x.plotPixel(col + posX, row + posY, 0, 0, 0);
            }
        }
    } else {
        for (int col = 0; col < width; col++){
            for (int row = 0; row < height; row++){
                if (a[row][40 - col] == 1) x.plotPixel(col + posX, row + posY, 255, 0, 0);
                else if (a[row][40 - col] == 2) x.plotPixel(col + posX, row + posY, 229, 255, 204);
                else if (a[row][40 - col] == 0) x.plotPixel(col + posX, row + posY, 0, 0, 0);
            }
        }
    }
}

bool Sprite::touchesBottomOf(Obstacle &x) {
    return (posY == (x.getPosY() + x.getHeight()) + 1) && ((posX + width >  x.getPosX()) || posX < x.getPosX() + x.getWidth());
}

bool Sprite::touchesTopOf(Obstacle &x) {
    return ((posY + height) == x.getPosY() +  1) && (posX + width >= x.getPosX()) && (posX <= x.getPosX() + x.getWidth());
}

void Sprite::drawCoinPixelArt(SDL_Plotter &x, int a[40][40]) {
    for (int col = 0; col <  width; col++){
        for (int row = 0; row < height; row++){
            if (a[row][col] == 1){
                x.plotPixel(col + posX, row + posY, 255, 165, 0); //Orange
            }  else if (a[row][col] == 2){
                x.plotPixel(col + posX, row + posY, 229, 255, 204); //Tan
            } else if (a[row][col] == 0){
                x.plotPixel(col + posX, row + posY, 0, 0, 0); //Black
            }
        }
    }
}

//-----------------------------------------------------------------------------


//==========================================================================

//return true if sprite collides with any obstacle
bool collided(Sprite & x, Obstacle list[], int size)
{
    bool collided = false;
    for(int i = 0; i < size; i++)
    {
        if(x.collidesWith(list[i]))
        {
            collided = true;
        }
    }
    return collided;
}

//-----------------------------------------------------------------------------

bool collidedBottomObstacle(Sprite & x, Obstacle list[], int size)
{
    bool collidedBottom = false;
    for(int i = 0; i < size; i++)
    {
        if(x.collidesWith(list[i]) && (x.getPosY() == list[i].getPosY() + list[i].getHeight()))
        {
            collidedBottom = true;
        }
    }
    return collidedBottom;
}

//-----------------------------------------------------------------------------

bool collidedTopObstacle(Sprite & x, Obstacle list[], int size) {
    bool collidedTop = false;
    for (int i = 0; i < size; i++) {
        if (x.collidesWith(list[i]) && (x.getPosY() + x.getHeight() == list[i].getPosY())) {
            collidedTop = true;
        }
    }
    return collidedTop;
}

void kill(Sprite & x)
{
    //move to top right corner
   // x.setPosX(1000 - x.getWidth());
    //x.setPosY(0);
    //black out
    //x.setColors(0, 0, 0);
    //set bool dead to true (so it doesnt keep drawing it in main)
    x.setDead(true);
}

//-----------------------------------------------------------------------------
//will implement gravity
void grav(Sprite list[], int size)
{
    for(int i =0; i<size; i++)
    {
    if (list[i].getGravityStatus() && !list[i].getDead()){
        list[i].gravity(WINDOW_HEIGHT, WINDOW_WIDTH);
    }
    }
}
//will draw enemies and make it move
void drawEnemies(SDL_Plotter &x,Sprite list[], int size)
{
    for(int i =0; i<size; i++)
    {
        if(!list[i].getDead()) {
            //list[i].setColors(60,60,60);
            list[i].draw(x);
            //move one way
            if(i%2 == 0){
            list[i].autoMove();
            }
            //move other way
            if(i%2 != 0){
            list[i].autoMove1();
        }
    }
}
}
void checkPos(Sprite list[],int size)
{
    for(int i =0; i<size; i++) {
        if (i % 3 == 0) {
            if (list[i].getPosX() == 0 && list[i].getPosY() >= 535) {
                list[i].setPosX(960);
                list[i].setPosY(385);
            }
                //if sprite is at the bottom right corner reposition to top left corner
            else if (list[i].getPosX() == 960 && list[i].getPosY() >= 535) {
                list[i].setPosX(0);
                list[i].setPosY(385);
            }
                //go one side to other
            else if (list[i].getPosX() == 0 && list[i].getPosY() + list[i].getWidth() > 10) { //S
                list[i].setPosX(960);
            }
                //go one side to other
            else if (list[i].getPosX() + list[i].getWidth() == 1000) {
                list[i].setPosX(0);
            }
        } else {
            //if sprite is at the bottom left corner reposition to top right corner
            if (list[i].getPosX() == 0 && list[i].getPosY() >= 535) {
                list[i].setPosX(960);
                list[i].setPosY(0);
            }
                //if sprite is at the bottom right corner reposition to top left corner
            else if (list[i].getPosX() + list[i].getWidth() == 960 && list[i].getPosY() >= 535) {
                list[i].setPosX(0);
                list[i].setPosY(0);
            }
                //go one side to other
            else if (list[i].getPosX() == 0 && list[i].getPosY() + list[i].getWidth() > 10) { //S
                list[i].setPosX(960);

            }
                //go one side to other
            else if (list[i].getPosX() + list[i].getWidth() == 1000) {
                list[i].setPosX(0);
            }
        }
    }
}
//will detect collision from mario then kill enemy
void killEnemy(Sprite list[], int size, Sprite &x)
{
    for(int i =0; i<size; i++)
    {
        if (x.isTouchingTopOf(list[i]))
        {
            kill(list[i]);
        }
    }
}



//----------------------------------------------------------------------------
// Displays a 1 or 2 digit pixeled integer based score or life passed to it
            if (a[row][col] == 1) x.plotPixel(col + posX, row + posY, 255, 165, 0);
            else if (a[row][col] == 2) x.plotPixel(col + posX, row + posY, 229, 255, 204);
            else if (a[row][col] == 0) x.plotPixel(col + posX, row + posY, 0, 0, 0);
        }
    }
}

Player::Player() : Sprite() {}
Player::Player(int x, int y, int h, int w, int r, int g, int b) : Sprite(x, y, h, w, r, g, b) {}
Enemy::Enemy() : Sprite() {}
Enemy::Enemy(int x, int y, int h, int w, int r, int g, int b) : Sprite(x, y, h, w, r, g, b) {}
Coin::Coin() : Sprite() {}
Coin::Coin(int x, int y, int h, int w, int r, int g, int b) : Sprite(x, y, h, w, r, g, b) {}
Platform::Platform() : Obstacle() {}
Platform::Platform(int h, int w, int x, int y) : Obstacle(h, w, x, y) {}
PowerBlock::PowerBlock() : Block() {}
PowerBlock::PowerBlock(int h, int w, int x, int y) : Block(h, w, x, y) {}

bool collided(Entity &x, Entity *const list[], int size) {
    for(int i = 0; i < size; i++) if (x.intersects(*list[i])) return true;
    return false;
}

bool collidedBottomObstacle(Entity &x, Entity *const list[], int size) {
    for(int i = 0; i < size; i++) {
        Bounds xb = x.getBounds();
        Bounds ob = list[i]->getBounds();
        if (x.intersects(*list[i]) && (xb.y == ob.y + ob.height)) return true;
    }
    return false;
}

bool collidedTopObstacle(Entity &x, Entity *const list[], int size) {
    for (int i = 0; i < size; i++) {
        Bounds xb = x.getBounds();
        Bounds ob = list[i]->getBounds();
        if (x.intersects(*list[i]) && (xb.y + xb.height == ob.y)) return true;
    }
    return false;
}

void kill(Entity &x) { x.setDead(true); }

void grav(Entity *list[], int size) {
    for(int i =0; i<size; i++) {
        Sprite* sprite = dynamic_cast<Sprite*>(list[i]);
        if (sprite && sprite->getGravityStatus() && !sprite->getDead()) {
            sprite->gravity(WINDOW_HEIGHT, WINDOW_WIDTH);
        }
    }
}

void drawEnemies(SDL_Plotter &x, Entity *list[], int size) {
    for(int i =0; i<size; i++) {
        Sprite* sprite = dynamic_cast<Sprite*>(list[i]);
        if (!sprite || sprite->getDead()) continue;
        sprite->draw(x);
        if(i%2 == 0) sprite->autoMove();
        else sprite->autoMove1();
    }
}

void checkPos(Entity *list[],int size) {
    for(int i =0; i<size; i++) {
        Sprite* sprite = dynamic_cast<Sprite*>(list[i]);
        if (!sprite) continue;
        if (i % 3 == 0) {
            if (sprite->getPosX() == 0 && sprite->getPosY() >= 535) { sprite->setPosX(960); sprite->setPosY(385); }
            else if (sprite->getPosX() == 960 && sprite->getPosY() >= 535) { sprite->setPosX(0); sprite->setPosY(385); }
            else if (sprite->getPosX() == 0 && sprite->getPosY() + sprite->getWidth() > 10) sprite->setPosX(960);
            else if (sprite->getPosX() + sprite->getWidth() == 1000) sprite->setPosX(0);
        } else {
            if (sprite->getPosX() == 0 && sprite->getPosY() >= 535) { sprite->setPosX(960); sprite->setPosY(0); }
            else if (sprite->getPosX() + sprite->getWidth() == 960 && sprite->getPosY() >= 535) { sprite->setPosX(0); sprite->setPosY(0); }
            else if (sprite->getPosX() == 0 && sprite->getPosY() + sprite->getWidth() > 10) sprite->setPosX(960);
            else if (sprite->getPosX() + sprite->getWidth() == 1000) sprite->setPosX(0);
        }
    }
}

void killEnemy(Entity *list[], int size, Entity &x) {
    Sprite* actor = dynamic_cast<Sprite*>(&x);
    if (!actor) return;
    for(int i =0; i<size; i++) {
        Sprite* target = dynamic_cast<Sprite*>(list[i]);
        if (target && actor->isTouchingTopOf(*target)) kill(*target);
    }
}

void numDisplay(SDL_Plotter &g, pixel box[18][22], int num, int x, int y)
{
    int ones = num % 10;
    int tens = ((num - ones)/10);

    if(num == 0)
    {
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
                g.plotPixel((x + col), (y + row), box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
        for(int row=10; row<18; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 1 || tens == 1)
    {
        for(int row=0; row<18; row++)
        {
            for(int col=0; col<2; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 2 || tens == 2)
    {
        for(int row=0; row<10; row++)
        {
            for(int col=2; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }

        for(int row=10; row<18; row++)
        {
            for(int col=0; col<8; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 3 || tens == 3)
    {
        for(int row=0; row<18; row++)
        {
            for(int col=2; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 4 || tens == 4)
    {
        for(int row=2; row<10; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }

        for(int row=10; row<16; row++)
        {
            for(int col=8; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 5 || tens == 5)
    {
        for(int row=0; row<10; row++)
        {
            for(int col=0; col<8; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }

        for(int row=10; row<18; row++)
        {
            for(int col=2; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 6 || tens == 6)
    {
        for(int row=0; row<10; row++)
        {
            for(int col=0; col<8; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }

        for(int row=10; row<18; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 7 || tens == 7)
    {
        for(int row=0; row<8; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }

        for(int row=10; row<16; row++)
        {
            for(int col=8; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 8 || tens == 8)
    {
        for(int row=0; row<18; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    else if(num == 9 || tens == 9)
    {
        for(int row=0; row<10; row++)
        {
            for(int col=0; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }

        for(int row=10; row<18; row++)
        {
            for(int col=2; col<10; col++)
            {
                g.plotPixel((x + col), (y + row),
                            box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }

    if((num >= 10) && (num < 100))
    {
        if(ones == 0)
        {
            for(int row=0; row<8; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<18; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }



        if(ones == 1)
        {
            for(int row=0; row<18; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 2)
        {
            for(int row=0; row<10; row++)
            {
                for(int col=14; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<18; row++)
            {
                for(int col=12; col<20; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }
        else if(ones == 3)
        {
            for(int row=0; row<18; row++)
            {
                for(int col=14; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 4)
        {
            for(int row=2; row<10; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<16; row++)
            {
                for(int col=20; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 5)
        {
            for(int row=0; row<10; row++)
            {
                for(int col=12; col<20; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<18; row++)
            {
                for(int col=14; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 6)
        {
            for(int row=0; row<10; row++)
            {
                for(int col=12; col<20; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<18; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 7)
        {
            for(int row=0; row<8; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<16; row++)
            {
                for(int col=20; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 8)
        {
            for(int row=0; row<18; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }

        else if(ones == 9)
        {
            for(int row=0; row<10; row++)
            {
                for(int col=12; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }

            for(int row=10; row<18; row++)
            {
                for(int col=14; col<22; col++)
                {
                    g.plotPixel((x + col), (y + row),
                                box[row][col].r, box[row][col].g, box[row][col].b);
                }
            }
        }
    }
}

//-----------------------------------------------------------------------------

void reviveAll(Sprite list[], int size)
{
    for(int i = 0; i < size; i++)
    {
        list[i].setDead(false);
    }
}
                g.plotPixel((x + col), (y + row), box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }
    else if (num < 10)
    {
        for(int row=0; row<18; row++)
        {
            for(int col=(ones*2); col<((ones*2) + 2); col++)
            {
                g.plotPixel((x + col - (ones*2)), (y + row), box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }
    else if(num >= 10)
    {
        for(int row=0; row<18; row++)
        {
            for(int col=(tens*2); col<((tens*2) + 2); col++)
            {
                g.plotPixel((x + col - (tens*2)), (y + row), box[row][col].r, box[row][col].g, box[row][col].b);
            }
            for(int col=(ones*2); col<((ones*2) + 2); col++)
            {
                g.plotPixel((x + col - (ones*2) + 11), (y + row), box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
    }
}

void reviveAll(Entity *list[], int size)
{
    for(int i = 0; i < size; i++) list[i]->setDead(false);
}
