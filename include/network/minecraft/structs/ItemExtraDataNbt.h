#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <nbt/list/Compound.h>
#include <string>

struct ItemExtraDataNbt
{
	uint8_t version;
	Compound *nbt;

	static ItemExtraDataNbt make(uint8_t version, Compound *nbt)
	{
		ItemExtraDataNbt result;
		result.version = version;
		result.nbt = nbt;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		stream->Read<uint8_t>(this->version);
		this->nbt = (Compound *)BitStreamHelper::ReadNbtRootLE(stream);
	}

	void serialize(BitStream *stream)
	{
		stream->Write<uint8_t>(this->version);
		BitStreamHelper::WriteNbtRootLE(this->nbt, stream);
	}
};