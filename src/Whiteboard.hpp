#pragma once

#include <vector>

#include <wx/wx.h>
#include <wx/dcgraph.h>
#include <wx/clrpicker.h>
#include <fmt/format.h>

struct PaintedLine
{
	int size;
	wxColour colour;
	std::vector<wxPoint> points;
};

class Whiteboard : public wxPanel
{
private:
	constexpr static int grid_size = 50;

private:
	bool m_is_mouse_down = false;
	wxColourPickerCtrl* m_pen_colour;
	wxSlider* m_pen_size;
	std::vector<PaintedLine> m_splines {};

public:
	Whiteboard(wxFrame* parent, wxColourPickerCtrl* _pen_colour, wxSlider* pen_size);

	void on_paint(wxPaintEvent& evt);
	void on_mouse_moved(wxMouseEvent& evt);
	void on_mouse_down(wxMouseEvent& evt);
	void on_mouse_up(wxMouseEvent& evt);
	void on_key_down(wxKeyEvent& evt);
	void on_key_up(wxKeyEvent& evt);

	void render(wxGCDC& gdc, bool draw_grid = true);

	DECLARE_EVENT_TABLE()
};
