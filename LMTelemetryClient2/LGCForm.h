#pragma once


// LGCForm-Dialog

class LGCForm : public CDialogEx
{
	DECLARE_DYNAMIC(LGCForm)

public:
	LGCForm(CWnd* pParent = nullptr);   // Standardkonstruktor
	virtual ~LGCForm();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG11 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	CEdit lgcListID;
	CEdit CSMPosX;
	CEdit CSMPosY;
	CEdit CSMPosZ;
	CEdit CSMVelX;
	CEdit CSMVelY;
	CEdit CSMVelZ;
	CEdit CSMTsv;
	CEdit DELLT4;
	CEdit RTARGX;
	CEdit RTARGY;
	CEdit RTARGZ;
	CEdit ELEV;
	CEdit TEVENT;
	CEdit REFS11;
	CEdit REFS12;
	CEdit REFS13;
	CEdit REFS21;
	CEdit REFS22;
	CEdit REFS23;
	CEdit CSITIG;
	CEdit CSIDVX;
	CEdit CSIDVY;
	CEdit CSIDVZ;
	CEdit VGTIGX;
	CEdit VGTIGY;
	CEdit VGTIGZ;
	CEdit LRVelZ;
	CEdit LRAlt;
	CEdit TTPF;
	CEdit RedoCounter;
	CEdit THETADX;
	CEdit THETADY;
	CEdit THETADZ;
	CEdit RSBBQ;
	CEdit BodyRateX;
	CEdit BodyRateY;
	CEdit BodyRateZ;
	CEdit CDUXD;
	CEdit CDUYD;
	CEdit CDUZD;
	CEdit ActualCDUX;
	CEdit ActualCDUY;
	CEdit ActualCDUZ;
	CEdit RRTrunnionCDU;
	CEdit Flagword01;
	CEdit Flagword23;
	CEdit Flagword45;
	CEdit Flagword67;
	CEdit Flagword89;
	CEdit Flagword1011;
	CEdit DSKY_Prog;
	CEdit DSKY_Verb;
	CEdit DSKY_Noun;
	CEdit DSKY_R1;
	CEdit DSKY_R2;
	CEdit DSKY_R3;
	CStatic DSKY_NoAtt;
	CStatic DSKY_GimbalLock;
	CStatic DSKY_ProgAlarm;
	CStatic DSKY_Tracker;
	CStatic DSKY_Alt;
	CStatic DSKY_Vel;
	CEdit Time1Time2;
	CEdit LMPosX;
	CEdit LMPosY;
	CEdit LMPosZ;
	CEdit LMVelX;
	CEdit LMVelY;
	CEdit LMVelZ;
	CEdit LMTsv;
	CEdit CADRFLSH1;
	CEdit CADRFLSH2;
	CEdit CADRFLSH3;
	CEdit DesiredBodyRateX;
	CEdit DesiredBodyRateY;
	CEdit DesiredBodyRateZ;
	CEdit FAILREG1;
	CEdit FAILREG2;
	CEdit FAILREG3;
	CEdit RADMODES;
	CEdit DAPBOOLS;
	CEdit POSTORKU;
	CEdit NEGTORKU;
	CEdit POSTORKV;
	CEdit NEGTORKV;
	CEdit CDHTIG;
	CEdit CDHDVX;
	CEdit CDHDVY;
	CEdit CDHDVZ;
	CEdit TPITIG;
	CEdit TPIDVX;
	CEdit TPIDVY;
	CEdit TPIDVZ;
	CEdit RRRange;
	CEdit RRRangeRate;
	CEdit LRVelX;
	CEdit LRVelY;
	CEdit CDHDH;
	CEdit LMMass;
	CEdit CSMMass;
	CEdit IMODES30;
	CEdit IMODES33;
	CEdit TIG;
	CEdit MomentOffsetQ;
	CEdit MomentOffsetR;
	CEdit DELV_SM_X;
	CEdit DELV_SM_Y;
	CEdit DELV_SM_Z;
	CEdit POSTORKP;
	CEdit NEGTORKP;
	CEdit TGO;
	CEdit PIPTIME1;
	CEdit Channel11_12;
	CEdit Channel13_14;
	CEdit Channel30_31;
	CEdit Channel32_33;
};
