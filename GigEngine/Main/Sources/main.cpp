#include "Application.h"
#include "Interface.h"

int main()
{
	Application app;
	Window& window = Application::GetWindow(); //Used as text replacement

	Interface interface(window.GetGLFWWindow(), window.GetGLSLVersion().c_str());

	while (!window.ShouldClose())
	{
		interface.BeginFrame();
		app.Run();
		interface.Draw();
		app.SwapFrames();
	}
}