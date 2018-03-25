 ///
 /// @file    MutexLock.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 14:44:54
 ///

#include "MutexLock.h"

#include <iostream>
using std::cout;
using std::endl;

namespace wd{

MutexLock::MutexLock()
: _isLocking(false)
{
	pthread_mutex_init(&_mutex, NULL);
}

MutexLock::~MutexLock(){
	pthread_mutex_destroy(&_mutex);
}

pthread_mutex_t * MutexLock::getMutexLockPtr(){
	return &_mutex;
}

void MutexLock::lock(){
	pthread_mutex_lock(&_mutex);
	_isLocking = true;
}

void MutexLock::unlock(){
	pthread_mutex_unlock(&_mutex);
	_isLocking = false;
}
}//end of namespace wd

