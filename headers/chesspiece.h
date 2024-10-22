#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <vector>
#include "boardposition.h"
#include "globals.h"
#include "imagemanager.h"

class MoveGenerator;

class ChessPiece: public QGraphicsPixmapItem
{
public:
    // returns all possible moves
    std::vector<BoardPosition> getValidMoves(MoveGenerator& movegenerator) const;
    virtual ChessPiece* clone() const = 0;
    virtual void setImage() = 0;
    const PieceColor&  getColor() const;
    const PieceType& getType() const;
    const BoardPosition& getBoardpositon() const;

    bool isFirstMove = true;

    bool operator==(const ChessPiece &other) const;
protected:
    ChessPiece(PieceColor _piececolor, PieceType _piecetype);
    const PieceColor piececolor;
    const PieceType piecetype;
    BoardPosition boardpos;

    friend class ChessBox;
};

#endif // CHESSPIECE_H
