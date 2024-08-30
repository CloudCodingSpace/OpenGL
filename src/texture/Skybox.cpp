#include "Skybox.hpp"

Skybox::Skybox(std::vector<std::string> filePaths)
{
    // Creating the shader
    shader = Shader("./shaders/skybox.vert", "./shaders/skybox.frag");

    // Creating the skybox mesh aka the cube
    float vertices[] =
    {
        -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 0.0f,
         1.0f, -1.0f, 0.0f
    };

    unsigned int indices[] =
    {
        0, 1, 2,
        1, 3, 2
    };

    glGenVertexArrays(1, &vaoID);
    glGenBuffers(1, &vboID);
    glGenBuffers(1, &eboID);

    glBindVertexArray(vaoID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

    //Creating the skybox texture
    glGenTextures(1, &ID);
    shader.PutTex(0, "cube");
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);

    int width, height, channels;
    unsigned char* data;
    stbi_set_flip_vertically_on_load(false);
    for(int i = 0; i < filePaths.size(); i++)
    {
        data = stbi_load(filePaths.at(i).c_str(), &width, &height, &channels, 0);
        if(data)
        {
            if(channels == 3)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
            }
            else if(channels == 4)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
            }
            else
            {
                std::cerr << "Wrong number of channels in the file :- " << filePaths.at(i) << std::endl;
                std::exit(-1);
            }
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Skybox::Render(Camera& camera)
{
    shader.Bind();
    shader.PutVec3(camera.GetFront(), "front");
    shader.PutVec3(camera.GetUp(), "up");
    shader.PutVec3(camera.GetRight(), "right");
    
    glBindVertexArray(vaoID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, ID);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    shader.Unbind();
}
    
void Skybox::Cleanup()
{
    shader.Cleanup();
    glDeleteTextures(1, &ID);
    glDeleteVertexArrays(1, &vaoID);
    glDeleteBuffers(1, &eboID);
    glDeleteBuffers(1, &vboID);
}