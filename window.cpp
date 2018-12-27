#include <QtWidgets>
#include "board.h"
#include "window.h"

TetrixWindow::TetrixWindow()
{
    QPixmap bkgnd("C://Users/gloomikon/Documents/KURSA4_Tetris/imgs/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //board = new TetrixBoard;
    //board = TetrixBoard::Instance();

    startButton = new QPushButton("Start");
    startButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton("Pause");
    pauseButton->setFocusPolicy(Qt::NoFocus);
    quitButton = new QPushButton("Quit");
    quitButton->setFocusPolicy(Qt::NoFocus);

    connect(startButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(start()));
    connect(pauseButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(pause()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(TetrixBoard::Instance(), 0, 1, 6, 2);
    layout->addWidget(pauseButton, 3, 3);
    layout->addWidget(quitButton, 4, 3);
    setLayout(layout);

    setWindowTitle("Tetris by KOLUMBIA");
    resize(1000, 1000);
}

TetrixWindow::~TetrixWindow()
{
    delete startButton;
    delete quitButton;
    //delete board;
}
