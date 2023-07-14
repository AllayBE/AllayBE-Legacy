#include <misc/BitStreamHelper.h>
#include <iostream>

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

void BitStreamHelper::WriteByteArrayVarInt(uint8_t *value, BitStream *stream)
{
	uint32_t numOfBytesToWrite = sizeof(value);
	WriteUnsignedVarInt(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes(value, numOfBytesToWrite);
}

void BitStreamHelper::WriteStringIntLE(std::string value, BitStream *stream)
{
	int32_t numOfBytesToWrite = sizeof(value);
	WriteLittleEndian<int32_t>(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes((unsigned char *)value.c_str(), numOfBytesToWrite);
}

void BitStreamHelper::WriteStringVarInt(std::string value, BitStream *stream)
{
	int32_t numOfBytesToWrite = sizeof(value);
	WriteUnsignedVarInt(numOfBytesToWrite, stream);
	stream->WriteAlignedBytes((unsigned char *)value.c_str(), numOfBytesToWrite);
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

std::string BitStreamHelper::ReadStringIntLE(BitStream* stream)
{
	int32_t byteArraySize;
    ReadLittleEndian<int32_t>(byteArraySize, stream);
    std::string result;

    if (byteArraySize > 0)
    {
        uint8_t* value = (uint8_t*)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
        if (stream->ReadAlignedBytes(value, byteArraySize))
        {
            value[byteArraySize] = 0;
            result = reinterpret_cast<char*>(value);
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
        uint8_t* value = (uint8_t*)rakMalloc_Ex(byteArraySize + 1, _FILE_AND_LINE_);
        if (stream->ReadAlignedBytes(value, byteArraySize))
        {
            value[byteArraySize] = 0;
            result = reinterpret_cast<char*>(value);
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

bool BitStreamHelper::ReadBool(bool &value, BitStream *stream)
{
	uint8_t retVal;
	bool read = stream->Read<uint8_t>(retVal);
	value = retVal;
	return read;
}