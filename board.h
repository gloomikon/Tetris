#ifndef TETRIXBOARD_H
#define TETRIXBOARD_H
#define BoardWidth 12
#define BoardHeight 20
#include <QBasicTimer>
#include <QFrame>
#include <QPointer>
#include <QLabel>

#include "piece.h"

class TetrixBoard : public QFrame
{
    Q_OBJECT
public:
    static TetrixBoard* Instance()
    {
        static TetrixBoard* instance = new TetrixBoard;
        return instance;
    }
    int getCurX() { return curX; }
    int getCurY() { return curY; }
    TetrixShape &shapeAt(int x, int y)
    {
        return board[(y * BoardWidth) + x];
    }
    int squareWidth() { return contentsRect().width() / BoardWidth; }
    int squareHeight() { return contentsRect().height() / BoardHeight; }
    void drawSquare(QPainter &painter, int x, int y, TetrixShape shape);

public slots:
    void start();
    void pause();
    void menu();

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;

private:
    TetrixBoard(QWidget *parent = nullptr);
    TetrixBoard(TetrixBoard const&) = delete;
    TetrixBoard& operator=(TetrixBoard const&) = delete;
    QBasicTimer timer;
    QPointer<QLabel> nextPieceLabel;
    bool isStarted;
    bool isPaused;
    bool isWaitingAfterLine;
    TetrixPiece *curPiece;
    TetrixPiece *nextPiece;
    int curX;
    int curY;
    int numLinesRemoved = 0;
    int numPiecesDropped = 0;
    int score;
    int level;
    TetrixShape* board;

    int timeoutTime() { return 1000 / (1 + level); }
    void clearBoard();
    void dropDown();
    void oneLineDown();
    void pieceDropped(int dropHeight);
    void removeFullLines();
    void newPiece();
    void showNextPiece();
    bool tryMove(TetrixPiece* newPiece, int newX, int newY);
    TetrixShape*    getBoard();
    int checkLava();

};

#endif
