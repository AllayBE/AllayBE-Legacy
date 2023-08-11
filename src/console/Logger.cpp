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
	this->Print("Alert", ConsoleColors::LightBlue(), message, arguments);
	va_end(arguments);
}

void Logger::Critical(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Critical", ConsoleColors::LightRed(), message, arguments);
	va_end(arguments);
}

void Logger::Debug(const char *message, ...)
{
	if (this->debugMode)
	{
		va_list arguments;
		va_start(arguments, message);
		this->Print("Debug", ConsoleColors::Gray(), message, arguments);
		va_end(arguments);
	}
}

void Logger::Error(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Error", ConsoleColors::DarkRed(), message, arguments);
	va_end(arguments);
}

void Logger::Fail(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Fail", ConsoleColors::DarkRed(), message, arguments);
	va_end(arguments);
}

void Logger::Info(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Info", ConsoleColors::Orange(), message, arguments);
	va_end(arguments);
}

void Logger::Success(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Success", ConsoleColors::LightGreen(), message, arguments);
	va_end(arguments);
}

void Logger::Warning(const char *message, ...)
{
	va_list arguments;
	va_start(arguments, message);
	this->Print("Warning", ConsoleColors::Yellow(), message, arguments);
	va_end(arguments);
}

void Logger::Print(const char *logMode, const char *logColor, const char *message, va_list arguments)
{
	const time_t currentTime = time(NULL);
	char timeBuffer[146];
#ifndef _TIME_FMT_PFX_
#define _TIME_FMT_PFX_ timeBuffer, sizeof(timeBuffer), "%H:%M:%S"
#endif
#ifndef _WIN32
	strftime(_TIME_FMT_PFX_, localtime(&currentTime));
#else
	struct tm ltn;
	localtime_s(&ltn, &currentTime);
	strftime(_TIME_FMT_PFX_, &ltn);
#endif
#undef _TIME_FMT_PFX_
	printf("%s[%s][%s: %s] -> %s%s", logColor, timeBuffer, this->name, logMode, ConsoleColors::Reset(), ConsoleColors::White());
	const char *formattedMessage = this->FormatMessage(message, arguments);
	if (formattedMessage != nullptr)
	{
		printf(formattedMessage);
	}
	printf(ConsoleColors::Reset());
}

const char *Logger::FormatMessage(const char *message, va_list arguments)
{
	char value[4][8096] = {};
	int index = 0;

	if (++index == 4)
	{
		index = 0;
	}

	int length = vsnprintf(value[index], sizeof(value[index]), message, arguments);
	if (length < 0 || length >= sizeof(value[index]))
	{
		return nullptr;
	}

	return (const char *)value[index];
}
