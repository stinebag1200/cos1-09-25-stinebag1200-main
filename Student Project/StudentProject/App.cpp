#include "App.h"
#include "MainWindow.h"

wxIMPLEMENT_APP(App);

App::App() {}
App::~App() {}

bool App::OnInit()
{
    // Create and show the main window
    mainWindow = new MainWindow();
    mainWindow->Show();
    return true;
}
