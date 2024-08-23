#include "../headers/pawn.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"

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

std::vector<BoardPosition> Pawn::getValidNormalMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;

    /*
        If we find the chessbox, then we are checking
        is given chessbox occupied. If yes: for moving we are skiiping,
        for taking piece we are adding to ValidMoves.
    */
    if(this->getColor() == chessboard.getBottomPiecesColor()) // i.e. for bottom Pieces
    {
        // one move forward
        ChessBox* possmove1 = chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y - 1));

        if(possmove1 != nullptr && possmove1->getPiece() == nullptr)
        {
            ValidMoves.push_back(possmove1->getBoardPositon());

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
        }
    }
    else //i.e. for upper Pieces
    {
        // one move forward
        ChessBox* possmove1 = chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y + 1));

        if(possmove1 != nullptr && possmove1->getPiece() == nullptr)
        {
            ValidMoves.push_back(possmove1->getBoardPositon());

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
        }
    }

    return ValidMoves;
}

std::vector<BoardPosition> Pawn::getValidCaptureMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;

    if(this->getColor() == chessboard.getBottomPiecesColor()) // i.e. for bottom Pieces
    {
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

std::vector<BoardPosition> Pawn::getValidMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;
    std::vector<BoardPosition> NormalValidMoves = getValidNormalMoves(chessboard);
    std::vector<BoardPosition> CaptureValidMoves =  getValidCaptureMoves(chessboard);

    ValidMoves.reserve(NormalValidMoves.size() + CaptureValidMoves.size());
    ValidMoves.insert(ValidMoves.end(), NormalValidMoves.begin(), NormalValidMoves.end());
    ValidMoves.insert(ValidMoves.end(), CaptureValidMoves.begin(), CaptureValidMoves.end());

    return ValidMoves;
}

