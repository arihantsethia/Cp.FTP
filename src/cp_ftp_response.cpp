// Class file for ftp response class functions.
#include "headers/cp_ftp_response.h"

// Default constructor function of ftp response class.
FTPResponse::FTPResponse() {

}

// Default destructor function of ftp response class.
FTPResponse::~FTPResponse(){
	_msg = "";
	status_code = "";
}

// Default constructor function of ftp response class with string response as function argument.
FTPResponse::FTPResponse(std::string response) {
	_msg = response;
	status_code = "";
}

// Default constructor function of ftp response class with string response as function argument.
FTPResponse::FTPResponse(std::string code,std::string msg){
	status_code = code;
	_msg = msg;
}

// set response function of ftp response class with string response as function argument.
void FTPResponse::setResponse(std::string response) {
	_msg = response;
	status_code = "";
}

// parse response function of ftp response class.
std::string FTPResponse::parseResponse() {
	std::string::size_type beginPos = _msg.find_first_not_of(" ", 0);
	if(isdigit(_msg[beginPos])){
		std::string::size_type endPos = _msg.find(" ",beginPos);
		status_code = _msg.substr(beginPos,endPos-beginPos);
		beginPos = _msg.find_first_not_of(" ", endPos);
	}
	return _msg.substr(beginPos);
}

// parse response function of ftp response class with code as function argument.
std::string FTPResponse::parseResponse(int& code) {
	std::string response = parseResponse();
	code = atoi(status_code.c_str());
	return response;
}

// form response function of ftp response class.
std::string FTPResponse::formResponse(){
	return status_code+" "+_msg+"\r\n";
}

// return code function of ftp response class.
int FTPResponse::returnCode() {
	if(status_code == "")
		std::string response = parseResponse();
	return atoi(status_code.c_str());
}

//	return port number.
int FTPResponse::getPort() {
	std::string::size_type beginPos = _msg.find("(", 0);
	std::string::size_type endPos = _msg.find(")",beginPos);
	std::string port_string = _msg.substr(beginPos+1,endPos-beginPos-1);
	int count = 0;
	std::string host="";
	beginPos = 0;
	while(count<4){
		beginPos = port_string.find(",", beginPos);
		if(count<3)
			port_string[beginPos] = '.';
		count++;
	}
	host = port_string.substr(0,beginPos);
	port_string = port_string.substr(beginPos+1);
	beginPos = port_string.find(",");
	int port = 256 * atoi(port_string.substr(0,beginPos).c_str());
	port += atoi(port_string.substr(beginPos+1).c_str());
	return port;
}
