#pragma once

class ConsoleColors
{
public:
	static const char *LightBlue()
	{
		return "\x1b[94m";
	}

	static const char *DarkBlue()
	{
		return "\x1b[34m";
	}

	static const char *Aqua()
	{
		return "\x1b[96m";
	}

	static const char *DarkGreen()
	{
		return "\x1b[32m";
	}

	static const char *LightGreen()
	{
		return "\x1b[92m";
	}

	static const char *LightRed()
	{
		return "\x1b[91m";
	}

	static const char *DarkRed()
	{
		return "\x1b[31m";
	}

	static const char *Pink()
	{
		return "\x1b[95m";
	}

	static const char *Purple()
	{
		return "\x1b[35m";
	}

	static const char *White()
	{
		return "\x1b[37m";
	}

	static const char *Reset()
	{
		return "\x1b[0m";
	}

	static const char *Gray()
	{
		return "\x1b[90m";
	}

	static const char *Yellow()
	{
		return "\x1b[33m";
	}

	static const char *Orange()
	{
		return "\x1b[38;5;202m";
	}
};