#include "DrawingPanel.h"
#include "wx/graphics.h"
#include "wx/dcbuffer.h"

DrawingPanel::DrawingPanel(wxWindow* parent)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(600, 600))
{
    // Allow custom painting on this panel
    this->SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind paint event to our custom drawing handler
    this->Bind(wxEVT_PAINT, &DrawingPanel::OnPaint, this);
}

DrawingPanel::~DrawingPanel()
{
    // Empty destructor for now
}

void DrawingPanel::OnPaint(wxPaintEvent& event)
{
    // Use buffered paint DC to prevent flickering
    wxAutoBufferedPaintDC dc(this);
    dc.Clear();

    // Create graphics context for smooth drawing
    wxGraphicsContext* context = wxGraphicsContext::Create(dc);
    if (!context)
        return;

    // Set pen and brush colors
    context->SetPen(*wxBLACK);
    context->SetBrush(*wxWHITE);

    // Get panel size dynamically
    wxSize panelSize = this->GetSize();
    int panelWidth = panelSize.GetWidth();
    int panelHeight = panelSize.GetHeight();

    // Calculate cell width and height dynamically
    double cellWidth = static_cast<double>(panelWidth) / gridSize;
    double cellHeight = static_cast<double>(panelHeight) / gridSize;

    // Draw 15x15 grid
    for (int row = 0; row < gridSize; ++row)
    {
        for (int col = 0; col < gridSize; ++col)
        {
            double x = col * cellWidth;
            double y = row * cellHeight;

            context->DrawRectangle(x, y, cellWidth, cellHeight);
        }
    }

    // Clean up graphics context
    delete context;
}
