#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H

#include "drawable.h"

enum TetrixShape
{
    NoShape, ZShape, SShape, IShape, TShape, SquareShape, LShape, JShape,  //0-7
    SquareBomb //8-..
};

class TetrixPiece : public Drawable
{
protected:
    TetrixShape pieceShape;
    int coords[4][2];

public:
    TetrixPiece();
    void setRandomShape();
    void setShape(TetrixShape shape);
    TetrixShape shape();
    int x(int index) const;
    int y(int index) const;
    void setX(int index, int x);
    void setY(int index, int y);
    int minX();
    int maxX();
    int minY();
    int maxY();
    void setPieceShape(TetrixShape shape) { this->pieceShape = shape; }
    TetrixPiece* rotatedLeft();
    TetrixPiece* rotatedRight();
    virtual void updateBoard();
    virtual TetrixPiece* returnCopyOfSelf();
    virtual void draw(QWidget *w) override;
};

#endif
