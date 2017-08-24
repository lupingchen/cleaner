// MyPicture.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyPicture.h"


// CMyPicture

IMPLEMENT_DYNAMIC(CMyPicture, CStatic)

CMyPicture::CMyPicture()
{

}

CMyPicture::~CMyPicture()
{
}


BEGIN_MESSAGE_MAP(CMyPicture, CStatic)
	ON_CONTROL_REFLECT(STN_CLICKED, &CMyPicture::OnStnClicked)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



// CMyPicture 消息处理程序




void CMyPicture::OnStnClicked()
{
	// TODO: 在此添加控件通知处理程序代码

	//1.win32
	//m_Picture1.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP2)));

	//2.MFC
	static UINT arrBitmap[] = {IDB_BITMAP3,IDB_BITMAP2,IDB_BITMAP1};
	CBitmap bitmap;
	static int i = 0;
	i = i%3;
	bitmap.LoadBitmap(arrBitmap[i]);
	SetBitmap((HBITMAP)bitmap.m_hObject);  //SetBitmap换图片
	++i;
	bitmap.Detach();  //对象和资源分离
}


//功能：按下右键，提示选择图片，然后在控件上显示选择的图片
void CMyPicture::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	
	CFileDialog dlg(TRUE);	//创建文件对话框对象
	
	if (dlg.DoModal() == IDOK)  //判断是按下“确定”
	{
		
		CRect rect;
		this->GetClientRect(rect); //谁调用就获取谁的大小

		CString strPath = dlg.GetPathName();	//1.获取路径名字

		CImage image;
		image.Load(strPath);	//2.加载图片

		CClientDC dc(this);	//谁调用 就获取谁的dc
		//image.StretchBlt(dc.m_hDC,0,0,rect.Width(),rect.Height(),SRCCOPY); //3.拉伸拷贝图片,将图片拉伸或缩小成指定大小

		//==================将选择的图片拉伸拷贝成控件大小 并在控件上显示========================
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());

		CDC cdc;
		cdc.CreateCompatibleDC(&dc);

		cdc.SelectObject(&bitmap); //创建一个控件大小的位图，并与cdc关联，然后将图片拉伸拷贝到cdc的位图上

		image.StretchBlt(cdc.m_hDC,0,0,rect.Width(),rect.Height(),SRCCOPY); //拉伸拷贝图片,将image图片拉伸拷贝到指定位图上
		
		SetBitmap(bitmap); //换图片


		bitmap.Detach();	//对象与资源分离

		Invalidate(); //重绘窗口
		//===============================================================================
	}

	CStatic::OnRButtonDown(nFlags, point);
}
