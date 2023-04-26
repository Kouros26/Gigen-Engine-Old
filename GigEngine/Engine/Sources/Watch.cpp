#include "Watch.h"
#include "Window.h"

float Time::FPS::GetFPS()
{
	return fps;
}

float Time::FPS::GetAverageFPS()
{
	return averageFps;
}

std::vector<float>& Time::FPS::GetFPSVec()
{
	return fpsVec;
}

void Time::FPS::UpdateFPS()
{
	if (currentTime - lastFPSUpdate < FPSUpdateDelay) return;

	fps = static_cast<float>(1 / deltaTime);
	lastFPSUpdate = currentTime;

	fpsVec.push_back(fps);

	const int size = fpsVec.size();
	if (size > MAX_FPS_VECTOR_SIZE)
	{
		fpsAddition -= fpsVec[0];
		fpsVec.erase(fpsVec.begin());
	}

	fpsAddition += fps;
	averageFps = fpsAddition / size;
}

void Time::FPS::ToggleVSync(const bool input)
{
	Window::ToggleVSync(input);
}

void Time::FPS::SetFPSUpdateDelay(const float newDelay)
{
	FPSUpdateDelay = newDelay;
}

float Time::FPS::GetFPSUpdateDelay()
{
	return FPSUpdateDelay;
}

void Time::UpdateDeltaTime()
{
	currentTime = glfwGetTime();
	unscaledDeltaTime = currentTime - lastTime;
	deltaTime = timeScale * unscaledDeltaTime;
	lastTime = currentTime;

	FPS::UpdateFPS();
}

double Time::GetDeltaTime()
{
	return deltaTime;
}

double Time::GetTimeScale()
{
	return timeScale;
}

double Time::GetUnscaledDeltaTime()
{
	return unscaledDeltaTime;
}

double Time::GetCurrentTime()
{
	return currentTime;
}

void Time::SetTimeScale(const double& newTimeScale)
{
	timeScale = newTimeScale;
}