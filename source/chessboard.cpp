#include "../headers/chessboard.h"
#include "../headers/pawn.h"
#include "../headers/knight.h"
#include "../headers/bishop.h"
#include "../headers/rook.h"
#include "../headers/queen.h"
#include "../headers/king.h"
#include "../headers/globals.h"
#include "../headers/chessboardcopy.h"
#include "../headers/movegenerator.h"
#include "../headers/movesstack.h"

#include <cmath>

/*
    Creating chessboard with pieces
*/
ChessBoard::ChessBoard(MoveManager* _movemanager, QGraphicsScene *_scene, PieceColor _PlayerColor) :
    scene(_scene), PlayerColor(_PlayerColor), boardview(new ChessBoardView(this, _scene)), ActivePiece(nullptr),
    movemanager(_movemanager)
{
    _movemanager->movegenerator.setChessBoard(*this);

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
    scene(nullptr), PlayerColor(PieceColor::White), boardview(new ChessBoardView(this, nullptr)), ActivePiece(nullptr)
{}

ChessBoard::~ChessBoard()
{
    // it means that this is ChessBoardCopy obj and
    // it's already cleaned up
    if(scene == nullptr)
        return;

    delete boardview;

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
void ChessBoard::Initialize()
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
ChessPiece* ChessBoard::getPieceAtMousePos(QPointF point) const
{
    for(auto const& a: WhitePiece)
    {
        if(a->boundingRect().contains(a->mapFromParent(point)))
            return a;
    }
    for(auto const& a: BlackPiece)
    {
        if(a->boundingRect().contains(a->mapFromParent(point)))
            return a;
    }
    return nullptr;
}

/* It transforms Pawn into other ChessPiece,
   appropriately to the selected ChessPiece.
   It's used only when Pawn have promotion.
 */
void ChessBoard::ChoosePawnPromotion(QPointF point)
{
    ChessPiece* PromotingPawn = boardview->pawnpromotion.pawn;
    BoardPosition PawnBoardPos= boardview->pawnpromotion.pawn->getBoardpositon();
    PieceType ChosenPieceType = boardview->pawnpromotion.getPieceTypeAtMousePos();
    ChessPiece* ChosenPiece = nullptr;

    if(ChosenPieceType == PieceType::NONE)
        return;
    else
    {
        switch(ChosenPieceType)
        {
            case PieceType::QUEEN:
                ChosenPiece = new Queen(PromotingPawn->getColor());
                movemanager->moves.LastMove()->PawnPromotionPieceType = PieceType::QUEEN;
            break;
            case PieceType::ROOK:
                ChosenPiece = new Rook(PromotingPawn->getColor());
                 movemanager->moves.LastMove()->PawnPromotionPieceType = PieceType::ROOK;
            break;
            case PieceType::BISHOP:
                ChosenPiece = new Bishop(PromotingPawn->getColor());
                 movemanager->moves.LastMove()->PawnPromotionPieceType = PieceType::BISHOP;
            break;
            case PieceType::KNIGHT:
                ChosenPiece = new Knight(PromotingPawn->getColor());
                 movemanager->moves.LastMove()->PawnPromotionPieceType = PieceType::KNIGHT;
            break;
            case PieceType::NONE:
            case PieceType::KING:
            case PieceType::PAWN:
                break;
        }

        if(PromotingPawn->getColor() == PieceColor::White)
            WhitePiece.push_back(ChosenPiece);
        else
            BlackPiece.push_back(ChosenPiece);

        RemoveChessPiece(PromotingPawn);
        setPieceInBoardPos(ChosenPiece, PawnBoardPos);
        scene->addItem(ChosenPiece);
        ActivePiece = ChosenPiece;
        boardview->Clear();
    }
}
// Moves the rook in order to make castling with king
void ChessBoard::HandleKingCastling()
{
    PieceColor KingColor = (getCurrentPlayerColor() == PieceColor::White ? PieceColor::Black : PieceColor::White);
    BoardPosition KingPos = getKing(KingColor)->getBoardpositon();
    const Move& currentMove = *movemanager->moves.LastMove();
    bool isShortCastle = (currentMove.endpos.x - currentMove.startpos.x > 0 ? true : false );
    ChessPiece* RookChessPiece = nullptr;
    PieceColor BottomColor = getBottomPiecesColor();

    if(BottomColor == PieceColor::White)
    {
        if(isShortCastle)
        {
            RookChessPiece = getPieceAtBoardPos(BoardPosition(7, KingPos.y));
            setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x - 2, RookChessPiece->getBoardpositon().y));
        }
        else
        {
            RookChessPiece = getPieceAtBoardPos(BoardPosition(0, KingPos.y));
            setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x +  3, RookChessPiece->getBoardpositon().y));
        }
    }
    else
    {
        if(isShortCastle)
        {
            RookChessPiece = getPieceAtBoardPos(BoardPosition(0, KingPos.y));
            setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x + 2, RookChessPiece->getBoardpositon().y));
        }
        else
        {
            RookChessPiece = getPieceAtBoardPos(BoardPosition(7, KingPos.y));
            setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x - 3, RookChessPiece->getBoardpositon().y));
        }
    }
}

void ChessBoard::DragPiece(ChessPiece* piece)
{
    if(piece->getColor() == getCurrentPlayerColor())
    {
       ActivePiece = piece;
       ActivePiece->setZValue(1);
       boardview->ShowPossibleMoves();
       boardview->DraggedPiece = ActivePiece;
    }
}

// Checks the validity of the move, recognize the type of move
// and drops chesspiece in correct place
void ChessBoard::DropPiece()
{
    // holds digit cordinates to Dropped ChessBox
    BoardPosition NewChessBoxPos =
        {
         static_cast<int>(round((ActivePiece->pos().x())/GLOB::BoxSize)),
         static_cast<int>(round((ActivePiece->pos().y())/GLOB::BoxSize))
    };

    if(NewChessBoxPos == ActivePiece->getBoardpositon())
        goto restart; // we dont need to check that cause it's just move in the same position

    if (isValidMove(NewChessBoxPos))
    {
       // clears the board view
       boardview->Clear();

       // getting chessbox on which user clicked
       ChessBox* NewChessBox = getBoxAtBoardPosition(NewChessBoxPos);

       // adding Move to our std::queue<Move>
       movemanager->moves.MakeMove(*NewChessBox, *ActivePiece);

       /* Its an capture from chessPiece */
       if(movemanager->moves.LastMove()->CapturedPieceType != PieceType::NONE)
       {
            RemoveChessPiece(NewChessBox->getPiece());
       }

       /* Its normal move */
       setPieceInBoardPos(ActivePiece, NewChessBox->getBoardPositon());
       ActivePiece->isFirstMove = false;

       /* Promoting pawn handling */
       if(movemanager->moves.LastMove()->PawnPromotionPieceType != PieceType::NONE)
       {
            GLOB::CurrentGameState = GameState::PawnPromotion;
       }
       else if(movemanager->moves.LastMove()->isKingCastling == true)
       {
            HandleKingCastling();
       }

       // detects what type of game state it is
       DetectGameState();
    }
    else
    {
       restart:
       ActivePiece->setPos(ActivePiece->getBoardpositon().x * GLOB::BoxSize, ActivePiece->getBoardpositon().y * GLOB::BoxSize);
    }

    // cleaning
    boardview->HidePossibleMoves();
    ActivePiece->setZValue(0);
    boardview->DraggedPiece = nullptr;
}

// Detects all game state except PawnPromotion
void ChessBoard::DetectGameState()
{
    /* King check/check mate handling */
    if(isKingInCheck() == true)
    {
       // if check-mate
       if(PlayerHaveMove() == false)
       {
           GLOB::CurrentGameState = GameState::Checkmate;
           return;
       }
       // if check
       else
       {
           GLOB::CurrentGameState = GameState::Check;
           return;
       }
    }
    /* Checking for Draw */
    if(PlayerHaveMove() == false)
    {
       GLOB::CurrentGameState = GameState::Draw;
       return;
    }
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
            std::vector<BoardPosition> PossibleMovesForPiece = piece->getValidMoves(movemanager->movegenerator);
            ValidateIsKingCheckAfterMoves(PossibleMovesForPiece, piece);
            if(PossibleMovesForPiece.size() > 0)
                return true;
       }
    }
    else
    {
       for(auto const& piece: BlackPiece)
       {
            std::vector<BoardPosition> PossibleMovesForPiece = piece->getValidMoves(movemanager->movegenerator);
            ValidateIsKingCheckAfterMoves(PossibleMovesForPiece, piece);
            if(PossibleMovesForPiece.size() > 0)
                return true;
       }
    }
    return false;
}

/* Removes moves which would cause our team king in check.

 We are copying The actual chessboard and we are testing on
 it, is our King in danger by moving piece to actual new chessbox.
 So we can know if after move, our king is in danger.
 If yes then we are removing this move. */
void ChessBoard::ValidateIsKingCheckAfterMoves(std::vector<BoardPosition>& PossibleMovesCheck, ChessPiece* PieceToCheck)
{
    if(PossibleMovesCheck.empty())
       return;

    ChessBoardCopy chessboard_cpy(*this);

    if(PieceToCheck == this->ActivePiece)
       PieceToCheck = chessboard_cpy.ActivePiece;
    else // <---------------------------------------------------------------zmienic !!!!!!!!!!!!!!!!!!!
       PieceToCheck = chessboard_cpy.getPieceAtBoardPos(PieceToCheck->getBoardpositon());

    for (auto PossMove = PossibleMovesCheck.begin(); PossMove != PossibleMovesCheck.end();)
    {
       /* moving piece in order to check for potential danger after move for our king */
       // adding move to std::stack<Move>
       ChessBox* NewChessBox = chessboard_cpy.getBoxAtBoardPosition(*PossMove);
       chessboard_cpy.movemanager->moves.AddMove(*NewChessBox, *PieceToCheck);

       // its Castling so we don't need to check that
       if(chessboard_cpy.movemanager->moves.LastMove()->isKingCastling == true)
       {
            chessboard_cpy.movemanager->moves.RemoveMove();
            ++PossMove;
            continue;
       }

       // its an capture move
       if(NewChessBox->getPiece() != nullptr)
       {
            chessboard_cpy.RemoveChessPiece(NewChessBox->getPiece());
       }

       // its an normal move
       chessboard_cpy.setPieceInBoardPos(PieceToCheck, *PossMove);

       if(chessboard_cpy.isKingInCheck() == true)
            PossMove = PossibleMovesCheck.erase(PossMove);
       else
            ++PossMove;

       // move piece to original place
       chessboard_cpy.movemanager->moves.UndoMove();
    }

}

// checking is King in check range, by
// checking all valid moves from the enemy pieces
bool ChessBoard::isKingInCheck() const
{
    auto start = std::chrono::high_resolution_clock::now();
    bool test = movemanager->movegenerator.isKingInCheck();

    // Record end time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate duration
    std::chrono::duration<double> duration = end - start;

    // Output the duration in seconds
    qDebug() << "Elapsed time isKingInCheck(): " << duration.count() << " seconds" << Qt::endl;

    return test;
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
ChessBox* ChessBoard::getChessBox(BoardPosition pos) const
{
    if((pos.x >= 0 && pos.x <=7) && (pos.y >= 0 && pos.y <=7))
        return this->chessbox[pos.y][pos.x];
    else
        return nullptr;
}
// returns ChessPiece constant ptr
ChessPiece* ChessBoard::getPieceAtBoardPos(BoardPosition pos) const
{
    return getChessBox(pos)->piece;
}

ChessPiece* ChessBoard::getActivePiece() const
{
    return ActivePiece;
}

void ChessBoard::setPieceInBoardPos(ChessPiece* Piece, BoardPosition BoardPos)
{
    getBoxAtBoardPosition(Piece->getBoardpositon())->setPiece(nullptr);
    getBoxAtBoardPosition(BoardPos)->setPiece(Piece);
}

// removing ChessPiece from the game
void ChessBoard::RemoveChessPiece(ChessPiece *PieceToRemove)
{
    // removing from scene
    scene->removeItem(PieceToRemove);

    // removing from the ChessBox
    ChessBox* RemovePieceBox = getBoxAtBoardPosition(PieceToRemove->getBoardpositon());
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

void ChessBoard::AddChessPiece(ChessPiece* PieceToAdd, const BoardPosition& boardposition)
{
    // adding to scene
    scene->addItem(PieceToAdd);

    // adding to ChessBox
    setPieceInBoardPos(PieceToAdd, boardposition);

    // adding to vector
    if(PieceToAdd->getColor() == PieceColor::White)
       WhitePiece.push_back(PieceToAdd);
    else
       BlackPiece.push_back(PieceToAdd);
}

// returns PieceColor of ChessPieces
// which are located on the bottom of the ChessBoard
PieceColor ChessBoard::getBottomPiecesColor() const
{ return this->PlayerColor; }

PieceColor ChessBoard::getCurrentPlayerColor() const
{
    if(movemanager->moves.size() % 2 == 0 || movemanager->moves.canUndo() == false)
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
{
    if(!movemanager->moves.empty())
       return movemanager->moves.size() / 2;
    else
       return 1;
}
