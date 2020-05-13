///-----------------------------------------------------------------
///
/// @file      PacManFrm.cpp
/// @author    Carlos, Alvaro e Ivan
/// Created:   09/05/2020 16:54:13
/// @section   DESCRIPTION
///            PacManFrm class implementation
///
///------------------------------------------------------------------

#include "PacManFrm.h"

//Do not add custom headers between
//Header Include Start and Header Include End
//wxDev-C++ designer will remove them
////Header Include Start
////Header Include End

//----------------------------------------------------------------------------
// PacManFrm
//----------------------------------------------------------------------------
//Add Custom Events only in the appropriate block.
//Code added in other places will be removed by wxDev-C++
////Event Table Start
BEGIN_EVENT_TABLE(PacManFrm,wxFrame)
	////Manual Code Start
	////Manual Code End
	
	EVT_CLOSE(PacManFrm::OnClose)
	EVT_ACTIVATE(PacManFrm::PacManFrmActivate)
	EVT_BUTTON(ID_A,PacManFrm::AClick)
	EVT_BUTTON(ID_D,PacManFrm::DClick)
	EVT_BUTTON(ID_S,PacManFrm::SClick)
	EVT_BUTTON(ID_W,PacManFrm::WClick)
END_EVENT_TABLE()
////Event Table End

PacManFrm::PacManFrm(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint &position, const wxSize& size, long style)
: wxFrame(parent, id, title, position, size, style)
{
	CreateGUIControls();
}

PacManFrm::~PacManFrm()
{
}

void PacManFrm::CreateGUIControls()
{
	//Do not add custom code between
	//GUI Items Creation Start and GUI Items Creation End
	//wxDev-C++ designer will remove them.
	//Add the custom code before or after the blocks
	////GUI Items Creation Start

	wxInitAllImageHandlers();   //Initialize graphic format handlers

	Jugador = new wxStaticBitmap(this, ID_JUGADOR, wxBitmap(_("Imagenes/Pacman.bmp"), wxBITMAP_TYPE_BMP), wxPoint(0, 0), wxSize(7, 7) );

	WxEdit4 = new wxTextCtrl(this, ID_WXEDIT4, _("0"), wxPoint(270, 220), wxSize(120, 40), 0, wxDefaultValidator, _("WxEdit4"));
	WxEdit4->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false));

	Puntuacion = new wxStaticText(this, ID_PUNTUACION, _("Puntuacion"), wxPoint(270, 200), wxDefaultSize, 0, _("Puntuacion"));

	WxEdit3 = new wxTextCtrl(this, ID_WXEDIT3, _("3"), wxPoint(270, 160), wxSize(120, 40), 0, wxDefaultValidator, _("WxEdit3"));
	WxEdit3->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false));

	WxEdit2 = new wxTextCtrl(this, ID_WXEDIT2, _("999"), wxPoint(270, 100), wxSize(120, 40), 0, wxDefaultValidator, _("WxEdit2"));
	WxEdit2->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false));

	WxEdit1 = new wxTextCtrl(this, ID_WXEDIT1, _("Normal"), wxPoint(270, 40), wxSize(120, 40), 0, wxDefaultValidator, _("WxEdit1"));
	WxEdit1->SetFont(wxFont(18, wxSWISS, wxNORMAL, wxNORMAL, false));

	A = new wxButton(this, ID_A, _("A"), wxPoint(80, 300), wxSize(40, 40), 0, wxDefaultValidator, _("A"));

	D = new wxButton(this, ID_D, _("D"), wxPoint(160, 300), wxSize(40, 40), 0, wxDefaultValidator, _("D"));

	S = new wxButton(this, ID_S, _("S"), wxPoint(120, 340), wxSize(40, 40), 0, wxDefaultValidator, _("S"));

	VIdas = new wxStaticText(this, ID_VIDAS, _("Vidas"), wxPoint(270, 140), wxDefaultSize, 0, _("VIdas"));

	Tiempo = new wxStaticText(this, ID_TIEMPO, _("Tiempo"), wxPoint(270, 80), wxDefaultSize, 0, _("Tiempo"));

	Dificultad = new wxStaticText(this, ID_DIFICULTAD, _("Dificultad"), wxPoint(270, 20), wxDefaultSize, 0, _("Dificultad"));

	WxStaticBitmap1 = new wxStaticBitmap(this, ID_WXSTATICBITMAP1, wxBitmap(_("Imagenes/Mapa.bmp"), wxBITMAP_TYPE_BMP), wxPoint(30, 5), wxSize(224, 249) );

	W = new wxButton(this, ID_W, _("W"), wxPoint(120, 261), wxSize(40, 40), 0, wxDefaultValidator, _("W"));

	SetTitle(_("PacMan"));
	SetIcon(wxNullIcon);
	SetSize(8,8,426,445);
	Center();
	
	////GUI Items Creation End
}

void PacManFrm::OnClose(wxCloseEvent& event)
{
	Destroy();
}

int x=134;
int y=189;
void PacManFrm::DClick(wxCommandEvent& event)
{
    x=x+8;
    if (wxDefaultPosition.x+x<238)
	Jugador->Move(wxDefaultPosition.x+x,wxDefaultPosition.y+y);
	else x=x-8;
	
}

void PacManFrm::AClick(wxCommandEvent& event)
{
    x=x-8;
    if (wxDefaultPosition.x+x>30)
	Jugador->Move(wxDefaultPosition.x+x,wxDefaultPosition.y+y);
	else x=x+8;
	
}
void PacManFrm::WClick(wxCommandEvent& event)
{
    y=y-8;
    if (wxDefaultPosition.y+y>5)
	Jugador->Move(wxDefaultPosition.x+x,wxDefaultPosition.y+y);
	else y=y+8;
}

void PacManFrm::SClick(wxCommandEvent& event)
{
    y=y+8;
    if (wxDefaultPosition.y+y<238)
	Jugador->Move(wxDefaultPosition.x+x,wxDefaultPosition.y+y);
	else y=y-8;
}

/*
 * PacManFrmActivate
 */
void PacManFrm::PacManFrmActivate(wxActivateEvent& event)
{
	// insert your code here
}
