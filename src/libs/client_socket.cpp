// Class file of Client Socket 

#include "client_socket.h"
#include "utility.h"

ClientSocket::ClientSocket(){

}

//Constructor function to create and connect a socket to particular IP and PORT
ClientSocket::ClientSocket(int ip, int port){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
	if(!Socket::connect(ip,port)){
		throw SocketException(strerror(errno));
	}
}

ClientSocket::ClientSocket(std::string ip_address, int port){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
	int ip = hostlookup(ip_address);
	if(!Socket::connect(ip,port)){
		throw SocketException(strerror(errno));
	}
}

ClientSocket::~ClientSocket(){
	Socket::close();
}

//Function to send data from socket 
ClientSocket& ClientSocket::operator << (std::string& s){
	if(Socket::send(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Function to recv data from socket
ClientSocket& ClientSocket::operator >> (std::string& s){
	if(Socket::recv(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Fuction to return the FD of the socket.
int ClientSocket::fd(){
	return Socket::fd();
}

//Function to close the socket.
void ClientSocket::close(){
	if(!Socket::close()){
		throw SocketException(strerror(errno));
	}
}
