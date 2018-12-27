#include <QRandomGenerator>
#include "superpiece.h"
#include "board.h"
#include <QPainter>

superPiece::superPiece(TetrixShape superType) : TetrixPiece (), superType{superType}
{
    superPos = QRandomGenerator::global()->bounded(4);
}

void superPiece::updateBoard()
{
    TetrixPiece::updateBoard();
    int x = TetrixBoard::Instance()->getCurX() + this->x(superPos);
    int y = TetrixBoard::Instance()->getCurY() - this->y(superPos);
    TetrixBoard::Instance()->shapeAt(x,y) = this->superType;
}

TetrixPiece *superPiece::returnCopyOfSelf()
{
    superPiece* result = new superPiece(this->superType);
    result->setShape(pieceShape);
    result->superPos = this->superPos;
    for (int i = 0; i < 4; ++i)
    {
        result->setX(i, x(i));
        result->setY(i, y(i));
    }
    return result;
}

void superPiece::draw(QWidget *w)
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
    int x = TetrixBoard::Instance()->getCurX() + this->x(superPos);
    int y = TetrixBoard::Instance()->getCurY() - this->y(superPos);
    TetrixBoard::Instance()->drawSquare(painter, rect.left() + x * TetrixBoard::Instance()->squareWidth(), boardTop + (BoardHeight - y - 1) * TetrixBoard::Instance()->squareHeight(), superType);
}
