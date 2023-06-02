#pragma once

#define RENDERER Renderer::GetInstance()
#define RD_TRIANGLE 0x0004
#define RD_UNSIGNED_INT 0x1405
#define RD_ARRAY_BUFFER 0x8892
#define RD_STATIC_DRAW 0x88E4
#define RD_ELEMENT_ARRAY_BUFFER 0x8893
#define RD_INT 0x1404
#define RD_FLOAT 0x1406
#define RD_FALSE 0
#define RD_TRUE 1
#define RD_COMPILE_STATUS 0x8B81
#define RD_VERTEX_SHADER 0x8B31
#define RD_FRAGMENT_SHADER 0x8B30
#define RD_LINK_STATUS 0x8B82
#define RD_INFO_LOG_LENGTH 0x8B84
#define RD_DEPTH_TEST 0x0B71
#define RD_LINES 0x0001
#define RD_COLOR_BUFFER_BIT 0x00004000
#define RD_DEPTH_BUFFER_BIT 0x00000100
#define RD_TEXTURE_2D 0x0DE1
#define RD_LESS 0x0201
#define RD_FRAMEBUFFER 0x8D40
#define RD_TEXTURE0 0x84C0
#define RD_TEXTURE1 0x84C1

class Font;
class UIImage;

namespace GigRenderer
{
	enum class UniformType
	{
		INT,
		FLOAT,
		VEC3,
		MAT4,
		BOOL,
		VEC4
	};

	struct Buffer
	{
		unsigned int& id;
		const void* data = nullptr;
		const unsigned int size = 0;

		//constructor
		Buffer(unsigned int& pID, const void* pData, const unsigned int pSize)
			: id(pID), data(pData), size(pSize)
		{
		}
	};

	struct BufferVAO
	{
		unsigned int& id;
	};

	enum class BufferType
	{
		VERTEX,
		ELEMENT,
		ARRAY
	};

	struct Renderer
	{
	public:
		Renderer() = default;
		~Renderer() = default;
		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;
		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;

		static Renderer& GetInstance();

		void Init();

        void DeleteVertexArray(int n, const unsigned int* pArray);
        void DeleteBuffer(int n, const unsigned int* pBuffer);
        void DeleteBuffer(Buffer& pVBO, Buffer pEBO, BufferVAO pVAO);
        void BindVertexArray(const unsigned int pArray);
        void BufferSubData(BufferType pType, int n, int size, float f[][4]);
        void BindBuffer(unsigned int pTarget, unsigned int pBuffer);
        void BindBuffer(BufferType pType, unsigned int pID);
        void DrawElements(unsigned int pMode, int pCount, unsigned int pType, const void* pIndices);
        void GenVertexArrays(int pN, unsigned int* pArray);
        void GenBuffers(int pN, unsigned int* pBuffer);
        void BufferData(unsigned int pTarget, int pSize, const void* pData, unsigned int pUsage);
        void BufferData(BufferType pType, unsigned int pSize, const void* pData, unsigned int pUsage);
        void EnableVertexAttribArray(unsigned int pIndex);
        void VertexAttribPointer(unsigned int pIndex, int pSize, unsigned int pType, bool pNormalized, int pStride, const void* pPointer);
        void DisableVertexAttribArray(unsigned int pIndex);
        [[nodiscard]] unsigned int CreateShader(unsigned int pShaderType);
        void ShaderSource(unsigned int pShader, int pCount, const char** pString, const int* pLength);
        void CompileShader(unsigned int pShader);
        void GetShaderiv(unsigned int pShader, unsigned int pName, int* pParams);
        void GetShaderInfoLog(unsigned int pShader, int pBufSize, int* pLength, char* pInfoLog);
        void ViewPort(int pX, int pY, int pWidth, int pHeight);
        void DeleteShader(unsigned int pShader);
        void DeleteProgram(unsigned int pProgram);
        void UseProgram(unsigned int pProgram);
        [[nodiscard]] unsigned int CreateProgram();
        void AttachShader(unsigned int pProgram, unsigned int pShader);
        void LinkProgram(unsigned int pProgram);
        void GetProgramiv(unsigned int pProgram, unsigned int pName, int* pParams);
        void GetProgramInfoLog(unsigned int pProgram, int pBufSize, int* pLength, char* pInfoLog);
        [[nodiscard]] int GetUniformLocation(unsigned int pProgram, const char* pName);
        void SetUniformValue(unsigned int pProgram, const char* pName, UniformType pType, void* pValue);
        void SetUniformValue(int pLocation, UniformType pType, void* pValue);
        void Disable(unsigned int pCap);
        void Enable(unsigned int pCap);
        void DrawArray(unsigned int pMode, int pFirst, int pCount);
        void ClearColor(float pRed, float pGreen, float pBlue, float pAlpha);
        void Clear(unsigned int pMask);
        void LoadTexture(unsigned int& pTexture, int pWidth, int pHeight, const void* pData);
        void LoadImguiTexture(unsigned int& pTexture, int pWidth, int pHeight, const void* pData);
        void BindTexture(unsigned int pTarget, unsigned int pTexture, unsigned int actifText);
        void DeleteTexture(unsigned int pTexture);
        void DepthFunction(unsigned int pFunc);
        void SetupBuffer(const Buffer& pVBO, const Buffer& pEBO, const BufferVAO& pVAO);
        void SetupBuffer(Buffer& pVBO, BufferVAO& pVAO);
        [[nodiscard]] bool LinkShader(unsigned int& pProgram, unsigned int& pVertexShader, unsigned int& pFragmentShader);
		void LoadUIImage(UIImage* img);
		void LoadFont(Font* f) const;
        void BindFrameBuffer(unsigned int type, unsigned int buff);
        void DeleteFrameBuffer(unsigned int buff);

        void InitShadowMapping() const;
        void RenderShadowMapping() const;
	};
};