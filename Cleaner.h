
// Cleaner.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCleanerApp:
// �йش����ʵ�֣������ Cleaner.cpp
//

class CCleanerApp : public CWinApp
{
public:
	CCleanerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCleanerApp theApp;