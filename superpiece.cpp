#include <QRandomGenerator>
#include "superpiece.h"
#include "board.h"

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
