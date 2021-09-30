#version 460
uniform mat4 MVP;
in vec3 vCol;
in vec3 vPos;
out vec3 color;
out vec4 position;
out vec2 u_resolution;
void main()
{
   gl_Position = MVP * vec4(vPos, 1.0);
   position = vec4(vPos, 1.0);
   color = vCol;
   u_resolution = vec2(1.0, 1.0);
}