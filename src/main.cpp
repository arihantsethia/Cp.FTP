#include "si_ftp_client.h"

int main(int argc, char* argv[]){
	/*
	int port = atoi(argv[2]);
	if(argc==2){
		FTPServer server();
		server.start();
	}
	*/
	if(argc==5 || 1){
		FTPClient client("127.0.0.1", 21, "arihant", "Arihant_2537");
		//FTPClient client("10.16.1.44", 21, "vinita", "vini");
		//FTPClient client();
		client.start();
		client.communicate();
	}
		
	return 0;
}
