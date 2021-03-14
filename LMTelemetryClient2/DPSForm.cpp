// DPSForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "DPSForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(DPSForm, CDialogEx)

DPSForm::DPSForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG8, pParent)
{
	Create(IDD_DIALOG8, pParent);
}

DPSForm::~DPSForm()
{
}

void DPSForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, s10A40);
	DDX_Control(pDX, IDC_EDIT15, s10A10);
	DDX_Control(pDX, IDC_EDIT16, s10A18);
	DDX_Control(pDX, IDC_EDIT17, s10A42);
	DDX_Control(pDX, IDC_EDIT18, s10A76);
	DDX_Control(pDX, IDC_EDIT19, s10A101);
	DDX_Control(pDX, IDC_EDIT20, s10A104);
	DDX_Control(pDX, IDC_EDIT21, s10A113);
	DDX_Control(pDX, IDC_EDIT22, s10A133);
	DDX_Control(pDX, IDC_EDIT23, s10A165);
	DDX_Control(pDX, IDC_EDIT24, s10A193);
	DDX_Control(pDX, IDC_EDIT25, s10A3);
	DDX_Control(pDX, IDC_EDIT26, s10A4);
	DDX_Control(pDX, IDC_EDIT51, s10A108);
	DDX_Control(pDX, IDC_EDIT52, s10A6);
	DDX_Control(pDX, IDC_EDIT53, s10A117);
	DDX_Control(pDX, IDC_EDIT54, s10A34);
	DDX_Control(pDX, IDC_EDIT27, s10E322);
}


BEGIN_MESSAGE_MAP(DPSForm, CDialogEx)
END_MESSAGE_MAP()