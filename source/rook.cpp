#include "../headers/rook.h"
#include "../headers/globals.h"
#include "../headers/game.h"

extern Game* game;

Rook::Rook(PieceColor _piececolor=PieceColor::Black):
    ChessPiece(_piececolor)
{
    setImage();
    piecetype = PieceType::Rook;
}

// Custom copy constructor
Rook::Rook(const Rook& other)
    : ChessPiece(other.piececolor)
{
    this->boardpos = other.boardpos;
    this->piecetype = other.piecetype;
    setImage();
}

ChessPiece* Rook::clone() const
{
    return new Rook(*this);
}

void Rook::setImage()
{
    if(piececolor == PieceColor::Black)
    {
        QPixmap pixmap(":/img/rook_black.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/rook_white.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        setPixmap(pixmap);
    }
}

std::vector<BoardPosition> Rook::getValidMoves(const ChessBoard& chessboard) const
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

    // Checking all possible straight moves
    std::vector<BoardPosition> vec1 = StraightCheck(this->boardpos, this->getColor(),DIRECTION::UP);
    std::vector<BoardPosition> vec2 = StraightCheck(this->boardpos, this->getColor(), DIRECTION::RIGHT);
    std::vector<BoardPosition> vec3 = StraightCheck(this->boardpos, this->getColor(), DIRECTION::LEFT);
    std::vector<BoardPosition> vec4 = StraightCheck(this->boardpos, this->getColor(), DIRECTION::DOWN);

    ValidMoves.insert(ValidMoves.end(), vec1.begin(), vec1.end());
    ValidMoves.insert(ValidMoves.end(), vec2.begin(), vec2.end());
    ValidMoves.insert(ValidMoves.end(), vec3.begin(), vec3.end());
    ValidMoves.insert(ValidMoves.end(), vec4.begin(), vec4.end());

    return ValidMoves;
}


