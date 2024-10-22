#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight: public ChessPiece
{
public:
    Knight(PieceColor _piececolor);
    Knight(const Knight& other);
    void setImage() override;
    ChessPiece* clone() const override;
};

#endif // KNIGHT_H
