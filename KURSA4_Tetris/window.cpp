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

    profiles = new Profile[10];
    table = new QTableWidget(10, 2, this);

    //Reading from files
    std::ifstream file;
    file.open("C://Users/gloomikon/Documents/KURSA4_Tetris/src/records.txt");
    int i = 0;
    while (!file.eof())
    {
        Profile profile;
        file >> profile.name >> profile.score;
        profiles[i] = profile;
        //qDebug() << profile.name.c_str() << profile.score << i;
        i++;
    }
    file.close();

    table->setHorizontalHeaderLabels(QString("Name,Score").split(','));
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    file.open("C://Users/gloomikon/Documents/KURSA4_Tetris/src/lastplayer.txt");
    file >> playerName;
    file.close();
    layout = new QGridLayout;
    name = new QLineEdit();
    startButton = new QPushButton("Start");
    pauseButton = new QPushButton("Pause");
    quitButton = new QPushButton("Quit");
    mainMenuButton = new QPushButton("Main Menu");
    scoreLcd = new QLCDNumber(5);
    levelLcd = new QLCDNumber(5);
    linesLcd = new QLCDNumber(5);
    //Labels
    nameLabel = createLabel("NAME:");
    levelLabel = createLabel("LEVEL");
    scoreLabel = createLabel("SCORE");
    linesRemovedLabel = createLabel("LINES\nREMOVED");
    leaderBoardsButton = new QPushButton("LeaderBoards");
    name->setStyleSheet("QLineEdit { height: 60px;"
                        "background-color: #db6653;"
                        "padding: 15px;}");

    //Buttons
    startButton->setFocusPolicy(Qt::NoFocus);
    pauseButton->setFocusPolicy(Qt::NoFocus);
    leaderBoardsButton->setFocusPolicy(Qt::NoFocus);
    quitButton->setFocusPolicy(Qt::NoFocus);
    mainMenuButton->setFocusPolicy(Qt::NoFocus);

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
    mainMenuButton->setStyleSheet("QPushButton{ background-color: #950000;"
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
    //LCDs
    scoreLcd->setSegmentStyle(QLCDNumber::Filled);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);
    linesLcd->setSegmentStyle(QLCDNumber::Filled);

    scoreLcd->setStyleSheet("QLCDNumber { background-color: rgba(165,0,0, 35%);}");
    levelLcd->setStyleSheet("QLCDNumber { background-color: rgba(165,0,0, 35%);}");
    linesLcd->setStyleSheet("QLCDNumber { background-color: rgba(165,0,0, 35%);}");

    connect(TetrixBoard::Instance(), &TetrixBoard::scoreChanged, scoreLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(TetrixBoard::Instance(), &TetrixBoard::levelChanged, levelLcd, QOverload<int>::of(&QLCDNumber::display));
    connect(TetrixBoard::Instance(), &TetrixBoard::linesRemovedChanged, linesLcd, QOverload<int>::of(&QLCDNumber::display));


    connect(startButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(start()));
    connect(pauseButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(pause()));
    connect(mainMenuButton, SIGNAL(clicked()), TetrixBoard::Instance(), SLOT(menu()));
    connect(leaderBoardsButton, SIGNAL(clicked()), this, SLOT(leaderboards()));
    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));



    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect(this);
    effect->setBlurRadius(0);
    effect->setColor(QColor("#EEEEEE"));
    effect->setOffset(1,1);

    nameLabel->setStyleSheet("QLabel{ color:black;"
                              "font-weight:bold;"
                              "font-size: 50px;"
                              "min-height: 50px;"
                              "max-height: 50px;}");
    nameLabel->setGraphicsEffect(effect);

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
    //State
    current = new MainMenuState;
    current->windowAction(this);


    setWindowTitle("Tetris by KOLUMBIA");
}

void TetrixWindow::leaderboards()
{
    updateUserName();
    this->current->stateToLeaderBoards(this);
    this->current->windowAction(this);
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

void TetrixWindow::sort()
{
    for (int i = 0; i < 10; i++)
    {
        int max = i;
        for(int j = i; j < 10; j++)
           if (profiles[j].score > profiles[max].score)
               max = j;
        Profile a = profiles[i];
        Profile b = profiles[max];
        profiles[i] = b;
        profiles[max] = a;
    }
}

void TetrixWindow::layoutClear()
{
    startButton->setVisible(false);
    layout->removeWidget(startButton);
    pauseButton->setVisible(false);
    layout->removeWidget(pauseButton);
    quitButton->setVisible(false);
    layout->removeWidget(quitButton);
    leaderBoardsButton->setVisible(false);
    layout->removeWidget(leaderBoardsButton);

    scoreLcd->setVisible(false);
    layout->removeWidget(scoreLcd);
    levelLcd->setVisible(false);
    layout->removeWidget(levelLcd);
    linesLcd->setVisible(false);
    layout->removeWidget(linesLcd);
    table->setVisible(false);
    layout->removeWidget(table);

    TetrixBoard::Instance()->setVisible(false);
    layout->removeWidget(TetrixBoard::Instance());
    mainMenuButton->setVisible(false);
    layout->removeWidget(mainMenuButton);
    linesRemovedLabel->setVisible(false);
    layout->removeWidget(linesRemovedLabel);
    scoreLabel->setVisible(false);
    layout->removeWidget(scoreLabel);
    levelLabel->setVisible(false);
    layout->removeWidget(levelLabel);
    nameLabel->setVisible(false);
    layout->removeWidget(nameLabel);
    name->setVisible(false);

}

void TetrixWindow::layoutToMainMenu()
{
    name->setText(playerName.c_str());

    startButton->setVisible(true);
    leaderBoardsButton->setVisible(true);
    name->setVisible(true);
    nameLabel->setVisible(true);
    quitButton->setVisible(true);

    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(name, 0, 1);
    layout->addWidget(startButton, 1, 0, 1, 2);
    layout->addWidget(leaderBoardsButton, 2, 0, 1 , 2);
    layout->addWidget(quitButton, 3, 0, 1 ,2);
    setLayout(layout);
    resize(650, 1000);
}

void TetrixWindow::layoutLeaderBoards()
{
    sort();
    for (int row = 0; row < 10; row++)
    {
        QTableWidgetItem *newItem = new QTableWidgetItem;
        newItem->setText(profiles[row].name.c_str());
        table->setItem(row,0, newItem);
        newItem = new QTableWidgetItem;
        newItem->setText(std::to_string(profiles[row].score).c_str());
        table->setItem(row,1, newItem);
    }
    table->setVisible(true);
    mainMenuButton->setVisible(true);
    layout->addWidget(table, 0,0, 5,1);
    layout->addWidget(mainMenuButton, 6, 0);
    resize(550,850);

    setLayout(layout);
}

void TetrixWindow::layoutInGame()
{
    TetrixBoard::Instance()->setFocus();
    levelLabel->setVisible(true);
    levelLcd->setVisible(true);
    startButton->setVisible(true);
    scoreLabel->setVisible(true);
    scoreLcd->setVisible(true);
    linesRemovedLabel->setVisible(true);
    linesLcd->setVisible(true);
    quitButton->setVisible(true);
    mainMenuButton->setVisible(true);
    pauseButton->setVisible(true);
    TetrixBoard::Instance()->setVisible(true);
    layout->addWidget(TetrixBoard::Instance(), 0, 1, 7, 2);
    //layout->addWidget(createLabel(tr("NEXT")), 0, 0);
    //layout->addWidget(nextPieceLabel, 1, 0);
    layout->addWidget(levelLabel, 2, 0);
    layout->addWidget(levelLcd, 3, 0);
    layout->addWidget(startButton, 4, 0);
    layout->addWidget(mainMenuButton, 5, 0);
    layout->addWidget(scoreLabel, 0, 3);
    layout->addWidget(scoreLcd, 1, 3);
    layout->addWidget(linesRemovedLabel, 2, 3);
    layout->addWidget(linesLcd, 3, 3);
    layout->addWidget(quitButton, 5, 3);
    layout->addWidget(pauseButton, 4, 3);
    setLayout(layout);
    resize(1000,1000);

}

void TetrixWindow::pasteScore(int score)
{
    for (int i = 0; i < 10; i++)
        if (profiles[i].score < score)
        {
            for (int k = 9; k > i; k--)
                 profiles[k] = profiles[k - 1];
            Profile profile;
            profile.name = playerName;
            profile.score = score;
            profiles[i] = profile;
            break;
        }
}

void TetrixWindow::updateUserName()
{
    playerName = name->text().toStdString();
}

void TetrixWindow::saveLog()
{
    std::ofstream file;
    file.open("C://Users/gloomikon/Documents/KURSA4_Tetris/src/records.txt");
    for (int i = 0; i < 10; i++)
    {
        file << profiles[i].name << " " << profiles[i].score;
        if (i < 9)
            file << "\n";
    }
    file.close();
    file.open("C://Users/gloomikon/Documents/KURSA4_Tetris/src/lastplayer.txt");
    file << playerName;
    file.close();
}

QLabel *TetrixWindow::createLabel(QString text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    return label;
}
