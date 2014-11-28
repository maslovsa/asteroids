#include "Game.h"
#include <iostream>
#include <algorithm>

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
    for (auto a : asteroids_) {
        delete a;
    }
    asteroids_.clear();
    
    for (auto b : bullets_) {
        delete b;
    }
    bullets_.clear();
    
    for (int i = 0; i < level_; ++i) {
        Asteroid *a = new Asteroid;
        a->position.x = rand() % WIDTH - WIDTH / 2;
        a->position.y = rand() % HEIGHT - HEIGHT / 2;
        a->velocity.x = 0.1f;
        a->velocity.y = 0.1f;
        asteroids_.push_back(a);
    }
}

void Game::render(Painter &p) const {
    ship_.render(p);
    
    for (auto a : asteroids_)
        a->render(p);

    for (auto b : bullets_)
        b->render(p);
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
    if (keys[KEY_FIRE]) {
        std::cout << "FIRE!!! \n";
        Bullet *b = new Bullet;
        b->velocity.x = ship_.direction.x;
        b->velocity.y = ship_.direction.y;
        b->position.x = ship_.size_ * ship_.direction.x;
        b->position.y = ship_.size_ * ship_.direction.y;
        bullets_.push_back(b);
    };

    vec2 v = vec2(0, 0);
    float accelerate = 5.0f;
    if (keys[KEY_UP]) {
        v.x = -accelerate * ship_.direction.x;
        v.y = -accelerate * ship_.direction.y;
        std::cout << "ACC+ :" << v.x << " " << v.y << "\n";
    }
    if (keys[KEY_DOWN]) {
        v.x = accelerate * ship_.direction.x;
        v.y = accelerate * ship_.direction.y;
        std::cout << "ACC- :" << v.x << " " << v.y << "\n";
    }

    for (auto b: bullets_)
        b->updateAnimation(v);
    
    for (auto a: asteroids_)
        a->updateAnimation(v);
    

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
    
    for (Bullets::iterator b = bullets_.begin(); b != bullets_.begin();){
        if (!(*b)->isLive) {
            delete *b;
            bullets_.erase(b);
            std::cout << "erase \n";
        } else {
            ++b;
        } // перейти на shared
    }
    
//    bullets_.erase(std::remove_if(bullets_.begin(), bullets_.end(), [](const Bullet &b) -> bool{
//        return !b.isLive;
//    }), bullets_.end());
    
    //        {
    myKeys.reset();
}

void Game::onFingerUp(ivec2 location) {
    //std::cout << "UP "<< location.x << " " << location.y << "\n";
}

void Game::onFingerDown(ivec2 location) {
    std::cout << "CLICK "<< location.x << " " << location.y << "\n";
    if (location.y > shotZone) {
        //
        if (location.x < WIDTH / 3) {
            myKeys.set(KEY_UP);
        } else if (location.x < WIDTH / 3 * 2) {
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
        std::cout << "x "<< direction.x << ":" << direction.y << " angle="<<m_rotationAngle << "\n";
        ship_.direction = direction;
        ship_.setAngel(m_rotationAngle);
    }
}

void Game::onFingerMove(ivec2 previous, ivec2 location) {


}


