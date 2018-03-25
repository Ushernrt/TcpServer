 ///
 /// @file    Condition.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 15:10:43
 ///

#include "Condition.h"

#include "MutexLock.h"

namespace wd{

Condition::Condition(MutexLock & mutex)
: _mutex(mutex)
{
	pthread_cond_init(&_cond, NULL);
}

Condition::~Condition(){
	pthread_cond_destroy(&_cond);
}

void Condition::wait(){
	pthread_cond_wait(&_cond, _mutex.getMutexLockPtr());
}

void Condition::notify(){
	pthread_cond_signal(&_cond);
}

void Condition::notifyall(){
	pthread_cond_broadcast(&_cond);
}

}//end of namespace wd

