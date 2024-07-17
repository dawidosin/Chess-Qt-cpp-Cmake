#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H
#include <QGraphicsPixmapItem>
#include <vector>
#include "pawnpromotion.h"

class ChessBoard;

struct ChessBoardView
{
    ChessBoardView(ChessBoard* _chessboard);
    void ShowPossibleMoves();
    void HidePossibleMoves();
    void ShowKingCheck();
    void HideKingCheck();
    void ShowPawnPromotion(ChessPiece* piece);
    void HidePawnPromotion();
    void MoveActivePieceToMouse(QPoint point);
    std::vector<QGraphicsPixmapItem*> PossibleMovesItems;
    PawnPromotion pawnpromotion;
private:
    ChessBoard* chessboard;
};

#endif // CHESSBOARDVIEW_H
