#include "Socket.h"

#include <iostream>

template<class sockAddrType>
Socket<sockAddrType>::Socket(Ws::AddressType addressType, Ws::Socket::SocketType socketType,
	Ws::Socket::Protocol protocol, SOCKET sockDescriptor)
	: _addressType(addressType), _socketType(socketType), _protocol(protocol), _socketDescriptor(sockDescriptor)
{
	if (sockDescriptor != INVALID_SOCKET)
	{
		create();
	}
}

template<class sockAddrType>
Socket<sockAddrType>::~Socket()
{
	close();
}

template<class sockAddrType>
void Socket<sockAddrType>::create()
{
	_socketDescriptor = Ws::Socket::createSocket(_addressType, _socketType, _protocol);
	_wasCreated = true;
}

template<class sockAddrType>
void Socket<sockAddrType>::bind(sockAddrType sockAddr)
{
	if (!wasCreated())
	{
		throw std::runtime_error("Socket is not created");
	}
	Ws::Socket::bind(_socketDescriptor, sockAddr);
	_wasBind = true;
}

template<class sockAddrType>
void Socket<sockAddrType>::connect()
{
	if (!wasCreated())
	{
		throw std::runtime_error("Socket is not created");
	}
	if (!wasBind())
	{
		throw std::runtime_error("Socket was not bound");
	}
	Ws::Socket::connect(_socketDescriptor, _socketAddress);
}

template<class sockAddrType>
void Socket<sockAddrType>::listen(int backlog)
{
	if (!wasCreated())
	{
		throw std::runtime_error("Socket is not created");
	}
	if (!wasBind())
	{
		throw std::runtime_error("Socket was not bound");
	}
	Ws::Socket::listen(_socketDescriptor, backlog);
}

template<class sockAddrType>
SOCKET Socket<sockAddrType>::getDescriptor() const
{
	return _socketDescriptor;
}

template<class sockAddrType>
void Socket<sockAddrType>::close()
{
	if (isValid())
	{
		Ws::Socket::closeSocket(_socketDescriptor);
	}
}

template<class sockAddrType>
bool Socket<sockAddrType>::isValid() const
{
	return _socketDescriptor != INVALID_SOCKET;
}

template<class sockAddrType>
bool Socket<sockAddrType>::wasBind() const
{
	return _wasBind;
}

template<class sockAddrType>
bool Socket<sockAddrType>::wasCreated() const
{
	return _wasCreated;
}

// TODO:
template<class sockAddrType>
void Socket<sockAddrType>::sendMessage(SOCKET sockDescriptor, const std::string& message)
{
	size_t messageSize = message.size();
	Ws::Socket::send(sockDescriptor, reinterpret_cast<const char*>(&messageSize));
	Ws::Socket::send(sockDescriptor, message.data());
}

template<class sockAddrType>
std::string Socket<sockAddrType>::receiveMessage(SOCKET sockDescriptor)
{
	int messageSize = 0;
	Ws::Socket::recv(sockDescriptor, reinterpret_cast<char*>(&messageSize));

	std::string message{ };
	message.resize(messageSize);
	Ws::Socket::recv(sockDescriptor, message.data());
	return message;
}

template<class sockAddrType>
Socket<sockAddrType> Socket<sockAddrType>::accept()
{
	sockaddr_in sockAddr;
	SOCKET tempSock = Ws::Socket::accept(tempSock, reinterpret_cast<sockaddr*>(&sockAddr));

	if (tempSock == INVALID_SOCKET)
	{
		Ws::ThrowAnError();
	}

	Socket sock(_addressType, _socketType, _protocol, tempSock);

	return Socket();
}