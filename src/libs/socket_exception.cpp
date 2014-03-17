
// Class file for various Socket Exceptions

#include <string>
#include "socket_exception.h"

SocketException::SocketException(std::string s){
	message = s;
}

SocketException::~SocketException(){

}

//Returns the description of the Exception
std::string SocketException::description(){
	return message;
}