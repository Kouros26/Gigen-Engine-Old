#include "Inputs.h"
#include "Application.h"
void GigInput::Inputs::UpdateMousePosition()
{
    Window& window = Application::GetWindow();
    window.getCursorPosition(mouse.x, mouse.y);

    mouse.mouseOffsetX = mouse.x - mouse.lastX;
    mouse.mouseOffsetY = mouse.y - mouse.lastY;

    mouse.lastX = mouse.x;
    mouse.lastY = mouse.y;

    mouse.isOnViewPort = false;
    if (mouse.x > window.GetVPX() && mouse.x < window.GetVPX() + window.GetVPWidth())
    {
        if (mouse.y > window.GetHeight() - (window.GetVPY() + window.GetVPHeight()) && mouse.y < window.GetHeight() - window.GetVPY())
        {
            mouse.isOnViewPort = true;
        }
    }
}

bool GigInput::Inputs::GetKey(const GigInput::Keys& pKey)
{
    auto key = static_cast<int>(pKey);
    if ('a' <= key && key <= 'z')
    {
        key -= ('a' - 'A');
    }
    if (key < 0 || key >= inputs.size())
    {
        return false;
    }
    return inputs[key];
}

bool GigInput::Inputs::GetKeyDown(const Keys& pKey)
{
    auto key = static_cast<int>(pKey);
    if ('a' <= key && key <= 'z')
    {
        key -= ('a' - 'A');
    }
    if (key < 0 || key >= inputs.size())
    {
        return false;
    }
    return inputs[key] == static_cast<int>(KeyState::PRESS);
}

bool GigInput::Inputs::GetKeyUp(const Keys& pKey)
{
    auto key = static_cast<int>(pKey);
    if ('a' <= key && key <= 'z')
    {
        key -= ('a' - 'A');
    }
    if (key < 0 || key >= inputs.size())
    {
        return false;
    }
    return inputs[key] == static_cast<int>(KeyState::RELEASE);
}

GigInput::Mouse& GigInput::Inputs::GetMouse()
{
    return mouse;
}

void GigInput::Inputs::UpdateKey(int key, int action)
{
    if (key < 0 || key >= inputs.size())
    {
        return;
    }
    inputs[key] = action == static_cast<int>(MouseState::RELEASE) ? false : true;
}

void GigInput::Inputs::UpdateMouseButton(int button, int action)
{
    mouse.leftClickOnce = false;

	if (button == static_cast<int>(MouseButton::LEFT)) 
	{
		if (mouse.leftClick != (bool)action) 
		{
			mouse.leftClick = action;
			mouse.leftClickOnce = action;
		}
	}

    if (button == static_cast<int>(MouseButton::RIGHT))
        mouse.rightClick = action;

    if (button == static_cast<int>(MouseButton::MIDDLE))
        mouse.wheelClick = action;
}

void GigInput::Inputs::UpdateMouseWheelOffset(double offset)
{
    mouse.wheelOffsetY = offset;
}

bool GigInput::Mouse::OnLeftClick()
{
    if (leftClickOnce)
    {
        leftClickOnce = false;
        return true;
    }
    return false;
}