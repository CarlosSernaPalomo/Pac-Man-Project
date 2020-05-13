///-----------------------------------------------------------------
///
/// @file      PacManFrm.h
/// @author    Carlos, Alvaro e Ivan
/// Created:   09/05/2020 16:54:13
/// @section   DESCRIPTION
///            PacManFrm class declaration
///
///------------------------------------------------------------------

#ifndef __PACMANFRM_H__
#define __PACMANFRM_H__

#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#ifndef WX_PRECOMP
	#include <wx/wx.h>
	#include <wx/frame.h>
#else
	#include <wx/wxprec.h>
#endif

//Do not add custom headers between 
//Header Include Start and Header Include End.
//wxDev-C++ designer will remove them. Add custom headers after the block.
////Header Include Start
#include <wx/textctrl.h>
#include <wx/stattext.h>
#include <wx/statbmp.h>
#include <wx/button.h>
////Header Include End

////Dialog Style Start
#undef PacManFrm_STYLE
#define PacManFrm_STYLE wxCAPTION | wxSYSTEM_MENU | wxMINIMIZE_BOX | wxCLOSE_BOX
////Dialog Style End

class PacManFrm : public wxFrame
{
	private:
		DECLARE_EVENT_TABLE();
		
	public:
		PacManFrm(wxWindow *parent, wxWindowID id = 1, const wxString &title = wxT("PacMan"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = PacManFrm_STYLE);
		virtual ~PacManFrm();
		void AClick(wxCommandEvent& event);
		void SClick(wxCommandEvent& event);
		void DClick(wxCommandEvent& event);
		void WClick(wxCommandEvent& event);
		void PacManFrmActivate(wxActivateEvent& event);
		
	private:
		//Do not add custom control declarations between
		//GUI Control Declaration Start and GUI Control Declaration End.
		//wxDev-C++ will remove them. Add custom code after the block.
		////GUI Control Declaration Start
		wxStaticBitmap *Jugador;
		wxTextCtrl *WxEdit4;
		wxStaticText *Puntuacion;
		wxTextCtrl *WxEdit3;
		wxTextCtrl *WxEdit2;
		wxTextCtrl *WxEdit1;
		wxButton *A;
		wxButton *D;
		wxButton *S;
		wxStaticText *VIdas;
		wxStaticText *Tiempo;
		wxStaticText *Dificultad;
		wxStaticBitmap *WxStaticBitmap1;
		wxButton *W;
		////GUI Control Declaration End
		
	private:
		//Note: if you receive any error with these enum IDs, then you need to
		//change your old form code that are based on the #define control IDs.
		//#defines may replace a numeric value for the enum names.
		//Try copy and pasting the below block in your old form header files.
		enum
		{
			////GUI Enum Control ID Start
			ID_JUGADOR = 1018,
			ID_WXEDIT4 = 1016,
			ID_PUNTUACION = 1015,
			ID_WXEDIT3 = 1014,
			ID_WXEDIT2 = 1013,
			ID_WXEDIT1 = 1012,
			ID_A = 1011,
			ID_D = 1009,
			ID_S = 1008,
			ID_VIDAS = 1007,
			ID_TIEMPO = 1006,
			ID_DIFICULTAD = 1005,
			ID_WXSTATICBITMAP1 = 1004,
			ID_W = 1002,
			////GUI Enum Control ID End
			ID_DUMMY_VALUE_ //don't remove this value unless you have other enum values
		};
		
	private:
		void OnClose(wxCloseEvent& event);
		void CreateGUIControls();
};

#endif
