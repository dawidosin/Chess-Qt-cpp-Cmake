#include "../headers/chessboard.h"
#include "../headers/pawn.h"
#include "../headers/knight.h"
#include "../headers/bishop.h"
#include "../headers/rook.h"
#include "../headers/queen.h"
#include "../headers/king.h"
#include "../headers/globals.h"
#include "../headers/chessboardcopy.h"
#include "../headers/gameenddialog.h"

#include <cmath>

/*
    Creating chessboard with pieces
*/
ChessBoard::ChessBoard(QGraphicsScene *_scene, PieceColor _PlayerColor) :
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
    // removing from scene
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            this->scene->removeItem(chessbox[y][x]);
        }
    }
    for(auto const& a: WhitePiece)
    this->scene->removeItem(a);
    for(auto const& a: BlackPiece)
    this->scene->removeItem(a);

    // deleting objects
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
                delete chessbox[y][x];
        }
    }
    for (auto piece : WhitePiece)
    delete piece;
    for (auto piece : BlackPiece)
    delete piece;
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

/* It transforms Pawn into other ChessPiece,
   appropriately to the selected ChessPiece.
   It's used only when Pawn have promotion.
 */
void ChessBoard::ChoosePawnPromotion(QPointF point)
{
    ChessPiece* PromotingPawn = boardview.pawnpromotion.pawn;
    BoardPosition PawnBoardPos= boardview.pawnpromotion.pawn->boardpos;
    PieceType ChosenPieceType = boardview.pawnpromotion.getPieceTypeAtPosition();
    ChessPiece* ChosenPiece = nullptr;

    if(ChosenPieceType == PieceType::None)
        return;
    else
    {
        switch(ChosenPieceType)
        {
            case PieceType::Queen:
                ChosenPiece = new Queen(PromotingPawn->getColor());
            break;
            case PieceType::Rook:
                ChosenPiece = new Rook(PromotingPawn->getColor());
            break;
            case PieceType::Bishop:
                ChosenPiece = new Bishop(PromotingPawn->getColor());
            break;
            case PieceType::Knight:
                ChosenPiece = new Knight(PromotingPawn->getColor());
            break;
        }

        if(PromotingPawn->getColor() == PieceColor::White)
            WhitePiece.push_back(ChosenPiece);
        else
            BlackPiece.push_back(ChosenPiece);

        RemoveChessPiece(PromotingPawn);
        boardview.HidePawnPromotion();

        setPieceInBoardPos(ChosenPiece, PawnBoardPos);
        scene->addItem(ChosenPiece);
        Game::gamestate = GameState::Default;
    }
}
// Moves the rook in order to make castling with king
void ChessBoard::HandleKingCastling()
{
    BoardPosition KingPos = {0,0};
    if(getCurrentPlayerColor() == PieceColor::White)
        KingPos = getKing(PieceColor::Black)->boardpos;
    else
        KingPos = getKing(PieceColor::White)->boardpos;

    const Move& currentMove = moves.top();
    // true (right castling)
    // false (left castling)
    bool isRightCastling = (currentMove.endpos.x - currentMove.startpos.x > 0 ? true : false );
    ChessPiece* RookChessPiece = nullptr;

    if(isRightCastling)
    {
        RookChessPiece = getPieceAtBoardPosition(BoardPosition(7, KingPos.y));
        setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->boardpos.x - 2, RookChessPiece->boardpos.y));
    }
    else
    {
        RookChessPiece = getPieceAtBoardPosition(BoardPosition(0, KingPos.y));
        setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->boardpos.x + 3, RookChessPiece->boardpos.y));
    }
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

// Checks the validity of the move, recognize the type of move
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
       moves.AddMove(*NewChessBox, *ActivePiece);

       /* Its an capture from chessPiece */
       if(moves.top().isPieceCaptured == true)
       {
            RemoveChessPiece(NewChessBox->getPiece());
       }

       /* Its normal move */
       setPieceInBoardPos(ActivePiece, NewChessBox->boardpos);
       ActivePiece->isFirstMove = false;

       /* King check handling */
       if(isKingInCheck() == true)
       {
            // if check-mate
            if(PlayerHaveMove() == false)
            {
                Game::gamestate = GameState::Checkmate;
            }
            // if check
            else
            {
                Game::gamestate = GameState::Check;
                boardview.ShowKingCheck();
            }
       }
       // no longer king check
       else if (Game::gamestate == GameState::Check)
       {
            Game::gamestate = GameState::Default;
            boardview.HideKingCheck();
       }

       /* Checking for Draw */
       if(PlayerHaveMove() == false)
       {
           Game::gamestate = GameState::Draw;
       }

       /* Promoting pawn handling */
       if(moves.top().isPawnPromotion == true)
       {
            boardview.ShowPawnPromotion(ActivePiece);
            Game::gamestate = GameState::PawnPromotion;
       }
       else if(moves.top().isKingCastling == true)
       {
            HandleKingCastling();
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

bool ChessBoard::isValidMove(BoardPosition move) const
{
    for(auto const& possmove: PossibleMoves)
    {
       if(move == possmove)
            return true;
    }
    return false;
}

// returns true wheter the current player have any valid move
bool ChessBoard::PlayerHaveMove()
{
    if(getCurrentPlayerColor() == PieceColor::White)
    {
       for(auto const& piece: WhitePiece)
       {
            std::vector<BoardPosition> PossibleMovesForPiece = piece->getValidMoves(*this);
            ValidateIsKingCheckAfterMoves(PossibleMovesForPiece, piece);
            if(PossibleMovesForPiece.size() > 0)
                return true;
       }
    }
    else
    {
       for(auto const& piece: BlackPiece)
       {
            std::vector<BoardPosition> PossibleMovesForPiece = piece->getValidMoves(*this);
            ValidateIsKingCheckAfterMoves(PossibleMovesForPiece, piece);
            if(PossibleMovesForPiece.size() > 0)
                return true;
       }
    }
    return false;
}

/* Removing moves which would cause our team king in check.
 We are copying The actual chessboard and we are testing on,
 it is our King in danger by moving piece to actual new chessbox.
 So we can know if after move, our king is in danger.
 If yes then we are removing this move. */
void ChessBoard::ValidateIsKingCheckAfterMoves(std::vector<BoardPosition>& PossibleMovesCheck, ChessPiece* PieceToCheck)
{
    if(PossibleMovesCheck.empty())
       return;

    ChessBoardCopy chessboard_cpy(*this);

    if(PieceToCheck == this->ActivePiece)
       PieceToCheck = chessboard_cpy.ActivePiece;
    else
    {
       PieceToCheck = chessboard_cpy.findPiece(PieceToCheck->boardpos);
    }

    for (auto Move = PossibleMovesCheck.begin(); Move != PossibleMovesCheck.end();)
    {
       /* moving piece in order to check for potential danger after move for our king */
       // adding move to  std::queue<moves>
       ChessBox* NewChessBox = chessboard_cpy.getBoxAtBoardPosition(*Move);
       chessboard_cpy.moves.AddMove(*NewChessBox, *PieceToCheck);

       // its an capture move
       if(NewChessBox->getPiece() != nullptr)
            chessboard_cpy.RemoveChessPiece(NewChessBox->getPiece());
       // its an normal move
       chessboard_cpy.setPieceInBoardPos(PieceToCheck, *Move);

       if(chessboard_cpy.isKingInCheck() == true)
            Move = PossibleMovesCheck.erase(Move);
       else
            ++Move;

       // move piece to original place
       chessboard_cpy.moves.UndoMove();
    }
}

bool ChessBoard::isChessBoxAttacked(const BoardPosition boardposition) const
{
    if(getCurrentPlayerColor() == PieceColor::Black)
    {
       for(auto const& Piece: WhitePiece)
       {
            std::vector<BoardPosition> possiblePieceMoves = Piece->getValidCaptureMoves(*this);
            for(auto const Move: possiblePieceMoves)
            {
                if(Move == boardposition)
                    return true;
            }
       }
    }
    else
    {
       for(auto const& Piece: BlackPiece)
       {
            std::vector<BoardPosition> possiblePieceMoves = Piece->getValidCaptureMoves(*this);
            for(auto const Move: possiblePieceMoves)
            {
                if(Move == boardposition)
                    return true;
            }
       }
    }
    return false;
}

// checking is King in check range, by
// checking all valid moves from the enemy pieces
bool ChessBoard::isKingInCheck() const
{
    if(getCurrentPlayerColor() == PieceColor::Black)
    {
       if(isChessBoxAttacked(BlackKing->boardpos) == true)       
            return true;
    }
    else
    {
       if(isChessBoxAttacked(WhiteKing->boardpos) == true)
            return true;
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
// returns ChessPiece constant ptr
ChessPiece* ChessBoard::findPiece(BoardPosition pos) const
{
    return findChessBox(pos)->piece;
}

ChessPiece* ChessBoard::getActivePiece() const
{
    return ActivePiece;
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

unsigned long long int ChessBoard::getTurn() const
{ return turn; }
