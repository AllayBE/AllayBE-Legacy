#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct GameRule
{
	std::string name;
	bool editable;
	uint32_t type;

	static GameRule make(std::string name, bool editable, uint32_t type)
	{
		GameRule gr;
		gr.name = name;
		gr.editable = editable;
		gr.type = type;
		return gr;
	}

	void deserialize(BitStream *stream)
	{
		this->name = BitStreamHelper::ReadStringVarInt(stream);
		BitStreamHelper::ReadBool(this->editable, stream);
		this->type = BitStreamHelper::ReadUnsignedVarInt(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->name, stream);
		BitStreamHelper::WriteBool(this->editable, stream);
		BitStreamHelper::WriteUnsignedVarInt(this->type, stream);
	}
};