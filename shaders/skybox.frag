#version 330 core

uniform samplerCube cube;

out vec4 FragColor;
in vec3 coords;

void main(void)
{
    FragColor = texture(cube, coords);
}