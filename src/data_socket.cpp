// Class file of Server Socket 

#include "data_socket.h"

//Constructor function to create a socket.
DataSocket::DataSocket(){
	if(!Socket::create()){
		throw SocketException(strerror(errno));
	}
}

//Constructor function to create, bind and listen a socket on a particular PORT
DataSocket::DataSocket(int port){
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

