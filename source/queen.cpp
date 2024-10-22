#include "../headers/queen.h"

Queen::Queen(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor, PieceType::QUEEN)
{setImage();}

// Custom copy constructor
Queen::Queen(const Queen& other)
    : ChessPiece(other.piececolor, PieceType::QUEEN)
{
    this->boardpos = other.getBoardpositon();
    this->isFirstMove = other.isFirstMove;
    setImage();
}

ChessPiece* Queen::clone() const
{
    return new Queen(*this);
}

void Queen::setImage()
{
    if(piececolor == PieceColor::Black)
        setPixmap(ImageManager::Queen_Black());
    else
        setPixmap(ImageManager::Queen_White());
}
