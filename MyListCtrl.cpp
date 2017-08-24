// MyListCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_COMMAND_RANGE(ID_POPUP_32771,ID_POPUP_32773,&CMyListCtrl::OnMenu)
	ON_NOTIFY_REFLECT(NM_RCLICK, &CMyListCtrl::OnNMRClick)
END_MESSAGE_MAP()

// CMyListCtrl 消息处理程序




void CMyListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	CMenu m_PopupMenu;
	CPoint point;
	GetCursorPos(&point);
	m_PopupMenu.LoadMenuW(IDR_MENU1);
	m_PopupMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_RIGHTBUTTON,point.x,point.y,this);

	*pResult = 0;
}


void CMyListCtrl::OnMenu(UINT nID)
{
	TCHAR szdisplayname[MAX_PATH] = {0};
	TCHAR szpath[MAX_PATH] = {0};
	BROWSEINFO bi;
	static int Index = 0;
	
	switch(nID)
	{
	case ID_POPUP_32771:  //添加目录
		{
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
				InsertItem(Index,szpath);
				Index++;
			}
		}
		break;

	case ID_POPUP_32772:	//删除目录
		//获得当前选中项
		{
			int nindex = GetSelectionMark(); //取回选中记号，返回值为标签
			if (nindex != -1)
			{
				DeleteItem(nindex);
			}
		}
		break;

	case ID_POPUP_32773:	//清空目录
		//如果想删除  提示窗口 询问是否要删除
		if (IDOK == MessageBox(_T("确定要删除吗?"),_T("温馨提示"),MB_OKCANCEL))
		{
			DeleteAllItems();  //删除全部标签
		}
		break;
	}
}