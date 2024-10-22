#include "../headers/movesstack.h"
#include "../headers/chessboard.h"
#include "../headers/pawn.h"
#include "../headers/knight.h"
#include "../headers/bishop.h"
#include "../headers/rook.h"
#include "../headers/queen.h"
#include "../headers/king.h"
#include "../headers/globals.h"

#include <cmath>

MovesStack::MovesStack(ChessBoard* _chessboard) : chessboard(_chessboard) {}

Move::Move(BoardPosition _startpos, BoardPosition _endpos, PieceType _CapturedPieceType,
           bool _isPieceFirstMove, bool _isCaptPieceFirstMove, bool _isKingCastling, PieceType _PawnPromotionPieceType):
    startpos(_startpos), endpos(_endpos), CapturedPieceType(_CapturedPieceType), isPieceFirstMove(_isPieceFirstMove),
    isCaptPieceFirstMove(_isCaptPieceFirstMove), isKingCastling(_isKingCastling), PawnPromotionPieceType(_PawnPromotionPieceType)
{}


// Adds moves to std::stack<Move> RedoStack
// Should be used only for ChessBoardCopy
void MovesStack::AddMove(const ChessBox& destinationBox, const ChessPiece& Piece)
{
    const BoardPosition& startPos = Piece.getBoardpositon();
    const BoardPosition& endPos = destinationBox.getBoardPositon();
    PieceType PawnPromotionPieceType = PieceType::NONE;
    bool isKingCastling = false;
    PieceType capturedPieceType = PieceType::NONE;
    bool isPieceFirstMove = Piece.isFirstMove;
    bool isCaptPieceFirstMove = false;

    // it's an capture move
    if(destinationBox.getPiece() != nullptr)
    {
        capturedPieceType = destinationBox.getPiece()->getType();
        isCaptPieceFirstMove = destinationBox.getPiece()->isFirstMove;
    }
    switch(Piece.getType())
    {
        case PieceType::PAWN: // checking for Pawn promotion
        {
            if((Piece.getColor() == chessboard->getBottomPiecesColor() && Piece.getBoardpositon().y == 1) || // for bottom pieces player
                (Piece.getColor() != chessboard->getBottomPiecesColor() && Piece.getBoardpositon().y == 6)) // for upper
            {
                PawnPromotionPieceType =  PieceType::PAWN; // holds any value regarding the NONE
            }
        }break;
        case PieceType::KING: // checking for King castling
        {
            if(abs(startPos.x-endPos.x) == 2)
                isKingCastling = true;
        }break;
        default:
        {} break; // we dont need to do anything
    }

    // adding the prepared Move
    UndoStack.push(Move{startPos, endPos, capturedPieceType, isPieceFirstMove, isCaptPieceFirstMove, isKingCastling, PawnPromotionPieceType});
}

// Adds moves to std::stack<Move> RedoStack
// Should be used only for ChessBoard
void MovesStack::MakeMove(const ChessBox& destinationBox, const ChessPiece& Piece)
{
    this->AddMove(destinationBox, Piece);

    /*  Removes not used part of the std::stack<> RedoStack.

        Cause when the user "Undo()" and then does the move
        we need to remove the old not used part intended for "Redo()"
    */
    if (!RedoStack.empty())
    {
        while(!RedoStack.empty())
            RedoStack.pop();
    }
}

// Undo a single chess move on the board
void MovesStack::Undo()
{
    if (canUndo())
    {
        ChessPiece* currentPiece = chessboard->getPieceAtBoardPos(LastMove()->endpos);

        // returning piece to the previous place and adding previous isFirstMove
        chessboard->setPieceInBoardPos(currentPiece, LastMove()->startpos);
        currentPiece->isFirstMove = LastMove()->isPieceFirstMove;

        // reviving captured piece if any
        if (LastMove()->CapturedPieceType != PieceType::NONE)
        {
            ChessPiece* CapturedPiece = nullptr;
            PieceColor oppositeColor = (currentPiece->getColor() == PieceColor::White ?
                PieceColor::Black : PieceColor::White);

            switch (LastMove()->CapturedPieceType)
            {
            case PieceType::PAWN:
                CapturedPiece = new Pawn(oppositeColor);
                break;
            case PieceType::KNIGHT:
                CapturedPiece = new Knight(oppositeColor);
                break;
            case PieceType::BISHOP:
                CapturedPiece = new Bishop(oppositeColor);
                break;
            case PieceType::ROOK:
                CapturedPiece = new Rook(oppositeColor);
                break;
            case PieceType::QUEEN:
                CapturedPiece = new Queen(oppositeColor);
                break;
            case PieceType::KING:
                CapturedPiece = new King(oppositeColor);
                break;
            }

            CapturedPiece->isFirstMove = LastMove()->isCaptPieceFirstMove;
            chessboard->AddChessPiece(CapturedPiece, LastMove()->endpos);

        }
        if(LastMove()->PawnPromotionPieceType != PieceType::NONE)
        {
            // removing new Promoted Piece
            ChessBox* currentChessBox = chessboard->getBoxAtBoardPosition(currentPiece->getBoardpositon());
            PieceColor currentPieceColor = currentPiece->getColor();

            chessboard->RemoveChessPiece(currentPiece);

            // restore the old Pawn
            currentPiece = new Pawn(currentPieceColor);
            chessboard->AddChessPiece(currentPiece, currentChessBox->getBoardPositon());
            currentPiece->isFirstMove = false;
        }
        else if(LastMove()->isKingCastling == true)
        {
            ChessPiece* KingChessPiece = chessboard->getPieceAtBoardPos(currentPiece->getBoardpositon());
            // means that rooks need to move 2 ChessBoxes instead of 3
            bool isShortCastle = (LastMove()->endpos.x - LastMove()->startpos.x > 0 ? true : false );
            ChessPiece* RookChessPiece = nullptr;
            PieceColor BottomColor = chessboard->getBottomPiecesColor();

            // Checking on which part of the board is Castle
            // and also which king color is castling.
            // Then moves the rook in previous position
            if(BottomColor == PieceColor::White)
            {
                if(isShortCastle)
                {
                    RookChessPiece = chessboard->getPieceAtBoardPos(BoardPosition(5, KingChessPiece->getBoardpositon().y));
                    chessboard->setPieceInBoardPos
                        (RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x + 2, RookChessPiece->getBoardpositon().y));
                }
                else
                {
                    RookChessPiece = chessboard->getPieceAtBoardPos(BoardPosition(3, KingChessPiece->getBoardpositon().y));
                    chessboard->setPieceInBoardPos
                        (RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x -  3, RookChessPiece->getBoardpositon().y));
                }
            }
            else
            {
                if(isShortCastle)
                {
                    RookChessPiece = chessboard->getPieceAtBoardPos(BoardPosition(2, KingChessPiece->getBoardpositon().y));
                    chessboard->setPieceInBoardPos
                        (RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x - 2, RookChessPiece->getBoardpositon().y));
                }
                else
                {
                    RookChessPiece = chessboard->getPieceAtBoardPos(BoardPosition(4, KingChessPiece->getBoardpositon().y));
                    chessboard->setPieceInBoardPos
                        (RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x + 3, RookChessPiece->getBoardpositon().y));
                }
            }
            RookChessPiece->isFirstMove = true;
        }
        else if(GLOB::CurrentGameState == GameState::InCheck)
            chessboard->boardview->Clear();
    }
}

// Redo a single chess move on the board
// and sets LastMove()
void MovesStack::Redo()
{
    if (canRedo())
    {
        const Move& FutureCurrMove  = RedoStack.top();
        ChessPiece* currentPiece = chessboard->getPieceAtBoardPos(FutureCurrMove.startpos);

        // capturing piece if any
        if (FutureCurrMove.CapturedPieceType != PieceType::NONE)
        {
            ChessPiece* CapturedPiece = chessboard->getPieceAtBoardPos(FutureCurrMove.endpos);
            chessboard->RemoveChessPiece(CapturedPiece);
        }

        // setting piece to the future place and adding future isFirstMove
        chessboard->setPieceInBoardPos(currentPiece, FutureCurrMove.endpos);
        currentPiece->isFirstMove = false;

        if(FutureCurrMove.PawnPromotionPieceType != PieceType::NONE)
        {
            // removing pawn
            ChessBox* currentChessBox = chessboard->getBoxAtBoardPosition(currentPiece->getBoardpositon());
            PieceColor currentPieceColor = currentPiece->getColor();
            chessboard->RemoveChessPiece(currentPiece);

            // restore the future promoted pawn
            switch(FutureCurrMove.PawnPromotionPieceType)
            {
            case PieceType::QUEEN:
                currentPiece = new Queen(currentPieceColor);
                break;
            case PieceType::ROOK:
               currentPiece = new Rook(currentPieceColor);
                break;
            case PieceType::BISHOP:
               currentPiece = new Bishop(currentPieceColor);
                break;
            case PieceType::KNIGHT:
                currentPiece = new Knight(currentPieceColor);
                break;
            default:
                break;
            }

            chessboard->AddChessPiece(currentPiece, currentChessBox->getBoardPositon());
            currentPiece->isFirstMove = false;
        }
        else if(FutureCurrMove.isKingCastling == true)
        {
            ChessPiece* KingChessPiece = chessboard->getPieceAtBoardPos(currentPiece->getBoardpositon());
            // means that rooks need to move 2 ChessBoxes instead of 3
            bool isShortCastle = (FutureCurrMove.endpos.x - FutureCurrMove.startpos.x > 0 ? true : false );
            ChessPiece* RookChessPiece = nullptr;

            // Checking on which part of the board is Castle
            // and also which king color is castling.
            // Then moves the rook in previous position

            if(isShortCastle)
            {
                RookChessPiece = chessboard->getPieceAtBoardPos(BoardPosition(7, KingChessPiece->getBoardpositon().y));
                chessboard->setPieceInBoardPos
                    (RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x - 2, RookChessPiece->getBoardpositon().y));
            }
            else
            {
                RookChessPiece = chessboard->getPieceAtBoardPos(BoardPosition(0, KingChessPiece->getBoardpositon().y));
                chessboard->setPieceInBoardPos
                    (RookChessPiece, BoardPosition(RookChessPiece->getBoardpositon().x + 3, RookChessPiece->getBoardpositon().y));
            }
        }

        // After Redo we need to detect current GameState
        chessboard->DetectGameState();

        if(GLOB::CurrentGameState == GameState::Check)
        {
            chessboard->boardview->ShowKingCheck();
            GLOB::CurrentGameState = GameState::InCheck;
        }
    }
}

void MovesStack::UndoTurn()
{
    // checking wheter the whole turn was previous
    // or just a half of it
    int UndoCounter = UndoStack.size() % 2 == 0 ? 2 : 1;

    for(; UndoCounter > 0; UndoCounter--)
    {
        Undo();
        // Moving current move to the RedoStack and setting previous move
        // to be at the top of the UndoStack (so it'll be current)
        auto temp = UndoStack.top();
        UndoStack.pop();
        RedoStack.push(temp);
    }
}

void MovesStack::RedoTurn()
{
    // checking wheter the whole turn was previous
    // or just a half of it
    int RedoCounter = RedoStack.size() % 2 == 0 ? 2 : 1;

    for(; RedoCounter > 0; RedoCounter--)
    {
        Redo();
        // Moving current move to the UndoStack and setting previous move
        // to be at the top of the RedoStack
        auto OldLastMove = RedoStack.top();
        RedoStack.pop();
        UndoStack.push(OldLastMove);
    }
}

void MovesStack::UndoMove()
{
    this->Undo();
    this->UndoStack.pop();
}

void MovesStack::onClickUndoBtn()
{
    this->UndoTurn();
}

void MovesStack::onClickRedoBtn()
{
    this->RedoTurn();
}

void MovesStack::setChessBoard(ChessBoard& _chessboard)
{
    this->chessboard = &_chessboard;
}

// If LastMove() isn't pointing to the invalid adress end()
bool MovesStack::canUndo() const
{
    bool a = this->UndoStack.empty() == false;
    return a;
}

// If LastMove() isn't pointing to the last adress end() - 1
bool MovesStack::canRedo() const
{
    bool a = this->RedoStack.empty() == false;
    return a;
}

void MovesStack::RemoveMove()
{
    if(canUndo())
    {
        UndoStack.pop();
    }
}

Move* MovesStack::LastMove()
{
    if(!this->empty())
        return &this->UndoStack.top();
    else nullptr;
}

const int MovesStack::size() const
{
    return this->UndoStack.size();
}

const bool MovesStack::empty() const
{
    return this->UndoStack.empty();
}

