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

	/*
	ftp>put filename to upload a file named filename to the server, 
	ftp>get filename to download a file named filename from the server, 
	ftp>ls to list the files under the present directory of the server, 
	ftp>cd to change the present working directory of the server, 
	ftp>pwd to display the present working directory of the server 
	ftp>!ls to list the files under the present directory of the client, 
	ftp>!cd to change the present directory of the client, 
	ftp>!pwd to display the present working directory of the client, 
	ftp>quit to quit from ftp session and return to Unix prompt. 
	*/
	
};

#endif