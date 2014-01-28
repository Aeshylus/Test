
// Diploma.h : main header file for the Diploma application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

#pragma comment(lib, "irrlicht.lib")

// CDiplomaApp:
// See Diploma.cpp for the implementation of this class
//

#include <boost\signal.hpp>

//////////////////////////////////////////////////////////////////////////
class CDiplomaApp : public CWinAppEx
{
typedef CWinAppEx _Super;
public:
	CDiplomaApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

  boost::signal<void (void)> m_update_view;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

  virtual int Run() override;

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

};

extern CDiplomaApp theApp;
