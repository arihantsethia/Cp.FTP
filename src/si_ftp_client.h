#ifndef SiFTP_Client_H
#define SiFTP_Client_H

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <iomanip>
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

	int return_code;
	ControlSocket *control_socket;
	DataSocket *data_socket;
	std::string request;
	std::string response;
	FTPResponse ftp_response;

	void help();
	void get(std::string);
	void put(std::string);
	void _cd(std::string, bool print = true);
	void _pwd(std::vector<std::string>, bool print = true);
	void _ls(std::vector<std::string>, std::vector<std::string>, bool print = true);
	void ls(std::vector<std::string>, std::vector<std::string>, bool print = true);
	std::string pwd(std::vector<std::string>, bool print = true);
	int mkd(std::string, bool print= false);
	int cd(std::string, bool print = true);
	int pasv();
	bool quit();

	std::string parseCommand(std::string, std::vector<std::string>&, std::vector<std::string>&);
	std::string getFileName(std::string);
	std::vector<std::string> tokenize(std::string, std::string);

public:
	FTPClient(std::string, int, std::string, std::string);
	~FTPClient();
	void start();
	void communicate();
};

#endif