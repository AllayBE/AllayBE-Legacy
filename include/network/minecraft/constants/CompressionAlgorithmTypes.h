#pragma once

#include <cstdint>

class CompressionAlgorithmTypes
{
public:
	static uint16_t Deflate()
	{
		return 0;
	}

	static uint16_t Snappy()
	{
		return 1;
	}
};