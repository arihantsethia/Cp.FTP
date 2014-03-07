#ifndef SiFTP_Client_H
#define SiFTP_Client_H

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "server_socket.h"
#include "client_socket.h"
#include "socket_exception.h"

class FTPClient{
private:
	void connect(ServerSocket *);

public:
	FTPClient(int);
	~FTPClient();
};

#endif