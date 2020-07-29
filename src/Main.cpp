
#include "Main.hpp"

Main::Main()
	: wxFrame(nullptr, 101, "Whiteboard", wxDefaultPosition, wxSize(800, 600))
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(0xffffff));

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer1->AddGrowableCol(0);
	fgSizer1->AddGrowableRow(1);
	fgSizer1->SetFlexibleDirection(wxVERTICAL);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	wxWrapSizer* wSizer2;
	wSizer2 = new wxWrapSizer(wxHORIZONTAL, 0);

	m_colourPicker1 = new wxColourPickerCtrl(this, wxID_ANY, wxColour(0, 0, 0), wxDefaultPosition, wxDefaultSize,
											 wxCLRP_DEFAULT_STYLE);
	wSizer2->Add(m_colourPicker1, 0, wxALL, 5);

	fgSizer1->Add(wSizer2, 1, wxEXPAND, 5);
	m_slider1 = new wxSlider(this, wxID_ANY, 4, 1, 10, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL);
	wSizer2->Add(m_slider1, 0, wxALL, 5);

	m_whiteboard = new Whiteboard(this, m_colourPicker1, m_slider1);
	fgSizer1->Add(m_whiteboard, 1, wxALL | wxEXPAND, 0);

	this->SetSizer(fgSizer1);
	this->Layout();

	this->Centre(wxBOTH);
}

Main::~Main()
{
}
