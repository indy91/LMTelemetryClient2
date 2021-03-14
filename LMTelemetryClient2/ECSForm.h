#pragma once

class ECSForm : public CDialogEx
{
	DECLARE_DYNAMIC(ECSForm)

public:
	ECSForm(CWnd* pParent = nullptr);
	virtual ~ECSForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10E51;
	CEdit s10E52;
	CEdit s10E53;
	CEdit s10E54;
	CEdit s10E55;
	CEdit s10E56;
	CEdit s10E31;
	CEdit s10E32;
	CEdit s10A172;
	CEdit s10A130;
	CEdit s10E33;
	CEdit s10E34;
	CEdit s10E41;
	CEdit s10E42;
	CEdit s10E43;
	CEdit s10E45;
	CEdit s10E47;
	CEdit s10A17;
	CEdit s10A128;
	CEdit s10A59;
	CEdit s10A137;
	CEdit s10A127;
	CEdit s10A16;
	CEdit s10A83;
	CEdit s10A73;
	CEdit s10A12;
	CEdit s10A131;
	CEdit s10A90;
	CEdit s10A194;
	CEdit s10A183;
	CEdit s10A141;
	CEdit s10A154;
	CEdit s10A58;
	CEdit s10A20;
	CEdit s10A24;
	CEdit s10A13;
	CEdit s10A135;
	CEdit s10A19;
	CEdit s10A120;
	CEdit s10A25;
	CEdit s10A33;
};
