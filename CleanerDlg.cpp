
// CleanerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cleaner.h"
#include "CleanerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCleanerDlg �Ի���



CCleanerDlg::CCleanerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCleanerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCleanerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PICTURE1, m_Mypicture);
	DDX_Control(pDX, IDC_TAB1, m_mytabctrl);
	DDX_Control(pDX, IDC_LIST1, m_listResult);
}

BEGIN_MESSAGE_MAP(CCleanerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCleanerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCleanerDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CCleanerDlg ��Ϣ�������

BOOL CCleanerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//�̳߳س�ʼ��
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	m_thp.InitializeThreadsPool(si.dwNumberOfProcessors);

	//����tab�ؼ�TabCtrl��ѡ��
	/*m_tabctrl.InsertItem(0,_T("��ɨĿ¼����"));
	m_tabctrl.InsertItem(1,_T("��ʾ��־"));
	m_tabctrl.InsertItem(2,_T("������Ϣ"));
	m_tabctrl.InsertItem(3,_T("ɨ�貢ɾ��"));*/

	UINT nTabCtrl[] = {IDS_CLEANCONTENT,IDS_SHOWCONTENT,IDS_SETCONTENT,IDS_DELETECONTENT};
	//��ʼ��TabCtrl��ǩ
	if (!m_mytabctrl.OnInitTabCtrl(4,nTabCtrl)) 
	{
		MessageBox(_T("Init failed!"));
	}

	m_mytabctrl.OnInitPage();

	//==============================������ʾ����������־================================
	//��ʼ�����Ի���Ĵ�С
	//��ô��ڵĴ�С
	GetWindowRect(m_RectBig);
	//���groupbox�Ĵ�С----С����
	GetDlgItem(IDC_SMALLRECT)->GetClientRect(m_RectSmall); //getdlgitem(ID)  ���ָ���ؼ���ָ��

	//MoveWindow(m_RectBig);
	SetWindowPos(/*&wndTopMost*/NULL,0,0,m_RectBig.Width(),m_RectSmall.Height(),SWP_NOMOVE);
	//==================================================================================

	m_listResult.InsertColumn(0,_T("path"),LVCFMT_CENTER,m_RectSmall.Width());//ΪlistCtrl�����
	m_listResult.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES);//���listctrl �ķ��
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCleanerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCleanerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCleanerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


unsigned int STask::TaskHandler(void * lpParam)
{
	Param *param=(Param*)lpParam;
	//2.��������
	CFileFind filefind;
	bool flag;
	//��õ�ǰ·���µ�����
	if (param->strpath.Right(1) != '\\')
	{
		param->strpath+= '\\';
	}
	flag = filefind.FindFile( param->strpath + _T("*.*"));
	while(flag)
	{
		flag = filefind.FindNextFile();
		CString str = filefind.GetFileName();
		//�ж����ļ������ļ���
		if (filefind.IsDirectory())
		{
			//������ļ��У��ٴι�������Ͷ��
			if (!filefind.IsDots())
			{
				//��������
				STask *temp_task=new STask;
				Param *temp_param=new Param;
				temp_param->object=param->object;
				temp_param->strpath=param->strpath+str;
				temp_task->m_pParam=temp_param;
				//Ͷ��
				param->object->m_thp.PostTask(temp_task);
#if 0
				lstdir.push_back(param->strpath+str);
#endif
			}
		}
		else
		{
			//��õ�ǰ�ļ������ݣ��ȽϺ�׺��Ҫɾ�����Ƿ���ͬ
			int nindex = str.ReverseFind('.');
			CString strtemp;
			if (nindex != -1)
			{
				strtemp = str.Right(str.GetLength()-nindex);
			}
			param->object->m_mytabctrl.m_digset.m_iter = find(param->object->m_mytabctrl.m_digset.m_list.begin(),param->object->m_mytabctrl.m_digset.m_list.end(),strtemp);
			if (param->object->m_mytabctrl.m_digset.m_iter != param->object->m_mytabctrl.m_digset.m_list.end())
			{
				//���뵽�ؼ���
				param->object->m_listResult.InsertItem(0,param->strpath+str);
			}
		}
	}

	return 1;
}


void CCleanerDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
#if 0
	list<CString> lstdir;
	list<CString>::iterator lstdirite;
#endif
	//1.���listCtrl�ϵ�·��������һ�����񣬼����̳߳�
	for (int i =0; i<m_mytabctrl.m_dlg.m_ListCtrl.GetItemCount();++i)
	{
		CString str = m_mytabctrl.m_dlg.m_ListCtrl.GetItemText(i,0);
		if (!str.IsEmpty())
		{
			//��������
			STask *temp_task=new STask;
			Param *temp_param=new Param;
			temp_param->object=this;
			temp_param->strpath=str;
			temp_task->m_pParam=temp_param;
			//Ͷ��
			m_thp.PostTask(temp_task);
#if 0
			lstdir.push_back(str);
#endif
		}
	}


	MessageBox(_T("������ɣ�"),_T("��ʾ"),MB_OKCANCEL);
}


void CCleanerDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nindex = m_listResult.GetSelectionMark();
	if (nindex != -1)
	{
		if (IDOK == MessageBox(_T("ȷ��Ҫɾ����?")),_T("��ʾ"),MB_OKCANCEL);
		{
			CString str = m_listResult.GetItemText(nindex,0);
			DeleteFile(str); //�ӵ�����ֱ��ɾ���ļ�
			m_listResult.DeleteItem(nindex);
		}

	}
}
