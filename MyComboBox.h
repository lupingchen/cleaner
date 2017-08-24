#pragma once


// CMyCombiBox

class CMyComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CMyComboBox)

public:
	CMyComboBox();
	virtual ~CMyComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	void OnInitCombobox();
	afx_msg void OnCbnCloseup();
};


