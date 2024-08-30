#version 330 core

layout (location = 0) in vec3 aPos;

out vec3 coords;

uniform vec3 front;
uniform vec3 right;
uniform vec3 up;

void main(void)
{
    gl_Position = vec4(aPos, 1.0);
    coords = normalize(front + right * aPos.x + up * aPos.y);
}