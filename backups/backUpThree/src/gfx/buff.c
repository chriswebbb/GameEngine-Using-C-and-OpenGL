#include "buff.h"

BUFF buff_create(GLuint typeOfBuff, GLenum usage)
{
    //Generate a buffer struct object
    BUFF buff = {
        .bufferType = typeOfBuff,
        .manageType = usage
    };
    glGenBuffers(1, &buff.buffID);  //Generates a buffer object name.
    return buff;
}

void buff_destroy(BUFF buff)
{
    glDeleteBuffers(1, & buff.buffID);  //Delete the buffer with given ID
}

void buff_bind(BUFF buff){
    glBindBuffer(buff.bufferType, buff.buffID); //Takes the buffer object name and binds it to a buffer of the type specified.
}

void buff_BindNData(BUFF buff, void * data, size_t stride){
    buff_bind(buff);

    //Creates and initialises a buffer objects data store within the GPU. 
    //The first argument is the type of data. 
    //Second is the size of data in bytes. 
    //Third is the data. 
    //Fourth specifies how to manage said data.
    glBufferData(buff.bufferType, stride, data, buff.manageType);
}