#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>

struct Vec3u
{
	uint32_t x;
	uint32_t y;
	uint32_t z;

	static Vec3u make(uint32_t x, uint32_t y, uint32_t z)
	{
		Vec3u vec;
		vec.x = x;
		vec.y = y;
		vec.z = z;
		return vec;
	}

	void deserialize(BitStream *stream)
	{
		this->x = BitStreamHelper::ReadUnsignedVarInt(stream);
		this->y = BitStreamHelper::ReadUnsignedVarInt(stream);
		this->z = BitStreamHelper::ReadUnsignedVarInt(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteUnsignedVarInt(this->x, stream);
		BitStreamHelper::WriteUnsignedVarInt(this->y, stream);
		BitStreamHelper::WriteUnsignedVarInt(this->z, stream);
	}
};