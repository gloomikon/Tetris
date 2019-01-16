#ifndef LINEBOMBPIECE_H
#define LINEBOMBPIECE_H

#include "superpiece.h"

class lineBombPiece : public superPiece
{
public:
    lineBombPiece();
    virtual void droppedAction() override;
        virtual TetrixPiece *returnCopyOfSelf() override;
};

#endif // LINEBOMBPIECE_H
