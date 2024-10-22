#ifndef PAWNPROMOTION_H
#define PAWNPROMOTION_H
#include <QGraphicsPixmapItem>
#include <vector>

#include "chesspiece.h"

class ChessBoard;

/*
   Its 4x1 Rectangle that shows all ChessPiece
   options for pawn promotion.
 */
class PawnPromotion
{
public:
    PawnPromotion(ChessBoard* _chessboard);
    PieceType getPieceTypeAtMousePos() const;
    void show(QGraphicsScene* scene);
    void hide(QGraphicsScene* scene);
    QGraphicsRectItem* rectangle;
    ChessPiece* pawn;
private:
    ChessBoard* chessboard;
    std::vector<ChessPiece*> PiecesToChoose;
};

#endif // PAWNPROMOTION_H
