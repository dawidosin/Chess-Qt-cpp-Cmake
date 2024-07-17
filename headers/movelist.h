#ifndef MOVELIST_H
#define MOVELIST_H
#include "chesspiece.h"
#include "chessbox.h"
#include "boardposition.h"

#include <stack>

class ChessBoard;

struct Move
{
public:
    Move(BoardPosition _startpos, BoardPosition _endpos, bool _isPawnPromotion, bool _isPieceCaptured,
         PieceType _CapturedPieceType, bool _isCaptPieceFirstMove, bool _isKingCastling);
    bool isPawnPromotion;
    bool isPieceCaptured;
    bool isKingCastling;
    BoardPosition startpos;
    BoardPosition endpos;
private:  
    PieceType CapturedPieceType; // Holds PieceType::None if no capture
    bool isCaptPieceFirstMove;

    friend class MoveList;
};

// it's an queue for holding all moves in chess algebric notation
struct MoveList: public std::stack<Move>
{
    MoveList(ChessBoard* _chessboard);
    void AddMove(const ChessBox& destinationBox, const ChessPiece& Piece);
    void UndoMove();
    void UndoTurn();
    ChessBoard* chessboard;
};

#endif // MOVELIST_H
