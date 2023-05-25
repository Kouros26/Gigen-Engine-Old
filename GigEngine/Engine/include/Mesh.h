#pragma once
#include "IResource.h"

#define MAX_BONE_INFLUENCE 4

class Mesh
{
public:
    Mesh(unsigned int verticesSize, unsigned int indicesSize);
    ~Mesh();

    Mesh(const Mesh& other);
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(const Mesh& other);
    Mesh& operator=(Mesh&& other) noexcept;

    std::string texturePath;
    unsigned int materialIndex;
    void Draw();
    void SetupBuffers();

    float* vertices = nullptr;
    unsigned int* indices = nullptr;

private:
    unsigned int verticesSize = 0;
    unsigned int indicesSize = 0;

    unsigned int VBO = 0;
    unsigned int VAO = 0;
    unsigned int EBO = 0;
};
