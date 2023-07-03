#include <network/minecraft/handlers/LoginPacketHandler.h>

bool LoginPacketHandler::ProcessPacket(MinecraftPacket *normalPacket, Player *player)
{
	LoginPacket *packet = (LoginPacket *)normalPacket;

	int32_t protocolVersion = packet->GetProtocolVersion();

	if (player->GetProtocolVersion() != protocolVersion)
	{
		player->SetProtocolVersion(protocolVersion);
	}

	printf("[LoginPacketHandler] Protocol version: %d\n", protocolVersion);

	if (protocolVersion != MINECRAFT_PROTOCOL_VERSION)
	{
		player->SendPlayStatus(protocolVersion < MINECRAFT_PROTOCOL_VERSION ? PlayStatusTypes::LoginFailedClient() : PlayStatusTypes::LoginFailedServer());
		return false;
	}

	printf("[LoginPacketHandler] Success on login\n");

	player->SendPlayStatus(PlayStatusTypes::LoginSuccess());

	ResourcePacksInfoPacket *secondPacket = new ResourcePacksInfoPacket();
	secondPacket->SetMustAccept(false);
	secondPacket->SetHasScripts(false);
	secondPacket->SetForceServerPacks(false);
	secondPacket->SetBehaviorPacks({});
	secondPacket->SetTexturePacks({});
	player->SendPacket(secondPacket);
	return true;
}