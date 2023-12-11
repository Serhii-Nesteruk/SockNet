#pragma once

#include <WinSock2.h>
#include <string>

// TODO: create SockAddrIPv6 class
namespace Ws
{
	static bool init(WSADATA& ws);

	enum class AddressType
	{
		IPv4 = AF_INET,
		IPv6 = AF_INET6
	};

	class Socket
	{
	public:
		enum class SocketType
		{
			UNDEFINED,
			DGRAM = SOCK_DGRAM,
			STREAM = SOCK_STREAM
		};

		[[nodiscard]] static SOCKET createSocket(const AddressType& addrType,
			const SocketType& sockType,
			int protocol = 0);
		static void bind(SOCKET sock, sockaddr_in* name);
		static void listen(SOCKET sock, int backlog = SOMAXCONN);
		static void connect(SOCKET sock, sockaddr_in* address);
		static void send(SOCKET sock, const char* data, int flags = 0);
		static void recv(SOCKET sock, char* buf, int flags = 0);

		static void closeSocket(SOCKET sock);
		[[nodiscard]] static bool isClosed(SOCKET sock);
		static bool isValid(SOCKET sock);
	};

	class SockAddrIPv4
	{
	public:
		static void setType(const AddressType& addrType, sockaddr_in& sockAddr);
		static void setPort(u_short port, sockaddr_in& sockAddr);
		static void setAddress(const std::string& address, sockaddr_in& sockAddr);

		[[nodiscard]] static std::string getAddress(const sockaddr_in& sockAddr);

		[[nodiscard]] static AddressType getAddrType();
	private:
		static AddressType _addrType; // TODO:
	};

	static void ThrowAnError();
	static void handleSocketError(SOCKET sock);
};