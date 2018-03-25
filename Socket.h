 ///
 /// @file    Socket.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 10:52:47
 ///

#ifndef __WD_SOCKET_H__
#define __WD_SOCKET_H__

#include "Noncopyable.h"

namespace wd{

class Socket 
: Noncopyable
{
public:
	Socket(int sockfd);
	Socket();
	~Socket();

	void shutdownWrite();
	int fd() const {
		return _sockfd;
	}

	void nonblock();

private:
	int _sockfd;

};

}//end of namespace wd
#endif

