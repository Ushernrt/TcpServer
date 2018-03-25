 ///
 /// @file    Noncopyable.h
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 10:49:46
 ///

#ifndef __WD_NONCOPYABLE_H__
#define __WD_NONCOPYABLE_H__

namespace wd{

class Noncopyable{

protected:
	Noncopyable(){}
	~Noncopyable(){}

	Noncopyable(const Noncopyable &) = delete;
	Noncopyable & operator=(const Noncopyable &) = delete;

};

}//end of namespace wd
#endif

