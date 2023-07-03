#pragma once

#include <BitStream.h>
#include <cstdint>
#include <misc/BitStreamHelper.h>

struct TexturePackInfo
{
	uint8_t *uuid;
	uint8_t *name;
	uint64_t size;
	uint8_t *contentKey;
	uint8_t *subPackName;
	uint8_t *contentIdentity;
	bool hasScripts;
	bool rtxEnabled;

	void deserialize(BitStream *stream)
	{
		this->uuid = BitStreamHelper::ReadByteArrayVarInt(stream);
		this->name = BitStreamHelper::ReadByteArrayVarInt(stream);
		BitStreamHelper::ReadLittleEndian<uint64_t>(this->size, stream);
		this->contentKey = BitStreamHelper::ReadByteArrayVarInt(stream);
		this->subPackName = BitStreamHelper::ReadByteArrayVarInt(stream);
		this->contentIdentity = BitStreamHelper::ReadByteArrayVarInt(stream);
		stream->Read<bool>(this->hasScripts);
		stream->Read<bool>(this->rtxEnabled);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteByteArrayVarInt(this->uuid, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->name, stream);
		BitStreamHelper::WriteLittleEndian<uint64_t>(this->size, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->contentKey, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->subPackName, stream);
		BitStreamHelper::WriteByteArrayVarInt(this->contentIdentity, stream);
		stream->Write<bool>(this->hasScripts);
		stream->Write<bool>(this->rtxEnabled);
	}
};