#include "MainWindow.h"
#include <vector>

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_SIZE(MainWindow::OnSizeChange)
    EVT_MENU(ID_PLAY, MainWindow::OnPlay)
    EVT_MENU(ID_PAUSE, MainWindow::OnPause)
    EVT_MENU(ID_NEXT, MainWindow::OnNext)
    EVT_MENU(ID_TRASH, MainWindow::OnClear)
    EVT_TIMER(ID_TIMER, MainWindow::OnTimer)
    EVT_KEY_DOWN(MainWindow::OnKeyDown)
wxEND_EVENT_TABLE()

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Main Window", wxPoint(0, 0), wxSize(600, 600)),
      gridSize(10) // Initialize gridSize, default value 10
{
    drawingPanel = new DrawingPanel(this, gameBoard); // Pass gameBoard by reference

    // Use box sizer for automatic resizing of the panel
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);
    this->SetSizer(sizer);

    InitializeGrid(); // Call grid initialization at the end of constructor
    statusBar = CreateStatusBar(); // Initialize status bar
    UpdateStatusBar(); // Set initial status bar text

    // Create and configure toolbar
    toolBar = CreateToolBar();
    wxBitmap playIcon(play_xpm);
    wxBitmap pauseIcon(pause_xpm);
    wxBitmap nextIcon(next_xpm);
    wxBitmap trashIcon(trash_xpm);
    toolBar->AddTool(ID_PLAY, "Play", playIcon);
    toolBar->AddTool(ID_PAUSE, "Pause", pauseIcon);
    toolBar->AddTool(ID_NEXT, "Next", nextIcon);
    toolBar->AddTool(ID_TRASH, "Clear", trashIcon);
    toolBar->Realize();

    timer = new wxTimer(this, ID_TIMER); // Initialize timer

    this->Layout(); // Ensure status bar and toolbar are visible
}

MainWindow::~MainWindow()
{
    if (drawingPanel)
        delete drawingPanel;
    if (timer)
        delete timer;
}

void MainWindow::OnPlay(wxCommandEvent&) {
    if (!isRunning && !isGameOver) {
        isRunning = true;
        timer->Start(timerInterval);
    }
}
void MainWindow::OnPause(wxCommandEvent&) {
    isRunning = false;
    timer->Stop();
}
void MainWindow::OnNext(wxCommandEvent&) {
    MoveSnake();
}
void MainWindow::OnClear(wxCommandEvent&) {
    timer->Stop();
    ResetGame();
}

void MainWindow::OnTimer(wxTimerEvent& event) {
    MoveSnake();
}

void MainWindow::OnKeyDown(wxKeyEvent& event) {
    switch (event.GetKeyCode()) {
        case WXK_UP: if (direction != Direction::DOWN) direction = Direction::UP; break;
        case WXK_DOWN: if (direction != Direction::UP) direction = Direction::DOWN; break;
        case WXK_LEFT: if (direction != Direction::RIGHT) direction = Direction::LEFT; break;
        case WXK_RIGHT: if (direction != Direction::LEFT) direction = Direction::RIGHT; break;
    }
}

void MainWindow::OnSizeChange(wxSizeEvent& event)
{
    if (drawingPanel)
    {
        drawingPanel->SetSize(event.GetSize());
        drawingPanel->Refresh();
    }
    event.Skip();
}

void MainWindow::InitializeGrid()
{
    gameBoard.resize(gridSize);
    for (auto& row : gameBoard)
        row.resize(gridSize);
    if (drawingPanel)
        drawingPanel->SetGridSize(gridSize);
}

void MainWindow::UpdateStatusBar()
{
    // Count living cells
    livingCells = 0;
    for (const auto& row : gameBoard)
        for (bool cell : row)
            if (cell) ++livingCells;
    wxString status = wxString::Format("Generation: %i | Living Cells: %i", generation, livingCells);
    if (statusBar)
        statusBar->SetStatusText(status);
}

void MainWindow::ResetGame() {
    isGameOver = false;
    isRunning = false;
    score = 0;
    generation = 0;
    direction = Direction::RIGHT;
    snake.clear();
    int mid = gridSize / 2;
    snake.push_back({mid, mid});
    SpawnFood();
    UpdateStatusBar();
    drawingPanel->Refresh();
}

void MainWindow::SpawnFood() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, gridSize - 1);
    while (true) {
        int x = dis(gen);
        int y = dis(gen);
        bool onSnake = false;
        for (auto& seg : snake) {
            if (seg.first == x && seg.second == y) {
                onSnake = true;
                break;
            }
        }
        if (!onSnake) {
            food = {x, y};
            break;
        }
    }
}

void MainWindow::MoveSnake() {
    if (isGameOver || !isRunning) return;
    auto head = snake.front();
    int dx = 0, dy = 0;
    switch (direction) {
        case Direction::UP: dy = -1; break;
        case Direction::DOWN: dy = 1; break;
        case Direction::LEFT: dx = -1; break;
        case Direction::RIGHT: dx = 1; break;
    }
    int newX = head.first + dx;
    int newY = head.second + dy;
    // Check wall collision
    if (newX < 0 || newX >= gridSize || newY < 0 || newY >= gridSize) {
        isGameOver = true;
        isRunning = false;
        UpdateStatusBar();
        drawingPanel->Refresh();
        return;
    }
    // Check self collision
    for (auto& seg : snake) {
        if (seg.first == newX && seg.second == newY) {
            isGameOver = true;
            isRunning = false;
            UpdateStatusBar();
            drawingPanel->Refresh();
            return;
        }
    }
    // Move snake
    snake.push_front({newX, newY});
    if (newX == food.first && newY == food.second) {
        score++;
        SpawnFood();
    } else {
        snake.pop_back();
    }
    generation++;
    UpdateStatusBar();
    drawingPanel->Refresh();
}
