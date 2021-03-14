#pragma once

class RadarForm : public CDialogEx
{
	DECLARE_DYNAMIC(RadarForm)

public:
	RadarForm(CWnd* pParent = nullptr); 
	virtual ~RadarForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG6 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10E11;
	CEdit s10E12;
	CEdit s10E13;
	CEdit s10A138;
	CEdit s10A164;
};
