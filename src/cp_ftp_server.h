#ifndef SiFTP_Server_H
#define SiFTP_Server_H

#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string>
#include <map>
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
#include "socket_exception.h"
#include "cp_ftp_request.h"
#include "cp_ftp_response.h"
#include "utility.h"

typedef std::map<std::string, pair<std::string, std::string> > LoginInfo;

class FTPServer{
private:
	int port;

	void help();
	void get(std::string);
	void put(std::string);
	void add();
	int ls(std::vector<std::string>, std::vector<std::string>, std::string&, bool print = false);
	std::string syst(bool print = false);
	std::string pwd(std::vector<std::string>, bool print = false);
	int cd(std::string, bool print = false);
	int mkd(std::string, std::string&, bool print= false);
	int pasv();
	bool quit();
	LoginInfo formLoginInfoList();
	void communicate(ServerSocket *);

	//std::string parseCommand(std::string, std::vector<std::string>&, std::vector<std::string>&);

public:
	FTPServer(int);
	~FTPServer();
	void start();
};

#endif