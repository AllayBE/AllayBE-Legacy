#include <nbt/list/Tag.h>

int8_t Tag::GetID() const
{
	return INT8_MAX;
}

bool Tag::DeserializeHeader(BitStream *stream)
{
	uint8_t id;
	if (!stream->Read<uint8_t>(id))
	{
		return false;
	}
	if (id != this->GetID())
	{
		throw std::runtime_error("The tag id is not the same as what was excepted");
	}
	return true;
}

bool Tag::DeserializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	return true;
}

bool Tag::DeserializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	return true;
}

bool Tag::DeserializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		if (!this->DeserializeHeader(stream))
		{
			return false;
		}
	}
	return true;
}

void Tag::SerializeHeader(BitStream *stream)
{
	stream->Write<uint8_t>(this->GetID());
}

void Tag::SerializeBE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
}

void Tag::SerializeLE(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
}

void Tag::SerializeNET(BitStream *stream, bool withHeader)
{
	if (withHeader)
	{
		this->SerializeHeader(stream);
	}
}