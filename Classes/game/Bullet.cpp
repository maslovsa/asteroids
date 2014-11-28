#include "Bullet.h"
#include "Game.h"
#include "Painter.h"

Bullet::Bullet()
            : live(0) {
    size_ = BULLET_SIZE;
    Vertex vertex;
    vec4 color(1, 0, 0, 1);
    vertex.Color = color;
    vertex.Position = vec2(-size_ / 2, size_ / 2);
    body.push_back(vertex);
    vertex.Position = vec2(size_ / 2, size_ / 2);
    body.push_back(vertex);
    vertex.Position = vec2(size_ / 2, -size_ / 2);
    body.push_back(vertex);
    vertex.Position = vec2(-size_ / 2, -size_ / 2);
    body.push_back(vertex);
}

void Bullet::updateAnimation(vec2 acc) {
    auto width = Game::getInstance().getWidth();
    auto height = Game::getInstance().getHeight();
    auto delta = Game::getInstance().getDelta();

    velocity.x += acc.x * delta / 1000.0f;
    velocity.y += acc.y * delta / 1000.0f;
    position.x += velocity.x * delta / 1000.0f;
    position.y += velocity.y * delta / 1000.0f;
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
    live += delta;
    angle_ += 3.0f * delta / 1000.0f;
}

void Bullet::render(Painter &p) const {
    p.drawGameObject(this);
}
