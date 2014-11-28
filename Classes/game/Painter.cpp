#include "Painter.h"

#define _USE_MATH_DEFINES

#include "Matrix.hpp"

Painter::Painter(GLuint program) : m_simpleProgram(program) {
}

//void Painter::drawAsteroid(const Asteroid *asteroid) {
//    mat4 rotation = mat4::Rotate(asteroid->getAngle());
//    mat4 scale = mat4::Scale(1);
//    mat4 translation = mat4::Translate(asteroid->position.x, asteroid->position.y, -1);
//    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
//    mat4 modelviewMatrix = scale * rotation * translation;
//    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
//
//    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
//    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");
//
//    glEnableVertexAttribArray(positionSlot);
//    glEnableVertexAttribArray(colorSlot);
//
//    GLsizei stride = sizeof(Vertex);
//    const GLvoid *pCoords = &asteroid->body[0].Position.x;
//    const GLvoid *pColors = &asteroid->body[0].Color.x;
//    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
//    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);
//
//    glDrawArrays(GL_LINE_LOOP, 0, asteroid->body.size());
//
//    glDisableVertexAttribArray(positionSlot);
//    glDisableVertexAttribArray(colorSlot);
//}

void Painter::drawShip(const Ship *ship) {
    mat4 rotation = mat4::Rotate(ship->getAngle());
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
    const GLvoid *pCoords = &ship->body[0].Position.x;
    const GLvoid *pColors = &ship->body[0].Color.x;
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);

    glDrawArrays(GL_LINE_LOOP, 0, ship->body.size());

    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);
}

void Painter::drawGameObject(const GameObject *gameObject) {
    mat4 rotation = mat4::Rotate(gameObject->getAngle());
    mat4 scale = mat4::Scale(1);
    mat4 translation = mat4::Translate(gameObject->position.x, gameObject->position.y, -1);
    GLint modelviewUniform = glGetUniformLocation(m_simpleProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());

    GLuint positionSlot = glGetAttribLocation(m_simpleProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(m_simpleProgram, "SourceColor");

    glEnableVertexAttribArray(positionSlot);
    glEnableVertexAttribArray(colorSlot);

    GLsizei stride = sizeof(Vertex);
    const GLvoid *pCoords = &gameObject->body[0].Position.x;
    const GLvoid *pColors = &gameObject->body[0].Color.x;
    glVertexAttribPointer(positionSlot, 2, GL_FLOAT, GL_FALSE, stride, pCoords);
    glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, pColors);

    glDrawArrays(GL_LINE_LOOP, 0, gameObject->body.size());

    glDisableVertexAttribArray(positionSlot);
    glDisableVertexAttribArray(colorSlot);

}
