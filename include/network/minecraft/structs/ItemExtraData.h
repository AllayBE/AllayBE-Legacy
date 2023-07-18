#pragma once

#include "ItemExtraDataNbt.h"
#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>
#include <vector>

typedef std::vector<uint8_t *> CanPlaceOnList_t;
typedef std::vector<uint8_t *> CanDestroyList_t;

struct ItemExtraData
{
	bool hasNbt;
	ItemExtraDataNbt nbt;
	CanPlaceOnList_t canPlaceOn;
	CanDestroyList_t canDestroy;
	bool withBlockingTick;
	int64_t blockingTick;

	static ItemExtraData makeWithNbt(ItemExtraDataNbt nbt, CanPlaceOnList_t canPlaceOn, CanDestroyList_t canDestroy, bool withBlockingTick, int64_t blockingTick)
	{
		ItemExtraData result;
		result.hasNbt = true;
		result.nbt = nbt;
		result.canPlaceOn = canPlaceOn;
		result.canDestroy = canDestroy;
		result.withBlockingTick = withBlockingTick;
		result.blockingTick = blockingTick;
		return result;
	}

	static ItemExtraData makeWithoutNbt(CanPlaceOnList_t canPlaceOn, CanDestroyList_t canDestroy, bool withBlockingTick, int64_t blockingTick)
	{
		ItemExtraData result;
		result.hasNbt = false;
		result.canPlaceOn = canPlaceOn;
		result.canDestroy = canDestroy;
		result.withBlockingTick = withBlockingTick;
		result.blockingTick = blockingTick;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		uint16_t hasNbtU16;
		BitStreamHelper::ReadLittleEndian<uint16_t>(hasNbtU16, stream);
		if (hasNbtU16 == 0)
		{
			this->hasNbt = false;
		}
		else if (hasNbtU16 == UINT16_MAX)
		{
			this->hasNbt = true;
		}
		if (this->hasNbt)
		{
			this->nbt.deserialize(stream);
		}
		int16_t canPlaceOnSize;
		BitStreamHelper::ReadLittleEndian<int16_t>(canPlaceOnSize, stream);
		for (int16_t i = 0; i < canPlaceOnSize; ++i)
		{
			this->canPlaceOn.push_back(BitStreamHelper::ReadByteArrayInt16LE(stream));
		}
		int16_t canDestroySize;
		BitStreamHelper::ReadLittleEndian<int16_t>(canDestroySize, stream);
		for (int16_t i = 0; i < canDestroySize; ++i)
		{
			this->canDestroy.push_back(BitStreamHelper::ReadByteArrayInt16LE(stream));
		}
		if (this->withBlockingTick)
		{
			BitStreamHelper::ReadLittleEndian<int64_t>(this->blockingTick, stream);
		}
	}

	void serialize(BitStream *stream)
	{
		uint16_t hasNbtU16;
		if (this->hasNbt)
		{
			hasNbtU16 = UINT16_MAX;
		}
		else
		{
			hasNbtU16 = 0;
		}
		BitStreamHelper::WriteLittleEndian<uint16_t>(hasNbtU16, stream);
		if (this->hasNbt)
		{
			this->nbt.serialize(stream);
		}
		int16_t canPlaceOnSize = static_cast<int16_t>(this->canPlaceOn.size());
		BitStreamHelper::WriteLittleEndian<int16_t>(canPlaceOnSize, stream);
		for (int16_t i = 0; i < canPlaceOnSize; ++i)
		{
			BitStreamHelper::WriteByteArrayInt16LE(this->canPlaceOn.at(i), stream);
		}
		int16_t canDestroySize = static_cast<int16_t>(this->canDestroy.size());
		BitStreamHelper::WriteLittleEndian<int16_t>(canDestroySize, stream);
		for (int16_t i = 0; i < canDestroySize; ++i)
		{
			BitStreamHelper::WriteByteArrayInt16LE(this->canDestroy.at(i), stream);
		}
		if (this->withBlockingTick)
		{
			BitStreamHelper::WriteLittleEndian<int64_t>(this->blockingTick, stream);
		}
	}
};