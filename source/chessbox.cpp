#include "../headers/chessbox.h"
#include "../headers/boardposition.h"
#include "../headers/globals.h"
#include <QPainter>


ChessBox::ChessBox(QColor _color, BoardPosition _boardpos)
    : color(_color), boardpos(_boardpos)
{
    setRect(boardpos.x * BoxSize, boardpos.y * BoxSize, BoxSize, BoxSize);
    setBrush(QBrush(color));
    update();

    piece = nullptr;
}

void ChessBox::setPiece(ChessPiece* _piece)
{
    if(_piece)
    {
        piece = _piece;
        piece->setPos(boardpos.x * BoxSize, boardpos.y * BoxSize);
        piece->boardpos = BoardPosition{boardpos.x, boardpos.y};
    }
    else
        piece = nullptr;
}

ChessPiece* ChessBox::getPiece() const
{
    return this->piece;
}

BoardPosition ChessBox::getBoardPositon() const
{
    return this->boardpos;
}

// overrided functions //
QRectF ChessBox::boundingRect() const {
    return QRectF(boardpos.x * BoxSize, boardpos.y * BoxSize, BoxSize, BoxSize);
}

void ChessBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setBrush(color);
    painter->drawRect(boardpos.x * BoxSize, boardpos.y * BoxSize, BoxSize, BoxSize);
}
