#include "si_ftp_request.h"

FTPRequest::FTPRequest() {

}

FTPRequest::~FTPRequest(){
	
}

FTPRequest::FTPRequest(std::string cmd) {
	_cmd = cmd;
	_arg = "";
}

FTPRequest::FTPRequest(std::string cmd, std::string arg) {
	_cmd = cmd;
	_arg =  arg;
}

void FTPRequest::setRequest(std::string cmd) {
	_cmd = cmd;
	_arg = "";
}

void FTPRequest::setRequest(std::string cmd, std::string arg) {
	_cmd = cmd;
	_arg =  arg;
}


std::string FTPRequest::getRequest() {
	if(_arg == "")	{
		return _cmd + "\r\n";
	}
	else {
		return _cmd + " " + _arg + "\r\n";
	}
}
