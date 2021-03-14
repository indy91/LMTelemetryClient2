
// LMTelemetryClient2Dlg.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "LMTelemetryClient2Dlg.h"
#include "afxdialogex.h"
#include "ws2tcpip.h"
#include <iostream>
#include <fstream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Telemetry measurement types
#define LTLM_A		1
#define LTLM_D		2
#define LTLM_DS		3
#define LTLM_E		4

#define LTLM_LGC_COAST_ALIGN 1
#define LTLM_LGC_AGS_INIT_UPDATE 2
#define LTLM_LGC_RENDEZVOUS_PRETHRUST 3
#define LTLM_LGC_ORBITAL_MANEUVERS 4
#define LTLM_LGC_DESCENT_ASCENT 5
#define LTLM_LGC_SURFACE_ALIGN 6

LGCDownlinkFormatEntry::LGCDownlinkFormatEntry()
{
	for (int i = 0;i < 2;i++)
	{
		type[i] = 0;
		disp[i] = 0;
		CF[i] = 0.0;
		Scale[i] = 0;
	}
}

static DWORD WINAPI LMTelemetry_Trampoline(LPVOID ptr) {
	CLMTelemetryClient2Dlg *client = (CLMTelemetryClient2Dlg *)ptr;
	return(client->ThreadTask());
}

CLMTelemetryClient2Dlg::CLMTelemetryClient2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LMTELEMETRYCLIENT2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLMTelemetryClient2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLMTelemetryClient2Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CLMTelemetryClient2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLMTelemetryClient2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CLMTelemetryClient2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CLMTelemetryClient2Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CLMTelemetryClient2Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON7, &CLMTelemetryClient2Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CLMTelemetryClient2Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CLMTelemetryClient2Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &CLMTelemetryClient2Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &CLMTelemetryClient2Dlg::OnBnClickedButton12)
	ON_BN_CLICKED(IDC_BUTTON13, &CLMTelemetryClient2Dlg::OnBnClickedButton13)
	ON_BN_CLICKED(IDC_BUTTON15, &CLMTelemetryClient2Dlg::OnBnClickedButton15)
END_MESSAGE_MAP()

BOOL CLMTelemetryClient2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//SetIcon(m_hIcon, TRUE);

	GetDlgItem(IDC_EDIT1)->SetWindowText(L"127.0.0.1");
	hThread = NULL;
	eps_form = NULL;
	ecs_form = NULL;
	gnc_form = NULL;
	ces_form = NULL;
	sci_form = NULL;
	radar_form = NULL;
	aps_form = NULL;
	dps_form = NULL;
	rcs_form = NULL;
	comm_ed_form = NULL;
	lgc_form = NULL;
	WinsockInit();
	for (int i = 0;i < 100;i++)
	{
		lgc_raw_data[i][0] = 0;
		lgc_raw_data[i][1] = 0;
	}

	ReadLGCDownlinkFormatFromFile();

	return TRUE;
}

void CLMTelemetryClient2Dlg::OnCancel()
{
	DWORD exitcode = 0;
	if (TerminateThread(hThread, exitcode))
	{
		if (hThread != NULL) { CloseHandle(hThread); }
	}
	conn_status = 0;
	shutdown(m_socket, SD_BOTH);
	closesocket(m_socket);
	if (eps_form)
	{
		delete eps_form;
		eps_form = NULL;
	}
	if (ecs_form)
	{
		delete ecs_form;
		ecs_form = NULL;
	}
	if (gnc_form)
	{
		delete gnc_form;
		gnc_form = NULL;
	}
	if (ces_form)
	{
		delete ces_form;
		ces_form = NULL;
	}
	if (sci_form)
	{
		delete sci_form;
		sci_form = NULL;
	}
	if (radar_form)
	{
		delete radar_form;
		radar_form = NULL;
	}
	if (aps_form)
	{
		delete aps_form;
		aps_form = NULL;
	}
	if (dps_form)
	{
		delete dps_form;
		dps_form = NULL;
	}
	if (rcs_form)
	{
		delete rcs_form;
		rcs_form = NULL;
	}
	if (comm_ed_form)
	{
		delete comm_ed_form;
		comm_ed_form = NULL;
	}
	if (lgc_form)
	{
		delete lgc_form;
		lgc_form = NULL;
	}

	DestroyWindow();
}

void CLMTelemetryClient2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CLMTelemetryClient2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLMTelemetryClient2Dlg::WinsockInit()
{
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"Error at WSAStartup()");
		return;
	}
	else {
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"Disconnected, Winsock Ready");
	}
};

void CLMTelemetryClient2Dlg::ConnectToHost()
{
	CString addr;

	if (conn_status == 0) {
		GetDlgItem(IDC_EDIT2)->SetWindowText(L"Connecting...");
		m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (m_socket == INVALID_SOCKET) {
			sprintf_s(msg2,"Error at socket(): %ld", WSAGetLastError());
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
			closesocket(m_socket);
			return;
		}
		// Address to ANSI string
		GetDlgItem(IDC_EDIT1)->GetWindowTextW(addr);
		CStringA addr2(addr);
		const char* addr3 = addr2;

		// Now connect
		clientService.sin_family = AF_INET;
		//clientService.sin_addr.s_addr = inet_addr(addr3);
		inet_pton(AF_INET, addr3, &clientService.sin_addr.s_addr);
		clientService.sin_port = htons(14243);

		if (connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR) {
			sprintf_s(msg2, "Failed to connect, Error %ld", WSAGetLastError());
			msg = msg2;
			closesocket(m_socket);
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
			return;
		}
		else {
			GetDlgItem(IDC_EDIT2)->SetWindowText(L"LOCK/OUT FRAM/000 WORD/000");
			DWORD id = 0;
			hThread = CreateThread(NULL, 0, LMTelemetry_Trampoline, this, 0, &id);
			DWORD err = GetLastError();
			GetDlgItem(IDC_BUTTON1)->SetWindowText(L"Disconnect");
			conn_status = 1;
		}
	}
	else {
		sprintf_s(msg2, "Disconnecting...");
		msg = msg2;
		GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		DWORD exitcode = 0;
		if (TerminateThread(hThread, exitcode))
		{
			if (hThread != NULL) { CloseHandle(hThread); }
		}
		conn_status = 0;
		shutdown(m_socket, SD_BOTH);
		closesocket(m_socket);
		GetDlgItem(IDC_BUTTON1)->SetWindowText(L"Connect");
	}
}

void CLMTelemetryClient2Dlg::CommThread()
{
	int bytesRecv = SOCKET_ERROR;
	unsigned char recvbuf[1024];
	int die = 0;

	int frame_count = 0;
	int word_addr = 0;
	int byte_offset = 0;
	int bytect = 0;

	lock_type = 0;   lgc_lock_type = 0;
	frame_addr = 0;	 lgc_frame_addr = 0;
	framect = 0;     lgc_framect = 0;
	while (!die) {
		bytesRecv = recv(m_socket, (char *)recvbuf, 1024, 0);
		if (bytesRecv == SOCKET_ERROR) {
			sprintf_s(msg2, "Failed to read, Error %ld\n", WSAGetLastError());
			closesocket(m_socket);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
			GetDlgItem(IDC_BUTTON1)->SetWindowText(L"Connect");
			conn_status = 0;
			return;
		}
		else {
			//sprintf_s(msg, "Got %d bytes\n", bytesRecv);
			//msg2 = msg;
			//GetDlgItem(IDC_EDIT2)->SetWindowText(msg2);
			byte_offset = 0;
			while (byte_offset < bytesRecv) {
				switch (lock_type) {
				case 0: // OUT SYNC 0
					GetDlgItem(IDC_EDIT2)->SetWindowText(L"LOCK/OUT FRAM/000 WORD/000");
					bytect = 0;
					if (recvbuf[byte_offset] == 0375) { // Sync char 1 recieved
						lock_type = 1;
					}
					break;

				case 1: // OUT SYNC 1
					GetDlgItem(IDC_EDIT2)->SetWindowText(L"LOCK/OUT FRAM/000 WORD/001");
					if (recvbuf[byte_offset] == 0312) { // Sync char 2 recieved
						lock_type = 2;
					}
					else {
						lock_type = 0;
					}
					break;

				case 2: // OUT SYNC 2
					GetDlgItem(IDC_EDIT2)->SetWindowText(L"LOCK/OUT FRAM/000 WORD/002");
					if (recvbuf[byte_offset] == 0150) { // Sync char 3 recieved
						lock_type = 3;
					}
					else {
						lock_type = 0;
					}
					break;
				case 3: // OUT SYNC 3
					GetDlgItem(IDC_EDIT2)->SetWindowText(L"LOCK/OUT FRAM/000 WORD/003");
					framect = recvbuf[byte_offset] & 077;
					lock_type++;
					break;
				case 4: // OUT SYNC 4 & CHECK FOR HBR OR LBR
					GetDlgItem(IDC_EDIT2)->SetWindowText(L"LOCK/OUT FRAM/000 WORD/004");
					if (recvbuf[byte_offset] == 0344) // LBR Sync char 4 recieved
					{
						lock_type = 10;
						bytect = 5;
					}
					else if (recvbuf[byte_offset] == 033)
					{
						lock_type = 20;
						bytect = 5;
					}
					else
					{
						lock_type = 0;
					}
					break;
				case 10: //LBR SYNC
					parse_lbr(recvbuf[byte_offset], bytect);
					bytect++;
					if (bytect > 199) {
						bytect = 0;
						sprintf_s(msg2, "LOCK/LBR /%.3d\n", bytect);
						msg = msg2;
						GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
					}
					break;
				case 20: // HBR
					parse_hbr(recvbuf[byte_offset], bytect);
					bytect++;
					if (bytect > 127) {
						bytect = 0;
						sprintf_s(msg2, "LOCK/HBR FRAM/%.3d", framect);
						msg = msg2;
						GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
						frame_addr++;
						if (frame_addr > 4) {
							frame_addr = 0;
						}
					}
					break;
				}
				byte_offset++;
			}
		}
	}
}

void CLMTelemetryClient2Dlg::parse_lbr(unsigned char data, int bytect)
{
	switch (bytect) {
	case 0: // SYNC 1
		if (data != 0375) {
			end_lbr();
			lock_type = 0;

			sprintf_s(msg2, "SYNC 1 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;
	case 1: // SYNC 2
		if (data != 0312)
		{
			end_lbr();
			lock_type = 0;
			sprintf_s(msg2, "SYNC 2 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;

	case 2: // SYNC 3
		if (data != 0150)
		{
			end_lbr();
			lock_type = 0;
			sprintf_s(msg2, "SYNC 3 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;

	case 3: // SYNC 4
		if (data != 01)
		{
			end_lbr();
			lock_type = 0;
			sprintf_s(msg2, "SYNC 4 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;
	case 4: // FORMAT
		if (data != 0344)
		{
			end_lbr();
			lock_type = 0;
			sprintf_s(msg2, "NOT LBR FORMAT %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;
	case 5:
		display(data, 10, LTLM_A, 5);
		break;
	case 6:
		display(data, 10, LTLM_A, 6);
		break;
	case 7:
		display(data, 10, LTLM_A, 7);
		break;
	case 8:
		display(data, 10, LTLM_A, 8);
		break;
	case 9:
		display(data, 10, LTLM_A, 9);
		break;
	case 10:
		display(data, 10, LTLM_A, 10);
		break;
	case 11:
		display(data, 10, LTLM_A, 11);
		break;
	case 12:
		display(data, 10, LTLM_A, 12);
		break;
	case 13:
		display(data, 10, LTLM_A, 13);
		break;
	case 14:
		display(data, 10, LTLM_A, 14);
		break;
	case 15:
		display(data, 10, LTLM_A, 15);
		break;
	case 16:
		display(data, 10, LTLM_A, 16);
		break;
	case 17:
		display(data, 10, LTLM_A, 17);
		break;
	case 18:
		display(data, 10, LTLM_A, 18);
		break;
	case 19:
		display(data, 10, LTLM_A, 19);
		break;
	case 20: //10D2: Open
		break;
	case 21: //10A20: ASC 1 H2O QTY
		display(data, 10, LTLM_A, 20);
		break;
	case 22: //10A21: RCS A OX MFLD PRESS
		display(data, 10, LTLM_A, 21);
		break;
	case 23: //10A22: PITCH GDA POS (GH1313V)
		display(data, 10, LTLM_A, 22);
		break;
	case 24: //10A23: 2.5 VDC TM BIAS
		display(data, 10, LTLM_A, 24);
		break;
	case 25: //10A24: ASC 2 H2O QTY
		display(data, 10, LTLM_A, 24);
		break;
	case 26: //10A25: H2O SEP RATE
		display(data, 10, LTLM_A, 25);
		break;
	case 27: //10A26: YAW ATT ERR (GH1455V)
		display(data, 10, LTLM_A, 26);
		break;
	case 28: //10A27: ASC 2 H2O TEMP
		break;
	case 29: //10A28: ASC 1 O2 PRESS
		break;
	case 30: //10A29: GLY PUMP PRESS
		break;
	case 31: //10A30: DPS HE PRESS
		break;
	case 32: //MET
		break;
	case 33: //MET
		break;
	case 34: //MET
		break;
	case 35: //MET
		break;
	case 36: //10A35: QUAD 3 TEMP
		display(data, 10, LTLM_A, 35);
		break;
	case 37: //10A36: BAT 6 VOLT (GC0206V)
		display(data, 10, LTLM_A, 36);
		break;
	case 38: //10A37: APS HE REG PRESS 1
		display(data, 10, LTLM_A, 37);
		break;
	case 39: //10A38: RCS B OX MFLD PRESS
		display(data, 10, LTLM_A, 38);
		break;
	case 40: //10D3
		break;
	case 41: //10D4
		break;
	case 42: //51E1
		display(data, 51, LTLM_E, 1);
		break;
	case 43: //51E2
		break;
	case 44: //10A42: DPS HE REG PRESS (GQ3018P)
		display(data, 10, LTLM_A, 42);
		break;
	case 45: //11A9: MG RSVR OUT SIN (GG2142V)
		display(data, 11, LTLM_A, 9);
		break;
	case 46: //11A14: IG RSVR OUT COS
		display(data, 11, LTLM_A, 14);
		break;
	case 47: //11A16: IG RSVR OUT SIN
		display(data, 11, LTLM_A, 16);
		break;
	case 48: //10A46: CO2 PART PRESS
		break;
	case 49: //11A19: RGA YAW RATE (GH1461V)
		display(data, 11, LTLM_A, 19);
		break;
	case 50: //11A24: OG RSVR OUT SIN
		display(data, 11, LTLM_A, 24);
		break;
	case 51: //11A26: CAL 85 PCT (GL0401V)
		display(data, 11, LTLM_A, 26);
		break;
	case 52: //10A50: ASC 2 H2O QTY
		break;
	case 53: //11A29: RGA PITCH RATE (GH1462V)
		display(data, 11, LTLM_A, 29);
		break;
	case 54: //11A34: RGA ROLL RATE (GH1463V)
		break;
	case 55: //11A36: CAL 15 PCT (GL0402V)
		display(data, 11, LTLM_A, 36);
		break;
	case 56: //10A54: ASC 1 H2O QTY
		break;
	case 57: //11A38: RGA ROLL RATE (GH1463V)
		display(data, 11, LTLM_A, 38);
		break;
	case 58: //11A43: RGA YAW RATE (GH1461V)
		break;
	case 59: //11A45: RGA PITCH RATE (GH1462V)
		break;
	case 60: //10D5
		break;
	case 61: //10A58: DES H2O QTY
		display(data, 10, LTLM_A, 58);
		break;
	case 62: //10A59: PRI GLY PUMP DP (GF2021P)
		display(data, 10, LTLM_A, 59);
		break;
	case 63: //10A60: PITCH ATT ERR (GH1456V)
		display(data, 10, LTLM_A, 60);
		break;
	case 64: //10A61: APS OX PRESS (GP1503P)
		display(data, 10, LTLM_A, 61);
		break;
	case 65: //10A62: APS FUEL PRESS (GP1501P)
		display(data, 10, LTLM_A, 62);
		break;
	case 66: //10A63: BAT 3 CUR
		display(data, 10, LTLM_A, 63);
		break;
	case 67: //10A64: OG RSVR OUT COS
		display(data, 10, LTLM_A, 64);
		break;
	case 68: //10A65: ASA TEMP (GI3301T)
		display(data, 10, LTLM_A, 65);
		break;
	case 69: //10A66: RCS A FUEL TEMP (GR2121T)
		display(data, 10, LTLM_A, 66);
		break;
	case 70: //10A67: BAT 4 CUR (GC1204C)
		display(data, 10, LTLM_A, 67);
		break;
	case 71: //10A68: BAT 5 CUR (GC1205C)
		display(data, 10, LTLM_A, 68);
		break;
	case 72: //10D6: Open
		break;
	case 73: //10D7
		break;
	case 74: //10D8
		break;
	case 75: //10D9: Open
		break;
	case 76: //10A73: ASC 2 O2 PRESS
		display(data, 10, LTLM_A, 73);
		break;
	case 77: //10A74: RCS B FUEL TEMP (GR2122T)
		display(data, 10, LTLM_A, 74);
		break;
	case 78: //10A75: BAT 6 CUR (GC1206C)
		display(data, 10, LTLM_A, 75);
		break;
	case 79: //10A76: DPS TCP (GQ6510P)
		display(data, 10, LTLM_A, 76);
		break;
	case 80: //10D10: Open
		break;
	case 81: //10E1
		display(data, 10, LTLM_E, 1);
		break;
	case 82: //10E2
		display(data, 10, LTLM_E, 2);
		break;
	case 83: //10E3
		display(data, 10, LTLM_E, 3);
		break;
	case 84: //10A80: QUAD 2 TEMP (GR6003T)
		display(data, 10, LTLM_A, 80);
		break;
	case 85: //10A81: VHF RCVR B AGC (GT0625)
		display(data, 10, LTLM_A, 81);
		break;
	case 86: //10A82: AC BUS VOLTS (GC0071)
		display(data, 10, LTLM_A, 82);
	break;
	case 87: //10A83: CABIN PRESS
		display(data, 10, LTLM_A, 83);
		break;
	case 88: //10A84: QUAD 1 TEMP (GR6004T)
		display(data, 10, LTLM_A, 84);
		break;
	case 89: //10A85: PCM OSC FAIL 3 (GL0423X)
		display(data, 10, LTLM_A, 85);
		break;
	case 90: //10A86: DPS TCP (GQ6510P)
		break;
	case 91: //10A87: BAT 6 CUR (GC1206C)
		break;
	case 92: //10A88: DES H20 QTY
		break;
	case 93: //10A89: ASA TEMP (GI3301T)
		break;
	case 94: //10A90: O2 MANIFOLD PRESS
		display(data, 10, LTLM_A, 90);
		break;
	case 95: //10A91: BAT 1 CUR (GC1201C)
		display(data, 10, LTLM_A, 91);
		break;
	case 96: //10A92: APS FUEL PRESS (GP1501P)
		break;
	case 97: //10A93: APS HE 2 PRESS (GP0002P)
		display(data, 10, LTLM_A, 93);
		break;
	case 98: //10A94: BAT 4 CUR (GC1204C)
		break;
	case 99: //10A95: BAT 3 CUR (GC1203C)
		break;
	case 100: //10E4
		display(data, 10, LTLM_E, 4);
		break;
	case 101: //10A97: ASC 2 O2 PRESS 
		break;
	case 102: //10A98: CABIN PRESS
		break;
	case 103: //10A99: PRI GLY PUMP DP (GF2021P)
		break;
	case 104: //10A100: APS HE 2 PRESS (GP0002P)
		break;
	case 105: //10A101: DPS FUEL 2 QTY (GQ3604Q)
		display(data, 10, LTLM_A, 101);
		break;
	case 106: //10A102: BAT 5 CUR (GC1205C)
		break;
	case 107: //10A103: O2 MANIFOLD PRESS
		break;
	case 108: //10A104: DPS FUEL 1 QTY (GQ3603Q)
		display(data, 10, LTLM_A, 104);
		break;
	case 109: //10A105: APS OX PRESS (GP1503P)
		break;
	case 110: //10A106: BAT 1 CUR (GC1201C)
		break;
	case 111: //10A107: S-BND ANT TEMP (GT0454T)
		display(data, 10, LTLM_A, 107);
		break;
	case 112: //10E5
		display(data, 10, LTLM_E, 5);
		break;
	case 113: //10E6
		display(data, 10, LTLM_E, 6);
		break;
	case 114: //10E7
		display(data, 10, LTLM_E, 7);
		break;
	case 115: //10E8
		break;
	case 116: //10A112: RCS A REG PRESS (GR1201P)
		display(data, 10, LTLM_A, 112);
		break;
	case 117: //10A113: DPS BALL VLV TEMP (GQ4220T)
		display(data, 10, LTLM_A, 113);
		break;
	case 118: //10A114: APS FUEL TEMP (GP0718T)
		display(data, 10, LTLM_A, 114);
		break;
	case 119: //10A115: ROLL ATT ERR (GH1457V)
		display(data, 10, LTLM_A, 115);
		break;
	case 120: //10E9
		break;
	case 121: //10E10
		display(data, 10, LTLM_E, 10);
		break;
	case 122: //10E11
		display(data, 10, LTLM_E, 11);
		break;
	case 123: //10E12
		break;
	case 124: //10A120: GLY TEMP
		display(data, 10, LTLM_A, 120);
		break;
	case 125: //10A121: IMU 28 VAC 800
		display(data, 10, LTLM_A, 121);
		break;
	case 126: //10A122: BAT 2 CUR (GC1202C)
		display(data, 10, LTLM_A, 122);
		break;
	case 127: //10A123: PIPA TEMP
		display(data, 10, LTLM_A, 123);
		break;
	case 128: //10A124: RCS B HE PRESS (GR1102P)
		display(data, 10, LTLM_A, 124);
		break;
	case 129: //10A125: RCS A HE PRESS (GR1101P)
		display(data, 10, LTLM_A, 125);
		break;
	case 130: //10A126: CDR BUS VOLT (GC0301V)
		display(data, 10, LTLM_A, 126);
		break;
	case 131: //10A127: W/B GLY OUT TEMP
		display(data, 10, LTLM_A, 127);
		break;
	case 132: //10A128: CABIN TEMP
		display(data, 10, LTLM_A, 128);
		break;
	case 133: //10A129: APS OX TEMP (GP1218T)
		display(data, 10, LTLM_A, 129);
		break;
	case 134: //10A130: SUIT PRESS
		display(data, 10, LTLM_A, 130);
		break;
	case 135: //10A131: DES O2 PRESS 
		display(data, 10, LTLM_A, 131);
		break;
	case 136: //10A132: MAN THRUST CMD (GH1311V)
		display(data, 10, LTLM_A, 132);
		break;
	case 137: //10A133: DPS OX 2 QTY (GQ4104Q)
		display(data, 10, LTLM_A, 133);
		break;
	case 138: //10A134: LMP BUS VOLT (GC0302V)
		display(data, 10, LTLM_A, 134);
		break;
	case 139: //10A135: ASC 1 H2O TEMP
		display(data, 10, LTLM_A, 135);
		break;
	case 140: //10E13
		break;
	case 141: //10A137: W/B GLY IN TEMP
		display(data, 10, LTLM_A, 137);
		break;
	case 142: //10A138: RR ANT TEMP (GN7723T)
		display(data, 10, LTLM_A, 138);
		break;
	case 143: //10A139: YAW ERR CMD (GH1247V)
		display(data, 10, LTLM_A, 139);
		break;
	case 144: //10A140: RCS B REG PRESS (GR1202P)
		display(data, 10, LTLM_A, 140);
		break;
	case 145: //10A141: PRI H2O REG DP
		display(data, 10, LTLM_A, 141);
		break;
	case 146: //10A142: DES O2 PRESS 
		break;
	case 147: //10A143: LMP BUS VOLT (GC0302V)
		break;
	case 148: //10A144: APS OX TEMP (GP1218T)
		break;
	case 149: //10A145: RCS B HE PRESS (GR1102P)
		break;
	case 150: //10A146: RCS PROP B QTY (GR1095Q)
		display(data, 10, LTLM_A, 146);
		break;
	case 151: //10A147: SUIT PRESS
		break;
	case 152: //10E14
		break;
	case 153: //10E15
		break;
	case 154: //10E16
		break;
	case 155: //10E17
		break;
	case 156: //10A152: S-BND RCVR SIG (GT0994V)
		display(data, 10, LTLM_A, 152);
		break;
	case 157: //10A153: APS HE 1 PRESS (GP0001P)
		display(data, 10, LTLM_A, 153);
		break;
	case 158: //10A154: PRI W/B H2O TEMP
		display(data, 10, LTLM_A, 154);
		break;
	case 159: //10A155: PITCH ERR CMD (GH1248V)
		display(data, 10, LTLM_A, 155);
		break;
	case 160: //10E18
		break;
	case 161: //10E19
		break;
	case 162: //10E20
		break;
	case 163: //10E21
		break;
	case 164: //10A160: RCS A HE PRESS (GR1101P)
		break;
	case 165: //10A161: S-BND RCVR SIG (GT0994V)
		break;
	case 166: //10A162: RCS PROP A QTY (GR1085Q)
		display(data, 10, LTLM_A, 162);
		break;
	case 167: //10A163: PRI W/B H2O TEMP
		break;
	case 168: //10A164: LR ANT TEMP (GN7563T)
		display(data, 10, LTLM_A, 164);
		break;
	case 169: //10A165: DPS OX 1 QTY (GQ4103Q)
		display(data, 10, LTLM_A, 165);
		break;
	case 170: //10A166: PIPA TEMP
		break;
	case 171: //10A167: BAT 2 CUR (GC1202C)
		break;
	case 172: //10A168: PRI H2O REG DP
		break;
	case 173: //10A169: GLY TEMP
		break;
	case 174: //10A170: ASC 1 H2O TEMP
		break;
	case 175: //10A171: PCM OSC FAIL 2 (GL0422X)
		display(data, 10, LTLM_A, 171);
		break;
	case 176: //10A172: SUIT TEMP (GF1281T)
		display(data, 10, LTLM_A, 172);
		break;
	case 177: //10A173: APS TCP (GP2010P)
		display(data, 10, LTLM_A, 173);
		break;
	case 178: //10A174: AC BUS FREQ (GC0155)
		display(data, 10, LTLM_A, 174);
		break;
	case 179: //10A175: ROLL ERR CMD (GH1249V)
		display(data, 10, LTLM_A, 175);
		break;
	case 180: //10E22
		break;
	case 181: //10A177: SUIT TEMP (GF1281T)
		break;
	case 182: //10A173: APS TCP (GP2010P)
		break;
	case 183: //10A179: APS HE 1 PRESS (GP0001P)
		break;
	case 184: //10A180: RTG TEMP (GL8275T)
		display(data, 10, LTLM_A, 180);
		break;
	case 185: //10A181: IN SH
		break;
	case 186: //10A182: IN SH
		break;
	case 187: //10A183: F/H RLF PRESS
		display(data, 10, LTLM_A, 183);
		break;
	case 188: //10A184: OPEN
		break;
	case 189: //10A185: S-BND ST PH ERR (GT0992B)
		display(data, 10, LTLM_A, 185);
		break;
	case 190: //10A186: AUTO THRUST CMD (GH1331V)
		display(data, 10, LTLM_A, 186);
		break;
	case 191: //10A187
		break;
	case 192: //10E23
		display(data, 10, LTLM_E, 23);
		break;
	case 193: //10E24
		display(data, 10, LTLM_E, 24);
		break;
	case 194: //10E25
		break;
	case 195: //10E26
		break;
	case 196: //10A192
		break;
	case 197: //10A193: VAR INJ ACT POS (GQ6806H)
		display(data, 10, LTLM_A, 193);
		break;
	case 198: //10A194: U/H RLF PRESS
		display(data, 10, LTLM_A, 194);
		break;
	case 199: //10A195: S-BND XMTR PO (GT0993E)
		display(data, 10, LTLM_A, 195);
		break;
	default:
	{
		//LBROutput[bytect] = data;
	}
	break;
	}
}

void CLMTelemetryClient2Dlg::end_lbr()
{

}

void CLMTelemetryClient2Dlg::end_hbr()
{

}

void CLMTelemetryClient2Dlg::parse_hbr(unsigned char data, int bytect)
{
	switch (bytect) {
	case 0: // SYNC 1
		if (data != 0375) {
			end_hbr();
			lock_type = 0;

			sprintf_s(msg2, "SYNC 1 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;
	case 1: // SYNC 2
		if (data != 0312)
		{
			end_hbr();
			lock_type = 0;
			sprintf_s(msg2, "SYNC 2 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;

	case 2: // SYNC 3
		if (data != 0150)
		{
			end_hbr();
			lock_type = 0;
			sprintf_s(msg2, "SYNC 3 FAILED %o\n", data);
			msg = msg2;
			GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
		}
		break;
	case 3: // FRAME COUNT
		framect = data & 077; // 1-50 frame count
		// GENERATE 0-4 SUBFRAME #
		sprintf_s(msg2, "%03d", framect - 1);
		switch (msg2[2]) {
		case '0':
		case '5':
			framead = 0; break;
		case '1':
		case '6':
			framead = 1; break;
		case '2':
		case '7':
			framead = 2; break;
		case '3':
		case '8':
			framead = 3; break;
		case '4':
		case '9':
			framead = 4; break;
		}
		break;
	case 4: //Word 5
		switch (framect)
		{
		case 1: // FORMAT
			if (data != 033)
			{
				end_hbr();
				lock_type = 0;
				sprintf_s(msg2, "NOT HBR FORMAT %o\n", data);
				msg = msg2;
				GetDlgItem(IDC_EDIT2)->SetWindowText(msg);
			}
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			//10A4
			//10A8
			//10A12
			//10A16
			display(data, 10, LTLM_A, framect * 4 - 4);
			break;
		case 6: //10D3
			break;
		case 7:
		case 8:
		case 9:
		case 10:
			//10A23
			//10A27
			//10A31
			//10A35
			display(data, 10, LTLM_A, framect * 4 - 5);
			break;
		case 11: //10D5
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			//10A42
			//10A46
			//10A50
			//10A54
			display(data, 10, LTLM_A, framect * 4 - 6);
			break;
		case 16: //10D7
			break;
		case 17:
		case 18:
		case 19:
		case 20:
			//10A61
			//10A65
			//10A69
			//10A73
			display(data, 10, LTLM_A, framect * 4 - 7);
			break;
		case 21: //10D9
			break;
		default: //Frames 22-50
			//10A80
			//...
			//10A192
			display(data, 10, LTLM_A, framect * 4 - 8);
			break;
		}
		break;
	case 5: //RCS THT 1
	case 37:
	case 69:
	case 101:
		display(data, 22, LTLM_E, 0x01A);
		break;
	case 6: //RCS THT 2
	case 38:
	case 70:
	case 102:
		display(data, 22, LTLM_E, 0x01B);
		break;
	case 7: //JET DRV 1
	case 71:
		display(data, 12, LTLM_E, 1);
		break;
	case 8: //22A1: GQ3611P
	case 40:
	case 72:
	case 104:
		display(data, 22, LTLM_A, 1);
		break;
	case 9: //22A2: GQ4111
	case 41:
	case 73:
	case 105:
		display(data, 22, LTLM_A, 2);
		break;
	case 10: //22A3: IN-SH
	case 42:
	case 74:
	case 106:
		display(data, 22, LTLM_A, 3);
		break;
	case 11://22A4: GQ3611P
	case 43:
	case 75:
	case 107:
		display(data, 22, LTLM_A, 4);
		break;
	case 12://22A5: GQ4111
	case 44:
	case 76:
	case 108:
		display(data, 22, LTLM_A, 5);
		break;
	case 13: //22A6: GQ6510
	case 45:
	case 77:
	case 109:
		display(data, 22, LTLM_A, 6);
		break;
	case 14: //22A7: GP2010
	case 46:
	case 78:
	case 110:
		display(data, 22, LTLM_A, 7);
		break;
	case 15: //JET DRV 1
	case 79:
		display(data, 12, LTLM_E, 2);
		break;
	case 16: //12A1: GG2107
	case 25: //12A9: GG2107
	case 80:
	case 89:
		display(data, 12, LTLM_A, 1);
		break;
	case 17: //12A2: Open
	case 81:
		display(data, 12, LTLM_A, 2);
		break;
	case 18: //12A3: GG2137
	case 82:
		display(data, 12, LTLM_A, 3);
		break;
	case 19: //12A4: IN-SH
	case 83:
		display(data, 12, LTLM_A, 4);
		break;
	case 20: //12A5: IN-SH
	case 84:
		display(data, 12, LTLM_A, 5);
		break;
	case 21: //12A6: Open
	case 85:
		display(data, 12, LTLM_A, 6);
		break;
	case 22: //12A7: GQ4104
	case 86:
		display(data, 12, LTLM_A, 7);
		break;
	case 23: //51E1: BL747
	case 31: //51E2: BL747
		display(data, 51, LTLM_E, 1);
		break;
	case 24: //12A8: GQ3603
	case 88:
		display(data, 12, LTLM_A, 8);
		break;
	case 26: //12A10: IN-SH
	case 90:
		display(data, 12, LTLM_A, 10);
		break;
	case 27: //12A11: GQ4103
	case 91:
		display(data, 12, LTLM_A, 11);
		break;
	case 28: //12A12: IN-SH
	case 92:
		display(data, 12, LTLM_A, 12);
		break;
	case 29: //12A13: GG2167
	case 93:
		display(data, 12, LTLM_A, 13);
		break;
	case 30: //12A14: IN-SH
	case 94:
		break;
	case 32:
		switch (framead)
		{
		case 0: //11D1a: GL0501
			display(data, 11, LTLM_D, 0x01A);
			break;
		case 1: //11A8: GH1241
			display(data, 11, LTLM_A, 8);
			break;
		case 2: //11A18: GH1242
			display(data, 11, LTLM_A, 18);
			break;
		case 3: //11A28: GG2173
			display(data, 11, LTLM_A, 28);
			break;
		case 4: //11A37: GH1457
			display(data, 11, LTLM_A, 37);
			break;
		}
		break;
	case 33:
		switch (framead)
		{
		case 0: //11D1b: GL0501
			display(data, 11, LTLM_D, 0x01B);
			break;
		case 1: //11A9: GG2142
			display(data, 11, LTLM_A, 9);
			break;
		case 2: //11A19: GH1461
			display(data, 11, LTLM_A, 19);
			break;
		case 3: //11A29: GH1462
			display(data, 11, LTLM_A, 29);
			break;
		case 4: //11A38: GH1463
			display(data, 11, LTLM_A, 38);
			break;
		}
		break;
	case 34:
		switch (framead)
		{
		case 0: //11D1c: GL0501
			display(data, 11, LTLM_D, 0x01C);
			break;
		case 1: //11A10: GG3305
			display(data, 11, LTLM_A, 10);
			break;
		case 2: //11A20: GG3325
			display(data, 11, LTLM_A, 20);
			break;
		case 3: //11A30: GH1313
			display(data, 11, LTLM_A, 30);
			break;
		case 4: //11A39: GH1455
			display(data, 11, LTLM_A, 39);
			break;
		}
		break;
	case 35:
		switch (framead)
		{
		case 0: //11D1d: GL0501
			display(data, 11, LTLM_D, 0x01D);
			break;
		case 1: //11A11: GG3324
			display(data, 11, LTLM_A, 11);
			break;
		case 2: //11A21: GH1331
			display(data, 11, LTLM_A, 21);
			break;
		case 3: //11A31: GH1314
			display(data, 11, LTLM_A, 31);
			break;
		case 4: //11A40: GG2142
			display(data, 11, LTLM_A, 40);
			break;
		}
		break;
	case 36: //Word 37
		switch (framect)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			display(data, 10, LTLM_A, framect * 4 - 3);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			display(data, 10, LTLM_A, framect * 4 - 4);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			display(data, 10, LTLM_A, framect * 4 - 5);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
			display(data, 10, LTLM_A, framect * 4 - 6);
			break;
		default:
			display(data, 10, LTLM_A, framect * 4 - 7);
			break;
		}
		break;
	case 39: //12E3: BL753
	case 103:
		display(data, 12, LTLM_E, 3);
		break;
	case 47: //12E4: JET DRV 2
	case 111:
		display(data, 12, LTLM_E, 4);
		break;
	case 48: //12A15: IN-SH
	case 112:
		display(data, 12, LTLM_A, 15);
		break;
	case 49: //12A16: GG2137
	case 113:
		display(data, 12, LTLM_A, 3);
		break;
	case 50: //12A17: IN-SH
	case 114:
		display(data, 12, LTLM_A, 17);
		break;
	case 51: //12A18: IN-SH
	case 115:
		display(data, 12, LTLM_A, 18);
		break;
	case 52: //12A19: GG2167
	case 116:
		display(data, 12, LTLM_A, 13);
		break;
	case 53: //12A20: Open
	case 117:
		display(data, 12, LTLM_A, 20);
		break;
	case 54: //12A21: GQ3604
	case 118:
		display(data, 12, LTLM_A, 21);
		break;
	case 55: //12A22: IN-SH
	case 119:
		display(data, 12, LTLM_A, 22);
		break;
	case 56: //51A1: GG2021
		display(data, 51, LTLM_A, 1);
		break;
	case 57: //51A2: GG2001
	case 60: //51A5: GG2001
		display(data, 51, LTLM_A, 2);
		break;
	case 58: //51A3: GG2041
	case 61: //51A6: GG2041
		display(data, 51, LTLM_A, 3);
		break;
	case 59: //51A4: GQ6806
	case 63: //51A8: GQ6806
		display(data, 51, LTLM_A, 4);
		break;
	case 62: //51A7: IN-SH
		display(data, 51, LTLM_A, 7);
		break;
	case 64:
		switch (framead)
		{
		case 0: //11A1: GH1240
			display(data, 11, LTLM_A, 1);
			break;
		case 1: //11A12: GG2143
			display(data, 11, LTLM_A, 12);
			break;
		case 2: //11A22: GP0042
			display(data, 11, LTLM_A, 22);
			break;
		case 3: //11A32: GG3304
			display(data, 11, LTLM_A, 32);
			break;
		case 4: //11A41: GL0401
			display(data, 11, LTLM_A, 41);
			break;
		}
		break;
	case 65:
		switch (framead)
		{
		case 0: //11A2: GT0992
			display(data, 11, LTLM_A, 2);
			break;
		case 1: //11A13: GH1457
			display(data, 11, LTLM_A, 13);
			break;
		case 2: //11A23: GG2279
			display(data, 11, LTLM_A, 23);
			break;
		case 3: //11A33: GH1248
			display(data, 11, LTLM_A, 33);
			break;
		case 4: //11A42: GH1456
			display(data, 11, LTLM_A, 42);
			break;
		}
		break;
	case 66:
		switch (framead)
		{
		case 0: //11A3: Open
			display(data, 11, LTLM_A, 3);
			break;
		case 1: //11A14: GH2113
			display(data, 11, LTLM_A, 14);
			break;
		case 2: //11A24: GG2172
			display(data, 11, LTLM_A, 24);
			break;
		case 3: //11A34: GH1463
			display(data, 11, LTLM_A, 34);
			break;
		case 4: //11A43: GH1461
			display(data, 11, LTLM_A, 43);
			break;
		}
		break;
	case 67:
		switch (framead)
		{
		case 0: //11A4: GP0041
			display(data, 11, LTLM_A, 4);
			break;
		case 1: //11A15: GH1455
			display(data, 11, LTLM_A, 15);
			break;
		case 2: //11A25: GH1247
			display(data, 11, LTLM_A, 25);
			break;
		case 3: //11A35: GG2219
			display(data, 11, LTLM_A, 35);
			break;
		case 4: //11A44: IN-SH
			display(data, 11, LTLM_A, 44);
			break;
		}
		break;
	case 68: //Word 69
		switch (framect)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			display(data, 10, LTLM_A, framect * 4 - 2);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			display(data, 10, LTLM_A, framect * 4 - 3);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			display(data, 10, LTLM_A, framect * 4 - 4);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
			display(data, 10, LTLM_A, framect * 4 - 5);
			break;
		default:
			display(data, 10, LTLM_A, framect * 4 - 6);
			break;
		}
		break;
	case 87: //51E3
		display(data, 51, LTLM_E, 3);
		break;
	case 95: //51E4
		display(data, 51, LTLM_E, 4);
		break;
	case 96: //51D2: GT0441
		display(data, 51, LTLM_D, 2);
		break;
	case 97: //Word 98
		switch (framect)
		{
		case 1:
		case 6:
		case 11:
		case 16:
		case 21:
		case 26:
		case 31:
		case 36:
		case 41:
		case 46:
			display(data, 11, LTLM_A, 5);
			break;
		case 2:
		case 3:
		case 4:
		case 5:
			display(data, 10, LTLM_E, framect - 1);
			break;
		case 7:
		case 8:
		case 9:
		case 10:
			display(data, 10, LTLM_E, framect - 2);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
			display(data, 10, LTLM_E, framect - 3);
			break;
		case 17:
		case 18:
		case 19:
		case 20:
			display(data, 10, LTLM_E, framect - 4);
			break;
		case 22:
		case 23:
		case 24:
		case 25:
		case 30:
		case 35:
		case 40:
		case 45:
		case 50:
			display(data, 10, LTLM_E, framect - 5);
			break;
		case 27:
		case 28:
		case 29:
		case 32:
		case 33:
		case 34:
		case 37:
		case 38:
		case 39:
		case 42:
		case 43:
		case 44:
		case 47:
		case 48:
		case 49:
			display(data, 10, LTLM_E, framect - 6);
			break;
		}
		break;
	case 98:
		switch (framead)
		{
		case 0: //11A6: IN-SH
			display(data, 11, LTLM_A, 6);
			break;
		case 1: //11A16: GG2112
			display(data, 11, LTLM_A, 16);
			break;
		case 2: //11A26: GL0401
			display(data, 11, LTLM_A, 26);
			break;
		case 3: //11A36: GL0402
			display(data, 11, LTLM_A, 36);
			break;
		case 4: //11A45: GH1462
			display(data, 11, LTLM_A, 45);
			break;
		}
		break;
	case 99: //Word 100
		switch (framect)
		{
		case 1:
		case 6:
		case 11:
		case 16:
		case 21:
		case 26:
		case 31:
		case 36:
		case 41:
		case 46:
			display(data, 11, LTLM_A, 7);
			break;
		case 2:
		case 7:
		case 12:
		case 17:
		case 22:
		case 27:
		case 32:
		case 37:
		case 42:
		case 47:
			display(data, 11, LTLM_A, 17);
			break;
		case 3:
		case 8:
		case 13:
		case 18:
		case 23:
		case 28:
		case 33:
		case 38:
		case 43:
		case 48:
			display(data, 11, LTLM_A, 27);
			break;
		case 4:
			display(data, 11, LTLM_D, 2);
			break;
		case 5:
		case 10:
		case 15:
		case 20:
		case 25:
		case 30:
		case 35:
		case 40:
		case 45:
		case 50:
			display(data, 11, LTLM_E, 1);
			break;
		case 9:
			display(data, 11, LTLM_D, 4);
			break;
		case 14:
			display(data, 11, LTLM_D, 6);
			break;
		case 19:
			display(data, 11, LTLM_D, 8);
			break;
		case 24:
			display(data, 11, LTLM_D, 10);
			break;
		case 29:
			display(data, 10, LTLM_E, 24);
			break;
		case 34:
			display(data, 10, LTLM_E, 29);
			break;
		case 39:
			display(data, 10, LTLM_E, 34);
			break;
		case 44:
			display(data, 10, LTLM_E, 39);
			break;
		case 49:
			display(data, 10, LTLM_E, 44);
			break;
		}
		break;
	case 100: //Word 101
		switch (framect)
		{
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			display(data, 10, LTLM_A, framect * 4 - 1);
			break;
		case 6:
		case 7:
		case 8:
		case 9:
		case 10:
			display(data, 10, LTLM_A, framect * 4 - 2);
			break;
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
			display(data, 10, LTLM_A, framect * 4 - 3);
			break;
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
			display(data, 10, LTLM_A, framect * 4 - 4);
			break;
		default:
			display(data, 10, LTLM_A, framect * 4 - 5);
			break;
		}
		break;
	case 120: //51DS1a: GG0001
		lgc_word[0] = data & 0177;
		lgc_word[0] <<= 8;
		break;
	case 121: //51DS1b: GG0001
		lgc_word[0] |= data & 0377;
		break;
	case 122: //51DS1c: GG0001
		lgc_word[1] = data & 0177;
		lgc_word[1] <<= 8;
		break;
	case 123: //51DS1d: GG0001
		lgc_word[1] |= data & 0377;
		break;
	case 124: //51DS1e: GG0001
		parse_lgc();
		break;
	case 125: //51DS2a: GG0001
		//TBD: AGS
		break;
	case 126: //51DS2b: GG0001
		//TBD: AGS
		break;
	case 127: //51DS2c: GG0001
		//TBD: AGS
		break;
	}
}

void CLMTelemetryClient2Dlg::parse_lgc()
{
	if (lgc_form == NULL) return;

	if (lgc_lock_type == 0) {
		lgc_frame_addr = 1;   // Hold at one
		DoLGCLock();
		return;
	}
	else {
		lgc_frame_addr++;
		if (lgc_frame_addr > 100) {
			lgc_frame_addr = 1; // LOOP
		}
	}

	// ACTUAL DATA PARSING HERE
	if (lgc_frame_addr == 1)
	{
		DoLGCLock();
	}
	if (lgc_lock_type == 0) return;
	//Store raw data
	lgc_raw_data[lgc_frame_addr - 1][0] = lgc_word[0];
	lgc_raw_data[lgc_frame_addr - 1][1] = lgc_word[1];

	ProcessLGC();
}

void CLMTelemetryClient2Dlg::ProcessLGC()
{
	LGCDownlinkFormatEntry format = LGCDownlinkFormat[lgc_lock_type - 1][lgc_frame_addr - 1];
	for (int i = 0;i < 2;i++)
	{
		switch (format.type[i])
		{
		case 1: //Double precision
			sprintf_s(msg2, "%g", ScaleAGCDouble(lgc_word[0], lgc_word[1], format.CF[0]*pow(2, format.Scale[0])));
			LGCWriteToForm(format.disp[0]);
			return;
		case 2: //Single precision raw octal
			sprintf_s(msg2, "%05o", lgc_word[i]);
			LGCWriteToForm(format.disp[i]);
			break;
		case 3: //Single precision signed
			sprintf_s(msg2, "%.5lf", ScaleAGCSingle(lgc_word[i], format.CF[i] * pow(2, format.Scale[i])));
			LGCWriteToForm(format.disp[i]);
			break;
		case 4: //Single precision unsigned
			sprintf_s(msg2, "%.5lf", ScaleAGCSingle(lgc_word[i], format.CF[i] * pow(2, format.Scale[i]), false));
			LGCWriteToForm(format.disp[i]);
			break;
		case 5: //Double precision raw octal
			sprintf_s(msg2, "%05o-%05o", lgc_word[0], lgc_word[1]);
			LGCWriteToForm(format.disp[0]);
			return;
		case 6: //DSKY
			dsptab[format.disp[i]] = lgc_word[i];
			if (format.disp[i] == 11)
			{
				ProcessDSKY();
			}
			break;
		}
	}
}

void CLMTelemetryClient2Dlg::ProcessDSKY()
{
	// PARSE DSPTAB AND CREATE DSKY DISPLAY
	char tmp[12];      // Temporary
	unsigned int bits; // Temporary
	// PROG
	bits = ((dsptab[10] & 01740) >> 5);
	tmp[0] = get_dsky_char(bits);
	bits = (dsptab[10] & 037);
	tmp[1] = get_dsky_char(bits);
	tmp[2] = 0;
	sprintf_s(msg2, tmp);
	showValue(&lgc_form->DSKY_Prog);
	//if (upl_form != NULL) { upl_form->textBox129->Text = tmp; upl_form->textBox129->Enabled = true; }
	// VERB
	bits = ((dsptab[9] & 01740) >> 5);
	tmp[0] = get_dsky_char(bits);
	bits = (dsptab[9] & 037);
	tmp[1] = get_dsky_char(bits);
	tmp[2] = 0;
	sprintf_s(msg2, tmp);
	showValue(&lgc_form->DSKY_Verb);
	//if (upl_form != NULL) { upl_form->textBox133->Text = tmp; upl_form->textBox133->Enabled = true; }
	// NOUN
	bits = ((dsptab[8] & 01740) >> 5);
	tmp[0] = get_dsky_char(bits);
	bits = (dsptab[8] & 037);
	tmp[1] = get_dsky_char(bits);
	tmp[2] = 0;
	sprintf_s(msg2, tmp);
	showValue(&lgc_form->DSKY_Noun);
	//if (upl_form != NULL) { upl_form->textBox134->Text = tmp; upl_form->textBox134->Enabled = true; }
	// R1
	tmp[0] = '_';
	if (dsptab[5] & 02000) {
		tmp[0] = '-';
	}
	if (dsptab[6] & 02000) {
		tmp[0] = '+';
	}
	bits = (dsptab[7] & 037);
	tmp[1] = get_dsky_char(bits);
	bits = ((dsptab[6] & 01740) >> 5);
	tmp[2] = get_dsky_char(bits);
	bits = (dsptab[6] & 037);
	tmp[3] = get_dsky_char(bits);
	bits = ((dsptab[5] & 01740) >> 5);
	tmp[4] = get_dsky_char(bits);
	bits = (dsptab[5] & 037);
	tmp[5] = get_dsky_char(bits);
	tmp[6] = 0;
	sprintf_s(msg2, tmp);
	showValue(&lgc_form->DSKY_R1);
	//if (upl_form != NULL) { upl_form->textBox135->Text = tmp; upl_form->textBox135->Enabled = true; }
	// R2
	tmp[0] = '_';
	if (dsptab[3] & 02000) {
		tmp[0] = '-';
	}
	if (dsptab[4] & 02000) {
		tmp[0] = '+';
	}
	bits = ((dsptab[4] & 01740) >> 5);
	tmp[1] = get_dsky_char(bits);
	bits = (dsptab[4] & 037);
	tmp[2] = get_dsky_char(bits);
	bits = ((dsptab[3] & 01740) >> 5);
	tmp[3] = get_dsky_char(bits);
	bits = (dsptab[3] & 037);
	tmp[4] = get_dsky_char(bits);
	bits = ((dsptab[2] & 01740) >> 5);
	tmp[5] = get_dsky_char(bits);
	tmp[6] = 0;
	sprintf_s(msg2, tmp);
	showValue(&lgc_form->DSKY_R2);
	//if (upl_form != NULL) { upl_form->textBox136->Text = tmp; upl_form->textBox136->Enabled = true; }
	// R3
	tmp[0] = '_';
	if (dsptab[0] & 02000) {
		tmp[0] = '-';
	}
	if (dsptab[1] & 02000) {
		tmp[0] = '+';
	}
	bits = (dsptab[2] & 037);
	tmp[1] = get_dsky_char(bits);
	bits = ((dsptab[1] & 01740) >> 5);
	tmp[2] = get_dsky_char(bits);
	bits = (dsptab[1] & 037);
	tmp[3] = get_dsky_char(bits);
	bits = ((dsptab[0] & 01740) >> 5);
	tmp[4] = get_dsky_char(bits);
	bits = (dsptab[0] & 037);
	tmp[5] = get_dsky_char(bits);
	tmp[6] = 0;
	sprintf_s(msg2, tmp);
	showValue(&lgc_form->DSKY_R3);
	//if (upl_form != NULL) { upl_form->textBox137->Text = tmp; upl_form->textBox137->Enabled = true; }
	// WARNING LIGHTS
	if (dsptab[11] & 00400) { lgc_form->DSKY_ProgAlarm.EnableWindow(true); }
	else { lgc_form->DSKY_ProgAlarm.EnableWindow(false); }
	if (dsptab[11] & 00200) { lgc_form->DSKY_Tracker.EnableWindow(true); }
	else { lgc_form->DSKY_Tracker.EnableWindow(false); }
	if (dsptab[11] & 00040) { lgc_form->DSKY_GimbalLock.EnableWindow(true); }
	else { lgc_form->DSKY_GimbalLock.EnableWindow(false); }
	if (dsptab[11] & 00020) { lgc_form->DSKY_Alt.EnableWindow(true); }
	else { lgc_form->DSKY_Alt.EnableWindow(false); }
	if (dsptab[11] & 00010) { lgc_form->DSKY_NoAtt.EnableWindow(true); }
	else { lgc_form->DSKY_NoAtt.EnableWindow(false); }
	if (dsptab[11] & 00004) { lgc_form->DSKY_Vel.EnableWindow(true); }
	else { lgc_form->DSKY_Vel.EnableWindow(false); }
	/*if (upl_form != NULL) {
		if (dsptab[11] & 00400) { upl_form->label72->Enabled = TRUE; }
		else { upl_form->label72->Enabled = FALSE; }
		if (dsptab[11] & 00200) { upl_form->label75->Enabled = TRUE; }
		else { upl_form->label75->Enabled = FALSE; }
		if (dsptab[11] & 00040) { upl_form->label70->Enabled = TRUE; }
		else { upl_form->label70->Enabled = FALSE; }
		if (dsptab[11] & 00010) { upl_form->label69->Enabled = TRUE; }
		else { upl_form->label69->Enabled = FALSE; }
	}*/
}

// Translate bits into DSKY display character
char CLMTelemetryClient2Dlg::get_dsky_char(unsigned int bits)
{
	switch (bits) {
	case 025:
		return('0');
	case 003:
		return('1');
	case 031:
		return('2');
	case 033:
		return('3');
	case 017:
		return('4');
	case 036:
		return('5');
	case 034:
		return('6');
	case 023:
		return('7');
	case 035:
		return('8');
	case 037:
		return('9');
	case 000:
		return('_');
	default:
		return('X');
	}
}

void CLMTelemetryClient2Dlg::DoLGCLock()
{
	if (lgc_word[1] == 077340) { // Check for SYNC 1
		switch (lgc_word[0]) {   // Switch other halfword
		case 077777:  // COAST AND ALIGN 
			lgc_lock_type = LTLM_LGC_COAST_ALIGN;
			sprintf_s(msg2, "COAST/ALIGN");
			setup_lgc_list();
			break;
		case 077776:  // AGS INITIALIZATION/UPDATE
			lgc_lock_type = 2;
			sprintf_s(msg2, "AGS INIT/UPDATE");
			setup_lgc_list();
			break;
		case 077775:  // RDZ AND PRETHRUST
			lgc_lock_type = 3;
			sprintf_s(msg2, "RDZ/PRETHRUST");
			setup_lgc_list();
			break;
		case 077774:  // ORBITAL MANEUVERS LIST
			lgc_lock_type = 4;
			sprintf_s(msg2, "ORBITAL MANEUVERS");
			setup_lgc_list();
			break;
		case 077773:  // DESCENT/ASCENT
			lgc_lock_type = 5;
			sprintf_s(msg2, "DESCENT/ASCENT");
			setup_lgc_list();
			break;
		case 077772:  // SURFACE ALIGN
			lgc_lock_type = 6;
			sprintf_s(msg2, "SURFACE ALIGN");
			setup_lgc_list();
			break;
		default:
			lgc_lock_type = 0;
			sprintf_s(msg2, "NO SYNC");
			break;
		}
	}
	else {
		lgc_lock_type = 0;
		sprintf_s(msg2, "NO SYNC");
	}
	showValue(&lgc_form->lgcListID);
}

// Enable/disable stuff in CMCForm and setup for the given list
void CLMTelemetryClient2Dlg::setup_lgc_list()
{
	if (lgc_form == NULL) { return; } // Safeguard
	bool onoff;
	if (lgc_lock_type != 0) { onoff = TRUE; }
	else { onoff = FALSE; }
}

double CLMTelemetryClient2Dlg::ScaleAGCSingle(unsigned int word, double scale, bool issigned)
{
	int val;
	if (issigned && word > 037777)
	{
		val = -(int)(077777 - word);
	}
	else
	{
		val = word;
	}
	return scale *pow(2, -14)*val;
}

double CLMTelemetryClient2Dlg::ScaleAGCDouble(unsigned int w0, unsigned int w1, double scale)
{
	int val1, val2;
	if (w0 > 037777)
	{
		val1 = -(int)(077777 - w0);
	}
	else
	{
		val1 = w0;
	}
	if (w1 > 037777)
	{
		val2 = -(int)(077777 - w1);
	}
	else
	{
		val2 = w1;
	}
	return scale * (pow(2, -14)*val1 + pow(2, -28)*val2);
}

void CLMTelemetryClient2Dlg::LGCWriteToForm(int out)
{
	switch (out)
	{
	case 1:
		showValue(&lgc_form->CSMPosX);
		break;
	case 2:
		showValue(&lgc_form->CSMPosY);
		break;
	case 3:
		showValue(&lgc_form->CSMPosZ);
		break;
	case 4:
		showValue(&lgc_form->CSMVelX);
		break;
	case 5:
		showValue(&lgc_form->CSMVelY);
		break;
	case 6:
		showValue(&lgc_form->CSMVelZ);
		break;
	case 7:
		showValue(&lgc_form->CSMTsv);
		break;
	case 8:
		showValue(&lgc_form->DELLT4);
		break;
	case 9:
		showValue(&lgc_form->RTARGX);
		break;
	case 10:
		showValue(&lgc_form->RTARGY);
		break;
	case 11:
		showValue(&lgc_form->RTARGZ);
		break;
	case 12:
		showValue(&lgc_form->ELEV);
		break;
	case 13:
		showValue(&lgc_form->TEVENT);
		break;
	case 14:
		showValue(&lgc_form->REFS11);
		break;
	case 15:
		showValue(&lgc_form->REFS12);
		break;
	case 16:
		showValue(&lgc_form->REFS13);
		break;
	case 17:
		showValue(&lgc_form->REFS21);
		break;
	case 18:
		showValue(&lgc_form->REFS22);
		break;
	case 19:
		showValue(&lgc_form->REFS23);
		break;
	case 20:
		showValue(&lgc_form->CSITIG);
		break;
	case 21:
		showValue(&lgc_form->CSIDVX);
		break;
	case 22:
		showValue(&lgc_form->CSIDVY);
		break;
	case 23:
		showValue(&lgc_form->CSIDVZ);
		break;
	case 24:
		showValue(&lgc_form->VGTIGX);
		break;
	case 25:
		showValue(&lgc_form->VGTIGY);
		break;
	case 26:
		showValue(&lgc_form->VGTIGZ);
		break;
	case 27:
		showValue(&lgc_form->LRVelZ);
		break;
	case 28:
		showValue(&lgc_form->LRAlt);
		break;
	case 29:
		showValue(&lgc_form->TTPF);
		break;
	case 30:
		showValue(&lgc_form->RedoCounter);
		break;
	case 31:
		showValue(&lgc_form->THETADX);
		break;
	case 32:
		showValue(&lgc_form->THETADY);
		break;
	case 33:
		showValue(&lgc_form->THETADZ);
		break;
	case 34:
		showValue(&lgc_form->RSBBQ);
		break;
	case 35:
		showValue(&lgc_form->BodyRateX);
		break;
	case 36:
		showValue(&lgc_form->BodyRateY);
		break;
	case 37:
		showValue(&lgc_form->BodyRateZ);
		break;
	case 38:
		showValue(&lgc_form->CDUXD);
		break;
	case 39:
		showValue(&lgc_form->CDUYD);
		break;
	case 40:
		showValue(&lgc_form->CDUZD);
		break;
	case 41:
		showValue(&lgc_form->ActualCDUX);
		break;
	case 42:
		showValue(&lgc_form->ActualCDUY);
		break;
	case 43:
		showValue(&lgc_form->ActualCDUZ);
		break;
	case 44:
		showValue(&lgc_form->RRTrunnionCDU);
		break;
	case 45:
		showValue(&lgc_form->Flagword01);
		break;
	case 46:
		showValue(&lgc_form->Flagword23);
		break;
	case 47:
		showValue(&lgc_form->Flagword45);
		break;
	case 48:
		showValue(&lgc_form->Flagword67);
		break;
	case 49:
		showValue(&lgc_form->Flagword89);
		break;
	case 50:
		showValue(&lgc_form->Flagword1011);
		break;
	case 51:
		showValue(&lgc_form->Time1Time2);
		break;
	case 52:
		showValue(&lgc_form->LMPosX);
		break;
	case 53:
		showValue(&lgc_form->LMPosY);
		break;
	case 54:
		showValue(&lgc_form->LMPosZ);
		break;
	case 55:
		showValue(&lgc_form->LMVelX);
		break;
	case 56:
		showValue(&lgc_form->LMVelY);
		break;
	case 57:
		showValue(&lgc_form->LMVelZ);
		break;
	case 58:
		showValue(&lgc_form->LMTsv);
		break;
	case 59:
		showValue(&lgc_form->DesiredBodyRateX);
		break;
	case 60:
		showValue(&lgc_form->DesiredBodyRateY);
		break;
	case 61:
		showValue(&lgc_form->DesiredBodyRateZ);
		break;
	case 62:
		showValue(&lgc_form->CADRFLSH1);
		break;
	case 63:
		showValue(&lgc_form->CADRFLSH2);
		break;
	case 64:
		showValue(&lgc_form->CADRFLSH3);
		break;
	case 65:
		showValue(&lgc_form->FAILREG1);
		break;
	case 66:
		showValue(&lgc_form->FAILREG2);
		break;
	case 67:
		showValue(&lgc_form->FAILREG3);
		break;
	case 68:
		showValue(&lgc_form->RADMODES);
		break;
	case 69:
		showValue(&lgc_form->DAPBOOLS);
		break;
	case 70:
		showValue(&lgc_form->POSTORKU);
		break;
	case 71:
		showValue(&lgc_form->NEGTORKU);
		break;
	case 72:
		showValue(&lgc_form->POSTORKV);
		break;
	case 73:
		showValue(&lgc_form->NEGTORKV);
		break;
	case 74:
		showValue(&lgc_form->CDHTIG);
		break;
	case 75:
		showValue(&lgc_form->CDHDVX);
		break;
	case 76:
		showValue(&lgc_form->CDHDVY);
		break;
	case 77:
		showValue(&lgc_form->CDHDVZ);
		break;
	case 78:
		showValue(&lgc_form->TPITIG);
		break;
	case 79:
		showValue(&lgc_form->TPIDVX);
		break;
	case 80:
		showValue(&lgc_form->TPIDVY);
		break;
	case 81:
		showValue(&lgc_form->TPIDVZ);
		break;
	case 82:
		showValue(&lgc_form->RRRange);
		break;
	case 83:
		showValue(&lgc_form->RRRangeRate);
		break;
	case 84:
		showValue(&lgc_form->LRVelX);
		break;
	case 85:
		showValue(&lgc_form->LRVelY);
		break;
	case 86:
		showValue(&lgc_form->CDHDH);
		break;
	case 87:
		showValue(&lgc_form->LMMass);
		break;
	case 88:
		showValue(&lgc_form->CSMMass);
		break;
	case 89:
		showValue(&lgc_form->IMODES30);
		break;
	case 90:
		showValue(&lgc_form->IMODES33);
		break;
	case 91:
		showValue(&lgc_form->TIG);
		break;
	case 92:
		showValue(&lgc_form->MomentOffsetQ);
		break;
	case 93:
		showValue(&lgc_form->MomentOffsetR);
		break;
	case 94:
		showValue(&lgc_form->POSTORKP);
		break;
	case 95:
		showValue(&lgc_form->NEGTORKP);
		break;
	case 96:
		showValue(&lgc_form->Channel11_12);
		break;
	case 97:
		showValue(&lgc_form->Channel13_14);
		break;
	case 98:
		showValue(&lgc_form->Channel30_31);
		break;
	case 99:
		showValue(&lgc_form->Channel32_33);
		break;
	case 100:
		showValue(&lgc_form->PIPTIME1);
		break;
	case 101:
		showValue(&lgc_form->DELV_SM_X);
		break;
	case 102:
		showValue(&lgc_form->DELV_SM_Y);
		break;
	case 103:
		showValue(&lgc_form->DELV_SM_Z);
		break;
	case 104:
		showValue(&lgc_form->TGO);
		break;
	/*case 105:
		showValue(&lgc_form->KFactor);
		break;
	case 106:
		showValue(&lgc_form->TAlign);
		break;
	case 107:
		showValue(&lgc_form->AOTCode);
		break;
	case 108:
		showValue(&lgc_form->RLS_X);
		break;
	case 109:
		showValue(&lgc_form->RLS_Y);
		break;
	case 110:
		showValue(&lgc_form->RLS_Z);
		break;
	case 111:
		showValue(&lgc_form->OGC);
		break;
	case 112:
		showValue(&lgc_form->IGC);
		break;
	case 113:
		showValue(&lgc_form->MGC);
		break;
	case 114:
		showValue(&lgc_form->StarIDs);
		break;
	case 115:
		showValue(&lgc_form->StarVector1_X);
		break;
	case 116:
		showValue(&lgc_form->StarVector1_Y);
		break;
	case 117:
		showValue(&lgc_form->StarVector1_Z);
		break;
	case 118:
		showValue(&lgc_form->StarVector2_X);
		break;
	case 119:
		showValue(&lgc_form->StarVector2_Y);
		break;
	case 120:
		showValue(&lgc_form->StarVector2_Z);
		break;
	case 121:
		showValue(&lgc_form->RRShaftCDU);
		break;
	case 122:
		showValue(&lgc_form->PIPAX);
		break;
	case 123:
		showValue(&lgc_form->PIPAY);
		break;
	case 124:
		showValue(&lgc_form->PIPAZ);
		break;
	case 125:
		showValue(&lgc_form->RRTrunError);
		break;
	case 126:
		showValue(&lgc_form->RRShaftError);
		break;*/
	}
}

void CLMTelemetryClient2Dlg::ReadLGCDownlinkFormatFromFile()
{
	std::string line;
	std::ifstream myfile;
	char listname[128];
	int type1, type2, scal1, disp1, scal2, disp2, counter;
	double cf1, cf2;

	for (int list = 0;list < 6;list++)
	{
		counter = 0;
		sprintf_s(listname, "LGCDownlinkFormat%d.txt", list + 1);
		myfile.open(listname);
		if (!myfile.is_open()) continue;
		while (getline(myfile, line))
		{
			//Format is: Name Type CF1 Scale1(2^X) Display1 CF2 Scale2(2^X) Display2
			if (sscanf_s(line.c_str(), "%d %lf %d %d %d %lf %d %d", &type1, &cf1, &scal1, &disp1, &type2, &cf2, &scal2, &disp2) == 8)
			{
				LGCDownlinkFormat[list][counter].type[0] = type1;
				LGCDownlinkFormat[list][counter].CF[0] = cf1;
				LGCDownlinkFormat[list][counter].Scale[0] = scal1;
				LGCDownlinkFormat[list][counter].disp[0] = disp1;
				LGCDownlinkFormat[list][counter].type[1] = type2;
				LGCDownlinkFormat[list][counter].CF[1] = cf2;
				LGCDownlinkFormat[list][counter].Scale[1] = scal2;
				LGCDownlinkFormat[list][counter].disp[1] = disp2;
			}
			counter++;
		}
		myfile.close();
	}
}

void CLMTelemetryClient2Dlg::display(unsigned char data, int channel, int type, int ccode)
{
	switch (type)
	{
	case LTLM_A:  // ANALOG
		switch (channel)
		{
		case 10: // S10A
			switch (ccode)
			{
			case 1: //Open
				break;
			case 2: //10A2: PLS TORQ REF (GG1040V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s10A2, data, 85.0, 135.0);
				}
				break;
			case 3: //10A3: DPS OX 1 TEMP (GQ4218T)
				if (dps_form)
				{
					showTempF(&dps_form->s10A3, data, 20.0, 120.0);
				}
				break;
			case 4: //10A4: DPS FUEL 1 TEMP (GQ3718T)
				if (dps_form)
				{
					showTempF(&dps_form->s10A4, data, 20.0, 120.0);
				}
				break;
			case 5: //10A5: IRIG SUSP 3.2 KC (GG1331V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s10A5, data, 0.0, 31.1);
				}
				break;
			case 6: //10A6: DPS HE PRESS (GQ3435P)
				if (dps_form)
				{
					showPSIA(&dps_form->s10A6, data, 0.0, 2000.0);
				}
				break;
			case 7: //10A7: MG RSVR OUT COS (GG2143V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s10A7, data, -20.25, 20.25);
				}
				break;
			case 8: //10A8: QUAD 4 TEMP
				if (rcs_form)
				{
					showTempF(&rcs_form->s10A8, data, 20.0, 200.0);
				}
				break;
			case 9: //10A9: BAT 5 VOLT
				if (eps_form)
				{
					showVolts(&eps_form->s10A9, data, 0.0, 40.0);
				}
				break;
			case 10: //10A10: DPS OX PRESS
				if (dps_form)
				{
					showPSIA(&dps_form->s10A10, data, 0.0, 300.0);
				}
				break;
			case 11: //10A11: ROLL GDA POS (GH1314V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A11, data, -15.0, 15.0);
				}
				break;
			case 12: //10A12: ASC 1 O2 PRESS 
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A12, data, 0.0, 1000.0);
				}
				break;
			case 13: //10A13: ASC 2 H2O TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A13, data, -200.0, 200.0);
				}
				break;
			case 14: //10A14: RCS A FUEL MFLD PRESS
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A14, data, 0.0, 350.0);
				}
				break;
			case 15: //10A15: RCS B FUEL MFLD PRESS
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A15, data, 0.0, 350.0);
				}
				break;
			case 16: //10A16: SEC GLY PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A16, data, 0.0, 60.0);
				}
				break;
			case 17: //10A17: CO2 PART PRESS
				if (ecs_form)
				{
					showMMHG(&ecs_form->s10A17, data, 0.0, 30.0);
				}
				break;
			case 18: //10A18: DPS FUEL PRESS
				if (dps_form)
				{
					showPSIA(&dps_form->s10A18, data, 0.0, 300.0);
				}
				break;
			case 19: //10A19: GLY PUMP PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A19, data, 0.0, 60.0);
				}
				break;
			case 20: //10A20: ASC 1 H2O QTY
				if (ecs_form)
				{
					showPercentage(&ecs_form->s10A20, data);
				}
				break;
			case 21: //10A21: RCS A OX MFLD PRESS
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A21, data, 0.0, 350.0);
				}
				break;
			case 22: //10A22: PITCH GDA POS (GH1313V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A22, data, -15.0, 15.0);
				}
				break;
			case 23: //10A23: 2.5 VDC TM BIAS (GG1110V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s10A23, data, 0.0, 5.0);
				}
				break;
			case 24: //10A24: ASC 2 H2O QTY
				if (ecs_form)
				{
					showPercentage(&ecs_form->s10A24, data);
				}
				break;
			case 25: //10A25: H2O SEP RATE
				if (ecs_form)
				{
					showRPM(&ecs_form->s10A25, data, 0.0, 3600.0);
				}
				break;
			case 26: //10A26: YAW ATT ERR (GH1455V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A26, data, -3.5, 3.5);
				}
				break;
			case 33: //10A33: DES H2O PRESS (GF4501)
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A33, data, 0.0, 60.0);
				}
				break;
			case 34: //10A34: DPS OX 2 TEMP (GQ4219T)
				if (dps_form)
				{
					showTempF(&dps_form->s10A34, data, 20.0, 120.0);
				}
				break;
			case 35: //10A35: QUAD 3 TEMP (GR6002T)
				if (rcs_form)
				{
					showTempF(&rcs_form->s10A35, data, 20.0, 200.0);
				}
				break;
			case 36: //10A36: BAT 6 VOLT (GC0206V)
				if (eps_form)
				{
					showVolts(&eps_form->s10A36, data, 0.0, 40.0);
				}
				break;
			case 37: //10A37: APS HE REG PRESS 1 (GP0018P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A37, data, 0.0, 300.0);
				}
				break;
			case 38: //10A38: RCS B OX MFLD PRESS
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A38, data, 0.0, 350.0);
				}
				break;
			case 40: //10A40: DPS START TANK P (GQ3015P)
				if (dps_form)
				{
					showPSIA(&dps_form->s10A40, data, 0.0, 1750.0);
				}
				break;
			case 41: //10A41: BAT 2 VOLT (GC0202V)
				if (eps_form)
				{
					showVolts(&eps_form->s10A41, data, 0.0, 40.0);
				}
				break;
			case 42: //10A42: DPS HE REG PRESS (GQ3018P)
				if (dps_form)
				{
					showPSIA(&dps_form->s10A42, data, 0.0, 300.0);
				}
				break;
			case 57: //10A57: BAT 4 VOLT (GC0204V)
				if (eps_form)
				{
					showVolts(&eps_form->s10A57, data, 0.0, 40.0);
				}
				break;
			case 58: //10A58: DES H2O QTY
				if (ecs_form)
				{
					showPercentage(&ecs_form->s10A58, data);
				}
				break;
			case 59: //10A59: PRI GLY PUMP DP (GF2021P)
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A59, data, 0.0, 50.0);
				}
				break;
			case 60: //10A60: PITCH ATT ERR (GH1456V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A60, data, -3.5, 3.5);
				}
				break;
			case 61: //10A61: APS OX PRESS (GP1503P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A61, data, 0.0, 250.0);
				}
				break;
			case 62: //10A62: APS FUEL PRESS (GP1501P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A62, data, 0.0, 250.0);
				}
				break;
			case 63: //10A63: BAT 3 CUR
				if (eps_form)
				{
					showAmps(&eps_form->s10A63, data, 0.0, 60.0);
				}
				break;
			case 64: //10A64: OG RSVR OUT COS (GG2173V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s10A64, data, -20.25, 20.25);
				}
				break;
			case 65: //10A65: ASA TEMP (GI3301T)
				if (ces_form)
				{
					showTempF(&ces_form->s10A65, data, 20.0, 200.0);
				}
				break;
			case 66: //10A66: RCS A FUEL TEMP (GR2121T)
				if (rcs_form)
				{
					showTempF(&rcs_form->s10A66, data, 20.0, 120.0);
				}
				break;
			case 67: //10A67: BAT 4 CUR (GC1204C)
				if (eps_form)
				{
					showAmps(&eps_form->s10A67, data, 0.0, 60.0);
				}
				break;
			case 68: //10A68: BAT 5 CUR (GC1205C)
				if (eps_form)
				{
					showAmps(&eps_form->s10A68, data, 0.0, 120.0);
				}
				break;
			case 70: //10A70: APS HE REG PRESS 2 (GP0025P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A70, data, 0.0, 300.0);
				}
				break;
			case 72: //10A72: BAT 1 VOLT (GC0201V)
				if (eps_form)
				{
					showVolts(&eps_form->s10A72, data, 0.0, 40.0);
				}
				break;
			case 73: //10A73: ASC 2 O2 PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A73, data, 0.0, 1000.0);
				}
				break;
			case 74: //10A74: RCS B FUEL TEMP (GR2122T)
				if (rcs_form)
				{
					showTempF(&rcs_form->s10A74, data, 20.0, 120.0);
				}
				break;
			case 75: //10A75: BAT 6 CUR (GC1206C)
				if (eps_form)
				{
					showAmps(&eps_form->s10A75, data, 0.0, 120.0);
				}
				break;
			case 76: //10A76: DPS TCP (GQ6510P)
				if (dps_form)
				{
					showPSIA(&dps_form->s10A76, data, 0.0, 200.0);
				}
				break;
			case 79: //10A79: BAT 3 VOLT (GC0203V)
				if (eps_form)
				{
					showVolts(&eps_form->s10A79, data, 0.0, 40.0);
				}
				break;
			case 80: //10A80: QUAD 2 TEMP (GR6003T)
				if (rcs_form)
				{
					showTempF(&rcs_form->s10A80, data, 20.0, 200.0);
				}
				break;
			case 81: //10A81: VHF RCVR B AGC (GT0625)
				if (comm_ed_form)
				{
					showVolts(&comm_ed_form->s10A81, data, 0.176, 0.282);
				}
				break;
			case 82: //10A82: AC BUS VOLTS (GC0071)
				if (eps_form)
				{
					showVolts(&eps_form->s10A82, data, 0.0, 125.0);
				}
				break;
			case 83: //10A83: CABIN PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A83, data, 0.0, 10.0);
				}
				break;
			case 84: //10A84: QUAD 1 TEMP (GR6004T)
				if (rcs_form)
				{
					showTempF(&rcs_form->s10A84, data, 20.0, 200.0);
				}
				break;
			case 85: //10A85: PCM OSC FAIL 3 (GL0423X)
				if (sci_form)
				{
					showVolts(&sci_form->s10A85, data, 0.0, 5.0);
				}
				break;
			case 90: //10A90: O2 MANIFOLD PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A90, data, 0.0, 1400.0);
				}
				break;
			case 91: //10A91: BAT 1 CUR (GC1201C)
				if (eps_form)
				{
					showAmps(&eps_form->s10A91, data, 0.0, 60.0);
				}
				break;
			case 93: //10A93: APS HE 2 PRESS (GP0002P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A93, data, 0.0, 4000.0);
				}
				break;
			case 101: //10A101: DPS FUEL 2 QTY (GQ3604Q)
				if (dps_form)
				{
					showPercentage(&dps_form->s10A101, data, 95.0);
				}
				break;
			case 104: //10A104: DPS FUEL 1 QTY (GQ3603Q)
				if (dps_form)
				{
					showPercentage(&dps_form->s10A104, data, 95.0);
				}
				break;
			case 107: //10A107: S-BND ANT TEMP (GT0454T)
				if (comm_ed_form)
				{
					showTempF(&comm_ed_form->s10A107, data, -200.0, 200.0);
				}
				break;
			case 108: //10A108: DPS HE REG PRESS (GQ3025P)
				if (dps_form)
				{
					showPSIA(&dps_form->s10A108, data, 0.0, 300.0);
				}
				break;
			case 112: //10A112: RCS A REG PRESS (GR1201P)
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A112, data, 0.0, 350.0);
				}
				break;
			case 113: //10A113: DPS BALL VLV TEMP (GQ4220T)
				if (dps_form)
				{
					showTempF(&dps_form->s10A113, data, -200.0, 500.0);
				}
				break;
			case 114: //10A114: APS FUEL TEMP (GP0718T)
				if (aps_form)
				{
					showTempF(&aps_form->s10A114, data, 20.0, 120.0);
				}
				break;
			case 115: //10A115: ROLL ATT ERR (GH1457V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A115, data, -3.5, 3.5);
				}
				break;
			case 117: //10A117: DPS FUEL 2 TEMP (GQ3719T)
				if (dps_form)
				{
					showTempF(&dps_form->s10A117, data, 20.0, 120.0);
				}
				break;
			case 120: //10A120: GLY TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A120, data, 20.0, 120.0);
				}
				break;
			case 121: //10A121: IMU 28 VAC 800 (GG1201V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s10A121, data, 0.0, 31.1);
				}
				break;
			case 122: //10A122: BAT 2 CUR
				if (eps_form)
				{
					showAmps(&eps_form->s10A122, data, 0.0, 60.0);
				}
				break;
			case 123: //10A123: PIPA TEMP
				if (gnc_form)
				{
					showTempF(&gnc_form->s10A123, data, 120.0, 140.0);
				}
				break;
			case 124: //10A124: RCS B HE PRESS (GR1102P)
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A124, data, 0.0, 3500.0);
				}
				break;
			case 125: //10A125: RCS A HE PRESS (GR1101P)
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A125, data, 0.0, 3500.0);
				}
				break;
			case 126: //10A126: CDR BUS VOLT
				if (eps_form)
				{
					showVolts(&eps_form->s10A126, data, 0.0, 40.0);
				}
				break;
			case 127: //10A127: W/B GLY OUT TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A127, data, 20.0, 120.0);
				}
				break;
			case 128: //10A128: CABIN TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A128, data, 20.0, 120.0);
				}
				break;
			case 129: //10A129: APS OX TEMP (GP1218T)
				if (aps_form)
				{
					showTempF(&aps_form->s10A129, data, 20.0, 120.0);
				}
				break;
			case 130: //10A130: SUIT PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A130, data, 0.0, 10.0);
				}
				break;
			case 131: //10A131: DES O2 PRESS 
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A131, data, 0.0, 3000.0);
				}
				break;
			case 132: //10A132: MAN THRUST CMD (GH1311V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A132, data, 0.0, 14.6);
				}
				break;
			case 133: //10A133: DPS OX 2 QTY (GQ4104Q)
				if (dps_form)
				{
					showPercentage(&dps_form->s10A133, data, 95.0);
				}
				break;
			case 134: //10A134: LMP BUS VOLT (GC0302V)
				if (eps_form)
				{
					showVolts(&eps_form->s10A134, data, 0.0, 40.0);
				}
				break;
			case 135: //10A135: ASC 1 H2O TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A135, data, -200.0, 200.0);
				}
				break;
			case 137: //10A137: W/B GLY IN TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A137, data, 20.0, 120.0);
				}
				break;
			case 138: //10A138: RR ANT TEMP (GN7723T)
				if (radar_form)
				{
					showTempF(&radar_form->s10A138, data, -200.0, 200.0);
				}
				break;
			case 139: //10A139: YAW ERR CMD (GH1247V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A139, data, -13.0, 13.0);
				}
				break;
			case 140: //10A140: RCS B REG PRESS (GR1202P)
				if (rcs_form)
				{
					showPSIA(&rcs_form->s10A140, data, 0.0, 350.0);
				}
				break;
			case 141: //10A141: PRI H2O REG DP
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A141, data, 0.0, 2.0);
				}
				break;
			case 146: //10A146: RCS PROP B QTY (GR1095Q)
				if (rcs_form)
				{
					showPercentage(&rcs_form->s10A146, data, 108.0);
				}
				break;
			case 152: //10A152: S-BND RCVR SIG (GT0994V)
				if (comm_ed_form)
				{
					showVolts(&comm_ed_form->s10A152, data, 0.0, 5.0);
				}
				break;
			case 153: //10A153: APS HE 1 PRESS (GP0001P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A153, data, 0.0, 4000.0);
				}
				break;
			case 154: //10A154: PRI W/B H2O TEMP
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A154, data, 20.0, 160.0);
				}
				break;
			case 155: //10A155: PITCH ERR CMD (GH1248V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A155, data, -13.0, 13.0);
				}
				break;
			case 162: //10A162: RCS PROP A QTY (GR1085Q)
				if (rcs_form)
				{
					showPercentage(&rcs_form->s10A162, data, 108.0);
				}
				break;
			case 164: //10A164: LR ANT TEMP (GN7563T)
				if (radar_form)
				{
					showTempF(&radar_form->s10A164, data, -200.0, 200.0);
				}
				break;
			case 165: //10A165: DPS OX 1 QTY (GQ4103Q)
				if (dps_form)
				{
					showPercentage(&dps_form->s10A165, data, 95.0);
				}
				break;
			case 171: //10A171: PCM OSC FAIL 2 (GL0422X)
				if (sci_form)
				{
					showVolts(&sci_form->s10A171, data, 0.0, 5.0);
				}
				break;
			case 172: //10A172: SUIT TEMP (GF1281T)
				if (ecs_form)
				{
					showTempF(&ecs_form->s10A172, data, 20.0, 120.0);
				}
				break;
			case 173: //10A173: APS TCP (GP2010P)
				if (aps_form)
				{
					showPSIA(&aps_form->s10A173, data, 0.0, 150.0);
				}
				break;
			case 174: //10A174: AC BUS FREQ (GC0155)
				if (eps_form)
				{
					showCPS(&eps_form->s10A174, data, 380.0, 420.0);
				}
				break;
			case 175: //10A175: ROLL ERR CMD (GH1249V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A175, data, -13.0, 13.0);
				}
				break;
			case 180: //10A180: RTG TEMP (GL8275T)
				if (sci_form)
				{
					showTempF(&sci_form->s10A180, data, -200.0, 500.0);
				}
				break;
			case 183: //10A183: F/H RLF PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A183, data, 0.0, 25.0);
				}
				break;
			case 185: //10A185: S-BND ST PH ERR (GT0992B)
				if (comm_ed_form)
				{
					showCPS(&comm_ed_form->s10A185, data, -90.0, 90.0);
				}
				break;
			case 186: //10A186: AUTO THRUST CMD (GH1331V)
				if (ces_form)
				{
					showVolts(&ces_form->s10A186, data, 0.0, 12.0);
				}
				break;
			case 193: //10A193: VAR INJ ACT POS (GQ6806H)
				if (dps_form)
				{
					showPercentage(&dps_form->s10A193, data);
				}
				break;
			case 194: //10A194: U/H RLF PRESS
				if (ecs_form)
				{
					showPSIA(&ecs_form->s10A194, data, 0.0, 25.0);
				}
				break;
			case 195: //10A195: S-BND XMTR PO (GT0993E)
				if (comm_ed_form)
				{
					showWatts(&comm_ed_form->s10A195, data, 0.3, 1.75);
				}
				break;
			}
			break;
		case 11: //S11A
			switch (ccode)
			{
			case 1: //11A1: X TRANS CMD (1240V)
				if (ces_form)
				{
					showVolts(&ces_form->s11A1, data, -10.0, 10.0);
				}
				break;
			case 4: //11A4: APS HE 1R PRESS (GP0041P)
				if (aps_form)
				{
					showPSIA(&aps_form->s11A4, data, 0.0, 4000.0);
				}
				break;
			case 8: //11A8: Y TRANS CMD (1241V)
				if (ces_form)
				{
					showVolts(&ces_form->s11A8, data, -10.0, 10.0);
				}
				break;
			case 9: //11A9: MG RSVR OUT SIN (GG2142V)
			case 40:
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A9, data, -20.25, 20.25);
				}
				break;
			case 10: //11A10: RR SHFT COS (GG3305V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A10, data, -21.5, 21.5);
				}
				break;
			case 11: //11A11: RR TRUN SIN (GG3324V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A11, data, -21.5, 21.5);
				}
				break;
			case 14: //11A14: IG RSVR OUT COS (GG2113V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A14, data, -20.25, 20.25);
				}
				break;
			case 16: //11A16: IG RSVR OUT SIN (GG2112V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A16, data, -20.25, 20.25);
				}
				break;
			case 17: //11A17: YAW ATT ERR (GG2249V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A17, data, -5.0, 5.0);
				}
				break;
			case 18: //11A18: X TRANS CMD (1242V)
				if (ces_form)
				{
					showVolts(&ces_form->s11A18, data, -10.0, 10.0);
				}
				break;
			case 19: //11A19: RGA YAW RATE (GH1461V)
				if (ces_form)
				{
					showVolts(&ces_form->s11A19, data, -3.5, 3.5);
				}
				break;
			case 20: //11A20: RR TRUN COS (GG3325V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A20, data, -21.5, 21.5);
				}
				break;
			case 22: //11A22: APS HE 2R PRESS (GP0042P)
				if (aps_form)
				{
					showPSIA(&aps_form->s11A22, data, 0.0, 4000.0);
				}
				break;
			case 23: //11A23: ROLL ATT ERR (GG2279V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A23, data, -5.0, 5.0);
				}
				break;
			case 24: //11A24: OG RSVR OUT SIN (GG2172V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A24, data, -20.25, 20.25);
				}
				break;
			case 26: //11A26: CAL 85 PCT (GL0401V)
				if (sci_form)
				{
					showVolts(&sci_form->s11A26, data, 0.0, 5.0);
				}
				break;
			case 29: //11A29: RGA PITCH RATE (GH1462V)
				if (ces_form)
				{
					showVolts(&ces_form->s11A29, data, -3.5, 3.5);
				}
				break;
			case 32: //11A32: RR SHFT SIN (GG3304V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A32, data, -21.5, 21.5);
				}
				break;
			case 35: //11A35: PITCH ATT ERR (GG2219V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s11A35, data, -5.0, 5.0);
				}
				break;
			case 36: //11A36: CAL 15 PCT (GL0402V)
				if (sci_form)
				{
					showVolts(&sci_form->s11A36, data, 0.0, 5.0);
				}
				break;
			case 38: //11A38: RGA ROLL RATE (GH1463V)
				if (ces_form)
				{
					showVolts(&ces_form->s11A38, data, -3.5, 3.5);
				}
				break;
			}
			break;
		case 12: //S12A
			switch (ccode)
			{
			case 1: //12A1: IG SVO ERR IN (GG2107V)
			case 9:
				if (gnc_form)
				{
					showVolts(&gnc_form->s12A1, data, -3.0, 3.0);
				}
				break;
			case 3: //12A3: MG SVO ERR IN (GG2137V)
			case 16:
				if (gnc_form)
				{
					showVolts(&gnc_form->s12A3, data, -3.0, 3.0);
				}
				break;
			case 13: //12A13: OG SVO ERR IN (GG2167V)
			case 19:
				if (gnc_form)
				{
					showVolts(&gnc_form->s12A13, data, -3.0, 3.0);
				}
				break;
			}
			break;
		case 51: //S51A
			switch (ccode)
			{
			case 1: //51A1: Y PIPA OUT IN PHI (GG2021V)
				if (gnc_form)
				{
					showVolts(&gnc_form->s51A1, data, -2.5, 2.5);
				}
				break;
			case 2: //51A2: X PIPA OUT IN PHI (GG2001V)
			case 5:
				if (gnc_form)
				{
					showVolts(&gnc_form->s51A2, data, -2.5, 2.5);
				}
				break;
			case 3: //51A3: Z PIPA OUT IN PHI (GG2041V)
			case 6:
				if (gnc_form)
				{
					showVolts(&gnc_form->s51A3, data, -2.5, 2.5);
				}
				break;
			}
			break;
		}
		break;
	case LTLM_E:
		switch (channel)
		{
		case 10:
			switch (ccode)
			{
			case 1: //10E1
				if (radar_form)
				{
					showEvent(&radar_form->s10E11, data, 01); //LR RANGE BAD (GN7521X)
					showEvent(&radar_form->s10E12, data, 02); //LR VEL BAD (GN7557X)
					showEvent(&radar_form->s10E13, data, 04); //RR NO TRACK (GN7621X)
				}
				break;
			case 2:  //10E2
			case 13: //10E13
				if (gnc_form)
				{
					showEvent(&gnc_form->s10E21, data, 01); //LGC WARNING (GG9001X)
					showEvent(&gnc_form->s10E22, data, 02); //ISS WARNING (GG9002X)
				}
				break;
			case 3:  //10E3
			case 14: //10E14
				if (ecs_form)
				{
					showEvent(&ecs_form->s10E31, data, 01); //CDR SUIT DISC (GF1201X)
					showEvent(&ecs_form->s10E32, data, 02); //LMP SUIT DISC (GF1202X)
					showEvent(&ecs_form->s10E33, data, 04); //GLY ACCUM LL (GF9986)
					showEvent(&ecs_form->s10E34, data, 010);//REPR ELEC OPEN (GF3572X)
				}
				break;
			case 4:  //10E4
			case 15: //10E15
				if (ecs_form)
				{
					showEvent(&ecs_form->s10E41, data, 01);		//CABIN RET CLSD (GF1231)
					showEvent(&ecs_form->s10E42, data, 02);		//CABIN RET OPEN (GF1232)
					showEvent(&ecs_form->s10E43, data, 04);		//DEMAND REG A CLSD (GF3071)
					showEvent(&ecs_form->s10E45, data, 020);	//DEMAND REG B CLSD (GF3073)
					showEvent(&ecs_form->s10E47, data, 0100);	//SEL GLY PMP FAIL (GF2936)
				}
				break;
			case 5:  //10E5
			case 16: //10E16
				if (ecs_form)
				{
					showEvent(&ecs_form->s10E51, data, 01); //SUIT FAN 1 MAL (GF1083X)
					showEvent(&ecs_form->s10E52, data, 02); //SUIT FAN 2 MAL (GF1084X)
					showEvent(&ecs_form->s10E53, data, 04); //SUIT RLF CLSD (GF1211X)
					showEvent(&ecs_form->s10E54, data, 010);//SUIT RLF OPEN (GF1212X)
					showEvent(&ecs_form->s10E55, data, 020);//SUIT DIV EGRESS (GF1221X)
					showEvent(&ecs_form->s10E56, data, 040);//SEC CO2 SEL (GF1241X)
				}
				break;
			case 6: //10E6
			case 17: //10E17
				if (gnc_form)
				{
					showEvent(&gnc_form->s10E61, data, 01); //IMU STBY (GG1513)
					showEvent(&gnc_form->s10E62, data, 02); //LGC OPR (GG1523)
				}
				break;
			case 7: //10E7
			case 18://10E18
				if (sci_form)
				{
					showEvent(&sci_form->s10E71, data, 01);  //CES AC PWR FAIL (GL4026X)
					showEvent(&sci_form->s10E72, data, 02);  //CES DC PWR FAIL (GL4027X)
					showEvent(&sci_form->s10E73, data, 04);  //ASA PWR/AEA FAIL (GL3028X)
					showEvent(&sci_form->s10E74, data, 010); //C&W PWR FAIL (GL4069X)
					showEvent(&sci_form->s10E75, data, 020); //MASTER ALARM ON (GL4069X)
					showEvent(&sci_form->s10E76, data, 040); //BAT MAL (GL4047X)
					showEvent(&sci_form->s10E78, data, 0200); //PCM OSC FAIL 1 (GL0400X)
				}
				break;
			case 10: //10E10
			case 21: //10E21
				if (rcs_form)
				{
					showEvent(&rcs_form->s10E101, data, 01);	//ASC FEED A OX OPN (GR9641U)
					showEvent(&rcs_form->s10E102, data, 02);	//ASC FEED B OX OPN (GR9642U)
					showEvent(&rcs_form->s10E103, data, 04);	//RCS MAIN A CLSD (GR9609U)
					showEvent(&rcs_form->s10E104, data, 010);	//RCS MAIN B CLSD (GR9610U)
					showEvent(&rcs_form->s10E105, data, 020);	//ASC FEED A FU OPN (GR9631U)
					showEvent(&rcs_form->s10E106, data, 040);	//ASC FEED B FU OPN (GR9632U)
					showEvent(&rcs_form->s10E107, data, 0100);	//A/B XFEED OPEN (GR9613U)
				}
				break;
			case 11: //10E11
				if (comm_ed_form)
				{
					showEvent(&comm_ed_form->s10E111, data, 01);  //ABORT CMD (GY0050X)
					showEvent(&comm_ed_form->s10E114, data, 010); //ED RLY A K7-K15 (GY0231X)
					showEvent(&comm_ed_form->s10E115, data, 020); //ED RLY B K7-K15 (GY0232X)
					showEvent(&comm_ed_form->s10E116, data, 040); //ED RLY A K1-K6 (GY0201X)
					showEvent(&comm_ed_form->s10E117, data, 0100);//ED RLY B K1-K6 (GY0202X)
				}
				break;
			case 23: //10E23
				if (ces_form)
				{
					showEvent(&ces_form->s10E231, data, 01); //AUTO ON (GH1214X)
					showEvent(&ces_form->s10E232, data, 02); //DPS ON (GH1301X)
					showEvent(&ces_form->s10E233, data, 04); //P TRM FAIL (GH1323X)
					showEvent(&ces_form->s10E234, data, 010);//R TRM FAIL (GH1330X)
					showEvent(&ces_form->s10E235, data, 020);//AGS SEL (GH1621X)
				}
				break;
			case 24: //10E24
				if (aps_form)
				{
					showEvent(&aps_form->s10E241, data, 01); //APS FUEL LO (GP0908X)
					showEvent(&aps_form->s10E242, data, 02); //APS OX LO (GP1408X)
				}
				break;
			case 27: //10E27
				if (ces_form)
				{
					showEvent(&ces_form->s10E271, data, 01); //ROLL PLSD/DIR (GH1628X)
					showEvent(&ces_form->s10E272, data, 02); //PITCH PLSD/DIR (GH1629X)
					showEvent(&ces_form->s10E273, data, 04); //YAW PLSD/DIR (GH1630X)
					showEvent(&ces_form->s10E274, data, 010); //AGS WARMUP (GI3305X)
					showEvent(&ces_form->s10E275, data, 020); //AGS STBY (GI3306X)
				}
				break;
			case 29:
				if (eps_form)
				{
					showEvent(&eps_form->s10E291, data, 01); //BAT 1 MAL (GC9961U)
					showEvent(&eps_form->s10E292, data, 02); //BAT 2 MAL (GC9962U)
					showEvent(&eps_form->s10E293, data, 04); //BAT 3 MAL (GC9963U)
					showEvent(&eps_form->s10E294, data, 010); //BAT 4 MAL (GC9964U)
					showEvent(&eps_form->s10E295, data, 020); //BAT 5 MAL (GC9965U)
					showEvent(&eps_form->s10E296, data, 040); //BAT 6 MAL (GC9966U)
				}
				break;
			case 30:
				if (eps_form)
				{
					showEvent(&eps_form->s10E301, data, 01); //BAT 1 HI TAP (GC4361X)
					showEvent(&eps_form->s10E302, data, 02); //BAT 1 LO TAP (GC4362X)
					showEvent(&eps_form->s10E303, data, 04); //BAT 2 HI TAP (GC4363X)
					showEvent(&eps_form->s10E304, data, 010); //BAT 2 LO TAP (GC4364X)
					showEvent(&eps_form->s10E305, data, 020); //BAT 3 HI TAP (GC4365X)
					showEvent(&eps_form->s10E306, data, 040); //BAT 3 LO TAP (GC4366X)
					showEvent(&eps_form->s10E307, data, 0100); //BAT 4 HI TAP (GC4367X)
					showEvent(&eps_form->s10E308, data, 0200); //BAT 4 LO TAP (GC4368X)
				}
				break;
			case 31:
				if (ces_form)
				{
					showEvent(&ces_form->s10E311, data, 01); //OUT DET (GH1204X)
					showEvent(&ces_form->s10E312, data, 02); //AUTO OFF (GH1217X)
					showEvent(&ces_form->s10E313, data, 04); //ENG FIRE OVERRIDE (GH1286X)
					showEvent(&ces_form->s10E314, data, 010); //PGNS MODE AUTO (GH1643X)
					showEvent(&ces_form->s10E315, data, 020); //PGNS MODE ATT HOLD (GH1644X)
					showEvent(&ces_form->s10E316, data, 040); //UNBAL CPLS (GH1896X)
					showEvent(&ces_form->s10E317, data, 0100); //AGS MODE ATT HOLD (GH1642X)
					showEvent(&ces_form->s10E318, data, 0200); //AGS MODE AUTO (GH1641X)
				}
				break;
			case 32: //10E32
				if (dps_form)
				{
					showEvent(&dps_form->s10E322, data, 02); //DPS PROP LO (GQ4455X)
				}
				if (aps_form)
				{
					showEvent(&aps_form->s10E323, data, 04); //APS PROP VLVS D POS (GP2997U)
					showEvent(&aps_form->s10E324, data, 010); //APS PROP VLVS D POS (GP2998U)
				}
				break;
			case 33:
				if (eps_form)
				{
					showEvent(&eps_form->s10E331, data, 01); //BAT 5 B/U CDR (GC4369X)
					showEvent(&eps_form->s10E332, data, 02); //BAT 6 NORM CDR (GC4370X)
					showEvent(&eps_form->s10E333, data, 04); //BAT 5 NORM CDR (GC4371X)
					showEvent(&eps_form->s10E334, data, 010); //BAT 6 B/U CDR (GC4372X)
				}
				break;
			case 40: //10E40
				if (sci_form)
				{
					showEvent(&sci_form->s10E401, data, 01); //LAND GEAR DEPLOY (GM5000U)
				}
				break;
			case 41: //10E41
				if (ces_form)
				{
					showEvent(&ces_form->s10E411, data, 01); //APS ARM (GH1230X)
					showEvent(&ces_form->s10E412, data, 02); //DPS ARM (GH1348X)
					showEvent(&ces_form->s10E413, data, 04); //WIDE DBND (GH1603X)
					showEvent(&ces_form->s10E414, data, 010); //X TRANS OVERRIDE (GH1893X)
				}
				break;
			case 42: //10E42
				if (rcs_form)
				{
					showEvent(&rcs_form->s10E421, data, 01);	//A4 ISO CLSD (GR9661U)
					showEvent(&rcs_form->s10E422, data, 02);	//B4 ISO CLSD (GR9662U)
					showEvent(&rcs_form->s10E423, data, 04);	//A3 ISO CLSD (GR9663U)
					showEvent(&rcs_form->s10E424, data, 010);	//B3 ISO CLSD (GR9664U)
					showEvent(&rcs_form->s10E425, data, 020);	//A2 ISO CLSD (GR9665U)
					showEvent(&rcs_form->s10E426, data, 040);	//B2 ISO CLSD (GR9666U)
					showEvent(&rcs_form->s10E427, data, 0100);	//A1 ISO CLSD (GR9667U)
					showEvent(&rcs_form->s10E428, data, 0200);	//B1 ISO CLSD (GR9668U)
				}
				break;
			case 43: //10E43
				if (aps_form)
				{
					showEvent(&aps_form->s10E431, data, 01); //APS HE 1 CLSD (GP0318X)
					showEvent(&aps_form->s10E432, data, 02); //APS HE 2 CLSD (GP0320X)
				}
				break;
			}
			break;
		case 12:
			switch (ccode)
			{
			case 1:
			case 2:
				if (ces_form)
				{
					showEvent(&ces_form->s12E11, data, 01);		//1D
					showEvent(&ces_form->s12E12, data, 02);		//1U
					showEvent(&ces_form->s12E13, data, 04);		//2D
					showEvent(&ces_form->s12E14, data, 010);	//2U
					showEvent(&ces_form->s12E15, data, 020);	//3D
					showEvent(&ces_form->s12E16, data, 040);	//3U
					showEvent(&ces_form->s12E17, data, 0100);	//4D
					showEvent(&ces_form->s12E18, data, 0200);	//4U
				}
				break;
			case 4:
				if (ces_form)
				{
					showEvent(&ces_form->s12E41, data, 01);		//1S
					showEvent(&ces_form->s12E42, data, 02);		//1F
					showEvent(&ces_form->s12E43, data, 04);		//2S
					showEvent(&ces_form->s12E44, data, 010);	//2F
					showEvent(&ces_form->s12E45, data, 020);	//3S
					showEvent(&ces_form->s12E46, data, 040);	//3F
					showEvent(&ces_form->s12E47, data, 0100);	//4S
					showEvent(&ces_form->s12E48, data, 0200);	//4F
				}
				break;
			}
			break;
		case 22:
			switch (ccode)
			{
			case 0x01A: //22E1a
				if (rcs_form)
				{
					showEvent(&rcs_form->s22E1a1, data, 01);
					showEvent(&rcs_form->s22E1a2, data, 02);
					showEvent(&rcs_form->s22E1a3, data, 04);
					showEvent(&rcs_form->s22E1a4, data, 010);
					showEvent(&rcs_form->s22E1a5, data, 020);
					showEvent(&rcs_form->s22E1a6, data, 040);
					showEvent(&rcs_form->s22E1a7, data, 0100);
					showEvent(&rcs_form->s22E1a8, data, 0200);
				}
				break;
			case 0x01B: //22E1b
				if (rcs_form)
				{
					showEvent(&rcs_form->s22E1b1, data, 01);
					showEvent(&rcs_form->s22E1b2, data, 02);
					showEvent(&rcs_form->s22E1b3, data, 04);
					showEvent(&rcs_form->s22E1b4, data, 010);
					showEvent(&rcs_form->s22E1b5, data, 020);
					showEvent(&rcs_form->s22E1b6, data, 040);
					showEvent(&rcs_form->s22E1b7, data, 0100);
					showEvent(&rcs_form->s22E1b8, data, 0200);
				}
				break;
			}
			break;
		case 51:
			switch (ccode)
			{
			case 1: //51E1
				if (ces_form)
				{
					showEvent(&ces_form->s51E11, data, 01); //APS ON (GH1260X)
					showEvent(&ces_form->s51E12, data, 02); //ABORT STAGE CMD (GH1283X)
				}
				break;
			}
			break;
		}
		break;
	}
}

// Unscale PCM data to original value
double CLMTelemetryClient2Dlg::unscale_data(unsigned char data, double low, double high)
{
	if (data == 0)
	{
		return low;
	}

	if (data == 0xFF)
	{
		return high;
	}

	double step = ((high - low) / 256.0);
	return (data * step) + low;
}

void CLMTelemetryClient2Dlg::showVolts(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf V", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showAmps(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf A", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showCPS(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf CPS", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showKC(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf KC", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showWatts(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf W", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showRPM(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf RPM", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showTempF(CEdit *tb, unsigned char data, double low, double high)
{
	char *sFormat;

	// If low < 0 we need the sign. If low > 0 then high must also be > 0.
	if (low < 0)
	{
		sFormat = "%+07.2f F";
	}
	else
	{
		sFormat = "%06.2f F";
	}

	sprintf_s(msg2, sFormat, unscale_data(data, low, high));
	showValue(tb);
}

void CLMTelemetryClient2Dlg::showPSIA(CEdit *tb, unsigned char data, double low, double high)
{
	char *sFormat = "%05.3f PSIA";
	if (high > 1000)
	{
		sFormat = "%04.0f PSIA";
	}
	else if (high > 100.0)
	{
		sFormat = "%05.1f PSIA";
	}
	else if (high > 10.0)
	{
		sFormat = "%05.2f PSIA";
	}

	sprintf_s(msg2, sFormat, unscale_data(data, low, high));
	showValue(tb);
}

void CLMTelemetryClient2Dlg::showMMHG(CEdit *tb, unsigned char data, double low, double high)
{
	double value = unscale_data(data, low, high);
	sprintf_s(msg2, "%04.2lf MMHG", value);
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::showPercentage(CEdit *tb, unsigned char data, double maxPercent)
{
	sprintf_s(msg2, "%05.2f %%", unscale_data(data, 0, maxPercent));
	showValue(tb);
}

void CLMTelemetryClient2Dlg::showPercentage(CEdit *tb, unsigned char data)
{
	showPercentage(tb, data, 100.0);
}

void CLMTelemetryClient2Dlg::showEvent(CEdit *tb, unsigned char data, int bit)
{
	char *sFormat;

	if (data & bit)
	{
		sFormat = "1111";
	}
	else
	{
		sFormat = "0000";
	}

	sprintf_s(msg2, sFormat);
	showValue(tb);
}

void CLMTelemetryClient2Dlg::showValue(CEdit *tb)
{
	msg = msg2;
	tb->SetWindowText(msg);
}

void CLMTelemetryClient2Dlg::OnBnClickedButton1()
{
	ConnectToHost();
}

void CLMTelemetryClient2Dlg::OnBnClickedButton2()
{
	ShowEPS();
}

void CLMTelemetryClient2Dlg::OnBnClickedButton3()
{
	ShowECS();
}

void CLMTelemetryClient2Dlg::OnBnClickedButton4()
{
	ShowGNC();
}

void CLMTelemetryClient2Dlg::ShowEPS()
{
	if (eps_form == NULL)
	{
		eps_form = new EPSForm(this);
	}
	eps_form->ShowWindow(SW_SHOW);
}

void CLMTelemetryClient2Dlg::ShowECS()
{
	if (ecs_form == NULL)
	{
		ecs_form = new ECSForm(this);
	}
	ecs_form->ShowWindow(SW_SHOW);
}

void CLMTelemetryClient2Dlg::ShowGNC()
{
	if (gnc_form == NULL)
	{
		gnc_form = new GNCForm(this);
	}
	gnc_form->ShowWindow(SW_SHOW);
}

void CLMTelemetryClient2Dlg::OnBnClickedButton5()
{
	if (ces_form == NULL)
	{
		ces_form = new CESForm(this);
	}
	ces_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton7()
{
	if (sci_form == NULL)
	{
		sci_form = new SCIForm(this);
	}
	sci_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton9()
{
	if (radar_form == NULL)
	{
		radar_form = new RadarForm(this);
	}
	radar_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton10()
{
	if (aps_form == NULL)
	{
		aps_form = new APSForm(this);
	}
	aps_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton11()
{
	if (dps_form == NULL)
	{
		dps_form = new DPSForm(this);
	}
	dps_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton12()
{
	if (rcs_form == NULL)
	{
		rcs_form = new RCSForm(this);
	}
	rcs_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton13()
{
	if (comm_ed_form == NULL)
	{
		comm_ed_form = new COMM_ED_Form(this);
	}
	comm_ed_form->ShowWindow(SW_SHOW);
}


void CLMTelemetryClient2Dlg::OnBnClickedButton15()
{
	if (lgc_form == NULL)
	{
		lgc_form = new LGCForm(this);
	}
	lgc_form->ShowWindow(SW_SHOW);
}
