#include "../headers/king.h"
#include "../headers/globals.h"
#include "../headers/game.h"

extern Game* game;

King::King(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor)
{
    setImage();
    piecetype = PieceType::King;
}

// Custom copy constructor
King::King(const King& other)
    : ChessPiece(other.piececolor)
{
    this->boardpos = other.boardpos;
    this->piecetype = other.piecetype;
    setImage();
}

ChessPiece* King::clone() const
{
    return new King(*this);
}
void King::setImage()
{
    if(piececolor == PieceColor::Black)
    {
        QPixmap pixmap(":/img/king_black.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/king_white.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
}

std::vector<BoardPosition> King::getValidMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;
    std::vector<ChessBox*> BoxesToCheck;

    // getting pointers to the possible ChessBoxes to move our ChessPiece
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y - 1)));     // up
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y - 1))); // up and right
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y)));     // right
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x + 1, boardpos.y + 1))); // down and right
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x, boardpos.y + 1)));     // down
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y + 1))); // down and left
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y)));     // left
    BoxesToCheck.push_back(chessboard.findChessBox(BoardPosition(boardpos.x - 1, boardpos.y - 1))); // up and left

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

