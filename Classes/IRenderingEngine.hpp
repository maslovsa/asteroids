#include "Vector.hpp"

// Create an instance of the renderer and set up various OpenGL state.
struct IRenderingEngine *CreateRenderer();

// Interface to the OpenGL ES renderer; consumed by GLView.
struct IRenderingEngine {
    virtual void Initialize(int width, int height) = 0;

    virtual void Render() const = 0;

    virtual void UpdateAnimation(float timeStep) = 0;

    virtual void OnFingerUp(ivec2 location) = 0;

    virtual void OnFingerDown(ivec2 location) = 0;

    virtual void OnFingerMove(ivec2 oldLocation, ivec2 newLocation) = 0;

    virtual ~IRenderingEngine() {
    }
};
