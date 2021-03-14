// RCSForm.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "RCSForm.h"
#include "afxdialogex.h"


// RCSForm-Dialog

IMPLEMENT_DYNAMIC(RCSForm, CDialogEx)

RCSForm::RCSForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG9, pParent)
{
	Create(IDD_DIALOG9, pParent);
}

RCSForm::~RCSForm()
{
}

void RCSForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, s10A8);
	DDX_Control(pDX, IDC_EDIT17, s10A14);
	DDX_Control(pDX, IDC_EDIT18, s10A15);
	DDX_Control(pDX, IDC_EDIT19, s10A21);
	DDX_Control(pDX, IDC_EDIT20, s10A35);
	DDX_Control(pDX, IDC_EDIT21, s10A38);
	DDX_Control(pDX, IDC_EDIT6, s10A66);
	DDX_Control(pDX, IDC_EDIT7, s10A74);
	DDX_Control(pDX, IDC_EDIT24, s10A80);
	DDX_Control(pDX, IDC_EDIT25, s10A84);
	DDX_Control(pDX, IDC_EDIT10, s10A112);
	DDX_Control(pDX, IDC_EDIT52, s10E101);
	DDX_Control(pDX, IDC_EDIT53, s10E102);
	DDX_Control(pDX, IDC_EDIT54, s10E103);
	DDX_Control(pDX, IDC_EDIT55, s10E104);
	DDX_Control(pDX, IDC_EDIT51, s10E105);
	DDX_Control(pDX, IDC_EDIT56, s10E106);
	DDX_Control(pDX, IDC_EDIT57, s10E107);
	DDX_Control(pDX, IDC_EDIT30, s10A124);
	DDX_Control(pDX, IDC_EDIT31, s10A125);
	DDX_Control(pDX, IDC_EDIT32, s10A140);
	DDX_Control(pDX, IDC_EDIT33, s10A146);
	DDX_Control(pDX, IDC_EDIT1, s10A162);
	DDX_Control(pDX, IDC_EDIT15, s22E1a8);
	DDX_Control(pDX, IDC_EDIT34, s22E1a7);
	DDX_Control(pDX, IDC_EDIT35, s22E1a6);
	DDX_Control(pDX, IDC_EDIT36, s22E1a5);
	DDX_Control(pDX, IDC_EDIT37, s22E1a4);
	DDX_Control(pDX, IDC_EDIT38, s22E1a3);
	DDX_Control(pDX, IDC_EDIT39, s22E1a2);
	DDX_Control(pDX, IDC_EDIT40, s22E1a1);
	DDX_Control(pDX, IDC_EDIT41, s22E1b8);
	DDX_Control(pDX, IDC_EDIT42, s22E1b7);
	DDX_Control(pDX, IDC_EDIT43, s22E1b6);
	DDX_Control(pDX, IDC_EDIT44, s22E1b5);
	DDX_Control(pDX, IDC_EDIT45, s22E1b4);
	DDX_Control(pDX, IDC_EDIT46, s22E1b3);
	DDX_Control(pDX, IDC_EDIT47, s22E1b2);
	DDX_Control(pDX, IDC_EDIT48, s22E1b1);
	DDX_Control(pDX, IDC_EDIT75, s10E421);
	DDX_Control(pDX, IDC_EDIT76, s10E422);
	DDX_Control(pDX, IDC_EDIT77, s10E423);
	DDX_Control(pDX, IDC_EDIT78, s10E424);
	DDX_Control(pDX, IDC_EDIT79, s10E425);
	DDX_Control(pDX, IDC_EDIT80, s10E426);
	DDX_Control(pDX, IDC_EDIT81, s10E427);
	DDX_Control(pDX, IDC_EDIT82, s10E428);
}


BEGIN_MESSAGE_MAP(RCSForm, CDialogEx)
END_MESSAGE_MAP()


// RCSForm-Meldungshandler
