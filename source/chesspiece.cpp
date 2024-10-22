#include "../headers/chesspiece.h"
#include "../headers/movegenerator.h"

ChessPiece::ChessPiece(PieceColor _piececolor = PieceColor::White, PieceType _piecetype = PieceType::NONE) :
    piececolor(_piececolor), piecetype(_piecetype), QGraphicsPixmapItem(nullptr), boardpos{0,0}
{}

std::vector<BoardPosition> ChessPiece::getValidMoves(MoveGenerator& movegenerator) const
{
    return movegenerator.getPossibleMoves(*this);
}

bool ChessPiece::operator==(const ChessPiece &other) const
{ return this->getBoardpositon() == other.getBoardpositon(); }

const PieceColor&  ChessPiece::getColor() const
{ return this->piececolor; }

const PieceType& ChessPiece::getType() const
{ return this->piecetype; }

const BoardPosition& ChessPiece::getBoardpositon() const
{ return this->boardpos; }

