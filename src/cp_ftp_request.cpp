#include "cp_ftp_request.h"

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
	_arg =  " "+arg;
}

FTPRequest::FTPRequest(std::string cmd, vector<std::string> flags) {
	_cmd = cmd;
	_arg = "";
	for(int i=0;i<flags.size();i++){
		_arg += " " + flags[i];
	}
}

FTPRequest::FTPRequest(std::string cmd, vector<std::string> flags, vector<std::string> args) {
	_cmd = cmd;
	_arg = "";
	for(int i=0;i<flags.size();i++){
		_arg += " " + flags[i];
	}
	for(int i=0;i<args.size();i++){
		_arg += " " + args[i];
	}
}

void FTPRequest::setRequest(std::string cmd) {
	_cmd = cmd;
	_arg = "";
}

void FTPRequest::setRequest(std::string cmd, std::string arg) {
	_cmd = cmd;
	_arg =  " "+arg;
}

void FTPRequest::setRequest(std::string cmd, vector<std::string> flags) {
	_cmd = cmd;
	_arg = "";
	for(int i=0;i<flags.size();i++){
		_arg += " " + flags[i];
	}
}

void FTPRequest::setRequest(std::string cmd, vector<std::string> flags, vector<std::string> args) {
	_cmd = cmd;
	_arg = "";
	for(int i=0;i<flags.size();i++){
		_arg += " " + flags[i];
	}
	for(int i=0;i<args.size();i++){
		_arg += " " + args[i];
	}
}

std::string FTPRequest::getRequest(std::string terminator) {
	if(_arg == "")	{
		return _cmd + terminator;
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
		return _cmd+" "+arg.str()+terminator;
	}
	else{
		return _cmd + _arg + terminator;
	}
}

std::string FTPRequest::getRequest() {
	return getRequest("\r\n");
}