#include <nbt/list/Compound.h>

Compound::Compound(std::string name, CTagList_t value)
{
	this->name = name;
	this->value = value;
}

int8_t Compound::GetID() const
{
	return ID_TAG_COMPOUND;
}

bool Compound::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16BE(stream);
	do
	{
		int8_t tagID;
		if (!stream->Read<int8_t>(tagID))
		{
			return false;
		}
		if (tagID == ID_TAG_END)
		{
			break;
		}
		Tag *tag = Nbt::GetTag(tagID);
		tag->DeserializeBE(stream, false);
		this->value.push_back(tag);
	} while (stream->GetNumberOfBitsUsed() > 0);
	return true;
}

bool Compound::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringUInt16LE(stream);
	do
	{
		int8_t tagID;
		if (!stream->Read<int8_t>(tagID))
		{
			return false;
		}
		if (tagID == ID_TAG_END)
		{
			break;
		}
		Tag *tag = Nbt::GetTag(tagID);
		tag->DeserializeLE(stream, false);
		this->value.push_back(tag);
	} while (stream->GetNumberOfBitsUsed() > 0);
	return true;
}

bool Compound::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	this->name = BitStreamHelper::ReadStringVarInt(stream);
	do
	{
		int8_t tagID;
		if (!stream->Read<int8_t>(tagID))
		{
			return false;
		}
		if (tagID == ID_TAG_END)
		{
			break;
		}
		Tag *tag = Nbt::GetTag(tagID);
		tag->DeserializeNET(stream, false);
		this->value.push_back(tag);
	} while (stream->GetNumberOfBitsUsed() > 0);
	return true;
}

void Compound::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16BE(this->name, stream);
	for (size_t i = 0; i < this->value.size(); ++i)
	{
		this->value.at(i)->SerializeBE(stream, true);
	}
	stream->Write<uint8_t>(ID_TAG_END);
}

void Compound::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringUInt16LE(this->name, stream);
	for (size_t i = 0; i < this->value.size(); ++i)
	{
		this->value.at(i)->SerializeLE(stream, true);
	}
	stream->Write<uint8_t>(ID_TAG_END);
}

void Compound::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
	BitStreamHelper::WriteStringVarInt(this->name, stream);
	for (size_t i = 0; i < this->value.size(); ++i)
	{
		this->value.at(i)->SerializeNET(stream, true);
	}
	stream->Write<uint8_t>(ID_TAG_END);
}

CTagList_t Compound::GetValue()
{
	return this->value;
}
