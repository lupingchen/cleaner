#pragma once
#include "MyListCtrl.h"

// CMyDialogClean 对话框

class CMyDialogClean : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogClean)

public:
	CMyDialogClean(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDialogClean();

// 对话框数据
	enum { IDD = IDD_MYDIALOGCLEAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyListCtrl m_ListCtrl;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};
