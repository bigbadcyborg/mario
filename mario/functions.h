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

struct Bounds {
    int x;
    int y;
    int width;
    int height;
};

class Entity {
protected:
    int posX;
    int posY;
    int height;
    int width;
    bool alive;

public:
    Entity(int x = 0, int y = 0, int h = 0, int w = 0);
    virtual ~Entity() = default;

    virtual void update() = 0;
    virtual void render(SDL_Plotter &x) = 0;
    virtual Bounds getBounds() const;

    bool intersects(const Entity &other) const;

    int getWidth() const;
    int getHeight() const;
    int getPosX() const;
    int getPosY() const;
    void addPosX(int x);
    void addPosY(int y);
    void setPosX(int x);
    void setPosY(int y);

    bool isAlive() const;
    bool isDead() const;
    void setAlive(bool state);
    bool setDead(bool state);
};

class StaticEntity : public Entity {
public:
    StaticEntity(int x = 0, int y = 0, int h = 0, int w = 0);
    void update() override;
};

class Obstacle : public StaticEntity
{
public:
    Obstacle();
    Obstacle(int, int, int, int);

    void drawObstacle(SDL_Plotter &x, int R, int G, int B, int r, int g, int b);
    void drawObstacle(SDL_Plotter &x, int R, int G, int B);
    void render(SDL_Plotter &x) override;

    int getHeight() const;
    int getWidth() const;
    int getPosX() const;
    int getPosY() const;
};

class Block : public StaticEntity {
public:
    Block();
    Block(int, int, int, int);

    void drawObstacle(SDL_Plotter &, int[36][36]);
    void render(SDL_Plotter &x) override;

    int getHeight() const;
    int getWidth() const;
    int getPosX() const;
    int getPosY() const;
};

class Sprite : public Entity {
private:
    int R;
    int G;
    int B;

    int gVelocity = 1;
    int mVelocity = 2;
    int eVelocity = 1;
    bool stopped = false;
    bool gravityOn = true;

public:
    Sprite();
    Sprite(int, int, int, int, int, int, int);

    void setStopped(bool);
    void setColors(int, int, int);
    void draw(SDL_Plotter &);
    void render(SDL_Plotter &) override;
    void update() override;

    void move(char, const int &, const int &);
    void jump(const int &, const int &, int &);
    void gravity(const int &, const int &);

    bool collidesWith(const Entity &) const;
    bool collidesWith(Sprite &) const;
    bool collidesWith(Obstacle &) const;
    bool collidesWith(Block &) const;

    void setGravity(bool);
    bool getGravityStatus();
    bool getStoppedStatus();

    int getWidth() const { return Entity::getWidth(); }
    int getHeight() const { return Entity::getHeight(); }
    int getPosY() const { return Entity::getPosY(); }
    int getPosX() const { return Entity::getPosX(); }
    void addPosX(int x) { Entity::addPosX(x); }
    void addPosY(int y) { Entity::addPosY(y); }
    void setPosX(int x) { Entity::setPosX(x); }
    void setPosY(int y) { Entity::setPosY(y); }

    bool isTouchingTopOf(Sprite &x);
    void autoMove();
    void autoMove1();
    void autoMove2();
    void autoMove3();

    bool getDead() const { return isDead(); }
    bool setDead(bool x) { return Entity::setDead(x); }

    void drawMarioPixelArt(SDL_Plotter &, int[40][40], bool);

    bool touchesBottomOf(Obstacle &x);
    bool touchesTopOf(Obstacle &x);
    bool isTouchingTopOf(Obstacle &x);

    void drawCoinPixelArt(SDL_Plotter &g, int a[40][40]);

    int getEVelocity() { return eVelocity; }
    void setEVelocity(int v) { eVelocity = v; }
};

class Player : public Sprite {
public:
    Player();
    Player(int, int, int, int, int, int, int);
};

class Enemy : public Sprite {
public:
    Enemy();
    Enemy(int, int, int, int, int, int, int);
};

class Coin : public Sprite {
public:
    Coin();
    Coin(int, int, int, int, int, int, int);
};

class Platform : public Obstacle {
public:
    Platform();
    Platform(int, int, int, int);
};

class PowerBlock : public Block {
public:
    PowerBlock();
    PowerBlock(int, int, int, int);
};

struct pixel{
    int r;
    int g;
    int b;
};

bool collided(Entity &x, Entity *const list[], int size);
bool collidedBottomObstacle(Entity &x, Entity *const list[], int size);
bool collidedTopObstacle(Entity &x, Entity *const list[], int size);

void kill(Entity &x);

void grav(Entity *list[], int size);
void drawEnemies(SDL_Plotter &x, Entity *list[], int size);
void checkPos(Entity *list[], int size);
void killEnemy(Entity *list[], int size, Entity &);

void numDisplay(SDL_Plotter &, pixel [][22], int, int, int);

void reviveAll(Entity *list[], int size);

#endif // FUNCTIONS_H_INCLUDED
