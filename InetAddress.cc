 ///
 /// @file    InetAddress.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 10:41:05
 ///

#include "InetAddress.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

namespace wd{

InetAddress::InetAddress(short port){
	::bzero(&_addr, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = INADDR_ANY;
}

InetAddress::InetAddress(const char *pIp, short port){
	::bzero(&_addr, sizeof(_addr));
	_addr.sin_family = AF_INET;
	_addr.sin_port = htons(port);
	_addr.sin_addr.s_addr = inet_addr(pIp);
}

InetAddress::InetAddress(const struct sockaddr_in & addr)
: _addr(addr)
{}

const struct sockaddr_in * InetAddress::getSockAddrPtr() const {
	return &_addr;
}

std::string InetAddress::ip() const {
	return std::string(inet_ntoa(_addr.sin_addr));
}

unsigned short InetAddress::port() const {
	return ntohs(_addr.sin_port);
}


}//end of namespace wd
