#include <nbt/list/Float.h>

Float::Float(std::string name, float value)
{
	this->name = name;
	this->value = value;
}

int8_t Float::GetID() const
{
	return ID_TAG_FLOAT;
}

bool Float::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	if (!stream->Read<float>(this->value))
	{
		return false;
	}
	return true;
}

bool Float::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	if (!BitStreamHelper::ReadLittleEndian<float>(this->value, stream))
	{
		return false;
	}
	return true;
}

bool Float::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadLittleEndian<float>(this->value, stream))
	{
		return false;
	}
	return true;
}

void Float::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	stream->Write<float>(this->value);
}

void Float::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	BitStreamHelper::WriteLittleEndian<float>(this->value, stream);
}

void Float::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	BitStreamHelper::ReadLittleEndian<float>(this->value, stream);
}

float Float::GetValue()
{
	return this->value;
}