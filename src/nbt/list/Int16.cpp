#include <nbt/list/Int16.h>

Int16::Int16(std::string name, int16_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int16::GetID() const
{
	return ID_TAG_INT16;
}

bool Int16::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	if (!stream->Read<int16_t>(this->value))
	{
		return false;
	}
	return true;
}

bool Int16::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	if (!BitStreamHelper::ReadLittleEndian<int16_t>(this->value, stream))
	{
		return false;
	}
	return true;
}

bool Int16::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadLittleEndian<int16_t>(this->value, stream))
	{
		return false;
	}
	return true;
}

void Int16::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	stream->Write<int16_t>(this->value);
}

void Int16::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	BitStreamHelper::WriteLittleEndian<int16_t>(this->value, stream);
}

void Int16::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	BitStreamHelper::WriteLittleEndian<int16_t>(this->value, stream);
}

int16_t Int16::GetValue()
{
	return this->value;
}