#pragma once

#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>
#include <string>

struct LoginTokens
{
	std::string identity;
	std::string client;

	void deserialize(BitStream *stream)
	{
		this->identity = BitStreamHelper::ReadStringIntLE(stream);
		this->client = BitStreamHelper::ReadStringIntLE(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringIntLE(this->identity, stream);
		BitStreamHelper::WriteStringIntLE(this->client, stream);
	}
};