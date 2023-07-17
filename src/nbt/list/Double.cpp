#include <nbt/list/Double.h>

Double::Double(std::string name, double value)
{
	this->name = name;
	this->value = value;
}

int8_t Double::GetID() const
{
	return ID_TAG_DOUBLE;
}

bool Double::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	if (!stream->Read<double>(this->value))
	{
		return false;
	}
	return true;
}

bool Double::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	if (!BitStreamHelper::ReadLittleEndian<double>(this->value, stream))
	{
		return false;
	}
	return true;
}

bool Double::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	if (!BitStreamHelper::ReadLittleEndian<double>(this->value, stream))
	{
		return false;
	}
	return true;
}

void Double::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	stream->Write<double>(this->value);
}

void Double::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	BitStreamHelper::WriteLittleEndian<double>(this->value, stream);
}

void Double::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	BitStreamHelper::ReadLittleEndian<double>(this->value, stream);
}

double Double::GetValue()
{
	return this->value;
}