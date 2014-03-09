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

#include "data_socket.h"
#include "control_socket.h"
#include "socket_exception.h"
#include "si_ftp_request.h"
#include "si_ftp_response.h"

class FTPClient{
private:
	std::string host;
	std::string user;
	std::string passwd;	
	int ip;
	int port;

	ControlSocket *control_socket;
	DataSocket *data_socket;
	std::string request;
	std::string response;

	void help();
	void pasv();
	void get();
	void put();
	void cd(std::vector<std::string>, std::vector<std::string>);
	void pwd(std::vector<std::string>);
	void ls(std::vector<std::string>, std::vector<std::string>);
	void _cd(std::vector<std::string>, std::vector<std::string>);
	void _pwd(std::vector<std::string>);
	void _ls(std::vector<std::string>, std::vector<std::string>);
	bool quit();

	std::string parseCommand(std::string command, std::vector<std::string>&, std::vector<std::string>&);

public:
	FTPClient(std::string, int, std::string, std::string);
	~FTPClient();
	void start();
	void communicate();
};

#endif