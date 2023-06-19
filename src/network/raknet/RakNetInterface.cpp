#include <network/raknet/RakNetInterface.h>

RakNetInterface::RakNetInterface(SocketDescriptor *descriptor, RakNetOfflineMessage *offlineMessage)
{
	this->peer = RakPeerInterface::GetInstance();
	this->descriptor = descriptor;
	this->offlineMessage = offlineMessage;
	this->initialized = false;
	this->running = false;
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

PlayerList_t RakNetInterface::GetPlayerList()
{
	return this->playerList;
}

void RakNetInterface::UpdatePong()
{
	if (!this->running)
	{
		return;
	}

	unsigned int playerListSize = this->playerList.Size();
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

		if (id == ID_NEW_INCOMING_CONNECTION)
		{
			if (!this->playerList.Has(packet->systemAddress.ToString(true)))
			{
				this->playerList.SetNew(packet->systemAddress.ToString(true), new Player(packet->systemAddress));
				printf("New connection: %s\n", packet->systemAddress.ToString(true));
			}
		}
		else if (id == ID_DISCONNECTION_NOTIFICATION)
		{
			if (this->playerList.Has(packet->systemAddress.ToString(true))) // doesnt work for some reason
			{
				this->playerList.Delete(packet->systemAddress.ToString(true));
			}
			printf("New disconnection: %s\n", packet->systemAddress.ToString(true));
		}
		else if (id == ID_GAME)
		{
			// Player *player = this->playerList.Get(packet->systemAddress.ToString(true));

			// printf("Player IN List: %d\n", player != NULL);
			// printf("Player IN List - 1: %d\n", player != nullptr);

			// if (player != nullptr)
			// {
			// 	printf("GamePacket Recieved From: %s\n", packet->systemAddress.ToString(true));
			// }
		}
	}
}

void RakNetInterface::FreeMemory()
{
	this->playerList.Clear();
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