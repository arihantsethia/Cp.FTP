// Contains functions that help in parsing the HTTP/1.0 Header.

#include "utility.h"

/*
	Function to tokenize a given string on the seperator and 
	return a vector of the tokenized strings.
*/
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

/*
	Function to return the hostname present in the vector of tokens
*/
std::string gethostname(std::vector<std::string> tokens){
	std::vector<std::string>::iterator it;
	for(it=tokens.begin();it!=tokens.end();it++){
		if((*it).find("Host:",0)!=std::string::npos){
			return (*it).substr(6);
		}
	}
	return "-1";
}


/*
	Function to return the url present in the vector of tokens
*/
std::string geturl(std::vector<std::string> tokens){
	std::vector<std::string>::iterator it;
	for(it=tokens.begin();it!=tokens.end();it++){
		std::string::size_type pos = (*it).find("GET ",0);
		if(pos!=std::string::npos){
			pos = pos+4;
			while(isspace((*it)[pos])){
				pos++;
			}
			std::string::size_type endPos = (*it).find(" ",pos);
			std::string::size_type hPos = (*it).find("HTTP/1.0",endPos);
			if(endPos==std::string::npos || hPos==std::string::npos){
				return "-2";
			}
			return (*it).substr(pos,endPos-pos);
		}
	}
	return "-1";
}


/*

This function accepts valid headers and converts according to the specifics of RFC1945 

Accept from client: 
	GET http://www.iitg.ernet.in/ HTTP/1.0
	or 
	GET / HTTP/1.0
	Host: www.iitg.ernet.in
Send to remote server: 
	GET / HTTP/1.0
	Host: www.iitg.ernet.in
	(Additional client specified headers, if any...)

*/

std::string convertheader(std::string hdr, std::string host, std::string r_url, std::string port){
	std::string sep = "\r\n";
	std::string cHdr = "";
	std::string a_url ="";
	std::string temp;
	std::vector<std::string> tokens = tokenize(hdr,sep);
	std::vector<std::string>::iterator it;
	a_url= geturl(tokens);
	for(it=tokens.begin();it!=tokens.end();it++){
		temp = *it;
		if((*it).find("GET ",0) !=std::string::npos){
			temp = temp.replace(temp.find(a_url),a_url.length(),r_url);
			temp = temp + "\r\n" + "Host: "+host+":"+port;
		}
		if((*it).find("Proxy",0)==std::string::npos && (*it).find("Host",0)==std::string::npos ){
			cHdr += temp + "\r\n";
		}
	}
	cHdr += "\r\n";
	return cHdr;
}

/*
	Wrapper Function around the function gethostbyname(char*)
	returns the IP of the given host
*/

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


/*
Function which accept only these type of valid headers from client: 
	GET http://www.iitg.ernet.in/ HTTP/1.0
	or 
	GET / HTTP/1.0
	Host: www.iitg.ernet.in
	+
	<HEADER NAME>: <HEADER VALUE>	i.e other valid header fields
	
	Also, it assigns HOST to "host" relative URL to "r_url" and PORT to "port" (Default Port : 80)
	Return value : 200

In case of an invalid header it return "400" for "Bad Request"
								   and "501" for "Method Not Implemented"
	
*/

int parseheader(std::string data, std::string& host, std::string &r_url, std::string& port){
	// "\r\n" = <CR><LF> is defined as line break in the protocol specification (RFC1945) 
	std::string::size_type pos;
	std::string sep = "\r\n";
	std::vector<std::string> tokens = tokenize(data,sep);
	std::string url = geturl(tokens);
	host = gethostname(tokens);
	if(!url.compare("-1")){
		return 501;
	}else if(!url.compare("-2")){
		return 400;
	}
	if(!host.compare("-1")){
		pos = url.find("http://",0);
		std::string::size_type ePos = url.find("/",pos+7);
		if(pos!=std::string::npos && ePos!=std::string::npos){
			host = url.substr(7,(ePos-7));
		}else{
			return 400; 
		}
	}
	pos = url.find("http://",0);
	if(pos!=std::string::npos){
		r_url = url.substr(url.find("/",pos+7));
	}else{
		r_url = url;
	}
	pos = host.find(":",0);
	if(pos!=std::string::npos){
		port = host.substr(pos+1);
		host = host.substr(0,pos);
	}else{
		 port = "80";
	}
	return 200;
}