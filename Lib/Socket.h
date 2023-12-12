#pragma once

#include "Ws.h"

// TODO: check sockAddrType type (concept)
template <class sockAddrType = sockaddr_in>
class Socket
{
public:
	Socket() = default;
	Socket(Ws::AddressType addressType, Ws::Socket::SocketType socketType,
		Ws::Socket::Protocol protocol = Ws::Socket::Protocol::AUTO,
		SOCKET sockDescriptor = INVALID_SOCKET);
	Socket(const Socket&) = delete;
	Socket& operator=(const Socket&) = delete;
	~Socket();

	void create();
	void bind(sockAddrType sockAddr);
	void connect();
	void close();
	void listen(int backlog = SOMAXCONN);
	Socket accept();

	void sendMessage(SOCKET sockDescriptor, const std::string& message);
	std::string receiveMessage(SOCKET sockDescriptor);

	[[nodiscard]] bool isValid() const;
	[[nodiscard]] bool wasBind() const;
	[[nodiscard]] bool wasCreated() const;
	[[nodiscard]] SOCKET getDescriptor() const;

private:
	bool _wasBind{ false };
	bool _wasCreated{ false };
	sockAddrType _socketAddress;
	SOCKET _socketDescriptor{ INVALID_SOCKET };
	Ws::Socket::Protocol _protocol{ Ws::Socket::Protocol::AUTO };
	Ws::AddressType _addressType{ Ws::AddressType::IPv4 };
	Ws::Socket::SocketType _socketType{ Ws::Socket::SocketType::UNDEFINED };
};

#include "Socket.inl"