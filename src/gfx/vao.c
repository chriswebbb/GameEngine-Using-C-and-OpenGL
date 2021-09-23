#include "vao.h"

GLuint vao_create()
{
    GLuint handle;
    glGenVertexArrays(1, &handle);
    return handle;
}

void vao_bind(GLuint vao)
{
    glBindVertexArray(vao);
}

void vao_attribute(GLuint vao, GLuint vbo, GLuint index, GLint size, GLenum type, GLsizei stride, size_t offset)
{
    
}