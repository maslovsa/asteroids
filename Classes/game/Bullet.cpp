#include "Bullet.h"
#include "Game.h"
#include "Painter.h"

Bullet::Bullet()
            : isLive(true) {
    size = Game::getInstance().getWidth() / 10 / 8;
    vAngle = 0.9f;
    scale = 1.0f;
    Vertex vertex;
    vertex.Color = vec4(1, 0, 0, 1);

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
    angle += vAngle;
}

void Bullet::render(Painter &p) const {
    p.drawGameObject(this);
}
