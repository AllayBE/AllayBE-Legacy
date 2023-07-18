#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>
#include <nbt/list/Tag.h>

struct BlockProperty
{
	std::string name;
	Tag *state;

	static BlockProperty make(std::string name, Tag *state)
	{
		BlockProperty result;
		result.name = name;
		result.state = state;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		this->name = BitStreamHelper::ReadStringVarInt(stream);
		this->state = BitStreamHelper::ReadNbtRootLE(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->name, stream);
		BitStreamHelper::WriteNbtRootLE(this->state, stream);
	}
};