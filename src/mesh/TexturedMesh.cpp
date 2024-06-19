#include "TexturedMesh.hpp"

TexturedMesh::TexturedMesh(Mesh &mesh, Texture &tex, Shader &shader)
{
    this->mesh = &mesh;
    this->tex = &tex;
    this->shader = &shader;
}

void TexturedMesh::Render()
{
    shader->PutTex(tex->getTexNumber() - 1, ("tex" + std::to_string(tex->getTexNumber() - 1)).c_str() );
    tex->Active();
    tex->Bind();
    mesh->Render();
    tex->Unbind();
}

void TexturedMesh::Cleanup()
{
    mesh->Cleanup();
    tex->Cleanup();
}