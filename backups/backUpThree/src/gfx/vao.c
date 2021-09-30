#include "vao.h"
#include "buff.h"

////////////////////////////////////////////////////////////////////////////////////////
//How to interpret the data passed to the GPU via VAO ( Vertex Array Object )
////////////////////////////////////////////////////////////////////////////////////////

GLuint vao_create()
{
    GLuint vaoID;                   //Varibale used to hold an Id for the vertex array object.
    glGenVertexArrays(1, &vaoID);   //Generates a buffer object name and assigns it to the variable given.
    return vaoID;                   //Return the ID name.
}

void vao_bind(GLuint vao)
{
    glBindVertexArray(vao);         //Takes the vertex array object name and binds it to vertex array object.
}

void vao_attribute(GLuint vao, BUFF buff, GLuint attribID, GLint numOfVerts, GLenum dataType, GLsizei stride, size_t offset)
{
    vao_bind(vao);                                                                          //Binds VAO
    buff_bind(buff);                                                                        //Binds the BUFFER (probs vbo)

    glVertexAttribPointer(attribID, numOfVerts, dataType, GL_FALSE, stride, (void*)offset);
    //Specifies the location and data format of the array of generic vertex attributes. 
    //The first argument specifies the index of the vertex attribute we wish to configure ( either via location = 0 or in attribute).
    //The second argument specified the size of the attribute either 2, 3, 4 as these are the vector sizes.
    //The third argument specifies the data type.
    //The fourth argument specifies whether or not the data needs to be normalised ( 0.0 - 1.0 )
    //The fifth argument is known as the stride and tells us the space between consecutive vertex attributes.
    //The sixth and final argument specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bount to the GL_ARRAY_BUFFER targer.
    
    glEnableVertexAttribArray(attribID);                                                    //Enable the generic vertex attribute arrays.
}