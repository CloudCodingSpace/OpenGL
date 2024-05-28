#include "ObjLoader.hpp"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Mesh ObjLoader::loadMesh(const char* path)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);
    tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;    
    std::vector<tinyobj::material_t> materials;
    std::string warning, error;

    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> coords;

    if(!tinyobj::LoadObj(&attribs, &shapes, &materials, &warning, &error, path))
    {
        std::cerr << "Can't load obj mesh!\nError :- " << error << std::endl;
        std::exit(-1);
    }

    for(const auto& shape : shapes)
    {
        for(const auto& index : shape.mesh.indices)
        {
            // Adding the vertex data
            vertices.push_back(attribs.vertices[3 * index.vertex_index]);
            vertices.push_back(attribs.vertices[3 * index.vertex_index + 1]);
            vertices.push_back(attribs.vertices[3 * index.vertex_index + 2]);
            // Adding the texCoords data
            coords.push_back(attribs.texcoords[2 * index.texcoord_index]);
            coords.push_back(attribs.texcoords[2 * index.texcoord_index + 1]);
            // Adding the normals data
            normals.push_back(attribs.normals[3 * index.normal_index]);
            normals.push_back(attribs.normals[3 * index.normal_index + 1]);
            normals.push_back(attribs.normals[3 * index.normal_index + 2]);
        }
    }

    GLfloat verts[vertices.size()];
    for(int i = 0; i < vertices.size(); i++)
        verts[i] = vertices.at(i);
    
    GLfloat coord[coords.size()];
    for(int i = 0; i < coords.size(); i++)
        coord[i] = coords.at(i);
    
    GLfloat norms[normals.size()];
    for(int i = 0; i < normals.size(); i++)
        norms[i] = normals.at(i);
    
    return Mesh(verts, coord, norms, sizeof(verts), sizeof(coord), sizeof(norms), sizeof(verts)/(sizeof(float) * 3));
    
}