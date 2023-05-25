#pragma once
#include <vector>
#include <string>

enum class logType
{
	DEFAULT,
	WARNING,
	ERROR
};

struct LogMessage
{
	std::string log;
	std::string time;
	logType type;
};

class Console
{

public :
	static void Log(const char* log);
	static void LogWarning(const char* log);
	static void LogError(const char* log);

	static void Clear();
	static void Draw();

private:
	static void AddLog(const char* log, logType type);
	static std::string GetTime();
	inline static std::vector<LogMessage> logs;
};
