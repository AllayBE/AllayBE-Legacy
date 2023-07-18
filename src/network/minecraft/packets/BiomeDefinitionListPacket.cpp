#include <network/minecraft/packets/BiomeDefinitionListPacket.h>

uint32_t BiomeDefinitionListPacket::GetID() const
{
	return ID_BIOME_DEFINITION_LIST;
}

bool BiomeDefinitionListPacket::DeserializeBody(BitStream *stream)
{
	this->nbt = (Compound *)BitStreamHelper::ReadNbtRootNET(stream);
	return true;
}

void BiomeDefinitionListPacket::SerializeBody(BitStream *stream)
{
	BitStreamHelper::WriteNbtRootNET(this->nbt, stream);
}

void BiomeDefinitionListPacket::SetNbt(Compound *nbt)
{
	this->nbt = nbt;
}

Compound *BiomeDefinitionListPacket::GetNbt()
{
	return this->nbt;
}