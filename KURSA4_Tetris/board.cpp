#include <QtWidgets>
#include <QDebug>

#include "board.h"
#include "linebombpiece.h"
#include "horizontallinebomb.h"
#include "squarebombpiece.h"
#include "window.h"

TetrixBoard::TetrixBoard(QWidget *parent) : QFrame(parent)
{
    setStyleSheet("border-image: url(C://Users/gloomikon/Documents/KURSA4_Tetris/imgs/board.jpg) 0 0 0 0 stretch stretch;");
    board = new TetrixShape[BoardWidth * BoardHeight];
    setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    isStarted = false;
    isPaused = false;
    clearBoard();
    curPiece = new TetrixPiece;
    curPiece->setRandomShape();
    nextPiece = new TetrixPiece;
    nextPiece->setRandomShape();
}

void TetrixBoard::start()
{
    TetrixWindow::Instance()->getState()->stateToGame(TetrixWindow::Instance());
    TetrixWindow::Instance()->getState()->windowAction(TetrixWindow::Instance());
    TetrixWindow::Instance()->updateUserName();
    if (isPaused)
        return;
    isStarted = true;
    isWaitingAfterLine = false;
    numLinesRemoved = 0;
    numPiecesDropped = 0;
    score = 0;
    level = 1;
    clearBoard();

    emit linesRemovedChanged(numLinesRemoved);
    emit scoreChanged(score);
    emit levelChanged(level);

    newPiece();
    timer.start(timeoutTime(), this);
}

void TetrixBoard::pause()
{
    if (!isStarted)
        return;
    isPaused = !isPaused;
    if (isPaused)
    {
        timer.stop();
    }
    else
    {
        timer.start(timeoutTime(), this);
    }
    update();
}

void TetrixBoard::menu()
{
    TetrixWindow::Instance()->getState()->stateToMainMenu(TetrixWindow::Instance());
    TetrixWindow::Instance()->getState()->windowAction(TetrixWindow::Instance());
    timer.stop();
}

void TetrixBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QRect rect = contentsRect();
    if (isPaused)
    {
        painter.drawText(rect, Qt::AlignCenter, "Pause");
        return;
    }
    int boardTop = rect.top();
    for (int i = 0; i < BoardHeight; i++)
    {
        for (int j = 0; j < BoardWidth; j++)
        {
            TetrixShape shape = shapeAt(j, BoardHeight - i - 1);
                drawSquare(painter, rect.left() + j * squareWidth(),
                           boardTop + i * squareHeight(), shape);
        }
    }
    if (curPiece->shape() != NoShape)
        curPiece->draw(this);
}

void TetrixBoard::keyPressEvent(QKeyEvent *event)
{
    if (!isStarted || isPaused || curPiece->shape() == NoShape)
    {
        return;
    }
    switch (event->key()) {
    case Qt::Key_A:
        tryMove(curPiece, curX - 1, curY);
        break;
    case Qt::Key_D:
        tryMove(curPiece, curX + 1, curY);
        break;
    case Qt::Key_S:
        tryMove(curPiece->rotatedRight(), curX, curY);
        break;
    case Qt::Key_W:
        tryMove(curPiece->rotatedLeft(), curX, curY);
        break;
    case Qt::Key_Shift:
        dropDown();
        break;
    case Qt::Key_Space:
        oneLineDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void TetrixBoard::timerEvent(QTimerEvent *)
{
    if (isWaitingAfterLine)
    {
        int line;
        if ((line = checkLava()) >= 0)
        {
            for (int j = 0; j < BoardWidth; j++)
                if (shapeAt(j, line) == Lava)
                {
                    for (int k = line; k < BoardHeight - 1; k++)
                    {
                        shapeAt(j, k) = shapeAt(j, k + 1);
                    }
                    shapeAt(j, BoardHeight - 1) = NoShape;
                }
            update();
        }
        else
        {
            isWaitingAfterLine = false;
            newPiece();
            timer.start(timeoutTime(), this);
        }
    }
    else
    {
        oneLineDown();
    }

}

void TetrixBoard::clearBoard()
{
    for (int i = 0; i < BoardHeight * BoardWidth; ++i)
        board[i] = NoShape;
}

void TetrixBoard::dropDown()
{
    int dropHeight = 0;
    int newY = curY;
    while (newY > 0)
    {
        if (!tryMove(curPiece, curX, newY - 1))
            break;
        --newY;
        ++dropHeight;
    }
    pieceDropped(dropHeight);
}

void TetrixBoard::oneLineDown()
{
    if (!tryMove(curPiece, curX, curY - 1))
        pieceDropped(0);
}

void TetrixBoard::pieceDropped(int dropHeight)
{
    curPiece->updateBoard();
    curPiece->droppedAction();
    ++numPiecesDropped;
    if (numPiecesDropped % 25 == 0)
    {
        ++level;
        timer.start(timeoutTime(), this);
        emit levelChanged(level);
    }

    score += dropHeight + 7;
        emit scoreChanged(score);

    removeFullLines();

    if (!isWaitingAfterLine)
        newPiece();
    update();
}

void TetrixBoard::removeFullLines()
{
    int numFullLines = 0;

    for (int i = BoardHeight - 1; i >= 0; --i)
    {
        bool lineIsFull = true;

        for (int j = 0; j < BoardWidth; ++j)
        {
            if (shapeAt(j, i) == NoShape)
            {
                lineIsFull = false;
                break;
            }
        }
        if (lineIsFull)
        {
            ++numFullLines;
            for (int j = 0; j < BoardWidth; ++j)
                if (shapeAt(j, i) == SquareBomb) //тута взрываем бомбму-кругляшёк
                {
                    if (j > 0)
                    {
                        if (i > 0)
                        {
                            qDebug() << "j > 0 i > 0";
                            shapeAt(j - 1, i - 1) = Lava;
                            shapeAt(j - 1, i) = Lava;
                            shapeAt(j - 1, i + 1) = Lava;
                            shapeAt(j, i - 1) = Lava;
                            shapeAt(j, i) = Lava;
                            shapeAt(j, i + 1) = Lava;
                            if (j < BoardWidth - 1)
                            {
                                shapeAt(j + 1, i - 1) = Lava;
                                shapeAt(j + 1, i) = Lava;
                                shapeAt(j + 1, i + 1) = Lava;
                            }
                        }
                        if (i == 0)
                        {
                            shapeAt(j - 1, i) = Lava;
                            shapeAt(j - 1, i + 1) = Lava;
                            shapeAt(j, i) = Lava;
                            shapeAt(j, i + 1) = Lava;
                            if (j < BoardWidth - 1)
                            {
                                shapeAt(j + 1, i) = Lava;
                                shapeAt(j + 1, i + 1) = Lava;
                            }
                        }
                    }
                    if (j == 0)
                    {
                        if (i > 0)
                        {
                            shapeAt(j + 1, i - 1) = Lava;
                            shapeAt(j + 1, i) = Lava;
                            shapeAt(j + 1, i + 1) = Lava;
                            shapeAt(j, i - 1) = Lava;
                            shapeAt(j, i) = Lava;
                            shapeAt(j, i + 1) = Lava;
                        }
                        if (i == 0)
                        {
                            shapeAt(j + 1, i) = Lava;
                            shapeAt(j + 1, i + 1) = Lava;
                            shapeAt(j, i) = Lava;
                            shapeAt(j, i + 1) = Lava;
                        }
                    }
                }
            for (int j = 0; j < BoardWidth; ++j)
                shapeAt(j, i) = Lava;
//            for (int k = i; k < BoardHeight - 1; ++k)
//            {
//                for (int j = 0; j < BoardWidth; ++j)
//                    shapeAt(j, k) = shapeAt(j, k + 1);
//            }
//            for (int j = 0; j < BoardWidth; ++j)
//                shapeAt(j, BoardHeight - 1) = NoShape;
        }
    }
    if (numFullLines > 0)
    {
        numLinesRemoved += numFullLines;
        score += 10 * numFullLines;
        emit linesRemovedChanged(numLinesRemoved);
        emit scoreChanged(score);

        timer.start(500, this);
        isWaitingAfterLine = true;
        curPiece->setShape(NoShape);
        update();
    }
}

void TetrixBoard::newPiece()
{
    curPiece = nextPiece;
    if (numPiecesDropped % 5 == 0)
        nextPiece = TetrixPiece::GeneratePiece(QRandomGenerator::global()->bounded(3) + 1);
    else
        nextPiece = new TetrixPiece;
    nextPiece->setRandomShape();
    //showNextPiece();
    curX = BoardWidth / 2 + 1;
    curY = BoardHeight - 1 + curPiece->minY();

    if (!tryMove(curPiece, curX, curY))
    {
        curPiece->setShape(NoShape);
        timer.stop();
        isStarted = false;
        TetrixWindow::Instance()->pasteScore(score);
    }
}
/*void TetrixBoard::showNextPiece()
{
    if (!nextPieceLabel)
        return;
    int dx = nextPiece->maxX() - nextPiece->minX() + 1;
    int dy = nextPiece->maxY() - nextPiece->minY() + 1;

    QPixmap pixmap(dx * squareWidth(), dy * squareHeight());
    QPainter painter(&pixmap);
    painter.fillRect(pixmap.rect(), nextPieceLabel->palette().background());

    for (int i = 0; i < 4; ++i)
    {
        int x = nextPiece->x(i) - nextPiece->minX();
        int y = nextPiece->y(i) - nextPiece->minY();
        drawSquare(painter, x * squareWidth(), y * squareHeight(), nextPiece->shape());
    }
    nextPieceLabel->setPixmap(pixmap);
}*/

bool TetrixBoard::tryMove(TetrixPiece *newPiece, int newX, int newY)
{
    for (int i = 0; i < 4; ++i)
    {
        int x = newX + newPiece->x(i);
        int y = newY - newPiece->y(i);
        if (x < 0 || x >= BoardWidth || y < 0 || y >= BoardHeight)
            return false;
        if (shapeAt(x, y) != NoShape)
            return false;
    }
    curPiece = newPiece;
    curX = newX;
    curY = newY;
    update();
    return true;
}

TetrixShape *TetrixBoard::getBoard()
{
    return this->board;
}

int TetrixBoard::checkLava()
{
    for (int i = 0; i < BoardHeight; i++)
        for (int j = 0; j < BoardWidth; j++)
            if (shapeAt(j, i) == Lava)
                return i;
    return -1;
}

void TetrixBoard::drawSquare(QPainter &painter, int x, int y, TetrixShape shape)
{
    static const std::string pixmapTable[11] = {
        "red.png", "green.png", "sky.png", "purple.png", "yellow.png", "orange.png", "blue.png",
        "lava.png", "bomb.png", "updown.png", "leftright.png"
    };
//    static const QRgb colorTable[9] = {
//        0xCC6666, 0x66CC66, 0x6666CC,
//        0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00,
//        0x000000
//    };
    painter.setPen(Qt::black);
    if (shape != NoShape)
    {
        std::string path = "C://Users/gloomikon/Documents/KURSA4_Tetris/imgs/" + pixmapTable[int(shape) - 1];
        //QColor color = colorTable[int(shape) - 1];
        QPixmap pixmap(path.c_str());
        QRect rect;
        rect.setCoords(x + 1, y + 1, x + 1 + squareWidth() - 2, y + 1 + squareHeight() - 2);
        painter.drawPixmap(rect, pixmap);
        //painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2, pixmap);
        //qDebug() << x+1 << y+1 << squareWidth() - 2<< squareHeight() - 2 << color ;
    }
    else
    {
        painter.drawRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2);
    }

}
