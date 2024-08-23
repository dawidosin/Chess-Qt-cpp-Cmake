#include "../headers/game.h"
#include "../headers/globals.h"

Game::Game(QWidget *parent = nullptr, PieceColor _PlayerColor = PieceColor::White) : QMainWindow(parent),
    scene(new QGraphicsScene(this)), view(new GameView(this)), PlayerColor(_PlayerColor)
{}

GameState Game::gamestate = GameState::Default;

void Game::start()
{
    // Adding the view as the central widget
    setCentralWidget(view);
    setFixedSize(ViewWidth, ViewHeight); 
    scene->setSceneRect(0, 0, ViewWidth, ViewHeight);
    setMouseTracking(true);

    // Configuring the view's scroll bar policies
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->viewport()->setMouseTracking(true);

    //Creating and Initializing the chessboard and setting it's scene
    chessboard = new ChessBoard(scene, PlayerColor);
    chessboard->InitializeBoard();
    view->setScene(scene);
}

void Game::restartGame()
{
    delete chessboard;
    chessboard = new ChessBoard(scene, PlayerColor);
    chessboard->InitializeBoard();
    Game::gamestate = GameState::Default;

    view->gameEndDialog->accept();
    delete view->gameEndDialog;
}

void Game::exitGame()
{
    view->gameEndDialog->accept();
    delete view->gameEndDialog;
    Game::gamestate = GameState::Default;

    QApplication::quit();
}


