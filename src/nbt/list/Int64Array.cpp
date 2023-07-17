#include <nbt/list/Int64Array.h>

Int64Array::Int64Array(std::string name, Int64List_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int64Array::GetID() const
{
	return ID_TAG_INT64_ARRAY;
}

bool Int64Array::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	int32_t arraySize;
	if (!stream->Read<int32_t>(arraySize))
	{
		return false;
	}
	for (int32_t i = 0; i < arraySize; ++i)
	{
		int64_t int64;
		if (!stream->Read<int64_t>(int64))
		{
			return false;
		}
		this->value.push_back(int64);
	}
	return true;
}

bool Int64Array::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	int32_t arraySize;
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(arraySize, stream))
	{
		return false;
	}
	for (int32_t i = 0; i < arraySize; ++i)
	{
		int64_t int64;
		if (!BitStreamHelper::ReadLittleEndian<int64_t>(int64, stream))
		{
			return false;
		}
		this->value.push_back(int64);
	}
	return true;
}

bool Int64Array::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	int32_t arraySize;
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(arraySize, stream))
	{
		return false;
	}
	for (int32_t i = 0; i < arraySize; ++i)
	{
		this->value.push_back(BitStreamHelper::ReadZigZag64(stream));
	}
	return true;
}

void Int64Array::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	int32_t arraySize = static_cast<int32_t>(this->value.size());
	stream->Write<int32_t>(arraySize);
	for (int32_t i = 0; i < arraySize; ++i)
	{
		stream->Write<int64_t>(this->value.at(i));
	}
}

void Int64Array::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	int32_t arraySize = static_cast<int32_t>(this->value.size());
	BitStreamHelper::WriteLittleEndian<int32_t>(arraySize, stream);
	for (int32_t i = 0; i < arraySize; ++i)
	{
		BitStreamHelper::WriteLittleEndian<int64_t>(this->value.at(i), stream);
	}
}

void Int64Array::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	int32_t arraySize = static_cast<int32_t>(this->value.size());
	BitStreamHelper::WriteZigZag32(arraySize, stream);
	for (int32_t i = 0; i < arraySize; ++i)
	{
		BitStreamHelper::WriteZigZag64(this->value.at(i), stream);
	}
}

Int64List_t Int64Array::GetValue()
{
	return this->value;
}