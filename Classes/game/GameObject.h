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

    //virtual ~GameObject();

    virtual void draw(Painter &) const = 0;

    float getAngle() const {
        return angle_;
    }

    float getSize() const {
        return size_;
    }

    std::vector<Vertex> body;
    vec2 position;
protected:
    float angle_;
    float size_;

};

#endif
