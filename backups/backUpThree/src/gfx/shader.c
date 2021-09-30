#include "shader.h"

GLuint loadAndCompileShader(char* name, GLenum type)
{
    FILE *f;
    char* text;
    int lengthOfFile;

    f = fopen(name, "rb");
    if(f == NULL)
    {
        fprintf(stderr, "\nError: File (%s) couldn't be found \n", name);
        exit(-1);
    }

    fseek(f, 0, SEEK_END);                              //Sets the pointer to the end of the file.
    lengthOfFile = ftell(f);                            //Using the pointer it will view the size of the file.
    fseek(f, 0, SEEK_SET);                              //Set the pointer back to the beginning.
    text = calloc(1, lengthOfFile);                     //Allocate contiguous memory for a single string of size lengthOfFile.
    fread(text, 1, lengthOfFile, f);                    //Read the file into the memory associated with text.
    if(strlen(text) == 0)exit(-2);
    fclose(f);                                          //Close the file.

    GLuint shaderID = glCreateShader(type);             //Generate an ID for the shader, specifying the type of shader and then assign it to the ID holder.
    glShaderSource(shaderID, 1, &text, &lengthOfFile);  //Attach the shader created using the ID. First argument is ID, second is the number of strings, third is the source code and the fourth is array of string lengths.
    glCompileShader(shaderID);                          //Compile the shader.

    free(text);                                         //Free the contiguous memory generated.
    return shaderID;                                    //Return the shaders ID.
}

shaderProgram shader_gen(char* vs_location, char* fs_location)
{
    shaderProgram shader;

    shader.programID = glCreateProgram();                                           //Generate an ID for the program and then assign it to the ID holder.
    shader.vertexSHID = loadAndCompileShader(vs_location, GL_VERTEX_SHADER);        //Generate the vertex shader and assign to the shader program struct.
    shader.fragmentSHID = loadAndCompileShader(fs_location, GL_FRAGMENT_SHADER);    //Generate the fragment shader and assign to the shader program struct.
    glAttachShader(shader.programID, shader.vertexSHID);                            //Attach the vertex shader object to the program object.
    glAttachShader(shader.programID, shader.fragmentSHID);                          //Attach the fragment shader object to the program object.
    glLinkProgram(shader.programID);                                                //Link the programs inputs and outputs together.

    return shader;                                                                  //Return the shader program struct.
}

void shader_bind(shaderProgram shader) {
    glUseProgram(shader.programID);
}