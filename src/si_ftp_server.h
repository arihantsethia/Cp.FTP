#ifndef SiFTP_Server_H
#define SiFTP_Server_H

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

#include "data_socket.h"
#include "control_socket.h"
#include "socket_exception.h"

class FTPServer{
private:
	void connect(DataSocket *);

public:
	FTPServer(int);
	~FTPServer();

	void cd();
	void pwd();
	void quit();
};

#endif