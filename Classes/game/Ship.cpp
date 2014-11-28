#include "Ship.h"
#include "Painter.h"

#define _USE_MATH_DEFINES

#include "Game.h"

Ship::Ship() {
    size_ = SHIP_SIZE;
    Vertex vertex;

    vec4 color(1, 1, 1, 1);
    vertex.Color = color;

    vertex.Position = vec2(0, size_ / 2);
    body.push_back(vertex);
    vertex.Position = vec2(size_ / 3, -size_ / 4);
    body.push_back(vertex);
    vertex.Position = vec2(0, 0);
    body.push_back(vertex);
    vertex.Position = vec2(-size_ / 3, -size_ / 4);
    body.push_back(vertex);
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
