#pragma once
#include "afxwin.h"
#include "MyComboBox.h"
#include "afxcmn.h"
#include "MyTreeCtrl.h"
#include "list"
// CMyDialogSet 对话框

class CMyDialogSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogSet)

public:
	CMyDialogSet(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyDialogSet();

// 对话框数据
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedOk();

public: 
	CMyComboBox m_CombBox;
	CMyTreeCtrl m_TreeCtrl;
	list<CString> m_list;
	list<CString>::iterator m_iter;
};
