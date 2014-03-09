#ifndef SOCKET_CLASS
#define SOCKET_CLASS

#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BACKLOG 20
#define MAXRECV	2048

class Socket{
private:
	int _sockfd;
	struct sockaddr_in _addr;
	bool is_valid();
public:
	Socket();
	~Socket();
	bool create();
	bool bind(int);
	bool connect(int,int);
	bool listen();
	bool accept(Socket&);
	int send(std::string);
	int recv(std::string&);
	bool close();
	int fd();
	void fd(int);
	int port();
};

#endif