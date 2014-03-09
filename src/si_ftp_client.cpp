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
	std::string command;
	while(1){
		std::cout<<"SiFTP > ";
		std::cin>>command;
		if(command=="pwd"){
			pwd();
		}
		else if(command=="ls"){
			ls();
		}
		else if(command=="quit"){
			if(quit()){
				(*control_socket).close();
				return;
			}else{
				std::cout<<"Couldn't terminate the session."<<std::endl;
			}
		}
		else if(command=="help" || 1){
			help();
		}
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

void FTPClient::pwd(){
	request = FTPRequest("PWD").getRequest();
	try{
		*control_socket<<request;		
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::cd(){
	request = FTPRequest("CWD").getRequest();
	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::ls(){
	request = FTPRequest("LIST").getRequest();
	try{
		*control_socket<<request;		
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::_pwd(){
	request = FTPRequest("PWD").getRequest();
	try{
		*control_socket<<request;		
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::_cd(){
	request = FTPRequest("CWD").getRequest();
	try{
		*control_socket<<request;
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::_ls(){
	request = FTPRequest("LIST").getRequest();
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