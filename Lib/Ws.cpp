#include "Ws.h"

#include "../Utils/Utils.h" // TODO:

#include <WS2tcpip.h>
#include <iostream>

SOCKET Ws::Socket::createSocket(const Ws::AddressType& addrType, const Ws::Socket::SocketType& sockType,
	Protocol protocol)
{
	SOCKET tempSocket = socket(static_cast<int>(addrType), static_cast<int>(sockType), static_cast<int>(protocol));
	if (tempSocket == INVALID_SOCKET)
	{
		ThrowAnError();
		WSACleanup();
		return SOCKET();
	}
	return tempSocket;
}

void Ws::Socket::bind(SOCKET sock, sockaddr_in* name)
{
	if (::bind(sock, reinterpret_cast<sockaddr*>(&name), sizeof(*name)) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

void Ws::Socket::listen(SOCKET sock, int backlog)
{
	if (::listen(sock, backlog) < 0)
	{
		handleSocketError(sock);
	}
}
void Ws::Socket::connect(SOCKET sock, sockaddr_in* address)
{
	if (::connect(sock, reinterpret_cast<sockaddr*>(&address), sizeof(*address)) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

void Ws::Socket::send(SOCKET sock, const char* data, int flags)
{
	if (::send(sock, data, sizeof(*data), flags) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

void Ws::Socket::recv(SOCKET sock, char* buf, int flags)
{
	if (::recv(sock, buf, sizeof(*buf), flags) == SOCKET_ERROR)
	{
		handleSocketError(sock);
	}
}

bool Ws::Socket::isValid(SOCKET sock)
{
	return sock != INVALID_SOCKET;
}
void Ws::Socket::closeSocket(SOCKET sock)
{
	::closesocket(sock);
}
bool Ws::Socket::isClosed(SOCKET sock)
{
	return sock == INVALID_SOCKET;
}
SOCKET Ws::Socket::accept(SOCKET sock, sockaddr* addr)
{
	socklen_t addrLen = sizeof(*addr);
	SOCKET tempSock = ::accept(sock, addr, &addrLen);

	if (tempSock == INVALID_SOCKET)
	{
		handleSocketError(tempSock);
	}

	return tempSock;
}

void Ws::SockAddrIPv4::setType(const Ws::AddressType& addrType, sockaddr_in& sockAddr)
{
	if (addrType == AddressType::IPv6)
	{
		throw std::runtime_error("SockAddrIPv4 error: address type must be IPv4");
	}
	sockAddr.sin_family = static_cast<u_short>(addrType);
	_addrType = addrType;
}

void Ws::SockAddrIPv4::setPort(u_short port, sockaddr_in& sockAddr)
{
	sockAddr.sin_port = htons(port);
}

void Ws::SockAddrIPv4::setAddress(const std::string& address, sockaddr_in& sockAddr)
{
	inet_pton(static_cast<int>(_addrType), address.data(), &sockAddr.sin_addr);
}

Ws::AddressType Ws::SockAddrIPv4::getAddrType()
{
	return _addrType;
}

std::string Ws::SockAddrIPv4::getAddress(const sockaddr_in& sockAddr)
{
	std::string buff{ };
	inet_ntop(sockAddr.sin_family, &sockAddr, buff.data(), buff.size());
	return buff;
}

void Ws::ThrowAnError()
{
	int errorCode = WSAGetLastError();
	throw std::runtime_error("WSAStartup failed with error: " + std::to_string(errorCode)
		+ " Message: " + Utils::GetWinSockErrorString(errorCode));
}

void Ws::handleSocketError(SOCKET sock)
{
	ThrowAnError();
	Socket::closeSocket(sock);
	WSACleanup();
}

bool Ws::init(WSADATA& ws)
{
	if (WSAStartup(MAKEWORD(2, 2), &ws) != 0)
	{
		ThrowAnError();
		return false;
	}

	return true;
}

void Ws::SockAddrIPv6::setType(const Ws::AddressType& addrType, sockaddr_in6& sockAddr)
{
	if (addrType == AddressType::IPv4)
	{
		throw std::runtime_error("SockAddrIPv6 error: address type must be IPv6");
	}
	sockAddr.sin6_family = static_cast<u_short>(addrType);
	_addrType = addrType;
}

void Ws::SockAddrIPv6::setPort(u_short port, sockaddr_in6& sockAddr)
{
	sockAddr.sin6_port = htons(port);
}
void Ws::SockAddrIPv6::setAddress(const std::string& address, sockaddr_in6& sockAddr)
{
	inet_pton(static_cast<int>(_addrType), address.data(), &sockAddr.sin6_addr);
}
std::string Ws::SockAddrIPv6::getAddress(const sockaddr_in6& sockAddr)
{
	std::string buff{ };
	inet_ntop(sockAddr.sin6_family, &sockAddr, buff.data(), buff.size());
	return buff;
}
Ws::AddressType Ws::SockAddrIPv6::getAddrType()
{
	return _addrType;
}
