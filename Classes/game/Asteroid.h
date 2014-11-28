//
//  Asteroid.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_Asteroid_h
#define Asteroids_Asteroid_h

#include "GameObject.h"
#include "keys.hpp"

class Painter;

const int ASTEROID_SIZE = 64;

class Asteroid : public GameObject {
public:
    Asteroid();

    void tick(vec2 acel);

    virtual void draw(Painter &) const;

    void setSize(float size);

    float vx;
    float vy;
//    float x;
//    float y;
private:

};

#endif

