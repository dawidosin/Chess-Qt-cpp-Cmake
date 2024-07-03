#ifndef GAME_H
#define GAME_H

#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QWidget>
#include <QMouseEvent>

#include "chessbox.h"
#include "chessboard.h"
#include "gameview.h"
/*
    Links all the components in the game.
*/
class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent, PieceColor _PlayerColor);
    void start();
    GameView *view;
    ~Game() {}
private:
    ChessBoard *chessboard;
    QGraphicsScene *scene;
    PieceColor PlayerColor;

    friend class GameView;
};

#endif // GAME_H
