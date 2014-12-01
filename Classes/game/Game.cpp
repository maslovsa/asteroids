#include "Game.h"
#include <iostream>

const float kFireZonePercentage = 85;
const float CONTROL_Y_PER_HEIGHT = 0.9f;
const int BULLET_VELOCITY_FACTOR = 6;
const float COLLISION_VELOCITY_IMPROVEMENT = 1.3f;
const float SHIP_ACCELERATE = 10;

Game::Game() {

}

Game::~Game() {
    for (auto a: asteroids) {
        delete a;
    }
}

void Game::init(int _width, int _height) {
    width = _width;
    height = _height;
    
    ship.init();
    
    keyUp.init(KEY_UP);
    keyDown.init(KEY_DOWN);
    keyFire.init(KEY_FIRE);
    
    keyUp.position.x =  -width + 1*width / 3;
    keyUp.position.y = -height * CONTROL_Y_PER_HEIGHT;
    keyDown.position.x = 0;
    keyDown.position.y = -height * CONTROL_Y_PER_HEIGHT;
    keyFire.position.x = width - 1*width / 3;
    keyFire.position.y = -height * CONTROL_Y_PER_HEIGHT;
    
    level_ = 1;
    m_pivotPoint.x = width / 2;
    m_pivotPoint.y = height / 2;
    shotZone = kFireZonePercentage / 100 * height;
    reset();
}

void Game::reset() {
    for (auto a : asteroids) {
        delete a;
    }
    asteroids.clear();

    for (auto b : bullets) {
        delete b;
    }
    bullets.clear();

    for (int i = 0; i < level_; ++i) {
        Asteroid *a = new Asteroid;
        a->position.x = rand() % width - width / 2;
        a->position.y = rand() % height - height / 2;
        a->velocity.x = 0.1f * level_ * (rand() % 2 - 2 );
        a->velocity.y = 0.1f * level_ * (rand() % 2 - 2 );
        asteroids.push_back(a);
    }
}

void Game::render(Painter &p) const {
    ship.render(p);

    for (auto a : asteroids) {
        a->render(p);
    }

    for (auto b : bullets) {
        b->render(p);
    }
    
    keyUp.render(p);
    keyDown.render(p);
    keyFire.render(p);
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
    keyUp.updateAnimation(keys);
    keyDown.updateAnimation(keys);
    keyFire.updateAnimation(keys);
    ship.updateAnimation(keys);
    
    if (keys[KEY_FIRE]) {
        Bullet *b = new Bullet;
        b->velocity.x = ship.direction.x * BULLET_VELOCITY_FACTOR;
        b->velocity.y = ship.direction.y * BULLET_VELOCITY_FACTOR;
        b->position.x = ship.getSize() * ship.direction.x;
        b->position.y = ship.getSize() * ship.direction.y;
        bullets.push_back(b);
    };

    vec2 v = vec2(0, 0);
    if (myKeys[KEY_UP] || myKeys[KEY_DOWN]) {
        currentDuration = 0.5f;
        v.x = (myKeys[KEY_DOWN] ? 1 : -1) * SHIP_ACCELERATE * ship.direction.x;
        v.y = (myKeys[KEY_DOWN] ? 1 : -1) * SHIP_ACCELERATE * ship.direction.y;
        currentVelocity = v;
    }
    if (currentDuration > 0) {
        std::cout << currentVelocity.x << currentVelocity.y << "\n";
        currentDuration -= timeStep;
        currentVelocity.x *= 0.9;
        currentVelocity.y *= 0.9;
        v = currentVelocity;
    }

    for (auto b: bullets) {
        b->updateAnimation(v);
    }

    for (auto a: asteroids) {
        a->updateAnimation(v);
    }
    bool isCollision = false;
    for (Asteroids::iterator a = asteroids.begin(); a != asteroids.end();) {
        for (Bullets::iterator b = bullets.begin(); b != bullets.end();) {
            float d = dist((*a)->position, (*b)->position);
            if (d < ((*a)->getSize() + (*b)->getSize())) {
                if ((*a)->isBig()) {
                    (*a)->setSize((*a)->getSize() / 2);
                    Asteroid *aa = new Asteroid(**a);
                    calculateCollidersVelocity((*a)->velocity, aa->velocity);
                    asteroids.push_back(aa);
                    delete *b;
                    bullets.erase(b);
                }
                else {
                    delete *a;
                    asteroids.erase(a);
                    
                    delete *b;
                    bullets.erase(b);
                    if (asteroids.empty()) {
                        ++level_;
                        reset();
                        return;
                    }
                }
                isCollision = true;
            } else {
                ++b;
            }
            if (isCollision)
                break;
        }
        
        ++a;
        if (isCollision)
            break;
    }


    for (Asteroids::iterator a = asteroids.begin(); a != asteroids.end(); ++a) {
        float d = distNormal((*a)->position);
        if (d < ((*a)->getSize() - 1)) {
            std::cout << "BANG! \n";
            level_ = 1;
            reset();
            return;
        }
    }

    for (Bullets::iterator b = bullets.begin(); b != bullets.end();) {
        if (!(*b)->isLive) {
            delete *b;
            bullets.erase(b);
        } else {
            ++b;
        }
    }

//    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &b) -> bool{
//        return !b.isLive;
//    }), bullets.end());

    //        {
    myKeys.reset();
}

void Game::onFingerUp(ivec2 location) {

}

void Game::onFingerDown(ivec2 location) {
    std::cout << "CLICK " << location.x << " " << location.y << "\n";
    bool isControlClicked = false;
    
    if(keyUp.isClicked(location)) {
        myKeys.set(KEY_UP);
        isControlClicked = true;
    }
    if(keyDown.isClicked(location)) {
        myKeys.set(KEY_DOWN);
        isControlClicked = true;
    }
    if(keyFire.isClicked(location)) {
        myKeys.set(KEY_FIRE);
        isControlClicked = true;
    }
    
    if (!isControlClicked) {
        vec2 direction = vec2(location - m_pivotPoint).Normalized();
        direction.y = -direction.y; // Flip the Y axis because pixel coords increase towards the bottom.
        float m_rotationAngle = (float) (std::acos(direction.y) * 180.0f * M_1_PI);
        if (direction.x > 0) {
            m_rotationAngle = -m_rotationAngle;
        }
        std::cout << "x " << direction.x << ":" << direction.y << " angle=" << m_rotationAngle << "\n";
        ship.direction = direction;
        ship.setAngel(m_rotationAngle);
    }
}

void Game::onFingerMove(ivec2 previous, ivec2 location) {

}

void Game::calculateCollidersVelocity(vec2 &a, vec2 &b) {
    b.x = -a.y * COLLISION_VELOCITY_IMPROVEMENT;
    b.y = a.x * COLLISION_VELOCITY_IMPROVEMENT;
    
    a.x = a.y * COLLISION_VELOCITY_IMPROVEMENT;
    a.y = -a.x * COLLISION_VELOCITY_IMPROVEMENT;
}


