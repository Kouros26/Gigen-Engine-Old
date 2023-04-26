#include "Renderer.h"
#include "Window.h"
#include "Inputs.h"
#include "Application.h"
#include <iostream>

using namespace GigRenderer;

void Window::Init()
{
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, versionMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, versionMinor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, RD_TRUE);

	GLFWmonitor* MyMonitor = glfwGetPrimaryMonitor();
	const GLFWvidmode mode = *glfwGetVideoMode(MyMonitor);

	width = mode.width;
	height = mode.height;

	//if I put my monitor here, can't debug
	window = glfwCreateWindow(width, height, APPLICATION_NAME, nullptr, nullptr);

	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	glfwSetWindowPos(window, 0, 0);
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	ToggleVSync(1);

	version = "#version ";
	version += std::to_string(versionMajor);
	version += std::to_string(versionMinor);
	version += '0';
}

void Window::ProcessInput() const
{
	glfwPollEvents();
	GigInput::Inputs::UpdateMousePosition();

	//if (GigInput::Inputs::GetKey(GigInput::Keys::ESCAPE))
		//here stop running in editor
}

void Window::Close()
{
	glfwSetWindowShouldClose(window, true);
}

void Window::KeyCallback(GLFWwindow* /*window*/, int key, int /*scancode*/, int action, int /*mods*/)
{
	GigInput::Inputs::UpdateKey(key, action);
}

void Window::MouseButtonCallback(GLFWwindow* /*window*/, int button, int action, int /*mods*/)
{
	GigInput::Inputs::UpdateMouseButton(button, action);
}

void Window::FrameBufferResizeCallback(GLFWwindow* pWindow, int width, int height)
{
	RENDERER.ViewPort(0, 0, width, height);

	const auto window = static_cast<Window*>(glfwGetWindowUserPointer(pWindow));
	window->width = width;
	window->height = height;
	Application::GetEditorCamera().SetRatio(window->GetViewPortRatio());
}

void Window::scrollCallback(GLFWwindow* /*window*/, double /*xoffset*/, double yoffset)
{
	GigInput::Inputs::UpdateMouseWheelOffset(yoffset);
}

void Window::setCursorShow(bool pShowCursor)
{
	if (pShowCursor)
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

void Window::swapBuffers() const
{
	glfwSwapBuffers(window);
}

void Window::getCursorPosition(double& xpos, double& ypos) const
{
	glfwGetCursorPos(window, &xpos, &ypos);
}

void Window::ToggleVSync(int input)
{
	glfwSwapInterval(input);
}

unsigned int Window::GetWidth() const
{
	return width;
}

unsigned int Window::GetHeight() const
{
	return height;
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

GLFWwindow* Window::GetGLFWWindow() const
{
	return window;
}

std::string& Window::GetGLSLVersion()
{
	return version;
}

float Window::GetViewPortRatio()
{
	return viewPortRatio;
}

void Window::SetViewPort(unsigned int pX, unsigned int pY, unsigned int pWidth, unsigned int pHeight)
{
	RENDERER.ViewPort(pX, pY, pWidth, pHeight);
	viewPortRatio = (float)pWidth / (float)pHeight;
	Application::GetEditorCamera().SetRatio(viewPortRatio);
}