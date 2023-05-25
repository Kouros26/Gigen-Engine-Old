#pragma once

#include <iostream>

#define GIG_LOG(message) GigDebug::Logger::Log(message)
#define GIG_WARNING(message) GigDebug::Logger::LogWarning(message)
#define GIG_ERROR(message) GigDebug::Logger::LogError(message)

namespace GigDebug
{
	class Logger
	{
	public:
		Logger() = default;

		static void Log(const std::string& pMessage);
		static void LogWarning(const std::string& pMessage);
		static void LogError(const std::string& pMessage);
	};
}
