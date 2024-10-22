#ifndef MOVEMANAGER_H
#define MOVEMANAGER_H
#include "movesstack.h"
#include "movegenerator.h"

class ChessBoard;

class MoveManager
{
public:
    MoveManager(ChessBoard* _chessboard);
    MoveGenerator movegenerator;
    MovesStack moves;
    void Initialize();
private:

};

#endif // MOVEMANAGER_H
