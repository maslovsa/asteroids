#include <OpenGLES/ES2/gl.h>
#include "IRenderingEngine.hpp"
#include "Game.h"
#include "Painter.h"
#define STRINGIFY(A)  #A
#include "../Shaders/Simple.vert"
#include "../Shaders/Simple.frag"
#include "ShaderHelper.h"

class RenderingEngine : public IRenderingEngine {
public:
    RenderingEngine();
    void init(int width, int height);
    void render() const;
    void updateAnimation(float timeStep);
    void onFingerUp(ivec2 location);
    void onFingerDown(ivec2 location);
    void onFingerMove(ivec2 oldLocation, ivec2 newLocation);
private:
    void applyOrtho(float maxX, float maxY) const;
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
};

IRenderingEngine* CreateRenderer()
{
    return new RenderingEngine();
}

RenderingEngine::RenderingEngine()
{
    // Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
}

void RenderingEngine::init(int width, int height)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1);
    // Create the framebuffer object and attach the color buffer.
    glGenFramebuffers(1, &m_framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                              GL_COLOR_ATTACHMENT0,
                              GL_RENDERBUFFER,
                              m_renderbuffer);

    glViewport(0, 0, width, height);

    m_simpleProgram = shader::BuildProgram(SimpleVertexShader, SimpleFragmentShader);
    glUseProgram(m_simpleProgram);

    // init the projection matrix.
    applyOrtho(width, height);
    Game::getInstance().init(width, height);
}

void RenderingEngine::applyOrtho(float maxX, float maxY) const
{
    float a = 1.0f / maxX;
    float b = 1.0f / maxY;
    float ortho[16] = {
        a, 0,  0, 0,
        0, b,  0, 0,
        0, 0, -1, 0,
        0, 0,  0, 1
    };

    GLint projectionUniform = glGetUniformLocation(m_simpleProgram, "Projection");
    glUniformMatrix4fv(projectionUniform, 1, 0, &ortho[0]);
}

void RenderingEngine::render() const {
    glClear(GL_COLOR_BUFFER_BIT);
    Painter p(m_simpleProgram);
    Game::getInstance().render(p);
}

void RenderingEngine::onFingerUp(ivec2 location){
    Game::getInstance().onFingerUp(location);
}

void RenderingEngine::onFingerDown(ivec2 location){
    Game::getInstance().onFingerDown(location);
}

void RenderingEngine::onFingerMove(ivec2 previous, ivec2 location){
    Game::getInstance().onFingerMove(previous, location);
}

void RenderingEngine::updateAnimation(float timeStep) {
    Game::getInstance().updateAnimation(timeStep);
}
