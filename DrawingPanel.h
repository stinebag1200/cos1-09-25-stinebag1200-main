#pragma once
#include "wx/wx.h"
#include <vector>

class DrawingPanel : public wxPanel
{
public:
    DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoardRef);
    ~DrawingPanel();

    void SetGridSize(int size); // Setter method for grid size
    void OnMouseClick(wxMouseEvent& event);
    wxDECLARE_EVENT_TABLE();

private:
    int gridSize = 15;  // Default grid size 15x15
    std::vector<std::vector<bool>>& gameBoard; // Reference to game board

    void OnPaint(wxPaintEvent& event);
};
