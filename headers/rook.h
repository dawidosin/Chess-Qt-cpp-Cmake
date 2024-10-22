#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook: public ChessPiece
{
public:
    Rook(PieceColor _piececolor);
    Rook(const Rook& other);
    void setImage() override;
    ChessPiece* clone() const override;
};

#endif // ROOK_H
