#include "../headers/pawn.h"
#include "../headers/globals.h"
#include "../headers/game.h"

extern Game* game;

Pawn::Pawn(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor)
{
    setImage();
    piecetype = PieceType::Pawn;
}

// Custom copy constructor
Pawn::Pawn(const Pawn& other)
    : ChessPiece(other.piececolor)
{
    this->boardpos = other.boardpos;
    this->piecetype = other.piecetype;
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
    {
        QPixmap pixmap(":/img/pawn_black.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/pawn_white.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
}

std::vector<BoardPosition> Pawn::getValidMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;

    // holds Color of ChessPiece that are on the bottom of the ChessBoard
    PieceColor BottomPiecesColor = chessboard.getBottomPiecesColor();
        /*
          If we find the chessbox, then we are checking
          is given chessbox occupied. If yes: for moving we are skiiping,
          for taking piece we are adding to ValidMoves.
        */
        if(this->getColor() == BottomPiecesColor) // i.e. for bottom Pieces
        {
            // one move forward
            ChessBox* possmove1 = chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y - 1));
            if(possmove1 != nullptr)
            {
                if(possmove1->getPiece() == nullptr)
                    ValidMoves.push_back(possmove1->getBoardPositon());
            }
            // two moves forward
            if(isFirstMove)
            {
                ChessBox* possmove2 = chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y - 2));
                if(possmove2 != nullptr)
                {
                    if(possmove2->getPiece() != nullptr)
                        return ValidMoves;
                    else
                        ValidMoves.push_back(possmove2->getBoardPositon());
                }
            }
            // diagonal capturing piece
            ChessBox* posstake1 = chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y - 1));
            ChessBox* posstake2 = chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y - 1));
            if(posstake1 != nullptr)
            {
                // if it's Piece from opposite team
                if(posstake1->getPiece() != nullptr &&
                    posstake1->getPiece()->getColor() != this->getColor())
                    ValidMoves.push_back(posstake1->getBoardPositon());
            }
            if(posstake2 != nullptr)
            {
                if(posstake2->getPiece() != nullptr &&
                    posstake2->getPiece()->getColor() != this->getColor())
                    ValidMoves.push_back(posstake2->getBoardPositon());
            }
        }
        else //i.e. for upper Pieces
        {
            // one move forward
            ChessBox* possmove1 = chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y + 1));
            if(possmove1 != nullptr)
            {
                if(possmove1->getPiece() == nullptr)
                    ValidMoves.push_back(possmove1->getBoardPositon());
            }
            // two moves forward
            if(isFirstMove)
            {
                ChessBox* possmove2 = chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y + 2));
                if(possmove2 != nullptr)
                {
                    if(possmove2->getPiece() != nullptr)
                        return ValidMoves;
                    else
                        ValidMoves.push_back(possmove2->getBoardPositon());
                }          
            }

            // diagonal capturing piece
            ChessBox* posstake1 = chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y + 1));
            ChessBox* posstake2 = chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y + 1));
            if(posstake1 != nullptr)
            {
                // if it's Piece from opposite team
                if(posstake1->getPiece() != nullptr &&
                    posstake1->getPiece()->getColor() != this->getColor())
                    ValidMoves.push_back(posstake1->getBoardPositon());
            }
            if(posstake2 != nullptr)
            {
                if(posstake2->getPiece() != nullptr &&
                    posstake2->getPiece()->getColor() != this->getColor())
                    ValidMoves.push_back(posstake2->getBoardPositon());
            }
        }

    return ValidMoves;
}

