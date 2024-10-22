#include "../headers/game.h"
#include "../headers/globals.h"

Game::Game(PieceColor _PlayerColor) : chessboard(nullptr), view(new GameView(this)),
    scene(new QGraphicsScene(this)), PlayerColor(_PlayerColor), movemanager(new MoveManager(nullptr))
{}

void Game::start()
{
    setFixedSize(GLOB::ViewWidth, GLOB::ViewHeight);
    scene->setSceneRect(0, 0, GLOB::ViewWidth, GLOB::ViewHeight);

    // Configuring the view's scroll bar policies
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->viewport()->setMouseTracking(true);
    view->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Creating the MoveManager
    movemanager = new MoveManager(nullptr);

    // Creating and Initializing the ChessBoard
    chessboard = new ChessBoard(movemanager, scene, PlayerColor);
    chessboard->Initialize();

    // Initializing the MoveManager
    movemanager->Initialize();

    // Creating and Initializing Interface
    interface = new Interface(chessboard);
    interface->Initialize();

    setMouseTracking(true);
    setCentralWidget(view);
    view->setScene(scene);
}

void Game::restartGame()
{
    delete chessboard;
    delete movemanager;

    chessboard = new ChessBoard(movemanager, scene, PlayerColor);
    chessboard->Initialize();
    GLOB::CurrentGameState = GameState::Default;

    view->gameEndDialog->accept();
    delete view->gameEndDialog;
}

void Game::exitGame()
{
    view->gameEndDialog->accept();
    delete view->gameEndDialog;
    GLOB::CurrentGameState = GameState::Default;

    QApplication::quit();
}

