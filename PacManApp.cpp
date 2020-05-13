//---------------------------------------------------------------------------
//
// Name:        PacManApp.cpp
// Author:      Carlos, Alvaro e Ivan
// Created:     09/05/2020 16:54:12
// Description: 
//
//---------------------------------------------------------------------------

#include "PacManApp.h"
#include "PacManFrm.h"

IMPLEMENT_APP(PacManFrmApp)

bool PacManFrmApp::OnInit()
{
    PacManFrm* frame = new PacManFrm(NULL);
    SetTopWindow(frame);
    frame->Show();
    return true;
}
 
int PacManFrmApp::OnExit()
{
	return 0;
}
