//
//  Painter.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef Asteroids_Painter_h
#define Asteroids_Painter_h

#include "jet.hpp"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <vector>
#include "vector.hpp"
#include "Asteroid.h"
#include "Bullet.h"
#include "Ship.h"

class Painter {
public:
    Painter(GLuint program);

    //void drawAsteroid(const Asteroid *asteroid);

    void drawShip(const Ship *ship);

    void drawGameObject(const GameObject *gameObject);

    GLuint m_simpleProgram;
};

#endif
