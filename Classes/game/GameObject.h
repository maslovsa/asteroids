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
        return angle_;
    }

    float getSize() const {
        return size_;
    }
    
public:
    std::vector<Vertex> body;
    vec2 position;
    vec2 velocity;
    float size_;
    float vAngle;
    
protected:
    float angle_; // radians
    
};

#endif
