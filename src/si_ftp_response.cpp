#include "si_ftp_response.h"

FTPResponse::FTPResponse() {

}

FTPResponse::~FTPResponse(){
	
}

FTPResponse::FTPResponse(std::string response) {
	_msg = response;
}

void FTPResponse::setResponse(std::string response) {
	_msg = response;
}

std::string FTPResponse::parseResponse() {
	std::string::size_type beginPos = _msg.find_first_not_of(" ", 0);
	std::string::size_type endPos = _msg.find(" ",beginPos);
	status_code = _msg.substr(beginPos,endPos-beginPos);
	beginPos = _msg.find_first_not_of(" ", endPos);
	return _msg.substr(beginPos);
}
