#include "Asteroid.h"
#include "Game.h"
#include "Painter.h"
#include <iostream>

Asteroid::Asteroid() {
    angle = rand() % 360;
    vAngle = 0.3f;
    scale = 1.0f;
    size = Game::getInstance().getWidth() / 8;
    Vertex vertex;
    vec4 color(0, 1, 1, 1);
    vertex.Color = color;
    int vertexCount = 8 + rand() % 8;
    for (int i = 0; i < vertexCount; ++i) {
        float kFactor = (i % 3) ? (rand() % 5 + 5) / 10.f : 1.0f;
        MakePoint(sin(2 * M_PI / vertexCount * i) * size / 2 * kFactor,
                  cos(2 * M_PI / vertexCount * i) * size / 2 * kFactor);
    }
}

void Asteroid::updateAnimation(vec2 acc) {
    auto width = Game::getInstance().getWidth();
    auto height = Game::getInstance().getHeight();

    position.x += velocity.x + acc.x;
    position.y += velocity.y + acc.y;

    if (position.x > width ) {
        position.x = -width;
    }
    if (position.y > height) {
        position.y = -height;
    }
    if (position.x < -width ) {
        position.x = width;
    }
    if (position.y < -height ) {
        position.y = height;
    }
    angle += vAngle;
}

void Asteroid::render(Painter &p) const {
    p.drawGameObject(this);
}

void Asteroid::setSize(float _size) {
    scale =  _size / size;
    size = _size;
}
