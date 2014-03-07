#ifndef SERVERSOCKET_CLASS
#define SERVERSOCKET_CLASS

#include "socket.h"
#include "socket_exception.h"

class ServerSocket : private Socket{
public:
	ServerSocket();
	ServerSocket(int port);
	~ServerSocket();
	ServerSocket& operator << (std::string&);
	ServerSocket& operator >> ( std::string& );
	void accept(ServerSocket&);
	void close();
	int fd();
};

#endif