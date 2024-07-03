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

/*
    Contains the chessboard and all pieces objects.
    Displays the chessboard.
*/
class ChessBoard
{
public:
    QGraphicsScene *scene;
    ChessBoardView boardview;

    ChessBoard(QWidget *parent, QGraphicsScene *_scene, PieceColor _PlayerColor);
    ChessBoard(); // default
    void InitializeBoard();
    void DragPiece(ChessPiece* piece);
    void DropPiece();
    void RemoveChessPiece(ChessPiece *PieceToRemove);
    void setPieceInBoardPos(ChessPiece* Piece, BoardPosition BoardPos);
    ChessPiece* getActivePiece();
    ChessBox* getBoxAtBoardPosition(BoardPosition pos);
    ChessBox* getBoxAtMousePosition(QPoint point);
    ChessPiece* getPieceAtMousePosition(QPointF point);
    ChessPiece* getPieceAtBoardPosition(BoardPosition pos);
    bool isPieceActive() const;
    virtual bool isKingInCheck() const;
    ChessPiece* getKing(PieceColor color) const;
    ChessBox* findChessBox(BoardPosition pos) const;
    PieceColor getBottomPiecesColor() const;
    PieceColor getCurrentPlayerColor() const;
    long long int getTurn() const;

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
    long long int turn = 1;
    mutable bool isCheck = false;
    MoveList moves;


    bool isValidMove(BoardPosition move);

    friend class ChessPiece;
    friend class ChessBoardCopy;
    friend struct MoveList;
    friend struct ChessBoardView;
};

#endif // CHESSBOARD_H
