#ifndef MOVEGENERATOR_H
#define MOVEGENERATOR_H

#include <map>
#include <vector>

#include "boardposition.h"
#include "chesspiece.h"
#include "globals.h"

class ChessBoard;

/*
    Detects Check and Check-mate

    targets: holds a possible moves from every PieceType and every ChessBox on the board.

    By using pre-calculated data structures, the application can avoid complex computations during runtime.
    Instead of dynamically calculating potential moves and checks on every turn,
    the program can perform fast lookups, significantly improving performance
*/
class MoveGenerator
{
public:
    MoveGenerator();
    bool isKingInCheck();
    void setChessBoard(const ChessBoard& _chessboard);
    void Initialize();
    std::vector<BoardPosition> getPossibleMoves(const ChessPiece& piece);
private:
    enum class PieceCheck // Defines all types of Pieces and moves for them
    {
        BotPawn, TopPawn, Knight, Bishop, Rook, Queen, King, BotPawnCapt, TopPawnCapt, Castling,
        Up, Down, Left, Right, Up_Left, Up_Right, Down_Left, Down_Right
    };
    // holds all possible moves for every BoardPositon
    std::map<PieceCheck, std::map<BoardPosition, std::vector<BoardPosition>>> targets;
    const ChessBoard* chessboard;

    std::vector<BoardPosition> getKingCastleMoves();
    std::vector<BoardPosition> getValidMoves(BoardPosition pos, PieceCheck piececheck);
    bool isChessBoxAttacked(const BoardPosition& currentPoschessboard);
    bool lineOfSight(const std::vector<BoardPosition>& path) const;
    std::vector<BoardPosition> ValidBox(const std::vector<BoardPosition>& pos) const;
    std::vector<BoardPosition>::const_iterator getStartOfPath(const std::vector<BoardPosition>& path, const BoardPosition& start_pos) const;
    PieceCheck getPathDirection(const BoardPosition& start, const BoardPosition& end) const;
    std::vector<BoardPosition> getPathBetween(const BoardPosition& KingPos, const BoardPosition& end) const;
};

#endif // MOVEGENERATOR_H
