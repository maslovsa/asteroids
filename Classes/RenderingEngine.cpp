#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "IRenderingEngine.hpp"
#include "Matrix.hpp"
#include "Game.h"
#include "Painter.h"
#define STRINGIFY(A)  #A
#include "../Shaders/Simple.vert"
#include "../Shaders/Simple.frag"
#include "ShaderHelper.h"

class RenderingEngine : public IRenderingEngine {
public:
    RenderingEngine();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep);
    void OnFingerUp(ivec2 location);
    void OnFingerDown(ivec2 location);
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation);
private:
    void ApplyOrtho(float maxX, float maxY) const;
    float m_desiredAngle;
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
    ivec2 m_pivotPoint;
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

void RenderingEngine::Initialize(int width, int height)
{
    m_pivotPoint = ivec2(width / 2, height / 2);
    glClearColor(0.02f, 0.02f, 0.02f, 1);
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
    
    // Initialize the projection matrix.
    //ApplyOrtho(2, 3);
    ApplyOrtho(width, height);
    Game::getInstance().Initialize(width, height);
}

void RenderingEngine::ApplyOrtho(float maxX, float maxY) const
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

void RenderingEngine::Render() const
{
    glClear(GL_COLOR_BUFFER_BIT);
    Painter p(m_simpleProgram);
    Game::getInstance().draw(p);
}

void RenderingEngine::OnFingerUp(ivec2 location){
    Game::getInstance().OnFingerUp(location);
}

void RenderingEngine::OnFingerDown(ivec2 location){
    Game::getInstance().OnFingerDown(location);
}

void RenderingEngine::OnFingerMove(ivec2 previous, ivec2 location){
    Game::getInstance().OnFingerMove(previous, location);
}

void RenderingEngine::UpdateAnimation(float timeStep)
{
     Keys keys;
     Game::getInstance().tick(keys);
}