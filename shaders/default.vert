#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 normal;

out vec2 coord;
out vec3 norm;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 proj; 
uniform mat4 view;

void main(void)
{
    gl_Position = proj * view * model * vec4(pos, 1.0);
    coord = texCoord;
    norm = normal;
    FragPos = vec3(model * vec4(pos, 1.0));
}