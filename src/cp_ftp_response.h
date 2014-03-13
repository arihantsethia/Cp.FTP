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
	FTPResponse(std::string);
	FTPResponse(std::string,std::string);
	~FTPResponse();	
	void setResponse(std::string);
	int returnCode();
	std::string parseResponse();
	std::string parseResponse(int&);
	std::string formResponse();
	int getPort();
};

#endif