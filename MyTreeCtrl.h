#pragma once

#include <vector>
using namespace std;
// CMyTreeCtrl

class CMyTreeCtrl : public CTreeCtrl
{
	DECLARE_DYNAMIC(CMyTreeCtrl)

public:
	CMyTreeCtrl();
	virtual ~CMyTreeCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTvnItemexpanding(NMHDR *pNMHDR, LRESULT *pResult);
	void OnFindFile(CString cPath , HTREEITEM hitem);
	CString OnGetParentPath(HTREEITEM hitem);
	void OnDelete(HTREEITEM hitem);
	afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);

public:
	vector<HTREEITEM> m_vec;
	vector<HTREEITEM>::iterator m_iter;
};


