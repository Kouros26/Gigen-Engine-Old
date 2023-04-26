#include "FPSDisplay.h"
#include "imgui.h"
#include "InterfaceManager.h"

FPSDisplay::FPSDisplay()
{
	InterfaceManager::AddEditorElement(this);
	delay = Time::FPS::GetFPSUpdateDelay();
}

FPSDisplay::~FPSDisplay()
= default;

void FPSDisplay::Draw()
{
	ImGui::Begin("FPS Counter");

	FPSDelay();
	VSync();
	FPSGraph();

	ImGui::End();
}

void FPSDisplay::FPSDelay()
{
	ImGui::Text("Average FPS : %.2f", Time::FPS::GetAverageFPS());
	ImGui::SliderFloat("FPS Update delay", &delay, 0.01f, 2, "%.1f");

	if (delay != lastDelay)
		Time::FPS::SetFPSUpdateDelay(delay);

	lastDelay = delay;
}

void FPSDisplay::VSync()
{
	ImGui::Checkbox("VSync", &vSync);

	if (vSync != lastVSync)
		Time::FPS::ToggleVSync(vSync);

	lastVSync = vSync;
}

void FPSDisplay::FPSGraph() const
{
	//ImGui::PlotLines("FPS ", Time::FPS::GetFPSVec().data(), 10);
	ImGui::SameLine();
	ImGui::Text("%.2f", Time::FPS::GetFPS());
}