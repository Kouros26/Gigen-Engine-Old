#include "Log.h"
#include "Console.h"

void GigDebug::Logger::Log(const std::string& pMessage)
{
    Console::Log(pMessage.c_str());
}

void GigDebug::Logger::LogWarning(const std::string& pMessage)
{
    Console::LogWarning(pMessage.c_str());
}

void GigDebug::Logger::LogError(const std::string& pMessage)
{
    Console::LogError(pMessage.c_str());
}