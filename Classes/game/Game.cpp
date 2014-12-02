#include "Game.h"
#include <iostream>

const float CONTROL_Y_PER_HEIGHT = 0.9f;
const float BULLET_VELOCITY_FACTOR = 6;
const float COLLISION_VELOCITY_IMPROVEMENT = 1.3f;
const float SHIP_ACCELERATE = 5;
const float SHIP_ACCELERATE_FACTOR = 0.95;
const float SHIP_ACCELERATE_DURATION = 20.f;

Game::Game() {

}

Game::~Game() {
    asteroids.clear();
}

void Game::init(int _width, int _height) {
    width = _width;
    height = _height;

    ship.init();

    controlUp.init(KEY_UP);
    controlDown.init(KEY_DOWN);
    controlFire.init(KEY_FIRE);

    controlUp.position.x = -width + width / 3;
    controlUp.position.y = -height * CONTROL_Y_PER_HEIGHT;
    controlDown.position.x = 0;
    controlDown.position.y = -height * CONTROL_Y_PER_HEIGHT;
    controlFire.position.x = width - width / 3;
    controlFire.position.y = -height * CONTROL_Y_PER_HEIGHT;

    level = 1;
    pivotPoint.x = width / 2;
    pivotPoint.y = height / 2;

    reset();
}

float dist(const vec2 aPosition, const vec2 bPosition) {
    return (float) sqrt((bPosition.x - aPosition.x) * (bPosition.x - aPosition.x)
                        + (bPosition.y - aPosition.y) * (bPosition.y - aPosition.y));
}

float distNormal(const vec2 aPosition) {
    return (float) sqrt(aPosition.x * aPosition.x + aPosition.y * aPosition.y);
}

int randomSign() {
    return ((rand() % 10) % 2==0) ? 1 : -1;
}

void Game::reset() {
    asteroids.clear();
    bullets.clear();
    for (int i = 0; i < level; ++i) {
        AsteroidPtr asteroid(new Asteroid());
        asteroid->position.x = rand() % width - width / 2;
        asteroid->position.y = rand() % height - height / 2;
        asteroid->velocity.x = randomSign() * 0.1f * level;
        asteroid->velocity.y = randomSign() * 0.1f * level;
        asteroids.push_back(std::move(asteroid));
    }
}

void Game::render(Painter &p) const {
    ship.render(p);

    for (auto a = asteroids.begin(); a != asteroids.end(); ++a)
        a->get()->render(p);
    
    for (auto b = bullets.begin(); b != bullets.end(); ++b)
        b->get()->render(p);

    controlUp.render(p);
    controlDown.render(p);
    controlFire.render(p);
}


Keys myKeys;

void Game::updateAnimation(float timeStep) {
    Keys keys = myKeys;
    controlUp.updateAnimation(keys);
    controlDown.updateAnimation(keys);
    controlFire.updateAnimation(keys);

    if (keys[KEY_FIRE]) {
        BulletPtr bullet(new Bullet());
        bullet->velocity.x = ship.direction.x * BULLET_VELOCITY_FACTOR;
        bullet->velocity.y = ship.direction.y * BULLET_VELOCITY_FACTOR;
        bullet->position.x = ship.getSize() * ship.direction.x;
        bullet->position.y = ship.getSize() * ship.direction.y;
        bullets.push_back(std::move(bullet));
    };

    vec2 v = vec2(0, 0);
    if (myKeys[KEY_UP] || myKeys[KEY_DOWN]) {
        currentDuration = SHIP_ACCELERATE_DURATION;
        v.x = (myKeys[KEY_DOWN] ? 1 : -1) * SHIP_ACCELERATE * ship.direction.x;
        v.y = (myKeys[KEY_DOWN] ? 1 : -1) * SHIP_ACCELERATE * ship.direction.y;
        oldKeys = myKeys;
        currentVelocity = v;
    } else {
        if (--currentDuration > 0) {
            std::cout << currentVelocity.x << currentVelocity.y << "\n";
            if (currentDuration > SHIP_ACCELERATE_DURATION / 2) {
                v.x = currentVelocity.x * currentDuration / SHIP_ACCELERATE_DURATION / 2;
                v.y = currentVelocity.y * currentDuration / SHIP_ACCELERATE_DURATION / 2;
            } else {
                currentVelocity.x *= SHIP_ACCELERATE_FACTOR;
                currentVelocity.y *= SHIP_ACCELERATE_FACTOR;
                v = currentVelocity;
            }
            myKeys = oldKeys;
        }
    }

    ship.updateAnimation(myKeys);

    for (auto a = asteroids.begin(); a != asteroids.end(); ++a)
        a->get()->updateAnimation(v);
    
    for (auto b = bullets.begin(); b != bullets.end(); ++b)
        b->get()->updateAnimation(v);
    
    checkColliders();

    myKeys.reset();
}

void Game::checkColliders() {
    bool isCollision = false;
    for (auto a = asteroids.begin(); a != asteroids.end();) {
        for (auto b = bullets.begin(); b != bullets.end();) {
            float d = dist((*a)->position, (*b)->position);
            if (d < ((*a)->getSize() + (*b)->getSize())) {
                if ((*a)->isBig()) {
                    (*a)->setSize((*a)->getSize() / 2);
                    AsteroidPtr asteroidNew(new Asteroid(**a));
                    calculateCollidersVelocity((*a)->velocity, asteroidNew->velocity);
                    asteroids.push_back(std::move(asteroidNew));
                    bullets.erase(b);
                } else {
                    asteroids.erase(a);
                    bullets.erase(b);
                    if (asteroids.empty()) {
                        ++level;
                        reset();
                        return;
                    }
                }
                isCollision = true;
            } else {
                ++b;
            }
            if (isCollision) {
                break;
            }
        }

        ++a;
        if (isCollision) {
            break;
        }
    }

    for (auto a = asteroids.begin(); a != asteroids.end(); ++a) {
        float d = distNormal((*a)->position);
        if (d < ((*a)->getSize() - 1)) {
            std::cout << "GAME OVER! \n";
            level = 1;
            reset();
            return;
        }
    }

    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](std::unique_ptr<Bullet> const& b) -> bool{
            return !b.get()->isLive;
       }), bullets.end());
}

void Game::onFingerUp(ivec2 location) {

}

void Game::onFingerDown(ivec2 location) {
    std::cout << "CLICK " << location.x << " " << location.y << "\n";
    bool isControlClicked = false;

    if (controlUp.isClicked(location)) {
        myKeys.set(KEY_UP);
        isControlClicked = true;
    }
    if (controlDown.isClicked(location)) {
        myKeys.set(KEY_DOWN);
        isControlClicked = true;
    }
    if (controlFire.isClicked(location)) {
        myKeys.set(KEY_FIRE);
        isControlClicked = true;
    }

    if (!isControlClicked) {
        vec2 direction = vec2(location - pivotPoint).Normalized();
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


