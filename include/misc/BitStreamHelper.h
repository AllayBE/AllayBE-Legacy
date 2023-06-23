#pragma once

#include <BitStream.h>
#include <cstdint>
#include <stdexcept>

using namespace RakNet;

class BitStreamHelper
{
public:
	static void WriteUnsignedVarInt(uint32_t value, BitStream *stream);
	static void WriteByteArrayVarInt(uint8_t *value, BitStream *stream);

	static uint32_t ReadUnsignedVarInt(BitStream *stream);
	static uint8_t *ReadByteArrayVarInt(BitStream *stream);
};