#pragma once
#include "MyDialogClean.h"
#include "MyListCtrl.h"
#include "MyDialogSet.h"
// CMyTabCtrl

class CMyTabCtrl : public CTabCtrl
{
	DECLARE_DYNAMIC(CMyTabCtrl)

public:
	CMyTabCtrl();
	virtual ~CMyTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	bool OnInitTabCtrl(int nCount , UINT nTabCtrl[]); //自己封装初始化函数

	void OnInitPage();	//自己封装的初始化对话框函数

public:
	CMyDialogSet m_digset;
	CMyDialogClean m_dlg;
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


