#pragma once

class COMM_ED_Form : public CDialogEx
{
	DECLARE_DYNAMIC(COMM_ED_Form)

public:
	COMM_ED_Form(CWnd* pParent = nullptr); 
	virtual ~COMM_ED_Form();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG10 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A81;
	CEdit s10A107;
	CEdit s10E111;
	CEdit s10E114;
	CEdit s10E115;
	CEdit s10E116;
	CEdit s10E117;
	CEdit s10A152;
	CEdit s10A185;
	CEdit s10A195;
};
