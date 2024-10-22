#include "../headers/king.h"

King::King(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor, PieceType::KING)
{setImage();}

// Custom copy constructor
King::King(const King& other)
    : ChessPiece(other.piececolor, PieceType::KING)
{
    this->boardpos = other.getBoardpositon();
    this->isFirstMove = other.isFirstMove;
    setImage();
}

ChessPiece* King::clone() const
{
    return new King(*this);
}

void King::setImage()
{
    if(piececolor == PieceColor::Black)
        setPixmap(ImageManager::King_Black());
    else
        setPixmap(ImageManager::King_White());
}
