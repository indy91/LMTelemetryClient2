// GNCForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "GNCForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(GNCForm, CDialogEx)

GNCForm::GNCForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{
	Create(IDD_DIALOG3, pParent);
}

GNCForm::~GNCForm()
{
}

void GNCForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, s10A23);
	DDX_Control(pDX, IDC_EDIT15, s10A121);
	DDX_Control(pDX, IDC_EDIT16, s10A5);
	DDX_Control(pDX, IDC_EDIT17, s10E61);
	DDX_Control(pDX, IDC_EDIT18, s10E62);
	DDX_Control(pDX, IDC_EDIT19, s11A16);
	DDX_Control(pDX, IDC_EDIT20, s11A14);
	DDX_Control(pDX, IDC_EDIT21, s11A9);
	DDX_Control(pDX, IDC_EDIT22, s10A7);
	DDX_Control(pDX, IDC_EDIT23, s11A24);
	DDX_Control(pDX, IDC_EDIT24, s10A64);
	DDX_Control(pDX, IDC_EDIT25, s10A123);
	DDX_Control(pDX, IDC_EDIT26, s10E21);
	DDX_Control(pDX, IDC_EDIT51, s10E22);
	DDX_Control(pDX, IDC_EDIT12, s10A2);
	DDX_Control(pDX, IDC_EDIT54, s51A1);
	DDX_Control(pDX, IDC_EDIT53, s51A2);
	DDX_Control(pDX, IDC_EDIT55, s51A3);
	DDX_Control(pDX, IDC_EDIT56, s12A1);
	DDX_Control(pDX, IDC_EDIT29, s12A3);
	DDX_Control(pDX, IDC_EDIT30, s12A13);
	DDX_Control(pDX, IDC_EDIT31, s11A35);
	DDX_Control(pDX, IDC_EDIT32, s11A17);
	DDX_Control(pDX, IDC_EDIT33, s11A23);
	DDX_Control(pDX, IDC_EDIT34, s11A32);
	DDX_Control(pDX, IDC_EDIT35, s11A10);
	DDX_Control(pDX, IDC_EDIT36, s11A11);
	DDX_Control(pDX, IDC_EDIT37, s11A20);
}


BEGIN_MESSAGE_MAP(GNCForm, CDialogEx)
END_MESSAGE_MAP()