#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct ItemState
{
	std::string name;
	int16_t runtimeID;
	bool componentBased;

	static ItemState make(std::string name, int16_t runtimeID, bool componentBased)
	{
		ItemState is;
		is.name = name;
		is.runtimeID = runtimeID;
		is.componentBased = componentBased;
		return is;
	}

	void deserialize(BitStream *stream)
	{
		this->name = BitStreamHelper::ReadStringVarInt(stream);
		BitStreamHelper::ReadLittleEndian<int16_t>(this->runtimeID, stream);
		BitStreamHelper::ReadBool(this->componentBased, stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->name, stream);
		BitStreamHelper::WriteLittleEndian<int16_t>(this->runtimeID, stream);
		BitStreamHelper::WriteBool(this->componentBased, stream);
	}
};