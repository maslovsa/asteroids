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
const float ASTEROID_SPEED_MAX = 10.0f;

class Asteroid : public GameObject {
public:
    Asteroid();

    virtual void render(Painter &) const;

    void updateAnimation(vec2 acc);

    void setSize(float size);

    float vAngle;
private:

};

#endif

