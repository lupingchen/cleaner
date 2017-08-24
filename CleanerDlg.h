
// CleanerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "MyPicture.h"
#include "afxcmn.h"
#include "MyTabCtrl.h"
#include "ThreadsPool.h"
class STask :public Task
{
	unsigned int TaskHandler(void * lpParam);

};

// CCleanerDlg 对话框
class CCleanerDlg : public CDialogEx
{


// 构造
public:
	CCleanerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CLEANER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CMyPicture m_Mypicture;
	CMyTabCtrl m_mytabctrl;

	CRect m_RectSmall,m_RectBig;
	afx_msg void OnBnClickedButton1();
	CListCtrl m_listResult;
	afx_msg void OnBnClickedButton2();
	ThreadsPool m_thp;
};

struct Param
{
	CCleanerDlg* object;
	CString strpath;
};
