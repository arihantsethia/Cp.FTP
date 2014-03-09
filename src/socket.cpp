//  Socket class file which provides wrapper functions to socket functions. 

#include "socket.h"

//Constructor function which intializes _addr to 0 and sets _sockfd to -1
Socket::Socket(){
	memset(&_addr, 0, sizeof _addr);
	_sockfd = -1;
}

//Destructor function
Socket::~Socket(){
	if(is_valid()){
		close();
	}
}

//Checks for a valid _sockfd i.e != -1
bool Socket::is_valid(){
	return _sockfd!=-1;
}

//Return the _sockfd
int Socket::fd(){
	return _sockfd;
}

int Socket::port(){
	struct sockaddr_in local_address;
	socklen_t address_length = sizeof(local_address);
	getsockname(_sockfd, (struct sockaddr*)&local_address, &address_length);
	return ntohs(local_address.sin_port);
}

//Allows to set _sockfd
void Socket::fd(int _fd){
	_sockfd = _fd;
}

//Wrapper function for socket(int domain, int type, int protocol);
bool Socket::create(){
	_sockfd = socket(PF_INET, SOCK_STREAM, 0);

	if(!is_valid()) {
		return false;
	}

	int yes = 1;
	
	if (setsockopt(_sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int)) == -1){
		return false;
	}

	return true;
}

//Wrapper function for bind(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);
bool Socket::bind(int port){
	if(!is_valid()){
		return false;
	}

	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	memset(_addr.sin_zero, '\0', sizeof _addr.sin_zero);

	if(::bind(_sockfd, (struct sockaddr *)&_addr, sizeof(_addr)) == -1){
		return false;
	}

	return true;
}

//Wrapper function for connect(int sockfd, const struct sockaddr *serv_addr,socklen_t addrlen);
bool Socket::connect(int ip, int port){
	if(!is_valid()){
		return false;
	}

	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = ip;

	if(::connect(_sockfd, (sockaddr *)&_addr, sizeof(_addr)) == -1){
		return false;
	}

	return true;
}

//Wrapper function for listen(int s, int backlog);
bool Socket::listen(){
	if(!is_valid()){
		return false;
	}

	if(::listen(_sockfd, BACKLOG) == -1){
		return false;
	}

	return true;
}

//Wrapper function for accept(int s, struct sockaddr *addr, socklen_t *addrlen);
bool Socket::accept(Socket& child_socket){
	if(!is_valid()){
		return false;
	}
	
	int addr_size = sizeof(_addr);
	int temp_fd = ::accept(_sockfd, (struct sockaddr *)&_addr,(socklen_t *) &addr_size);
	if(temp_fd == -1){
		return false;
	}

	child_socket.fd(temp_fd);

	return true;
}

//Wrapper function for send(int s, const void *buf, size_t len, int flags);
int Socket::send(std::string msg){
	if(!is_valid()){
		return -1;
	}
	
	return ::send(_sockfd, msg.c_str(), msg.length(), MSG_NOSIGNAL); //Set flags to MSG_SIGNAL to IGNORE Broken Pipe Errors.
}

//Wrapper function for recv(int s, void *buf, size_t len, int flags);
int Socket::recv(std::string& s){
	if(!is_valid()){
		return -1;
	}

	char buffer[MAXRECV+5];
	int status = ::recv(_sockfd, buffer, MAXRECV, 0);

	if(status > 0){
		s.assign(buffer,status);
	}

	return status;
}

//Wrapper function for close(int s);
bool Socket::close(){
	if(!is_valid()){
		return true;
	}

	if(::close(_sockfd) == -1){
		return false;
	}

	return true;
}