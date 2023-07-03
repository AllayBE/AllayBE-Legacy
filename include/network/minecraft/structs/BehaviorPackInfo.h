#pragma once

#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>

struct BehaviorPackInfo
{
	uint8_t *uuid;
	uint8_t *version;
	uint64_t size;
	uint8_t *contentKey;
	uint8_t *subPackName;
	uint8_t *contentIdentity;
	bool hasScripts;

	void deserialize(BitStream *stream)
	{
		this->uuid = BitStreamHelper::ReadByteArrayVarInt(stream);
		this->version = BitStreamHelper::ReadByteArrayVarInt(stream);
		BitStreamHelper::ReadLittleEndian<uint64_t>(this->size, stream);
		this->contentKey = BitStreamHelper::ReadByteArrayVarInt(stream);
		this->subPackName = BitStreamHelper::ReadByteArrayVarInt(stream);
		this->contentIdentity = BitStreamHelper::ReadByteArrayVarInt(stream);
		stream->Read<bool>(this->hasScripts);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteByteArrayVarInt(this->uuid, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->version, stream);
		BitStreamHelper::WriteLittleEndian<uint64_t>(this->size, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->contentKey, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->subPackName, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->contentIdentity, stream);
		stream->Write<bool>(this->hasScripts);
	}
};