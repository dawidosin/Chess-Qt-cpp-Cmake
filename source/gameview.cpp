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
    if (event->button() == Qt::LeftButton)
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
    }

    QGraphicsView::mousePressEvent(event);
    mouseMoveEvent(event);
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
    switch(game->gamestate)
    {
        case GameState::Checkmate:
        {
            this->gameEndDialog = new GameEndDialog();
            this->gameEndDialog->win(game->chessboard->getCurrentPlayerColor());
            connect(gameEndDialog->getRestartButton(), &QPushButton::clicked, game, &Game::restartGame);
            connect(gameEndDialog->getExitButton(), &QPushButton::clicked, game, &Game::exitGame);
            gameEndDialog->exec();
        } break;
        case GameState::Draw:
        {
            this->gameEndDialog = new GameEndDialog();
            this->gameEndDialog->draw();
            connect(gameEndDialog->getRestartButton(), &QPushButton::clicked, game, &Game::restartGame);
            connect(gameEndDialog->getExitButton(), &QPushButton::clicked, game, &Game::exitGame);
            gameEndDialog->exec();
        } break;
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
