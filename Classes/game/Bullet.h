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

class Painter;

class Bullet : public GameObject {

public:
    Bullet();

    virtual void render(Painter &) const;

    void updateAnimation(vec2 acc);

    bool isLive;
};

#endif
