//
//  Game.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_Game_h
#define Asteroids_Game_h

#include "Ship.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Control.h"

class Painter;

typedef std::vector<Bullet *> Bullets;
typedef std::vector<Asteroid *> Asteroids;

class Game {
public:
    static Game &getInstance() {
        static Game instance;
        return instance;
    }

    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
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
    
    void checkColliders();
    
    void calculateCollidersVelocity(vec2 &a, vec2 &b);
private:
    int width;
    int height;
    ivec2 m_pivotPoint;
    float shotZone;

    Ship ship;
    Bullets bullets;
    Asteroids asteroids;
    Control keyUp;
    Control keyDown;
    Control keyFire;
    int level_;
    vec2 currentVelocity;
    float currentDuration;
    Keys oldKeys;
};

#endif
