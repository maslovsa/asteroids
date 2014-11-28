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

const int BULLET_SIZE = 14;

class Bullet : public GameObject {

public:
    Bullet();

    virtual void render(Painter &) const;

    void updateAnimation(vec2 acc);

    int live;
};

#endif
