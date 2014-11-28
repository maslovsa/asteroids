#include "Vector.hpp"

// Create an instance of the renderer and set up various OpenGL state.
struct IRenderingEngine *CreateRenderer();

// Interface to the OpenGL ES renderer; consumed by GLView.
struct IRenderingEngine {
    virtual void init(int width, int height) = 0;

    virtual void render() const = 0;

    virtual void updateAnimation(float timeStep) = 0;

    virtual void onFingerUp(ivec2 location) = 0;

    virtual void onFingerDown(ivec2 location) = 0;

    virtual void onFingerMove(ivec2 oldLocation, ivec2 newLocation) = 0;

    virtual ~IRenderingEngine() {
    }
};
