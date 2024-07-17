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
        switch(game->gamestate)
        {
            case GameState::Default: // if we clicked on piece
            case GameState::Check:
            {
                ChessPiece* ClickedPiece = game->chessboard->getPieceAtMousePosition(event->pos());
                if(ClickedPiece != nullptr)
                {
                    game->chessboard->DragPiece(ClickedPiece);
                }
            } break;
            case GameState::PawnPromotion:
            {
                game->chessboard->ChoosePawnPromotion(event->pos());
            } break;

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
