#include "Ship.h"
#include "Painter.h"
#include "Game.h"

Ship::Ship() {
}

void Ship::init() {
    angle_ = 0;
    size = Game::getInstance().getWidth() / 10;
    scale = 1.0f;
    Vertex vertex;
    direction = vec2(0,1);

    vertex.Color = vec4(1, 1, 1, 1);
    MakePoint(0, size / 2);
    MakePoint(size / 3, -size / 4);
    MakePoint(0, 0);
    MakePoint(-size / 3, -size / 4);
}

void Ship::updateAnimation(Keys keys) {
    jet_[JET_FRONT] = keys[KEY_DOWN];
    jet_[JET_BACK] = keys[KEY_UP];
}

void Ship::render(Painter &p) const {
    p.drawShip(this);
}

void Ship::setAngel(float angle) {
    angle_ = angle;
}
