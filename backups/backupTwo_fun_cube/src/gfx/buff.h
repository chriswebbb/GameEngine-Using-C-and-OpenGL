#ifndef BUFF_H
#define BUFF_H

#include <utils.h>
#include <gfx.h>

typedef struct BUFF 
{
    GLuint buffID;
    GLint bufferType;
    GLenum manageType;
}BUFF;

BUFF buff_create(GLuint bufferType, GLenum manageType);
void buff_destroy(BUFF buff);
void buff_bind(BUFF buff);
void buff_BindNData(BUFF buff, void * data, size_t stride);

#endif