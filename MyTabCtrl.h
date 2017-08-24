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
	bool OnInitTabCtrl(int nCount , UINT nTabCtrl[]); //�Լ���װ��ʼ������

	void OnInitPage();	//�Լ���װ�ĳ�ʼ���Ի�����

public:
	CMyDialogSet m_digset;
	CMyDialogClean m_dlg;
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


