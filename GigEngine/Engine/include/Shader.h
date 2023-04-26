#pragma once
#include "IResource.h"

#include <string>

namespace lm
{
    struct FMat4;
}

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    bool Link(class VertexShader* vertex, class FragmentShader* fragment);
    void Use();
    void UnUse();

    unsigned int GetId();
    unsigned int GetUniform(const char* name);

	void SetVec3(float vec[3], const char* name);
	void SetVec4(float vec[4], const char* name);
	void SetMat4(lm::FMat4& value, const char* name);
	void SetBool(bool& value, const char* name);
	void SetInt(int& value, const char* name);
	void SetFloat(float& value, const char* name);

private:
    unsigned int shaderProgram = 0;
};

class Shader : public IResource
{
public:
    Shader(std::string const& filePath, int shaderType);
    unsigned int shaderId = 0;
    int shaderType = 0;
    std::string shader;
    void Init() override;
};

class VertexShader : public Shader
{
public:
    VertexShader(std::string const& filePath);
};

class FragmentShader : public Shader
{
public:
    FragmentShader(std::string const& filePath);
};