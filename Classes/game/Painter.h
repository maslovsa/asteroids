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

class Painter {
public:
    Painter(GLuint program);

    void drawAsteroid(const Asteroid *asteroid);

    void drawShip(std::vector<Vertex> body, float angle, Jet state);

    void drawBullet(float x, float y);

    GLuint m_simpleProgram;
};

#endif
