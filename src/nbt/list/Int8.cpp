#include <nbt/list/Int8.h>

Int8::Int8(std::string name, int8_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int8::GetID() const
{
	return ID_TAG_INT8;
}

bool Int8::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	if (!stream->Read<int8_t>(this->value))
	{
		return false;
	}
	return true;
}

bool Int8::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	if (!stream->Read<int8_t>(this->value))
	{
		return false;
	}
	return true;
}

bool Int8::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	if (!stream->Read<int8_t>(this->value))
	{
		return false;
	}
	return true;
}

void Int8::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	stream->Write<int8_t>(this->value);
}

void Int8::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	stream->Write<int8_t>(this->value);
}

void Int8::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	stream->Write<int8_t>(this->value);
}

int8_t Int8::GetValue()
{
	return this->value;
}