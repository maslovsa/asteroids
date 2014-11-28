#include "Painter.h"

#define _USE_MATH_DEFINES

#include "Matrix.hpp"

Painter::Painter(GLuint program) : m_simpleProgram(program) {
}

void Painter::drawAsteroid(const Asteroid *asteroid) {
//void Painter::drawAsteroid(float x, float y, float size, float angle) {
    mat4 rotation = mat4::Rotate(asteroid->getAngle());
    mat4 scale = mat4::Scale(1);
    mat4 translation = mat4::Translate(asteroid->position.x, asteroid->position.y, -1);
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());

    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");

    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);

    GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &asteroid->body[0].Position.x;
    const GLvoid *pColors = &asteroid->body[0].Color.x;
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);

    glDrawArrays(GL_LINE_LOOP, 0, asteroid->body.size());

    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
}

void Painter::drawShip(std::vector<Vertex> body, float angle, Jet state) {
    mat4 rotation = mat4::Rotate(angle);
    mat4 scale = mat4::Scale(1);
    mat4 translation = mat4::Translate(0, 0, -1);
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());

    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");

    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);

    GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &body[0].Position.x;
    const GLvoid *pColors = &body[0].Color.x;
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);

    glDrawArrays(GL_LINE_LOOP, 0, body.size());

    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
}

void Painter::drawBullet(float x, float y) {

}
