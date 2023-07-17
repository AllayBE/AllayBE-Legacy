#include <network/raknet/RakNetOfflineMessage.h>

RakNetOfflineMessage::RakNetOfflineMessage(
	const char *edition,
	char *motd,
	unsigned int protocolVersion,
	const char *minecraftVersion,
	unsigned int onlinePlayers,
	unsigned int maxPlayers,
	uint64_t uniqueID,
	char *secondMotd,
	const char *gameMode
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	,
	char gameModeInInt,
	unsigned short portv4,
	unsigned short portv6
#endif
)
{
	this->edition = edition;
	this->motd = motd;
	this->protocolVersion = protocolVersion;
	this->minecraftVersion = minecraftVersion;
	this->onlinePlayers = onlinePlayers;
	this->maxPlayers = maxPlayers;
	this->uniqueID = uniqueID;
	this->secondMotd = secondMotd;
	this->gameMode = gameMode;
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	this->gameModeInInt = gameModeInInt;
	this->portv4 = portv4;
	this->portv6 = portv6;
#endif
}

void RakNetOfflineMessage::SetMotd(char *value)
{
	this->motd = value;
}

void RakNetOfflineMessage::SetOnlinePlayers(unsigned int value)
{
	this->onlinePlayers = value;
}

void RakNetOfflineMessage::SetSecondMotd(char *value)
{
	this->secondMotd = value;
}

const char *RakNetOfflineMessage::GetEdition()
{
	return this->edition;
}

char *RakNetOfflineMessage::GetMotd()
{
	return this->motd;
}

unsigned int RakNetOfflineMessage::GetProtocolVersion()
{
	return this->protocolVersion;
}

const char *RakNetOfflineMessage::GetMinecraftVersion()
{
	return this->minecraftVersion;
}

unsigned int RakNetOfflineMessage::GetOnlinePlayers()
{
	return this->onlinePlayers;
}

unsigned int RakNetOfflineMessage::GetMaxPlayers()
{
	return this->maxPlayers;
}

uint64_t RakNetOfflineMessage::GetUniqueID()
{
	return this->uniqueID;
}

char *RakNetOfflineMessage::GetSecondMotd()
{
	return this->secondMotd;
}

const char *RakNetOfflineMessage::GetGameMode()
{
	return this->gameMode;
}

#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
char RakNetOfflineMessage::GetGameModeInInt()
{
	return this->gameModeInInt;
}

unsigned short RakNetOfflineMessage::GetPortv4()
{
	return this->portv4;
}

unsigned short RakNetOfflineMessage::GetPortv6()
{
	return this->portv6;
}
#endif

RakString RakNetOfflineMessage::ToString()
{
	RakString value(this->edition);
	value += ";";
	value += this->motd;
	value += ";";
	value += std::to_string(this->protocolVersion).c_str();
	value += ";";
	value += this->minecraftVersion;
	value += ";";
	value += std::to_string(this->onlinePlayers).c_str();
	value += ";";
	value += std::to_string(this->maxPlayers).c_str();
	value += ";";
	value += std::to_string(this->uniqueID).c_str();
	value += ";";
	value += this->secondMotd;
	value += ";";
	value += this->gameMode;
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	value += ";";
	value += std::to_string(this->gameModeInInt);
	value += ";";
	value += std::to_string(this->portv4);
	value += ";";
	value += std::to_string(this->portv6);
#endif
	return value;
}