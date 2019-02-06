#include "windowstate.h"
#include "window.h"

void WindowState::stateToMainMenu(TetrixWindow *window)
{
    window->setCurrentState(new MainMenuState);
    delete this;
}

void WindowState::stateToGame(TetrixWindow *window)
{
    window->setCurrentState(new InGameState);
    delete this;
}

void WindowState::stateToLeaderBoards(TetrixWindow *window)
{
    window->setCurrentState(new ShowLeaderBoardsState);
    delete this;
}

WindowState::~WindowState()
{

}

void MainMenuState::windowAction(TetrixWindow *window)
{
    window->layoutClear();
    window->layoutToMainMenu();
}

void InGameState::windowAction(TetrixWindow *window)
{
    window->layoutClear();
    window->layoutInGame();
}

void ShowLeaderBoardsState::windowAction(TetrixWindow *window)
{
    window->layoutClear();
    window->layoutLeaderBoards();
}
