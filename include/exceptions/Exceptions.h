#pragma once

#include <stdexcept>
#include <string>

class InvalidPacketIDException : public std::exception
{
private:
	std::string _Message;

public:
	InvalidPacketIDException(const std::string &value) : _Message(value.c_str()) {}
	InvalidPacketIDException(const char *value) : _Message(value) {}

	virtual const char *what() const throw()
	{
		return _Message.c_str();
	}
};