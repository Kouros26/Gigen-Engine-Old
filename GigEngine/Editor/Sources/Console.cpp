#include "Console.h"
#include <chrono>
#include "imgui.h"

void Console::Log(const char* log)
{
	AddLog(log, logType::DEFAULT);
}

void Console::LogWarning(const char* log)
{
	AddLog(log, logType::WARNING);
}

void Console::LogError(const char* log)
{
	AddLog(log, logType::ERROR);
}

void Console::Clear()
{
	logs.clear();
}

void Console::Draw()
{
	ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 30);
	if (ImGui::Button("Clear"))
	{
		Clear();
	}

	ImGui::BeginGroup();
	for (int i = logs.size(); i > 0; i--)
	{
		LogMessage logmsg = logs[i - 1];
		switch (logmsg.type)
		{
		case logType::WARNING:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 255, 0, 255));
			ImGui::TextWrapped(logmsg.log.c_str());
			ImGui::PopStyleColor();
			break;
		case logType::ERROR:
			ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(255, 0, 0, 255));
			ImGui::TextWrapped(logmsg.log.c_str());
			ImGui::PopStyleColor();
			break;
		default:
			ImGui::TextWrapped(logmsg.log.c_str());
			break;
		}
		ImGui::SameLine(ImGui::GetWindowContentRegionWidth() - 90);
		ImGui::TextColored({ 0.7f,0.7f,0.7f, 1 }, logmsg.time.c_str());
		ImGui::Separator();
	}
	ImGui::EndGroup();
}

void Console::AddLog(const char* log, logType type)
{
	LogMessage temp;
	temp.log = log;

	if (temp.log.length() == 0)
	{
		return;
	}

	temp.type = type;
	temp.time = GetTime();

	logs.push_back(temp);
}

std::string Console::GetTime()
{
	const auto now = std::chrono::system_clock::now();
	const auto in_time_t = std::chrono::system_clock::to_time_t(now);

	std::stringstream ss;
	ss << std::put_time(std::localtime(&in_time_t), "%HH:%MM:%SS");
	return ss.str();
}