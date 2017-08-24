// MyListCtrl.cpp : ʵ���ļ�
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

// CMyListCtrl ��Ϣ�������




void CMyListCtrl::OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	case ID_POPUP_32771:  //���Ŀ¼
		{
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
				InsertItem(Index,szpath);
				Index++;
			}
		}
		break;

	case ID_POPUP_32772:	//ɾ��Ŀ¼
		//��õ�ǰѡ����
		{
			int nindex = GetSelectionMark(); //ȡ��ѡ�мǺţ�����ֵΪ��ǩ
			if (nindex != -1)
			{
				DeleteItem(nindex);
			}
		}
		break;

	case ID_POPUP_32773:	//���Ŀ¼
		//�����ɾ��  ��ʾ���� ѯ���Ƿ�Ҫɾ��
		if (IDOK == MessageBox(_T("ȷ��Ҫɾ����?"),_T("��ܰ��ʾ"),MB_OKCANCEL))
		{
			DeleteAllItems();  //ɾ��ȫ����ǩ
		}
		break;
	}
}