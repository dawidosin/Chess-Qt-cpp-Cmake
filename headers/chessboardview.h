#ifndef CHESSBOARDVIEW_H
#define CHESSBOARDVIEW_H
#include <QGraphicsPixmapItem>
#include <vector>

class ChessBoard;

struct ChessBoardView
{
    ChessBoardView(ChessBoard* _chessboard);
    void ShowPossibleMoves();
    void HidePossibleMoves();
    void ShowKingCheck();
    void HideKingCheck();
    void MoveActivePieceToMouse(QPoint point);
    std::vector<QGraphicsPixmapItem*> PossibleMovesImg;
private:
    ChessBoard* chessboard;
};

#endif // CHESSBOARDVIEW_H
