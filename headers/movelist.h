#ifndef MOVELIST_H
#define MOVELIST_H
#include "chesspiece.h"
#include "chessbox.h"
#include "boardposition.h"

#include <stack>

class ChessBoard;

struct Move {
    Move(BoardPosition _startpos, BoardPosition _endpos, PieceType _CapturedPiece, bool _isCaptPieceFirstMove);
    BoardPosition startpos;
    BoardPosition endpos;
    PieceType CapturedPiece; // Holds PieceType::None if no capture
    bool isCaptPieceFirstMove;
};

// it's an queue for holding all moves in chess algebric notation
struct MoveList: public std::stack<Move>
{
    MoveList(ChessBoard* _chessboard);
    void AddMove(const ChessBox* destinationBox);
    void UndoMove();
    void UndoTurn();
    ChessBoard* chessboard;
};

#endif // MOVELIST_H
