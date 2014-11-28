//
//  Game.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_Game_h
#define Asteroids_Game_h

#include "keys.hpp"
#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include <deque>
#include <set>

class Painter;

typedef std::deque<Bullet> Bullets;
typedef std::set<Asteroid *> Asteroids;

class Game {
public:
    static Game &getInstance() {
        static Game instance;
        return instance;
    }

    int getWidth() const {
        return WIDTH;
    }
    int getHeight() const {
        return HEIGHT;
    }
    int getDelta() const {
        return DELTA_T;
    }
    void init(int width, int height);

    void render(Painter &p) const;

    void updateAnimation(float timeStep);

    void onFingerUp(ivec2 location);

    void onFingerDown(ivec2 location);

    void onFingerMove(ivec2 oldLocation, ivec2 newLocation);

private:
    Game();

    Game(Game const &);

    void operator=(Game const &);

    ~Game();

    void reset();

private:
    int WIDTH;
    int HEIGHT;
    int DELTA_T;
    Ship ship_;
    Bullets bullets_;
    Asteroids asteroids_;
    int level_;
    ivec2 m_pivotPoint;
    float shotZone;
};

#endif
