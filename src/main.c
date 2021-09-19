#include "main.h"

    int firstMouse = 1;
    vec3 cameraFront;

    float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch =  0.0f;

    float lastX =  1920.0f / 2.0;
    float lastY =  1080.0 / 2.0;

typedef struct Vertex
{
    vec3 pos;
    vec3 col;
} Vertex;

static const Vertex vertices[] =
{
    { {  0.0f,  0.0f, 0.0f }, { 1.f, 0.f, 0.f } },
    { {  1.0f,  1.0f, 0.0f }, { 0.f, 1.f, 0.f } },
    { {  1.0f,  0.0f, 0.0f }, { 0.f, 0.f, 1.f } },
    { {  0.0f,  1.0f, 0.0f }, { 0.f, 0.f, 1.f } },

    { {  0.0f,  1.0f, 1.0f }, { 1.f, 0.f, 0.f } },
    { {  1.0f,  1.0f, 1.0f }, { 0.f, 1.f, 0.f } },
    { {  0.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } },
    { {  1.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } }   
    
};

static const Vertex vertices_two[] =
{
    { {  2.0f,  0.0f, 0.0f }, { 1.f, 0.f, 0.f } },
    { {  3.0f,  1.0f, 0.0f }, { 0.f, 1.f, 0.f } },
    { {  3.0f,  0.0f, 0.0f }, { 0.f, 0.f, 1.f } },
    { {  2.0f,  1.0f, 0.0f }, { 0.f, 0.f, 1.f } },

    { {  2.0f,  1.0f, 1.0f }, { 1.f, 0.f, 0.f } },
    { {  3.0f,  1.0f, 1.0f }, { 0.f, 1.f, 0.f } },
    { {  2.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } },
    { {  3.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } }   
    
};

unsigned int indices[] = {  0, 1, 2,
                            0, 3, 1,

                            3, 4, 5,
                            5, 1, 3,

                            2, 1, 5, 
                            2, 5, 7,

                            0, 3, 4,
                            0, 4, 6,

                            6, 4, 5,
                            6, 5, 7,

                            0, 6, 7,
                            0, 7, 2
};

const char* load_shader( char* pathToFile )
{
    //Gotta use file length to get the size of the text file
    //Then malloc to dynamically assign a buffer size. ( Allocate at runtime )
    FILE *fp;
    char buff[255];
    char shader[10000];

    fp = fopen(pathToFile, "r");

    fread( shader, 1, 10000, fp );
    printf("\n\n\nPrint Shader\n");
    printf("___________\n");
    printf("\n%s", shader);
    printf("\n\n\n PRINTED SHADER \n\n\n");
    fclose(fp);

    return shader;
}

void shader_error(GLuint shader)
{
    int success = 0;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("$s", infoLog);
    }else printf("\nShader compiled successfully");
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "\nError: %s", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    cameraFront[0] = cos((3.14159265358979323846*yaw)/180) * cos((3.14159265358979323846*pitch)/180);
    cameraFront[1] = sin((3.14159265358979323846*pitch)/180);
    cameraFront[2] = sin((3.14159265358979323846*yaw)/180) * cos((3.14159265358979323846*pitch)/180);
    glm_normalize(cameraFront);
}

GLFWwindow* create_window(int width, int height, char* name)
{
    if (!glfwInit())                                                        //initialise GLFW
    exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);                          //Tell GLFW which version of 4.6 works
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);          //Tell GLFW we are using the core profile

    GLFWwindow* window = glfwCreateWindow(width, height, name, NULL, NULL); //Create window object
    if (!window)
    {
        printf("\nError: Failed to generate glfw window");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);                                   //Key callback function
    glfwSetErrorCallback(error_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwMakeContextCurrent(window);                                             //Makes the window object the current context of the calling thread 
    gladLoadGL();
    //gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(0.0);                                                      //Time to wait between buffer updates
    
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    return window;
}

void processInput(GLFWwindow *window, vec3 *cameraPos, vec3 *cameraForward, vec3 *cameraUp, int deltaTime)
{
    vec3 result;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        glm_vec3_scale(cameraForward, cameraSpeed, result);
        glm_vec3_add(cameraPos, result, cameraPos);
        printf("\nRegistered W being pressed");
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm_vec3_scale(cameraForward, cameraSpeed, result);
        glm_vec3_sub(cameraPos, result, cameraPos);
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        glm_cross(cameraForward, cameraUp, result);
        glm_normalize(result);
        glm_vec3_scale(result, cameraSpeed, result);
        glm_vec3_sub(cameraPos, result, cameraPos);
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm_cross(cameraForward, cameraUp, result);
        glm_normalize(result);
        glm_vec3_scale(result, cameraSpeed, result);
        glm_vec3_add(cameraPos, result, cameraPos);
    }
}

int main(void)
{
    GLFWwindow* window = create_window(1920, 1080, "OpenGL Triangle");

    int multiple_cubs = 0;

    mat4 view = GLM_MAT4_IDENTITY_INIT;
    vec3 eye = {0.0f, 0.0f, 3.0f};
    vec3 forward = {0.0f, 0.0f, -1.0f};
    vec3 up = {0.0f, 1.0f, 0.0f};

    glm_look(eye, forward, up, view);

    ////////////////////////////////////////////////////////////////////////////////////////
    //Creating and initializing Shaders, then adding them to a program. 
    //Then linking them within the program
    ////////////////////////////////////////////////////////////////////////////////////////

    const GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);              //Generate an ID for the shader, specifying that it is a vertex shader and then assign it to the ID holder.
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);                //Attach the shader created using the ID. First argument is ID, second is the number of strings, third is the source code and the fourth is array of string lengths.
    glCompileShader(vertex_shader);                                             //Compile the shader.
    shader_error(vertex_shader);

    const GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);          //The same as vertex shader but for fragment shader instead.
    glShaderSource(fragment_shader, 1, &fragment_shader_text_three, NULL);
    glCompileShader(fragment_shader);
    shader_error(fragment_shader);

    const GLuint program = glCreateProgram();                                   //Generates a program ID and provides it to the program variables
    glAttachShader(program, vertex_shader);                                     //Attach the vertex shader object to the program object
    glAttachShader(program, fragment_shader);                                   //Attach the fragment_shader object to the program object
    glLinkProgram(program);                                                     //Links the program object specified

    //Second Shader construction.

    const GLuint fragment_shader_two = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_two, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader_two);
    shader_error(fragment_shader_two);

    const GLuint program_two = glCreateProgram();
    glAttachShader(program_two, vertex_shader);
    glAttachShader(program_two, fragment_shader_two);
    glLinkProgram(program_two);

    //Now the shaders have been put into the program object and linked we can delete the original shader objects.
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glDeleteShader(fragment_shader_two);

    ////////////////////////////////////////////////////////////////////////////////////////
    //Creating and initializing VBO ( Vertex Buffer Object )
    ////////////////////////////////////////////////////////////////////////////////////////

    GLuint vertex_buffer;                                                       //Holds the ID of the buffer containing the vertex data.
    glGenBuffers(1, &vertex_buffer);                                            //Generates a buffer object name
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);                               //Takes the buffer object name and binds it to a buffer of the type specified.
    
    //Creates and initialises a buffer objects data store within the GPU. The first argument is the type of data, second is the size of data in bytes, third is the data and 
    //the fourth specifies how to manage said data.
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);                                  

    ////////////////////////////////////////////////////////////////////////////////////////
    //How to interpret the data passed to the GPU via VAO ( Vertex Array Object )
    ////////////////////////////////////////////////////////////////////////////////////////

    const GLint mvp_location = glGetUniformLocation(program, "MVP");        //Returns the location of a uniform variable
    const GLint vpos_location = glGetAttribLocation(program, "vPos");
    const GLint vcol_location = glGetAttribLocation(program, "vCol");
    const GLint u_time_location = glGetUniformLocation(program, "u_time");

    GLuint vertex_array;                                                    //Generates an Id for the vertexArray object
    glGenVertexArrays(1, &vertex_array);                                    //Generate a vertex array object
    glBindVertexArray(vertex_array);                                        //Binds the vertex array object to the name specified
    glEnableVertexAttribArray(vpos_location);                               //Enable the generic vertex attrivute arrays
    //The first argument specifies the vertex attribute we wish to configure ( either via location = 0 or in attribute).
    //The second argument specified the size of the attribute either 2, 3, 4 as these are the vector sizes
    //The third argument specifies the data type
    //The fourth argument specifies whether or not the data needs to be normalised ( 0.0 - 1.0 )
    //The fifth argument is known as the stride and tells us the space between consecutive vertex attributes.
    //The sixth and final argument specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bount to the GL_ARRAY_BUFFER targer.
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, col));
  
    ////////////////////////////////////////////////////////////////////////////////////////
    //Using EBO ( Element Buffer Object ) to draw with indices
    //////////////////////////////////////////////////////////////////////////////////////// 

    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);


    ////////////////////////////////////////////////////////////////////////////////////////
    //Creating a second cube that uses a seperate vertex array object
    ////////////////////////////////////////////////////////////////////////////////////////

    const GLint mvp_location_two = glGetUniformLocation(program_two, "MVP");        //Returns the location of a uniform variable
    const GLint vpos_location_two = glGetAttribLocation(program_two, "vPos");
    const GLint vcol_location_two = glGetAttribLocation(program_two, "vCol");
    const GLint u_time_location_two = glGetUniformLocation(program_two, "u_time");

    //1. Generate and bind vertex buffer object and copy the vertex data into the buffer
    GLuint vertex_buffer_two;
    glGenBuffers(1, &vertex_buffer_two);                                            
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_two);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices_two, GL_DYNAMIC_DRAW);
    //2. Generate and bind vertex array
    GLuint vertex_array_two;                                                    
    glGenVertexArrays(1, &vertex_array_two);                                    
    glBindVertexArray(vertex_array_two);                                        
    glEnableVertexAttribArray(vpos_location_two);
    glVertexAttribPointer(vpos_location_two, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, pos));
    glEnableVertexAttribArray(vcol_location_two);
    glVertexAttribPointer(vcol_location_two, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, col));
    //3. Generate and bind the element buffer object and then populate the buffer
    unsigned int EBO_two;
    glGenBuffers(1, &EBO_two);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_two);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_DYNAMIC_DRAW);

    ////////////////////////////////////////////////////////////////////////////////////////
    //Z-Buffer
    //////////////////////////////////////////////////////////////////////////////////////// 

    glEnable(GL_DEPTH_TEST);

    ////////////////////////////////////////////////////////////////////////////////////////
    //Game loop
    //////////////////////////////////////////////////////////////////////////////////////// 

    int width, height;

    vec3 result;

    load_shader("shader_two.fs");

    float u_time = glfwGetTime();   //Gets the time for the shader file
    float currentFrame;             //Holds the value for current frame 
    float lastFrame;                //Holds the previous frames start time
    float deltaTime;                //Difference in time between frames

    while (!glfwWindowShouldClose(window))  //Checks if the window is meant to close
    {   
        
        currentFrame = glfwGetTime();           //Set the time equal to the current frame variable 
        deltaTime = currentFrame - lastFrame;   //Delta time
        lastFrame = currentFrame;

        u_time = glfwGetTime();

        // processInput(window, &eye, &forward, &up, 0.1f);

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   //Checks for W press, multiplies the forward vector generated 
        {
            glm_vec3_scale(cameraFront, 1.5f * deltaTime, result);
            glm_vec3_add(eye, result, eye);
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            glm_vec3_scale(cameraFront, 1.5f * deltaTime, result);
            glm_vec3_sub(eye, result, eye);
        }

        if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)    //Rotates the forward vector in the y-axis and then normalises it.
        {
            glm_vec3_rotate(forward, -(45*3.14159265358979323846*deltaTime)/180, (vec3){0.0f, 1.0f, 0.0f});
            glm_vec3_normalize(forward);
        }

        if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            glm_vec3_rotate(forward, (45*3.14159265358979323846*deltaTime)/180, (vec3){0.0f, 1.0f, 0.0f});
            glm_vec3_normalize(forward);
        }

        if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)       //Same as W but for vertical movement instead.
        {
            glm_vec3_scale(up, 1.5f * deltaTime, result);
            glm_vec3_add(eye, result, eye);
        }

        if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            glm_vec3_scale(up, 1.5f * deltaTime, result);
            glm_vec3_sub(eye, result, eye);
        }

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)       //Takes a forward vector and the up vector and cross product them to get the new right 
        {                                                       //vector and then do the same as the rest.
            glm_cross(forward, up, result);
            glm_normalize(result);
            glm_vec3_scale(result, 1.5f * deltaTime, result);
            glm_vec3_sub(eye, result, eye);
        }

        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            glm_cross(forward, up, result);
            glm_normalize(result);
            glm_vec3_scale(result, 1.5f * deltaTime, result);
            glm_vec3_add(eye, result, eye);
        }

        // glm_look(eye, forward, up, view);                       //Generate the updated view matrix
        glm_look(eye, cameraFront, up, view);

        //Retrieves the window dimensions and then alters the width and height variables so that the game engine gets the correct values.
        glfwGetFramebufferSize(window, &width, &height);
        //The ratio of screen width to heigh for projection matrix.
        const float ratio = width / (float) height;
        
        //This tells OpenGL the size of the window so it can adjust the data accordingly to render to the screen.
        //Essentially it converts the 2D projection space generated into the normalised screen space.
        //The first two arguments are the bottom left coordinates, the third and four coordinates are for the top right.
        glViewport(0, 0, width, height);
        //This clears the colour buffer               
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        mat4x4_translate(m, -0.5, -0.5, 0.0);
        //mat4x4_rotate_X(m, m, glfwGetTime()*0.75);
        mat4x4_rotate_Y(m, m, glfwGetTime()*0.25);
        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 10.f, -10.f);
        //mat4x4_perspective(p, (50*3.14159265358979323846)/180, ratio, 0.1f, 100.0f);
        glm_perspective((60*3.14159265358979323846)/180, ratio, 0.5f, 100.f, p);
        mat4x4_mul(mvp, view, m);   //Does M*V
        mat4x4_mul(mvp, p, mvp);    //Then does (M*V)*P for the final transformation matrix

        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glUniform1f(u_time_location, u_time);
        glBindVertexArray(vertex_array);    //Binds the vertex array object declared above to t
        //glDrawArrays(GL_TRIANGLES, 0, 6);   //Draws the triangles specified by the vertex array object
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        mat4x4_identity(m);
        //mat4x4_translate(m, 0.0, 0.0, 10.0);
        //mat4x4_rotate_X(m, m, glfwGetTime()*1.5);
        glm_perspective((60*3.14159265358979323846)/180, ratio, 0.5f, 100.0f, p);
        mat4x4_mul(mvp, view, m);
        mat4x4_mul(mvp, p, mvp);

        glUseProgram(program_two);
        glUniformMatrix4fv(mvp_location_two, 1, GL_FALSE, (const GLfloat*) &mvp);
        glUniform1f(u_time_location_two, u_time);
        glBindVertexArray(vertex_array_two);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        glfwSwapBuffers(window);    //Swaps the back and front buffers, ensures that the amount of time specified in the interval has been met first before the change. 
        glfwPollEvents();           //Checks if any events have been triggered and then updates the windows state accordingly.
    }

    glDeleteVertexArrays(1, vertex_array);
    glDeleteBuffers(1, vertex_buffer);
    glDeleteVertexArrays(1, vertex_array_two);
    glDeleteBuffers(1, vertex_buffer_two);
    glDeleteProgram(program);
    glDeleteProgram(program_two); 

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}




//! [code]
