#include <nbt/list/Int32.h>

Int32::Int32(std::string name, int32_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int32::GetID() const
{
	return ID_TAG_INT32;
}

bool Int32::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	if (!stream->Read<int32_t>(this->value))
	{
		return false;
	}
	return true;
}

bool Int32::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(this->value, stream))
	{
		return false;
	}
	return true;
}

bool Int32::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	this->value = BitStreamHelper::ReadZigZag32(stream);
	return true;
}

void Int32::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	stream->Write<int32_t>(this->value);
}

void Int32::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	BitStreamHelper::WriteLittleEndian<int32_t>(this->value, stream);
}

void Int32::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	BitStreamHelper::WriteZigZag32(this->value, stream);
}

int32_t Int32::GetValue()
{
	return this->value;
}