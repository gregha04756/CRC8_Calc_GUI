
// CRC8_Calc_GUI.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCRC8CalcGUIApp:
// See CRC8_Calc_GUI.cpp for the implementation of this class
//

class CCRC8CalcGUIApp : public CWinApp
{
public:
	CCRC8CalcGUIApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CCRC8CalcGUIApp theApp;
