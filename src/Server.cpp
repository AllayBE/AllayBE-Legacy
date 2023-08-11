#include <Server.h>

Server::Server()
{
	this->logger = new Logger("Server", false);
	SocketDescriptor *descriptor = new SocketDescriptor(19132, "0.0.0.0");
	RakNetOfflineMessage *offlineMessage = new RakNetOfflineMessage(
		"MCPE",
		"AllayBE Motd",
		MINECRAFT_PROTOCOL_VERSION,
		MINECRAFT_VERSION,
		0,
		10,
		this->rakNetInterface->Generate64BitUnqiueNumber(),
		"AllayBE SubMotd",
		"Creative"
	);
	this->rakNetInterface = new RakNetInterface(descriptor, offlineMessage);
	this->rakNetInterface->Initialize();
}

RAK_THREAD_DECLARATION(RakNetPongHandle)
{
	RakNetInterface *rakNetInterface = (RakNetInterface *)arguments;

	while (rakNetInterface->isRunning()) {
		rakNetInterface->UpdatePong();
	}
	return 0;
}

bool Server::IsWindows()
{
	bool value = false;
#ifdef _WIN32
	value = true;
#endif
	return value;
}

void Server::Start()
{
	this->logger->Info("Starting Server...\n");
	if (!this->rakNetInterface->Start()) {
		return;
	}

	unsigned threadPriority = 1000;
#ifdef _WIN32
	threadPriority = THREAD_PRIORITY_NORMAL;
#endif

	int errorCode = RakThread::Create(RakNetPongHandle, this->rakNetInterface, threadPriority);

	if (errorCode != 0)
	{
		this->Stop();
		return;
	}

	this->logger->Info("Server started!\n");

	while (true)
	{
		this->rakNetInterface->Handle();
	}
}

void Server::Stop()
{
	this->rakNetInterface->Shutdown();
}

Logger *Server::GetLogger()
{
	return this->logger;
}

RakNetInterface *Server::GetRakNetInterface()
{
	return this->rakNetInterface;
}
