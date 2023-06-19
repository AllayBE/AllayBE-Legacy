#pragma once

#include <cstdarg>
#include <cstdio>
#include <ctime>
#include <string>
#include <colors/ConsoleColors.h>

#ifndef LOGGER_
#define LOGGER_

class Logger
{
protected:
	const char *name;
	bool debugMode;

public:
	Logger(const char *name, bool debugMode);

	void Alert(const char *message, ...);
	void Critical(const char *message, ...);
	void Debug(const char *message, ...);
	void Error(const char *message, ...);
	void Fail(const char *message, ...);
	void Info(const char *message, ...);
	void Success(const char *message, ...);
	void Warning(const char *message, ...);

	void Print(const char *logName, const char *logColor, const char *message, va_list arguments);
	const char *FormatMessage(const char *message, va_list arguments);
};

#endif