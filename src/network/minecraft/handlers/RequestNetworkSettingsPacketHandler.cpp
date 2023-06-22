#include <network/minecraft/handlers/RequestNetworkSettingsPacketHandler.h>

bool RequestNetworkSettingsPacketHandler::processPacket(MinecraftPacket *normalPacket, Player *player)
{
	RequestNetworkSettingsPacket *packet = (RequestNetworkSettingsPacket *)normalPacket;
	printf("Protocol version: %d\n", packet->GetProtocolVersion());
	return true;
}