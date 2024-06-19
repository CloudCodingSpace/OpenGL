#ifndef TEXTURED_MESH_CLASS_HPP
#define TEXTURED_MESH_CLASS_HPP

#include "Mesh.hpp"
#include "../texture/Texture.hpp"
#include "../shaders/Shader.hpp"

class TexturedMesh
{
public:
    TexturedMesh() = default;
    TexturedMesh(Mesh& mesh, Texture& tex, Shader& shader);
    void Render();
    void Cleanup();
private:
    Mesh* mesh;
    Texture* tex;
    Shader* shader;
};

#endif