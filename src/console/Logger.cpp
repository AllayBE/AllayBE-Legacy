#include <console/Logger.h>

Logger::Logger(const char *name, bool debugMode)
{
	this->name = name;
	this->debugMode = debugMode;
}

void Logger::Alert(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Alert", ConsoleColor_Light_Blue, message, arguments);
	va_end(arguments);
}

void Logger::Critical(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Critical", ConsoleColor_Light_Red, message, arguments);
	va_end(arguments);
}

void Logger::Debug(const char *message, ...)
{
	if (this->debugMode)
	{
		va_list arguments;
		va_start(arguments, message);
		this->Print("Debug", ConsoleColor_Gray, message, arguments);
		va_end(arguments);
	}
}

void Logger::Error(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Error", ConsoleColor_Dark_Red, message, arguments);
	va_end(arguments);
}

void Logger::Fail(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Fail", ConsoleColor_Light_Red, message, arguments);
	va_end(arguments);
}

void Logger::Info(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Info", ConsoleColor_Orange, message, arguments);
	va_end(arguments);
}

void Logger::Success(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Success", ConsoleColor_Light_Green, message, arguments);
	va_end(arguments);
}

void Logger::Warning(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Warning", ConsoleColor_Yellow, message, arguments);
	va_end(arguments);
}

void Logger::Print(const char *logName, const char *logColor, const char *message, va_list arguments)
{
	const time_t currentTime = time(NULL);
	char timeBuffer[146];
#ifndef _TIME_FMT_PFX_
#define _TIME_FMT_PFX_ timeBuffer, sizeof(timeBuffer), "%H:%M:%S"
#endif
#ifdef _CRT_SECURE_NO_WARNINGS
	strftime(_TIME_FMT_PFX_, localtime(&currentTime));
#else
	struct tm ltn;
	localtime_s(&ltn, &currentTime);
	strftime(_TIME_FMT_PFX_, &ltn);
#endif
#undef _TIME_FMT_PFX_
	printf("%s[%s][%s] -> %s", logColor, timeBuffer, logName, ConsoleColor_White);
	const char *formattedMessage = this->FormatMessage(message, arguments);
	if (formattedMessage != nullptr)
	{
		printf(formattedMessage);
	}
	printf(ConsoleColor_Reset);
}

const char *Logger::FormatMessage(const char *message, va_list arguments)
{
	char value[4][8096] = {};
	int index = 0;

	if (++index == 4)
	{
		index = 0;
	}

	int length;
#ifndef _CRT_SECURE_NO_WARNINGS
	length = vsnprintf(value[index], sizeof(value[index]), message, arguments);
#else
	length = _vsnprintf(value[index], sizeof(value[index]), message, arguments);
#endif
	if (length < 0 || length >= sizeof(value[index]))
	{
		return nullptr;
	}

	return (const char *)value[index];
}