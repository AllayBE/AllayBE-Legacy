#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>

struct Vec2f
{
	float x;
	float z;

	static Vec2f make(float x, float z)
	{
		Vec2f vec;
		vec.x = x;
		vec.z = z;
		return vec;
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