#include <QGraphicsView>
#include "../headers/chessboardview.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"
#include "../headers/imagemanager.h"

ChessBoardView::ChessBoardView(ChessBoard* _chessboard, QGraphicsScene* _scene): chessboard(_chessboard), pawnpromotion(_chessboard),
    DraggedPiece(nullptr), scene(_scene)
{}

// Shows possible moves for ActivePiece
void ChessBoardView::ShowPossibleMoves()
{
    if(chessboard->ActivePiece)
    {
        // clears previous shown moves
        HidePossibleMoves();

        chessboard->PossibleMoves = chessboard->ActivePiece->getValidMoves(chessboard->movemanager->movegenerator);
        chessboard->ValidateIsKingCheckAfterMoves(chessboard->PossibleMoves, chessboard->ActivePiece);

        for (const auto& possmove : chessboard->PossibleMoves)
        {
            QGraphicsPixmapItem *img;

            // normal move graphic
            if (chessboard->chessbox[possmove.y][possmove.x]->getPiece() == nullptr)
                img = new QGraphicsPixmapItem(ImageManager::Move());
            // capture move graphic
            else
                img = new QGraphicsPixmapItem(ImageManager::Capture());

            img->setPos(possmove.x * GLOB::BoxSize, possmove.y * GLOB::BoxSize);
            PossibleMovesItems.push_back(img);
            scene->addItem(img);
        }
    }
}

// Hides possible moves for ActivePiece
void ChessBoardView::HidePossibleMoves()
{
    for (auto img : PossibleMovesItems)
    {
        scene->removeItem(img);
        delete img;
    }
    PossibleMovesItems.clear();
    chessboard->PossibleMoves.clear();
}

void ChessBoardView::ShowKingCheck()
{
    if(chessboard->getCurrentPlayerColor() == PieceColor::White)
        chessboard->WhiteKing->setPixmap(ImageManager::King_White_Danger());
    else
        chessboard->BlackKing->setPixmap(ImageManager::King_Black_Danger());
}

void ChessBoardView::HideKingCheck()
{
    if(chessboard->getCurrentPlayerColor() == PieceColor::White)
        chessboard->WhiteKing->setPixmap(ImageManager::King_White());
    else
        chessboard->BlackKing->setPixmap(ImageManager::King_Black());
}

void ChessBoardView::ShowPawnPromotion(ChessPiece* piece)
{
    pawnpromotion.pawn = piece;
    pawnpromotion.show(scene);
}

void ChessBoardView::HidePawnPromotion()
{
    pawnpromotion.pawn = nullptr;
    pawnpromotion.hide(scene);
}
void ChessBoardView::MoveActivePieceToMouse(QPoint point)
{
    chessboard->ActivePiece->setPos(point.x(), point.y());
}

void ChessBoardView::Clear()
{
    switch(GLOB::CurrentGameState)
    {
        case GameState::InPawnPromotion:
        {
            GLOB::CurrentGameState = GameState::Default;
            HidePawnPromotion();
            chessboard->DetectGameState();

        }break;
        case GameState::InCheck:
        {
            GLOB::CurrentGameState = GameState::Default;
            HideKingCheck();
        }break;
    }
}
