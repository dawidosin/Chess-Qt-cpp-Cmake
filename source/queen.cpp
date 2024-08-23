#include "../headers/queen.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"

Queen::Queen(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor)
{
    setImage();
    piecetype = PieceType::Queen;
}

// Custom copy constructor
Queen::Queen(const Queen& other)
    : ChessPiece(other.piececolor)
{
    this->boardpos = other.boardpos;
    this->piecetype = other.piecetype;
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
    {
        QPixmap pixmap(":/img/queen_black.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/queen_white.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
}

std::vector<BoardPosition> Queen::getValidMoves(const ChessBoard& chessboard) const
{
    std::vector<BoardPosition> ValidMoves;

    enum DIRECTION
    {
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    // check straight moves for Rook
    auto StraightCheck = [&chessboard](const BoardPosition& boardpos, PieceColor ThisPieceColor, DIRECTION direction)
    {
        std::vector<BoardPosition> StraightMoves;
        // used to identify the direction
        int horizontal = 0;
        int vertical = 0;

        switch(direction)
        {
        case LEFT:
        {
            horizontal = -1;
        }break;
        case RIGHT:
        {
            horizontal = 1;
        }break;
        case UP:
        {
            vertical = -1;
        }break;
        case DOWN:
        {
            vertical = 1;
        }break;
        }

        for (int x = horizontal, y = vertical; (x < 8 && y < 8); x = x + horizontal, y = y + vertical)
        {
            ChessBox* possmove = chessboard.findChessBox(BoardPosition(boardpos.x + x, boardpos.y + y));
            if (possmove == nullptr) // this ChessBox doesn't exists
            {
                break;
            }
            else if (possmove->getPiece() != nullptr) // Piece blocking our way
            {
                // Capturing opposite ChessPiece
                if (possmove->getPiece()->getColor()!= ThisPieceColor)
                {
                    StraightMoves.push_back(possmove->getBoardPositon());
                }
                break;
            }
            else // Valid Move
            {
                StraightMoves.push_back(possmove->getBoardPositon());
            }
        }
        return StraightMoves;
    };

    // check diagonal moves
    auto DiagonalCheck = [&chessboard](const BoardPosition& boardpos, PieceColor ThisPieceColor, DIRECTION d_x, DIRECTION d_y) -> std::vector<BoardPosition>
    {
        std::vector<BoardPosition> DiagonalMoves;
        // used to identify the direction
        int horizontal = 0;
        int vertical = 0;

        switch(d_x)
        {
        case LEFT:
        {
            horizontal = -1;
        }break;
        case RIGHT:
        {
            horizontal = 1;
        }break;
        }

        switch(d_y)
        {
        case UP:
        {
            vertical = -1;
        }break;
        case DOWN:
        {
            vertical = 1;
        }break;
        }


        for (int x = horizontal, y = vertical; (x < 8 && y < 8); x = x + horizontal, y = y + vertical)
        {
            ChessBox* possmove = chessboard.findChessBox(BoardPosition(boardpos.x + x, boardpos.y + y));
            if (possmove == nullptr) // this ChessBox doesn't exists
            {
                break;
            }
            else if (possmove->getPiece() != nullptr) // Piece blocking our way
            {
                // Capturing opposite ChessPiece
                if (possmove->getPiece()->getColor()!= ThisPieceColor)
                {
                    DiagonalMoves.push_back(possmove->getBoardPositon());
                }
                break;
            }
            else // Valid Move
            {
                DiagonalMoves.push_back(possmove->getBoardPositon());
            }
        }
        return DiagonalMoves;
    };

    // Checking all possible straight moves
    std::vector<BoardPosition> vec1 = StraightCheck(this->boardpos, this->getColor(),DIRECTION::UP);
    std::vector<BoardPosition> vec2 = StraightCheck(this->boardpos, this->getColor(), DIRECTION::RIGHT);
    std::vector<BoardPosition> vec3 = StraightCheck(this->boardpos, this->getColor(), DIRECTION::LEFT);
    std::vector<BoardPosition> vec4 = StraightCheck(this->boardpos, this->getColor(), DIRECTION::DOWN);

    ValidMoves.insert(ValidMoves.end(), vec1.begin(), vec1.end());
    ValidMoves.insert(ValidMoves.end(), vec2.begin(), vec2.end());
    ValidMoves.insert(ValidMoves.end(), vec3.begin(), vec3.end());
    ValidMoves.insert(ValidMoves.end(), vec4.begin(), vec4.end());

    // Checking all possible diagonal moves
    std::vector<BoardPosition> vec5 = DiagonalCheck(this->boardpos, this->getColor(), DIRECTION::RIGHT, DIRECTION::UP);
    std::vector<BoardPosition> vec6 = DiagonalCheck(this->boardpos, this->getColor(), DIRECTION::LEFT, DIRECTION::UP);
    std::vector<BoardPosition> vec7 = DiagonalCheck(this->boardpos, this->getColor(), DIRECTION::RIGHT, DIRECTION::DOWN);
    std::vector<BoardPosition> vec8 = DiagonalCheck(this->boardpos, this->getColor(), DIRECTION::LEFT, DIRECTION::DOWN);

    ValidMoves.insert(ValidMoves.end(), vec5.begin(), vec5.end());
    ValidMoves.insert(ValidMoves.end(), vec6.begin(), vec6.end());
    ValidMoves.insert(ValidMoves.end(), vec7.begin(), vec7.end());
    ValidMoves.insert(ValidMoves.end(), vec8.begin(), vec8.end());

    return ValidMoves;
}

