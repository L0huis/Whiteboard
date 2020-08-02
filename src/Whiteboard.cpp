#include "Whiteboard.hpp"

Whiteboard::Whiteboard(wxFrame* parent, wxColourPickerCtrl* pen_colour, wxSlider* pen_size)
	: m_pen_colour(pen_colour)
	, m_pen_size(pen_size)
	, wxPanel(parent)
{
	SetBackgroundColour(wxColor(0xFFFFFF));
	m_splines.reserve(1024);
	SetDoubleBuffered(true);

	wxInitAllImageHandlers();
}

void Whiteboard::on_paint(wxPaintEvent& evt)
{
	wxPaintDC dc(this);
	wxGCDC gdc(dc);
	render(gdc);
}

void Whiteboard::on_mouse_moved(wxMouseEvent& evt)
{
	if (m_is_mouse_down)
	{
		auto position = evt.GetPosition();
		if (m_splines.back().points.empty() || position != m_splines.back().points.back())
		{
			m_splines.back().points.push_back(position);
			Refresh();
		}
	}
}

void Whiteboard::on_mouse_down(wxMouseEvent& evt)
{
	m_is_mouse_down = true;
	m_splines.push_back({ m_pen_size->GetValue(), m_pen_colour->GetColour() });
	m_splines.back().points.reserve(64);
	evt.Skip();
}

void Whiteboard::on_mouse_up(wxMouseEvent& evt)
{
	m_is_mouse_down = false;
	evt.Skip();
}

void Whiteboard::on_key_down(wxKeyEvent& evt)
{
	if (!m_splines.empty() && evt.ControlDown() && evt.GetUnicodeKey() == 'Z')
	{
		m_splines.pop_back();
		Refresh();
	}
	if (!m_splines.empty() && evt.ControlDown() && evt.GetUnicodeKey() == 'C')
	{
		m_splines.clear();
		Refresh();
	}
	if (evt.ControlDown() && evt.GetUnicodeKey() == 'S')
	{
		wxFileDialog save_file_dialog(this, "Save PNG file", "", "", "PNG files (*.png)|*.png",
									  wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

		if (save_file_dialog.ShowModal() == wxID_CANCEL) return;

		wxBitmap bmp(GetSize());
		wxMemoryDC dc(bmp);
		wxGCDC gdc(dc);
		gdc.SetPen(wxPen(wxColour(0xffffff)));
		gdc.DrawRectangle(wxPoint(0, 0), GetSize());
		render(gdc, false);
		bmp.ConvertToImage().SaveFile(save_file_dialog.GetPath(), wxBITMAP_TYPE_PNG);
	}
	evt.Skip();
}

void Whiteboard::on_key_up(wxKeyEvent& evt)
{
}

void Whiteboard::render(wxGCDC& gdc, bool draw_grid)
{
	PrepareDC(gdc);

	// Draw Grid
	if (draw_grid)
	{
		gdc.SetPen(wxPen(wxColour(0xdedede), 1));
		auto size = GetSize();
		for (int i = -1; i < size.x; i += grid_size) { gdc.DrawLine(wxPoint(i, 0), wxPoint(i, size.y)); }
		for (int i = 0; i < size.y; i += grid_size) { gdc.DrawLine(wxPoint(0, i), wxPoint(size.x, i)); }
	}

	// Draw all Splines
	for (auto& spline : m_splines)
	{
		if (spline.points.size() > 2)
		{
			gdc.SetPen(wxPen(spline.colour, spline.size));
			gdc.DrawLines(spline.points.size(), spline.points.data());
		}
	}
}

BEGIN_EVENT_TABLE(Whiteboard, wxPanel)
EVT_PAINT(Whiteboard::on_paint)
EVT_MOTION(Whiteboard::on_mouse_moved)
EVT_LEFT_DOWN(Whiteboard::on_mouse_down)
EVT_LEFT_UP(Whiteboard::on_mouse_up)
EVT_KEY_DOWN(Whiteboard::on_key_down)
EVT_KEY_UP(Whiteboard::on_key_up)
END_EVENT_TABLE()