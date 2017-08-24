#pragma once
#include "afxwin.h"
#include "MyComboBox.h"
#include "afxcmn.h"
#include "MyTreeCtrl.h"
#include "list"
// CMyDialogSet �Ի���

class CMyDialogSet : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogSet)

public:
	CMyDialogSet(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyDialogSet();

// �Ի�������
	enum { IDD = IDD_DIALOG_SET };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
