#include <player/Player.h>

Player::Player(SystemAddress address, size_t hashedAddress, RakPeerInterface *peer)
{
	this->address = address;
	this->hashedAddress = hashedAddress;
	this->peer = peer;
	this->compressionEnabled = false;
}

void Player::SetCompressionEnabled(bool value)
{
	this->compressionEnabled = value;
}

bool Player::IsCompressionEnabled()
{
	return this->compressionEnabled;
}

SystemAddress Player::GetAddress()
{
	return this->address;
}

size_t Player::GetHashedAddress()
{
	return this->hashedAddress;
}

void Player::SendPacket(MinecraftPacket *packet, bool force)
{
	char *packetBuffer = (char *)rakMalloc_Ex(0, _FILE_AND_LINE_);
	BitStream *packetStream = new BitStream((unsigned char *)packetBuffer, 0, true);
	rakFree(packetBuffer);
	packet->serialize(packetStream);

	char *gamePacketBuffer = (char *)rakMalloc_Ex(0, _FILE_AND_LINE_);
	BitStream *gamePacketStream = new BitStream((unsigned char *)gamePacketBuffer, 0, true);
	rakFree(gamePacketBuffer);
	GamePacket *gamePacket = new GamePacket();
	gamePacket->SetCompressionEnabled(this->IsCompressionEnabled());
	gamePacket->SetStreams({packetStream});
	gamePacket->serialize(gamePacketStream);

	this->peer->Send(gamePacketStream, force == true ? IMMEDIATE_PRIORITY : HIGH_PRIORITY, RELIABLE_ORDERED, 0, this->GetAddress(), false, 0);
}