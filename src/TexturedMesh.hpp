#ifndef TEXTURED_CLASS_HPP
#define TEXTURED_CLASS_HPP

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class TexturedMesh
{
public:
    TexturedMesh(Mesh& mesh, Texture& tex, Shader& shader);
    void Render();
    void Cleanup();
private:
    Mesh* mesh;
    Texture* tex;
    Shader* shader;
};

#endif