// MyDialogSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyDialogSet.h"
#include "afxdialogex.h"


// CMyDialogSet �Ի���

IMPLEMENT_DYNAMIC(CMyDialogSet, CDialogEx)

CMyDialogSet::CMyDialogSet(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDialogSet::IDD, pParent)
{

}

CMyDialogSet::~CMyDialogSet()
{
}

void CMyDialogSet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_CombBox);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
}


BEGIN_MESSAGE_MAP(CMyDialogSet, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CMyDialogSet::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &CMyDialogSet::OnBnClickedOk)
END_MESSAGE_MAP()


// CMyDialogSet ��Ϣ�������


BOOL CMyDialogSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	m_CombBox.OnInitCombobox();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CMyDialogSet::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	/*HTREEITEM  nn = m_TreeCtrl.InsertItem(_T("�����"));
	m_TreeCtrl.InsertItem(_T("C��"),nn,NULL);
	HTREEITEM MM = m_TreeCtrl.InsertItem(_T("D��"),nn,NULL);
	m_TreeCtrl.InsertItem(_T("�½��ļ���"),MM,NULL);*/

	//���combox����ϵ�����
	CString str;
	m_CombBox.GetWindowText(str); //��ȡ��ǰ�ؼ��ϵ�����
	//���뵽tree�ؼ���
	if (!str.IsEmpty())		//�жϵ�ǰ�ַ����Ƿ�Ϊ��
	{
		//��tree�ؼ��ϲ����ȡ������
		HTREEITEM  root = m_TreeCtrl.InsertItem(str); 

		//����ǰ·���µ��ļ���ʾ����
		m_TreeCtrl.OnFindFile(str,root);
		
	}

}


void CMyDialogSet::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	//��������������
	for (m_TreeCtrl.m_iter = m_TreeCtrl.m_vec.begin();m_TreeCtrl.m_iter != m_TreeCtrl.m_vec.end();m_TreeCtrl.m_iter++)
	{
		//������ѡ��
		if ( m_TreeCtrl.GetCheck( (*m_TreeCtrl.m_iter) ) )  //GetCheck�ж��ǹ���ѡ��
		{
			//��õ�ǰѡ��������ݣ�ȡ���ļ���׺������������
			CString str = m_TreeCtrl.GetItemText( (*m_TreeCtrl.m_iter) );
			int nindex = str.ReverseFind('.');  //���ַ������濪ʼ�����ַ�

			if (-1 != nindex)
			{
				str = str.Right(str.GetLength() - nindex); // ��ȡ��׺

				//�жϵ�ǰ�������Ƿ���ڴ˺�׺ �� ���������������������
				m_iter = find(m_list.begin(),m_list.end(),str);
				if ( m_iter == m_list.end() )
				{
					m_list.push_back(str);
				}
			}
		}
	}

	CDialogEx::OnOK();
}
