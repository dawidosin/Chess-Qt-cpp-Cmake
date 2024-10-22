#include "../headers/knight.h"

Knight::Knight(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor, PieceType::KNIGHT)
{setImage();}

Knight::Knight(const Knight& other)
    : ChessPiece(other.piececolor, PieceType::KNIGHT)
{
    this->boardpos = other.boardpos;
    this->isFirstMove = other.isFirstMove;
    setImage();
}

ChessPiece* Knight::clone() const
{
    return new Knight(*this);
}

void Knight::setImage()
{
    if(piececolor == PieceColor::Black)
        setPixmap(ImageManager::Knight_Black());
    else
        setPixmap(ImageManager::Knight_White());
}


