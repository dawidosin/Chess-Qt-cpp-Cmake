#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King: public ChessPiece
{
public:
    King(PieceColor _piececolor);
    King(const King& other);
    void setImage() override;
    ChessPiece* clone() const override;
};

#endif // KING_H
