#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>

struct BlockCoordinates
{
	int32_t x;
	uint32_t y;
	int32_t z;
	
	static BlockCoordinates make(int32_t x, uint32_t y, int32_t z)
	{
		BlockCoordinates bc;
		bc.x = x;
		bc.y = y;
		bc.z = z;
		return bc;
	}

	void deserialize(BitStream *stream)
	{
		this->x = BitStreamHelper::ReadZigZag32(stream);
		this->y = BitStreamHelper::ReadUnsignedVarInt(stream);
		this->z = BitStreamHelper::ReadZigZag32(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteZigZag32(this->x, stream);
		BitStreamHelper::WriteUnsignedVarInt(this->y, stream);
		BitStreamHelper::WriteZigZag32(this->z, stream);
	}
};