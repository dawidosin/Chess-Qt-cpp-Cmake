#ifndef CHESSBOARDCOPY_H
#define CHESSBOARDCOPY_H
#include "chessboard.h"

/*
    Holds necessary data for Checking potential danger
    for our King after move.
    Doesn't have scene for displaying
    also overrides some necessary virtual functions
*/
struct ChessBoardCopy : public ChessBoard
{
    ChessBoardCopy(ChessBoard& other);
    ~ChessBoardCopy();
    bool isKingInCheck() const override;
    PieceColor getCurrentPlayerColor() const override;
    void RemoveChessPiece(ChessPiece *PieceToRemove) override;
    void AddChessPiece(ChessPiece* PieceToAdd, const BoardPosition& boardposition) override;
private:
    ChessBoard& originalBoard;
};

#endif // CHESSBOARDCOPY_H
