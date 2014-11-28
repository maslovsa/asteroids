//
//  Bullet.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_Bullet_h
#define Asteroids_Bullet_h

#include "GameObject.h"
#include "keys.hpp"
#include "jet.hpp"

class Painter;

class Bullet : public GameObject {

public:
    Bullet();

    //virtual ~Bullet();
    void tick(vec2 acel);

    virtual void draw(Painter &) const;

    float vx;
    float vy;
    int live;
};

#endif
