//---------------------------------------------------------------------------
//
// Name:        PacManApp.h
// Author:      Carlos, Alvaro e Ivan
// Created:     09/05/2020 16:54:12
// Description: 
//
//---------------------------------------------------------------------------

#ifndef __PACMANFRMApp_h__
#define __PACMANFRMApp_h__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#else
	#include <wx/wxprec.h>
#endif

class PacManFrmApp : public wxApp
{
	public:
		bool OnInit();
		int OnExit();
};

#endif
