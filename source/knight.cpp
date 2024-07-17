#include "../headers/knight.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"

Knight::Knight(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor)
{
    setImage();
    piecetype = PieceType::Knight;
}

// Custom copy constructor
Knight::Knight(const Knight& other)
    : ChessPiece(other.piececolor)
{
    this->boardpos = other.boardpos;
    this->piecetype = other.piecetype;
    setImage();
}

ChessPiece* Knight::clone() const
{
    return new Knight(*this);
}

void Knight::setImage()
{
    if(piececolor == PieceColor::Black)
    {
        QPixmap pixmap(":/img/knight_black.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/knight_white.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
}

std::vector<BoardPosition> Knight::getValidMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;
    std::vector<ChessBox*> BoxesToCheck;

    // getting pointers to the possible ChessBoxes to move our ChessPiece
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y - 2))); // up and left
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y - 2))); // up and right
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 2, boardpos.y - 1))); // right and up
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 2, boardpos.y + 1))); // right and down
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y + 2))); // down and right
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y + 2))); // down and left
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 2, boardpos.y + 1))); // left and down
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 2, boardpos.y - 1))); // left and up

    // checking are this ChessBoxes a valid moves
    for(int i=BoxesToCheck.size() - 1;i >= 0;i--)
    {
        // if we didn't find the ChessBox
        if(BoxesToCheck[i] == nullptr)
            BoxesToCheck.erase(BoxesToCheck.begin() + i);
        // if we are capturing Piece from our team (illegal move)
        else if((BoxesToCheck[i]->getPiece() != nullptr) &&
                 (BoxesToCheck[i]->getPiece()->getColor() == this->getColor()))
            BoxesToCheck.erase(BoxesToCheck.begin() + i);
    }
    // adding Valid moves
    for(auto a: BoxesToCheck)
        ValidMoves.push_back(a->getBoardPositon());

    return ValidMoves;
}

