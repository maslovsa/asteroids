//
//  ShaderHelper.h
//  Asteroids
//
//  Created by Sergey Maslov on 27.11.14.
//
//

#ifndef __Asteroids__ShaderHelper__
#define __Asteroids__ShaderHelper__

#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>
#include <cmath>
#include <iostream>

namespace shader {
    GLuint BuildShader(const char *source, GLenum shaderType);

    GLuint BuildProgram(const char *vertexShaderSource,
                        const char *fragmentShaderSource);
}

#endif /* defined(__Asteroids__ShaderHelper__) */
