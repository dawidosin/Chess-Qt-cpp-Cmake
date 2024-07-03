#ifndef CHESSBOARDCOPY_H
#define CHESSBOARDCOPY_H
#include "chessboard.h"

/*
    Holds necessary data for Checking potential danger
    for our King after move
*/
struct ChessBoardCopy : public ChessBoard
{
    ChessBoardCopy(const ChessBoard& other);
    bool isKingInCheck() const override;
};

#endif // CHESSBOARDCOPY_H
