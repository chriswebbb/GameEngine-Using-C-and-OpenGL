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

    fseek(f, 0, SEEK_END);                  //sets the pointer to the end of the file
    lengthOfFile = ftell(f);                //using the pointer it will view the size of the file
    fseek(f, 0, SEEK_SET);                  //set the pointer back to the beginning
    text = calloc(1, lengthOfFile);         //allocate contiguous memory for a single string of size lengthOfFile
    fread(text, 1, lengthOfFile, f);        //read the file into the memory associated with text
    if(strlen(text) == 0)exit(-2);
    fclose(f);                              //close the file

    GLuint shaderID = glCreateShader(type);
    glShaderSource(shaderID, 1, &text, &lengthOfFile);
    glCompileShader(shaderID);

    free(text);
    return shaderID;
}

shaderProgram shader_gen(char* vs_location, char* fs_location)
{
    shaderProgram shader;

    shader.programID = glCreateProgram();
    shader.vertexSHID = loadAndCompileShader(vs_location, GL_VERTEX_SHADER);
    shader.fragmentSHID = loadAndCompileShader(fs_location, GL_FRAGMENT_SHADER);
    glAttachShader(shader.programID, shader.vertexSHID);
    glAttachShader(shader.programID, shader.fragmentSHID);
    glLinkProgram(shader.programID);

    return shader;
}

void shader_bind(shaderProgram shader) {
    glUseProgram(shader.programID);
}