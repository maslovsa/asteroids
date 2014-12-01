#include "Bullet.h"
#include "Game.h"
#include "Painter.h"
#include "Entities.h"
#include <iostream>

Bullet::Bullet()
            : isLive(true) {
    size = BULLET_SIZE;
    vAngle = 0.9f;
    scale = 1.0f;
    Vertex vertex;
    vec4 color(1, 0, 0, 1);
    vertex.Color = color;

    MakePoint(-size / 2, size / 2);
    MakePoint(size / 2, size / 2);
    MakePoint(size / 2, -size / 2);
    MakePoint(-size / 2, -size / 2);
}

void Bullet::updateAnimation(vec2 acc) {
    auto width = Game::getInstance().getWidth();
    auto height = Game::getInstance().getHeight();

    position.x += velocity.x + acc.x;
    position.y += velocity.y + acc.y;
    if (position.x > width ) {
        isLive = false;
    }
    if (position.y > height ) {
        isLive = false;
    }
    if (position.x < -width ) {
        isLive = false;
    }
    if (position.y < -height) {
        isLive = false;
    }
    if (!isLive) {
        std::cout << "now erase \n";
    }
    angle_ += vAngle;
}

void Bullet::render(Painter &p) const {
    p.drawGameObject(this);
}
