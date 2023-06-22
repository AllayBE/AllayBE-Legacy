#include <network/raknet/RakNetInterface.h>

RakNetInterface::RakNetInterface(SocketDescriptor *descriptor, RakNetOfflineMessage *offlineMessage)
{
	this->peer = RakPeerInterface::GetInstance();
	this->descriptor = descriptor;
	this->offlineMessage = offlineMessage;
	this->initialized = false;
	this->running = false;
	this->logger = new Logger("RakNet", true);
	this->packetManager = new PacketManager();
	this->playerManager = new PlayerManager();
}

bool RakNetInterface::isInitialized()
{
	return this->initialized;
}

bool RakNetInterface::isRunning()
{
	return this->running;
}

bool RakNetInterface::Initialize()
{
	if (this->isInitialized())
	{
		return false;
	}

	this->peer->SetRakNetProtocolVersion(MINECRAFT_RAKNET_PROTOCOL_VERSION);
	this->peer->SetMaximumIncomingConnections((unsigned short)this->offlineMessage->GetMaxPlayers());
	this->peer->SetOfflinePingData(this->offlineMessage->ToString().C_String());

	this->initialized = true;
	return true;
}

bool RakNetInterface::Start()
{
	if (!this->isInitialized() || this->isRunning())
	{
		return false;
	}

	if (this->peer->Startup(this->offlineMessage->GetMaxPlayers(), this->descriptor, 1) != RAKNET_STARTED)
	{
		return false;
	}

	this->running = true;
	return true;
}

void RakNetInterface::SetMotd(unsigned char *value)
{
	if (!this->initialized)
	{
		return;
	}

	this->offlineMessage->SetMotd(value);
}

void RakNetInterface::SetSecondMotd(unsigned char *value)
{
	if (!this->initialized)
	{
		return;
	}

	this->offlineMessage->SetSecondMotd(value);
}

PlayerManager *RakNetInterface::GetPlayerManager()
{
	return this->playerManager;
}

PacketManager *RakNetInterface::GetPacketManager()
{
	return this->packetManager;
}

void RakNetInterface::UpdatePong()
{
	if (!this->running)
	{
		return;
	}

	unsigned int playerListSize = this->playerManager->GetAll().Size();
	if (this->offlineMessage->GetOnlinePlayers() != playerListSize)
	{
		this->offlineMessage->SetOnlinePlayers(playerListSize);
	}
	this->peer->SetOfflinePingData(this->offlineMessage->ToString());
}

void RakNetInterface::Handle()
{
	if (!this->running)
	{
		return;
	}

	for (Packet *packet = this->peer->Receive(); packet; this->peer->DeallocatePacket(packet), packet = this->peer->Receive())
	{
		BitStream *stream = new BitStream(packet->data, packet->bitSize, false);
		uint8_t id;
		if (!stream->Read<uint8_t>(id))
		{
			return;
		}

		SystemAddress systemAddress = packet->systemAddress;
		size_t hashedAddress = this->playerManager->HashAddress(systemAddress.ToString(true));

		if (id < ID_USER_PACKET_ENUM)
		{
			if (id == ID_NEW_INCOMING_CONNECTION)
			{
				if (this->playerManager->Add(systemAddress, this->peer))
				{
					this->logger->Debug("New incoming connection, hash=%zu, address=%s\n", hashedAddress, systemAddress.ToString(true));
				}
			}
			else if (id == ID_DISCONNECTION_NOTIFICATION)
			{
				if (this->playerManager->Remove(hashedAddress))
				{
					this->logger->Debug("Disconnection received, hash=%zu, address=%s\n", hashedAddress, systemAddress.ToString(true));
				}
			}
		}
		else if (this->playerManager->Has(hashedAddress))
		{
			if (id != ID_GAME)
			{
				this->logger->Debug("Unable to receive the gamepacket and got another packets instead\n");
				continue;
			}

			Player *player = this->playerManager->Get(hashedAddress);

			if (player != nullptr)
			{
				this->logger->Debug("GamePacket received from, hash=%zu, address=%s\n", hashedAddress, systemAddress.ToString(true));

				GamePacket *packet = new GamePacket();
				packet->SetCompressionEnabled(player->IsCompressionEnabled());
				packet->deserialize(stream);
				this->packetManager->HandleGameStreams(packet->GetStreams(), player);
			}
		}
	}
}

void RakNetInterface::FreeMemory()
{
	this->playerManager->GetAll().Clear();
	this->packetManager->GetAll().Clear();
	this->packetManager->GetPacketsHandlerManager()->GetAll().Clear();
	this->offlineMessage->FreeMemory();
}

void RakNetInterface::Shutdown()
{
	this->peer->Shutdown(1000);
	RakPeerInterface::DestroyInstance(this->peer);
}

uint64_t RakNetInterface::Generate64BitUnqiueNumber()
{
	return this->peer->Get64BitUniqueRandomNumber();
}

uint32_t RakNetInterface::Generate32BitUnqiueNumber()
{
	uint64_t uniqueID = this->Generate64BitUnqiueNumber();
	return static_cast<uint32_t>((uniqueID >> 32) ^ uniqueID);
}