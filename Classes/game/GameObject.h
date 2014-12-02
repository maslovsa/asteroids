//
//  GameObject.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_GameObject_h
#define Asteroids_GameObject_h

#include "vector.hpp"
#include <vector>

class Painter;

class GameObject {

public:
    virtual void render(Painter &) const = 0;

    float getAngle() const {
        return angle;
    }

    float getSize() const {
        return size;
    }

public:
    std::vector<Vertex> body;
    vec2 position;
    vec2 velocity;

    float scale;
    float vAngle;

protected:
    float angle;
    float size;
};

#endif
