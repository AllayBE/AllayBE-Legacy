#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>

struct Vec2f
{
	float x;
	float z;

	static Vec2f make(float x, float z)
	{
		Vec2f result;
		result.x = x;
		result.z = z;
		return result;
	}

	void deserialize(BitStream *stream)
	{
		BitStreamHelper::ReadLittleEndian<float>(this->x, stream);
		BitStreamHelper::ReadLittleEndian<float>(this->z, stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteLittleEndian<float>(this->x, stream);
		BitStreamHelper::WriteLittleEndian<float>(this->z, stream);
	}
};