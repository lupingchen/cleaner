#pragma once
#include "MyListCtrl.h"

// CMyDialogClean �Ի���

class CMyDialogClean : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogClean)

public:
	CMyDialogClean(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDialogClean();

// �Ի�������
	enum { IDD = IDD_MYDIALOGCLEAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
