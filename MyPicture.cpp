// MyPicture.cpp : ʵ���ļ�
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



// CMyPicture ��Ϣ�������




void CMyPicture::OnStnClicked()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//1.win32
	//m_Picture1.SetBitmap(LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BITMAP2)));

	//2.MFC
	static UINT arrBitmap[] = {IDB_BITMAP3,IDB_BITMAP2,IDB_BITMAP1};
	CBitmap bitmap;
	static int i = 0;
	i = i%3;
	bitmap.LoadBitmap(arrBitmap[i]);
	SetBitmap((HBITMAP)bitmap.m_hObject);  //SetBitmap��ͼƬ
	++i;
	bitmap.Detach();  //�������Դ����
}


//���ܣ������Ҽ�����ʾѡ��ͼƬ��Ȼ���ڿؼ�����ʾѡ���ͼƬ
void CMyPicture::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	
	CFileDialog dlg(TRUE);	//�����ļ��Ի������
	
	if (dlg.DoModal() == IDOK)  //�ж��ǰ��¡�ȷ����
	{
		
		CRect rect;
		this->GetClientRect(rect); //˭���þͻ�ȡ˭�Ĵ�С

		CString strPath = dlg.GetPathName();	//1.��ȡ·������

		CImage image;
		image.Load(strPath);	//2.����ͼƬ

		CClientDC dc(this);	//˭���� �ͻ�ȡ˭��dc
		//image.StretchBlt(dc.m_hDC,0,0,rect.Width(),rect.Height(),SRCCOPY); //3.���쿽��ͼƬ,��ͼƬ�������С��ָ����С

		//==================��ѡ���ͼƬ���쿽���ɿؼ���С ���ڿؼ�����ʾ========================
		CBitmap bitmap;
		bitmap.CreateCompatibleBitmap(&dc,rect.Width(),rect.Height());

		CDC cdc;
		cdc.CreateCompatibleDC(&dc);

		cdc.SelectObject(&bitmap); //����һ���ؼ���С��λͼ������cdc������Ȼ��ͼƬ���쿽����cdc��λͼ��

		image.StretchBlt(cdc.m_hDC,0,0,rect.Width(),rect.Height(),SRCCOPY); //���쿽��ͼƬ,��imageͼƬ���쿽����ָ��λͼ��
		
		SetBitmap(bitmap); //��ͼƬ


		bitmap.Detach();	//��������Դ����

		Invalidate(); //�ػ洰��
		//===============================================================================
	}

	CStatic::OnRButtonDown(nFlags, point);
}
