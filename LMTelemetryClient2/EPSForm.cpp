// EPSForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "EPSForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(EPSForm, CDialogEx)

EPSForm::EPSForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	Create(IDD_DIALOG1, pParent);
}

EPSForm::~EPSForm()
{
}

void EPSForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, s10A82);
	DDX_Control(pDX, IDC_EDIT2, s10A174);
	DDX_Control(pDX, IDC_EDIT4, s10A9);
	DDX_Control(pDX, IDC_EDIT5, s10A36);
	DDX_Control(pDX, IDC_EDIT6, s10A126);
	DDX_Control(pDX, IDC_EDIT7, s10A134);
	DDX_Control(pDX, IDC_EDIT8, s10A91);
	DDX_Control(pDX, IDC_EDIT9, s10A122);
	DDX_Control(pDX, IDC_EDIT11, s10A63);
	DDX_Control(pDX, IDC_EDIT10, s10A67);
	DDX_Control(pDX, IDC_EDIT12, s10A68);
	DDX_Control(pDX, IDC_EDIT13, s10A75);
	DDX_Control(pDX, IDC_EDIT3, s10A72);
	DDX_Control(pDX, IDC_EDIT20, s10A41);
	DDX_Control(pDX, IDC_EDIT27, s10A79);
	DDX_Control(pDX, IDC_EDIT28, s10A57);
	DDX_Control(pDX, IDC_EDIT14, s10E301);
	DDX_Control(pDX, IDC_EDIT29, s10E302);
	DDX_Control(pDX, IDC_EDIT30, s10E303);
	DDX_Control(pDX, IDC_EDIT31, s10E304);
	DDX_Control(pDX, IDC_EDIT32, s10E305);
	DDX_Control(pDX, IDC_EDIT33, s10E306);
	DDX_Control(pDX, IDC_EDIT34, s10E307);
	DDX_Control(pDX, IDC_EDIT35, s10E308);
	DDX_Control(pDX, IDC_EDIT36, s10E331);
	DDX_Control(pDX, IDC_EDIT37, s10E332);
	DDX_Control(pDX, IDC_EDIT38, s10E333);
	DDX_Control(pDX, IDC_EDIT39, s10E334);
	DDX_Control(pDX, IDC_EDIT40, s10E291);
	DDX_Control(pDX, IDC_EDIT41, s10E292);
	DDX_Control(pDX, IDC_EDIT42, s10E293);
	DDX_Control(pDX, IDC_EDIT43, s10E294);
	DDX_Control(pDX, IDC_EDIT44, s10E295);
	DDX_Control(pDX, IDC_EDIT45, s10E296);
}


BEGIN_MESSAGE_MAP(EPSForm, CDialogEx)
END_MESSAGE_MAP()