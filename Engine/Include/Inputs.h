#pragma once
#include <GLFW/glfw3.h>
#include<string>
#include<vector>

#define SPACE GLFW_KEY_SPACE
#define ESCAPE GLFW_KEY_ESCAPE
#define ENTER GLFW_KEY_ENTER
#define TAB GLFW_KEY_TAB
#define BACKSPACE GLFW_KEY_BACKSPACE
#define INSERT GLFW_KEY_INSERT
#define DELETE GLFW_KEY_DELETE
#define RIGHT GLFW_KEY_RIGHT
#define LEFT GLFW_KEY_LEFT
#define DOWN GLFW_KEY_DOWN
#define LEFT_SHIFT GLFW_KEY_LEFT_SHIFT
#define RIGHT_SHIFT GLFW_KEY_RIGHT_SHIFT
#define UP GLFW_KEY_UP
#define F1 GLFW_KEY_F1
#define F2 GLFW_KEY_F2
#define F3 GLFW_KEY_F3
#define F4 GLFW_KEY_F4
#define F5 GLFW_KEY_F5

struct Mouse
{
	double x;
	double y;

	double lastX;
	double lastY;

	double mouseOffsetX;
	double mouseOffsetY;

	bool rightClick;
	bool leftClick;
};

class Inputs
{
public:
	Inputs() = delete;

	static bool GetKey(int key);

	static Mouse GetMouse();

	static void UpdateKey(int key, int action);

	static void UpdateMousePosition(GLFWwindow* window);

	static void UpdateMouseButton(int button, int action);

private:
	inline static Mouse mouse;
	inline static std::vector<bool> inputs = std::vector<bool>(GLFW_KEY_LAST + 1, false);
};

inline bool Inputs::GetKey(int key)
{
	if ('a' <= key && key <= 'z')
	{
		key -= ('a' - 'A');
	}
	return inputs[key];
}

inline Mouse Inputs::GetMouse()
{
	return mouse;
}

inline void Inputs::UpdateKey(int key, int action)
{
	inputs[key] = action == GLFW_RELEASE ? false : true;
}

inline void Inputs::UpdateMousePosition(GLFWwindow* window)
{
	glfwGetCursorPos(window, &mouse.x, &mouse.y);

	mouse.mouseOffsetX = mouse.x - mouse.lastX;
	mouse.mouseOffsetY = mouse.y - mouse.lastY;

	mouse.lastX = mouse.x;
	mouse.lastY = mouse.y;
}

inline void Inputs::UpdateMouseButton(int button, int action)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT)
		mouse.leftClick = action;

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
		mouse.rightClick = action;
}