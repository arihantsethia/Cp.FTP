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


#include "../libs/server_socket.h"
#include "../libs/socket_exception.h"
#include "../libs/utility.h"
#include "cp_ftp_request.h"
#include "cp_ftp_response.h"

typedef std::map<std::string, pair<std::string, std::string> > LoginInfo;

class FTPServer{
private:
	int port;

	void help();
	void get(std::string);
	void put(std::string);
	void add();
	int ls(std::string, std::string&, bool print = false);
	std::string syst(bool print = false);
	std::string pwd(bool print = false);
	int cd(std::string, bool print = false);
	int mkd(std::string, std::string&, bool print= false);
	int pasv();
	bool quit();
	int setRootDir(std::string, bool print = false);
	LoginInfo formLoginInfoList();
	void communicate(ServerSocket *);

public:
	FTPServer(int);
	~FTPServer();
	void start();
};

#endif