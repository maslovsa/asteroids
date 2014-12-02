#include "Ship.h"
#include "Painter.h"
#include "Game.h"

Ship::Ship() {
}

void Ship::init() {
    angle = 0;
    size = Game::getInstance().getWidth() / 10;
    scale = 1.0f;
    Vertex vertex;
    direction = vec2(0, 1);

    vertex.Color = vec4(1, 1, 1, 1);
    MakePoint(0, size / 2);
    MakePoint(sin(2 * M_PI / 3 * 1) * size / 2,
              cos(2 * M_PI / 3 * 1) * size / 2);
    MakePoint(0, 0);
    MakePoint(sin(2 * M_PI / 3 * 2) * size / 2,
              cos(2 * M_PI / 3 * 2) * size / 2);
}

void Ship::updateAnimation(Keys keys) {
    jet_[JET_FRONT] = keys[KEY_DOWN];
    jet_[JET_BACK] = keys[KEY_UP];
}

void Ship::render(Painter &p) const {
    p.drawShip(this);
}

void Ship::setAngel(float _angle) {
    angle = _angle;
}
