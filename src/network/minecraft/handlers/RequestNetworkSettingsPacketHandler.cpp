#include <network/minecraft/handlers/RequestNetworkSettingsPacketHandler.h>

bool RequestNetworkSettingsPacketHandler::ProcessPacket(MinecraftPacket *normalPacket, Player *player)
{
	RequestNetworkSettingsPacket *packet = (RequestNetworkSettingsPacket *)normalPacket;
	player->SetProtocolVersion(packet->GetProtocolVersion());

	NetworkSettingsPacket *secondPacket = new NetworkSettingsPacket();
	secondPacket->SetCompressionThreshold(CompressionThresholdTypes::All());
	secondPacket->SetCompressionAlgorithm(CompressionAlgorithmTypes::Deflate());
	secondPacket->SetClientThrottle(false);
	secondPacket->SetClientThrottleThreshold(0);
	secondPacket->SetClientThrottleScalar(0.0f);
	player->SendPacket(secondPacket, false);

	player->SetCompressionEnabled(true);
	return true;
}