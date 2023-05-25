#pragma once
#include "Displayable.h"
#include "Watch.h"

class FPSDisplay : public Displayable
{
public:

	FPSDisplay();
	~FPSDisplay() override;

	void Draw() override;

private:

	void FPSDelay();
	void VSync();
	void FPSGraph() const;

	float timeScale = 1.0f;
	float lastTimeScale = 1.0f;
	float delay = 0.0f;
	float lastDelay = 0.0f;
	bool vSync = true;
	bool lastVSync = true;
};
