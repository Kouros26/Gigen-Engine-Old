#pragma once
#include <vector>

constexpr int MAX_FPS_VECTOR_SIZE = 10;

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
		static inline std::vector<float> fpsVec;

		static inline float fps = 0;
		static inline float averageFps = 0;
		static inline float fpsAddition = 0;
		static inline float FPSUpdateDelay = 0.5f;
		static inline float lastFPSUpdate = 0.0f;

	public:
		static void UpdateFPS();
		static void ToggleVSync(bool input);

		static void SetFPSUpdateDelay(const float newDelay);
		static float GetFPSUpdateDelay();
		[[nodiscard]] static float GetFPS();
		static float GetAverageFPS();
		static std::vector<float>& GetFPSVec();
	};

	static void UpdateDeltaTime();

	[[nodiscard]] static double GetDeltaTime();
	[[nodiscard]] static double GetTimeScale();
	[[nodiscard]] static double GetUnscaledDeltaTime();
	[[nodiscard]] static double GetCurrentTime();

	static void SetTimeScale(const double& newTimeScale);
};
