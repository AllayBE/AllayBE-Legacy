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
	const char *edition;
	char *motd;
	unsigned int protocolVersion;
	const char *minecraftVersion;
	unsigned int onlinePlayers;
	unsigned int maxPlayers;
	uint64_t uniqueID;
	char *secondMotd;
	const char *gameMode;
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	char gameModeInInt;
	short portv4;
	short portv6;
#endif
	std::vector<RakString> usedStrings;

public:
	RakNetOfflineMessage(
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
	);

	void SetMotd(char *value);
	void SetOnlinePlayers(unsigned int value);
	void SetSecondMotd(char *value);

	const char *GetEdition();
	char *GetMotd();
	unsigned int GetProtocolVersion();
	const char *GetMinecraftVersion();
	unsigned int GetOnlinePlayers();
	unsigned int GetMaxPlayers();
	uint64_t GetUniqueID();
	char *GetSecondMotd();
	const char *GetGameMode();
#ifdef _CONTINUE_RAKNET_OFFLINE_MESSAGE
	char GetGameModeInInt();
	unsigned short GetPortv4();
	unsigned short GetPortv6();
#endif

	RakString ToString();
	void FreeMemory();
};