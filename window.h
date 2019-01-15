#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include "board.h"
#include "windowstate.h"

class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
    TetrixWindow();
    void    setCurrentState(WindowState *state);
    ~TetrixWindow();
private:
    WindowState *current;
    //TetrixBoard *board;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *quitButton;
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

    QLabel* createLabel(QString text);
};

#endif
