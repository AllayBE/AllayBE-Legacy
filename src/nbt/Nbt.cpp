#include <nbt/Nbt.h>

Tag *Nbt::GetTag(int8_t tagID)
{
	if (tagID == ID_TAG_INT8)
	{
		return new Int8("", 0);
	}
	else if (tagID == ID_TAG_INT16)
	{
		return new Int16("", 0);
	}
	else if (tagID == ID_TAG_INT32)
	{
		return new Int32("", 0);
	}
	else if (tagID == ID_TAG_INT64)
	{
		return new Int64("", 0);
	}
	else if (tagID == ID_TAG_FLOAT)
	{
		return new Float("", 0.0f);
	}
	else if (tagID == ID_TAG_DOUBLE)
	{
		return new Double("", 0.0);
	}
	else if (tagID == ID_TAG_INT8_ARRAY)
	{
		return new Int8Array("", {});
	}
	else if (tagID == ID_TAG_STRING)
	{
		return new String("", "");
	}
	else if (tagID == ID_TAG_LIST)
	{
		return new List("", {});
	}
	else if (tagID == ID_TAG_COMPOUND)
	{
		return new Compound("", {});
	}
	else if (tagID == ID_TAG_INT32_ARRAY)
	{
		return new Int32Array("", {});
	}
	else if (tagID == ID_TAG_INT64_ARRAY)
	{
		return new Int64Array("", {});
	}

	throw std::runtime_error("Tag not found");
}

void Nbt::WriteRootBE(Tag *tag, BitStream *stream)
{
	tag->SerializeBE(stream, true);
}

void Nbt::WriteRootLE(Tag *tag, BitStream *stream)
{
	tag->SerializeLE(stream, true);
}

void Nbt::WriteRootNET(Tag *tag, BitStream *stream)
{
	tag->SerializeNET(stream, true);
}

Tag *Nbt::ReadRootBE(BitStream *stream)
{
	int8_t tagID;

	if (!stream->Read<int8_t>(tagID))
	{
		throw std::runtime_error("unable to read the tag id");
	}
	if (tagID == ID_TAG_END)
	{
		throw std::runtime_error("unable to read root tag from TAG_END");
	}

	Tag *tag = Nbt::GetTag(tagID);
	tag->DeserializeBE(stream, false);
	return tag;
}

Tag *Nbt::ReadRootLE(BitStream *stream)
{
	int8_t tagID;

	if (!stream->Read<int8_t>(tagID))
	{
		throw std::runtime_error("unable to read the tag id");
	}
	if (tagID == ID_TAG_END)
	{
		throw std::runtime_error("unable to read root tag from TAG_END");
	}

	Tag *tag = Nbt::GetTag(tagID);
	tag->DeserializeLE(stream, false);
	return tag;
}

Tag *Nbt::ReadRootNET(BitStream *stream)
{
	int8_t tagID;

	if (!stream->Read<int8_t>(tagID))
	{
		throw std::runtime_error("unable to read the tag id");
	}
	if (tagID == ID_TAG_END)
	{
		throw std::runtime_error("unable to read root tag from TAG_END");
	}

	Tag *tag = Nbt::GetTag(tagID);
	tag->DeserializeNET(stream, false);
	return tag;
}