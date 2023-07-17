#include <nbt/list/Int8Array.h>

Int8Array::Int8Array(std::string name, Int8List_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Int8Array::GetID() const
{
	return ID_TAG_INT8_ARRAY;
}

bool Int8Array::DeserializeBE(BitStream *stream, bool withHeader)
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
		int8_t int8;
		if (!stream->Read<int8_t>(int8))
		{
			return false;
		}
		this->value.push_back(int8);
	}
	return true;
}

bool Int8Array::DeserializeLE(BitStream *stream, bool withHeader)
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
		int8_t int8;
		if (!stream->Read<int8_t>(int8))
		{
			return false;
		}
		this->value.push_back(int8);
	}
	return true;
}

bool Int8Array::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	int32_t arraySize = BitStreamHelper::ReadZigZag32(stream);
	for (int32_t i = 0; i < arraySize; ++i)
	{
		int8_t int8;
		if (!stream->Read<int8_t>(int8))
		{
			return false;
		}
		this->value.push_back(int8);
	}
	return true;
}

void Int8Array::SerializeBE(BitStream *stream, bool withHeader)
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
		stream->Write<int8_t>(this->value.at(i));
	}
}

void Int8Array::SerializeLE(BitStream *stream, bool withHeader)
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
		stream->Write<int8_t>(this->value.at(i));
	}
}

void Int8Array::SerializeNET(BitStream *stream, bool withHeader)
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
		stream->Write<int8_t>(this->value.at(i));
	}
}

Int8List_t Int8Array::GetValue()
{
	return this->value;
}