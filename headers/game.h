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

enum GameState
{
    Default,
    PawnPromotion,
    Check,
    Checkmate,
    Draw
};

// Links all the components in the game.
class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent, PieceColor _PlayerColor);
    void start();

    static GameState gamestate;
private:
    ChessBoard *chessboard;
    GameView *view;
    QGraphicsScene *scene;
    PieceColor PlayerColor;

public slots:
    void restartGame();
    void exitGame();

    friend class GameView;
};

#endif // GAME_H
