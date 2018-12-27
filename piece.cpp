#include <QRandomGenerator>
#include <stdlib.h>
#include "piece.h"
#include "board.h"
#include <QPainter>

TetrixPiece::TetrixPiece()
{
    setShape(NoShape);
}


void TetrixPiece::setRandomShape()
{
    setShape(TetrixShape(QRandomGenerator::global()->bounded(7) + 1));
}
void TetrixPiece::setShape(TetrixShape shape)
{
    const int coordsTable[8][4][2] = {
        { { 0, 0 },   { 0, 0 },   { 0, 0 },   { 0, 0 } },
        { { 0, -1 },  { 0, 0 },   { -1, 0 },  { -1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 1, 0 },   { 1, 1 } },
        { { 0, -1 },  { 0, 0 },   { 0, 1 },   { 0, 2 } },
        { { -1, 0 },  { 0, 0 },   { 1, 0 },   { 0, 1 } },
        { { 0, 0 },   { 1, 0 },   { 0, 1 },   { 1, 1 } },
        { { -1, -1 }, { 0, -1 },  { 0, 0 },   { 0, 1 } },
        { { 1, -1 },  { 0, -1 },  { 0, 0 },   { 0, 1 } }
    };

    for (int i = 0; i < 4 ; i++) {
        for (int j = 0; j < 2; ++j)
            coords[i][j] = coordsTable[shape][i][j];
    }
    pieceShape = shape;
}

TetrixShape TetrixPiece::shape()
{
    return pieceShape;
}

int TetrixPiece::x(int index) const
{
    return coords[index][0];
}

int TetrixPiece::y(int index) const
{
    return coords[index][1];
}

void TetrixPiece::setX(int index, int x)
{
    coords[index][0] = x;
}

void TetrixPiece::setY(int index, int y)
{
    coords[index][1] = y;
}

int TetrixPiece::minX()
{
    int min = coords[0][0];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coords[i][0]);
    return min;
}

int TetrixPiece::maxX()
{
    int max = coords[0][0];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, coords[i][0]);
    return max;
}

int TetrixPiece::minY()
{
    int min = coords[0][1];
    for (int i = 1; i < 4; ++i)
        min = qMin(min, coords[i][1]);
    return min;
}

int TetrixPiece::maxY()
{
    int max = coords[0][1];
    for (int i = 1; i < 4; ++i)
        max = qMax(max, coords[i][1]);
    return max;
}

TetrixPiece* TetrixPiece::rotatedLeft()
{
    TetrixPiece* result = returnCopyOfSelf();
    result->pieceShape = this->pieceShape;
    for (int i = 0; i < 4; ++i) {
        result->setX(i, y(i));
        result->setY(i, -x(i));
    }
    return result;
}

TetrixPiece* TetrixPiece::rotatedRight()
{
    TetrixPiece* result = returnCopyOfSelf();
    result->pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        result->setX(i, -y(i));
        result->setY(i, x(i));
    }
    return result;
}

void TetrixPiece::updateBoard()
{
    for (int i = 0; i < 4; ++i)
    {
        int x = TetrixBoard::Instance()->getCurX() + this->x(i);
        int y = TetrixBoard::Instance()->getCurY() - this->y(i);
        TetrixBoard::Instance()->shapeAt(x, y) = this->shape();
    }
}

TetrixPiece *TetrixPiece::returnCopyOfSelf()
{
    TetrixPiece* result = new TetrixPiece;
    result->pieceShape = pieceShape;
    for (int i = 0; i < 4; ++i) {
        result->setX(i, x(i));
        result->setY(i, y(i));
    }
    return result;
}

void TetrixPiece::draw(QWidget *w)
{
    QPainter painter(w);
    QRect rect = TetrixBoard::Instance()->contentsRect();
    int boardTop = rect.top();
    for (int i = 0; i < 4; ++i)
    {
        int x = TetrixBoard::Instance()->getCurX() + this->x(i);
        int y = TetrixBoard::Instance()->getCurY() - this->y(i);
        TetrixBoard::Instance()->drawSquare(painter, rect.left() + x * TetrixBoard::Instance()->squareWidth(), boardTop + (BoardHeight - y - 1) * TetrixBoard::Instance()->squareHeight(), this->shape());
    }
}
