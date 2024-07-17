#include "../headers/pawnpromotion.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"
#include "../headers/queen.h"
#include "../headers/rook.h"
#include "../headers/bishop.h"
#include "../headers/knight.h"

PawnPromotion::PawnPromotion(ChessBoard* _chessboard):
    chessboard(_chessboard)
{}

PieceType PawnPromotion::getPieceTypeAtPosition()
{
    for(const auto& piece: PiecesToChoose)
    {
        if(piece->isUnderMouse())
            return piece->getType();
    }
    return PieceType::None;
}

/*
  Shows all promoting option for pawn,
  distinguishing between Pieces that are on the bottom
  of the screen and upper.

  displays 1x4 rectangle that contains all of the
  promoting chesspiece options
*/
void PawnPromotion::show()
{
    rectangle = new QGraphicsRectItem(0, 0, BoxSize, BoxSize*4);
    rectangle->setPen(QPen(Qt::black));
    rectangle->setBrush(QBrush(Qt::white));

    ChessPiece* Queen_item = new Queen(pawn->getColor());
    ChessPiece* Rook_item = new Rook(pawn->getColor());
    ChessPiece* Bishop_item = new Bishop(pawn->getColor());
    ChessPiece* Knight_item = new Knight(pawn->getColor());

    QPixmap Queen_img, Rook_img, Bishop_img, Knight_img;

    std::vector<QPixmap*> img; // holds [0]:Queen, [1]:Rook, [2]:Bishop, [3]:Knight

    // holds [0]:Queen, [1]:Rook, [2]:Bishop, [3]:Knight
    PiecesToChoose.push_back(Queen_item);
    PiecesToChoose.push_back(Rook_item);
    PiecesToChoose.push_back(Bishop_item);
    PiecesToChoose.push_back(Knight_item);

    img.push_back(&Queen_img);
    img.push_back(&Rook_img);
    img.push_back(&Bishop_img);
    img.push_back(&Knight_img);

    for(int i = 0; i<=3; i++)
    {        
        PiecesToChoose[i]->setZValue(0);
        PiecesToChoose[i]->setParentItem(rectangle);
        PiecesToChoose[i]->setPos(QPointF(rectangle->pos().x(), rectangle->pos().y() + (BoxSize*i)));
    }

    chessboard->scene->addItem(rectangle);

    if(pawn->boardpos.y == 0) // upper pieces
        rectangle->setPos(pawn->pos());
    else // bottom pieces
        rectangle->setPos(QPointF(pawn->pos().x(), pawn->pos().y() - BoxSize*3));
}

void PawnPromotion::hide()
{
   for (auto Piece : PiecesToChoose)
    {
        chessboard->scene->removeItem(Piece);
        delete Piece;
    }

    PiecesToChoose.clear();
    chessboard->scene->removeItem(rectangle);
    delete rectangle;
}
