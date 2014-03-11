#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "socket_exception.h"

static int RVAL = 0;

bool is_number(std::string);
std::string exec_cmd(std::string, std::string,int& code = RVAL);
std::string getFileName(std::string);
std::string getPassword();
std::vector<std::string> tokenize(std::string, std::string);

#endif