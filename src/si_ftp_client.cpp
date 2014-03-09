#include "si_ftp_client.h"

FTPClient::FTPClient(std::string host_name, int port_number, std::string user_name, std::string password){
	std::cout<<"Si.FTP-Client Started\n";
	host = host_name;
	user = user_name;
	passwd = password;
	port = port_number;
}

FTPClient::~FTPClient() {

}

void FTPClient::start(){
	std::cout<<"Connecting to Host : "<< host<< " Port : "<<port<<std::endl;

	try{
		control_socket = new ControlSocket(host,port);
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();

		request = FTPRequest("USER",user).getRequest();
		*control_socket<< request;
		*control_socket>>response;

		request = FTPRequest("PASS",passwd).getRequest();
		*control_socket<<request;
		*control_socket>>response;

		std::cout<<FTPResponse(response).parseResponse();

	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::communicate(){
	std::string command,cmd;
	std::vector<std::string> flags,args;

	while(1){
		std::cout<<"SiFTP > ";
		std::getline(std::cin,command);
		cmd = parseCommand(command,flags,args);
		if(cmd=="pwd" && args.size() == 0){
			pwd(flags);
		}
		else if(cmd=="cd"){
			cd(flags,args);
		}
		else if(cmd=="ls"){
			pasv();
			ls(flags,args);
		}
		else if(cmd=="quit"){
			if(quit()){
				(*control_socket).close();
				return;
			}else{
				std::cout<<"Couldn't terminate the session."<<std::endl;
			}
		}
		else if(cmd=="help" || 1){
			help();
		}
		flags.clear();
		args.clear();
	}
}

void FTPClient::get(){

}

void FTPClient::put(){

}

bool FTPClient::quit(){
	request = FTPRequest("QUIT").getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return false;
	}
	return true;
}

void FTPClient::pasv(){
	request = FTPRequest("PASV").getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		FTPResponse ftp_response(response);
		std::cout<<ftp_response.parseResponse();
		int port = ftp_response.getPort();
		data_socket = new DataSocket(host,port);
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return;
	}
}

void FTPClient::pwd(std::vector<std::string> flags){
	request = FTPRequest("PWD",flags).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::cd(std::vector<std::string> flags, std::vector<std::string> args){
	request = FTPRequest("CWD",flags,args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::ls(std::vector<std::string> flags, std::vector<std::string> args){
	request = FTPRequest("LIST",flags,args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
		*data_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::_pwd(std::vector<std::string> flags){
	request = FTPRequest("PWD",flags).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::_cd(std::vector<std::string> flags, std::vector<std::string> args){
	request = FTPRequest("CWD",flags,args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::_ls(std::vector<std::string> flags, std::vector<std::string> args){
	request = FTPRequest("LIST",flags,args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::help(){
	string cmd_desc = "";

	cmd_desc += "put filename to upload a file named filename to the server\n" ;
	cmd_desc += "get filename to download a file named filename from the server\n" ;
	cmd_desc += "ls to list the files under the present directory of the server\n" ;
	cmd_desc += "cd to change the present working directory of the server\n" ;
	cmd_desc += "pwd to display the present working directory of the server\n" ; 
	cmd_desc += "!ls to list the files under the present directory of the client\n" ;
	cmd_desc += "!cd to change the present directory of the client\n" ;
	cmd_desc += "!pwd to display the present working directory of the client\n" ;
	cmd_desc += "quit to quit from ftp session and return to Unix prompt.\n";
	
	std::cout<<cmd_desc<<std::endl;
}

std::string FTPClient::parseCommand(std::string command, std::vector<std::string>& flags, std::vector<std::string>& args){
	std::string::size_type beginPos = command.find_first_not_of(" \r\n", 0);
	std::string::size_type endPos = command.find_first_of(" \r\n",beginPos);
	std::string cmd = command.substr(beginPos,endPos-beginPos);

	while(beginPos!=std::string::npos){
		beginPos = command.find_first_not_of(" \r\n", endPos);
		endPos = command.find_first_of(" \r\n",beginPos);
		if(beginPos!=std::string::npos){
			if(command[beginPos] == '-'){
				flags.push_back(command.substr(beginPos,endPos-beginPos));
			}else{
				args.push_back(command.substr(beginPos,endPos-beginPos));
			}
		}
	}
	return cmd;
}