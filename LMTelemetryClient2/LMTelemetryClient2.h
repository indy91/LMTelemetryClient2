
// LMTelemetryClient2.h
//

#pragma once

#ifndef __AFXWIN_H__
	#error "Include 'stdafx.h'"
#endif

#include "resource.h"

class CLMTelemetryClient2App : public CWinApp
{
public:
	CLMTelemetryClient2App();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CLMTelemetryClient2App theApp;
