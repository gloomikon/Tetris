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

    startButton->setStyleSheet("QPushButton{ background-color: #950000;"
                               "width: 200px;"
                               "height: 60px;"
                               "line-height: 100px;"
                               "color: #fff;"
                               "position: absolute;"
                               "border: solid;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);}"
                               "QPushButton:hover { background-color: #f5c8ff;"
                               "width: 200px;"
                               "height: 60px;"
                               "line-height: 100px;"
                               "color: #000000;"
                               "position: absolute;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);}");
    pauseButton->setStyleSheet("QPushButton{ background-color: #950000;"
                               "width: 200px;"
                               "height: 60px;"
                               "line-height: 100px;"
                               "color: #fff;"
                               "position: absolute;"
                               "border: solid;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);}"
                               "QPushButton:hover { background-color: #f5c8ff;"
                               "width: 200px;"
                               "height: 60px;"
                               "line-height: 100px;"
                               "color: #000000;"
                               "position: absolute;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);}");
    quitButton->setStyleSheet("QPushButton{ background-color: #950000;"
                               "width: 200px;"
                               "height: 60px;"
                               "line-height: 100px;"
                               "color: #fff;"
                               "position: absolute;"
                               "border: solid;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);}"
                               "QPushButton:hover { background-color: #f5c8ff;"
                               "width: 200px;"
                               "height: 60px;"
                               "line-height: 100px;"
                               "color: #000000;"
                               "position: absolute;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);}");


    /*startButton->setStyleSheet("display: block;"
                               "background-color: #950000;"
                               "width: 300px;"
                               "height: 100px;"
                               "line-height: 100px;"
                               "margin: auto;"
                               "color: #fff;"
                               "position: absolute;"
                               "top: 0;"
                               "bottom: 0;"
                               "left: 0;"
                               "right: 0;"
                               "overflow: hidden;"
                               "border-radius: 5px;"
                               "box-shadow: 0 0 20px 0 rgba(0,0,0,.3);");*/

    connect(startButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(start()));
    connect(pauseButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(pause()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));

    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd = new QLCDNumber(5);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    connect(TetrixBoard::Instance(), &TetrixBoard::scoreChanged, scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(TetrixBoard::Instance(), &TetrixBoard::levelChanged, levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(TetrixBoard::Instance(), &TetrixBoard::linesRemovedChanged, linesLcd, QOverload<int>::of(&QLCDNumber::display));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(TetrixBoard::Instance(), 0, 1, 7, 2);
    layout->addWidget(pauseButton, 4, 3);
    layout->addWidget(quitButton, 5, 3);
    layout->addWidget(createLabel("SCORE"), 0, 3);
    layout->addWidget(scoreLcd, 1, 3);
    layout->addWidget(createLabel("LINES REMOVED"), 2, 3);
    layout->addWidget(linesLcd, 3, 3);
    layout->addWidget(createLabel("LEVEL"), 2, 0);
    layout->addWidget(levelLcd, 3, 0);
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

QLabel *TetrixWindow::createLabel(QString text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return label;
}
