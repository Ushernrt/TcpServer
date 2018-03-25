 ///
 /// @file    testserver.cc
 /// @author  xiu(1107040857@qq.com)
 /// @date    2018-03-25 20:34:18
 ///

#include "TcpServer.h"
#include "Threadpool.h"

#include <iostream>
using std::cout;
using std::endl;

class Task{
public:
	Task(const string & query, const wd::TcpConnectionPtr & conn)
	: _query(query)
	, _conn(conn)
	{}
	
	void process(){
		cout << "> task is processing" << endl;

		_conn->sendInLoop(_query);
	}

private:
	 string _query;
	 wd::TcpConnectionPtr _conn;

};

wd::Threadpool * g_threadpool = NULL;

void onConnection(const wd::TcpConnectionPtr & conn){
	cout << conn->toString() << endl;
	conn -> send("hello, welcome to Char Server.\r\n");
}

void onMessage(const wd::TcpConnectionPtr & conn){
	std::string s(conn->receive());
	
	Task task(s, conn);
	g_threadpool->addTask(std::bind(&Task::process, task));
	cout << "> add task to threadpool" << endl;

}

void onClose(const wd::TcpConnectionPtr & conn){
	printf("%s close\n", conn->toString().c_str());
}

int main(){
	wd::Threadpool threadpool(4, 10);
	g_threadpool = &threadpool;
	threadpool.start();

	wd::TcpServer tcpserver(8888);
	tcpserver.setConnectionCallback(&onConnection);
	tcpserver.setMessageCallback(&onMessage);
	tcpserver.setCloseCallback(&onClose);

	tcpserver.start();
	

	return 0;

}
