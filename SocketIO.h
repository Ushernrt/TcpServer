 ///
 /// @file    SocketIO.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 11:28:34
 ///

#ifndef _WD_SOCKETIO_H__
#define _WD_SOCKETIO_H__

#include <stdio.h>

namespace wd{

class SocketIO{

public:
	SocketIO(int sockfd);

	size_t readn(char * buf, size_t count);
	size_t writen(const char * buf, size_t count);
	size_t readline(char * buf, size_t max_len);

private:
	size_t recv_peek(char * buf, size_t count);

private:
	int _sockfd;

};

}//end of namespace wd
#endif

