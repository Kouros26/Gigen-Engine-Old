#pragma once
#include "FixedQueue.h"

class Time
{
	static inline double deltaTime = 0;
	static inline double timeScale = 1;
	static inline double unscaledDeltaTime;
	static inline double currentTime = 0;
	static inline double lastTime = 0;

public:

	class FPS
	{
		static inline FixedQueue<unsigned short, 10> fpsQueue;

		static inline unsigned short fps = 0;
		static inline unsigned int averageFps = 0;
		static inline double FPSUpdateDelay = 1;
		static inline double lastFPSUpdate = 0;
		static inline bool vSync = true;

		static void UpdateAverageFPS();

	public:
		static void UpdateFPS();
		static void ToggleVSync();
		static void SetFPSUpdateDelay(const double& newDelay);
		[[nodiscard]] static unsigned short GetFPS();
		[[nodiscard]] static bool IsVSyncOn();
	};

	static void UpdateDeltaTime();

	[[nodiscard]] static double GetDeltaTime();
	[[nodiscard]] static double GetTimeScale();
	[[nodiscard]] static double GetUnscaledDeltaTime();

	static void SetTimeScale(const double& newTimeScale);
};