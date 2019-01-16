#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QTableWidget>
#include "board.h"
#include "windowstate.h"

struct Profile
{
    int score;
    std::string name;
};

class TetrixWindow : public QWidget
{
    Q_OBJECT
private slots:
    void leaderboards();
public:
    static TetrixWindow* Instance()
    {
        static TetrixWindow* instance = new TetrixWindow;
        return instance;
    }
    void    setCurrentState(WindowState *state);

    void    layoutClear();
    void    layoutToMainMenu();
    void    layoutLeaderBoards();
    void    layoutInGame();
    WindowState* getState() { return current; }

    //Profile* getProfiles() { return profiles; }
    void pasteScore(int score);
    void updateUserName();
    void saveLog();
private:
    TetrixWindow();
    ~TetrixWindow();
    void sort();
    WindowState *current;
    std::string playerName;
    //TetrixBoard *board;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *quitButton;
    QPushButton *mainMenuButton;
    QPushButton *leaderBoardsButton;

    QLCDNumber *scoreLcd;
    QLCDNumber *levelLcd;
    QLCDNumber *linesLcd;

    QLabel     *nextPieceLabel;
    QLabel     *linesRemovedLabel;
    QLabel     *scoreLabel;
    QLabel     *levelLabel;
    QLabel     *nameLabel;

    QLineEdit  *name;
    QTableWidget *table;

    QGridLayout *layout;

    QLabel* createLabel(QString text);
    Profile *profiles;
};

#endif
