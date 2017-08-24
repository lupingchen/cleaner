// MyTreeCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyTreeCtrl.h"


// CMyTreeCtrl

IMPLEMENT_DYNAMIC(CMyTreeCtrl, CTreeCtrl)

CMyTreeCtrl::CMyTreeCtrl()
{

}

CMyTreeCtrl::~CMyTreeCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTreeCtrl, CTreeCtrl)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CMyTreeCtrl::OnTvnItemexpanding)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTreeCtrl::OnNMClick)
END_MESSAGE_MAP()



// CMyTreeCtrl 消息处理程序


//当点击+按钮时走的函数
void CMyTreeCtrl::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码

	//1.获得当前选中项——要展开项
	HTREEITEM hCurrentitem = pNMTreeView->itemNew.hItem; //当前选中项在参数中就有

	CString str = GetItemText(hCurrentitem);  //获得该项的名字

	//2.获得当前选中项的儿子们
	HTREEITEM hSonitem  = GetChildItem(hCurrentitem);

	while(hSonitem != nullptr)  //给所有儿子加儿子
	{
		//删除hSonitem的儿子
		OnDelete(hSonitem);
		//3.给当前选中项的儿子们加儿子
		CString str = OnGetParentPath(hSonitem);
			//获得当前项的路径
		OnFindFile(str,hSonitem);
		//4.找儿子的兄弟
		hSonitem = GetNextSiblingItem(hSonitem);
	}
	
	*pResult = 0;
}

//删除儿子
void CMyTreeCtrl::OnDelete(HTREEITEM hitem)
{
	Expand(hitem,TVE_COLLAPSE);
	HTREEITEM hchilditem = GetChildItem(hitem);
	HTREEITEM htempitem = nullptr;
	while (hchilditem)
	{
		htempitem = hchilditem;
		hchilditem = GetNextSiblingItem(hchilditem);
		DeleteItem(htempitem);
	}
}

//获得当前项的路径
CString CMyTreeCtrl::OnGetParentPath(HTREEITEM hitem)
{
	CString hpath , htemppath;
	while (hitem)
	{
		htemppath = GetItemText(hitem);
		if (htemppath.Right(1) != _T("\\"))
		{
			htemppath += _T("\\");
		}
		hpath = htemppath + hpath;
		//获得父亲项
		hitem = GetParentItem(hitem);
	}
	
	return hpath;
}

//找到当前项的儿子
void CMyTreeCtrl::OnFindFile(CString cPath , HTREEITEM hitem)
{
	//判断当前的路径是否带\ ，系统盘都自带\，如“C:\”，而它内部的文件没有“C:\360”
	if (cPath.Right(1) != _T("\\"))
	{
		cPath += _T("\\");
	}
	BOOL flag ;
	CFileFind findfile;

	//判断当前路径是否有文件
	flag = findfile.FindFile(cPath+_T("*.*"));

	while (flag)
	{
		//判断是否还有下一个文件
		flag = findfile.FindNextFile();
		//获取文件的名字
		CString str = findfile.GetFileName();
	
		//判断是否是“.”和“..” ，“.”代表自己和“..”代表上级目录
		if (!findfile.IsDots())
		{
			InsertItem(str,hitem); //插入项目
		}
		
	}
}



void CMyTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码

	//获得当前选中项
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	HTREEITEM hitem = HitTest(pt); //返回鼠标单击所在位置的treectrl项
	CString str = GetItemText(hitem);

	if (!str.IsEmpty())//判断是否获得的是空字符 即系统盘
	{
		//加入变量中
		m_vec.push_back(hitem);
	}

	*pResult = 0;
}
