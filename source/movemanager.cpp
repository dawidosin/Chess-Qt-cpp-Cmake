#include "../headers/movemanager.h"

MoveManager::MoveManager(ChessBoard* _chessboard): moves(_chessboard)
{
    movegenerator.setChessBoard(*_chessboard);
}

void MoveManager::Initialize()
{
    this->movegenerator.Initialize();
}
