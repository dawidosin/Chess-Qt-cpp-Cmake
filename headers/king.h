#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King: public ChessPiece
{
public:
    King(PieceColor _piececolor);
    King(const King& other);
    void setImage() override;
    std::vector<BoardPosition> getValidMoves(const ChessBoard& chessboard) const override;
    std::vector<BoardPosition> getValidNormalMoves(const ChessBoard& chessboard) const override;
    std::vector<BoardPosition> getValidCaptureMoves(const ChessBoard& chessboard) const override;
    ChessPiece* clone() const override;
private:
    std::vector<BoardPosition> getMovesWithoutCastle(const ChessBoard& chessboard) const;
};

#endif // KING_H
