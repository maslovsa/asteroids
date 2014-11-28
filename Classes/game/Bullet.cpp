#include "Bullet.h"
#include "Game.h"
#include "Painter.h"
#include <iostream>
Bullet::Bullet()
            : live(0), isLive(true) {
    size_ = BULLET_SIZE;
    vAngle = 0.9f;
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
   // auto delta = Game::getInstance().getDelta();

    //velocity.x = std::max(std::min(velocity.x + acc.x, ASTEROID_SPEED_MAX), -ASTEROID_SPEED_MAX);
    //velocity.y = std::max(std::min(velocity.y + acc.y, ASTEROID_SPEED_MAX), -ASTEROID_SPEED_MAX);
    
    position.x += velocity.x + acc.x;
    position.y += velocity.y + acc.y;
    if (position.x > width / 2) {
        isLive = false;
    }
    if (position.y > height / 2) {
        isLive = false;
    }
    if (position.x < -width / 2) {
        isLive = false;
    }
    if (position.y < -height / 2) {
        isLive = false;
    }
    if (!isLive){
     std::cout << "now erase \n";
    }
    angle_ += vAngle;
}

void Bullet::render(Painter &p) const {
    p.drawGameObject(this);
}
