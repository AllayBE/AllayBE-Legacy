#pragma once

#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>
#include <string>

struct TexturePackInfo
{
	std::string uuid;
	std::string name;
	uint64_t size;
	std::string contentKey;
	std::string subPackName;
	std::string contentIdentity;
	bool hasScripts;
	bool rtxEnabled;

	void deserialize(BitStream *stream)
	{
		this->uuid = BitStreamHelper::ReadStringVarInt(stream);
		this->name = BitStreamHelper::ReadStringVarInt(stream);
		BitStreamHelper::ReadLittleEndian<uint64_t>(this->size, stream);
		this->contentKey = BitStreamHelper::ReadStringVarInt(stream);
		this->subPackName = BitStreamHelper::ReadStringVarInt(stream);
		this->contentIdentity = BitStreamHelper::ReadStringVarInt(stream);
		BitStreamHelper::ReadBool(this->hasScripts, stream);
		BitStreamHelper::ReadBool(this->rtxEnabled, stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->uuid, stream);
		BitStreamHelper::WriteStringVarInt(this->name, stream);
		BitStreamHelper::WriteLittleEndian<uint64_t>(this->size, stream);
		BitStreamHelper::WriteStringVarInt(this->contentKey, stream);
		BitStreamHelper::WriteStringVarInt(this->subPackName, stream);
		BitStreamHelper::WriteStringVarInt(this->contentIdentity, stream);
		BitStreamHelper::WriteBool(this->hasScripts, stream);
		BitStreamHelper::WriteBool(this->rtxEnabled, stream);
	}
};