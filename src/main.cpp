#include "si_ftp_client.h"
#include "utility.h"

int main(int argc, char* argv[]){
	/*
	int port = atoi(argv[2]);
	if(argc==2){
		FTPServer server();
		server.start();
	}
	std::string x;
	getline(cin,x);
	//std::cout<<chdir(x.c_str());
	std::cout<<exec_cmd(x);
	
	std::cout<<mkdir("tmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);*/
	if(argc==5 || 1){
		FTPClient client("127.0.0.1", 21, "arihant", "Arihant_2537");
		//FTPClient client("10.16.1.44", 21, "vinita", "vini");
		client.start();
		client.communicate();
	}//*/
		
	return 0;
}
