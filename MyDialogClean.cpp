// MyDialogClean.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyDialogClean.h"
#include "afxdialogex.h"


// CMyDialogClean 对话框

IMPLEMENT_DYNAMIC(CMyDialogClean, CDialogEx)

CMyDialogClean::CMyDialogClean(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialogClean::IDD, pParent)
{

}

CMyDialogClean::~CMyDialogClean()
{
}

void CMyDialogClean::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX,IDC_LIST1,m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogClean, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDialogClean::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMyDialogClean::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMyDialogClean::OnBnClickedButton3)
END_MESSAGE_MAP()


// CMyDialogClean 消息处理程序


void CMyDialogClean::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR szdisplayname[MAX_PATH] = {0};
	TCHAR szpath[MAX_PATH] = {0};
	BROWSEINFO bi;
	static int Index = 0;

	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szdisplayname;
	bi.lpszTitle = _T("请选择要浏览的目录");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	//弹出浏览文件夹的对话框
	PIDLIST_ABSOLUTE pa = SHBrowseForFolder(&bi);

	if (pa)
	{
		//取路径
		SHGetPathFromIDList(pa,szpath);
		m_ListCtrl.InsertItem(Index,szpath);
		Index++;
	}
}


void CMyDialogClean::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nindex = m_ListCtrl.GetSelectionMark(); //取回选中记号，返回值为标签
	if (nindex != -1)
	{
		m_ListCtrl.DeleteItem(nindex);
	}
}


void CMyDialogClean::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (IDOK == MessageBox(_T("确定要删除吗?"),_T("温馨提示"),MB_OKCANCEL))
	{
		m_ListCtrl.DeleteAllItems();  //删除全部标签
	}
}
