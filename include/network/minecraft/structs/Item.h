#pragma once

#include "ItemExtraData.h"
#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct Item
{
	int32_t networkID;
	uint16_t count;
	uint32_t metadata;
	int32_t blockRuntimeID;
	ItemExtraData extraData;

	static Item make(int32_t networkID, uint16_t count, uint32_t metadata, int32_t blockRuntimeID, ItemExtraData extraData)
	{
		Item result;
		result.networkID = networkID;
		result.count = count;
		result.metadata = metadata;
		result.blockRuntimeID = blockRuntimeID;
		result.extraData = extraData;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		this->networkID = BitStreamHelper::ReadZigZag32(stream);
		BitStreamHelper::ReadLittleEndian<uint16_t>(this->count, stream);
		this->metadata = BitStreamHelper::ReadUnsignedVarInt(stream);
		this->blockRuntimeID = BitStreamHelper::ReadZigZag32(stream);
		this->extraData.deserialize(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteZigZag32(this->networkID, stream);
		BitStreamHelper::WriteLittleEndian<uint16_t>(this->count, stream);
		BitStreamHelper::WriteUnsignedVarInt(this->metadata, stream);
		BitStreamHelper::WriteZigZag32(this->blockRuntimeID, stream);
		this->extraData.serialize(stream);
	}
};