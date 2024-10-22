#include "../headers/sidebarmenu.h"
#include "../headers/chessboard.h"
#include "../headers/globals.h"
#include <QDebug>
#include <QFont>
#include <QColor>

SideBarMenu::SideBarMenu(ChessBoard* _chessboard): chessboard(_chessboard)
{
    UndoBtn = new QGraphicsPixmapItem;
    RedoBtn = new QGraphicsPixmapItem;
    WhoseTurn = new QGraphicsTextItem;

    isUndoBtnBlocked = true;
    isRedoBtnBlocked = true;
}

void SideBarMenu::Initialize()
{
    // Create background and custom color for it
    QGraphicsRectItem* background = new QGraphicsRectItem(GLOB::BoardWidth, 0, GLOB::SideBarMenuWidth, GLOB::SideBarMenuHeight);
    background->setBrush(QBrush(QColor(92, 91, 90)));
    chessboard->scene->addItem(background);

    UndoBtn->setPixmap(ImageManager::Undo_Blocked());
    UndoBtn->setPos(GLOB::BoardWidth, GLOB::BoardHeight - GLOB::BoxSize);
    chessboard->scene->addItem(UndoBtn);

    RedoBtn->setPixmap(ImageManager::Redo_Blocked());
    RedoBtn->setPos(GLOB::BoardWidth + ImageManager::Redo().width(), GLOB::BoardHeight - GLOB::BoxSize);
    chessboard->scene->addItem(RedoBtn);

    WhoseTurn = new QGraphicsTextItem("Game Status");
    QFont WhoseTurnFont = WhoseTurn->font();
    WhoseTurnFont.setPointSize(20);
    WhoseTurn->setFont(WhoseTurnFont);
    WhoseTurn->setPos(GLOB::BoardWidth, 50); // added padding
    chessboard->scene->addItem(WhoseTurn);
}

void SideBarMenu::mousePressEvent(const QMouseEvent& event)
{
    QPoint clickedPos = event.pos();

    // checking for click on Undo/Redo btns
    if (!isUndoBtnBlocked && UndoBtn->boundingRect().contains(UndoBtn->mapFromParent(clickedPos)))
    {
        this->Undo();
        this->Update();
    }
    else if (!isRedoBtnBlocked && RedoBtn->boundingRect().contains(RedoBtn->mapFromParent(clickedPos)))
    {
        this->Redo();
        this->Update();
    }
}

void SideBarMenu::Update()
{
    // Changing the Turn description
    if(chessboard->getCurrentPlayerColor() == PieceColor::White)
        WhoseTurn->setPlainText("White's Turn");
    else
        WhoseTurn->setPlainText("Black's Turn");

    // Handling for UndoBtn
    if(chessboard->movemanager->moves.canUndo() == false)
    {
        isUndoBtnBlocked = true;
        UndoBtn->setPixmap(ImageManager::Undo_Blocked());
    }
    else
    {
        isUndoBtnBlocked = false;
        UndoBtn->setPixmap(ImageManager::Undo());
    }
    // Handling for RedoBtn
    if(chessboard->movemanager->moves.canRedo() == false)
    {
        isRedoBtnBlocked = true;
        RedoBtn->setPixmap(ImageManager::Redo_Blocked());
    }
    else
    {
        isRedoBtnBlocked = false;
        RedoBtn->setPixmap(ImageManager::Redo());
    }
}

void SideBarMenu::Undo()
{
    chessboard->movemanager->moves.onClickUndoBtn();
}

void SideBarMenu::Redo()
{
    chessboard->movemanager->moves.onClickRedoBtn();
}
