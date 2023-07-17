#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct ResourcePackIDVersion
{
	std::string uuid;
	std::string version;
	std::string name;

	void deserialize(BitStream *stream)
	{
		this->uuid = BitStreamHelper::ReadStringVarInt(stream);
		this->version = BitStreamHelper::ReadStringVarInt(stream);
		this->name = BitStreamHelper::ReadStringVarInt(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->uuid, stream);
		BitStreamHelper::WriteStringVarInt(this->version, stream);
		BitStreamHelper::WriteStringVarInt(this->name, stream);
	}
};