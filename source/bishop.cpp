#include "../headers/bishop.h"

Bishop::Bishop(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor, PieceType::BISHOP)
{setImage();}

// Custom copy constructor
Bishop::Bishop(const Bishop& other)
    : ChessPiece(other.piececolor, PieceType::BISHOP)
{
    this->boardpos = other.getBoardpositon();
    this->isFirstMove = other.isFirstMove;
    setImage();
}

ChessPiece* Bishop::clone() const
{
    return new Bishop(*this);
}

void Bishop::setImage()
{
    if(piececolor == PieceColor::Black)
        setPixmap(ImageManager::Bishop_Black());
    else
        setPixmap(ImageManager::Bishop_White());
}
