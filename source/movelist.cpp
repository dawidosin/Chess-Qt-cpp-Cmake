#include "../headers/movelist.h"
#include "../headers/chessboard.h"
#include "../headers/pawn.h"
#include "../headers/knight.h"
#include "../headers/bishop.h"
#include "../headers/rook.h"
#include "../headers/queen.h"
#include "../headers/king.h"

MoveList::MoveList(ChessBoard* _chessboard) : chessboard(_chessboard) {}

Move::Move(BoardPosition _startpos, BoardPosition _endpos, PieceType _CapturedPiece, bool _isCaptPieceFirstMove)
    : startpos(_startpos), endpos(_endpos), CapturedPiece(_CapturedPiece), isCaptPieceFirstMove(_isCaptPieceFirstMove) {}

// Adds moves to std::stack<Move> Moves
void MoveList::AddMove(const ChessBox* destinationBox) {
    const ChessPiece* piece = chessboard->ActivePiece;
    BoardPosition startPos = piece->boardpos;
    BoardPosition endPos = destinationBox->getBoardPositon();
    PieceType capturedPieceType;
    bool isCaptPieceFirstMove = false;

    if(destinationBox->getPiece() != nullptr) // it's an capture move
    {
        capturedPieceType = destinationBox->getPiece()->getType();
        isCaptPieceFirstMove = destinationBox->getPiece()->isFirstMove;
    }
    else // it's a normal move
    {
        capturedPieceType = PieceType::None;
    }

    this->push(Move{startPos, endPos, capturedPieceType, isCaptPieceFirstMove});
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
        if (currentMove.CapturedPiece != PieceType::None)
        {
            ChessPiece* CapturedPiece = nullptr;
            PieceColor oppositeColor = (currentPiece->getColor() == PieceColor::White ?
                PieceColor::Black : PieceColor::White);

            switch (currentMove.CapturedPiece)
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

            // adding CapturedPiece to the container and setting its position
            if (oppositeColor == PieceColor::White)
                chessboard->WhitePiece.push_back(CapturedPiece);
            else
                chessboard->BlackPiece.push_back(CapturedPiece);

            CapturedPiece->isFirstMove = currentMove.isCaptPieceFirstMove;
            chessboard->setPieceInBoardPos(CapturedPiece, currentMove.endpos);
        }

        this->pop();
    }
}
