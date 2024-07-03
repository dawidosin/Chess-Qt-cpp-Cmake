#include "../headers/chessboard.h"
#include "../headers/pawn.h"
#include "../headers/knight.h"
#include "../headers/bishop.h"
#include "../headers/rook.h"
#include "../headers/queen.h"
#include "../headers/king.h"
#include "../headers/game.h"
#include "../headers/globals.h"
#include <cmath>
extern Game* game;

/*
    Creating chessboard with pieces
*/
ChessBoard::ChessBoard(QWidget *parent, QGraphicsScene *_scene, PieceColor _PlayerColor) :
    scene(_scene), PlayerColor(_PlayerColor), moves(this), boardview(this)
{
    scene->setSceneRect(0, 0, ViewWidth, ViewHeight);
    // adding Boxes
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
    // Initializing Pieces
    //pawn
    for(int x = 0; x < 8; x++)
    {
        WhitePiece.push_back(new Pawn(PieceColor::White));
        BlackPiece.push_back(new Pawn(PieceColor::Black));

        chessbox[1][x]->setPiece(BlackPiece.back());
        chessbox[6][x]->setPiece(WhitePiece.back());
    }
    //knight
        WhitePiece.push_back(new Knight(PieceColor::White));
        BlackPiece.push_back(new Knight(PieceColor::Black));
        chessbox[0][1]->setPiece(BlackPiece.back());
        chessbox[7][6]->setPiece(WhitePiece.back());

        WhitePiece.push_back(new Knight(PieceColor::White));
        BlackPiece.push_back(new Knight(PieceColor::Black));
        chessbox[0][6]->setPiece(BlackPiece.back());
        chessbox[7][1]->setPiece(WhitePiece.back());
    //bishop
        WhitePiece.push_back(new Bishop(PieceColor::White));
        BlackPiece.push_back(new Bishop(PieceColor::Black));
        chessbox[0][2]->setPiece(BlackPiece.back());
        chessbox[7][5]->setPiece(WhitePiece.back());

        WhitePiece.push_back(new Bishop(PieceColor::White));
        BlackPiece.push_back(new Bishop(PieceColor::Black));
        chessbox[0][5]->setPiece(BlackPiece.back());
        chessbox[7][2]->setPiece(WhitePiece.back());
    //rook
        WhitePiece.push_back(new Rook(PieceColor::White));
        BlackPiece.push_back(new Rook(PieceColor::Black));
        chessbox[0][0]->setPiece(BlackPiece.back());
        chessbox[7][7]->setPiece(WhitePiece.back());

        WhitePiece.push_back(new Rook(PieceColor::White));
        BlackPiece.push_back(new Rook(PieceColor::Black));
        chessbox[0][7]->setPiece(BlackPiece.back());
        chessbox[7][0]->setPiece(WhitePiece.back());
    //Queen
        WhitePiece.push_back(new Queen(PieceColor::White));
        BlackPiece.push_back(new Queen(PieceColor::Black));
        chessbox[0][3]->setPiece(BlackPiece.back());
        chessbox[7][3]->setPiece(WhitePiece.back());
    //King
        WhitePiece.push_back(new King(PieceColor::White));
        BlackPiece.push_back(new King(PieceColor::Black));
        chessbox[0][4]->setPiece(BlackPiece.back());
        chessbox[7][4]->setPiece(WhitePiece.back());

        WhiteKing = WhitePiece.back();
        BlackKing = BlackPiece.back();
}

// deafault constructor for ChessBoardCopy
ChessBoard::ChessBoard() :
    scene(nullptr), PlayerColor(PieceColor::White), moves(this), boardview(this)
{}

ChessBoard::~ChessBoard()
{
    for (auto piece : WhitePiece)
    delete piece;

    for (auto piece : BlackPiece)
    delete piece;

    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            delete chessbox[y][x];
        }
    }
}
// adding all Items to the scene
void ChessBoard::InitializeBoard()
{
    // adding boxes
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            this->scene->addItem(chessbox[y][x]);
        }
    }
    // adding Pieces to scene
    for(auto const& a: WhitePiece)
        this->scene->addItem(a);
    for(auto const& a: BlackPiece)
        this->scene->addItem(a);
}

// returns ChessPiece that contains point
ChessPiece* ChessBoard::getPieceAtMousePosition(QPointF point)
{
    auto isPointInBox = [](const QPointF cord, int width, const QPointF pkt) -> bool {
        int x1 = cord.x();
        int y1 = cord.y();
        int x2 = x1 + width;
        int y2 = y1 + width;

        int px = pkt.x();
        int py = pkt.y();

        return (px >= x1 && px <= x2 && py >= y1 && py <= y2);
    };

    for(auto const& a: WhitePiece)
    {
        if(isPointInBox(a->pos(), BoxSize, point))
            return a;
    }
    for(auto const& a: BlackPiece)
    {
        if(isPointInBox(a->pos(), BoxSize, point))
            return a;
    }
    return nullptr;
}

ChessPiece* ChessBoard::getPieceAtBoardPosition(BoardPosition pos)
{
    return  getBoxAtBoardPosition(pos)->piece;
}

ChessBox* ChessBoard::getBoxAtMousePosition(QPoint point)
{
    for(int y=0;y<8;y++)
    {
       for(int x=0;x<8;x++)
       {
            if(this->chessbox[y][x]->contains(point))
                return chessbox[y][x];
       }
    }
    return nullptr;
}

void ChessBoard::DragPiece(ChessPiece* piece)
{
    if(piece->getColor() == getCurrentPlayerColor())
    {
       ActivePiece = piece;
       ActivePiece->setZValue(1);
       boardview.ShowPossibleMoves();
    }
}

// Checks the validity of the move, and recognize is it capture or move
// and drops chesspiece in correct place
void ChessBoard::DropPiece()
{
    // holds digit cordinates to Dropped ChessBox
    BoardPosition NewChessBoxPos =
    {
        static_cast<int>(round((ActivePiece->pos().x())/BoxSize)),
        static_cast<int>(round((ActivePiece->pos().y())/BoxSize))
    };

    if (isValidMove(NewChessBoxPos))
    {
       ChessBox* NewChessBox = getBoxAtBoardPosition(NewChessBoxPos);
       ChessBox* OldChessBox = getBoxAtBoardPosition(ActivePiece->boardpos);

       // adding Move to our std::queue<Move>
       moves.AddMove(NewChessBox);

       /* Its an capture from chessPiece */
       if(NewChessBox->getPiece() != nullptr )
            RemoveChessPiece(NewChessBox->getPiece());

       /* Its normal move */
       ActivePiece->isFirstMove = false;
       OldChessBox->setPiece(nullptr);
       NewChessBox->setPiece(ActivePiece);

       /* King check handling */
       if(isKingInCheck() == true)
            boardview.ShowKingCheck();
       // king is no longer check
       else if (isCheck == true)
       {
            isCheck = false;
            boardview.HideKingCheck();
       }

       // incrementing turn
       if(moves.size() % 2 == 0 && !moves.empty())
           turn++; // 1 turn == 2 moves
    }
    else
    {
       ActivePiece->setPos(ActivePiece->boardpos.x * BoxSize, ActivePiece->boardpos.y * BoxSize);      
    }
    boardview.HidePossibleMoves();
    ActivePiece->setZValue(0);
    ActivePiece = nullptr;
}

bool ChessBoard::isValidMove(BoardPosition move)
{
    for(auto const& possmove: PossibleMoves)
    {
       if(move == possmove)
            return true;
    }
    return false;
}

// checking is King in check range, by
// checking all valid moves from the enemy pieces
bool ChessBoard::isKingInCheck() const
{
    if(getCurrentPlayerColor() == PieceColor::Black)
    {
       for(auto const& Piece: WhitePiece)
       {
            std::vector<BoardPosition> possiblePieceMoves = Piece->getValidMoves(*this);
            for(auto const Move: possiblePieceMoves)
            {
                if(Move == BlackKing->boardpos)
                {
                    isCheck = true;
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
                    isCheck = true;
                    return true;
                }
            }
       }
    }
    return false;
}

// returns ChessBox ptr
ChessBox* ChessBoard::getBoxAtBoardPosition(BoardPosition pos)
{
    if((pos.x >= 0 && pos.x <=7) && (pos.y >= 0 && pos.y <=7))
       return this->chessbox[pos.y][pos.x];
    else
       return nullptr;
}

// returns ChessBox constant ptr
ChessBox* ChessBoard::findChessBox(BoardPosition pos) const
{
    if((pos.x >= 0 && pos.x <=7) && (pos.y >= 0 && pos.y <=7))
        return this->chessbox[pos.y][pos.x];
    else
        return nullptr;
}

bool ChessBoard::isPieceActive() const
{
    if(ActivePiece)
       return true;
    else
       return false;
}

void ChessBoard::setPieceInBoardPos(ChessPiece* Piece, BoardPosition BoardPos)
{
    getBoxAtBoardPosition(Piece->boardpos)->setPiece(nullptr);
    getBoxAtBoardPosition(BoardPos)->setPiece(Piece);
}

// removing ChessPiece from the game
void ChessBoard::RemoveChessPiece(ChessPiece *PieceToRemove)
{
    //removing from the scene
    scene->removeItem(PieceToRemove);

    //removing from the ChessBox
    ChessBox* RemovePieceBox = getBoxAtBoardPosition(PieceToRemove->boardpos);
    RemovePieceBox->setPiece(nullptr);

    // removing from the vector
    if(PieceToRemove->getColor() == PieceColor::White)
    {
       auto it = std::remove(WhitePiece.begin(), WhitePiece.end(), PieceToRemove);
       if (it != WhitePiece.end())
            WhitePiece.erase(it, WhitePiece.end());
    }
    else
    {
       auto it = std::remove(BlackPiece.begin(), BlackPiece.end(), PieceToRemove);
       if (it != BlackPiece.end())
            BlackPiece.erase(it, BlackPiece.end());
    }

    delete PieceToRemove;
}

// returns nullptr if no piece is active
ChessPiece* ChessBoard::getActivePiece()
{ return this->ActivePiece; }

// returns PieceColor of ChessPieces
// which are located on the bottom of the ChessBoard
PieceColor ChessBoard::getBottomPiecesColor() const
{ return this->PlayerColor; }

PieceColor ChessBoard::getCurrentPlayerColor() const
{
    if(moves.size() % 2 == 0 || moves.empty())
       return PieceColor::White;
    else
       return PieceColor::Black;
}

ChessPiece* ChessBoard::getKing(PieceColor color) const
{
    if(color == PieceColor::White)
       return WhiteKing;
    else
       return BlackKing;
}

long long int ChessBoard::getTurn() const
{ return turn; }
