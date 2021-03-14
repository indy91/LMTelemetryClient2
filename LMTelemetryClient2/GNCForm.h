#pragma once

class GNCForm : public CDialogEx
{
	DECLARE_DYNAMIC(GNCForm)

public:
	GNCForm(CWnd* pParent = nullptr); 
	virtual ~GNCForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A23;
	CEdit s10A121;
	CEdit s10A5;
	CEdit s10E61;
	CEdit s10E62;
	CEdit s11A16;
	CEdit s11A14;
	CEdit s11A9;
	CEdit s10A7;
	CEdit s11A24;
	CEdit s10A64;
	CEdit s10A123;
	CEdit s10E21;
	CEdit s10E22;
	CEdit s10A2;
	CEdit s51A1;
	CEdit s51A2;
	CEdit s51A3;
	CEdit s12A1;
	CEdit s12A3;
	CEdit s12A13;
	CEdit s11A35;
	CEdit s11A17;
	CEdit s11A23;
	CEdit s11A11;
	CEdit s11A10;
	CEdit s11A20;
	CEdit s11A32;
};
