#include "../headers/chessboardcopy.h"

// copy constructor only for Checking The Check for King
ChessBoardCopy::ChessBoardCopy(const ChessBoard& other)
{
    this->turn = other.turn;
    this->scene = new QGraphicsScene;
    this->PlayerColor = other.PlayerColor;
    this->moves = other.moves;
    this->moves.chessboard = this;

    // copying vectors of ChessPieces
    for (auto piece : other.WhitePiece)
    {
        this->WhitePiece.push_back(piece->clone());
    }
    for (auto piece : other.BlackPiece)
    {
        this->BlackPiece.push_back(piece->clone());
    }

    // copying 2d array of ChessBoxes
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if((x + y) % 2 == 0)
                chessbox[y][x] = new ChessBox(Qt::lightGray, BoardPosition{x, y});
            else
                chessbox[y][x] = new ChessBox(Qt::darkGray, BoardPosition{x, y});
        }
    }

    // adding pieces to chessbox
    for (auto& piece : WhitePiece)
    {
        chessbox[piece->boardpos.y][piece->boardpos.x]->setPiece(piece);
    }
    for (auto& piece : BlackPiece)
    {
        chessbox[piece->boardpos.y][piece->boardpos.x]->setPiece(piece);
    }

    this->ActivePiece = this->getBoxAtBoardPosition(other.ActivePiece->boardpos)->piece;
    this->WhiteKing =  this->getBoxAtBoardPosition(other.WhiteKing->boardpos)->piece;
    this->BlackKing = this->getBoxAtBoardPosition(other.BlackKing->boardpos)->piece;
}

// It's an overrided function cause it get's the curr color and uses BlackPiece vector and so on
// but the base class use opposite approach so if curr color is White it checks the WhitePiece vector
//
// checking is King in check range, by
// checking all valid moves from the enemy pieces
bool ChessBoardCopy::isKingInCheck() const
{
    if(getCurrentPlayerColor() == PieceColor::White)
    {
        for(auto const& Piece: WhitePiece)
        {
            std::vector<BoardPosition> possiblePieceMoves = Piece->getValidMoves(*this);
            for(auto const Move: possiblePieceMoves)
            {
                if(Move == BlackKing->boardpos)
                {
                    Game::gamestate = GameState::Check;
                    return true;
                }
            }
        }
    }
    else
    {
        for(auto const& Piece: BlackPiece)
        {
            std::vector<BoardPosition> possiblePieceMoves = Piece->getValidMoves(*this);
            for(auto const Move: possiblePieceMoves)
            {
                if(Move == WhiteKing->boardpos)
                {
                    Game::gamestate = GameState::Check;
                    return true;
                }
            }
        }
    }
    return false;
}


