// SCIForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "SCIForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(SCIForm, CDialogEx)

SCIForm::SCIForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{
	Create(IDD_DIALOG5, pParent);
}

SCIForm::~SCIForm()
{
}

void SCIForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT15, s11A26);
	DDX_Control(pDX, IDC_EDIT16, s11A36);
	DDX_Control(pDX, IDC_EDIT17, s10A85);
	DDX_Control(pDX, IDC_EDIT18, s10E71);
	DDX_Control(pDX, IDC_EDIT19, s10E72);
	DDX_Control(pDX, IDC_EDIT20, s10E73);
	DDX_Control(pDX, IDC_EDIT21, s10E76);
	DDX_Control(pDX, IDC_EDIT22, s10E74);
	DDX_Control(pDX, IDC_EDIT23, s10E75);
	DDX_Control(pDX, IDC_EDIT24, s10A171);
	DDX_Control(pDX, IDC_EDIT25, s10A180);
	DDX_Control(pDX, IDC_EDIT1, s10E78);
	DDX_Control(pDX, IDC_EDIT26, s10E401);
}


BEGIN_MESSAGE_MAP(SCIForm, CDialogEx)
END_MESSAGE_MAP()