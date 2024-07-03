#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <vector>
#include "boardposition.h"

class ChessBoard;

enum class PieceType {
    King,
    Queen,
    Rook,
    Bishop,
    Knight,
    Pawn,
    None
};

enum PieceColor
{
    Black,
    White
};

class ChessPiece: public QGraphicsPixmapItem
{
public:
    BoardPosition boardpos;
    bool isFirstMove = true;
    virtual void setImage() = 0;
    virtual std::vector<BoardPosition> getValidMoves(const ChessBoard& chessboard) const = 0;
    virtual ChessPiece* clone() const = 0;
    PieceColor getColor() const;
    PieceType getType() const;
    void ValidateIsKingCheckAfterMoves(const ChessBoard& chessboard, std::vector<BoardPosition>& PossibleMoves);
protected:
    ChessPiece(PieceColor _piececolor);
    PieceColor piececolor;
    PieceType piecetype;
};

#endif // CHESSPIECE_H