#include "vao.h"

GLuint vao_create()
{
    GLuint vaoID;
    glGenVertexArrays(1, &vaoID);
    return vaoID;
}

void vao_bind(GLuint vao)
{
    glBindVertexArray(vao);
}

void vao_attribute(GLuint vao, BUFF vbo, GLuint attribID, GLint numOfVerts, GLenum dataType, GLsizei stride, size_t offset)
{
    vao_bind(vao);

    glVertexAttribPointer(attribID, numOfVerts, dataType, GL_FALSE, stride, (void*)offset);
    glEnableVertexAttribArray(attribID);
}