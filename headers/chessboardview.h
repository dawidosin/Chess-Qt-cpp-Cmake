#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H
#include <QGraphicsPixmapItem>
#include <vector>
#include "pawnpromotion.h"
#include "chesspiece.h"

class ChessBoard;

struct ChessBoardView
{
    ChessBoardView(ChessBoard* _chessboard, QGraphicsScene* _scene);
    void ShowPossibleMoves();
    void HidePossibleMoves();
    void ShowKingCheck();
    void HideKingCheck();
    void ShowPawnPromotion(ChessPiece* piece);
    void HidePawnPromotion();
    void MoveActivePieceToMouse(QPoint point);
    void Clear();
    std::vector<QGraphicsPixmapItem*> PossibleMovesItems;
    PawnPromotion pawnpromotion;
    ChessPiece* DraggedPiece;
private:
    QGraphicsScene* scene;
    ChessBoard* chessboard;
};

#endif // CHESSBOARDVIEW_H
