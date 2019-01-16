#include "horizontallinebomb.h"
#include "board.h"

horizontalLineBomb::horizontalLineBomb(): superPiece (TetrixShape(11))
{

}

void horizontalLineBomb::droppedAction()
{
    for (int i = 0; i < BoardWidth; i++)
        if (TetrixBoard::Instance()->shapeAt(i, TetrixBoard::Instance()->getCurY() - this->y(superPos)) != NoShape)
            TetrixBoard::Instance()->shapeAt(i, TetrixBoard::Instance()->getCurY() - this->y(superPos)) = Lava;
    TetrixBoard::Instance()->setAwaitingUpd();

}

TetrixPiece *horizontalLineBomb::returnCopyOfSelf()
{
    horizontalLineBomb* result = new horizontalLineBomb;
     result->setShape(pieceShape);
     result->superPos = this->superPos;
     for (int i = 0; i < 4; ++i)
     {
         result->setX(i, x(i));
         result->setY(i, y(i));
     }
     return result;

}
