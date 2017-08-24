// MyTreeCtrl.cpp : ʵ���ļ�
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



// CMyTreeCtrl ��Ϣ�������


//�����+��ťʱ�ߵĺ���
void CMyTreeCtrl::OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//1.��õ�ǰѡ�����Ҫչ����
	HTREEITEM hCurrentitem = pNMTreeView->itemNew.hItem; //��ǰѡ�����ڲ����о���

	CString str = GetItemText(hCurrentitem);  //��ø��������

	//2.��õ�ǰѡ����Ķ�����
	HTREEITEM hSonitem  = GetChildItem(hCurrentitem);

	while(hSonitem != nullptr)  //�����ж��ӼӶ���
	{
		//ɾ��hSonitem�Ķ���
		OnDelete(hSonitem);
		//3.����ǰѡ����Ķ����ǼӶ���
		CString str = OnGetParentPath(hSonitem);
			//��õ�ǰ���·��
		OnFindFile(str,hSonitem);
		//4.�Ҷ��ӵ��ֵ�
		hSonitem = GetNextSiblingItem(hSonitem);
	}
	
	*pResult = 0;
}

//ɾ������
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

//��õ�ǰ���·��
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
		//��ø�����
		hitem = GetParentItem(hitem);
	}
	
	return hpath;
}

//�ҵ���ǰ��Ķ���
void CMyTreeCtrl::OnFindFile(CString cPath , HTREEITEM hitem)
{
	//�жϵ�ǰ��·���Ƿ��\ ��ϵͳ�̶��Դ�\���硰C:\���������ڲ����ļ�û�С�C:\360��
	if (cPath.Right(1) != _T("\\"))
	{
		cPath += _T("\\");
	}
	BOOL flag ;
	CFileFind findfile;

	//�жϵ�ǰ·���Ƿ����ļ�
	flag = findfile.FindFile(cPath+_T("*.*"));

	while (flag)
	{
		//�ж��Ƿ�����һ���ļ�
		flag = findfile.FindNextFile();
		//��ȡ�ļ�������
		CString str = findfile.GetFileName();
	
		//�ж��Ƿ��ǡ�.���͡�..�� ����.�������Լ��͡�..�������ϼ�Ŀ¼
		if (!findfile.IsDots())
		{
			InsertItem(str,hitem); //������Ŀ
		}
		
	}
}



void CMyTreeCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��õ�ǰѡ����
	CPoint pt;
	GetCursorPos(&pt);
	ScreenToClient(&pt);
	HTREEITEM hitem = HitTest(pt); //������굥������λ�õ�treectrl��
	CString str = GetItemText(hitem);

	if (!str.IsEmpty())//�ж��Ƿ��õ��ǿ��ַ� ��ϵͳ��
	{
		//���������
		m_vec.push_back(hitem);
	}

	*pResult = 0;
}
