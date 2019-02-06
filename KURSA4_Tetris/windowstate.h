#ifndef WINDOWSTATE_H
#define WINDOWSTATE_H


class TetrixWindow;
//Common State
class WindowState
{
public:
    virtual void windowAction(TetrixWindow *window) = 0;
    void    stateToMainMenu(TetrixWindow *window);
    void    stateToGame(TetrixWindow *window);
    void    stateToLeaderBoards(TetrixWindow *window);
    virtual ~WindowState() = 0;
};
//In Main Menu
class MainMenuState : public WindowState
{
    virtual void windowAction(TetrixWindow *window) override;
};
//While game
class InGameState : public WindowState
{
    virtual void windowAction(TetrixWindow *window) override;
};
//In Leader Boards
class ShowLeaderBoardsState : public WindowState
{
    virtual void windowAction(TetrixWindow *window) override;
};

#endif // WINDOWSTATE_H
