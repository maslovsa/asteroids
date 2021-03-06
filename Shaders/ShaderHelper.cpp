//
//  ShaderHelper.cpp
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#include "ShaderHelper.h"

namespace shader {

    GLuint BuildShader(const char *source, GLenum shaderType) {
        GLuint shaderHandle = glCreateShader(shaderType);
        glShaderSource(shaderHandle, 1, &source, 0);
        glCompileShader(shaderHandle);

        GLint compileSuccess;
        glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);

        if (compileSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
            std::cout << messages;
            exit(1);
        }

        return shaderHandle;
    }

    GLuint BuildProgram(const char *vertexShaderSource,
                        const char *fragmentShaderSource) {
        GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
        GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

        GLuint programHandle = glCreateProgram();
        glAttachShader(programHandle, vertexShader);
        glAttachShader(programHandle, fragmentShader);
        glLinkProgram(programHandle);

        GLint linkSuccess;
        glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
        if (linkSuccess == GL_FALSE) {
            GLchar messages[256];
            glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
            std::cout << messages;
            exit(1);
        }

        return programHandle;
    }
}
