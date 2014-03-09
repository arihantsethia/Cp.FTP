#ifndef CONTROLSOCKET_CLASS
#define CONTROLSOCKET_CLASS

#include "socket.h"
#include "socket_exception.h"

class ControlSocket : private Socket{
	int hostlookup(std::string);
public:
	ControlSocket();
	ControlSocket(int, int);
	ControlSocket(std::string, int);
	~ControlSocket();
	ControlSocket& operator << (std::string&);
	ControlSocket& operator >> (std::string&);
	void close();
	int fd();
};

#endif