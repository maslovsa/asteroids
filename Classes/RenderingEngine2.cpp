#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>
#include "IRenderingEngine.hpp"
#include "Matrix.hpp"
#define STRINGIFY(A)  #A
#include "../Shaders/Simple.vert"
#include "../Shaders/Simple.frag"
#include "ShaderHelper.h"

class RenderingEngine2 : public IRenderingEngine {
public:
    RenderingEngine2();
    void Initialize(int width, int height);
    void Render() const;
    void UpdateAnimation(float timeStep);
    void OnFingerUp(ivec2 location);
    void OnFingerDown(ivec2 location);
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation);
private:
    void ApplyOrtho(float maxX, float maxY) const;
    float m_desiredAngle;
    //float m_currentAngle;
    GLuint m_simpleProgram;
    GLuint m_framebuffer;
    GLuint m_renderbuffer;
    ivec2 m_pivotPoint;
    GLfloat m_scale;
};

IRenderingEngine* CreateRenderer2()
{
    return new RenderingEngine2();
}

struct Vertex {
    float Position[2];
    float Color[4];
};

// Define the positions and colors of two triangles.
const Vertex Vertices[] = {
    {{0, 15}, {1, 1, 0.5f, 1}},
    {{10, -7}, {1, 1, 0.5f, 1}},
    {{0, 0},  {1, 1, 0.5f, 1}},
    {{-10, -7}, {1, 1, 0.5f, 1}},
};

RenderingEngine2::RenderingEngine2()
{
    // Create & bind the color buffer so that the caller can allocate its space.
    glGenRenderbuffers(1, &m_renderbuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);
}

void RenderingEngine2::Initialize(int width, int height)
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
    
    //m_currentAngle = m_desiredAngle;
    m_scale = 3.0f;
}

void RenderingEngine2::ApplyOrtho(float maxX, float maxY) const
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

void RenderingEngine2::Render() const
{
    //glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    
    mat4 rotation = mat4::Rotate(m_desiredAngle);
    mat4 scale = mat4::Scale(m_scale);
    mat4 translation = mat4::Translate(0, 0, -1);
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation* translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
    
    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");
    
    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);
    
    GLsizei stride = sizeof(Vertex);
    const GLvoid* pCoords = &Vertices[0].Position[0];
    const GLvoid* pColors = &Vertices[0].Color[0];
   
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);
    
    GLsizei vertexCount = sizeof(Vertices) / sizeof(Vertex);
    glDrawArrays(GL_LINE_LOOP, 0, vertexCount);
    
    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
}

void RenderingEngine2::OnFingerUp(ivec2 location)
{
    //m_scale = 1.0f;
}

void RenderingEngine2::OnFingerDown(ivec2 location)
{
    //m_scale = 1.5f;
    //OnFingerMove(location, location);
    //std::cout << "shot at " << location.x << " " << location.y;
}

void RenderingEngine2::OnFingerMove(ivec2 previous, ivec2 location)
{
    vec2 direction = vec2(location - m_pivotPoint).Normalized();
    
    // Flip the Y axis because pixel coords increase towards the bottom.
    direction.y = -direction.y;
    
    float m_rotationAngle = std::acos(direction.y) * 180.0f / 3.14159f;
    if (direction.x > 0)
        m_rotationAngle = -m_rotationAngle;
    //std::cout << "(x,y)  - angle " << direction.x << " " << direction.y <<  " angle "<< m_desiredAngle<<"\n";
    m_desiredAngle = m_rotationAngle;
}


void RenderingEngine2::UpdateAnimation(float timeStep)
{

}