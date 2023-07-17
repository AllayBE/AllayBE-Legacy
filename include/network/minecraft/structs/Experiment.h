#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct Experiment
{
	std::string name;
	bool enabled;

	void deserialize(BitStream *stream)
	{
		this->name = BitStreamHelper::ReadStringVarInt(stream);
		BitStreamHelper::ReadBool(this->enabled, stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->name, stream);
		BitStreamHelper::WriteBool(this->enabled, stream);
	}
};