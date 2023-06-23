#pragma once

#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>

struct LoginTokens
{
	uint8_t *identity;
	uint8_t *client;

	void deserialize(BitStream *stream)
	{
		this->identity = BitStreamHelper::ReadByteArrayVarInt(stream); // should be rakstring so it doesnt turn into crap
		this->client = BitStreamHelper::ReadByteArrayVarInt(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteByteArrayVarInt(this->identity, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->client, stream);
	}
};