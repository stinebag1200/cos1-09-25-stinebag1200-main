#include "DrawingPanel.h"
#include <wx/dcclient.h>

wxBEGIN_EVENT_TABLE(DrawingPanel, wxPanel)
    EVT_PAINT(DrawingPanel::OnPaint)
    EVT_LEFT_UP(DrawingPanel::OnMouseClick)
wxEND_EVENT_TABLE()

DrawingPanel::DrawingPanel(wxWindow* parent, std::vector<std::vector<bool>>& gameBoardRef)
    : wxPanel(parent), gameBoard(gameBoardRef)
{
    // Event table handles events, no Bind() needed
}

DrawingPanel::~DrawingPanel() {}

void DrawingPanel::SetGridSize(int size)
{
    gridSize = size;
    Refresh(); // Redraw panel with new grid size
}

void DrawingPanel::OnMouseClick(wxMouseEvent& event)
{
    int cellWidth = GetSize().GetWidth() / gridSize;
    int cellHeight = GetSize().GetHeight() / gridSize;
    int col = event.GetX() / cellWidth;
    int row = event.GetY() / cellHeight;
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize)
    {
        gameBoard[row][col] = !gameBoard[row][col]; // Toggle cell state
        Refresh();
    }
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    wxPaintDC dc(this);
    int cellWidth = GetSize().GetWidth() / gridSize;
    int cellHeight = GetSize().GetHeight() / gridSize;
    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            if (gameBoard[row][col])
                dc.SetBrush(wxBrush(wxLIGHT_GREY)); // Alive
            else
                dc.SetBrush(wxBrush(wxWHITE)); // Dead
            dc.SetPen(*wxBLACK_PEN);
            dc.DrawRectangle(col * cellWidth, row * cellHeight, cellWidth, cellHeight);
        }
    }
}
