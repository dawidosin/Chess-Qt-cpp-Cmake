#ifndef SIDEBARMENU_H
#define SIDEBARMENU_H

#include <QWidget>
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QGraphicsView>

class ChessBoard;

class SideBarMenu : public QWidget
{
public:
    SideBarMenu(ChessBoard* _chessboard);
    void Initialize();
    void mousePressEvent(const QMouseEvent& event);
    void Update();
private slots:
    void Undo();
    void Redo();
    //void goMainMenu();
private:
    bool isUndoBtnBlocked;
    bool isRedoBtnBlocked;
    ChessBoard* chessboard;
    QGraphicsPixmapItem* UndoBtn;
    QGraphicsPixmapItem* RedoBtn;
    QGraphicsTextItem* WhoseTurn;
};

#endif // SIDEBARMENU_H
