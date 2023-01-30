#include "Window.h"

#include <stdexcept>

#include "Application.h"
#include "Inputs.h"

void Window::ProcessInput() const
{
	Inputs::UpdateMousePosition(window);

	if (Inputs::GetKey(ESCAPE))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

Window::Window()
{
	height = 0;
	width = 0;
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode mode = *glfwGetVideoMode(MyMonitor);

	window = glfwCreateWindow(mode.width, mode.height, appName.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
}

void Window::KeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
	Inputs::UpdateKey(key, action);
}

void Window::MouseButtonCallback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
{
	Inputs::UpdateMouseButton(button, action);
}

void Window::FrameBufferResizeCallback(GLFWwindow* pWindow, int /*width*/, int /*height*/)
{
	const auto app = static_cast<Application*>(glfwGetWindowUserPointer(pWindow));
	app->SetFrameBufferResized(true);
}

int Window::CreateSurface(Application& app) const
{
	return glfwCreateWindowSurface(app.GetInstance(), window, nullptr, &app.GetSurface());
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetGLFWWindow() const
{
	return window;
}
