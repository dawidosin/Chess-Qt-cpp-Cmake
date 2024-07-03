#include "../headers/chesspiece.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"
#include "../headers/chessboardcopy.h"

ChessPiece::ChessPiece(PieceColor _piececolor = PieceColor::White) :
    piececolor(_piececolor), QGraphicsPixmapItem(nullptr), boardpos{0,0}
{
}

/* Removing moves which would cause our team king in check.
 We are copying The actual chessboard and we are testing on,
 it is our King in danger by moving piece to actual new chessbox.
 So we can know if after move, our king is in danger.
 If yes then we are removing this movse. */
void ChessPiece::ValidateIsKingCheckAfterMoves(const ChessBoard& chessboard, std::vector<BoardPosition>& PossibleMoves)
{
    if(PossibleMoves.empty())
        return;

    ChessBoardCopy chessboard_cpy(chessboard);

    for (auto Move = PossibleMoves.begin(); Move != PossibleMoves.end();)
    {
        /* moving piece in order to check for potential danger after move for our king */
        // adding move to  std::queue<moves>
        ChessBox* NewChessBox = chessboard_cpy.getBoxAtBoardPosition(*Move);
        chessboard_cpy.moves.AddMove(chessboard_cpy.getBoxAtBoardPosition(*Move));

        // its an capture move
        if(NewChessBox->getPiece() != nullptr )
            chessboard_cpy.RemoveChessPiece(NewChessBox->getPiece());

        // its an normal move
        chessboard_cpy.setPieceInBoardPos(chessboard_cpy.ActivePiece, *Move);

        if(chessboard_cpy.isKingInCheck() == true)
            Move = PossibleMoves.erase(Move);
        else
            ++Move;

        // move piece to original place
        chessboard_cpy.moves.UndoMove();
    }
}

PieceColor ChessPiece::getColor() const
{ return this->piececolor; }

PieceType ChessPiece::getType() const
{ return this->piecetype; }
