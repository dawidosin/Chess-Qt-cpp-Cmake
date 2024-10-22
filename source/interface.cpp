#include "../headers/interface.h"
#include "../headers/chessboard.h"

Interface::Interface(ChessBoard* _chessboard): chessboard(_chessboard)
{
    // Creating and Initializing the SideBarMenu
    sidebarmenu = new SideBarMenu(_chessboard);
}

void Interface::Initialize()
{
    sidebarmenu->Initialize();
    sidebarmenu->Update();
}
