#include "../headers/gameview.h"
#include "../headers/game.h"
#include "../headers/chessboard.h"
#include "../headers/sidebarmenu.h"
#include "../headers/globals.h"

GameView::GameView(const Game* _game): game(_game)
{
    setMouseTracking(true);
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        // Check for Click on the ChessBoard
        switch(GLOB::CurrentGameState)
        {
            case GameState::Default: // if we clicked on piece
            case GameState::InCheck:
            {
                ChessPiece* ClickedPiece = game->chessboard->getPieceAtMousePos(event->pos());
                if(ClickedPiece != nullptr)
                {
                    game->chessboard->DragPiece(ClickedPiece);
                }
            } break;
            case GameState::InPawnPromotion:
            {
                game->chessboard->ChoosePawnPromotion(event->pos());   
            } break;
            default:
            {}//do nothing
        }

        // Check for Click on the SideBar
        game->interface->sidebarmenu->mousePressEvent(*event);
    }

    QGraphicsView::mousePressEvent(event);
    mouseMoveEvent(event);
}

void GameView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(game->chessboard->boardview->DraggedPiece)
        {
            game->chessboard->DropPiece();
            game->interface->sidebarmenu->Update();
        }
    }
    switch(GLOB::CurrentGameState)
    {
        case GameState::Check:
        {
            game->chessboard->boardview->ShowKingCheck();
            GLOB::CurrentGameState = GameState::InCheck;
        }break;
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
        case GameState::PawnPromotion:
        {
            game->chessboard->boardview->ShowPawnPromotion(game->chessboard->getActivePiece());
            GLOB::CurrentGameState = GameState::InPawnPromotion;
        }break;
        default:
        {}//do nothing
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void GameView::mouseMoveEvent(QMouseEvent *event)
{
    if(game->chessboard->boardview->DraggedPiece)
    {
        QPoint point = {
            event->pos().x() - (GLOB::BoxSize/2),
            event->pos().y() - (GLOB::BoxSize/2)
        };
        game->chessboard->boardview->MoveActivePieceToMouse(point);
    }
    QGraphicsView::mouseMoveEvent(event);
}
