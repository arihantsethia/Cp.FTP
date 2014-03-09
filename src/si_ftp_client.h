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

#include "si_ftp_request.h"
#include "si_ftp_response.h"
#include "server_socket.h"
#include "client_socket.h"
#include "socket_exception.h"

class FTPClient{
private:
	std::string host;
	std::string user;
	std::string passwd;	
	int ip;
	int port;

	ClientSocket *control_socket;
	ServerSocket *data_socket;
	std::string request;
	std::string response;

	void help();
	void get();
	void put();
	void cd();
	void pwd();
	void ls();
	void _cd();
	void _pwd();
	void _ls();
	bool quit();

public:
	FTPClient(std::string, int, std::string, std::string);
	~FTPClient();

	void start();
	void communicate();

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