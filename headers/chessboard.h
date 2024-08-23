#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <vector>

#include "chessbox.h"
#include "globals.h"
#include "boardposition.h"
#include "movelist.h"
#include "chessboardview.h"
#include "game.h"

class Game;

/*
    Contains the chessboard and all pieces objects.
    Displays the chessboard.
*/
class ChessBoard
{
public:
    QGraphicsScene *scene;
    ChessBoardView boardview;

    ChessBoard(QGraphicsScene *_scene, PieceColor _PlayerColor);
    ChessBoard(); // default
    void InitializeBoard();
    void DragPiece(ChessPiece* piece);
    void DropPiece();
    ChessPiece* getPieceAtMousePosition(QPointF point);
    void ChoosePawnPromotion(QPointF point);
    ChessPiece* getActivePiece() const;
    bool isPieceActive() const;
    virtual bool isKingInCheck() const;
    bool isChessBoxAttacked(const BoardPosition boardposition) const;
    ChessPiece* getKing(PieceColor color) const;
    ChessBox* findChessBox(BoardPosition pos) const;
    ChessPiece* findPiece(BoardPosition pos) const;
    PieceColor getBottomPiecesColor() const;
    PieceColor getCurrentPlayerColor() const;
    unsigned long long int getTurn() const;

    ~ChessBoard();
private:
    ChessBox* chessbox[8][8];
    std::vector <ChessPiece*> WhitePiece;
    std::vector <ChessPiece*> BlackPiece;
    std::vector<BoardPosition> PossibleMoves;
    ChessPiece* ActivePiece = nullptr;
    PieceColor PlayerColor = PieceColor::White;
    ChessPiece* WhiteKing;
    ChessPiece* BlackKing;
    unsigned long long int turn = 1;
    MoveList moves;

    void setPieceInBoardPos(ChessPiece* Piece, BoardPosition BoardPos);
    void RemoveChessPiece(ChessPiece *PieceToRemove);
    ChessBox* getBoxAtBoardPosition(BoardPosition pos);
    ChessPiece* getPieceAtBoardPosition(BoardPosition pos);
    bool isValidMove(BoardPosition move) const;
    bool PlayerHaveMove();
    void HandleKingCastling();
    void ValidateIsKingCheckAfterMoves(std::vector<BoardPosition>& PossibleMovesCheck, ChessPiece* PieceToCheck);
    void ResetTheBoard();

    friend class ChessBoardCopy;
    friend struct ChessBoardView;
    friend struct MoveList;
};

#endif // CHESSBOARD_H
