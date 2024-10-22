#ifndef GLOBALS_H
#define GLOBALS_H

class MoveGenerator;

enum class PieceType
{
    NONE, KING, QUEEN, ROOK, BISHOP, KNIGHT, PAWN
};
enum class PieceColor
{
    Black, White
};
enum class GameState
{
    Default, Check, InCheck, Checkmate, Draw,
    PawnPromotion, InPawnPromotion, AfterPawnPromotion,
};

// global variables
namespace GLOB
{
    extern GameState CurrentGameState;

    extern const int BoardHeight;
    extern const int BoardWidth;
    extern const int SideBarMenuHeight;
    extern const int SideBarMenuWidth;
    extern const int ViewHeight;
    extern const int ViewWidth;
    extern const int BoxSize;
}

#endif // GLOBALS_H
