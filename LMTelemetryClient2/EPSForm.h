#pragma once

class EPSForm : public CDialogEx
{
	DECLARE_DYNAMIC(EPSForm)

public:
	EPSForm(CWnd* pParent = nullptr); 
	virtual ~EPSForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A9;
	CEdit s10A36;
	CEdit s10A82;
	CEdit s10A174;
	CEdit s10A126;
	CEdit s10A134;
	CEdit s10A91;
	CEdit s10A122;
	CEdit s10A63;
	CEdit s10A67;
	CEdit s10A68;
	CEdit s10A75;
	CEdit s10A72;
	CEdit s10A41;
	CEdit s10A79;
	CEdit s10A57;
	CEdit s10E301;
	CEdit s10E302;
	CEdit s10E303;
	CEdit s10E304;
	CEdit s10E305;
	CEdit s10E306;
	CEdit s10E307;
	CEdit s10E308;
	CEdit s10E331;
	CEdit s10E332;
	CEdit s10E333;
	CEdit s10E334;
	CEdit s10E291;
	CEdit s10E292;
	CEdit s10E293;
	CEdit s10E294;
	CEdit s10E295;
	CEdit s10E296;
};
