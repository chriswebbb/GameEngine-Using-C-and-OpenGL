#ifndef SHADER_H
#define SHADER_H

#include "gfx.h"
#include "utils.h"

typedef struct shaderProgram{
    GLuint programID;
    GLuint vertexSHID;
    GLuint fragmentSHID;
    GLuint geoSHID;
}shaderProgram;

GLuint loadAndCompileShader(char* name, GLenum type);
shaderProgram shader_gen(char* vs_location, char* fs_location);
void shader_bind(shaderProgram shader);

#endif