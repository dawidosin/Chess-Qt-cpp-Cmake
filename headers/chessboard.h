#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <vector>

#include "chessbox.h"
#include "chesspiece.h"
#include "globals.h"
#include "boardposition.h"
#include "movesstack.h"
#include "chessboardview.h"
#include "movemanager.h"

/*
    Contains the chessboard and all pieces objects.
    Displays the chessboard.
*/
class ChessBoard
{
public:
    ChessBoardView* boardview;

    ChessBoard(MoveManager* _movemanager, QGraphicsScene* _scene, PieceColor _PlayerColor);
    ChessBoard(); // default
    void Initialize();
    void DragPiece(ChessPiece* piece);
    void DropPiece();
    void DetectGameState();
    void ChoosePawnPromotion(QPointF point);
    ChessPiece* getPieceAtMousePos(QPointF point) const;
    ChessPiece* getActivePiece() const;
    virtual bool isKingInCheck() const;
    ChessPiece* getKing(PieceColor color) const;
    ChessBox* getChessBox(BoardPosition pos) const;
    ChessPiece* getPieceAtBoardPos(BoardPosition pos) const;
    PieceColor getBottomPiecesColor() const;
    virtual PieceColor getCurrentPlayerColor() const;
    unsigned long long int getTurn() const;

    ~ChessBoard();
private:
    ChessBox* chessbox[8][8];
    std::vector <ChessPiece*> WhitePiece;
    std::vector <ChessPiece*> BlackPiece;
    std::vector<BoardPosition> PossibleMoves;
    ChessPiece* ActivePiece;
    PieceColor PlayerColor;
    ChessPiece* WhiteKing;
    ChessPiece* BlackKing;
    QGraphicsScene* scene;
    MoveManager* movemanager;

    void setPieceInBoardPos(ChessPiece* Piece, BoardPosition BoardPos);
    virtual void RemoveChessPiece(ChessPiece *PieceToRemove);
    virtual void AddChessPiece(ChessPiece* PieceToAdd, const BoardPosition& boardposition);
    ChessBox* getBoxAtBoardPosition(BoardPosition pos);
    bool isValidMove(BoardPosition move) const;
    bool PlayerHaveMove();
    void HandleKingCastling();
    void ValidateIsKingCheckAfterMoves(std::vector<BoardPosition>& PossibleMovesCheck, ChessPiece* PieceToCheck);

    friend class ChessBoardCopy;
    friend class MoveGenerator;
    friend struct ChessBoardView;
    friend class MovesStack;
    friend class SideBarMenu;
};

#endif // CHESSBOARD_H
