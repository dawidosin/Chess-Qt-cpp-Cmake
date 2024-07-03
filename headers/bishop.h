#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop: public ChessPiece
{
public:
    Bishop(PieceColor _piececolor);
    Bishop(const Bishop& other);
    void setImage() override;
    std::vector<BoardPosition> getValidMoves(const ChessBoard& chessboard) const override;
    ChessPiece* clone() const override;
};

#endif // BISHOP_H
