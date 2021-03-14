// LGCForm.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "LMTelemetryClient2.h"
#include "LGCForm.h"
#include "afxdialogex.h"


// LGCForm-Dialog

IMPLEMENT_DYNAMIC(LGCForm, CDialogEx)

LGCForm::LGCForm(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG11, pParent)
{
	Create(IDD_DIALOG11, pParent);
}

LGCForm::~LGCForm()
{
}

void LGCForm::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, lgcListID);
	DDX_Control(pDX, IDC_EDIT2, CSMPosX);
	DDX_Control(pDX, IDC_EDIT17, CSMPosY);
	DDX_Control(pDX, IDC_EDIT18, CSMPosZ);
	DDX_Control(pDX, IDC_EDIT19, CSMVelX);
	DDX_Control(pDX, IDC_EDIT20, CSMVelY);
	DDX_Control(pDX, IDC_EDIT21, CSMVelZ);
	DDX_Control(pDX, IDC_EDIT22, CSMTsv);
	DDX_Control(pDX, IDC_EDIT23, DELLT4);
	DDX_Control(pDX, IDC_EDIT24, RTARGX);
	DDX_Control(pDX, IDC_EDIT25, RTARGY);
	DDX_Control(pDX, IDC_EDIT26, RTARGZ);
	DDX_Control(pDX, IDC_EDIT51, ELEV);
	DDX_Control(pDX, IDC_EDIT52, TEVENT);
	DDX_Control(pDX, IDC_EDIT53, REFS11);
	DDX_Control(pDX, IDC_EDIT54, REFS12);
	DDX_Control(pDX, IDC_EDIT55, REFS13);
	DDX_Control(pDX, IDC_EDIT56, REFS21);
	DDX_Control(pDX, IDC_EDIT57, REFS22);
	DDX_Control(pDX, IDC_EDIT83, REFS23);
	DDX_Control(pDX, IDC_EDIT84, CSITIG);
	DDX_Control(pDX, IDC_EDIT85, CSIDVX);
	DDX_Control(pDX, IDC_EDIT86, CSIDVY);
	DDX_Control(pDX, IDC_EDIT87, CSIDVZ);
	DDX_Control(pDX, IDC_EDIT88, VGTIGX);
	DDX_Control(pDX, IDC_EDIT89, VGTIGY);
	DDX_Control(pDX, IDC_EDIT90, VGTIGZ);
	DDX_Control(pDX, IDC_EDIT94, LRVelZ);
	DDX_Control(pDX, IDC_EDIT91, LRAlt);
	DDX_Control(pDX, IDC_EDIT95, TTPF);
	DDX_Control(pDX, IDC_EDIT96, RedoCounter);
	DDX_Control(pDX, IDC_EDIT97, THETADX);
	DDX_Control(pDX, IDC_EDIT98, THETADY);
	DDX_Control(pDX, IDC_EDIT99, THETADZ);
	DDX_Control(pDX, IDC_EDIT100, RSBBQ);
	DDX_Control(pDX, IDC_EDIT101, BodyRateX);
	DDX_Control(pDX, IDC_EDIT102, BodyRateY);
	DDX_Control(pDX, IDC_EDIT103, BodyRateZ);
	DDX_Control(pDX, IDC_EDIT104, CDUXD);
	DDX_Control(pDX, IDC_EDIT105, CDUYD);
	DDX_Control(pDX, IDC_EDIT106, CDUZD);
	DDX_Control(pDX, IDC_EDIT107, ActualCDUX);
	DDX_Control(pDX, IDC_EDIT108, ActualCDUY);
	DDX_Control(pDX, IDC_EDIT109, ActualCDUZ);
	DDX_Control(pDX, IDC_EDIT110, RRTrunnionCDU);
	DDX_Control(pDX, IDC_EDIT111, Flagword01);
	DDX_Control(pDX, IDC_EDIT112, Flagword23);
	DDX_Control(pDX, IDC_EDIT113, Flagword45);
	DDX_Control(pDX, IDC_EDIT114, Flagword67);
	DDX_Control(pDX, IDC_EDIT115, Flagword89);
	DDX_Control(pDX, IDC_EDIT116, Flagword1011);
	DDX_Control(pDX, IDC_EDIT117, DSKY_Prog);
	DDX_Control(pDX, IDC_EDIT118, DSKY_Verb);
	DDX_Control(pDX, IDC_EDIT119, DSKY_Noun);
	DDX_Control(pDX, IDC_EDIT120, DSKY_R1);
	DDX_Control(pDX, IDC_EDIT121, DSKY_R2);
	DDX_Control(pDX, IDC_EDIT122, DSKY_R3);
	DDX_Control(pDX, IDC_STATIC46, DSKY_NoAtt);
	DDX_Control(pDX, IDC_STATIC47, DSKY_GimbalLock);
	DDX_Control(pDX, IDC_STATIC48, DSKY_ProgAlarm);
	DDX_Control(pDX, IDC_STATIC49, DSKY_Tracker);
	DDX_Control(pDX, IDC_STATIC50, DSKY_Alt);
	DDX_Control(pDX, IDC_STATIC51, DSKY_Vel);
	DDX_Control(pDX, IDC_EDIT123, Time1Time2);
	DDX_Control(pDX, IDC_EDIT49, LMPosX);
	DDX_Control(pDX, IDC_EDIT124, LMPosY);
	DDX_Control(pDX, IDC_EDIT125, LMPosZ);
	DDX_Control(pDX, IDC_EDIT126, LMVelX);
	DDX_Control(pDX, IDC_EDIT127, LMVelY);
	DDX_Control(pDX, IDC_EDIT128, LMVelZ);
	DDX_Control(pDX, IDC_EDIT129, LMTsv);
	DDX_Control(pDX, IDC_EDIT130, CADRFLSH1);
	DDX_Control(pDX, IDC_EDIT131, CADRFLSH2);
	DDX_Control(pDX, IDC_EDIT132, CADRFLSH3);
	DDX_Control(pDX, IDC_EDIT133, DesiredBodyRateX);
	DDX_Control(pDX, IDC_EDIT134, DesiredBodyRateY);
	DDX_Control(pDX, IDC_EDIT135, DesiredBodyRateZ);
	DDX_Control(pDX, IDC_EDIT136, FAILREG1);
	DDX_Control(pDX, IDC_EDIT137, FAILREG2);
	DDX_Control(pDX, IDC_EDIT138, FAILREG3);
	DDX_Control(pDX, IDC_EDIT141, RADMODES);
	DDX_Control(pDX, IDC_EDIT142, DAPBOOLS);
	DDX_Control(pDX, IDC_EDIT143, POSTORKU);
	DDX_Control(pDX, IDC_EDIT144, NEGTORKU);
	DDX_Control(pDX, IDC_EDIT145, POSTORKV);
	DDX_Control(pDX, IDC_EDIT146, NEGTORKV);
	DDX_Control(pDX, IDC_EDIT147, CDHTIG);
	DDX_Control(pDX, IDC_EDIT148, CDHDVX);
	DDX_Control(pDX, IDC_EDIT149, CDHDVY);
	DDX_Control(pDX, IDC_EDIT150, CDHDVZ);
	DDX_Control(pDX, IDC_EDIT151, TPITIG);
	DDX_Control(pDX, IDC_EDIT152, TPIDVX);
	DDX_Control(pDX, IDC_EDIT153, TPIDVY);
	DDX_Control(pDX, IDC_EDIT154, TPIDVZ);
	DDX_Control(pDX, IDC_EDIT139, RRRange);
	DDX_Control(pDX, IDC_EDIT140, RRRangeRate);
	DDX_Control(pDX, IDC_EDIT92, LRVelX);
	DDX_Control(pDX, IDC_EDIT93, LRVelY);
	DDX_Control(pDX, IDC_EDIT155, CDHDH);
	DDX_Control(pDX, IDC_EDIT156, LMMass);
	DDX_Control(pDX, IDC_EDIT157, CSMMass);
	DDX_Control(pDX, IDC_EDIT158, IMODES30);
	DDX_Control(pDX, IDC_EDIT159, IMODES33);
	DDX_Control(pDX, IDC_EDIT160, TIG);
	DDX_Control(pDX, IDC_EDIT164, MomentOffsetQ);
	DDX_Control(pDX, IDC_EDIT165, MomentOffsetR);
	DDX_Control(pDX, IDC_EDIT161, DELV_SM_X);
	DDX_Control(pDX, IDC_EDIT162, DELV_SM_Y);
	DDX_Control(pDX, IDC_EDIT163, DELV_SM_Z);
	DDX_Control(pDX, IDC_EDIT166, POSTORKP);
	DDX_Control(pDX, IDC_EDIT167, NEGTORKP);
	DDX_Control(pDX, IDC_EDIT168, TGO);
	DDX_Control(pDX, IDC_EDIT169, PIPTIME1);
	DDX_Control(pDX, IDC_EDIT170, Channel11_12);
	DDX_Control(pDX, IDC_EDIT171, Channel13_14);
	DDX_Control(pDX, IDC_EDIT172, Channel30_31);
	DDX_Control(pDX, IDC_EDIT173, Channel32_33);
}


BEGIN_MESSAGE_MAP(LGCForm, CDialogEx)
END_MESSAGE_MAP()


// LGCForm-Meldungshandler
