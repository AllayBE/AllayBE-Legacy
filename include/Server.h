#pragma once

#include <console\Logger.h>
#include <cstdint>
#include <network/minecraft/MinecraftVersionDefinitions.h>
#include <network/raknet/RakNetInterface.h>
#include <network/raknet/RakNetOfflineMessage.h>
#include <RakThread.h>

class Server
{
protected:
	Logger *logger;
	RakNetInterface *rakNetInterface;

public:
	Server();

	bool IsWindows();

	void Start();
	void Stop();

	Logger *GetLogger();
	RakNetInterface *GetRakNetInterface();
};