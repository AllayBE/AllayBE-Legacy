#pragma once

#include <BitStream.h>
#include <cstdint>
#include <nbt/Nbt.h>
#include <stdexcept>
#include <string>

using namespace RakNet;

class BitStreamHelper
{
public:
	static void WriteUnsignedVarInt(uint32_t value, BitStream *stream);
	static void WriteUnsignedVarLong(uint64_t value, BitStream *stream);
	static void WriteZigZag32(int32_t value, BitStream *stream);
	static void WriteZigZag64(int64_t value, BitStream *stream);
	static void WriteByteArrayVarInt(uint8_t *value, BitStream *stream);
	static void WriteStringInt32LE(std::string value, BitStream *stream);
	static void WriteStringVarInt(std::string value, BitStream *stream);
	static void WriteStringUInt16BE(std::string value, BitStream *stream);
	static void WriteStringUInt16LE(std::string value, BitStream *stream);
	static void WriteNbtRootBE(Tag *value, BitStream *stream);
	static void WriteNbtRootLE(Tag *value, BitStream *stream);
	static void WriteNbtRootNET(Tag *value, BitStream *stream);
	static void WriteUuid(std::string value, int version, BitStream *stream);
	static void WriteBool(bool value, BitStream *stream);

	template <typename T>
	static void WriteLittleEndian(T &value, BitStream *stream)
	{
		unsigned char output[sizeof(T)];
		stream->ReverseBytes((unsigned char *)&value, output, sizeof(T));
		stream->WriteBits((unsigned char *)output, sizeof(T) * 8, true);
	};

	static uint32_t ReadUnsignedVarInt(BitStream *stream);
	static uint64_t ReadUnsignedVarLong(BitStream *stream);
	static int32_t ReadZigZag32(BitStream *stream);
	static int64_t ReadZigZag64(BitStream *stream);
	static uint8_t *ReadByteArrayVarInt(BitStream *stream);
	static std::string ReadStringInt32LE(BitStream *stream);
	static std::string ReadStringVarInt(BitStream *stream);
	static std::string ReadStringUInt16BE(BitStream *stream);
	static std::string ReadStringUInt16LE(BitStream *stream);
	static Tag *ReadNbtRootBE(BitStream *stream);
	static Tag *ReadNbtRootLE(BitStream *stream);
	static Tag *ReadNbtRootNET(BitStream *stream);
	static std::string ReadUuid(BitStream *stream);
	static bool ReadBool(bool &value, BitStream *stream);

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
