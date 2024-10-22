#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>

#include "chessboard.h"
#include "interface.h"
#include "gameview.h"
#include "movesstack.h"
#include "movemanager.h"

// Links all the components in the game.
class Game : public QMainWindow
{
    Q_OBJECT
public:
    explicit Game(PieceColor _PlayerColor);
    void start();
public slots:
    void restartGame();
    void exitGame();
private:
    ChessBoard* chessboard;
    Interface* interface;
    GameView* view;
    QGraphicsScene* scene;
    PieceColor PlayerColor;
    MoveManager* movemanager;

    friend class GameView;
};

#endif // GAME_H
