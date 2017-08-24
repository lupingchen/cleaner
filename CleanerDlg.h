
// CleanerDlg.h : ͷ�ļ�
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

// CCleanerDlg �Ի���
class CCleanerDlg : public CDialogEx
{


// ����
public:
	CCleanerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CLEANER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
