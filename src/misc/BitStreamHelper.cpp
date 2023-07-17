#include <misc/BitStreamHelper.h>

void BitStreamHelper::WriteUnsignedVarInt(uint32_t value, BitStream *stream)
{
	for (uint8_t i = 0; i < 5; ++i)
	{
		uint8_t toWrite = value & 0x7f;

		value >>= 7;

		if (value != 0)
		{
			stream->Write<uint8_t>(toWrite | 0x80);
		}
		else
		{
			stream->Write<uint8_t>(toWrite);
			break;
		}
	}
}

void BitStreamHelper::WriteUnsignedVarLong(uint64_t value, BitStream *stream)
{
	for (uint8_t i = 0; i < 10; ++i)
	{
		uint8_t toWrite = value & 0x7f;

		value >>= 7;

		if (value != 0)
		{
			stream->Write<uint8_t>(toWrite | 0x80);
		}
		else
		{
			stream->Write<uint8_t>(toWrite);
			break;
		}
	}
}

void BitStreamHelper::WriteZigZag32(int32_t value, BitStream *stream)
{
	WriteUnsignedVarInt((uint32_t)((value << 1) ^ (value >> 31)), stream);
}

void BitStreamHelper::WriteZigZag64(int64_t value, BitStream *stream)
{
	WriteUnsignedVarLong((uint64_t)((value << 1) ^ (value >> 63)), stream);
}

void BitStreamHelper::WriteByteArrayVarInt(uint8_t *value, BitStream *stream)
{
	uint32_t numOfBytesToWrite = sizeof(value);
	WriteUnsignedVarInt(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes(value, numOfBytesToWrite);
}

void BitStreamHelper::WriteStringInt32LE(std::string value, BitStream *stream)
{
	int32_t numOfBytesToWrite = sizeof(value);
	WriteLittleEndian<int32_t>(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes((unsigned char *)value.c_str(), numOfBytesToWrite);
}

void BitStreamHelper::WriteStringVarInt(std::string value, BitStream *stream)
{
	uint32_t numOfBytesToWrite = sizeof(value);
	WriteUnsignedVarInt(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes((unsigned char *)value.c_str(), numOfBytesToWrite);
}

void BitStreamHelper::WriteStringUInt16BE(std::string value, BitStream *stream)
{
	uint16_t numOfBytesToWrite = sizeof(value);
	stream->Write<uint16_t>(numOfBytesToWrite);
	stream->WriteAlignedBytes((unsigned char *)value.c_str(), numOfBytesToWrite);
}

void BitStreamHelper::WriteStringUInt16LE(std::string value, BitStream *stream)
{
	uint16_t numOfBytesToWrite = sizeof(value);
	WriteLittleEndian<uint16_t>(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes((unsigned char *)value.c_str(), numOfBytesToWrite);
}

void BitStreamHelper::WriteNbtRootBE(Tag *value, BitStream *stream)
{
	Nbt::WriteRootBE(value, stream);
}

void BitStreamHelper::WriteNbtRootLE(Tag *value, BitStream *stream)
{
	Nbt::WriteRootLE(value, stream);
}

void BitStreamHelper::WriteNbtRootNET(Tag *value, BitStream *stream)
{
	Nbt::WriteRootNET(value, stream);
}

void BitStreamHelper::WriteUuid(std::string value, int version, BitStream *stream)
{
	for (size_t i = 0; i < version << 3; i += 2)
	{
		stream->Write<uint8_t>(static_cast<uint8_t>(stoi(value.substr(i, 2), nullptr, 16)));
	}
}

void BitStreamHelper::WriteBool(bool value, BitStream *stream)
{
	stream->Write<uint8_t>(value == true ? 1 : false);
}

uint32_t BitStreamHelper::ReadUnsignedVarInt(BitStream *stream)
{
	uint32_t value = 0;
	for (uint8_t i = 0; i < 35; i += 7)
	{
		uint8_t toRead;
		stream->Read<uint8_t>(toRead);

		value |= (toRead & 0x7f) << i;

		if ((toRead & 0x80) == 0)
		{
			return value;
		}
	}
	throw std::runtime_error("VarInt is too big");
}

uint64_t BitStreamHelper::ReadUnsignedVarLong(BitStream *stream)
{
	uint64_t value = 0;
	for (uint8_t i = 0; i < 70; i += 7)
	{
		uint8_t toRead;
		stream->Read<uint8_t>(toRead);

		value |= (toRead & 0x7f) << i;

		if ((toRead & 0x80) == 0)
		{
			return value;
		}
	}
	throw std::runtime_error("VarLong is too big");
}

int32_t BitStreamHelper::ReadZigZag32(BitStream *stream)
{
	uint32_t value = ReadUnsignedVarInt(stream);
	return (int32_t)(((int32_t)value >> 1) ^ -((int32_t)value & 1));
}

int64_t BitStreamHelper::ReadZigZag64(BitStream *stream)
{
	uint64_t value = ReadUnsignedVarLong(stream);
	return (int64_t)(((int64_t)value >> 1) ^ -((int64_t)value & 1));
}

uint8_t *BitStreamHelper::ReadByteArrayVarInt(BitStream *stream)
{
	uint32_t byteArraySize = ReadUnsignedVarInt(stream);
	uint8_t *value = (uint8_t *)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
	if (byteArraySize > 0)
	{
		if (stream->ReadAlignedBytes(value, byteArraySize))
		{
			value[byteArraySize] = 0;
		}
		else
		{
			rakFree_Ex(value, _FILE_AND_LINE_);
		}
	}
	else
	{
		stream->AlignReadToByteBoundary();
	}
	return value;
}

std::string BitStreamHelper::ReadStringInt32LE(BitStream *stream)
{
	int32_t byteArraySize;
	ReadLittleEndian<int32_t>(byteArraySize, stream);
	std::string result;

	if (byteArraySize > 0)
	{
		uint8_t *value = (uint8_t *)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
		if (stream->ReadAlignedBytes(value, byteArraySize))
		{
			value[byteArraySize] = 0;
			result = reinterpret_cast<char *>(value);
		}
		else
		{
			rakFree_Ex(value, _FILE_AND_LINE_);
		}
	}
	else
	{
		stream->AlignReadToByteBoundary();
	}
	return result;
}

std::string BitStreamHelper::ReadStringVarInt(BitStream *stream)
{
	uint32_t byteArraySize = ReadUnsignedVarInt(stream);
	std::string result;

	if (byteArraySize > 0)
	{
		uint8_t *value = (uint8_t *)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
		if (stream->ReadAlignedBytes(value, byteArraySize))
		{
			value[byteArraySize] = 0;
			result = reinterpret_cast<char *>(value);
		}
		else
		{
			rakFree_Ex(value, _FILE_AND_LINE_);
		}
	}
	else
	{
		stream->AlignReadToByteBoundary();
	}
	return result;
}

std::string BitStreamHelper::ReadStringUInt16BE(BitStream *stream)
{
	uint16_t byteArraySize;
	stream->Read<uint16_t>(byteArraySize);
	std::string result;

	if (byteArraySize > 0)
	{
		uint8_t *value = (uint8_t *)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
		if (stream->ReadAlignedBytes(value, byteArraySize))
		{
			value[byteArraySize] = 0;
			result = reinterpret_cast<char *>(value);
		}
		else
		{
			rakFree_Ex(value, _FILE_AND_LINE_);
		}
	}
	else
	{
		stream->AlignReadToByteBoundary();
	}
	return result;
}

std::string BitStreamHelper::ReadStringUInt16LE(BitStream *stream)
{
	uint16_t byteArraySize;
	ReadLittleEndian<uint16_t>(byteArraySize, stream);
	std::string result;

	if (byteArraySize > 0)
	{
		uint8_t *value = (uint8_t *)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
		if (stream->ReadAlignedBytes(value, byteArraySize))
		{
			value[byteArraySize] = 0;
			result = reinterpret_cast<char *>(value);
		}
		else
		{
			rakFree_Ex(value, _FILE_AND_LINE_);
		}
	}
	else
	{
		stream->AlignReadToByteBoundary();
	}
	return result;
}

Tag *BitStreamHelper::ReadNbtRootBE(BitStream *stream)
{
	return Nbt::ReadRootBE(stream);
}

Tag *BitStreamHelper::ReadNbtRootLE(BitStream *stream)
{
	return Nbt::ReadRootLE(stream);
}

Tag *BitStreamHelper::ReadNbtRootNET(BitStream *stream)
{
	return Nbt::ReadRootNET(stream);
}

std::string BitStreamHelper::ReadUuid(BitStream *stream)
{
	// todo
	uint8_t buffer[16];
	stream->ReadAlignedBytes(buffer, 16);

	return "reading uuid when its not done";
}

bool BitStreamHelper::ReadBool(bool &value, BitStream *stream)
{
	uint8_t retVal;
	bool read = stream->Read<uint8_t>(retVal);
	value = retVal;
	return read;
}