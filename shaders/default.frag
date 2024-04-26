#version 330 core

out vec4 FragColor;

uniform sampler2D tex0;
uniform vec3 lightPos, lightColor, cameraPos;
uniform float shininess;

in vec3 FragPos;
in vec3 norm;
in vec2 coord; 

vec3 lightDir;

float getDiffuse();
float getSpecular();

void main(void)
{
    vec4 lightCol = vec4(lightColor, 1.0f); // Converting the lightColor from vec3 to vec4

    float ambientStrength = 0.3f; // Setting the strength of the ambient color
    float diffuseAmount = getDiffuse(); // Getting the diffuse amount
    float spec = getSpecular(); // Getting the specular amount

    vec4 resultLighting = (spec + diffuseAmount + ambientStrength) * lightCol; // Calculating the result after the calculations

    FragColor = resultLighting * texture(tex0, coord);
}

float getDiffuse()
{
    lightDir = normalize(lightPos - FragPos); // Calculating the light direction
    float diff = max(dot(norm, lightDir), 0.0f); // Calculating the diffuse amount

    return diff;
}

float getSpecular()
{
    vec3 viewDir = normalize(cameraPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    return pow(max(dot(viewDir, reflectDir), 0.0f), shininess);
}