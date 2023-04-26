#include "Inputs.h"
#include "Application.h"
void GigInput::Inputs::UpdateMousePosition()
{
    Application::GetWindow().getCursorPosition(mouse.x, mouse.y);

    mouse.mouseOffsetX = mouse.x - mouse.lastX;
    mouse.mouseOffsetY = mouse.y - mouse.lastY;

    mouse.lastX = mouse.x;
    mouse.lastY = mouse.y;
}

bool GigInput::Inputs::GetKey(GigInput::Keys pKey)
{
    auto key = (int)pKey;
    if ('a' <= key && key <= 'z')
    {
        key -= ('a' - 'A');
    }
    return inputs[key];
}

GigInput::Mouse GigInput::Inputs::GetMouse()
{
    return mouse;
}

void GigInput::Inputs::UpdateKey(int key, int action)
{
    inputs[key] = action == (int)MouseState::RELEASE ? false : true;
}

void GigInput::Inputs::UpdateMouseButton(int button, int action)
{
    if (button == (int)MouseButton::LEFT)
        mouse.leftClick = action;

    if (button == (int)MouseButton::RIGHT)
        mouse.rightClick = action;

    if (button == (int)MouseButton::MIDDLE)
        mouse.wheelClick = action;
}

void GigInput::Inputs::UpdateMouseWheelOffset(double offset)
{
    mouse.wheelOffsetY = offset;
}