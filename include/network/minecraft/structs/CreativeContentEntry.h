#pragma once

#include "Item.h"
#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <nbt/list/Tag.h>
#include <string>

struct CreativeContentEntry
{
	uint32_t entryID;
	Item item;

	static CreativeContentEntry make(uint32_t entryID, Item item)
	{
		CreativeContentEntry result;
		result.entryID = entryID;
		result.item = item;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		this->entryID = BitStreamHelper::ReadUnsignedVarInt(stream);
		this->item.deserialize(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteUnsignedVarInt(this->entryID, stream);
		this->item.serialize(stream);
	}
};