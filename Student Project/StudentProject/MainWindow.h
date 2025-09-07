#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"

class MainWindow : public wxFrame
{
private:
    DrawingPanel* drawingPanel = nullptr;

    // Handle window resizing
    void OnSizeChange(wxSizeEvent& event);

public:
    MainWindow();
    ~MainWindow();
};
