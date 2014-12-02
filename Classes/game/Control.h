//
//  Control.h
//  Asteroids
//
//  Created by Sergey Maslov on 01.12.14.
//
//

#ifndef __Asteroids__Control__
#define __Asteroids__Control__

#include "GameObject.h"
#include "Entities.h"

class Painter;

class Control : public GameObject {

public:
    Control();

    void init(KeyState keystate);

    virtual void render(Painter &) const;

    void updateAnimation(Keys);

    bool isClicked(vec2 location);

private:
    KeyState keystate;
};

#endif /* defined(__Asteroids__Control__) */
