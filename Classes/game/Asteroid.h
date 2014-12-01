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

class Painter;

const int ASTEROID_SIZE = 32;

class Asteroid : public GameObject {
public:
    Asteroid();

    virtual void render(Painter &) const;

    void updateAnimation(vec2 acc);

    void setSize(float size);

private:

};

#endif

