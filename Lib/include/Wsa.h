#pragma once

#include "Ws.h"
#include "Singleton.h"

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
