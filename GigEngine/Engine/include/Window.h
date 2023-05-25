#pragma once
#include <string>
#include "Mat4/FMat4.hpp"
#include <GLFW/glfw3.h>

enum class CursorShape
{
	ARROW,
	EYE,
	GRAB,
};

class Window
{
public:
	void Init();
	void ProcessInput() const;

	static void ToggleVSync(int input);
	void setCursorShow(bool pShowCursor) const;
	void swapBuffers() const;
	void getCursorPosition(double& xpos, double& ypos) const;
	void SetMouseIcon(CursorShape shape) const;
	void Close() const;

	[[nodiscard]] unsigned int GetWidth() const;
	[[nodiscard]] unsigned int GetHeight() const;

	[[nodiscard]] unsigned int GetVPWidth() const;
	[[nodiscard]] unsigned int GetVPHeight() const;
	[[nodiscard]] unsigned int GetVPX() const;
	[[nodiscard]] unsigned int GetVPY() const;

	[[nodiscard]] bool ShouldClose() const;
	[[nodiscard]] GLFWwindow* GetGLFWWindow() const;
	std::string& GetGLSLVersion();

	lm::FMat4& GetOrthoMatrix();

	float GetViewPortRatio() const;
	void SetViewPort(unsigned int pX, unsigned int pY, unsigned int pWidth, unsigned int pHeight);

private:

	const char* APPLICATION_NAME = "Gigen Engine";

	GLFWwindow* window = nullptr;
	GLFWimage mouseIcons[2];
	std::string version;
	const int versionMajor = 4;
	const int versionMinor = 6;

	unsigned int width = 0;
	unsigned int height = 0;

	unsigned int vpWidth = 0;
	unsigned int vpHeight = 0;
	unsigned int vpPosx = 0;
	unsigned int vpPosy = 0;

	float viewPortRatio = 1;

	lm::FMat4 orthoMatrix;

	void SetIcon(const std::string& pPath) const;

	static void KeyCallback(GLFWwindow*, int key, int, int action, int);
	static void MouseButtonCallback(GLFWwindow*, int button, int action, int);
	static void FrameBufferResizeCallback(GLFWwindow* pWindow, int width, int height);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
