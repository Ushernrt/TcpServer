 ///
 /// @file    vim SocketIO.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 11:31:46
 ///

#include "SocketIO.h"
#include "SocketUtil.h"

namespace wd{

SocketIO::SocketIO(int sockfd)
: _sockfd(sockfd)
{}

size_t SocketIO::readn(char * buf, size_t count)
{
	size_t nleft = count;
	char * pbuf = buf;
	while(nleft > 0){
		int nread = ::read(_sockfd, pbuf, nleft);
		if(-1 == nread){
			if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
		}else if(0 == nread){
			break;
		}
		pbuf += nread;
		nleft -= nread;
	}
	return (count - nleft);
}

size_t SocketIO::recv_peek(char * buf, size_t count){
	int nread;
	do{
		nread = ::recv(_sockfd, buf, count, MSG_PEEK);
	}while(-1 == nread && errno == EINTR);
	return nread;
}

size_t SocketIO::writen(const char * buf, size_t count){
	size_t nleft = count;
	const char * pbuf = buf;
	while(nleft > 0){
		int nwrite = ::write(_sockfd, pbuf, nleft);
		if(-1 == nwrite){
			if(errno == EINTR)
				continue;
			return EXIT_FAILURE;
		}
		nleft -= nwrite;
		pbuf += nwrite;
	}
	return (count - nleft);
}

size_t SocketIO::readline(char * buf, size_t maxlen){
	int nleft = maxlen-1;
	char * pbuf = buf;
	size_t total = 0;
	while(nleft > 0){
		size_t nread = recv_peek(pbuf, nleft);
		if(nread <= 0)
			return nread;

		for(size_t idx = 0; idx != nread; ++idx){
			if(pbuf[idx] == '\n'){
				size_t nsize = idx + 1;
				if(readn(pbuf, nsize) != nsize)
					return EXIT_FAILURE;
				pbuf += nsize;
				total += nsize;

				*pbuf = 0;
				return total;
			}
		}
		if(readn(pbuf, nread) != nread)
			return EXIT_FAILURE;
		pbuf += nread;
		nleft -= nread;
		total += nread;
	}
	*pbuf = 0;
	return maxlen - 1;
}
}//end of namespace wd

