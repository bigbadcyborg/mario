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
                g.plotPixel((x + col), (y + row), box[row][col].r, box[row][col].g, box[row][col].b);
            }
        }
        for(int row=10; row<18; row++)
        {
            for(int col=0; col<10; col++)
            {
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
