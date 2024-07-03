#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen: public ChessPiece
{
public:
    Queen(PieceColor _piececolor);
    Queen(const Queen& other);
    void setImage() override;
    std::vector<BoardPosition> getValidMoves(const ChessBoard& chessboard) const override;
    ChessPiece* clone() const override;
};

#endif // QUEEN_H
