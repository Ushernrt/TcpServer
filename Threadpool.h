 ///
 /// @file    Threadpool.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 15:35:49
 ///

#ifndef __WD_THREADPOOL_H__
#define __WD_THREADPOOL_H__

#include "TaskQueue.h"

#include <memory>
#include <vector>
#include <functional>

using std::vector;
using std::unique_ptr;

namespace wd{

class Thread;

class Threadpool
{
	using Task = std::function<void()>;
public:
	Threadpool(size_t threadNum, size_t queSize);
	~Threadpool();

	void start();
	void stop();

	void addTask(Task);
private:

	Task getTask();

	void threadFunc(void);

private:
	size_t _threadNum;
	size_t _queSize;
	vector<unique_ptr<Thread>> _threads;
	TaskQueue _taskque;
	bool _isExit;

};

}//end of namespace wd
#endif

