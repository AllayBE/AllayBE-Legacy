#pragma once

#include <BitStream.h>
#include <misc/BitStreamHelper.h>
#include <string>

struct EducationSharedResourceUri
{
	std::string buttonName;
	std::string linkUri;

	static EducationSharedResourceUri make(std::string buttonName, std::string linkUri)
	{
		EducationSharedResourceUri esru;
		esru.buttonName = buttonName;
		esru.linkUri = linkUri;
		return esru;
	}

	void deserialize(BitStream *stream)
	{
		this->buttonName = BitStreamHelper::ReadStringVarInt(stream);
		this->linkUri = BitStreamHelper::ReadStringVarInt(stream);
	}

	void serialize(BitStream *stream)
	{
		BitStreamHelper::WriteStringVarInt(this->buttonName, stream);
		BitStreamHelper::WriteStringVarInt(this->linkUri, stream);
	}
};