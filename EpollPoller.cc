 ///
 /// @file    EpollPoller.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 08:49:56
 ///

#include "EpollPoller.h"
#include "SocketUtil.h"
#include "Acceptor.h"
#include <assert.h>

#include <iostream>
using std::cout;
using std::endl;

namespace wd{

EpollPoller::EpollPoller(Acceptor & acceptor)
: _acceptor(acceptor)
, _epollfd(createEpollFd())
, _eventfd(createEventFd())
, _listenfd(_acceptor.fd())
, _isLooping(false)
, _eventsList(1024){
	addEpollFdRead(_epollfd, _listenfd);
	addEpollFdRead(_epollfd, _eventfd);
}

EpollPoller::~EpollPoller(){
	::close(_epollfd);
}

void EpollPoller::loop(){
	_isLooping = true;
	while(_isLooping){
		waitEpollfd();
	}
}

void EpollPoller::unloop(){
	if(_isLooping)
		_isLooping = false;
}

void EpollPoller::setConnectionCallback(EpollCallback cb){
	_onConnectionCb = cb;
}

void EpollPoller::setMessageCallback(EpollCallback cb){
	_onMessageCb = cb;
}

void EpollPoller::setCloseCallback(EpollCallback cb){
	_onCloseCb = cb;
}

void EpollPoller::waitEpollfd(){
	int nready;
	do {
		nready = ::epoll_wait(_epollfd,
				&(*_eventsList.begin()),
				_eventsList.size(),
				5000);
	}while(-1 == nready && errno == EINTR);

	if(-1 == nready){
		perror("epoll_wait error");
		exit(EXIT_FAILURE);
	}else if(0 == nready){
		printf("epoll_wait timeout\n");
	}else{
		if(static_cast<int>(_eventsList.size()) == nready){
			_eventsList.resize(_eventsList.size() * 2);
		}
		
		for(int idx = 0; idx != nready; ++idx){
			if(_eventsList[idx].data.fd == _listenfd){
				if(_eventsList[idx].events & EPOLLIN)
					handleConnection();
			}else if(_eventsList[idx].data.fd == _eventfd){
				handleRead();
				cout << "> doPendingFunctors()" << endl;
				doPendingFunctors();
			}else{
				if(_eventsList[idx].events & EPOLLIN){
					handleMessage(_eventsList[idx].data.fd);
				}
			}
		}
	}
}

void EpollPoller::handleConnection(){
	int peerfd = _acceptor.accept();
	addEpollFdRead(_epollfd, peerfd);

	TcpConnectionPtr conn(new TcpConnection(peerfd, this));

	conn->setConnectionCallback(_onConnectionCb);
	conn->setMessageCallback(_onMessageCb);
	conn->setCloseCallback(_onCloseCb);
	
	std::pair<ConnectionMap::iterator, bool> ret;
	ret = _connMap.insert(std::make_pair(peerfd, conn));
	assert(true == ret.second);

	conn->handleConnectionCallback();

}

void EpollPoller::handleMessage(int peerfd){
	bool isClosed = isConnectionClosed(peerfd);
	ConnectionMap::iterator it = _connMap.find(peerfd);
	assert(it != _connMap.end());
	
	if(isClosed){
		it->second->handleCloseCallback();
		delEpollReadFd(_epollfd, peerfd);
		_connMap.erase(it);
	}else{
		it->second->handleMessageCallback();
	}
}

void EpollPoller::runInLoop(const Functor && cb){
	{
		MutexLockGuard mlg(_mutex);
		_pendingFunctors.push_back(std::move(cb));
	}
	wakeup();
}

void EpollPoller::doPendingFunctors(){
	std::vector<Functor> tmp;
	{
		MutexLockGuard mlg(_mutex);
		tmp.swap(_pendingFunctors);
	}
	for(auto & functor : tmp){
		functor();
	}
}

void EpollPoller::handleRead(){
	uint64_t howmany;
	int ret = ::read(_eventfd, &howmany, sizeof(howmany));
	if(ret != sizeof(howmany)){
		perror("read error");
	}
}

void EpollPoller::wakeup(){
	uint64_t one = 1;
	int ret = ::write(_eventfd, &one, sizeof(one));
	if(ret != sizeof(one)){
		perror("write error");
	}
}


}//end of namespace wd
