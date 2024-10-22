#ifndef INTERFACE_H
#define INTERFACE_H
#include "sidebarmenu.h"

class ChessBoard;

class Interface
{
public:
    Interface(ChessBoard* _chessboard);
    SideBarMenu* sidebarmenu;
    void Initialize();
private:
    ChessBoard* chessboard;
};

#endif // INTERFACE_H
