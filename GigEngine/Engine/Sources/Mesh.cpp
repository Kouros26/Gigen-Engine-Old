#include "Renderer.h"
#include "Mesh.h"

using namespace GigRenderer;

Mesh::Mesh(unsigned int verticesSize, unsigned int indicesSize)
    :verticesSize(verticesSize), indicesSize(indicesSize)
{
    materialIndex = 0;
}

Mesh::Mesh(const Mesh& other)
{
    this->verticesSize = other.verticesSize;
    this->indicesSize = other.indicesSize;

    this->vertices = new float[verticesSize];
    this->indices = new unsigned int[indicesSize];

    for (int i = 0; i < verticesSize; i++)
        this->vertices[i] = other.vertices[i];

    for (int i = 0; i < indicesSize; i++)
        this->indices[i] = other.indices[i];

    SetupBuffers();
}

Mesh::Mesh(Mesh&& other) noexcept
{
    this->verticesSize = other.verticesSize;
    this->indicesSize = other.indicesSize;

    this->vertices = other.vertices;
    this->indices = other.indices;

    this->VAO = other.VAO;
    this->VBO = other.VBO;
    this->EBO = other.EBO;

    this->materialIndex = other.materialIndex;

    other.vertices = nullptr;
    other.indices = nullptr;
    other.VAO = 0;
    other.VBO = 0;
    other.EBO = 0;
    other.materialIndex = 0;

    other.verticesSize = 0;
    other.indicesSize = 0;
}

Mesh::~Mesh()
{
    delete[] vertices;
    delete[] indices;
    RENDERER.DeleteVertexArray(1, &VAO);
    RENDERER.DeleteBuffer(1, &VBO);
    RENDERER.DeleteBuffer(1, &EBO);
}

Mesh& Mesh::operator=(const Mesh& other)
{
    if (this != &other)
    {
        this->verticesSize = other.verticesSize;
        this->indicesSize = other.indicesSize;

        this->vertices = new float[verticesSize];
        this->indices = new unsigned int[indicesSize];
        this->materialIndex = other.materialIndex;

        for (int i = 0; i < verticesSize; i++)
            this->vertices[i] = other.vertices[i];

        for (int i = 0; i < indicesSize; i++)
            this->indices[i] = other.indices[i];

        SetupBuffers();
    }
    return *this;
}

Mesh& Mesh::operator=(Mesh&& other) noexcept
{
    if (this != &other)
    {
        this->verticesSize = other.verticesSize;
        this->indicesSize = other.indicesSize;

        this->vertices = other.vertices;
        this->indices = other.indices;

        this->VAO = other.VAO;
        this->VBO = other.VBO;
        this->EBO = other.EBO;
        this->materialIndex = other.materialIndex;

        other.vertices = nullptr;
        other.indices = nullptr;
        other.VAO = 0;
        other.VBO = 0;
        other.EBO = 0;
        other.materialIndex = 0;

        other.verticesSize = 0;
        other.indicesSize = 0;
    }
    return *this;
}

void Mesh::Draw()
{
    RENDERER.BindVertexArray(VAO);
    RENDERER.DrawElements(RD_TRIANGLE, indicesSize, RD_UNSIGNED_INT, 0);
    RENDERER.BindVertexArray(0);
}

void Mesh::SetupBuffers()
{
    Buffer VBO{ this->VBO, this->vertices, verticesSize };
    Buffer EBO{ this->EBO, this->indices,indicesSize };
    BufferVAO VAO{ this->VAO };
    RENDERER.SetupBuffer(VBO, EBO, VAO);
}