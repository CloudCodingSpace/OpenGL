#ifndef MESH_CLASS_HPP
#define MESH_CLASS_HPP

#include <iostream>
#include <glad/glad.h>

class Mesh
{
public:
    Mesh() = default;
    Mesh(GLfloat* vertices, GLfloat* coord, GLfloat* normals, GLsizeiptr vertSize, GLsizeiptr coordSize, GLsizeiptr normSize, GLuint count);
    void Render();
    void Cleanup();
private:
    GLuint vao, posVbo, texVbo, normVbo, vertCount;
};

#endif