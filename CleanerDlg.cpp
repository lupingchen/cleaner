
// CleanerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "CleanerDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
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


// CCleanerDlg 对话框



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


// CCleanerDlg 消息处理程序

BOOL CCleanerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//线程池初始化
	SYSTEM_INFO si;
	GetSystemInfo(&si);

	m_thp.InitializeThreadsPool(si.dwNumberOfProcessors);

	//设置tab控件TabCtrl的选项
	/*m_tabctrl.InsertItem(0,_T("清扫目录设置"));
	m_tabctrl.InsertItem(1,_T("显示日志"));
	m_tabctrl.InsertItem(2,_T("设置信息"));
	m_tabctrl.InsertItem(3,_T("扫描并删除"));*/

	UINT nTabCtrl[] = {IDS_CLEANCONTENT,IDS_SHOWCONTENT,IDS_SETCONTENT,IDS_DELETECONTENT};
	//初始化TabCtrl标签
	if (!m_mytabctrl.OnInitTabCtrl(4,nTabCtrl)) 
	{
		MessageBox(_T("Init failed!"));
	}

	m_mytabctrl.OnInitPage();

	//==============================设置显示窗口清理日志================================
	//初始化主对话框的大小
	//获得窗口的大小
	GetWindowRect(m_RectBig);
	//获得groupbox的大小----小矩形
	GetDlgItem(IDC_SMALLRECT)->GetClientRect(m_RectSmall); //getdlgitem(ID)  获得指定控件的指针

	//MoveWindow(m_RectBig);
	SetWindowPos(/*&wndTopMost*/NULL,0,0,m_RectBig.Width(),m_RectSmall.Height(),SWP_NOMOVE);
	//==================================================================================

	m_listResult.InsertColumn(0,_T("path"),LVCFMT_CENTER,m_RectSmall.Width());//为listCtrl添加列
	m_listResult.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES);//添加listctrl 的风格
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCleanerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCleanerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


unsigned int STask::TaskHandler(void * lpParam)
{
	Param *param=(Param*)lpParam;
	//2.遍历链表
	CFileFind filefind;
	bool flag;
	//获得当前路径下的内容
	if (param->strpath.Right(1) != '\\')
	{
		param->strpath+= '\\';
	}
	flag = filefind.FindFile( param->strpath + _T("*.*"));
	while(flag)
	{
		flag = filefind.FindNextFile();
		CString str = filefind.GetFileName();
		//判断是文件还是文件夹
		if (filefind.IsDirectory())
		{
			//如果是文件夹，再次构造任务投递
			if (!filefind.IsDots())
			{
				//构造任务
				STask *temp_task=new STask;
				Param *temp_param=new Param;
				temp_param->object=param->object;
				temp_param->strpath=param->strpath+str;
				temp_task->m_pParam=temp_param;
				//投递
				param->object->m_thp.PostTask(temp_task);
#if 0
				lstdir.push_back(param->strpath+str);
#endif
			}
		}
		else
		{
			//获得当前文件的内容，比较后缀与要删除的是否相同
			int nindex = str.ReverseFind('.');
			CString strtemp;
			if (nindex != -1)
			{
				strtemp = str.Right(str.GetLength()-nindex);
			}
			param->object->m_mytabctrl.m_digset.m_iter = find(param->object->m_mytabctrl.m_digset.m_list.begin(),param->object->m_mytabctrl.m_digset.m_list.end(),strtemp);
			if (param->object->m_mytabctrl.m_digset.m_iter != param->object->m_mytabctrl.m_digset.m_list.end())
			{
				//加入到控件中
				param->object->m_listResult.InsertItem(0,param->strpath+str);
			}
		}
	}

	return 1;
}


void CCleanerDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
#if 0
	list<CString> lstdir;
	list<CString>::iterator lstdirite;
#endif
	//1.获得listCtrl上的路径，构建一个任务，加入线程池
	for (int i =0; i<m_mytabctrl.m_dlg.m_ListCtrl.GetItemCount();++i)
	{
		CString str = m_mytabctrl.m_dlg.m_ListCtrl.GetItemText(i,0);
		if (!str.IsEmpty())
		{
			//构造任务
			STask *temp_task=new STask;
			Param *temp_param=new Param;
			temp_param->object=this;
			temp_param->strpath=str;
			temp_task->m_pParam=temp_param;
			//投递
			m_thp.PostTask(temp_task);
#if 0
			lstdir.push_back(str);
#endif
		}
	}


	MessageBox(_T("搜索完成！"),_T("提示"),MB_OKCANCEL);
}


void CCleanerDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int nindex = m_listResult.GetSelectionMark();
	if (nindex != -1)
	{
		if (IDOK == MessageBox(_T("确定要删除吗?")),_T("提示"),MB_OKCANCEL);
		{
			CString str = m_listResult.GetItemText(nindex,0);
			DeleteFile(str); //从电脑中直接删除文件
			m_listResult.DeleteItem(nindex);
		}

	}
}
