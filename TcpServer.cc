 ///
 /// @file    TcpServer.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 20:24:36
 ///
 
#include "TcpServer.h"
#include "InetAddress.h"
#include "SocketUtil.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd{

TcpServer::TcpServer(const string & ip, unsigned short port)
: _acceptor(createSocketFd(), InetAddress(ip.c_str(), port))
, _poller(_acceptor)
{}

TcpServer::TcpServer(unsigned short port)
: _acceptor(createSocketFd(), InetAddress("127.0.0.1",port))
, _poller(_acceptor)
{}

void TcpServer::start(){
	_acceptor.ready();
	_poller.setConnectionCallback(_connectionCallback);
	_poller.setMessageCallback(_messageCallback);
	_poller.setCloseCallback(_closeCallback);
	_poller.loop();

}

void TcpServer::stop(){
	_poller.unloop();
}

void TcpServer::setConnectionCallback(TcpServerCallback cb){
	_connectionCallback = cb;
}

void TcpServer::setMessageCallback(TcpServerCallback cb){
	_messageCallback = cb;
}

void TcpServer::setCloseCallback(TcpServerCallback cb){
	_closeCallback = cb;
}

}//end of namespace wd
