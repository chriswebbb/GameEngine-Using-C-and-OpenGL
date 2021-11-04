#ifndef VAO_H
#define VAO_H

#include <utils.h>
#include <gfx.h>
#include "buff.h"

GLuint vao_create();
void vao_bind(GLuint vao);
void vao_attribute(GLuint vao, BUFF vbo, GLuint attribID, GLint numOfVerts, GLenum dataType, GLsizei stride, size_t offset);

#endif