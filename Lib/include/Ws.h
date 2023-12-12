#pragma once

#include <WinSock2.h>
#include <string>
#include <ws2ipdef.h>

#pragma comment(lib, "ws2_32.lib")

namespace Ws
{
	static bool init(WSADATA& ws);

	enum class AddressType
	{
		IPv4 = AF_INET,
		IPv6 = AF_INET6
	};

	// TODO: implement bind function for IPv6
	class Socket
	{
	public:
		enum class SocketType
		{
			UNDEFINED,
			DGRAM = SOCK_DGRAM,
			STREAM = SOCK_STREAM
		};

		enum class Protocol
		{
			AUTO = 0,
			TCP = IPPROTO_TCP,
			UDP = IPPROTO_UDP,
		};

		// TODO: Replace sockaddr_in with sockaddr
		[[nodiscard]] static SOCKET createSocket(const AddressType& addrType,
			const SocketType& sockType = SocketType::UNDEFINED,
			Protocol protocol = Protocol::AUTO);
		static void bind(SOCKET sock, sockaddr_in* name);
		static void listen(SOCKET sock, int backlog = SOMAXCONN);
		static void connect(SOCKET sock, sockaddr_in* address);
		static void send(SOCKET sock, const char* data, int flags = 0);
		static void recv(SOCKET sock, char* buf, int flags = 0);
		[[nodiscard]] static SOCKET accept(SOCKET sock, sockaddr* addr);

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
		inline static AddressType _addrType = AddressType::IPv4;
	};

	class SockAddrIPv6
	{
	public:
		static void setType(const AddressType& addrType, sockaddr_in6& sockAddr);
		static void setPort(u_short port, sockaddr_in6& sockAddr);
		static void setAddress(const std::string& address, sockaddr_in6& sockAddr);

		[[nodiscard]] static std::string getAddress(const sockaddr_in6& sockAddr);

		[[nodiscard]] static AddressType getAddrType();
	private:
		inline static AddressType _addrType = AddressType::IPv6;
	};

	static void ThrowAnError();
	static void handleSocketError(SOCKET sock);
};