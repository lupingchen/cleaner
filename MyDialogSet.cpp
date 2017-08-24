// MyDialogSet.cpp : 实现文件
//

#include "stdafx.h"
#include "Cleaner.h"
#include "MyDialogSet.h"
#include "afxdialogex.h"


// CMyDialogSet 对话框

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


// CMyDialogSet 消息处理程序


BOOL CMyDialogSet::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_CombBox.OnInitCombobox();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CMyDialogSet::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	/*HTREEITEM  nn = m_TreeCtrl.InsertItem(_T("计算机"));
	m_TreeCtrl.InsertItem(_T("C盘"),nn,NULL);
	HTREEITEM MM = m_TreeCtrl.InsertItem(_T("D盘"),nn,NULL);
	m_TreeCtrl.InsertItem(_T("新建文件夹"),MM,NULL);*/

	//获得combox组件上的内容
	CString str;
	m_CombBox.GetWindowText(str); //获取当前控件上的内容
	//插入到tree控件上
	if (!str.IsEmpty())		//判断当前字符串是否为空
	{
		//在tree控件上插入获取的内容
		HTREEITEM  root = m_TreeCtrl.InsertItem(str); 

		//将当前路径下的文件显示出来
		m_TreeCtrl.OnFindFile(str,root);
		
	}

}


void CMyDialogSet::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	//遍历向量或链表
	for (m_TreeCtrl.m_iter = m_TreeCtrl.m_vec.begin();m_TreeCtrl.m_iter != m_TreeCtrl.m_vec.end();m_TreeCtrl.m_iter++)
	{
		//如果这项被选中
		if ( m_TreeCtrl.GetCheck( (*m_TreeCtrl.m_iter) ) )  //GetCheck判断是够被选中
		{
			//获得当前选中项的内容，取出文件后缀，并存入链表
			CString str = m_TreeCtrl.GetItemText( (*m_TreeCtrl.m_iter) );
			int nindex = str.ReverseFind('.');  //从字符串后面开始查找字符

			if (-1 != nindex)
			{
				str = str.Right(str.GetLength() - nindex); // 获取后缀

				//判断当前链表中是否存在此后缀 ， 如果如果不存在则加入链表
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
