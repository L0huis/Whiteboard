#pragma once

#include <string>

#include <fmt/format.h>

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/clrpicker.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/string.h>
#include <wx/wrapsizer.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/frame.h>

#include "Whiteboard.hpp"

class Main : public wxFrame
{
private:
protected:
	wxColourPickerCtrl* m_colourPicker1;
	wxSlider* m_slider1;
	Whiteboard* m_whiteboard;

public:
	Main();

	~Main();
};