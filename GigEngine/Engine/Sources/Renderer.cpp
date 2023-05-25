#include <GLAD/glad.h>
#include "Renderer.h"
#include "Font.h"
#include "UIImage.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H

using namespace GigRenderer;

Renderer& Renderer::GetInstance()
{
    static Renderer instance;
    return instance;
}

void Renderer::Init()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }

    //use to display png
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::DeleteVertexArray(int n, const unsigned int* array)
{
    glDeleteVertexArrays(n, array);
}

void Renderer::DeleteBuffer(int n, const unsigned int* pBuffer)
{
    glDeleteBuffers(n, pBuffer);
}

void Renderer::BindVertexArray(const unsigned int pArray)
{
    glBindVertexArray(pArray);
}

void Renderer::BufferSubData(BufferType pType, int n, int size, float f[][4])
{
    glBufferSubData(GL_ARRAY_BUFFER, n, size, f);
}

void Renderer::BindBuffer(unsigned int pTarget, unsigned int pBuffer)
{
    glBindBuffer(pTarget, pBuffer);
}

void Renderer::DrawElements(unsigned int pMode, int pCount, unsigned int pType, const void* pIndices)
{
    glDrawElements(pMode, pCount, pType, pIndices);
}

void Renderer::GenVertexArrays(int n, unsigned int* array)
{
    if (n == 0)
        glGenVertexArrays(n, array);
}

void Renderer::GenBuffers(int n, unsigned int* buffer)
{
    if (n == 0)
        glGenBuffers(n, buffer);
}

void Renderer::BufferData(unsigned int pTarget, int pSize, const void* pData, unsigned int pUsage)
{
    glBufferData(pTarget, pSize, pData, pUsage);
}

void Renderer::EnableVertexAttribArray(unsigned int pIndex)
{
    glEnableVertexAttribArray(pIndex);
}

void Renderer::VertexAttribPointer(unsigned int pIndex, int pSize, unsigned int pType, bool pNormalized, int pStride, const void* pPointer)
{
    glVertexAttribPointer(pIndex, pSize, pType, pNormalized, pStride, pPointer);
}

void Renderer::DisableVertexAttribArray(unsigned int pIndex)
{
    glDisableVertexAttribArray(pIndex);
}

unsigned int Renderer::CreateShader(unsigned int shaderType)
{
    return glCreateShader(shaderType);
}

void Renderer::ShaderSource(unsigned int shader, int count, const char** string, const int* length)
{
    glShaderSource(shader, count, string, length);
}

void Renderer::CompileShader(unsigned int shader)
{
    glCompileShader(shader);
}

void Renderer::GetShaderiv(unsigned int pShader, unsigned int pName, int* pParams)
{
    glGetShaderiv(pShader, pName, pParams);
}

void Renderer::GetShaderInfoLog(unsigned int pShader, int pBufSize, int* pLength, char* pInfoLog)
{
    glGetShaderInfoLog(pShader, pBufSize, pLength, pInfoLog);
}

void Renderer::ViewPort(int x, int y, int width, int height)
{
    glViewport(x, y, width, height);
}

void Renderer::DeleteShader(unsigned int pShader)
{
    glDeleteShader(pShader);
}

void Renderer::DeleteProgram(unsigned int pProgram)
{
    glDeleteProgram(pProgram);
}

void Renderer::UseProgram(unsigned int pProgram)
{
    glUseProgram(pProgram);
}

unsigned int Renderer::CreateProgram()
{
    return glCreateProgram();
}

void Renderer::AttachShader(unsigned int pProgram, unsigned int pShader)
{
    glAttachShader(pProgram, pShader);
}

void Renderer::LinkProgram(unsigned int pProgram)
{
    glLinkProgram(pProgram);
}

void Renderer::GetProgramiv(unsigned int pProgram, unsigned int pName, int* pParams)
{
    glGetProgramiv(pProgram, pName, pParams);
}

void Renderer::GetProgramInfoLog(unsigned int pProgram, int pBufSize, int* pLength, char* pInfoLog)
{
    glGetProgramInfoLog(pProgram, pBufSize, pLength, pInfoLog);
}

int Renderer::GetUniformLocation(unsigned int pProgram, const char* pName)
{
    return glGetUniformLocation(pProgram, pName);
}

void Renderer::SetUniformValue(unsigned int pProgram, const char* pName, UniformType pType, void* pValue)
{
    int location = GetUniformLocation(pProgram, pName);
    switch (pType)
    {
    case UniformType::FLOAT:
        glUniform1f(location, *(float*)pValue);
        break;
    case UniformType::INT:
        glUniform1i(location, *(int*)pValue);
        break;
    case UniformType::BOOL:
        glUniform1i(location, *(bool*)pValue);
        break;
    case UniformType::VEC3:
        glUniform3fv(location, 1, (float*)pValue);
        break;
    case UniformType::MAT4:
        glUniformMatrix4fv(location, 1, GL_FALSE, (float*)pValue);
        break;
    default:
        break;
    }
}

void Renderer::SetUniformValue(int pLocation, UniformType pType, void* pValue)
{
    switch (pType)
    {
    case UniformType::FLOAT:
        glUniform1f(pLocation, *(float*)pValue);
        break;
    case UniformType::INT:
        glUniform1i(pLocation, *(int*)pValue);
        break;
    case UniformType::BOOL:
        glUniform1i(pLocation, *(bool*)pValue);
        break;
    case UniformType::VEC3:
        glUniform3fv(pLocation, 1, (float*)pValue);
        break;
    case UniformType::MAT4:
        glUniformMatrix4fv(pLocation, 1, GL_FALSE, (float*)pValue);
        break;
    case UniformType::VEC4:
        glUniform4fv(pLocation, 1, (float*)pValue);
        break;
    default:
        break;
    }
}

void Renderer::Disable(unsigned int pCap)
{
    glDisable(pCap);
}

void Renderer::Enable(unsigned int pCap)
{
    glEnable(pCap);
}

void Renderer::DrawArray(unsigned int pMode, int pFirst, int pCount)
{
    glDrawArrays(pMode, pFirst, pCount);
}

void Renderer::ClearColor(float pRed, float pGreen, float pBlue, float pAlpha)
{
    glClearColor(pRed, pGreen, pBlue, pAlpha);
}

void Renderer::Clear(unsigned int pMask)
{
    glClear(pMask);
}

void Renderer::LoadTexture(unsigned int& pTexture, int pWidth, int pHeight, const void* pData)
{
    glGenTextures(1, &pTexture);
    BindTexture(GL_TEXTURE_2D, pTexture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);
    glGenerateMipmap(GL_TEXTURE_2D);

    BindTexture(GL_TEXTURE_2D, RD_FALSE);
}

void Renderer::LoadImguiTexture(unsigned int& pTexture, int pWidth, int pHeight, const void* pData)
{
    glGenTextures(1, &pTexture);
    BindTexture(GL_TEXTURE_2D, pTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

    // Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pWidth, pHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pData);

    BindTexture(GL_TEXTURE_2D, RD_FALSE);
}

void Renderer::BindTexture(unsigned int pTarget, unsigned int pTexture)
{
    glBindTexture(pTarget, pTexture);
}

void Renderer::DeleteTexture(unsigned int pTexture)
{
    glDeleteTextures(1, &pTexture);
}

void Renderer::DepthFunction(unsigned int pFunc)
{
    glDepthFunc(pFunc);
}

void Renderer::SetupBuffer(const Buffer& pVBO, const Buffer& pEBO, const BufferVAO& pVAO)
{
    if (pVAO.id == 0)
    {
        glGenVertexArrays(1, &pVAO.id);
    }
    if (pVBO.id == 0)
    {
        glGenBuffers(1, &pVBO.id);
    }

    if (pEBO.id == 0)
    {
        glGenBuffers(1, &pEBO.id);
    }

    BindBuffer(BufferType::ARRAY, pVAO.id);

    BindBuffer(BufferType::VERTEX, pVBO.id);
    BufferData(BufferType::VERTEX, pVBO.size * sizeof(float), pVBO.data, RD_STATIC_DRAW);

    BindBuffer(BufferType::ELEMENT, pEBO.id);
    BufferData(BufferType::ELEMENT, pEBO.size * sizeof(unsigned int), pEBO.data, RD_STATIC_DRAW);

    EnableVertexAttribArray(0);       // position
    VertexAttribPointer(0, 3, RD_FLOAT, RD_FALSE, 16 * sizeof(float), (void*)0);

    EnableVertexAttribArray(1);       // normal
    VertexAttribPointer(1, 3, RD_FLOAT, RD_FALSE, 16 * sizeof(float), (void*)(3 * sizeof(float)));

    EnableVertexAttribArray(2);       // texture
    VertexAttribPointer(2, 2, RD_FLOAT, RD_FALSE, 16 * sizeof(float), (void*)(6 * sizeof(float)));

    EnableVertexAttribArray(3);       // id
    VertexAttribPointer(3, 4, RD_FLOAT, RD_FALSE, 16 * sizeof(float), (void*)(8 * sizeof(float)));

    EnableVertexAttribArray(4);       // weight
    VertexAttribPointer(4, 4, RD_FLOAT, RD_FALSE, 16 * sizeof(float), (void*)(12 * sizeof(float)));

    BindBuffer(BufferType::ARRAY, RD_FALSE);
    BindBuffer(BufferType::VERTEX, RD_FALSE);
    BindBuffer(BufferType::ELEMENT, RD_FALSE);

    DisableVertexAttribArray(0);
    DisableVertexAttribArray(1);
    DisableVertexAttribArray(2);
    DisableVertexAttribArray(3);
    DisableVertexAttribArray(4);
}

void Renderer::SetupBuffer(Buffer& pVBO, BufferVAO& pVAO)
{
    //check if the buffer is already created
    if (pVAO.id == 0)
    {
        glGenVertexArrays(1, &pVAO.id);
    }

    if (pVBO.id == 0)
    {
        glGenBuffers(1, &pVBO.id);
    }

    GenVertexArrays(1, &pVAO.id);
    GenBuffers(1, &pVBO.id);
    BindBuffer(BufferType::ARRAY, pVAO.id);

    BindBuffer(BufferType::VERTEX, pVBO.id);
    BufferData(BufferType::VERTEX, pVBO.size, pVBO.data, RD_STATIC_DRAW);

    VertexAttribPointer(0, 3, RD_FLOAT, RD_FALSE, 3 * sizeof(float), (void*)0);
    EnableVertexAttribArray(0);

    BindBuffer(BufferType::VERTEX, 0);
    BindBuffer(BufferType::ARRAY, 0);
}

void Renderer::BindBuffer(BufferType pType, unsigned int pID)
{
    switch (pType)
    {
    case BufferType::VERTEX:
        glBindBuffer(GL_ARRAY_BUFFER, pID);
        break;
    case BufferType::ELEMENT:
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pID);
        break;
    case BufferType::ARRAY:
        glBindVertexArray(pID);
        break;
    default:
        break;
    }
}

void Renderer::BufferData(BufferType pType, unsigned int pSize, const void* pData, unsigned int pUsage)
{
    switch (pType)
    {
    case BufferType::VERTEX:
        glBufferData(GL_ARRAY_BUFFER, pSize, pData, pUsage);
        break;
    case BufferType::ELEMENT:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, pSize, pData, pUsage);
        break;
    default:
        break;
    }
}

void Renderer::DeleteBuffer(Buffer& pVBO, Buffer pEBO, BufferVAO pVAO)
{
    glDeleteBuffers(1, &pVBO.id);
    glDeleteBuffers(1, &pEBO.id);
    glDeleteVertexArrays(1, &pVAO.id);
}

bool GigRenderer::Renderer::LinkShader(unsigned int& pProgram, unsigned int& pVertexShader, unsigned int& pFragmentShader)
{
    if (pProgram == RD_FALSE)
        pProgram = CreateProgram();

    if (pVertexShader == RD_FALSE || pFragmentShader == RD_FALSE)
        return false;

    AttachShader(pProgram, pVertexShader);
    AttachShader(pProgram, pFragmentShader);
    LinkProgram(pProgram);

    int success = RD_TRUE;
    char infoLog[512]{ 0 };
    GetShaderiv(pProgram, RD_LINK_STATUS, &success);
    if (success == RD_FALSE) {
        int logLen;
        GetProgramiv(pProgram, RD_INFO_LOG_LENGTH, &logLen);
        int written;
        GetProgramInfoLog(pProgram, logLen, &written, infoLog);
        std::cout << "error linking program : " << std::endl;
        std::cout << infoLog << std::endl;
        return false;
    }

    return true;
}

void Renderer::LoadUIImage(UIImage* img)
{
    glGenVertexArrays(1, &img->GetVAO());
    glGenBuffers(1, &img->GetVBO());
    glBindVertexArray(img->GetVAO());
    glBindBuffer(GL_ARRAY_BUFFER, img->GetVBO());
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Renderer::LoadFont(Font* f) const
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return;
    }

    FT_Face face;
    if (FT_New_Face(ft, f->GetFilePath().c_str(), 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return;
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // disable byte-alignment restriction

    for (unsigned int c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            lm::FVec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            lm::FVec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            (unsigned int)face->glyph->advance.x
        };

        f->AddCharacter(std::pair<char, Character>(c, character));
    }

    glGenVertexArrays(1, &f->GetVAO());
    glGenBuffers(1, &f->GetVBO());
    glBindVertexArray(f->GetVAO());
    glBindBuffer(GL_ARRAY_BUFFER, f->GetVBO());
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}