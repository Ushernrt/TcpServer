 ///
 /// @file    TcpServer.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 17:45:03
 ///

#ifndef __WD_TCPSERVER_H__
#define __WD_TCPSERVER_H__

#include "Acceptor.h"
#include "EpollPoller.h"
#include <string>

using std::string;

namespace wd{

class TcpServer{
public:
	using TcpServerCallback = EpollPoller::EpollCallback;
	TcpServer(const string & ip, unsigned short port);
	TcpServer(unsigned short port);

	void start();
	void stop();

	void setConnectionCallback(TcpServerCallback cb);
	void setMessageCallback(TcpServerCallback cb);
	void setCloseCallback(TcpServerCallback cb);

private:
	Acceptor _acceptor;
	EpollPoller _poller;

	TcpServerCallback _connectionCallback;
	TcpServerCallback _messageCallback;
	TcpServerCallback _closeCallback;

};

}//end of namespace wd
#endif
