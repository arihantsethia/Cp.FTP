// Class file of Client Socket 

#include "control_socket.h"

ControlSocket::ControlSocket(){

}

//Constructor function to create and connect a socket to particular IP and PORT
ControlSocket::ControlSocket(int ip, int port){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
	if(!Socket::connect(ip,port)){
		throw SocketException(strerror(errno));
	}
}

//Constructor function to create and connect a socket to particular IP and PORT
ControlSocket::ControlSocket(std::string ip_address, int port){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
	int ip = hostlookup(ip_address);
	if(!Socket::connect(ip,port)){
		throw SocketException(strerror(errno));
	}
}


ControlSocket::~ControlSocket(){
	Socket::close();
}

//Function to send data from socket 
ControlSocket& ControlSocket::operator << (std::string& s){
	if(Socket::send(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Function to recv data from socket
ControlSocket& ControlSocket::operator >> (std::string& s){
	if(Socket::recv(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Fuction to return the FD of the socket.
int ControlSocket::fd(){
	return Socket::fd();
}

//Function to close the socket.
void ControlSocket::close(){
	if(!Socket::close()){
		throw SocketException(strerror(errno));
	}
}


int ControlSocket::hostlookup(std::string h){
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