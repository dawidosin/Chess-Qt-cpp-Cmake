#include "../headers/movelist.h"
#include "../headers/chessboard.h"
#include "../headers/pawn.h"
#include "../headers/knight.h"
#include "../headers/bishop.h"
#include "../headers/rook.h"
#include "../headers/queen.h"
#include "../headers/king.h"

#include <cmath>

MoveList::MoveList(ChessBoard* _chessboard) : chessboard(_chessboard) {}

Move::Move(BoardPosition _startpos, BoardPosition _endpos, bool _isPawnPromotion, bool _isPieceCaptured,
           PieceType _CapturedPieceType, bool _isCaptPieceFirstMove, bool _isKingCastling):
    startpos(_startpos), endpos(_endpos), isPieceCaptured(_isPieceCaptured),
    isPawnPromotion(_isPawnPromotion), CapturedPieceType(_CapturedPieceType),
    isCaptPieceFirstMove(_isCaptPieceFirstMove), isKingCastling(_isKingCastling)
{}

// Adds moves to std::stack<Move> Moves
// default values are for normal moves
// without capture, pawn promotion, castling
void MoveList::AddMove(const ChessBox& destinationBox, const ChessPiece& Piece)
{
    BoardPosition startPos = Piece.boardpos;
    BoardPosition endPos = destinationBox.getBoardPositon();
    bool isPawnPromotion = false;
    bool isKingCastling = false;
    bool isPieceCaptured = false;
    PieceType capturedPieceType = PieceType::None;
    bool isCaptPieceFirstMove = false;

    // it's an capture move
    if(destinationBox.getPiece() != nullptr)
    {
        isPieceCaptured = true;
        capturedPieceType = destinationBox.getPiece()->getType();
        isCaptPieceFirstMove = destinationBox.getPiece()->isFirstMove;
    }

    switch(Piece.getType())
    {
        case PieceType::Pawn: // checking for Pawn promotion
        {
            if((Piece.getColor() == chessboard->getBottomPiecesColor() && Piece.boardpos.y == 1) || // for bottom pieces player
                (Piece.getColor() != chessboard->getBottomPiecesColor() && Piece.boardpos.y == 6)) // for upper
            {
                isPawnPromotion =  true;
            }
        }break;
        case PieceType::King: // checking for King castling
        {
            if(abs(startPos.x-endPos.x) == 2)
                isKingCastling = true;
        }break;
    }


    this->push(Move{startPos, endPos, isPawnPromotion, isPieceCaptured, capturedPieceType, isCaptPieceFirstMove, isKingCastling});
}

// Undo a single chess move on the board
void MoveList::UndoMove()
{
    if (!this->empty())
    {
        Move currentMove = this->top();

        ChessPiece* currentPiece = chessboard->getPieceAtBoardPosition(currentMove.endpos);

        // returning piece to the previous place
        chessboard->setPieceInBoardPos(currentPiece, currentMove.startpos);

        // reviving captured piece if any
        if (currentMove.isPieceCaptured == true)
        {
            ChessPiece* CapturedPiece = nullptr;
            PieceColor oppositeColor = (currentPiece->getColor() == PieceColor::White ?
                PieceColor::Black : PieceColor::White);

            switch (currentMove.CapturedPieceType)
            {
            case PieceType::Pawn:
                CapturedPiece = new Pawn(oppositeColor);
                break;
            case PieceType::Knight:
                CapturedPiece = new Knight(oppositeColor);
                break;
            case PieceType::Bishop:
                CapturedPiece = new Bishop(oppositeColor);
                break;
            case PieceType::Rook:
                CapturedPiece = new Rook(oppositeColor);
                break;
            case PieceType::Queen:
                CapturedPiece = new Queen(oppositeColor);
                break;
            case PieceType::King:
                CapturedPiece = new King(oppositeColor);
                break;
            }

            if(CapturedPiece)
            {
                // adding CapturedPiece to the container and setting its position
                if (oppositeColor == PieceColor::White)
                    chessboard->WhitePiece.push_back(CapturedPiece);
                else
                    chessboard->BlackPiece.push_back(CapturedPiece);

                CapturedPiece->isFirstMove = currentMove.isCaptPieceFirstMove;
                chessboard->setPieceInBoardPos(CapturedPiece, currentMove.endpos);
            }           
        }
        if(currentMove.isPawnPromotion == true)
        {
            // removing new Promoted Piece
            ChessBox* currentChessBox = chessboard->getBoxAtBoardPosition(currentPiece->boardpos);
            PieceColor currentPieceColor = currentPiece->getColor();
            chessboard->RemoveChessPiece(currentPiece);

            // restore the old Pawn
            currentPiece = new Pawn(currentPieceColor);
            if(currentPieceColor == PieceColor::White)
                chessboard->WhitePiece.push_back(currentPiece);
            else
                chessboard->BlackPiece.push_back(currentPiece);

            chessboard->setPieceInBoardPos(currentPiece, currentChessBox->getBoardPositon());
        }
        else if(currentMove.isKingCastling == true)
        {
            ChessPiece* KingChessPiece = chessboard->getPieceAtBoardPosition(currentPiece->boardpos);
            // true (right castling)
            // false (left castling)
            bool isRightCastling = (currentMove.endpos.x - currentMove.startpos.x > 0 ? true : false );
            ChessPiece* RookChessPiece = nullptr;

            if(isRightCastling)
            {
                RookChessPiece = chessboard->getPieceAtBoardPosition(BoardPosition(7, currentPiece->boardpos.y));
                chessboard->setPieceInBoardPos(KingChessPiece, BoardPosition(KingChessPiece->boardpos.x + 2, KingChessPiece->boardpos.y));
                chessboard->setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->boardpos.x - 2, RookChessPiece->boardpos.y));
            }
            else
            {
                RookChessPiece = chessboard->getPieceAtBoardPosition(BoardPosition(0, currentPiece->boardpos.y));
                chessboard->setPieceInBoardPos(KingChessPiece, BoardPosition(KingChessPiece->boardpos.x - 2, KingChessPiece->boardpos.y));
                chessboard->setPieceInBoardPos(RookChessPiece, BoardPosition(RookChessPiece->boardpos.x + 3, RookChessPiece->boardpos.y));
            }
        }

        this->pop();
    }
}
