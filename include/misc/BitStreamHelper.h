#pragma once

#include <BitStream.h>
#include <cstdint>
#include <stdexcept>

using namespace RakNet;

class BitStreamHelper
{
public:
	static void WriteUnsignedVarInt(uint32_t value, BitStream *stream);

	static uint32_t ReadUnsignedVarInt(BitStream *stream);
};