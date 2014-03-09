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
	else if(_cmd == "PORT"){
		std::stringstream arg;
		for(int i=0;i<_arg.length();i++){
			if(_arg[i]=='.')
				arg<<',';
			if(_arg[i]==':'){
				arg<<',';
				int port = atoi(_arg.substr(i+1).c_str());
				arg<<port/256<<","<<port%256;
				break;
			}else{
				arg<<_cmd[i];
			}
		}
		return _cmd+" "+arg.str()+"\r\n";
	}
	else{
		return _cmd + " " + _arg + "\r\n";
	}
}
