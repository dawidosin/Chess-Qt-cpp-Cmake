#include "../headers/chesspiece.h"
#include "../headers/chessboard.h"

ChessPiece::ChessPiece(PieceColor _piececolor = PieceColor::White) :
    piececolor(_piececolor), QGraphicsPixmapItem(nullptr), boardpos{0,0}
{}

std::vector<BoardPosition> ChessPiece::getValidNormalMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves = getValidMoves(chessboard);
    std::vector<BoardPosition> ValidNormalMoves;

    // adding only normal moves without capture
    for(int i=ValidMoves.size() - 1;i >= 0;i--)
    {
        if(chessboard.findChessBox(ValidMoves[i])->getPiece() == nullptr)
        {
            ValidNormalMoves.push_back(std::move(ValidMoves[i]));
            ValidMoves.erase(ValidMoves.begin() + i);
        }
    }
    return ValidNormalMoves;
}

std::vector<BoardPosition> ChessPiece::getValidCaptureMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves = getValidMoves(chessboard);
    std::vector<BoardPosition> ValidCaptrueMoves;

    // adding only capture moves
    for(int i=ValidMoves.size() - 1;i >= 0;i--)
    {
        if(chessboard.findChessBox(ValidMoves[i])->getPiece() != nullptr)
        {
            ValidCaptrueMoves.push_back(std::move(ValidMoves[i]));
            ValidMoves.erase(ValidMoves.begin() + i);
        }
    }
    return ValidCaptrueMoves;
}


bool ChessPiece::operator==(const ChessPiece &other) const
{ return this->boardpos == other.boardpos; }

PieceColor ChessPiece::getColor() const
{ return this->piececolor; }

PieceType ChessPiece::getType() const
{ return this->piecetype; }
