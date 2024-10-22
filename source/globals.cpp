#include "../headers/globals.h"

namespace GLOB
{
    GameState CurrentGameState = GameState::Default;
    const int BoardHeight = 700;
    const int BoardWidth = 700;
    const int SideBarMenuHeight = BoardHeight;
    const int SideBarMenuWidth = BoxSize * 2;
    const int ViewHeight = BoardHeight;
    const int ViewWidth = BoardWidth + SideBarMenuWidth;
    const int BoxSize = BoardHeight / 8;
}



