#include "cp_ftp_response.h"

FTPResponse::FTPResponse() {

}

FTPResponse::~FTPResponse(){
	_msg = "";
	status_code = "";
}

FTPResponse::FTPResponse(std::string response) {
	_msg = response;
	status_code = "";
}

FTPResponse::FTPResponse(std::string code,std::string msg){
	status_code = code;
	_msg = msg;
}

void FTPResponse::setResponse(std::string response) {
	_msg = response;
	status_code = "";
}

std::string FTPResponse::parseResponse() {
	std::string::size_type beginPos = _msg.find_first_not_of(" ", 0);
	if(isdigit(_msg[beginPos])){
		std::string::size_type endPos = _msg.find(" ",beginPos);
		status_code = _msg.substr(beginPos,endPos-beginPos);
		beginPos = _msg.find_first_not_of(" ", endPos);
	}
	return _msg.substr(beginPos);
}

std::string FTPResponse::parseResponse(int& code) {
	std::string response = parseResponse();
	code = atoi(status_code.c_str());
	return response;
}

std::string FTPResponse::formResponse(){
	return status_code+" "+_msg+"\r\n";
}

int FTPResponse::returnCode() {
	if(status_code == "")
		std::string response = parseResponse();
	return atoi(status_code.c_str());
}

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
