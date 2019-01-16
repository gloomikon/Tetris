#ifndef HORIZONTALLINEBOMB_H
#define HORIZONTALLINEBOMB_H

#include "superpiece.h"

class horizontalLineBomb : public superPiece
{
public:
    horizontalLineBomb();
    virtual void droppedAction() override;
    virtual TetrixPiece *returnCopyOfSelf() override;
};

#endif // HORIZONTALLINEBOMB_H
