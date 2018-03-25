 ///
 /// @file    TcpConnection.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 15:57:05
 ///

#ifndef _WD_TCPCONNECTION_H__
#define _WD_TCPCONNECTION_H__

#include "Noncopyable.h"
#include "InetAddress.h"
#include "Socket.h"
#include "SocketIO.h"

#include <string>
#include <memory>
#include <functional>

namespace wd{

class EpollPoller;
class TcpConnection;
typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection
: Noncopyable
, public std::enable_shared_from_this<TcpConnection>
{
public:
	using TcpConnectionCallback = std::function<void(const TcpConnectionPtr &)>;
	TcpConnection(int sockfd, EpollPoller * loop);
	~TcpConnection();

	std::string receive();
	void send(const std::string & msg);
	void sendInLoop(const std::string & msg);
	void shutdown();

	std::string toString();

	void setConnectionCallback(TcpConnectionCallback cb);
	void setMessageCallback(TcpConnectionCallback cb);
	void setCloseCallback(TcpConnectionCallback cb);

	void handleConnectionCallback();
	void handleMessageCallback();
	void handleCloseCallback();

private:
	Socket _sockfd;
	SocketIO _sockIO;
	const InetAddress _localAddr;
	const InetAddress _peerAddr;
	bool _isShutdownWrite;
	EpollPoller * _loop;

	TcpConnectionCallback _onConnectionCb;
	TcpConnectionCallback _onMessageCb;
	TcpConnectionCallback _onCloseCb;
};


}//end of namespace wd
#endif
