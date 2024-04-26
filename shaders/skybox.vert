#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 coords;

uniform mat4 view;
uniform mat4 proj;

void main(void)
{
    coords = aPos;
    vec4 pos = proj * view * vec4(aPos, 0.0);
    gl_Position  = pos.xyww;
}