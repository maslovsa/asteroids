#include "Bullet.h"
#include "Game.h"
#include "Painter.h"

Bullet::Bullet()
            : live(0) {
}

//Bullet::~Bullet() {
//    std::cout << "die bullet\n";
//}

void Bullet::tick(vec2 acel) {
    vx += acel.x * Game::getInstance().DELTA_T / 1000.0f;
    vy += acel.y * Game::getInstance().DELTA_T / 1000.0f;
    position.x += vx * Game::getInstance().DELTA_T / 1000.0f;
    position.y += vy * Game::getInstance().DELTA_T / 1000.0f;
    if (position.x > Game::getInstance().WIDTH / 2) {
        position.x -= Game::getInstance().WIDTH;
    }
    if (position.y > Game::getInstance().HEIGHT / 2) {
        position.y -= Game::getInstance().HEIGHT;
    }
    if (position.x < -Game::getInstance().WIDTH / 2) {
        position.x += Game::getInstance().WIDTH;
    }
    if (position.y < -Game::getInstance().HEIGHT / 2) {
        position.y += Game::getInstance().HEIGHT;
    }
    live += Game::getInstance().DELTA_T;
}

void Bullet::draw(Painter &p) const {
    p.drawBullet(position.x, position.y);
}
