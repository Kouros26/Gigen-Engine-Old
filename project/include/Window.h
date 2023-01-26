#pragma once
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

class Application;
class Window
{
	GLFWwindow* window;
	unsigned int width{};
	unsigned int height{};

	char* const APPLICATION_NAME = "Gigen Engine";

	void ProcessInput() const; 
	static void KeyCallback(GLFWwindow*, int key, int, int action, int);
	static void MouseButtonCallback(GLFWwindow*, int button, int action, int);
	static void FrameBufferResizeCallback(GLFWwindow* pWindow, int width, int height);

public:
	Window();
	int CreateSurface(Application& app) const;
	[[nodiscard]] bool ShouldClose() const;
	[[nodiscard]] GLFWwindow* GetGLFWWindow() const;
};