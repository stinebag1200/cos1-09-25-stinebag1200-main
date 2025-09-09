#pragma once
#include "wx/wx.h"
#include "DrawingPanel.h"
#include <vector>
#include <deque>
#include <random>

// Include icon files
#include "play.xpm"
#include "pause.xpm"
#include "next.xpm"
#include "trash.xpm"

// Toolbar button IDs
constexpr int ID_PLAY = 10001;
constexpr int ID_PAUSE = 10002;
constexpr int ID_NEXT = 10003;
constexpr int ID_TRASH = 10004;
constexpr int ID_TIMER = 10005; // Unique timer ID

enum class Direction { UP, DOWN, LEFT, RIGHT };

class MainWindow : public wxFrame
{
private:
    DrawingPanel* drawingPanel = nullptr;
    std::vector<std::vector<bool>> gameBoard; // Game board state
    int gridSize = 15; // Default grid size
    void OnSizeChange(wxSizeEvent& event);
    void InitializeGrid(); // Grid initialization method

    wxStatusBar* statusBar = nullptr; // Status bar pointer
    int generation = 0; // Track current generation
    int livingCells = 0; // Track number of living cells
    void UpdateStatusBar(); // Update status bar text

    wxToolBar* toolBar = nullptr; // Toolbar pointer
    void OnPlay(wxCommandEvent& event);
    void OnPause(wxCommandEvent& event);
    void OnNext(wxCommandEvent& event);
    void OnClear(wxCommandEvent& event);

    wxTimer* timer = nullptr; // Timer for snake movement
    int timerInterval = 100; // Timer interval in ms
    std::deque<std::pair<int, int>> snake; // Snake body positions
    Direction direction = Direction::RIGHT; // Current direction
    std::pair<int, int> food; // Food position
    bool isRunning = false; // Game running state
    bool isGameOver = false; // Game over state
    int score = 0; // Score

    void OnTimer(wxTimerEvent& event); // Timer event handler
    void OnKeyDown(wxKeyEvent& event); // Keyboard event handler
    void SpawnFood(); // Place food on the board
    void MoveSnake(); // Move snake one step
    void ResetGame(); // Reset game state

public:
    MainWindow();
    ~MainWindow();
    wxDECLARE_EVENT_TABLE();
};
