#include <network/minecraft/packets/BiomeDefinitionListPacket.h>

uint32_t BiomeDefinitionListPacket::GetID() const
{
	return ID_BIOME_DEFINITION_LIST;
}

bool BiomeDefinitionListPacket::DeserializeBody(BitStream *stream)
{
	return true;
}

void BiomeDefinitionListPacket::SerializeBody(BitStream *stream)
{
	// temp
	BitStreamHelper::WriteNbtRootNET(new Compound("", {
		new String("", "Plains")
	}), stream);
}