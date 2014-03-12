// Class file of Server Socket 

#include "server_socket.h"
#include "utility.h"

//Constructor function to create a socket.
ServerSocket::ServerSocket(){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}

}

//Constructor function to create, bind and listen a socket on a particular PORT
ServerSocket::ServerSocket(int port){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}

	if(!Socket::bind(port)){
		throw SocketException(strerror(errno));
	}

	if(!Socket::listen()){
		throw SocketException(strerror(errno));
	}
}

ServerSocket::~ServerSocket(){

}

//Function to send data from socket 
ServerSocket& ServerSocket::operator << (std::string& s){
	if(Socket::send(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Function to recv data from socket
ServerSocket& ServerSocket::operator >> (std::string& s) {
	if(Socket::recv(s)==-1){
		throw SocketException(strerror(errno));
	}
	return *this;
}

//Fuction to return the FD of the socket.
int ServerSocket::fd(){
	return Socket::fd();
}

//Fuction to return the port of the socket.
int ServerSocket::port(){
	return Socket::port();
}

//Fuction to return the host of the socket.
std::string ServerSocket::host(){
	return Socket::host();
}

// Function to accept the incoming socket connection
void ServerSocket::accept(ServerSocket& _socket){
	if(!Socket::accept(_socket)){
		throw SocketException(strerror(errno));
	}
}

//Function to close the socket.
void  ServerSocket::close(){
	if(!Socket::close()){
		throw SocketException(strerror(errno));
	}
}

