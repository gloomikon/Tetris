#ifndef TETRIXWINDOW_H
#define TETRIXWINDOW_H

#include <QFrame>
#include <QWidget>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include "board.h"

class TetrixWindow : public QWidget
{
    Q_OBJECT

public:
    TetrixWindow();
    ~TetrixWindow();
private:
    TetrixBoard *board;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QPushButton *quitButton;
};

#endif
