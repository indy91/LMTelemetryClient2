#pragma once

class CESForm : public CDialogEx
{
	DECLARE_DYNAMIC(CESForm)

public:
	CESForm(CWnd* pParent = nullptr);
	virtual ~CESForm();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A11;
	CEdit s10A22;
	CEdit s10A26;
	CEdit s51E11;
	CEdit s51E12;
	CEdit s11A19;
	CEdit s11A29;
	CEdit s11A38;
	CEdit s10A60;
	CEdit s10A65;
	CEdit s10A115;
	CEdit s10A132;
	CEdit s10A139;
	CEdit s10A155;
	CEdit s10A175;
	CEdit s10A186;
	CEdit s10E231;
	CEdit s10E232;
	CEdit s10E233;
	CEdit s10E234;
	CEdit s10E235;
	CEdit s12E11;
	CEdit s12E12;
	CEdit s12E13;
	CEdit s12E14;
	CEdit s12E15;
	CEdit s12E16;
	CEdit s12E17;
	CEdit s12E18;
	CEdit s12E41;
	CEdit s12E42;
	CEdit s12E43;
	CEdit s12E44;
	CEdit s12E45;
	CEdit s12E46;
	CEdit s12E47;
	CEdit s12E48;
	CEdit s10E311;
	CEdit s10E312;
	CEdit s10E313;
	CEdit s10E314;
	CEdit s10E315;
	CEdit s10E316;
	CEdit s10E317;
	CEdit s10E318;
	CEdit s10E411;
	CEdit s10E412;
	CEdit s10E413;
	CEdit s10E414;
	CEdit s11A1;
	CEdit s11A8;
	CEdit s11A18;
	CEdit s10E271;
	CEdit s10E272;
	CEdit s10E273;
	CEdit s10E274;
	CEdit s10E275;
};
