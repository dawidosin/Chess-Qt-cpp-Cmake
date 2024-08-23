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
    // returns all possible moves
    virtual std::vector<BoardPosition> getValidMoves(const ChessBoard& chessboard) const = 0;
    // returns all Moves without capture
    virtual std::vector<BoardPosition> getValidNormalMoves(const ChessBoard& chessboard) const;
    // returns all capture moves
    virtual std::vector<BoardPosition> getValidCaptureMoves(const ChessBoard& chessboard) const;
    virtual ChessPiece* clone() const = 0;
    virtual void setImage() = 0;
    PieceColor getColor() const;
    PieceType getType() const;

    bool operator==(const ChessPiece &other) const;
protected:
    ChessPiece(PieceColor _piececolor);
    PieceColor piececolor;
    PieceType piecetype;
};

#endif // CHESSPIECE_H
