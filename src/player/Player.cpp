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

void Player::SetProtocolVersion(int32_t value)
{
	this->protocolVersion = value;
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

int32_t Player::GetProtocolVersion()
{
	return this->protocolVersion;
}

void Player::SendPlayStatus(int32_t status, bool force)
{
	PlayStatusPacket *packet = new PlayStatusPacket();
	packet->SetStatus(status);
	this->SendPacket(packet, force);
}

void Player::SendPacket(MinecraftPacket *packet, bool force)
{
	uint8_t *packetBuffer = (uint8_t *)rakMalloc_Ex(0, _FILE_AND_LINE_);
	BitStream *packetStream = new BitStream(packetBuffer, sizeof(packetBuffer), true);
	rakFree_Ex(packetBuffer, _FILE_AND_LINE_);
	packet->Serialize(packetStream);

	uint8_t *gamePacketBuffer = (uint8_t *)rakMalloc_Ex(0, _FILE_AND_LINE_);
	BitStream *gamePacketStream = new BitStream(gamePacketBuffer, sizeof(gamePacketBuffer), true);
	rakFree_Ex(gamePacketBuffer, _FILE_AND_LINE_);
	GamePacket *gamePacket = new GamePacket();
	gamePacket->SetCompressionEnabled(this->IsCompressionEnabled());
	gamePacket->SetStreams({packetStream});
	gamePacket->Serialize(gamePacketStream);

	this->peer->Send(gamePacketStream, force == true ? IMMEDIATE_PRIORITY : HIGH_PRIORITY, RELIABLE_ORDERED, 0, this->GetAddress(), false, 0);
}