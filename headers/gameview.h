#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

#include "gameenddialog.h"

class Game;

class GameView : public QGraphicsView
{
public:
    GameView(const Game* _game);
    GameEndDialog* gameEndDialog = nullptr;
private:
    const Game* game;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // GAMEVIEW_H
