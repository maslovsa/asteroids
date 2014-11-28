#include "Asteroid.h"
#include "Game.h"
#include "Painter.h"

Asteroid::Asteroid() {
    angle_ = rand() % 31400 / 1000.0f;
    //    for (int i = 0; i < 5; ++i)
    //glVertex2f(sin(2 * M_PI / 5 * i), cos(2 * M_PI / 5 * i));
    size_ = ASTEROID_SIZE;
    Vertex vertex;
    vec4 color(0, 1, 1, 1);
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

void Asteroid::tick(vec2 acel) {
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
    angle_ += 3.0f * Game::getInstance().DELTA_T / 1000.0f;
}

void Asteroid::draw(Painter &p) const {
    p.drawAsteroid(this);
}

void Asteroid::setSize(float size) {
    size_ = size;
}
