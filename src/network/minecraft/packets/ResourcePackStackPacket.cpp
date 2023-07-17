#include <network/minecraft/packets/ResourcePackStackPacket.h>

uint32_t ResourcePackStackPacket::GetID() const
{
	return ID_RESOURCE_PACK_STACK;
}

bool ResourcePackStackPacket::DeserializeBody(BitStream *stream)
{
	if (!BitStreamHelper::ReadBool(this->mustAccept, stream))
	{
		return false;
	}

	uint32_t behaviorPackSize = BitStreamHelper::ReadUnsignedVarInt(stream);
	for (uint32_t i = 0; i < behaviorPackSize; ++i)
	{
		this->behaviorPacks[i].deserialize(stream);
	}

	uint32_t resourcePackSize = BitStreamHelper::ReadUnsignedVarInt(stream);
	for (uint32_t i = 0; i < resourcePackSize; ++i)
	{
		this->resourcePacks[i].deserialize(stream);
	}

	this->gameVersion = BitStreamHelper::ReadStringVarInt(stream);

	int32_t experimentSize;
	if (!BitStreamHelper::ReadLittleEndian<int32_t>(experimentSize, stream))
	{
		return false;
	}
	for (int32_t i = 0; i < experimentSize; ++i)
	{
		this->experiments[i].deserialize(stream);
	}

	if (!BitStreamHelper::ReadBool(this->experimentPreviouslyUsed, stream))
	{
		return false;
	}
	return true;
}

void ResourcePackStackPacket::SerializeBody(BitStream *stream)
{
	BitStreamHelper::WriteBool(this->mustAccept, stream);

	uint32_t behaviorPacksSize = static_cast<uint32_t>(this->behaviorPacks.size());
	BitStreamHelper::WriteUnsignedVarInt(behaviorPacksSize, stream);
	for (uint32_t i = 0; i < behaviorPacksSize; ++i)
	{
		this->behaviorPacks[i].serialize(stream);
	}

	uint32_t resourcePackSize = static_cast<uint32_t>(this->resourcePacks.size());
	BitStreamHelper::WriteUnsignedVarInt(resourcePackSize, stream);
	for (uint32_t i = 0; i < resourcePackSize; ++i)
	{
		this->resourcePacks[i].serialize(stream);
	}

	BitStreamHelper::WriteStringVarInt(this->gameVersion, stream);

	int32_t experimentSize = static_cast<int32_t>(this->experiments.size());
	BitStreamHelper::WriteLittleEndian<int32_t>(experimentSize, stream);
	for (int32_t i = 0; i < experimentSize; ++i)
	{
		this->experiments[i].serialize(stream);
	}

	BitStreamHelper::WriteBool(this->experimentPreviouslyUsed, stream);
}

void ResourcePackStackPacket::SetMustAccept(bool value)
{
	this->mustAccept = value;
}

void ResourcePackStackPacket::SetBehaviorPacks(SBehaviorPackList_t value)
{
	this->behaviorPacks = value;
}

void ResourcePackStackPacket::SetResourcePacks(SResourcePackList_t value)
{
	this->resourcePacks = value;
}

void ResourcePackStackPacket::SetGameVersion(std::string value)
{
	this->gameVersion = value;
}

void ResourcePackStackPacket::SetExperiments(ExperimentList_t value)
{
	this->experiments = value;
}

void ResourcePackStackPacket::SetExperimentPreviouslyUsed(bool value)
{
	this->experimentPreviouslyUsed = value;
}

bool ResourcePackStackPacket::GetMustAccept()
{
	return this->mustAccept;
}

SBehaviorPackList_t ResourcePackStackPacket::GetBehaviorPacks()
{
	return this->behaviorPacks;
}

SResourcePackList_t ResourcePackStackPacket::GetResourcePacks()
{
	return this->resourcePacks;
}

std::string ResourcePackStackPacket::GetGameVersion()
{
	return this->gameVersion;
}

ExperimentList_t ResourcePackStackPacket::GetExperiments()
{
	return this->experiments;
}

bool ResourcePackStackPacket::GetExperimentPreviouslyUsed()
{
	return this->experimentPreviouslyUsed;
}