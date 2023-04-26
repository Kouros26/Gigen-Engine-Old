#pragma once
#include <string>

#include <GLFW/glfw3.h>

class Window
{
public:
	void Init();
	void ProcessInput() const;

	static void ToggleVSync(int input);
	void setCursorShow(bool pShowCursor);
	void swapBuffers() const;
	void getCursorPosition(double& xpos, double& ypos) const;
	void Close();

	[[nodiscard]] unsigned int GetWidth() const;
	[[nodiscard]] unsigned int GetHeight() const;

	[[nodiscard]] bool ShouldClose() const;
	[[nodiscard]] GLFWwindow* GetGLFWWindow() const;
	std::string& GetGLSLVersion();

	float GetViewPortRatio();
	void SetViewPort(unsigned int pX, unsigned int pY, unsigned int pWidth, unsigned int pHeight);

private:

	const char* APPLICATION_NAME = "Gigen Engine";

	GLFWwindow* window = nullptr;
	std::string version;
	const int versionMajor = 4;
	const int versionMinor = 6;

	unsigned int width = 0;
	unsigned int height = 0;

	float viewPortRatio = 1;

	static void KeyCallback(GLFWwindow*, int key, int, int action, int);
	static void MouseButtonCallback(GLFWwindow*, int button, int action, int);
	static void FrameBufferResizeCallback(GLFWwindow* pWindow, int width, int height);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};
