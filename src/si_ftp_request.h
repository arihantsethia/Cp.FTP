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
	void setRequest(std::string,std::string);
	void setRequest(std::string, vector<std::string>);
	void setRequest(std::string, vector<std::string>, vector<std::string>);

public:

	FTPRequest();
	FTPRequest(std::string);
	FTPRequest(std::string,std::string);
	FTPRequest(std::string, vector<std::string>);
	FTPRequest(std::string, vector<std::string>, vector<std::string>);
	~FTPRequest();
	std::string getRequest();

};

#endif