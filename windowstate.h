#ifndef WINDOWSTATE_H
#define WINDOWSTATE_H


class TetrixWindow;

class WindowState
{
public:
    virtual void windowAction(TetrixWindow *window) = 0;
    virtual ~WindowState() = 0;
};

class MainMenuState : public WindowState
{
    virtual void windowAction(TetrixWindow *window) override;
};

class InGameState : public WindowState
{
    virtual void windowAction(TetrixWindow *window) override;
};

class ShowLeaderBoardsState : public WindowState
{
    virtual void windowAction(TetrixWindow *window) override;
};

#endif // WINDOWSTATE_H
