#pragma once

#include <string>
#include <cstdint>
#include <RakMemoryOverride.h>
#include <RakString.h>
#include <vector>

using namespace RakNet;

class RakNetOfflineMessage
{
protected:
	const unsigned char *edition;
	unsigned char *motd;
	unsigned int protocolVersion;
	const unsigned char *minecraftVersion;
	unsigned int onlinePlayers;
	unsigned int maxPlayers;
	long long uniqueID;
	unsigned char *secondMotd;
	const unsigned char *gameMode;
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	char gameModeInInt;
	short portv4;
	short portv6;
#endif
	std::vector<RakString> usedStrings;

public:
	RakNetOfflineMessage(
		const unsigned char *edition,
		unsigned char *motd,
		unsigned int protocolVersion,
		const unsigned char *minecraftVersion,
		unsigned int onlinePlayers,
		unsigned int maxPlayers,
		uint64_t uniqueID,
		unsigned char *secondMotd,
		const unsigned char *gameMode
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
		,
		unsigned char gameModeInInt,
		unsigned short portv4,
		unsigned short portv6
#endif
	);

	void SetMotd(unsigned char *value);
	void SetOnlinePlayers(unsigned int value);
	void SetSecondMotd(unsigned char *value);

	const unsigned char *GetEdition();
	unsigned char *GetMotd();
	unsigned int GetProtocolVersion();
	const unsigned char *GetMinecraftVersion();
	unsigned int GetOnlinePlayers();
	unsigned int GetMaxPlayers();
	uint64_t GetUniqueID();
	unsigned char *GetSecondMotd();
	const unsigned char *GetGameMode();
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	unsigned char GetGameModeInInt();
	unsigned short GetPortv4();
	unsigned short GetPortv6();
#endif

	RakString ToString();
	void FreeMemory();
};