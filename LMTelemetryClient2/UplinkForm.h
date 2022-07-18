#pragma once

class CLMTelemetryClient2Dlg;

class UplinkForm : public CDialogEx
{
	DECLARE_DYNAMIC(UplinkForm)

public:
	UplinkForm(CWnd* pParent = nullptr);   // Standardkonstruktor
	virtual ~UplinkForm();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG12 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CLMTelemetryClient2Dlg *parent;
	CEdit DSKY_Prog;
	CEdit DSKY_Verb;
	CEdit DSKY_Noun;
	CEdit DSKY_R1;
	CEdit DSKY_R2;
	CEdit DSKY_R3;
	afx_msg void OnBnClickedButtonDSKY_0();
	afx_msg void OnBnClickedButtonDSKY_1();
	afx_msg void OnBnClickedButtonDSKY_2();
	afx_msg void OnBnClickedButtonDSKY_3();
	afx_msg void OnBnClickedButtonDSKY_4();
	afx_msg void OnBnClickedButtonDSKY_5();
	afx_msg void OnBnClickedButtonDSKY_6();
	afx_msg void OnBnClickedButtonDSKY_7();
	afx_msg void OnBnClickedButtonDSKY_8();
	afx_msg void OnBnClickedButtonDSKY_9();
	afx_msg void OnBnClickedButtonDSKY_V();
	afx_msg void OnBnClickedButtonDSKY_N();
	afx_msg void OnBnClickedButtonDSKY_R();
	afx_msg void OnBnClickedButtonDSKY_C();
	afx_msg void OnBnClickedButtonDSKY_K();
	afx_msg void OnBnClickedButtonDSKY_E();
	CStatic DSKY_ProgAlarm;
	CStatic DSKY_Tracker;
	CStatic DSKY_GimbalLock;
	CStatic DSKY_Alt;
	CStatic DSKY_NoAtt;
	CStatic DSKY_Vel;
	CStatic DSKY_UplinkActivity;
	CStatic DSKY_Temp;
	CStatic DSKY_Standby;
	CStatic DSKY_KeyReleaseLight;
	CStatic DSKY_Restart;
	CStatic DSKY_OperatorError;
	CEdit s10E411;
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	CEdit s10E235;
};
