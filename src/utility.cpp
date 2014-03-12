#include "utility.h"

int hostlookup(std::string h){
	const char *host = h.c_str();
	struct sockaddr_in inaddr;
	struct hostent *hostp;

	if ((host == NULL) || (*host == '\0')){
		return(INADDR_ANY);
	}

	memset ((char * ) &inaddr, 0, sizeof inaddr);

	if ((int)(inaddr.sin_addr.s_addr = inet_addr(host)) == -1){
		if ((hostp = gethostbyname(host)) == NULL){
			throw SocketException(strerror(errno));
		}
		if (hostp->h_addrtype != AF_INET){ 
			errno = EPROTOTYPE;
			throw SocketException(strerror(errno));
		}
		memcpy((char * ) &inaddr.sin_addr, (char * ) hostp->h_addr, sizeof(inaddr.sin_addr));
	}
	return(inaddr.sin_addr.s_addr);
}

bool is_number(std::string s) {
	for(int i=0; i<s.length(); i++)
		if(!isdigit(s[i]))
			return false ;
	return true ;
}

std::string getPassword(){
	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	std::string pass;
	getline(std::cin, pass);
	getline(std::cin, pass);
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	std::cout<<std::endl;
	return pass;
}

std::string getFileName(std::string str){
	std::string::size_type pos = str.find_last_of("/\\");
	return str.substr(pos+1);
}

std::string getFilePath(std::string str){
	std::string::size_type pos = str.find_last_of("/\\");
	return str.substr(0,pos);
}

std::string exec_cmd(std::string cmd_type,std::string cmd,int& code) {

	FILE *in;
	char buff[2048];
	std::stringstream data;
	code = 0;
	if(cmd_type == "pwd"){
		if (getcwd(buff, sizeof(buff)) != NULL){
			code = 1;
			data<<"\""<<buff<<"\""<<std::endl;
		}
		else {
			data<<"Error : "<<strerror(errno)<<std::endl;
		}
	}
	else if(cmd_type == "cd"){
		if(chdir(cmd.c_str()) == 0){
			code = 1;
			data<<"Succesfully changed to directory : "<<cmd<<"."<<std::endl;
		}else{
			data<<"Error : "<<strerror(errno)<<std::endl;
		}
	}
	else if(cmd_type == "mkdir"){
		if(mkdir(cmd.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == 0){
			code = 1;
			data<<"Succesfully created directory : \""<<system("pwd")+"/"+cmd<<"\"."<<std::endl;
		}else{
			data<<"Error : "<<strerror(errno)<<std::endl;
		}
	}
	else{
		if(!(in = popen(cmd.c_str(), "r"))){
			data<<"Couldn't execute the command : "<<cmd<<std::endl;
		}
		else{
			code = 1;
			while(fgets(buff,sizeof(buff), in)!=NULL){
				data<<buff;
			}

			pclose(in);
		}
	}

	return data.str();
}

std::vector<std::string> tokenize(std::string s, std::string sep){
	// Skip delimiters at beginning.
	std::string::size_type lastPos = s.find_first_not_of(sep, 0);	
	// Find first "non-delimiter", which will be between lastPos and pos
	std::string::size_type pos = s.find_first_of(sep, lastPos); 
	std::vector<std::string> tokens;
	while(pos != std::string::npos || lastPos != std::string::npos){
		tokens.push_back(s.substr(lastPos,(pos - lastPos)));
		// Skip delimiters
		lastPos = s.find_first_not_of(sep, pos);	
		// Find "non-delimiter", which will be between lastPos and pos
		pos = s.find_first_of(sep, lastPos); 
	}
	return tokens;
}

std::string parseCommand(std::string command, std::vector<std::string>& flags, std::vector<std::string>& args){
	std::string::size_type beginPos = command.find_first_not_of(" \r\n", 0);
	std::string::size_type endPos = command.find_first_of(" \r\n",beginPos);
	std::string cmd = command.substr(beginPos,endPos-beginPos);
	while(beginPos!=std::string::npos){
		beginPos = command.find_first_not_of(" \r\n", endPos);
		if(beginPos != std::string::npos){
			endPos = command.find_first_of(" \r\n",beginPos);
			if(endPos != std::string::npos){
				if(command[beginPos] == '-'){
					flags.push_back(command.substr(beginPos,endPos-beginPos));
				}else{
					args.push_back(command.substr(beginPos,endPos-beginPos));
				}
			}else{
				if(command[beginPos] == '-'){
					flags.push_back(command.substr(beginPos));
				}else{
					args.push_back(command.substr(beginPos));
				}
				break;
			}
		}
	}
	return cmd;
}