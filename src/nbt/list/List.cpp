#include <nbt/list/List.h>

List::List(std::string name, TagList_t value)
{
	this->name = name;
	this->value = value;
}

int8_t List::GetID() const
{
	return ID_TAG_LIST;
}

bool List::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	int8_t tagID;
	if (!stream->Read<int8_t>(tagID))
	{
		return false;
	}
	int32_t arraySize;
	if (!stream->Read<int32_t>(arraySize))
	{
		return false;
	}
	for (int32_t i = 0; i < arraySize; ++i)
	{
		Tag *tag = Nbt::GetTag(tagID);
		tag->DeserializeBE(stream, false);
		this->value.push_back(tag);
	}
	return true;
}

bool List::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	int8_t tagID;
	if (!stream->Read<int8_t>(tagID))
	{
		return false;
	}
	int32_t arraySize;
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(arraySize, stream))
	{
		return false;
	}
	for (int32_t i = 0; i < arraySize; ++i)
	{
		Tag *tag = Nbt::GetTag(tagID);
		tag->DeserializeLE(stream, false);
		this->value.push_back(tag);
	}
	return true;
}

bool List::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	int8_t tagID;
	if (!stream->Read<int8_t>(tagID))
	{
		return false;
	}
	int32_t arraySize = BitStreamHelper::ReadZigZag32(stream);
	for (int32_t i = 0; i < arraySize; ++i)
	{
		Tag *tag = Nbt::GetTag(tagID);
		tag->DeserializeNET(stream, false);
		this->value.push_back(tag);
	}
	return true;
}

void List::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	int32_t arraySize = static_cast<int32_t>(this->value.size());
	for (int32_t i = 0; i < arraySize; ++i)
	{
		stream->Write<int8_t>(this->value.at(i)->GetID());
		stream->Write<int32_t>(arraySize);
		this->value.at(i)->SerializeBE(stream, false);
	}
}

void List::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	int32_t arraySize = static_cast<int32_t>(this->value.size());
	for (int32_t i = 0; i < arraySize; ++i)
	{
		stream->Write<int8_t>(this->value.at(i)->GetID());
		BitStreamHelper::WriteLittleEndian<int32_t>(arraySize, stream);
		this->value.at(i)->SerializeLE(stream, false);
	}
}

void List::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	int32_t arraySize = static_cast<int32_t>(this->value.size());
	for (int32_t i = 0; i < arraySize; ++i)
	{
		stream->Write<int8_t>(this->value.at(i)->GetID());
		BitStreamHelper::WriteZigZag32(arraySize, stream);
		this->value.at(i)->SerializeNET(stream, false);
	}
}

TagList_t List::GetValue()
{
	return this->value;
}