#include "Game.h"
#include <iostream>

static float kFireZonePercentage = 85;

Game::Game() {

}

Game::~Game() {
    for (auto a: asteroids_) {
        delete a;
    }
}

void Game::init(int width, int height) {
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
    asteroids_.clear();

    for (int i = 0; i < level_; ++i) {
        Asteroid *a = new Asteroid;
        a->position.x = rand() % WIDTH - WIDTH / 2;
        a->position.y = rand() % HEIGHT - HEIGHT / 2;
        a->velocity.x = 0.1f;
        a->velocity.y = 0.1f;
        asteroids_.insert(a);
    }
}

void Game::render(Painter &p) const {
    ship_.render(p);

    for (auto b : bullets_) {
        b.render(p);
    }

    for (auto a : asteroids_) {
        a->render(p);
    }
}

float dist(const vec2 aPosition, const vec2 bPosition) {
    return (float) sqrt((bPosition.x - aPosition.x) * (bPosition.x - aPosition.x)
                                    + (bPosition.y - aPosition.y) * (bPosition.y - aPosition.y));
}

float distNormal(const vec2 aPosition) {
    return (float) sqrt(aPosition.x * aPosition.x + aPosition.y * aPosition.y);
}

Keys myKeys;

void Game::updateAnimation(float timeStep) {
    Keys keys = myKeys;
    ship_.updateAnimation(keys);

    float shipAngle = ship_.getAngle();// * M_PI / 180;
    if (keys[KEY_FIRE] && (bullets_.size() == 0 || bullets_.back().live > 200)) {
        Bullet b;
        b.velocity.x = 100 * cos(shipAngle);
        b.velocity.y = 100 * sin(shipAngle);
        b.position.x = 20 * cos(shipAngle);
        b.position.y = 20 * sin(shipAngle);
        bullets_.push_back(b);
    };

    vec2 v = vec2(0, 0);
    float accelerate = 1.0f;
    if (keys[KEY_UP]) {
        v.x = -accelerate * sin(shipAngle);
        v.y = -accelerate * cos(shipAngle);
        std::cout << "ACC+" << v.x << " " << v.y << "\n";
    }
//    if (keys[KEY_DOWN]) {
//        v.x = accelerate * sin(shipAngle);
//        v.y = accelerate * cos(shipAngle);
//        std::cout << "ACC-" << v.x << " " << v.y << "\n";
//    }

    for (auto b: bullets_) {
        b.updateAnimation(v);
    }
    for (auto a: asteroids_) {
        a->updateAnimation(v);
    }

//    for (Asteroids::const_iterator a = asteroids_.begin(); a != asteroids_.end(); ++a)
//        for (Bullets::iterator b = bullets_.begin(); b != bullets_.end(); ++b)
//        {
//            float d = dist((*a)->position, b->position);
//            if (d < ((*a)->getSize() + 1.5))
//            {
//                if ((*a)->getSize() > 8)
//                {
//                    (*a)->setSize((*a) -> getSize() / 1.414);
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
//        float d = distNormal((*a)->position);
//        if (d < ((*a) -> getSize() + 15))
//        {
//            reset();
//            return;
//        }
//    }
//    while (bullets_.size() != 0 && bullets_.front().live > 3000)
//        bullets_.pop_front();
    myKeys.reset();
}

void Game::onFingerUp(ivec2 location) {
    //std::cout << "UP "<< location.x << " " << location.y << "\n";
}

void Game::onFingerDown(ivec2 location) {
    if (location.y > shotZone) {
        //std::cout << "FIRE!!! \n";
        if (location.x < WIDTH / 3) {
            myKeys.set(KEY_UP);
        } else if (location.x < WIDTH / 2 * 3) {
            myKeys.set(KEY_DOWN);
        } else {
            myKeys.set(KEY_FIRE);
        }

    } else {
        vec2 direction = vec2(location - m_pivotPoint).Normalized();
        direction.y = -direction.y; // Flip the Y axis because pixel coords increase towards the bottom.
        float m_rotationAngle = (float) (std::acos(direction.y) * 180.0f * M_1_PI);
        if (direction.x > 0) {
            m_rotationAngle = -m_rotationAngle;
        }
        ship_.setAngel(m_rotationAngle);
    }
}

void Game::onFingerMove(ivec2 previous, ivec2 location) {
//    if (location.y > shotZone) {
//        return;
//    }
//    vec2 direction = vec2(location - m_pivotPoint).Normalized();
//    direction.y = -direction.y; // Flip the Y axis because pixel coords increase towards the bottom.
//    float m_rotationAngle = std::acos(direction.y) * 180.0f * M_1_PI;
//    if (direction.x > 0) {
//        m_rotationAngle = -m_rotationAngle;
//    }
//    ship_.setAngel(m_rotationAngle);
//

}


