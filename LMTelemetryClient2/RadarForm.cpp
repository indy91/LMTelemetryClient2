// RadarForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "RadarForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(RadarForm, CDialogEx)

RadarForm::RadarForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG6, pParent)
{
	Create(IDD_DIALOG6, pParent);
}

RadarForm::~RadarForm()
{
}

void RadarForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, s10E11);
	DDX_Control(pDX, IDC_EDIT15, s10E12);
	DDX_Control(pDX, IDC_EDIT17, s10E13);
	DDX_Control(pDX, IDC_EDIT18, s10A138);
	DDX_Control(pDX, IDC_EDIT16, s10A164);
}


BEGIN_MESSAGE_MAP(RadarForm, CDialogEx)
END_MESSAGE_MAP()