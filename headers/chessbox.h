#ifndef SQUAREITEM_H
#define SQUAREITEM_H

#include <QGraphicsItem>
#include <QColor>

#include "chesspiece.h"

class ChessBox : public QGraphicsRectItem {
public:
    ChessBox(QColor _color, BoardPosition _boardpos);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPiece(ChessPiece* _piece);
    ChessPiece* getPiece() const;
    BoardPosition getBoardPositon() const;
private:
    QColor color;
    BoardPosition boardpos;
    ChessPiece* piece;

    friend class ChessBoard;
    friend class ChessBoardCopy;
};

#endif // SQUAREITEM_H
