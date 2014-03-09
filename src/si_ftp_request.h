#ifndef SiFTP_REQUEST_H
#define SiFTP_REQUEST_H

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

using namespace std;

class FTPRequest {
private:
	std::string _cmd;
	std::string _arg;
	void setRequest(std::string);
	void setRequest(std::string, std::string);

public:

	FTPRequest();
	FTPRequest(std::string cmd);
	FTPRequest(std::string cmd, std::string arg);
	~FTPRequest();
	std::string getRequest();

};

#endif