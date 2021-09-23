#include "buff.h"

BUFF buff_create(GLuint typeOfBuff, GLenum usage)
{
    BUFF buff = {
        .bufferType = typeOfBuff,
        .manageType = usage
    };
    glGenBuffers(1, &buff.buffID);
    return buff;
}

void buff_destroy(BUFF buff)
{
    glDeleteBuffers(1, & buff.buffID);
}

void buff_bind(BUFF buff){
    glBindBuffer(buff.bufferType, buff.buffID);
}

void buff_BindNData(BUFF buff, void * data, size_t stride){
    buff_bind(buff);
    glBufferData(buff.bufferType, stride, data, buff.manageType);
}