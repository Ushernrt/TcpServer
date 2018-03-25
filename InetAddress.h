 ///
 /// @file    InetAddress.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 10:37:39
 ///

#ifndef _WD_INETADDRESS_H__
#define _WD_INETADDRESS_H__

#include <netinet/in.h>
#include <string>

namespace wd{

class InetAddress{
public:
	InetAddress(short port);

	InetAddress(const char *pIp, short port);

	InetAddress(const struct sockaddr_in & addr);

	const struct sockaddr_in * getSockAddrPtr() const;
	std::string ip() const;
	unsigned short port() const;

private:
	struct sockaddr_in _addr;
};

}//end of namespace wd
#endif

