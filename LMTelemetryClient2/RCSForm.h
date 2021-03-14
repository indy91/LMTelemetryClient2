#pragma once


// RCSForm-Dialog

class RCSForm : public CDialogEx
{
	DECLARE_DYNAMIC(RCSForm)

public:
	RCSForm(CWnd* pParent = nullptr);   // Standardkonstruktor
	virtual ~RCSForm();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG9 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CEdit s10A8;
	CEdit s10A14;
	CEdit s10A15;
	CEdit s10A21;
	CEdit s10A35;
	CEdit s10A38;
	CEdit s10A66;
	CEdit s10A74;
	CEdit s10A80;
	CEdit s10A84;
	CEdit s10A112;
	CEdit s10E101;
	CEdit s10E102;
	CEdit s10E103;
	CEdit s10E104;
	CEdit s10E105;
	CEdit s10E106;
	CEdit s10E107;
	CEdit s10A124;
	CEdit s10A125;
	CEdit s10A140;
	CEdit s10A146;
	CEdit s10A162;
	CEdit s22E1a8;
	CEdit s22E1a7;
	CEdit s22E1a6;
	CEdit s22E1a5;
	CEdit s22E1a4;
	CEdit s22E1a3;
	CEdit s22E1a2;
	CEdit s22E1a1;
	CEdit s22E1b8;
	CEdit s22E1b7;
	CEdit s22E1b6;
	CEdit s22E1b5;
	CEdit s22E1b4;
	CEdit s22E1b3;
	CEdit s22E1b2;
	CEdit s22E1b1;
	CEdit s10E421;
	CEdit s10E422;
	CEdit s10E423;
	CEdit s10E424;
	CEdit s10E425;
	CEdit s10E426;
	CEdit s10E427;
	CEdit s10E428;
};
