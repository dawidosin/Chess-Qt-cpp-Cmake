#include "../headers/pawn.h"

Pawn::Pawn(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor, PieceType::PAWN)
{setImage();}

// Custom copy constructor
Pawn::Pawn(const Pawn& other)
    : ChessPiece(other.piececolor, PieceType::PAWN)
{
    this->boardpos = other.getBoardpositon();
    this->isFirstMove = other.isFirstMove;
    setImage();
}

ChessPiece* Pawn::clone() const
{
    return new Pawn(*this);
}

void Pawn::setImage()
{
    if(piececolor == PieceColor::Black)
        setPixmap(ImageManager::Pawn_Black());
    else
        setPixmap(ImageManager::Pawn_White());
}
