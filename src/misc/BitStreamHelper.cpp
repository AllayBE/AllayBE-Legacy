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
