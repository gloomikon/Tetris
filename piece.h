#ifndef TETRIXPIECE_H
#define TETRIXPIECE_H

enum TetrixShape
{
    NoShape, ZShape, SShape, IShape, TShape, SquareShape, LShape, JShape,  //0-7
    LineBomb //8-..
};

class TetrixPiece
{
protected:
    TetrixShape pieceShape;
    int coords[4][2];

public:
    TetrixPiece();
    virtual ~TetrixPiece();
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
};

#endif
