 ///
 /// @file    TaskQueue.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 15:25:27
 ///

#include "TaskQueue.h"

#include <iostream>
using std::cout;
using std::endl;

using namespace wd;

TaskQueue::TaskQueue(int queSize)
: _mutex()
, _notFull(_mutex)
, _notEmpty(_mutex)
, _queSize(queSize)
, _flag(true)
{}

bool TaskQueue::full() const {
	return _que.size() == _queSize;
}

bool TaskQueue::empty() const {
	return 0 == _que.size();
}

void TaskQueue::push(TaskQueue::Product product){
	MutexLockGuard mlg(_mutex);
	while(full()){
		_notFull.wait();
	}

	_que.push(product);
	_notEmpty.notify();
}

TaskQueue::Product TaskQueue::pop(){
	MutexLockGuard mlg(_mutex);
	while(_flag && empty()){
		_notEmpty.wait();
	}

	if(_flag){
		Product product = _que.front();
		_que.pop();
		_notFull.notify();

		return product;
	}else 
		return NULL;
}

void TaskQueue::wakeup(){
	_flag = false;
	_notEmpty.notifyall();
}
