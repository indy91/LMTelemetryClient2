// UplinkForm.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "UplinkForm.h"
#include "LMTelemetryClient2Dlg.h"
#include "afxdialogex.h"


// UplinkForm-Dialog

IMPLEMENT_DYNAMIC(UplinkForm, CDialogEx)

UplinkForm::UplinkForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG12, pParent)
{
	Create(IDD_DIALOG12, pParent);

	parent = (CLMTelemetryClient2Dlg*)pParent;
}

UplinkForm::~UplinkForm()
{
}

void UplinkForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, DSKY_Prog);
	DDX_Control(pDX, IDC_EDIT16, DSKY_Verb);
	DDX_Control(pDX, IDC_EDIT15, DSKY_Noun);
	DDX_Control(pDX, IDC_EDIT17, DSKY_R1);
	DDX_Control(pDX, IDC_EDIT18, DSKY_R2);
	DDX_Control(pDX, IDC_EDIT19, DSKY_R3);
	DDX_Control(pDX, IDC_STATIC16, DSKY_ProgAlarm);
	DDX_Control(pDX, IDC_STATIC18, DSKY_Tracker);
	DDX_Control(pDX, IDC_STATIC15, DSKY_GimbalLock);
	DDX_Control(pDX, IDC_STATIC19, DSKY_Alt);
	DDX_Control(pDX, IDC_STATIC11, DSKY_NoAtt);
	DDX_Control(pDX, IDC_STATIC20, DSKY_Vel);
	DDX_Control(pDX, IDC_STATIC9, DSKY_UplinkActivity);
	DDX_Control(pDX, IDC_STATIC10, DSKY_Temp);
	DDX_Control(pDX, IDC_STATIC12, DSKY_Standby);
	DDX_Control(pDX, IDC_STATIC13, DSKY_KeyReleaseLight);
	DDX_Control(pDX, IDC_STATIC17, DSKY_Restart);
	DDX_Control(pDX, IDC_STATIC14, DSKY_OperatorError);
	DDX_Control(pDX, IDC_EDIT5, s10E411);
	DDX_Control(pDX, IDC_EDIT6, s10E235);
}


BEGIN_MESSAGE_MAP(UplinkForm, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON27, &UplinkForm::OnBnClickedButtonDSKY_0)
	ON_BN_CLICKED(IDC_BUTTON6, &UplinkForm::OnBnClickedButtonDSKY_1)
	ON_BN_CLICKED(IDC_BUTTON18, &UplinkForm::OnBnClickedButtonDSKY_2)
	ON_BN_CLICKED(IDC_BUTTON19, &UplinkForm::OnBnClickedButtonDSKY_3)
	ON_BN_CLICKED(IDC_BUTTON20, &UplinkForm::OnBnClickedButtonDSKY_4)
	ON_BN_CLICKED(IDC_BUTTON21, &UplinkForm::OnBnClickedButtonDSKY_5)
	ON_BN_CLICKED(IDC_BUTTON22, &UplinkForm::OnBnClickedButtonDSKY_6)
	ON_BN_CLICKED(IDC_BUTTON23, &UplinkForm::OnBnClickedButtonDSKY_7)
	ON_BN_CLICKED(IDC_BUTTON24, &UplinkForm::OnBnClickedButtonDSKY_8)
	ON_BN_CLICKED(IDC_BUTTON25, &UplinkForm::OnBnClickedButtonDSKY_9)
	ON_BN_CLICKED(IDC_BUTTON3, &UplinkForm::OnBnClickedButtonDSKY_V)
	ON_BN_CLICKED(IDC_BUTTON4, &UplinkForm::OnBnClickedButtonDSKY_N)
	ON_BN_CLICKED(IDC_BUTTON5, &UplinkForm::OnBnClickedButtonDSKY_R)
	ON_BN_CLICKED(IDC_BUTTON8, &UplinkForm::OnBnClickedButtonDSKY_C)
	ON_BN_CLICKED(IDC_BUTTON14, &UplinkForm::OnBnClickedButtonDSKY_K)
	ON_BN_CLICKED(IDC_BUTTON17, &UplinkForm::OnBnClickedButtonDSKY_E)
	ON_BN_CLICKED(IDC_BUTTON9, &UplinkForm::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &UplinkForm::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &UplinkForm::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &UplinkForm::OnBnClickedButton12)
END_MESSAGE_MAP()


// UplinkForm-Meldungshandler

void UplinkForm::OnBnClickedButtonDSKY_0()
{
	parent->send_agc_key('0');
}

void UplinkForm::OnBnClickedButtonDSKY_1()
{
	parent->send_agc_key('1');
}

void UplinkForm::OnBnClickedButtonDSKY_2()
{
	parent->send_agc_key('2');
}

void UplinkForm::OnBnClickedButtonDSKY_3()
{
	parent->send_agc_key('3');
}

void UplinkForm::OnBnClickedButtonDSKY_4()
{
	parent->send_agc_key('4');
}

void UplinkForm::OnBnClickedButtonDSKY_5()
{
	parent->send_agc_key('5');
}

void UplinkForm::OnBnClickedButtonDSKY_6()
{
	parent->send_agc_key('6');
}

void UplinkForm::OnBnClickedButtonDSKY_7()
{
	parent->send_agc_key('7');
}

void UplinkForm::OnBnClickedButtonDSKY_8()
{
	parent->send_agc_key('8');
}

void UplinkForm::OnBnClickedButtonDSKY_9()
{
	parent->send_agc_key('9');
}

void UplinkForm::OnBnClickedButtonDSKY_V()
{
	parent->send_agc_key('V');
}

void UplinkForm::OnBnClickedButtonDSKY_N()
{
	parent->send_agc_key('N');
}

void UplinkForm::OnBnClickedButtonDSKY_R()
{
	parent->send_agc_key('R');
}

void UplinkForm::OnBnClickedButtonDSKY_C()
{
	parent->send_agc_key('C');
}

void UplinkForm::OnBnClickedButtonDSKY_K()
{
	parent->send_agc_key('K');
}

void UplinkForm::OnBnClickedButtonDSKY_E()
{
	parent->send_agc_key('E');
}

void UplinkForm::OnBnClickedButton9()
{
	parent->send_aeaa_cmd(true, true);
}


void UplinkForm::OnBnClickedButton10()
{
	parent->send_aeaa_cmd(true, false);
}


void UplinkForm::OnBnClickedButton11()
{
	parent->send_aeaa_cmd(false, true);
}


void UplinkForm::OnBnClickedButton12()
{
	parent->send_aeaa_cmd(false, false);
}
