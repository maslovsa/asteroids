//
//  Ship.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_Ship_h
#define Asteroids_Ship_h

#include "GameObject.h"
#include "Entities.h"

class Painter;

const int SHIP_SIZE = 30;

class Ship : public GameObject {

public:
    Ship();

    virtual void render(Painter &) const;

    void updateAnimation(Keys);

    void setAngel(float angle);

    vec2 direction;

protected:
    Jet jet_;
};

#endif
