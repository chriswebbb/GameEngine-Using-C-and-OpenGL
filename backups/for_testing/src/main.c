#include "main.h"

#define WINDOWHEIGHT 1920
#define WINDOWWIDTH 1080
#define PI 3.14159265358979323846f
#define NUMOFOCTAVES 7
#define MAP_NUM_VERTICES_XAXIS 1000
#define MAP_NUM_VERTICES_ZAXIS 1000
#define RANDOM_SAMPLE 8
#define SCALE 0.002f

gameEngineState engineState = { .windowHeight = WINDOWHEIGHT, 
                                .windowWidth = WINDOWWIDTH, 
                                .toggleWireMesh = 0, 
                                .deltaTime = 0.0f};

cameraState camera = {  .yaw = -90.0f,
                        .pitch = 0.0f, 
                        .view = GLM_MAT4_IDENTITY_INIT, 
                        .eye = {0.0f, 0.0f, 3.0f},
                        .forward = {0.0f, 0.0f, -1.0f},
                        .up = {0.0f, 1.0f, 0.0f}, 
                        .FOV = 100.0f};

mouseState mouse = {
                        .lastX = WINDOWHEIGHT / 2.0,
                        .lastY = WINDOWWIDTH / 2.0,
                        .firstMouse = 1
};

Vertex axis[] ={
                        {0.0f, 0.0f, 0.0f},
                        {1.0f, 0.0f, 0.0f},
                        {0.0f, 2.0f, 0.0f}, 
                        {0.0f, 0.0f, 3.0f}
};

int axisIndices[] = {0,1,0,2,0,3};

static const Vertex vertices[] = {
    { {  0.0f,  0.0f, 0.0f }, { 1.f, 0.f, 0.f } },
    { {  1.0f,  1.0f, 0.0f }, { 0.f, 1.f, 0.f } },
    { {  1.0f,  0.0f, 0.0f }, { 0.f, 0.f, 1.f } },
    { {  0.0f,  1.0f, 0.0f }, { 0.f, 0.f, 1.f } },

    { {  0.0f,  1.0f, 1.0f }, { 1.f, 0.f, 0.f } },
    { {  1.0f,  1.0f, 1.0f }, { 0.f, 1.f, 0.f } },
    { {  0.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } },
    { {  1.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } }   
};

static const Vertex vertices_two[] = {
    { {  1.0f,  0.0f, 0.0f }, { 1.f, 0.f, 0.f } },
    { {  2.0f,  1.0f, 0.0f }, { 0.f, 1.f, 0.f } },
    { {  2.0f,  0.0f, 0.0f }, { 0.f, 0.f, 1.f } },
    { {  1.0f,  1.0f, 0.0f }, { 0.f, 0.f, 1.f } },

    { {  1.0f,  1.0f, 1.0f }, { 1.f, 0.f, 0.f } },
    { {  2.0f,  1.0f, 1.0f }, { 0.f, 1.f, 0.f } },
    { {  1.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } },
    { {  2.0f,  0.0f, 1.0f }, { 0.f, 0.f, 1.f } }   
};

//Counter-ClockWise winding
unsigned int indices[] = {  //front
                            0, 1, 2,
                            0, 3, 1,
                            //Top
                            3, 4, 5,
                            5, 1, 3,
                            //Right
                            2, 1, 5, 
                            2, 5, 7,
                            //Left
                            0, 6, 3,
                            3, 6, 4,
                            //Back
                            4, 6, 7,
                            4, 7, 5,
                            //Bottom
                            0, 2, 6,
                            6, 2, 7
};

float random[MAP_NUM_VERTICES_XAXIS];
float noise[MAP_NUM_VERTICES_XAXIS];
float random2D[MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS];
float noise2D[MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS];
Vertex meshForHeight[MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS];
unsigned int indicesForMesh[2 * ((3 * (MAP_NUM_VERTICES_XAXIS - 1) * (MAP_NUM_VERTICES_ZAXIS - 1)) + MAP_NUM_VERTICES_XAXIS + MAP_NUM_VERTICES_ZAXIS - 2)];

void updateMesh(Vertex* mesh, float* noise);
void one_dimensional_perlin_noise(float* random, float* noise, int octaves);
void two_dimensional_perlin_noise(float* random, float* noiseArray, int octave);
void init_mesh_lines(Vertex* mesh, unsigned int* indices, float* noise);
void shader_error(GLuint shader);
static void error_callback(int error, const char* description);
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processMovementInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
GLFWwindow* create_window(int width, int height, char* name);

int main(void)
{
    if(CGLM_CONFIG_CLIP_CONTROL == CGLM_CLIP_CONTROL_LH_NO)
    {
        printf("\n\n\nYEEEEEET\n\n\n");
    }

    GLFWwindow* window = create_window(1920, 1080, "OpenGL Game Engine");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); //Hides the cursor and forces it into the centre of the window

    int multiple_cubs = 0;

    glm_look(camera.eye, camera.forward, camera.up, camera.view);

    printf("\n\n%i", &meshForHeight[0]);
    
    //one_dimensional_perlin_noise(&random, &noise, 2);
    
    two_dimensional_perlin_noise(&random2D, &noise2D, NUMOFOCTAVES);

    init_mesh_lines(&meshForHeight, &indicesForMesh, &noise2D);

    int yeet = 0;
    // for(int j = 0; j < MAP_NUM_VERTICES_ZAXIS * MAP_NUM_VERTICES_XAXIS;  j++)
    // {
    //     printf("\nindex -> %i   z -> %.2f   x -> %.2f", j, meshForHeight[j].pos[2], meshForHeight[j].pos[0]);
    // }

    // printf("\n");

    // for(int w = 0; w < 2 * ((3 * (MAP_NUM_VERTICES_XAXIS - 1) * (MAP_NUM_VERTICES_ZAXIS - 1)) + MAP_NUM_VERTICES_XAXIS + MAP_NUM_VERTICES_ZAXIS - 2); w++)
    // {
    //     printf("_%i_", indicesForMesh[w]);
    // }

    

    // printf("\n\n");
    // for(int z = 0; z < MAP_NUM_VERTICES_ZAXIS; z++){
    //     for(int x = 0; x < MAP_NUM_VERTICES_ZAXIS; x++)
    //     {
    //         int index = z * MAP_NUM_VERTICES_XAXIS + x;
    //         printf(" %.3f", noise2D[index]);
    //     }
    //     printf("\n");
    // }

    ////////////////////////////////////////////////////////////////////////////////////////
    //Shaders
    ////////////////////////////////////////////////////////////////////////////////////////

    shaderProgram shader = shader_gen("shader.vs", "shader.fs");

    //Second Shader construction.

    shaderProgram shaderTwo = shader_gen("shader.vs", "shader.fs");

    //Now the shaders have been put into the program object and linked we can delete the original shader objects.
    glDeleteShader(shader.vertexSHID);
    glDeleteShader(shader.fragmentSHID);
    glDeleteShader(shaderTwo.vertexSHID);
    glDeleteShader(shaderTwo.fragmentSHID);

    ////////////////////////////////////////////////////////////////////////////////////////
    //Creating and initializing VBO ( Vertex Buffer Object )
    ////////////////////////////////////////////////////////////////////////////////////////
                                
    BUFF vbo = buff_create(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(vbo, &vertices, sizeof(vertices));

    ////////////////////////////////////////////////////////////////////////////////////////
    //How to interpret the data passed to the GPU via VAO ( Vertex Array Object )
    ////////////////////////////////////////////////////////////////////////////////////////

    GLuint mvp_location = glGetUniformLocation(shader.programID, "MVP");        //Returns the location of a uniform variable
    GLuint vpos_location = glGetAttribLocation(shader.programID, "vPos");
    GLuint vcol_location = glGetAttribLocation(shader.programID, "vCol");
    GLuint u_time_location = glGetUniformLocation(shader.programID, "u_time");

    GLuint vao = vao_create();
    vao_bind(vao);

    //vao_attribute(vao, vbo, vcol_location, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, norm));
    vao_attribute(vao, vbo, vpos_location, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));

    ////////////////////////////////////////////////////////////////////////////////////////
    //Using EBO ( Element Buffer Object ) to draw with indices
    ////////////////////////////////////////////////////////////////////////////////////////

    BUFF ebo = buff_create(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(ebo, &indices, sizeof(indices));

    ////////////////////////////////////////////////////////////////////////////////////////
    //Creating a second cube that uses a seperate vertex array object
    ////////////////////////////////////////////////////////////////////////////////////////

    const GLint mvp_location_two = glGetUniformLocation(shaderTwo.programID, "MVP");        //Returns the location of a uniform variable
    const GLint vpos_location_two = glGetAttribLocation(shaderTwo.programID, "vPos");
    const GLint vcol_location_two = glGetAttribLocation(shaderTwo.programID, "vCol");
    const GLint u_time_location_two = glGetUniformLocation(shaderTwo.programID, "u_time");

    //1. Generate and bind vertex buffer object and copy the vertex data into the buffer
    BUFF vboTwo = buff_create(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(vboTwo, &vertices_two, sizeof(vertices));

    //2. Generate and bind vertex array
    GLuint vaoTwo = vao_create();
    vao_bind(vaoTwo);

    //vao_attribute(vaoTwo, vboTwo, vcol_location_two, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, norm));
    vao_attribute(vaoTwo, vboTwo, vpos_location_two, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));

    //3. Generate and bind the element buffer object and then populate the buffer
    BUFF eboTwo = buff_create(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(eboTwo, &indices, sizeof(indices));

    ////////////////////////////////////////////////////////////////////////////////////////
    //Mesh generation
    //////////////////////////////////////////////////////////////////////////////////////// 

    const GLint mvp_location_three = glGetUniformLocation(shaderTwo.programID, "MVP");        //Returns the location of a uniform variable
    const GLint vpos_location_three = glGetAttribLocation(shaderTwo.programID, "vPos");
    const GLint vcol_location_three = glGetAttribLocation(shaderTwo.programID, "vCol");
    const GLint u_time_location_three = glGetUniformLocation(shaderTwo.programID, "u_time");

    //1. Generate and bind vertex buffer object and copy the vertex data into the buffer
    BUFF vboThree = buff_create(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(vboThree, meshForHeight, sizeof(meshForHeight));

    //2. Generate and bind vertex array
    GLuint vaoThree = vao_create();
    vao_bind(vaoThree);

    //vao_attribute(vaoThree, vboThree, vcol_location_three, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, norm));
    vao_attribute(vaoThree, vboThree, vpos_location_three, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));

    //3. Generate and bind the element buffer object and then populate the buffer
    BUFF eboThree = buff_create(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(eboThree, indicesForMesh, sizeof(indicesForMesh));

    ////////////////////////////////////////////////////////////////////////////////////////
    //Axis Generation
    ////////////////////////////////////////////////////////////////////////////////////Four

    const GLint mvp_location_Four = glGetUniformLocation(shaderTwo.programID, "MVP");        //Returns the location of a uniform variable
    const GLint vpos_location_Four = glGetAttribLocation(shaderTwo.programID, "vPos");
    const GLint vcol_location_Four = glGetAttribLocation(shaderTwo.programID, "vCol");
    const GLint u_time_location_Four = glGetUniformLocation(shaderTwo.programID, "u_time");

    //1. Generate and bind vertex buffer object and copy the vertex data into the buffer
    BUFF vboFour = buff_create(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(vboFour, &axis, sizeof(vertices));

    //2. Generate and bind vertex array
    GLuint vaoFour = vao_create();
    vao_bind(vaoFour);

    //vao_attribute(vaoFour, vboFour, vcol_location_Four, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, norm));
    vao_attribute(vaoFour, vboFour, vpos_location_Four, 3, GL_FLOAT, sizeof(Vertex), (void*) offsetof(Vertex, pos));

    //3. Generate and bind the element buffer object and then populate the buffer
    BUFF eboFour = buff_create(GL_ELEMENT_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
    buff_BindNData(eboFour, &axisIndices, sizeof(indicesForMesh));


    ////////////////////////////////////////////////////////////////////////////////////////
    //Z-Buffer and culling
    //////////////////////////////////////////////////////////////////////////////////////// 

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);   
    glFrontFace(GL_CCW);  

    ////////////////////////////////////////////////////////////////////////////////////////
    //Game loop
    //////////////////////////////////////////////////////////////////////////////////////// 

    int width, height;

    float u_time = glfwGetTime();   //Gets the time for the shader file
    float currentFrame;             //Holds the value for current frame 
    float lastFrame;                //Holds the previous frames start time                

    //The ratio of screen width to heigh for projection matrix.
    float ratio = width / (float) height;

    while (!glfwWindowShouldClose(window))  //Checks if the window is meant to close
    {   

        if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
        {
            two_dimensional_perlin_noise(&random2D, &noise2D, NUMOFOCTAVES);
            update_line_mesh(&meshForHeight, &noise2D);
            buff_bind(vboThree);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS, &meshForHeight);
        }

        currentFrame = glfwGetTime();           //Set the time equal to the current frame variable 
        engineState.deltaTime = currentFrame - lastFrame;   //Delta time
        lastFrame = currentFrame;

        u_time = glfwGetTime();
        
        processMovementInput(window);
        
        // glm_look(eye, forward, up, view);                       //Generate the updated view matrix
        glm_look(camera.eye, camera.forward, camera.up, &camera.view);

        //Retrieves the window dimensions and then alters the width and height variables so that the game engine gets the correct values.
        glfwGetFramebufferSize(window, &engineState.windowWidth, &engineState.windowHeight);
        
        //The ratio of screen width to heigh for projection matrix.
        ratio = (float)engineState.windowWidth / (float) engineState.windowHeight;

        //This tells OpenGL the size of the window so it can adjust the data accordingly to render to the screen.
        //Essentially it converts the 2D projection space generated into the normalised screen space.
        //The first two arguments are the bottom left coordinates, the third and four coordinates are for the top right.
        glViewport(0, 0, engineState.windowWidth, engineState.windowHeight);
        //This clears the colour buffer               
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mat4x4 m, p, mvp;
        mat4x4_identity(m);
        //mat4x4_translate(m, -0.5, -0.5, 0.0);
        //mat4x4_rotate_X(m, m, glfwGetTime()*0.75);
        //mat4x4_rotate_Y(m, m, glfwGetTime()*0.25);
        //mat4x4_ortho(p, -ratio, ratio, -1.f, 1.f, 10.f, -10.f);
        // // // glm_perspective((camera.FOV*PI)/180, ratio, 0.01f, 100.0f, p);
        // // // mat4x4_mul(mvp, camera.view, m);   //Does M*V
        // // // mat4x4_mul(mvp, p, mvp);    //Then does (M*V)*P for the final transformation matrix

        // // // glUseProgram(shader.programID);
        // // // glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        // // // glUniform1f(u_time_location, u_time);
        //glBindVertexArray(vao);    //Binds the vertex array object declared above to t
        //glDrawArrays(GL_TRIANGLES, 0, 6);   //Draws the triangles specified by the vertex array object
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glBindVertexArray(vaoFour);
        glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, 0);

        mat4x4_identity(m);
        //mat4x4_translate(m, 3.0, 0.0, 0.0);
        //mat4x4_rotate_X(m, m, glfwGetTime()*1.5);
        glm_perspective((camera.FOV*PI)/180, ratio, 0.01f, 100.0f, p);
        mat4x4_mul(mvp, camera.view, m);
        mat4x4_mul(mvp, p, mvp);

        glUseProgram(shaderTwo.programID);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) &mvp);
        glUniform1f(u_time_location, u_time);
        //glBindVertexArray(vaoTwo);
        //glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glUniform1f(u_time_location, u_time);
        glBindVertexArray(vaoThree);
        glDrawElements(GL_LINES, 2 * ((3 * (MAP_NUM_VERTICES_XAXIS - 1) * (MAP_NUM_VERTICES_ZAXIS - 1)) + MAP_NUM_VERTICES_XAXIS + MAP_NUM_VERTICES_ZAXIS - 2), GL_UNSIGNED_INT,0);
    
        if(engineState.toggleWireMesh)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }else{
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        //printf("\n%.3f ms => %.3f fps", engineState.deltaTime*1000, 1/engineState.deltaTime);

        glfwSwapBuffers(window);    //Swaps the back and front buffers, ensures that the amount of time specified in the interval has been met first before the change. 
        glfwPollEvents();           //Checks if any events have been triggered and then updates the windows state accordingly.

    }

    glDeleteVertexArrays(1, vao);
    glDeleteBuffers(1, vbo.buffID);
    glDeleteVertexArrays(1, vaoTwo);
    glDeleteBuffers(1, vboTwo.buffID);
    glDeleteProgram(shader.programID);
    glDeleteProgram(shaderTwo.programID); 

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}

void one_dimensional_perlin_noise(float* random, float* noiseArray, int octaves)
{
    for(int index = 0; index < MAP_NUM_VERTICES_XAXIS; index++) 
    {
        random[index] = (float)rand()/(float)RAND_MAX; 
    }

    for(int x = 0; x < MAP_NUM_VERTICES_XAXIS; x++) 
    {   
        float noise = 0;                                    //Variable used to hold accumulated value.
        float scale = 0.5f;
        float scaleAcc = 0.0f;

        for(int o = 0; o < octaves;  o++)
        {
            int period = MAP_NUM_VERTICES_XAXIS >> o;
            int sample1 = (x / period) * period;
            int sample2 = (sample1 + period) % MAP_NUM_VERTICES_XAXIS;

            float fBlend = (float)(x-sample1) / (float)period;
            float y = (1.0f - fBlend) * random[sample1] + fBlend * random[sample2];

            noise += y * scale;
            scaleAcc += scale;
            scale = scale / 2.0f;
        }
        noiseArray[x] = noise / scaleAcc;
        //printf("\n%.3f", noiseArray[x]);
    }
}

void two_dimensional_perlin_noise(float* random, float* noiseArray, int octave)
{
    for(int index = 0; index < MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS; index++) 
    {
        random[index] = (float)rand()/(float)RAND_MAX; 
    }

    for(int z = 0; z < MAP_NUM_VERTICES_XAXIS; z++){
        for(int x = 0; x < MAP_NUM_VERTICES_ZAXIS; x++) 
        {   
            float noise = 0;                                    //Variable used to hold accumulated value.
            float scale = 1.0f;
            float scaleAcc = 0.0f;

            for(int o = 0; o < octave;  o++)
            {
                int period = MAP_NUM_VERTICES_XAXIS >> o;
                int sampleX1 = (x / period) * period;
                int sampleZ1 = (z / period) * period;
                int sampleX2 = (sampleX1 + period) % MAP_NUM_VERTICES_XAXIS;
                int sampleZ2 = (sampleZ1 + period) % MAP_NUM_VERTICES_XAXIS;

                float blendX = (float)(x-sampleX1) / (float)period;
                float blendY = (float)(z-sampleZ1) / (float)period;
                float yT = (1.0f - blendX) * random[sampleZ1 * MAP_NUM_VERTICES_XAXIS + sampleX1] + blendX * random[sampleZ1 * MAP_NUM_VERTICES_XAXIS + sampleX2];
                float yB = (1.0f - blendX) * random[sampleZ2 * MAP_NUM_VERTICES_XAXIS + sampleX1] + blendX * random[sampleZ2 * MAP_NUM_VERTICES_XAXIS + sampleX2];
                
                noise += (blendY * (yB-yT) + yT) * scale;
                scaleAcc += scale;
                scale = scale / 2.0f;
            }
            noiseArray[z * MAP_NUM_VERTICES_XAXIS + x] = noise / scaleAcc;
            //printf("\n%.3f", noiseArray[x]);
        }
    }

}

void init_mesh_lines(Vertex* mesh, unsigned int* indices, float* noise)
{   
    printf("\n\n%i\n\n", &mesh[0]);
    int index = 0;
    //Initialise the mesh
    for(int k = 0; k < MAP_NUM_VERTICES_ZAXIS; k++)
    {
        for(int i = 0; i < MAP_NUM_VERTICES_XAXIS;  i++)
        {
            index = k * MAP_NUM_VERTICES_XAXIS + i;

            mesh[index].pos[0] = SCALE * (float)i;//0.5f * (float)(i - (int)(MAP_NUM_VERTICES_XAXIS/2));
            //printf("%.2f", mesh[index].pos[0]);
            mesh[index].pos[1] = 0.0f;
            mesh[index].pos[2] = SCALE * (float)k;
        }
    }

    index = 0;
    // //Initialise indices

    for (int i = 0 ; i < MAP_NUM_VERTICES_ZAXIS - 1 ; i++)
    {
        indices[index++] = (i + 1) * MAP_NUM_VERTICES_XAXIS - 1;
        //printf("%i", i);
        indices[index++] = (i + 2) * MAP_NUM_VERTICES_XAXIS - 1;
    }

    for (int i = 0 ; i < MAP_NUM_VERTICES_XAXIS - 1 ; ++i)
    {
        indices[index++] = MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS - 1 - i;
        indices[index++] = MAP_NUM_VERTICES_XAXIS * MAP_NUM_VERTICES_ZAXIS - i - 2;
    }

    for(int k = 0; k < (MAP_NUM_VERTICES_ZAXIS - 1);  k++)
    {
        for(int i = 0; i < (MAP_NUM_VERTICES_XAXIS - 1);  i++)
        {
            //Horizontal lines
            indices[index++] = k * MAP_NUM_VERTICES_XAXIS + i;
            //printf("\n\n%i\n\n", indices[index - 1]);
            indices[index++] = k * MAP_NUM_VERTICES_XAXIS + i + 1;

            //Vertical lines
            indices[index++] = k * MAP_NUM_VERTICES_XAXIS + i;
            indices[index++] = k * MAP_NUM_VERTICES_XAXIS + i + MAP_NUM_VERTICES_XAXIS;


            indices[index++] = k * MAP_NUM_VERTICES_XAXIS + i;
            indices[index++] = k * MAP_NUM_VERTICES_XAXIS + i + MAP_NUM_VERTICES_XAXIS + 1;
        }
    }

    index = 0;

    for(int k = 0; k < MAP_NUM_VERTICES_ZAXIS; k++)
    {
        for(int i = 0; i < MAP_NUM_VERTICES_XAXIS;  i++)
        {
            index = k * MAP_NUM_VERTICES_XAXIS + i;

            mesh[index].pos[1] = 2.0f * noise[index];
            
        }
    }

    printf("Error checking");

}

void update_line_mesh(Vertex* mesh, float* noise)
{
    int index = 0;

    for(int k = 0; k < MAP_NUM_VERTICES_ZAXIS; k++)
    {
        for(int i = 0; i < MAP_NUM_VERTICES_XAXIS;  i++)
        {
            index = k * MAP_NUM_VERTICES_XAXIS + i;

            mesh[index].pos[1] = 2.0f * noise[index];
        }
    }
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
    if (glfwGetKey(window, GLFW_KEY_F3) == GLFW_PRESS)
    {
        if(engineState.toggleWireMesh){
            engineState.toggleWireMesh = 0;
        }else if(!engineState.toggleWireMesh ){
            engineState.toggleWireMesh = 1;
        }
    }
}

void processMovementInput(GLFWwindow* window)
{
            // processInput(window, &eye, &forward, &up, 0.1f);
    vec3 result;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)   //Checks for W press, multiplies the forward vector generated 
    {
        glm_vec3_scale(camera.forward, 1.5f * engineState.deltaTime, result);
        glm_vec3_add(camera.eye, result, camera.eye);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        glm_vec3_scale(camera.forward, 1.5f * engineState.deltaTime, result);
        glm_vec3_sub(camera.eye, result, camera.eye);
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)    //Rotates the forward vector in the y-axis and then normalises it.
    {
        glm_vec3_rotate(camera.forward, -(45*PI*engineState.deltaTime)/180, (vec3){0.0f, 1.0f, 0.0f});
        glm_vec3_normalize(camera.forward);
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        glm_vec3_rotate(camera.forward, (45*PI*engineState.deltaTime)/180, (vec3){0.0f, 1.0f, 0.0f});
        glm_vec3_normalize(camera.forward);
    }

    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)       //Same as W but for vertical movement instead.
    {
        glm_vec3_scale(camera.up, 1.5f * engineState.deltaTime, result);
        glm_vec3_add(camera.eye, result, camera.eye);
    }

    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        glm_vec3_scale(camera.up, 1.5f * engineState.deltaTime, result);
        glm_vec3_sub(camera.eye, result, camera.eye);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)       //Takes a forward vector and the up vector and cross product them to get the new right 
    {                                                       //vector and then do the same as the rest.
        glm_cross(camera.forward, camera.up, result);
        glm_normalize(result);
        glm_vec3_scale(result, 1.5f * engineState.deltaTime, result);
        glm_vec3_sub(camera.eye, result, camera.eye);
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        glm_cross(camera.forward, camera.up, result);
        glm_normalize(result);
        glm_vec3_scale(result, 1.5f * engineState.deltaTime, result);
        glm_vec3_add(camera.eye, result, camera.eye);
    }
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (mouse.firstMouse)
    {
        mouse.lastY = ypos;
        mouse.lastX = xpos;
        mouse.firstMouse = 0;
    }

    float xoffset = xpos - mouse.lastX;
    float yoffset = mouse.lastY - ypos; // reversed since y-coordinates go from bottom to top
    mouse.lastX = xpos;
    mouse.lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    camera.yaw += xoffset;
    camera.pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (camera.pitch > 89.0f)
        camera.pitch = 89.0f;
    if (camera.pitch < -89.0f)
        camera.pitch = -89.0f;

    camera.forward[0] = cos((3.14159265358979323846*camera.yaw)/180) * cos((3.14159265358979323846*camera.pitch)/180);
    camera.forward[1] = sin((3.14159265358979323846*camera.pitch)/180);
    camera.forward[2] = sin((3.14159265358979323846*camera.yaw)/180) * cos((3.14159265358979323846*camera.pitch)/180);
    glm_normalize(camera.forward);
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