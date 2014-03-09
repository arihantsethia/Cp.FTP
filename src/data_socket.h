#ifndef SERVERSOCKET_CLASS
#define SERVERSOCKET_CLASS

#include "socket.h"
#include "socket_exception.h"

class DataSocket : private Socket{
private:
	int hostlookup(std::string);
	
public:
	DataSocket();
	DataSocket(std::string,int);
	~DataSocket();
	DataSocket& operator << (std::string&);
	DataSocket& operator >> ( std::string& );
	void accept(DataSocket&);
	void close();
	int fd();
};

#endif