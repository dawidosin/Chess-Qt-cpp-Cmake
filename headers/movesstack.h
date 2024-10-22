#ifndef MovesStack_H
#define MovesStack_H
#include "globals.h"
#include "chesspiece.h"
#include "chessbox.h"
#include "boardposition.h"

#include <stack>

class ChessBoard;

// holds all necessary info about single Move
struct Move
{
public:
    Move(BoardPosition _startpos, BoardPosition _endpos, PieceType _CapturedPieceType,
        bool _isPieceFirstMove, bool _isCaptPieceFirstMove, bool _isKingCastling, PieceType _PawnPromotionPieceType);
    bool isKingCastling;
    PieceType PawnPromotionPieceType;
    BoardPosition startpos;
    BoardPosition endpos;
    PieceType CapturedPieceType; // Holds PieceType::None if no capture
private:  
    bool isPieceFirstMove;
    bool isCaptPieceFirstMove;

    friend class MovesStack;
};

// it's an overridden std::list which holds all the moves and their specification
class MovesStack
{
public:
    MovesStack(ChessBoard* _chessboard);
    void AddMove(const ChessBox& destinationBox, const ChessPiece& Piece);
    void MakeMove(const ChessBox& destinationBox, const ChessPiece& Piece);
    void RemoveMove();
    void onClickUndoBtn();
    void onClickRedoBtn();
    void UndoMove();
    void setChessBoard(ChessBoard& _chessboard);
    bool canUndo() const;
    bool canRedo() const;
    Move* LastMove();
    const int size() const;
    const bool empty() const;

private:
    std::stack<Move> RedoStack;
    std::stack<Move> UndoStack;
    void Undo();
    void Redo();
    void UndoTurn();
    void RedoTurn();
    ChessBoard* chessboard;

    friend class MoveGenerator;
};
#endif // MovesStack_H
