#ifndef SiFTP_RESPONSE_H
#define SiFTP_RESPONSE_H

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <iostream>

using namespace std;

class FTPResponse {
private:
	std::string _msg;
	std::string status_code;
public:
	FTPResponse();
	FTPResponse(std::string response);
	~FTPResponse();	
	void setResponse(std::string);
	int returnCode();
	std::string parseResponse();
	std::string parseResponse(int&);
	int getPort();
	long fileSize();
};

#endif