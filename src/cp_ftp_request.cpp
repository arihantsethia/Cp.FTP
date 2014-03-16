// Class file for ftp request functions.
#include "headers/cp_ftp_request.h"

// Default constructor function of ftp request class.
FTPRequest::FTPRequest() {

}

// Default destructor function of ftp request class.
FTPRequest::~FTPRequest(){
	
}

// Constructor function of ftp request class with command as argument.
FTPRequest::FTPRequest(std::string cmd) {
	_cmd = cmd;
	_arg = "";
}

// Constructor function of ftp request class with command and argument as function argument.
FTPRequest::FTPRequest(std::string cmd, std::string arg) {
	_cmd = cmd;
	_arg =  " "+arg;
}

// Constructor function of ftp request class with command and flags as function argument.
FTPRequest::FTPRequest(std::string cmd, vector<std::string> flags) {
	_cmd = cmd;
	_arg = "";
	for(int i=0;i<flags.size();i++){
		_arg += " " + flags[i];
	}
}

// Constructor function of ftp request class with command, argument and flags as function argument.
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

// set request function of ftp request class with command as function argument.
void FTPRequest::setRequest(std::string cmd) {
	_cmd = cmd;
	_arg = "";
}

// set request function of ftp request class with command and argument as function argument.
void FTPRequest::setRequest(std::string cmd, std::string arg) {
	_cmd = cmd;
	_arg =  " "+arg;
}

// set request function of ftp request class with command and flags as function argument.
void FTPRequest::setRequest(std::string cmd, vector<std::string> flags) {
	_cmd = cmd;
	_arg = "";
	for(int i=0;i<flags.size();i++){
		_arg += " " + flags[i];
	}
}

// set request function of ftp request class with command, arguments and flags as function argument.
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

// get request function of ftp request class with terminator as function argument.
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

// get request function of ftp request class without any function argument.
std::string FTPRequest::getRequest() {
	return getRequest("\r\n");
}