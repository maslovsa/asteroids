#include "Game.h"
#include <iostream>

static float kFireZonePercentage = 85;

Game::Game() {

}

Game::~Game() {
    for (auto a : asteroids_) {
        delete a;
    }
//    for (Asteroids::iterator i = asteroids_.begin(); i != asteroids_.end(); ++i)
//        delete *i;
}

void Game::Initialize(int width, int height) {
    WIDTH = width;
    HEIGHT = height;
    DELTA_T = 1000 / 10;
    level_ = 1;
//    m_pivotPoint.x = width / 3;
//    m_pivotPoint.y = height - width / 3;
    m_pivotPoint.x = width / 2;
    m_pivotPoint.y = height / 2;
    shotZone = kFireZonePercentage / 100 * height;
    reset();
}

void Game::reset() {
    if (!bullets_.empty()) {
        bullets_.clear();
    }

    for (auto a : asteroids_) {
        delete a;
    }
//    for (Asteroids::iterator i = asteroids_.begin(); i != asteroids_.end(); ++i) {
//        delete *i;
//    }
    asteroids_.clear();
    for (int i = 0; i < level_; ++i) {
        Asteroid *a = new Asteroid;
        //a -> setSize(ASTEROID_SIZE);
        a->position.x = rand() % WIDTH - WIDTH / 2;
        a->position.y = rand() % HEIGHT - HEIGHT / 2;
        a->vx = rand() % 40 - 20;
        a->vy = rand() % 40 - 20;
        asteroids_.insert(a);
    }
}

void Game::draw(Painter &p) const {
    ship_.draw(p);

    for (auto b : bullets_) {
        b.draw(p);
    }

    for (auto a : asteroids_) {
        a->draw(p);
    }
}

void Game::tick(Keys keys) {
    ship_.tick(keys);
    float shipAngle = ship_.getAngle();
    if (keys[KEY_FIRE] && (bullets_.size() == 0 || bullets_.back().live > 200)) {
        Bullet b;
        b.vx = 100 * cos(shipAngle);
        b.vy = 100 * sin(shipAngle);
        b.position.x = 20 * cos(shipAngle);
        b.position.y = 20 * sin(shipAngle);
        bullets_.push_back(b);
    };

    vec2 v = vec2(0, 0);

    if (keys[KEY_UP]) {
        v.x = -200 * cos(shipAngle);
        v.y = -200 * sin(shipAngle);
    }
    if (keys[KEY_DOWN]) {
        v.x = 200 * cos(shipAngle);
        v.y = 200 * sin(shipAngle);
    }

    for (auto b : bullets_) {
        b.tick(v);
    }
    for (auto a : asteroids_) {
        a->tick(v);
    }

//    for (Asteroids::const_iterator a = asteroids_.begin(); a != asteroids_.end(); ++a)
//        for (Bullets::iterator b = bullets_.begin(); b != bullets_.end(); ++b)
//        {
//            float d = sqrt((b -> x - (*a) ->position.x) * (b -> x - (*a) ->position.x) + (b -> y - (*a) ->position.y) * (b -> y - (*a) ->position.y));
//            if (d < ((*a) -> getSize() + 1.5))
//            {
//                if ((*a) -> getSize() > 8)
//                {
//                    (*a) -> setSize((*a) -> getSize() / 1.414);
//                    Asteroid *aa = new Asteroid(**a);
//                    aa -> vx += rand() % 20 - 20;
//                    aa -> vy += rand() % 20 - 20;
//                    asteroids_.insert(aa);
//                }
//                else
//                {
//                    delete *a;
//                    asteroids_.erase(*a);
//                    if (asteroids_.size() == 0)
//                    {
//                        ++level_;
//                        reset();
//                        return;
//                    }
//                }
//                goto a;
//            }
//        }
//    a:
//    for (Asteroids::const_iterator a = asteroids_.begin(); a != asteroids_.end(); ++a)  {
//        float d = sqrt((*a) ->position.x * (*a)->position.x + (*a) ->position.y * (*a) ->position.y);
//        if (d < ((*a) -> getSize() + 15))
//        {
//            reset();
//            return;
//        }
//    }
//    while (bullets_.size() != 0 && bullets_.front().live > 3000)
//        bullets_.pop_front();
}

void Game::OnFingerUp(ivec2 location) {
    //std::cout << "UP "<< location.x << " " << location.y << "\n";
}

void Game::OnFingerDown(ivec2 location) {
    std::cout << "DO " << location.x << " " << location.y << "\n";
    if (location.y > shotZone) {
        std::cout << "FIRE!!! \n";
        Keys keys;
        keys.set(KEY_FIRE);
        tick(keys);
    }
}

void Game::OnFingerMove(ivec2 previous, ivec2 location) {
    if (location.y > shotZone) {
        return;
    }
    vec2 direction = vec2(location - m_pivotPoint).Normalized();
    direction.y = -direction.y; // Flip the Y axis because pixel coords increase towards the bottom.
    float m_rotationAngle = std::acos(direction.y) * 180.0f / 3.14159f;
    if (direction.x > 0) {
        m_rotationAngle = -m_rotationAngle;
    }
    ship_.setAngel(m_rotationAngle);
    Keys keys;
    keys.set(KEY_UP);
    ship_.tick(keys);
}

int Game::getLevel() const {
    return level_;
}
