#ifndef UTILITY_H
#define UTILITY_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "socket_exception.h"

std::vector<std::string> tokenize(std::string, std::string);
std::string gethostname(std::vector<std::string>);
std::string geturl(std::vector<std::string>);
std::string convertheader(std::string, std::string, std::string, std::string);
int hostlookup(std::string h);
int parseheader(std::string, std::string&, std::string&, std::string&);

#endif