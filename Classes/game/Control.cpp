#include "Control.h"
#include "Game.h"
#include "Painter.h"
#include "Entities.h"
#include <iostream>

Control::Control() {

}

void Control::init(KeyState _keystate) {
    keystate = _keystate;
    size = Game::getInstance().getWidth() / 5;
    angle_ = 0;
    scale = 1.0f;
    Vertex vertex;

    switch (keystate) {
        case KEY_UP:
            vertex.Color = vec4(0, 1, 0, 1);
            MakePoint(0, size / 2);
            MakePoint(size / 2, 0);
            MakePoint(size / 4, 0);
            MakePoint(size / 4, -size / 2);
            MakePoint(-size / 4, -size / 2);
            MakePoint(-size / 4, 0);
            MakePoint(-size / 2, 0);
            break;
            
        case KEY_DOWN:
            vertex.Color = vec4(1, 1, 0, 1);
            MakePoint(0, size / 2);
            MakePoint(size / 2, 0);
            MakePoint(size / 4, 0);
            MakePoint(size / 4, -size / 2);
            MakePoint(-size / 4, -size / 2);
            MakePoint(-size / 4, 0);
            MakePoint(-size / 2, 0);
            break;
           
        case KEY_FIRE:
            Vertex vertex;
            vertex.Color = vec4(1,0,0,1);
            int vertexCount = 16;
            for (int i = 0; i < vertexCount; ++i) {
                float kFactor = (i % 2) ? 0.5f : 1.0f;
                MakePoint(sin(2 * M_PI / vertexCount * i) * size / 2 * kFactor,
                          cos(2 * M_PI / vertexCount * i) * size / 2 * kFactor);
            }
            break;
    }
    
    if (keystate == KEY_DOWN) {
        angle_= 180;
    }
}

void Control::updateAnimation(Keys keys) {
    if (keys[keystate]) {
        scale = 1.2f;
    } else {
        scale = 1;
    }
}

void Control::render(Painter &p) const {
    p.drawGameObject(this);
}

bool Control::isClicked(vec2 location) {
    auto width = Game::getInstance().getWidth();
    auto height = Game::getInstance().getHeight();
    vec2 originInScreen;
    originInScreen.x = (position.x + width) / 2;
    originInScreen.y = (-position.y + height) / 2;
    
    float distance = (float) sqrt((originInScreen.x - location.x) * (originInScreen.x - location.x)
                                  + (originInScreen.y - location.y) * (originInScreen.y - location.y));
    if(distance <= size) {
        return true;
    } else {
        return false;
    }
}
