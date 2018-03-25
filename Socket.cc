 ///
 /// @file    Socket.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 11:23:42
 ///

#include "Socket.h"
#include "SocketUtil.h"
#include "InetAddress.h"

namespace wd{

Socket::Socket(int sockfd)
: _sockfd(sockfd)
{}

Socket::Socket()
: _sockfd(createSocketFd())
{}

Socket::~Socket(){
	::close(_sockfd);
}

void Socket::nonblock(){
	setNonblock(_sockfd);
}

void Socket::shutdownWrite(){
	if(::shutdown(_sockfd, SHUT_WR) == -1){
		perror("shutdown write error!");
	}
}

}// end of namespace wd

