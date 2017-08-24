// MyTabCtrl.cpp : ʵ���ļ�
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



// CMyTabCtrl ��Ϣ�������


//�Լ���װ�ĳ�ʼ������
bool CMyTabCtrl::OnInitTabCtrl(int nCount , UINT nTabCtrl[])	
{
	//У�����
	if (nCount<=0 || !nTabCtrl)
	{
		return false;
	}

	CString str;
	for (int i = 0;i<nCount;++i)
	{
		str.LoadString(nTabCtrl[i]); //�����ַ���
		InsertItem(i,str);		//����tab�ؼ�TabCtrl�ı�ǩ,InsertItem��CTabCtrl���еĳ�Ա����
	}
	return true;
}


//�Լ���װ�ĳ�ʼ���Ի�����
void CMyTabCtrl::OnInitPage()
{
	//������ģ̬�Ի���
	m_dlg.Create(IDD_DIALOG_CLEAN,this);
	m_dlg.ShowWindow(SW_SHOW);

	CRect rect,rectdialog;

	//��õ�ǰ�ؼ�����
	GetClientRect(rect);

	//��ñ�ǩ�߶�
	this->GetItemRect(0,&rectdialog);

	//�ƶ��Ի���ָ��λ��
	rect.top += rectdialog.Height();
	
	//�ı䴰��λ�úʹ�С
	m_dlg.MoveWindow(rect);	
}



void CMyTabCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//1.��õ�ǰѡ�еı�ǩ
	CCleanerDlg* dig_parent = (CCleanerDlg*)GetParent();
	int nindex = GetCurSel(); //��õ�ǰѡ�е�tab��ǩ
	static bool bflag = true;
	if (nindex == 1)
	{

		//�ı䴰�ڴ�С
		if (bflag)
		{
			//�����
			//dig_parent->MoveWindow(dig_parent->m_RectBig);
			//dig_parent->SetWindowPos(&wndTopMost,0,0,dig_parent->m_RectBig.Width(),dig_parent->m_RectBig.Height(),SWP_NOMOVE);

			SetTimer(10,10,NULL); //���ö�ʱ��  Ϊ�˴ﵽ��̬Ч��
		}
		else
		{
			//С����
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


//��ʱ��������
void CMyTabCtrl::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CCleanerDlg* dig_parent = (CCleanerDlg*)GetParent();
	//�ж϶�ʱ��ID
	if (nIDEvent == 10)
	{
		CRect rect;
		dig_parent->GetWindowRect(&rect); //��õ�ǰ�����ڵĴ�С
		if (rect.Height()+10 <= dig_parent->m_RectBig.Height())
		{
			dig_parent->SetWindowPos(/*&CWnd::wndTopMost*/ NULL,0,0,dig_parent->m_RectBig.Width(),rect.Height()+10,SWP_NOMOVE);
		}
		else
		{
			dig_parent->SetWindowPos(/*&CWnd::wndTopMost*/NULL ,0,0,dig_parent->m_RectBig.Width(),dig_parent->m_RectBig.Height(),SWP_NOMOVE);
			KillTimer(10);  //ֹͣ��ʱ������
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
