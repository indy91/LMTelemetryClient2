// APSForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "APSForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(APSForm, CDialogEx)

APSForm::APSForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG7, pParent)
{
	Create(IDD_DIALOG7, pParent);
}

APSForm::~APSForm()
{
}

void APSForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT15, s10A37);
	DDX_Control(pDX, IDC_EDIT16, s10A61);
	DDX_Control(pDX, IDC_EDIT17, s10A62);
	DDX_Control(pDX, IDC_EDIT18, s10A93);
	DDX_Control(pDX, IDC_EDIT19, s10A114);
	DDX_Control(pDX, IDC_EDIT20, s10A129);
	DDX_Control(pDX, IDC_EDIT1, s10A153);
	DDX_Control(pDX, IDC_EDIT21, s10A173);
	DDX_Control(pDX, IDC_EDIT22, s10E241);
	DDX_Control(pDX, IDC_EDIT23, s10E242);
	DDX_Control(pDX, IDC_EDIT24, s10A70);
	DDX_Control(pDX, IDC_EDIT25, s11A4);
	DDX_Control(pDX, IDC_EDIT26, s11A22);
	DDX_Control(pDX, IDC_EDIT51, s10E431);
	DDX_Control(pDX, IDC_EDIT52, s10E432);
	DDX_Control(pDX, IDC_EDIT53, s10E323);
	DDX_Control(pDX, IDC_EDIT54, s10E324);
}


BEGIN_MESSAGE_MAP(APSForm, CDialogEx)
END_MESSAGE_MAP()