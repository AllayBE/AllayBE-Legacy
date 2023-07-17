#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>

struct Vec3f
{
	float x;
	float y;
	float z;

	static Vec3f make(float x, float y, float z)
	{
		Vec3f vec;
		vec.x = x;
		vec.y = y;
		vec.z = z;
		return vec;
	}

	void deserialize(BitStream *stream)
	{
		BitStreamHelper::ReadLittleEndian<float>(this->x, stream);
		BitStreamHelper::ReadLittleEndian<float>(this->y, stream);
		BitStreamHelper::ReadLittleEndian<float>(this->z, stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteLittleEndian<float>(this->x, stream);
		BitStreamHelper::WriteLittleEndian<float>(this->y, stream);
		BitStreamHelper::WriteLittleEndian<float>(this->z, stream);
	}
};