#pragma once

class DPSForm : public CDialogEx
{
	DECLARE_DYNAMIC(DPSForm)

public:
	DPSForm(CWnd* pParent = nullptr);
	virtual ~DPSForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG8 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A40;
	CEdit s10A10;
	CEdit s10A18;
	CEdit s10A42;
	CEdit s10A76;
	CEdit s10A101;
	CEdit s10A104;
	CEdit s10A113;
	CEdit s10A133;
	CEdit s10A165;
	CEdit s10A193;
	CEdit s10A3;
	CEdit s10A4;
	CEdit s10A108;
	CEdit s10A6;
	CEdit s10A117;
	CEdit s10A34;
	CEdit s10E322;
};
