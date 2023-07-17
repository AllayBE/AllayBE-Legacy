#include <nbt/list/Int32Array.h>

Int32Array::Int32Array(std::string name, Int32List_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int32Array::GetID() const
{
	return ID_TAG_INT32_ARRAY;
}

bool Int32Array::DeserializeBE(BitStream *stream, bool withHeader)
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
		int32_t int32;
		if (!stream->Read<int32_t>(int32))
		{
			return false;
		}
		this->value.push_back(int32);
	}
	return true;
}

bool Int32Array::DeserializeLE(BitStream *stream, bool withHeader)
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
		int32_t int32;
		if (!BitStreamHelper::ReadLittleEndian<int32_t>(int32, stream))
		{
			return false;
		}
		this->value.push_back(int32);
	}
	return true;
}

bool Int32Array::DeserializeNET(BitStream *stream, bool withHeader)
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
		this->value.push_back(BitStreamHelper::ReadZigZag32(stream));
	}
	return true;
}

void Int32Array::SerializeBE(BitStream *stream, bool withHeader)
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
		stream->Write<int32_t>(this->value.at(i));
	}
}

void Int32Array::SerializeLE(BitStream *stream, bool withHeader)
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
		BitStreamHelper::WriteLittleEndian<int32_t>(this->value.at(i), stream);
	}
}

void Int32Array::SerializeNET(BitStream *stream, bool withHeader)
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
		BitStreamHelper::WriteZigZag32(this->value.at(i), stream);
	}
}

Int32List_t Int32Array::GetValue()
{
	return this->value;
}