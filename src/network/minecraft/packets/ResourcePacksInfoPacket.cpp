#include <network/minecraft/packets/ResourcePacksInfoPacket.h>

uint32_t ResourcePacksInfoPacket::GetID() const
{
	return ID_RESOURCE_PACKS_INFO;
}

bool ResourcePacksInfoPacket::DeserializeBody(BitStream *stream)
{
	if (!stream->Read<bool>(this->mustAccept))
	{
		return false;
	}
	if (!stream->Read<bool>(this->hasScripts))
	{
		return false;
	}
	if (!stream->Read<bool>(this->forceServerPacks))
	{
		return false;
	}
	int16_t behaviorPacksSize;
	if (!BitStreamHelper::ReadLittleEndian<int16_t>(behaviorPacksSize, stream))
	{
		return false;
	}
	for (int16_t i = 0; i < behaviorPacksSize; ++i)
	{
		this->behaviorPacks[i].deserialize(stream);
	}

	int16_t texturePacksSize;
	if (!BitStreamHelper::ReadLittleEndian<int16_t>(texturePacksSize, stream))
	{
		return false;
	}
	for (int16_t i = 0; i < texturePacksSize; ++i)
	{
		this->texturePacks[i].deserialize(stream);
	}
	return true;
}

void ResourcePacksInfoPacket::SerializeBody(BitStream *stream)
{
	stream->Write<bool>(this->mustAccept);
	stream->Write<bool>(this->hasScripts);
	stream->Write<bool>(this->forceServerPacks);

	int16_t behaviorPacksSize = static_cast<int16_t>(this->behaviorPacks.size());
	BitStreamHelper::WriteLittleEndian<int16_t>(behaviorPacksSize, stream);
	for (int16_t i = 0; i < behaviorPacksSize; ++i)
	{
		this->behaviorPacks[i].serialize(stream);
	}

	int16_t texturePacksSize = static_cast<int16_t>(this->texturePacks.size());
	BitStreamHelper::WriteLittleEndian<int16_t>(texturePacksSize, stream);
	for (int16_t i = 0; i < texturePacksSize; ++i)
	{
		this->texturePacks[i].serialize(stream);
	}
}

void ResourcePacksInfoPacket::SetMustAccept(bool value)
{
	this->mustAccept = value;
}

void ResourcePacksInfoPacket::SetHasScripts(bool value)
{
	this->hasScripts = value;
}

void ResourcePacksInfoPacket::SetForceServerPacks(bool value)
{
	this->forceServerPacks = value;
}

void ResourcePacksInfoPacket::SetBehaviorPacks(BehaviorPackList_t value)
{
	this->behaviorPacks = value;
}

void ResourcePacksInfoPacket::SetTexturePacks(TexturePackList_t value)
{
	this->texturePacks = value;
}

bool ResourcePacksInfoPacket::GetMustAccept()
{
	return this->mustAccept;
}

bool ResourcePacksInfoPacket::GetHasScripts()
{
	return this->hasScripts;
}

bool ResourcePacksInfoPacket::GetForceServerPacks()
{
	return this->forceServerPacks;
}

BehaviorPackList_t ResourcePacksInfoPacket::GetBehaviorPacks()
{
	return this->behaviorPacks;
}

TexturePackList_t ResourcePacksInfoPacket::GetTexturePacks()
{
	return this->texturePacks;
}