#pragma once


// CMyPicture

class CMyPicture : public CStatic
{
	DECLARE_DYNAMIC(CMyPicture)

public:
	CMyPicture();
	virtual ~CMyPicture();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClicked();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};


