#include <nbt/list/Int64.h>

Int64::Int64(std::string name, int64_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int64::GetID() const
{
	return ID_TAG_INT64;
}

bool Int64::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	if (!stream->Read<int64_t>(this->value))
	{
		return false;
	}
	return true;
}

bool Int64::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	if (!BitStreamHelper::ReadLittleEndian<int64_t>(this->value, stream))
	{
		return false;
	}
	return true;
}

bool Int64::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	this->value = BitStreamHelper::ReadZigZag64(stream);
	return true;
}

void Int64::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	stream->Write<int64_t>(this->value);
}

void Int64::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	BitStreamHelper::WriteLittleEndian<int64_t>(this->value, stream);
}

void Int64::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	BitStreamHelper::WriteZigZag64(this->value, stream);
}

int64_t Int64::GetValue()
{
	return this->value;
}