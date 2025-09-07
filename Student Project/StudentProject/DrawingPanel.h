#pragma once
#include "wx/wx.h"

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent);
    ~DrawingPanel();

private:
    int gridSize = 15;  // Default grid size 15x15

    void OnPaint(wxPaintEvent& event);
};
