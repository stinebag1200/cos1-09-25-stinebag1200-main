#include "MainWindow.h"

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Main Window", wxPoint(0, 0), wxSize(600, 600))
{
    // Create the drawing panel
    drawingPanel = new DrawingPanel(this);

    // Use box sizer for automatic resizing of the panel
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(sizer);

    // Bind window resize event
    this->Bind(wxEVT_SIZE, &MainWindow::OnSizeChange, this);
}

MainWindow::~MainWindow()
{
    if (drawingPanel)
        delete drawingPanel;
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    // Adjust panel size dynamically on window resize
    drawingPanel->SetSize(event.GetSize());
    drawingPanel->Refresh();
    event.Skip();
}
