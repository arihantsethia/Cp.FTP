#ifndef CLIENTSOCKET_CLASS
#define CLIENTSOCKET_CLASS

#include "socket.h"
#include "socket_exception.h"

class ClientSocket : private Socket{
public:
	ClientSocket();
	ClientSocket(int ip, int port);
	~ClientSocket();
	ClientSocket& operator << (std::string&);
	ClientSocket& operator >> (std::string&);
	void close();
	int fd();
};

#endif