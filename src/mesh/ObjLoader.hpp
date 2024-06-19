#ifndef OBJ_LOADER_HPP
#define OBJ_LOADER_HPP

#include "Mesh.hpp"

#include <glad/glad.h>
#include <vector>
#include <iostream>
#include <tinyobj/tiny_obj_loader.h>

class ObjLoader
{
public:
    static Mesh loadMesh(const char *path);
};

#endif