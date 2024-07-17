#include "../headers/king.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"

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

    // checks wheter any chesspiece is blocking our King to castle
    auto isAnyPieceInTheRookToKingWay = [&chessboard](const ChessPiece& Rook, const ChessPiece& King) -> bool
    {
        int difference = 0;

        if(King.boardpos.x - Rook.boardpos.x > 0) // Rook is on the left
            difference = -1;
        else // Rook is on the right
            difference = 1;

        while(true)
        {
            difference += difference;

            const ChessBox* chessbox = chessboard.findChessBox(BoardPosition(King.boardpos.x + difference, King.boardpos.y));
            if(chessbox == nullptr)
                return false;
            const ChessPiece* currentPiece = chessbox->getPiece();

            if(currentPiece != nullptr)
            {
                if(*currentPiece == Rook)
                    return false;
                else
                    return true;
            }
        }
    };

    // Checks are any Piece attacking boxes between Rook and King
    auto isAnyPieceAttackingCastlingBoxes = [&chessboard](const ChessPiece& Rook, const ChessPiece& King) -> bool
    {
        int difference = 0;

        if(King.boardpos.x - Rook.boardpos.x > 0) // Rook is on the left
            difference = -1;
        else // Rook is on the right
            difference = 1;

        while(true)
        {
            difference += difference;

            const ChessBox* chessbox = chessboard.findChessBox(BoardPosition(King.boardpos.x + difference, King.boardpos.y));
            if(chessbox == nullptr)
                return false;
            const ChessPiece* currentPiece = chessbox->getPiece();

            if(currentPiece != nullptr && *currentPiece == Rook)
                return false;

            if(chessboard.isChessBoxAttacked(chessbox->getBoardPositon()) == true)
                return true;
        }
    };

    /* Checking for possible castling.
        1. Neither the king nor the rook has previously moved.
        2. There are no pieces between the king and the rook.
        3. The king is not currently in check.
        4. The king does not pass through or finish on a square that is attacked by an enemy piece
    */

    if(this->isFirstMove == true)
    {
        const ChessPiece* LeftRook = chessboard.findPiece(BoardPosition(0, this->boardpos.y));
        const ChessPiece* RightRook = chessboard.findPiece(BoardPosition(7, this->boardpos.y));

            // left castling requirement
        if(LeftRook != nullptr && LeftRook->getType() == PieceType::Rook &&
            LeftRook->isFirstMove == true && isAnyPieceInTheRookToKingWay(*LeftRook, *this) == false &&
            Game::gamestate != GameState::Check && isAnyPieceAttackingCastlingBoxes(*LeftRook, *this) == false)
        {
            ValidMoves.push_back(BoardPosition(this->boardpos.x - 2, this->boardpos.y));
        }

        // right castling requirement
        if(RightRook != nullptr && RightRook->getType() == PieceType::Rook &&
            RightRook->isFirstMove == true && isAnyPieceInTheRookToKingWay(*RightRook, *this) == false &&
            Game::gamestate != GameState::Check && isAnyPieceAttackingCastlingBoxes(*RightRook, *this) == false)
        {
            ValidMoves.push_back(BoardPosition(this->boardpos.x + 2, this->boardpos.y));
        }
    }


    // adding Valid moves
    for(auto a: BoxesToCheck)
        ValidMoves.push_back(a->getBoardPositon());

    return ValidMoves;
}

