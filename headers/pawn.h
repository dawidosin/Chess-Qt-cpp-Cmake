#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn: public ChessPiece
{
public:
    Pawn(PieceColor _piececolor);
    Pawn(const Pawn& other);
    void setImage() override;
    std::vector<BoardPosition> getValidMoves(const ChessBoard& chessboard) const override;
    ChessPiece* clone() const override;
};

#endif // PAWN_H
