#include "Ship.h"
#include "Painter.h"
#include "Game.h"

Ship::Ship() {
    size = SHIP_SIZE;
    scale = 1.0f;
    Vertex vertex;

    vec4 color(1, 1, 1, 1);
    vertex.Color = color;

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
