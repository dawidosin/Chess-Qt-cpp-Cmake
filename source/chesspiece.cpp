#include "../headers/chesspiece.h"

ChessPiece::ChessPiece(PieceColor _piececolor = PieceColor::White) :
    piececolor(_piececolor), QGraphicsPixmapItem(nullptr), boardpos{0,0}
{}

bool ChessPiece::operator==(const ChessPiece &other) const
{ return this->boardpos == other.boardpos; }

PieceColor ChessPiece::getColor() const
{ return this->piececolor; }

PieceType ChessPiece::getType() const
{ return this->piecetype; }
