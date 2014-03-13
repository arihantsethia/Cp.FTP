#include "cp_ftp_client.h"

FTPClient::FTPClient(std::string host_name, int port_number, std::string user_name, std::string password){
	std::cout<<"\nSi.FTP-Client Started\n\n";
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
		control_socket = new ClientSocket(host,port);
		*control_socket>>response;
		std::cout<<FTPResponse(response).parseResponse();

		request = FTPRequest("USER",user).getRequest();
		*control_socket<< request;
		*control_socket>>response;

		request = FTPRequest("PASS",passwd).getRequest();
		*control_socket<<request;
		*control_socket>>response;

		std::cout<<FTPResponse(response).parseResponse(return_code);
		if(return_code != 230){
			std::cout<<"Re-enter User Name : ";
			std::cin>>user;
			std::cout<<"Re-enter Password : ";
			passwd = getPassword();
			start();
		}
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

void FTPClient::communicate(){
	std::string command,cmd;
	std::vector<std::string> flags,args;

	while(1){
		flags.clear();
		args.clear();
		std::cout<<"Cp.FTP > ";
		std::getline(std::cin,command);
		cmd = parseCommand(command,flags,args);

		if(cmd=="get" && (args.size() == 1 || args.size()==2) && flags.size()==0){
			std::string curr_loc = _pwd(false);
			std::string curr_loc_server = pwd(false);

			if(args.size()==2){
				if(_cd(args[1],false)!= 1){
					std::cout<<"Destination doesn't exist. File Transfer couldn't be done."<<std::endl;
					continue;
				}
			}

			std::string filePath = getFilePath(args[0]);

			if(filePath!=""){
				if(cd(filePath,false) != 250){
					_cd(curr_loc,false);
					std::cout<<"Destination doesn't exist. File Transfer couldn't be done."<<std::endl;
					continue;
				}
			}

			get(getFileName(args[0]));
			cd(curr_loc_server,false);
			_cd(curr_loc,false);
		}
		else if(cmd=="put" && (args.size() == 1 || args.size()==2) && flags.size()==0){
			std::string curr_loc = pwd(false);

			if(args.size()==2){
				if(cd(args[1],false)!= 250){
					std::cout<<"Destination doesn't exist. File Transfer couldn't be done."<<std::endl;
					continue;
				}
			}

			put(args[0]);
			cd(curr_loc,false);
		}
		else if(cmd=="pwd" && args.size() == 0 && flags.size() == 0){
			pwd();
		}
		else if(cmd=="cd" && flags.size() == 0 && args.size() == 1){
			cd(args[0]);
		}
		else if(cmd=="ls"){			
			if(pasv()!=227){
				std::cout<<"Couldn't get file listing."<<std::endl;
				continue;
			}
			ls(flags,args);
		}
		else if(cmd=="mkdir" && args.size() == 1 && flags.size() == 0){
			bool flag = true;
			std::string curr_loc = pwd(false);
			std::vector<string> dirs = tokenize(args[0],"/");

			for(int i=0;i<dirs.size();i++){
				if(mkd(dirs[i],false)!=257 && cd(dirs[i],false) != 250){
					std::cout<<"Couldn't create the required directory structure."<<std::endl;
					flag = false;
					break;
				}				
			}

			cd(curr_loc,false);

			if(flag){
				std::cout<<"Directory structure "<<args[0]<< " successfully created."<<std::endl;
			}
		}
		else if(cmd=="!pwd" && args.size() == 0 && flags.size()==0){
			_pwd();
		}
		else if(cmd=="!cd" && flags.size() == 0 && args.size() == 1){
			_cd(args[0]);
		}
		else if(cmd=="!ls"){
			_ls(flags,args);
		}
		else if(cmd=="!mkdir" && args.size() == 1 && flags.size() == 0){
			bool flag = true;
			std::string curr_loc = _pwd(false);

			std::vector<string> dirs = tokenize(args[0],"/");
			for(int i=0;i<dirs.size();i++){
				int status = _mkd(dirs[i],false);
				status = status | _cd(dirs[i],false);
				if(_mkd(dirs[i],false)!=1 && _cd(dirs[i],false) != 1){
					std::cout<<"Couldn't create the required directory structure."<<std::endl;
					flag = false;
					break;
				}				
			}

			_cd(curr_loc,false);
			if(flag){
				std::cout<<"Directory structure "<<args[0]<< " successfully created."<<std::endl;
			}
		}
		else if(cmd=="quit"){
			if(quit()){
				(*control_socket).close();
				return;
			}else{
				std::cout<<"Couldn't terminate the session."<<std::endl;
			}
		}
		else if(cmd=="help"){
			help();
		}
		else{
			std::cout<<"Command improperly formatted. Type \"help\" for reference."<<std::endl;
		}
	}
}

void FTPClient::get(std::string args){
	std::ofstream out(getFileName(args).c_str(), std::ios::out| std::ios::binary);
	string data;
	double length;
	if(out){
		request =  FTPRequest("TYPE","I").getRequest();
		try{
			*control_socket<<request;
			*control_socket>>response;
			ftp_response.setResponse(response);
			std::cout<<ftp_response.parseResponse(return_code);
			if(return_code != 200){
				return;
			}
		} catch(SocketException &e){
			std::cout<<"Exception occurred : "<<e.description()<<std::endl;
			return;
		}

		if(pasv()!=227){
			std::cout<<"File Transfer couldn't be initiated."<<std::endl;
			return;
		}
		
		request =  FTPRequest("RETR",getFileName(args)).getRequest();
		try{
			*control_socket<<request;
			*control_socket>>response;
			std::cout<<FTPResponse(response).parseResponse(return_code);
			if(return_code != 150){
				return;
			}
		} catch(SocketException &e){
			std::cout<<"Exception occurred : "<<e.description()<<std::endl;
			return;
		}

		std::cout<<"Receiving File : "<<getFileName(args)<<" ...."<<std::endl;
		
		while (1){
			data = "";
			*data_socket>>data;
			length = length + data.length();
			if(data.length()==0){
				break;
			}
			out<<data;
		}

		(*data_socket).close();
		*control_socket>>response;
		out.close();
		int status_code,precision;
		FTPResponse ftp_response(response);
		std::cout<<ftp_response.parseResponse(status_code);

		if(status_code == 226){
			std::string size_msg = "bytes";
			precision = 0;

			if(length/1024 >= 1){
				size_msg = "KB";
				length /= 1024;
				precision = 2;

				if(length/1024 >= 1){
					size_msg="MB";
					length /= 1024;

					if(length/1024 >= 1){
						size_msg="GB";
						length /= 1024;
					}
				}
			}

			std::cout<<std::setprecision(precision)<<std::fixed<<"Succefully transferred file : "<<getFileName(args)<< " ( " << length <<size_msg<< " )"<<std::endl;
		}
	}else{
		std::cout<<"File : "<<getFileName(args)<<" couldn't be created."<<std::endl;
	}
}

void FTPClient::put(std::string args){
	std::ifstream in(args.c_str(), std::ios::in | std::ios::binary | std::ios::ate);
	
	if(in){
		long length = in.tellg();
		in.seekg (0, in.beg);
		request =  FTPRequest("TYPE","I").getRequest();

		try{
			*control_socket<<request;
			*control_socket>>response;
			ftp_response.setResponse(response);
			std::cout<<ftp_response.parseResponse(return_code);
			if(return_code != 200){
				return;
			}
		} catch(SocketException &e){
			std::cout<<"Exception occurred : "<<e.description()<<std::endl;
			return;
		}

		if(pasv()!=227){
			std::cout<<"File Transfer couldn't be initiated."<<std::endl;
			return;
		}
		
		request =  FTPRequest("STOR",getFileName(args)).getRequest();
		try{
			*control_socket<<request;
			*control_socket>>response;
			ftp_response.setResponse(response);
			std::cout<<ftp_response.parseResponse(return_code);
			if(return_code != 150){
				return;
			}
		} catch(SocketException &e){
			std::cout<<"Exception occurred : "<<e.description()<<std::endl;
			return;
		}

		std::cout<<"Sending File : "<<getFileName(args)<<" ...."<<std::endl;
		string data;

		double c_length=length;
		
		while (length>0){
			int read_sz = MAXRECV<length ? MAXRECV : length;
			char buf[MAXRECV+1];
			in.read(buf,read_sz);
			data.assign(buf,read_sz);
			*data_socket<<data;
			length -= read_sz;
		}

		(*data_socket).close();
		*control_socket>>response;
		in.close();
		int status_code,precision;
		FTPResponse ftp_response(response);
		std::cout<<ftp_response.parseResponse(status_code);
		if(status_code == 226){
			std::string size_msg = "bytes";
			precision = 0;

			if(c_length/1024 >= 1){
				size_msg = "KB";
				c_length /= 1024;
				precision = 2;

				if(c_length/1024 >= 1){
					size_msg="MB";
					c_length /= 1024;

					if(c_length/1024 >= 1){
						size_msg="GB";
						c_length /= 1024;
					}
				}
			}
			std::cout<<std::setprecision(precision)<<std::fixed<<"Succefully transferred file : "<<getFileName(args)<< " ( " << c_length <<size_msg<< " )"<<std::endl;
		}
	}else{
		std::cout<<"File : "<<getFileName(args)<<" doesn't exist. Please check the filename."<<std::endl;
	}

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

int FTPClient::pasv(){
	request = FTPRequest("PASV").getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		FTPResponse ftp_response(response);
		ftp_response.setResponse(response);
		std::cout<<ftp_response.parseResponse(return_code);
		if(return_code != 227){
			return return_code;
		}
		int port = ftp_response.getPort();
		data_socket = new ClientSocket(host,port);
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return -1;
	}
	return return_code;
}

std::string FTPClient::pwd( bool print){
	request = FTPRequest("PWD","").getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		ftp_response.setResponse(response);		
		std::string p_response = ftp_response.parseResponse(return_code);
		if(print){
			std::cout<<p_response;
		}
		return p_response.substr(1,p_response.length()-4);
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return "" ;
	}
}

int FTPClient::cd(std::string args,bool print){
	request = FTPRequest("CWD",args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		ftp_response.setResponse(response);
		if(print){
			std::cout<<ftp_response.parseResponse(return_code);
		}
		return ftp_response.returnCode();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return -1;
	}
}

int FTPClient::mkd(std::string args,bool print){
	request = FTPRequest("MKD",args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		ftp_response.setResponse(response);
		if(print){
			std::cout<<ftp_response.parseResponse(return_code);
		}
		return ftp_response.returnCode();
	} catch(SocketException &e){
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return -1;
	}
}

void FTPClient::ls(std::vector<std::string> flags, std::vector<std::string> args, bool print){
	request = FTPRequest("LIST",flags,args).getRequest();

	try{
		*control_socket<<request;
		*control_socket>>response;
		ftp_response.setResponse(response);
		std::string p_response= ftp_response.parseResponse(return_code);
		if(print){
			std::cout<<p_response;
		}
		if(return_code != 150){
			return;
		}

		while(1){
			response = "";
			*data_socket >> response;
			if(response.length()==0){
				break;
			}
			if(print){
				std::cout<<response;
			}																				
		}
		(*control_socket)>>response;
		ftp_response.setResponse(response);
		p_response= ftp_response.parseResponse(return_code);		
		if(print){
			std::cout<<p_response;
		}
	} catch(SocketException &e){
		(*data_socket).close();
		std::cout<<"Exception occurred : "<<e.description()<<std::endl;
		return ;
	}
}

std::string FTPClient::_pwd(bool print){
	request = FTPRequest("pwd","").getRequest("\n");
	response = exec_cmd("pwd",request);
	if(print){
		std::cout<<response;
	}
	return response.substr(1,response.length()-3);
}

int FTPClient::_cd(std::string args, bool print){
	response = exec_cmd("cd",args,return_code);
	if(print){
		std::cout<<response;
	}
	return return_code;
}

void FTPClient::_ls(std::vector<std::string> flags, std::vector<std::string> args, bool print){
	request = FTPRequest("ls",flags,args).getRequest("\n");
	response = exec_cmd("ls",request);
	if(print){
		std::cout<<response;
	}
}

int FTPClient::_mkd(std::string args,bool print){
	response = exec_cmd("mkdir",args,return_code);
	if(print){
		std::cout<<response;
	}
	return return_code;
}

void FTPClient::help(){
	string cmd_desc = "";

	cmd_desc += "put [sourcepath]filename [destination] : filename to upload the file(relative or absolute address) to the server [at the specified destination].\n" ;
	cmd_desc += "get [sourcepath]filename [destination] : filename to download the file(relative or absolute address) from the server [at the specified destination].\n" ;
	cmd_desc += "ls [flags(like -l, -a, etc)] [args1 args2...] : to list the files under the present directory or mentoned directories in args[] of the server.\n" ;
	cmd_desc += "cd destiation : to change the present working directory of the server to destination.\n" ;
	cmd_desc += "pwd : to display the present working directory of the server.\n" ; 
	cmd_desc += "!ls [flags(like -l, -a, etc)] [args1 args2...] : to list the files under the present directory or mentoned directories in args[] of your machine.\n" ;
	cmd_desc += "!cd destiation : to change the present working directory of your machine to destination.\n" ;
	cmd_desc += "!pwd : to display the present working directory of your machine.\n" ; 
	cmd_desc += "quit : to quit from ftp session and return to Unix prompt.\n";
	
	std::cout<<cmd_desc<<std::endl;
}