#pragma once

class SCIForm : public CDialogEx
{
	DECLARE_DYNAMIC(SCIForm)

public:
	SCIForm(CWnd* pParent = nullptr);
	virtual ~SCIForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); 

	DECLARE_MESSAGE_MAP()
public:
	CEdit s11A26;
	CEdit s11A36;
	CEdit s10A85;
	CEdit s10E71;
	CEdit s10E72;
	CEdit s10E73;
	CEdit s10E76;
	CEdit s10E74;
	CEdit s10E75;
	CEdit s10A171;
	CEdit s10A180;
	CEdit s10E78;
	CEdit s10E401;
};
