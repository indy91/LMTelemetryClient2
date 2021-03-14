// ECSForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "ECSForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(ECSForm, CDialogEx)

ECSForm::ECSForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{
	Create(IDD_DIALOG2, pParent);
}

ECSForm::~ECSForm()
{
}

void ECSForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, s10E51);
	DDX_Control(pDX, IDC_EDIT15, s10E52);
	DDX_Control(pDX, IDC_EDIT18, s10E53);
	DDX_Control(pDX, IDC_EDIT19, s10E54);
	DDX_Control(pDX, IDC_EDIT20, s10E55);
	DDX_Control(pDX, IDC_EDIT23, s10E56);
	DDX_Control(pDX, IDC_EDIT16, s10E31);
	DDX_Control(pDX, IDC_EDIT17, s10E32);
	DDX_Control(pDX, IDC_EDIT24, s10A172);
	DDX_Control(pDX, IDC_EDIT25, s10A130);
	DDX_Control(pDX, IDC_EDIT45, s10E33);
	DDX_Control(pDX, IDC_EDIT32, s10E34);
	DDX_Control(pDX, IDC_EDIT21, s10E41);
	DDX_Control(pDX, IDC_EDIT22, s10E42);
	DDX_Control(pDX, IDC_EDIT29, s10E43);
	DDX_Control(pDX, IDC_EDIT30, s10E45);
	DDX_Control(pDX, IDC_EDIT28, s10E47);
	DDX_Control(pDX, IDC_EDIT26, s10A17);
	DDX_Control(pDX, IDC_EDIT11, s10A128);
	DDX_Control(pDX, IDC_EDIT12, s10A59);
	DDX_Control(pDX, IDC_EDIT13, s10A137);
	DDX_Control(pDX, IDC_EDIT14, s10A127);
	DDX_Control(pDX, IDC_EDIT27, s10A16);
	DDX_Control(pDX, IDC_EDIT31, s10A83);
	DDX_Control(pDX, IDC_EDIT34, s10A73);
	DDX_Control(pDX, IDC_EDIT33, s10A12);
	DDX_Control(pDX, IDC_EDIT35, s10A131);
	DDX_Control(pDX, IDC_EDIT36, s10A90);
	DDX_Control(pDX, IDC_EDIT37, s10A194);
	DDX_Control(pDX, IDC_EDIT39, s10A183);
	DDX_Control(pDX, IDC_EDIT38, s10A141);
	DDX_Control(pDX, IDC_EDIT42, s10A154);
	DDX_Control(pDX, IDC_EDIT44, s10A58);
	DDX_Control(pDX, IDC_EDIT41, s10A20);
	DDX_Control(pDX, IDC_EDIT43, s10A24);
	DDX_Control(pDX, IDC_EDIT50, s10A13);
	DDX_Control(pDX, IDC_EDIT49, s10A135);
	DDX_Control(pDX, IDC_EDIT46, s10A19);
	DDX_Control(pDX, IDC_EDIT47, s10A120);
	DDX_Control(pDX, IDC_EDIT48, s10A25);
	DDX_Control(pDX, IDC_EDIT40, s10A33);
}


BEGIN_MESSAGE_MAP(ECSForm, CDialogEx)
END_MESSAGE_MAP()