#pragma once

class APSForm : public CDialogEx
{
	DECLARE_DYNAMIC(APSForm)

public:
	APSForm(CWnd* pParent = nullptr);
	virtual ~APSForm();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG7 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A37;
	CEdit s10A61;
	CEdit s10A62;
	CEdit s10A93;
	CEdit s10A114;
	CEdit s10A129;
	CEdit s10A153;
	CEdit s10A173;
	CEdit s10E241;
	CEdit s10E242;
	CEdit s10A70;
	CEdit s11A4;
	CEdit s11A22;
	CEdit s10E431;
	CEdit s10E432;
	CEdit s10E323;
	CEdit s10E324;
};
