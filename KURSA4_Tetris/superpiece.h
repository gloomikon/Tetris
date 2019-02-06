#ifndef SUPERPIECE_H
#define SUPERPIECE_H

#include "piece.h"

class superPiece : public TetrixPiece
{
protected:
    int superPos;
    TetrixShape superType;
public:
    superPiece(TetrixShape superType);
    virtual void updateBoard() override;
    virtual TetrixPiece* returnCopyOfSelf() override;
    virtual void draw(QWidget *w) override;
};

#endif // SUPERPIECE_H
