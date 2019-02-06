#include "linebombpiece.h"
#include "board.h"

lineBombPiece::lineBombPiece() : superPiece (TetrixShape(10))
{
}

void lineBombPiece::droppedAction()
{
    for (int i = 0; i < BoardHeight; i++)
        if (TetrixBoard::Instance()->shapeAt(TetrixBoard::Instance()->getCurX() + this->x(superPos), i) != NoShape)
            TetrixBoard::Instance()->shapeAt(TetrixBoard::Instance()->getCurX() + this->x(superPos), i) = Lava;
    TetrixBoard::Instance()->setAwaitingUpd();

}

TetrixPiece *lineBombPiece::returnCopyOfSelf()
{
    lineBombPiece* result = new lineBombPiece;
     result->setShape(pieceShape);
     result->superPos = this->superPos;
     for (int i = 0; i < 4; ++i)
     {
         result->setX(i, x(i));
         result->setY(i, y(i));
     }
     return result;
}
