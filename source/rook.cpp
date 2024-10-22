#include "../headers/rook.h"

Rook::Rook(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor, PieceType::ROOK)
{setImage();}

Rook::Rook(const Rook& other)
    : ChessPiece(other.piececolor, PieceType::ROOK)
{
    this->boardpos = other.boardpos;
    this->isFirstMove = other.isFirstMove;
    setImage();
}

ChessPiece* Rook::clone() const
{
    return new Rook(*this);
}

void Rook::setImage()
{
    if(piececolor == PieceColor::Black)
        setPixmap(ImageManager::Rook_Black());
    else
        setPixmap(ImageManager::Rook_White());
}



