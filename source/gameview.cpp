#include "../headers/gameview.h"
#include "../headers/game.h"

extern Game* game;

GameView::GameView(QWidget *parent)
    : QGraphicsView(parent)
{
    setMouseTracking(true);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    // if we had active pawn already && clicked on chessbox
    if(game->chessboard->isPieceActive() && game->chessboard->getBoxAtMousePosition(event->pos()))
    {

    }
    // if we clicked on piece
    else
    {
        ChessPiece* ClickedPiece = game->chessboard->getPieceAtMousePosition(event->pos());
        if(ClickedPiece != nullptr)
        {
            game->chessboard->DragPiece(ClickedPiece);
        }
    }
    QGraphicsView::mousePressEvent(event);
}

void GameView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(game->chessboard->isPieceActive())
        {           
            game->chessboard->DropPiece();
        }
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    if(game->chessboard->isPieceActive())
    {
        QPoint point = {
            event->pos().x() - (BoxSize/2),
            event->pos().y() - (BoxSize/2)
        };
        game->chessboard->boardview.MoveActivePieceToMouse(point);
    }
    QGraphicsView::mouseMoveEvent(event);
}
