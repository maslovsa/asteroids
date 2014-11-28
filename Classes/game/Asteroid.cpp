#include "Asteroid.h"
#include "Game.h"
#include "Painter.h"
#include <iostream>

Asteroid::Asteroid() {
    angle_ = rand() % 31400 / 1000.0f;
    vAngle = 0.3f;
    size_ = ASTEROID_SIZE;
    Vertex vertex;
    vec4 color(0, 1, 1, 1);
    vertex.Color = color;
    int vertexCount = 8 + rand() % 8;
    for (int i = 0; i < vertexCount; ++i) {
        float kFactor = (i % 3) ? (rand() % 5 + 5) / 10.f : 1.0f;
        vertex.Position = vec2(sin(2 * M_PI / vertexCount * i) * ASTEROID_SIZE / 2 * kFactor,
                               cos(2 * M_PI / vertexCount * i) * ASTEROID_SIZE / 2 * kFactor);
        body.push_back(vertex);
    }
}

void Asteroid::updateAnimation(vec2 acc) {
    auto width = Game::getInstance().getWidth();
    auto height = Game::getInstance().getHeight();

    //velocity.x = std::max(std::min(velocity.x + acc.x, ASTEROID_SPEED_MAX), -ASTEROID_SPEED_MAX);
    //velocity.y = std::max(std::min(velocity.y + acc.y, ASTEROID_SPEED_MAX), -ASTEROID_SPEED_MAX);
    
    position.x += velocity.x + acc.x;
    position.y += velocity.y + acc.y;
    
    if (position.x > width / 2) {
        position.x -= width;
    }
    if (position.y > height / 2) {
        position.y -= height;
    }
    if (position.x < -width / 2) {
        position.x += width;
    }
    if (position.y < -height / 2) {
        position.y += height;
    }
    //std::cout << position.x << " " << position.y << " speed " << velocity.x << ":" << velocity.y << "\n";
    angle_ += vAngle;
}

void Asteroid::render(Painter &p) const {
    p.drawGameObject(this);
}

void Asteroid::setSize(float size) {
    size_ = size;
}
