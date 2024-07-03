#include <QGraphicsView>

#include "../headers/chessboardview.h"
#include "../headers/globals.h"
#include "../headers/chessboard.h"

ChessBoardView::ChessBoardView(ChessBoard* _chessboard): chessboard(_chessboard)
{}

// Shows possible moves for ActivePiece
void ChessBoardView::ShowPossibleMoves()
{
    if(chessboard->ActivePiece)
    {
        // clears previous shown moves
        HidePossibleMoves();

        chessboard->PossibleMoves = chessboard->ActivePiece->getValidMoves(*chessboard);
        chessboard->ActivePiece->ValidateIsKingCheckAfterMoves(*chessboard, chessboard->PossibleMoves);

        for (const auto& possmove : chessboard->PossibleMoves)
        {
            QGraphicsPixmapItem *img;
            if (chessboard->chessbox[possmove.y][possmove.x]->getPiece() == nullptr)
            {
                QPixmap pixmap(":/img/dot.png");
                pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
                img = new QGraphicsPixmapItem(pixmap);
            }
            else
            {
                QPixmap pixmap(":/img/kill.png");
                pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
                img = new QGraphicsPixmapItem(pixmap);
            }

            img->setPos(possmove.x * BoxSize, possmove.y * BoxSize);
            PossibleMovesImg.push_back(img);
            chessboard->scene->addItem(img);
        }
    }
}

// Hides possible moves for ActivePiece
void ChessBoardView::HidePossibleMoves()
{
    for (auto img : PossibleMovesImg)
    {
        chessboard->scene->removeItem(img);
        delete img;
    }
    PossibleMovesImg.clear();
    chessboard->PossibleMoves.clear();
}

void ChessBoardView::ShowKingCheck()
{
    if(chessboard->getCurrentPlayerColor() == PieceColor::White)
    {
        QPixmap pixmap(":/img/king_white_danger.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        chessboard->WhiteKing->setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/king_black_danger.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        chessboard->BlackKing->setPixmap(pixmap);
    }
}

void ChessBoardView::HideKingCheck()
{
    if(chessboard->getCurrentPlayerColor() == PieceColor::Black)
    {
        QPixmap pixmap(":/img/king_white.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        chessboard->WhiteKing->setPixmap(pixmap);
    }
    else
    {
        QPixmap pixmap(":/img/king_black.png");
        pixmap = pixmap.scaled(QSize(BoxSize, BoxSize), Qt::KeepAspectRatio);
        chessboard->BlackKing->setPixmap(pixmap);
    }
}

void ChessBoardView::MoveActivePieceToMouse(QPoint point)
{
    chessboard->ActivePiece->setPos(point.x(), point.y());
}


