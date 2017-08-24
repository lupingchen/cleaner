// MyCombiBox.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyComboBox.h"


// CMyCombiBox

IMPLEMENT_DYNAMIC(CMyComboBox, CComboBox)

CMyComboBox::CMyComboBox()
{

}

CMyComboBox::~CMyComboBox()
{
}


BEGIN_MESSAGE_MAP(CMyComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_CLOSEUP, &CMyComboBox::OnCbnCloseup)
END_MESSAGE_MAP()



// CMyCombiBox 消息处理程序

//combo box 初始化函数  自己封装
void CMyComboBox::OnInitCombobox()
{
	this->AddString(_T("默认目录"));
	this->AddString(_T("加载自定义目录"));
}


//关闭并收起时运行的事件
void CMyComboBox::OnCbnCloseup() 
{
	// TODO: 在此添加控件通知处理程序代码

	int nIndex = GetCurSel();  //获取选中项
	
	if (nIndex == 1)
	{
		//==============创建浏览文件对话框===================
		TCHAR szdisplayname[MAX_PATH] = {0};
		TCHAR szpath[MAX_PATH] = {0};
		BROWSEINFO bi;
		//初始化BROWSEINFO类变量
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

		//处理选择的选项
		if (pa)
		{
			//取路径
			SHGetPathFromIDList(pa,szpath);
			if (wcscmp(szpath , _T("")))
			{
				AddString(szpath);

				int n = GetCount();  //获得一共有多少下拉列表
				if(n>=1)
				{
					SetCurSel(n-1);  //将选中的字符串显示在combo box 上
				}
				Index++;
			}
			
		}
		//=========================================================
	}
}
