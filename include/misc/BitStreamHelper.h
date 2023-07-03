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

	template <typename T>
	static void WriteLittleEndian(T &value, BitStream *stream)
	{
		unsigned char output[sizeof(T)];
		stream->ReverseBytes((unsigned char *)&value, output, sizeof(T));
		stream->WriteBits((unsigned char *)output, sizeof(T) * 8, true);
	};

	static uint32_t ReadUnsignedVarInt(BitStream *stream);
	static uint8_t *ReadByteArrayVarInt(BitStream *stream);

	template <typename T>
	static bool ReadLittleEndian(T &value, BitStream *stream)
	{
		unsigned char output[sizeof(T)];
		if (!stream->ReadBits((unsigned char *)output, sizeof(T) * 8, true))
		{
			return false;
		}
		stream->ReverseBytes(output, (unsigned char *)&value, sizeof(T));
		return true;
	};
};
