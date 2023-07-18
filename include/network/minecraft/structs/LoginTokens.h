#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct LoginTokens
{
	std::string identity;
	std::string client;

	static LoginTokens make(std::string identity, std::string client)
	{
		LoginTokens result;
		result.identity = identity;
		result.client = client;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		this->identity = BitStreamHelper::ReadStringInt32LE(stream);
		this->client = BitStreamHelper::ReadStringInt32LE(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringInt32LE(this->identity, stream);
		BitStreamHelper::WriteStringInt32LE(this->client, stream);
	}
};