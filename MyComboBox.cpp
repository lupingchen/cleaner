// MyCombiBox.cpp : ʵ���ļ�
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



// CMyCombiBox ��Ϣ�������

//combo box ��ʼ������  �Լ���װ
void CMyComboBox::OnInitCombobox()
{
	this->AddString(_T("Ĭ��Ŀ¼"));
	this->AddString(_T("�����Զ���Ŀ¼"));
}


//�رղ�����ʱ���е��¼�
void CMyComboBox::OnCbnCloseup() 
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	int nIndex = GetCurSel();  //��ȡѡ����
	
	if (nIndex == 1)
	{
		//==============��������ļ��Ի���===================
		TCHAR szdisplayname[MAX_PATH] = {0};
		TCHAR szpath[MAX_PATH] = {0};
		BROWSEINFO bi;
		//��ʼ��BROWSEINFO�����
		static int Index = 0;
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

		//����ѡ���ѡ��
		if (pa)
		{
			//ȡ·��
			SHGetPathFromIDList(pa,szpath);
			if (wcscmp(szpath , _T("")))
			{
				AddString(szpath);

				int n = GetCount();  //���һ���ж��������б�
				if(n>=1)
				{
					SetCurSel(n-1);  //��ѡ�е��ַ�����ʾ��combo box ��
				}
				Index++;
			}
			
		}
		//=========================================================
	}
}
