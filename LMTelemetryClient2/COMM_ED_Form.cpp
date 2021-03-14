// COMM_ED_Form.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "COMM_ED_Form.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(COMM_ED_Form, CDialogEx)

COMM_ED_Form::COMM_ED_Form(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG10, pParent)
{
	Create(IDD_DIALOG10, pParent);
}

COMM_ED_Form::~COMM_ED_Form()
{
}

void COMM_ED_Form::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT18, s10A81);
	DDX_Control(pDX, IDC_EDIT1, s10A107);
	DDX_Control(pDX, IDC_EDIT19, s10E111);
	DDX_Control(pDX, IDC_EDIT22, s10E114);
	DDX_Control(pDX, IDC_EDIT23, s10E115);
	DDX_Control(pDX, IDC_EDIT20, s10E116);
	DDX_Control(pDX, IDC_EDIT21, s10E117);
	DDX_Control(pDX, IDC_EDIT17, s10A152);
	DDX_Control(pDX, IDC_EDIT15, s10A185);
	DDX_Control(pDX, IDC_EDIT16, s10A195);
}


BEGIN_MESSAGE_MAP(COMM_ED_Form, CDialogEx)
END_MESSAGE_MAP()