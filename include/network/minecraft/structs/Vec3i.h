#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>

struct Vec3i
{
	int32_t x;
	int32_t y;
	int32_t z;

	static Vec3i make(int32_t x, int32_t y, int32_t z)
	{
		Vec3i result;
		result.x = x;
		result.y = y;
		result.z = z;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		this->x = BitStreamHelper::ReadZigZag32(stream);
		this->y = BitStreamHelper::ReadZigZag32(stream);
		this->z = BitStreamHelper::ReadZigZag32(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteZigZag32(this->x, stream);
		BitStreamHelper::WriteZigZag32(this->y, stream);
		BitStreamHelper::WriteZigZag32(this->z, stream);
	}
};