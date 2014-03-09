#ifndef SiFTP_RESPONSE_H
#define SiFTP_RESPONSE_H

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

class FTPResponse {
private:
	std::string _msg;
	std::string status_code;

	void setResponse(std::string);

public:

	FTPResponse();
	FTPResponse(std::string response);
	~FTPResponse();
	std::string parseResponse();
	std::string parseResponse(int&);

};

#endif