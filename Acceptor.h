 ///
 /// @file    Acceptor.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 11:50:10
 ///

#ifndef __WD_ACCEPTOR_H__
#define __WD_ACCEPTOR_H__

#include "Socket.h"
#include "InetAddress.h"

namespace wd{

class Acceptor{

public:
	Acceptor(int listenfd, const InetAddress & addr);

	void ready();
	int accept();

	int fd() const{
		return _listenSock.fd();
	}

private:
	void setReuseAddr(bool);
	void setReusePort(bool);
	void bind();
	void listen();

private:
	Socket _listenSock;
	InetAddress _addr;

};

}//end of namespace wd
#endif
