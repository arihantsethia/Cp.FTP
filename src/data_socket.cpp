// Class file of Server Socket 

#include "data_socket.h"

//Constructor function to create a socket.
DataSocket::DataSocket(){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
}

//Constructor function to create, bind and listen a socket on a particular PORT
DataSocket::DataSocket(std::string host, int port){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
	int ip = hostlookup(host);
	if(!Socket::connect(ip,port)){
		throw SocketException(strerror(errno));
	}
}

DataSocket::~DataSocket(){

}

//Function to send data from socket 
DataSocket& DataSocket::operator << (std::string& s){
	if(Socket::send(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Function to recv data from socket
DataSocket& DataSocket::operator >> (std::string& s) {
	if(Socket::recv(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Fuction to return the FD of the socket.
int DataSocket::fd(){
	return Socket::fd();
}

// Function to accept the incoming socket connection
void DataSocket::accept(DataSocket& _socket){
	if(!Socket::accept(_socket)){
		throw SocketException(strerror(errno));
	}
}

//Function to close the socket.
void  DataSocket::close(){
	if(!Socket::close()){
		throw SocketException(strerror(errno));
	}
}


int DataSocket::hostlookup(std::string h){
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