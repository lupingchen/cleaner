// MyDialogClean.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyDialogClean.h"
#include "afxdialogex.h"


// CMyDialogClean �Ի���

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


// CMyDialogClean ��Ϣ�������


void CMyDialogClean::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szdisplayname[MAX_PATH] = {0};
	TCHAR szpath[MAX_PATH] = {0};
	BROWSEINFO bi;
	static int Index = 0;

	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = szdisplayname;
	bi.lpszTitle = _T("��ѡ��Ҫ�����Ŀ¼");
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX;
	bi.lpfn = NULL;
	bi.lParam = NULL;
	bi.iImage = NULL;
	//��������ļ��еĶԻ���
	PIDLIST_ABSOLUTE pa = SHBrowseForFolder(&bi);

	if (pa)
	{
		//ȡ·��
		SHGetPathFromIDList(pa,szpath);
		m_ListCtrl.InsertItem(Index,szpath);
		Index++;
	}
}


void CMyDialogClean::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nindex = m_ListCtrl.GetSelectionMark(); //ȡ��ѡ�мǺţ�����ֵΪ��ǩ
	if (nindex != -1)
	{
		m_ListCtrl.DeleteItem(nindex);
	}
}


void CMyDialogClean::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (IDOK == MessageBox(_T("ȷ��Ҫɾ����?"),_T("��ܰ��ʾ"),MB_OKCANCEL))
	{
		m_ListCtrl.DeleteAllItems();  //ɾ��ȫ����ǩ
	}
}
