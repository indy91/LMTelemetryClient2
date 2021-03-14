// CESForm.cpp
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "CESForm.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CESForm, CDialogEx)

CESForm::CESForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{
	Create(IDD_DIALOG4, pParent);
}

CESForm::~CESForm()
{
}

void CESForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT22, s10A11);
	DDX_Control(pDX, IDC_EDIT23, s10A22);
	DDX_Control(pDX, IDC_EDIT25, s10A26);
	DDX_Control(pDX, IDC_EDIT51, s51E11);
	DDX_Control(pDX, IDC_EDIT52, s51E12);
	DDX_Control(pDX, IDC_EDIT53, s11A19);
	DDX_Control(pDX, IDC_EDIT54, s11A29);
	DDX_Control(pDX, IDC_EDIT55, s11A38);
	DDX_Control(pDX, IDC_EDIT28, s10A60);
	DDX_Control(pDX, IDC_EDIT57, s10A65);
	DDX_Control(pDX, IDC_EDIT30, s10A115);
	DDX_Control(pDX, IDC_EDIT31, s10A132);
	DDX_Control(pDX, IDC_EDIT32, s10A139);
	DDX_Control(pDX, IDC_EDIT33, s10A155);
	DDX_Control(pDX, IDC_EDIT34, s10A175);
	DDX_Control(pDX, IDC_EDIT35, s10A186);
	DDX_Control(pDX, IDC_EDIT15, s10E231);
	DDX_Control(pDX, IDC_EDIT58, s10E232);
	DDX_Control(pDX, IDC_EDIT37, s10E233);
	DDX_Control(pDX, IDC_EDIT38, s10E234);
	DDX_Control(pDX, IDC_EDIT39, s10E235);
	DDX_Control(pDX, IDC_EDIT50, s12E11);
	DDX_Control(pDX, IDC_EDIT49, s12E12);
	DDX_Control(pDX, IDC_EDIT46, s12E13);
	DDX_Control(pDX, IDC_EDIT45, s12E14);
	DDX_Control(pDX, IDC_EDIT42, s12E15);
	DDX_Control(pDX, IDC_EDIT41, s12E16);
	DDX_Control(pDX, IDC_EDIT8, s12E17);
	DDX_Control(pDX, IDC_EDIT5, s12E18);
	DDX_Control(pDX, IDC_EDIT60, s12E41);
	DDX_Control(pDX, IDC_EDIT59, s12E42);
	DDX_Control(pDX, IDC_EDIT48, s12E43);
	DDX_Control(pDX, IDC_EDIT47, s12E44);
	DDX_Control(pDX, IDC_EDIT44, s12E45);
	DDX_Control(pDX, IDC_EDIT43, s12E46);
	DDX_Control(pDX, IDC_EDIT40, s12E47);
	DDX_Control(pDX, IDC_EDIT10, s12E48);
	DDX_Control(pDX, IDC_EDIT1, s10E311);
	DDX_Control(pDX, IDC_EDIT16, s10E312);
	DDX_Control(pDX, IDC_EDIT61, s10E313);
	DDX_Control(pDX, IDC_EDIT62, s10E314);
	DDX_Control(pDX, IDC_EDIT63, s10E315);
	DDX_Control(pDX, IDC_EDIT65, s10E316);
	DDX_Control(pDX, IDC_EDIT71, s10E317);
	DDX_Control(pDX, IDC_EDIT70, s10E318);
	DDX_Control(pDX, IDC_EDIT17, s10E411);
	DDX_Control(pDX, IDC_EDIT72, s10E412);
	DDX_Control(pDX, IDC_EDIT66, s10E413);
	DDX_Control(pDX, IDC_EDIT64, s10E414);
	DDX_Control(pDX, IDC_EDIT18, s11A1);
	DDX_Control(pDX, IDC_EDIT19, s11A8);
	DDX_Control(pDX, IDC_EDIT20, s11A18);
	DDX_Control(pDX, IDC_EDIT67, s10E271);
	DDX_Control(pDX, IDC_EDIT68, s10E272);
	DDX_Control(pDX, IDC_EDIT69, s10E273);
	DDX_Control(pDX, IDC_EDIT73, s10E274);
	DDX_Control(pDX, IDC_EDIT74, s10E275);
}


BEGIN_MESSAGE_MAP(CESForm, CDialogEx)
END_MESSAGE_MAP()