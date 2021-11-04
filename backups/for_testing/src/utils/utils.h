#ifndef UTILS_H
#define UTILS_H

//By defining STB_IMAGE_IMPLEMENTATION the preprocessor modifies the header file such that it only contains the relevant definition source code, effectively turning the header file into a .cpp file, and that's about it
#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "linmath.h"
#include <CGLM/cglm.h>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#define PI 3.14159265358979323846f

typedef struct gameEngineState
{
    int windowHeight;
    int windowWidth;
    int toggleWireMesh;
    float deltaTime;    //Difference in time between frames
}gameEngineState;

typedef struct cameraState
{
    float yaw;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
    float pitch;
    mat4 view;
    vec3 eye;
    vec3 forward;
    vec3 up;
    float FOV;
}cameraState;

typedef struct Vertex
{
    float pos[3];
    float col[3];
    vec2 texture;
}Vertex;

typedef struct mouseState{
    float lastX, lastY;
    int firstMouse;
}mouseState;

static const char* vertex_shader_text =
"#version 460\n"
"uniform mat4 MVP;\n"
"in vec3 vCol;\n"
"in vec3 vPos;\n"
"out vec3 color;\n"
"out vec3 position;\n"
"out vec2 u_resolution;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(vPos, 1.0);\n"
"   position = vPos;\n"
"   color = vCol;\n"
"   u_resolution = vec2(1.0, 1.0);\n"
"}\n";

static const char* fragment_shader_text =
"#version 460\n"
"in vec3 color;\n"
"in vec3 position;\n"
"out vec4 fragment;\n"
"void main()\n"
"{\n"
"    fragment = vec4(position.x, position.y, position.z, 1.0);\n"
"}\n";

static const char* fragment_shader_text_two =
"#version 460\n"
"in vec3 color;\n"
"in vec3 position;\n"
"in vec2 u_resolution;\n"
"out vec4 fragment;\n"
"\n"
"float random (in vec2 st) {\n"
"    return fract(sin(dot(st.xy,\n"
"                         vec2(12.9898,78.233)))*\n"
"        43759.553);\n"
"}\n"
"float noise (in vec2 st) {\n"
"    vec2 i = floor(st);\n"
"    vec2 f = fract(st);\n"
"    float a = random(i);\n"
"    float b = random(i + vec2(1.0, 0.0));\n"
"    float c = random(i + vec2(0.0, 1.0));\n"
"    float d = random(i + vec2(1.0, 1.0));\n"
"    vec2 u = f * f * (3.0 - 2.0 * f);\n"
"    return mix(a, b, u.x) +\n"
"            (c - a)* u.y * (1.0 - u.x) +\n"
"            (d - b) * u.x * u.y;\n"
"}\n"
"#define OCTAVES 60\n"
"float fbm (in vec2 st) {\n"
"    float value = -0.288;\n"
"    float amplitude = 0.908;\n"
"    float frequency = 1.264;\n"
"    for (int i = 0; i < OCTAVES; i++) {\n"
"        value += amplitude * noise(st);\n"
"        st *= 3.792;\n"
"        amplitude *= 0.548;\n"
"    }\n"
"    return value;\n"
"}\n"
"void main() {\n"
"    vec2 st = position.xy/u_resolution.xy;\n"
"    st.x *= u_resolution.x/u_resolution.y;\n"
"    vec3 color = vec3(0.133,0.003,0.145);\n"
"    color += fbm(st*4.808);\n"
"    fragment = vec4(color,1.0);\n"
"    }\n";


static const char* fragment_shader_text_three =
"#version 460\n"
"in vec3 color;\n"
"in vec3 position;\n"
"in vec2 u_resolution;\n"
"out vec4 fragment;\n"
"uniform float u_time;\n"
"float random (in vec2 _st) {\n"
"    return fract(sin(dot(_st.xy,\n"
"                         vec2(12.9898,78.233)))*\n"
"        43758.5453123);\n"
"}\n"
"float noise (in vec2 _st) {\n"
"    vec2 i = floor(_st);\n"
"    vec2 f = fract(_st);\n"
"\n"
"    float a = random(i);\n"
"    float b = random(i + vec2(1.0, 0.0));\n"
"    float c = random(i + vec2(0.0, 1.0));\n"
"    float d = random(i + vec2(1.0, 1.0));\n"
"\n"
"    vec2 u = f * f * (3.0 - 2.0 * f);\n"
"\n"
"    return mix(a, b, u.x) +\n"
"            (c - a)* u.y * (1.0 - u.x) +\n"
"            (d - b) * u.x * u.y;\n"
"}\n"
"#define NUM_OCTAVES 100\n"
"float fbm ( in vec2 _st) {\n"
"    float v = -0.296;\n"
"    float a = 0.828;\n"
"    vec2 shift = vec2(0.790,0.790);\n"
"    mat2 rot = mat2(cos(0.5), sin(0.5),\n"
"                    -sin(0.5), cos(0.50));\n"
"    for (int i = 0; i < NUM_OCTAVES; ++i) {\n"
"        v += a * noise(_st);\n"
"        _st = rot * _st * 2.0 + shift;\n"
"        a *= 0.5;\n"
"    }\n"
"    return v;\n"
"}\n"
"void main() {\n"
"    vec2 st = position.xy/u_resolution.xy*3.;\n"
"    vec3 color = vec3(0.0);\n"
"    vec2 q = vec2(0.);\n"
"    q.x = fbm( st + 0.00*u_time);\n"
"    q.y = fbm( st + vec2(1.0));\n"
"    vec2 r = vec2(0.);\n"
"    r.x = fbm( st + 1.0*q + vec2(1.7,9.2)+ 0.15*u_time );\n"
"    r.y = fbm( st + 1.0*q + vec2(8.3,2.8)+ 0.126*u_time);\n"
"    float f = fbm(st + fbm(st + fbm(st+r)));\n"
"    color = mix(vec3(0.101961,0.619608,0.666667),\n"
"                vec3(0.666667,0.666667,0.498039),\n"
"                clamp((f*f)*4.0,0.0,1.0));\n"
"    color = mix(color,\n"
"                vec3(0,0,0.164706),\n"
"                clamp(length(q),0.0,1.0));\n"
"    color = mix(color,\n"
"                vec3(0.666667,1,1),\n"
"                clamp(length(r.x),0.0,1.0));\n"
"    fragment = vec4((f*f*f+.6*f*f+.5*f)*color.x,(f*f*f+.6*f*f+.5*f)*color.y,(f*f*f+.6*f*f+.5*f)*color.z,1.);\n"
"}\n";

#endif