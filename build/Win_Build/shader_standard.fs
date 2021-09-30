#version 460
in vec3 color;
in vec4 position;
out vec4 fragment;
void main()
{
    fragment = vec4(position.x, position.y, position.z, 1.0);
}