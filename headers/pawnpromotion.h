#ifndef PAWNPROMOTION_H
#define PAWNPROMOTION_H
#include <QGraphicsPixmapItem>
#include <vector>

#include "chesspiece.h"

/*
   Its 4x1 Rectangle that shows all ChessPiece
   options for pawn promotion.
 */
class ChessBoard;

class PawnPromotion
{
public:
    PawnPromotion(ChessBoard* _chessboard);
    PieceType getPieceTypeAtPosition();
    void show();
    void hide();
    QGraphicsRectItem* rectangle;
    ChessPiece* pawn;
private:
    ChessBoard* chessboard;
    std::vector<ChessPiece*> PiecesToChoose;
};

#endif // PAWNPROMOTION_H
