#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "../libs/socket_exception.h"

static int RVAL = 0;

int hostlookup(std::string);
bool is_number(std::string);

std::string getPassword();
std::string getFileName(std::string);
std::string getFilePath(std::string);
std::string exec_cmd(std::string, std::string,int& code = RVAL);
std::vector<std::string> tokenize(std::string, std::string);
std::string parseCommand(std::string, std::vector<std::string>&, std::vector<std::string>&);

#endif