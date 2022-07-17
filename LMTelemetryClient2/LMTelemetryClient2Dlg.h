
// LMTelemetryClient2Dlg.h
//

#pragma once

#include "EPSForm.h"
#include "ECSForm.h"
#include "GNCForm.h"
#include "CESForm.h"
#include "SCIForm.h"
#include "RadarForm.h"
#include "APSForm.h"
#include "DPSForm.h"
#include "RCSForm.h"
#include "COMM_ED_Form.h"
#include "LGCForm.h"
#include "UplinkForm.h"

struct LGCDownlinkFormatEntry
{
	LGCDownlinkFormatEntry();
	int type[2]; //0 = do nothing, 1 = double precision (ignore type2), 2 = raw octal
	int disp[2]; //Number used for LGCWriteToForm
	double CF[2];
	int Scale[2];
};

class CLMTelemetryClient2Dlg : public CDialogEx
{
public:
	CLMTelemetryClient2Dlg(CWnd* pParent = nullptr);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LMTELEMETRYCLIENT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);


protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	int ThreadTask()
	{
		CommThread();
		return 0;
	}

	void send_agc_key(char key);
protected:
	void ConnectToHost();
	void WinsockInit();
	void CommThread();
	void display(unsigned char data, int channel, int type, int ccode);
	void parse_lbr(unsigned char data, int bytect);
	void parse_hbr(unsigned char data, int bytect);
	void parse_lgc();
	void setup_lgc_list();
	void DoLGCLock();
	void ProcessLGC();
	void LGCWriteToForm(int out);
	void ReadLGCDownlinkFormatFromFile();
	void ProcessDSKY();
	char get_dsky_char(unsigned int bits);
	void end_lbr();
	void end_hbr();

	void ShowEPS();
	void ShowECS();
	void ShowGNC();

	void showVolts(CEdit *tb, unsigned char data, double low, double high);
	void showAmps(CEdit *tb, unsigned char data, double low, double high);
	void showTempF(CEdit *tb, unsigned char data, double low, double high);
	void showPSIA(CEdit *tb, unsigned char data, double low, double high);
	void showMMHG(CEdit *tb, unsigned char data, double low, double high);
	void showCPS(CEdit *tb, unsigned char data, double low, double high);
	void showKC(CEdit *tb, unsigned char data, double low, double high);
	void showWatts(CEdit *tb, unsigned char data, double low, double high);
	void showRPM(CEdit *tb, unsigned char data, double low, double high);
	void showPercentage(CEdit *tb, unsigned char data, double maxPercent);
	void showPercentage(CEdit *tb, unsigned char data);
	void showEvent(CEdit *tb, unsigned char data, int bit);
	void showValue(CEdit *tb);

	double unscale_data(unsigned char data, double low, double high);
	double ScaleAGCSingle(unsigned int word, double scale, bool issigned = true);
	double ScaleAGCDouble(unsigned int w0, unsigned int w1, double scale);

	// Winsock
	WSADATA wsaData;
	SOCKET m_socket;
	sockaddr_in clientService;
	int conn_status;

	HANDLE hThread;

	int lock_type;
	int framect;
	int framead;
	int frame_addr;

	// LGC datastream parser
	unsigned int lgc_word[2];
	unsigned int lgc_upbuff__nogc[20];
	unsigned int lgc_compnumb;
	unsigned int lgc_upoldmod;
	unsigned int lgc_upverb;
	unsigned int lgc_upcount;
	unsigned int lgc_upindex;
	int lgc_lock_type;
	int lgc_framect;
	int lgc_frame_addr;
	unsigned lgc_raw_data[100][2];
	LGCDownlinkFormatEntry LGCDownlinkFormat[6][100];
	unsigned dsptab[12];

	CString msg;
	char msg2[256];

	EPSForm *eps_form;
	ECSForm *ecs_form;
	GNCForm *gnc_form;
	CESForm *ces_form;
	SCIForm *sci_form;
	RadarForm *radar_form;
	APSForm *aps_form;
	DPSForm *dps_form;
	RCSForm *rcs_form;
	COMM_ED_Form *comm_ed_form;
	LGCForm *lgc_form;
	UplinkForm *uplink_form;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton12();
	afx_msg void OnBnClickedButton13();
	afx_msg void OnBnClickedButton15();
};
