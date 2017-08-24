#include "stdafx.h"
#include "ThreadsPool.h"

Task::Task()
{
	m_pParam = NULL;
	m_bDone = FALSE;
}

Task::~Task()
{}

BOOL Task::isDone()
{
	return m_bDone;
}

ThreadsPool::ThreadsPool()
{
	m_arrhThreads = NULL;
	m_hSmphTask = NULL;
	m_hEvtQuit = NULL;
	m_hMtxTask = NULL;
	m_nThreads = 0;
}

ThreadsPool::ThreadsPool(int nThreads)
{
	InitializeThreadsPool(nThreads);
}

ThreadsPool::~ThreadsPool()
{
	if (WAIT_TIMEOUT == WaitForSingleObject(m_hEvtQuit, 10))
	{
		DeleteThreadsPool();
	}
}

BOOL ThreadsPool::InitializeThreadsPool()
{
	// 初始化线程句柄数组
	try
	{
		m_arrhThreads = new HANDLE[DEFAULT_THREADS];
	}
	catch (const std::bad_alloc &err)
	{
		return FALSE;
	}
	// 这个函数，不是志玲
	memset(m_arrhThreads, 0, sizeof(HANDLE)*DEFAULT_THREADS);
	// 这个函数，才是志玲
	// ZeroMemory();
	// 创建信号量
	m_hSmphTask = CreateSemaphore(NULL, 0, DEFAULT_THREADS, NULL);
	if (!m_hSmphTask)
	{
		delete []m_arrhThreads;
		m_arrhThreads = NULL;
		printf("ERROR: CREATE SEMAPHORE FAILED.\n");
		return FALSE;
	}
	// 创建事件
	m_hEvtQuit = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!m_hEvtQuit)
	{
		delete []m_arrhThreads;
		m_arrhThreads = NULL;
		CloseHandle(m_hSmphTask);
		m_hSmphTask = NULL;
		printf("ERROR: CREATE EVENT FAILED.\n");
		return FALSE;
	}
	// 创建互斥量
	m_hMtxTask = CreateMutex(NULL, FALSE, NULL);
	if (!m_hMtxTask)
	{
		delete []m_arrhThreads;
		m_arrhThreads = NULL;
		CloseHandle(m_hSmphTask);
		m_hSmphTask = NULL;
		CloseHandle(m_hEvtQuit);
		m_hEvtQuit = NULL;
		printf("ERROR: CREATE MUTEX FAILED.\n");
		return FALSE;
	}
	// 创建线程池中的线程
	for (int i = 0; i < DEFAULT_THREADS; i++)
	{
		HANDLE temp;
		temp = (HANDLE)_beginthreadex(NULL, 0, procWork, this, 0, NULL);
		if (!temp)
		{
			delete []m_arrhThreads;
			m_arrhThreads = NULL;
			CloseHandle(m_hEvtQuit);
			m_hEvtQuit = NULL;
			CloseHandle(m_hSmphTask);
			m_hSmphTask = NULL;
			CloseHandle(m_hMtxTask);
			m_hMtxTask = NULL;
			for (int n = 0; n < i; n++)
			{
				TerminateThread(m_arrhThreads[n], -1);
				CloseHandle(m_arrhThreads[n]);
				m_arrhThreads[n] = NULL;
			}
			printf("ERROR: CREATE THREADS FAILED.\n");
			return FALSE;
		}
		m_arrhThreads[i] = temp;
	}

	m_nThreads = DEFAULT_THREADS;
	return TRUE;	
}

BOOL ThreadsPool::InitializeThreadsPool(int nThreads)
{
	// 初始化线程句柄数组
	try
	{
		m_arrhThreads = new HANDLE[nThreads];
	}
	catch (const std::bad_alloc &err)
	{
		return FALSE;
	}
	// 这个函数，不是志玲
	memset(m_arrhThreads, 0, sizeof(HANDLE)*nThreads);
	// 这个函数，才是志玲
	// ZeroMemory();
	// 创建信号量
	m_hSmphTask = CreateSemaphore(NULL, 0, nThreads, NULL);
	if (!m_hSmphTask)
	{
		delete []m_arrhThreads;
		m_arrhThreads = NULL;
		printf("ERROR: CREATE SEMAPHORE FAILED.\n");
		return FALSE;
	}
	// 创建事件
	m_hEvtQuit = CreateEvent(NULL, TRUE, FALSE, NULL);
	if (!m_hEvtQuit)
	{
		delete []m_arrhThreads;
		m_arrhThreads = NULL;
		CloseHandle(m_hSmphTask);
		m_hSmphTask = NULL;
		printf("ERROR: CREATE EVENT FAILED.\n");
		return FALSE;
	}
	// 创建互斥量
	m_hMtxTask = CreateMutex(NULL, FALSE, NULL);
	if (!m_hMtxTask)
	{
		delete []m_arrhThreads;
		m_arrhThreads = NULL;
		CloseHandle(m_hSmphTask);
		m_hSmphTask = NULL;
		CloseHandle(m_hEvtQuit);
		m_hEvtQuit = NULL;
		printf("ERROR: CREATE MUTEX FAILED.\n");
		return FALSE;
	}
	// 创建线程池中的线程
	for (int i = 0; i < nThreads; i++)
	{
		HANDLE temp;
		temp = (HANDLE)_beginthreadex(NULL, 0, procWork, this, 0, NULL);
		if (!temp)
		{
			delete []m_arrhThreads;
			m_arrhThreads = NULL;
			CloseHandle(m_hEvtQuit);
			m_hEvtQuit = NULL;
			CloseHandle(m_hSmphTask);
			m_hSmphTask = NULL;
			CloseHandle(m_hMtxTask);
			m_hMtxTask = NULL;
			for (int n = 0; n < i; n++)
			{
				TerminateThread(m_arrhThreads[n], -1);
				CloseHandle(m_arrhThreads[n]);
				m_arrhThreads[n] = NULL;
			}
			printf("ERROR: CREATE THREADS FAILED.\n");
			return FALSE;
		}
		m_arrhThreads[i] = temp;
	}

	m_nThreads = nThreads;
	return TRUE;
}

void ThreadsPool::DeleteThreadsPool()
{
	CloseHandle(m_hSmphTask);
	m_hSmphTask = NULL;
	SetEvent(m_hEvtQuit);
	if (WAIT_TIMEOUT == WaitForMultipleObjects(m_nThreads, m_arrhThreads, TRUE, 
		500))
	{
		for (int i = 0; i < m_nThreads; i++)
		{
			printf("WARNING: TERMINATE THREAD.\n");
			TerminateThread(m_arrhThreads[i], -1);
		}
	}
	for (int i = 0; i < m_nThreads; i++)
	{
		CloseHandle(m_arrhThreads[i]);
	}
	memset(m_arrhThreads, 0, sizeof(HANDLE)*m_nThreads);
	
	delete []m_arrhThreads;
	m_arrhThreads = NULL;

	CloseHandle(m_hEvtQuit);
	m_hEvtQuit = NULL;

	CloseHandle(m_hMtxTask);
	m_hMtxTask = NULL;
}

BOOL ThreadsPool::PostTask(Task * task)
{
	if (!task)
		return FALSE; 
	while (1)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(m_hMtxTask, 20))
		{
			m_TaskQueue.push(task);
			break;
		}
	}
	ReleaseMutex(m_hMtxTask);
	ReleaseSemaphore(m_hSmphTask, 1, NULL);
	
	Sleep(1);
	return TRUE;
}

unsigned int __stdcall ThreadsPool::procWork(void * lpParam)
{
	ThreadsPool * pthis = (ThreadsPool*)lpParam;
	while (1)
	{
		if (WAIT_OBJECT_0 == WaitForSingleObject(pthis->m_hSmphTask, 20))
		{
			// 1. 取任务
			while (!(pthis->m_TaskQueue.empty()))
			{
				if (WAIT_OBJECT_0 == WaitForSingleObject(pthis->m_hEvtQuit, 20))
				{
					printf("NOTIFY: NOTIFIED TO QUIT.\n");
					break;
				}
				// 从任务队列中，读取一个任务处理
				// 注意：互斥访问
				if (WAIT_OBJECT_0 == WaitForSingleObject(pthis->m_hMtxTask, 20))
				{
					if (! (pthis->m_TaskQueue.empty()) )
					{
						Task* ptask = pthis->m_TaskQueue.front();
						pthis->m_TaskQueue.pop();
						// 2. 调用独取出来的任务中的任务处理函数
						ptask->TaskHandler(ptask->m_pParam);
					}
					// 释放互斥量
					ReleaseMutex(pthis->m_hMtxTask);
				}
			}
		}
	}
	return 1;
}
