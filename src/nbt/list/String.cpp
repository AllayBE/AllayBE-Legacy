#include <nbt/list/String.h>

String::String(std::string name, std::string value)
{
	this->name = name;
	this->value = value;
}

int8_t String::GetID() const
{
	return ID_TAG_STRING;
}

bool String::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	this->value = BitStreamHelper::ReadStringUInt16BE(stream);
	return true;
}

bool String::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	this->value = BitStreamHelper::ReadStringUInt16LE(stream);
	return true;
}

bool String::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	this->value = BitStreamHelper::ReadStringVarInt(stream);
	return true;
}

void String::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	BitStreamHelper::WriteStringUInt16BE(this->value, stream);
}

void String::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	BitStreamHelper::WriteStringUInt16LE(this->value, stream);
}

void String::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	BitStreamHelper::WriteStringVarInt(this->value, stream);
}

std::string String::GetValue()
{
	return this->value;
}