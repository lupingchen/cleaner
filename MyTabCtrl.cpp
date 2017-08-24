// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyTabCtrl.h"
#include "CleanerDlg.h"
#include "MyDialogSet.h"
// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTabCtrl::OnNMClick)
	ON_WM_TIMER()
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序


//自己封装的初始化函数
bool CMyTabCtrl::OnInitTabCtrl(int nCount , UINT nTabCtrl[])	
{
	//校验参数
	if (nCount<=0 || !nTabCtrl)
	{
		return false;
	}

	CString str;
	for (int i = 0;i<nCount;++i)
	{
		str.LoadString(nTabCtrl[i]); //加载字符串
		InsertItem(i,str);		//设置tab控件TabCtrl的标签,InsertItem是CTabCtrl类中的成员函数
	}
	return true;
}


//自己封装的初始化对话框函数
void CMyTabCtrl::OnInitPage()
{
	//创建非模态对话框
	m_dlg.Create(IDD_DIALOG_CLEAN,this);
	m_dlg.ShowWindow(SW_SHOW);

	CRect rect,rectdialog;

	//获得当前控件坐标
	GetClientRect(rect);

	//获得标签高度
	this->GetItemRect(0,&rectdialog);

	//移动对话框到指定位置
	rect.top += rectdialog.Height();
	
	//改变窗口位置和大小
	m_dlg.MoveWindow(rect);	
}



void CMyTabCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	//1.获得当前选中的标签
	CCleanerDlg* dig_parent = (CCleanerDlg*)GetParent();
	int nindex = GetCurSel(); //获得当前选中的tab标签
	static bool bflag = true;
	if (nindex == 1)
	{

		//改变窗口大小
		if (bflag)
		{
			//大矩形
			//dig_parent->MoveWindow(dig_parent->m_RectBig);
			//dig_parent->SetWindowPos(&wndTopMost,0,0,dig_parent->m_RectBig.Width(),dig_parent->m_RectBig.Height(),SWP_NOMOVE);

			SetTimer(10,10,NULL); //设置定时器  为了达到动态效果
		}
		else
		{
			//小矩形
			//dig_parent->MoveWindow(dig_parent->m_RectSmall);
			//dig_parent->SetWindowPos(&wndTopMost,0,0,dig_parent->m_RectBig.Width(),dig_parent->m_RectSmall.Height(),SWP_NOMOVE);
			SetTimer(20,10,NULL);
		}
		bflag = !bflag;
	}

	else if(nindex == 2)
	{
		m_digset.DoModal();
	}

	*pResult = 0;
}


//定时器处理函数
void CMyTabCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CCleanerDlg* dig_parent = (CCleanerDlg*)GetParent();
	//判断定时器ID
	if (nIDEvent == 10)
	{
		CRect rect;
		dig_parent->GetWindowRect(&rect); //获得当前主窗口的大小
		if (rect.Height()+10 <= dig_parent->m_RectBig.Height())
		{
			dig_parent->SetWindowPos(/*&CWnd::wndTopMost*/ NULL,0,0,dig_parent->m_RectBig.Width(),rect.Height()+10,SWP_NOMOVE);
		}
		else
		{
			dig_parent->SetWindowPos(/*&CWnd::wndTopMost*/NULL ,0,0,dig_parent->m_RectBig.Width(),dig_parent->m_RectBig.Height(),SWP_NOMOVE);
			KillTimer(10);  //停止定时器处理
		}
	}
	
	if (nIDEvent == 20)
	{
		CRect rect;
		dig_parent->GetWindowRect(&rect);
		if (rect.Height()-10 >= dig_parent->m_RectSmall.Height())
		{
			dig_parent->SetWindowPos(/*&wndTopMost*/NULL,0,0,dig_parent->m_RectBig.Width(),rect.Height()-10,SWP_NOMOVE);
		}
		else
		{
			dig_parent->SetWindowPos(/*&wndTopMost*/NULL,0,0,dig_parent->m_RectBig.Width(),dig_parent->m_RectSmall.Height(),SWP_NOMOVE);
			KillTimer(20);
		}
	}

	CTabCtrl::OnTimer(nIDEvent);
}
