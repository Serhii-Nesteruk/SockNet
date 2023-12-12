#pragma once

#include "Ws.h"
#include "../Utils/Singleton.h" // TODO:

class Wsa : public Utils::Singleton<Wsa>
{
public:
	void initialize()
	{
		Ws::init(ws);
	}

	void cleanup()
	{
		WSACleanup();
	}

private:
	bool wasInitialized{ false };
	WSAData ws;
};
