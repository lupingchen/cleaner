#ifndef __THREADS_POOL__
#define __THREADS_POOL__

#include <process.h>
#include <Windows.h>
#include <queue>

#ifndef BOOL
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define DEFAULT_THREADS	(10)

class Task
{
public:
	Task();
	~Task();
public:
	virtual unsigned int TaskHandler(void * lpParam) = 0;
	BOOL isDone();
public:
	void * m_pParam;
protected:
	BOOL m_bDone;
};

class ThreadsPool
{
public:
	ThreadsPool();
	ThreadsPool(int nThreads);
	~ThreadsPool();
public:
	BOOL InitializeThreadsPool();
	BOOL InitializeThreadsPool(int nThreads);
	void DeleteThreadsPool();
	BOOL PostTask(Task * task);
	static unsigned int __stdcall procWork(void * lpParam);
protected:
	HANDLE * m_arrhThreads;
	HANDLE m_hSmphTask;
	HANDLE m_hEvtQuit;
	std::queue<Task*> m_TaskQueue;
	HANDLE m_hMtxTask;
	int m_nThreads;
};




#endif