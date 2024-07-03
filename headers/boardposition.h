#ifndef BOARDPOSITION_H
#define BOARDPOSITION_H

// holds cordinates to 8x8 chessboard in range [0-7]
struct BoardPosition
{
    int x,y;

    BoardPosition(int _x, int _y)
    {
        this->x = _x;
        this->y = _y;
    }

    bool operator==(const BoardPosition& position) const
    {
        return x == position.x && y == position.y;
    }
};

#endif // BOARDPOSITION_H
