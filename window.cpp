#include <QtWidgets>
#include "board.h"
#include "window.h"
#include <fstream>

TetrixWindow::TetrixWindow()
{
    //Background
    QPixmap bkgnd("C://Users/gloomikon/Documents/KURSA4_Tetris/imgs/background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    //Reading from files
    std::ifstream file;
    file.open("C://Users/gloomikon/Documents/KURSA4_Tetris/src/lastplayer.txt");
    std::string playerName;
    file >> playerName;
    name = new QLineEdit();
    name->setText(playerName.c_str());
    name->setStyleSheet("QLineEdit { height: 60px;"
                        "background-color: #db6653;"
                        "padding: 15px;}");

    //Buttons
    startButton = new QPushButton("Start");
    startButton->setFocusPolicy(Qt::NoFocus);
    pauseButton = new QPushButton("Pause");
    pauseButton->setFocusPolicy(Qt::NoFocus);
    leaderBoardsButton = new QPushButton("LeaderBoards");
    leaderBoardsButton->setFocusPolicy(Qt::NoFocus);
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
    leaderBoardsButton->setStyleSheet("QPushButton{ background-color: #950000;"
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

    connect(startButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(start()));
    connect(pauseButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(pause()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));

    //LCDs
    scoreLcd = new QLCDNumber(5);
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd = new QLCDNumber(5);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd = new QLCDNumber(5);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    scoreLcd->setStyleSheet("QLCDNumber { background-color: rgba(165,0,0, 35%);}");
    levelLcd->setStyleSheet("QLCDNumber { background-color: rgba(165,0,0, 35%);}");
    linesLcd->setStyleSheet("QLCDNumber { background-color: rgba(165,0,0, 35%);}");

    connect(TetrixBoard::Instance(), &TetrixBoard::scoreChanged, scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(TetrixBoard::Instance(), &TetrixBoard::levelChanged, levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(TetrixBoard::Instance(), &TetrixBoard::linesRemovedChanged, linesLcd, QOverload<int>::of(&QLCDNumber::display));

    //Labels
    levelLabel = createLabel("LEVEL");
    scoreLabel = createLabel("SCORE");
    nameLabel = createLabel("Name:");
    linesRemovedLabel = createLabel("LINES\nREMOVED");

    levelLabel->setFocusPolicy(Qt::NoFocus);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(0);
    effect->setColor(QColor("#EEEEEE"));
    effect->setOffset(1,1);

    levelLabel->setStyleSheet("QLabel{ color:black;"
                              "font-weight:bold;"
                              "font-size: 50px;"
                              "min-height: 50px;"
                              "max-height: 50px;}");
    levelLabel->setGraphicsEffect(effect);
    scoreLabel->setStyleSheet("QLabel{ color:black;"
                              "font-weight:bold;"
                              "font-size: 50px;"
                              "min-height: 50px;"
                              "max-height: 50px;}");
    scoreLabel->setGraphicsEffect(effect);
    linesRemovedLabel->setStyleSheet("QLabel{ color:black;"
                              "font-weight:bold;"
                              "font-size: 50px;}");
    linesRemovedLabel->setGraphicsEffect(effect);
    nameLabel->setStyleSheet("QLabel{ color:black;"
                              "font-weight:bold;"
                              "font-size: 50px;"
                              "min-height: 50px;"
                              "max-height: 50px;}");
    nameLabel->setGraphicsEffect(effect);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(name, 0, 1);
    layout->addWidget(startButton, 1, 0, 1, 2);
    //layout->addWidget(TetrixBoard::Instance(), 0, 1, 7, 2);
    //layout->addWidget(pauseButton, 4, 3);
    layout->addWidget(leaderBoardsButton, 2, 0, 1 , 2);
    layout->addWidget(quitButton, 3, 0, 1 ,2);
    //layout->addWidget(scoreLabel, 0, 3);
    //layout->addWidget(scoreLcd, 1, 3);
    //layout->addWidget(linesRemovedLabel, 2, 3);
    //layout->addWidget(linesLcd, 3, 3);
    //layout->addWidget(levelLabel, 2, 0);
    //layout->addWidget(levelLcd, 3, 0);
    setLayout(layout);

    //layout->removeWidget(scoreLabel);
    //layout->takeAt(layout->indexOf(scoreLabel));
    setLayout(layout);

    setWindowTitle("Tetris by KOLUMBIA");
    resize(650, 1000);
}

void TetrixWindow::setCurrentState(WindowState *state)
{
    this->current = state;
}

TetrixWindow::~TetrixWindow()
{
    delete startButton;
    delete quitButton;
}

QLabel *TetrixWindow::createLabel(QString text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    return label;
}
