#include "../headers/movegenerator.h"
#include "../headers/chessboard.h"

MoveGenerator::MoveGenerator(): chessboard(nullptr)
{}

void MoveGenerator::Initialize()
{
    // holds all positions on the board
    std::vector<BoardPosition> positions;

    // Initialize board positions
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            positions.push_back(BoardPosition{x, y});
        }
    }

    // adding all types of linear moves
    for (const auto& box : positions)
    {
        std::vector<BoardPosition> Up, Down, Left, Right, Up_Left, Up_Right, Down_Left, Down_Right;

        for (int i = 1; i < 8; ++i)
        {
            Up.push_back(BoardPosition{box.x, box.y - i}); // up
            Down.push_back(BoardPosition{box.x, box.y + i}); // down
            Left.push_back(BoardPosition{box.x - i, box.y}); // left
            Right.push_back(BoardPosition{box.x + i, box.y}); // right
            Up_Left.push_back(BoardPosition{box.x - i, box.y - i}); // up and left
            Up_Right.push_back(BoardPosition{box.x + i, box.y - i}); // up and right
            Down_Right.push_back(BoardPosition{box.x + i, box.y + i}); // down and right
            Down_Left.push_back(BoardPosition{box.x - i, box.y + i}); // down and left
        }

        targets[PieceCheck::Up][box] = ValidBox(Up);
        targets[PieceCheck::Down][box] = ValidBox(Down);
        targets[PieceCheck::Left][box] = ValidBox(Left);
        targets[PieceCheck::Right][box] = ValidBox(Right);
        targets[PieceCheck::Up_Left][box] = ValidBox(Up_Left);
        targets[PieceCheck::Up_Right][box] = ValidBox(Up_Right);
        targets[PieceCheck::Down_Right][box] = ValidBox(Down_Right);
        targets[PieceCheck::Down_Left][box] = ValidBox(Down_Left);
    }

    // adding all possible moves for every ChessPiece
    for (const auto& box : positions)
    {
        // Pawn
        switch(box.y)
        {
        case 1:
        {
            targets[PieceCheck::TopPawn][box] = ValidBox({
                {box.x, box.y + 1},
                {box.x, box.y + 2}
            });
            targets[PieceCheck::BotPawn][box] = ValidBox({
                {box.x, box.y - 1}
            });
        } break;
        case 6:
        {
            targets[PieceCheck::BotPawn][box] = ValidBox({
                {box.x, box.y - 1},
                {box.x, box.y - 2}
            });
            targets[PieceCheck::TopPawn][box] = ValidBox({
                {box.x, box.y + 1}
            });
        } break;
        default:
        {
            targets[PieceCheck::TopPawn][box] = ValidBox({
                {box.x, box.y + 1}
            });
            targets[PieceCheck::BotPawn][box] = ValidBox({
                {box.x, box.y - 1}
            });
        }
        }
        targets[PieceCheck::BotPawnCapt][box] = ValidBox({
            {box.x - 1, box.y - 1},
            {box.x + 1, box.y - 1}
        });
        targets[PieceCheck::TopPawnCapt][box] = ValidBox({
            {box.x - 1, box.y + 1},
            {box.x + 1, box.y + 1}
        });

        // Knight
        targets[PieceCheck::Knight][box] = ValidBox({
            {box.x + 2, box.y + 1}, {box.x + 2, box.y - 1},
            {box.x + 1, box.y + 2}, {box.x + 1, box.y - 2},
            {box.x - 2, box.y + 1}, {box.x - 2, box.y - 1},
            {box.x - 1, box.y + 2}, {box.x - 1, box.y - 2}
        });

        // Bishop
        targets[PieceCheck::Bishop][box] = targets[PieceCheck::Up_Left][box];
        targets[PieceCheck::Bishop][box].insert(
            targets[PieceCheck::Bishop][box].end(),
            targets[PieceCheck::Up_Right][box].begin(),
            targets[PieceCheck::Up_Right][box].end()
            );
        targets[PieceCheck::Bishop][box].insert(
            targets[PieceCheck::Bishop][box].end(),
            targets[PieceCheck::Down_Right][box].begin(),
            targets[PieceCheck::Down_Right][box].end()
            );
        targets[PieceCheck::Bishop][box].insert(
            targets[PieceCheck::Bishop][box].end(),
            targets[PieceCheck::Down_Left][box].begin(),
            targets[PieceCheck::Down_Left][box].end()
            );

        // Rook
        targets[PieceCheck::Rook][box] = targets[PieceCheck::Up][box];
        targets[PieceCheck::Rook][box].insert(
            targets[PieceCheck::Rook][box].end(),
            targets[PieceCheck::Down][box].begin(),
            targets[PieceCheck::Down][box].end()
            );
        targets[PieceCheck::Rook][box].insert(
            targets[PieceCheck::Rook][box].end(),
            targets[PieceCheck::Left][box].begin(),
            targets[PieceCheck::Left][box].end()
            );
        targets[PieceCheck::Rook][box].insert(
            targets[PieceCheck::Rook][box].end(),
            targets[PieceCheck::Right][box].begin(),
            targets[PieceCheck::Right][box].end()
            );

        // Queen
        targets[PieceCheck::Queen][box] = targets[PieceCheck::Bishop][box];
        targets[PieceCheck::Queen][box].insert(
            targets[PieceCheck::Queen][box].end(),
            targets[PieceCheck::Rook][box].begin(),
            targets[PieceCheck::Rook][box].end()
            );

        // King
        targets[PieceCheck::King][box] = ValidBox({
            {box.x, box.y - 1}, {box.x + 1, box.y - 1},
            {box.x + 1, box.y}, {box.x + 1, box.y + 1},
            {box.x, box.y + 1}, {box.x - 1, box.y + 1},
            {box.x - 1, box.y}, {box.x - 1, box.y - 1}
        });
        // King castling
        if(box.y == 0 || box.y == 7)
        {
            if(box.x == 3 || box.x == 4)
                targets[PieceCheck::Castling][box] = ValidBox({{box.x - 2, box.y}, {box.x + 2, box.y}});
        }
    }

}

/* Changes ptr to other ChessBoard obj.
   Use whenever need to Make new chessboard->
*/
void MoveGenerator::setChessBoard(const ChessBoard& _chessboard)
{
    this->chessboard = &_chessboard;
}

bool MoveGenerator::isChessBoxAttacked(const BoardPosition& currentPos)
{
    bool attackByPawn = false;
    bool attackByKnight = false;
    PieceColor currentColor = chessboard->getCurrentPlayerColor();

    // Knight
    attackByKnight = std::any_of(
        targets[PieceCheck::Knight][currentPos].begin(),
        targets[PieceCheck::Knight][currentPos].end(),
        [&](const BoardPosition& pos){
            const ChessPiece* piece = chessboard->getPieceAtBoardPos(pos);
            return piece != nullptr && piece->getType() == PieceType::KNIGHT && piece->getColor() != currentColor;
        });
    if(attackByKnight == true)
        return true;

    // Bishop
    for(const auto& pos : targets[PieceCheck::Bishop][currentPos])
    {
        const ChessPiece* piece = chessboard->getPieceAtBoardPos(pos);
        if(piece != nullptr && piece->getType() == PieceType::BISHOP && piece->getColor() != currentColor)
        {
                if(lineOfSight(getPathBetween(currentPos, pos)) == true)
                {
                    return true;
                }
        }
    }

    // Rook
    for(const auto& pos : targets[PieceCheck::Rook][currentPos])
    {
        const ChessPiece* piece = chessboard->getPieceAtBoardPos(pos);
        if(piece != nullptr && piece->getType() == PieceType::ROOK && piece->getColor() != currentColor)
        {
                if(lineOfSight(getPathBetween(currentPos, pos)) == true)
                {
                    return true;
                }
        }
    }

    // Queen
    for(const auto& pos : targets[PieceCheck::Queen][currentPos])
    {
        const ChessPiece* piece = chessboard->getPieceAtBoardPos(pos);

        if(piece != nullptr && piece->getType() == PieceType::QUEEN && piece->getColor() != currentColor)
        {
                if(lineOfSight(getPathBetween(currentPos, pos)) == true)
                {
                    return true;
                }
        }
    }

    // Pawn
    if(chessboard->getBottomPiecesColor() != currentColor)
    {
        attackByPawn = std::any_of(
            targets[PieceCheck::TopPawnCapt][currentPos].begin(),
            targets[PieceCheck::TopPawnCapt][currentPos].end(),
            [&](const BoardPosition& pos){
                const ChessPiece* piece = chessboard->getPieceAtBoardPos(pos);
                return piece != nullptr && piece->getType() == PieceType::PAWN && piece->getColor() != currentColor;
            });
    }
    else
    {
        attackByPawn = std::any_of(
            targets[PieceCheck::BotPawnCapt][currentPos].begin(),
            targets[PieceCheck::BotPawnCapt][currentPos].end(),
            [&](const BoardPosition& pos){
                const ChessPiece* piece = chessboard->getPieceAtBoardPos(pos);
                return piece != nullptr && piece->getType() == PieceType::PAWN && piece->getColor() != currentColor;
            });
    }
    if(attackByPawn == true)
        return true;

    // no enemy ChessPiece is attacking
    return false;
}

/*
    Detects wheter any enemy chesspiece is in King view
    By checking alerady computed moves (targets) for every ChessPiece
*/
bool MoveGenerator::isKingInCheck()
{
    const ChessPiece* CurrentKing = chessboard->getKing(chessboard->getCurrentPlayerColor());
    return isChessBoxAttacked(CurrentKing->getBoardpositon());
}

// checks wheter BoardPosiiton is in x[0-7], y[0-7] range
std::vector<BoardPosition> MoveGenerator::ValidBox(const std::vector<BoardPosition>& pos) const
{
    std::vector<BoardPosition> ValidBoxPos;
    for (const auto& p : pos)
    {
        if (p.x >= 0 && p.x < 8 && p.y >= 0 && p.y < 8)
        {
            ValidBoxPos.push_back(p);
        }
    }
    return ValidBoxPos;
}

MoveGenerator::PieceCheck MoveGenerator::getPathDirection(const BoardPosition& start, const BoardPosition& end) const
{
    if (end.x < start.x && end.y == start.y)
        return PieceCheck::Left;
    else if (end.x > start.x && end.y == start.y)
        return PieceCheck::Right;
    else if (end.x == start.x && end.y < start.y)
        return PieceCheck::Up;
    else if (end.x == start.x && end.y > start.y)
        return PieceCheck::Down;
    else if (end.x < start.x && end.y < start.y)
        return PieceCheck::Up_Left;
    else if (end.x > start.x && end.y < start.y)
        return PieceCheck::Up_Right;
    else if (end.x < start.x && end.y > start.y)
        return PieceCheck::Down_Left;
    else
        return PieceCheck::Down_Right;
}


/* returns the path between start and end */
std::vector<BoardPosition> MoveGenerator::getPathBetween(const BoardPosition& start, const BoardPosition& end) const
{
    std::vector<BoardPosition> path;

    const PieceCheck PathDirection = getPathDirection(start, end);
    const std::vector<BoardPosition>& temp = targets.at(PathDirection).at(start);

    auto it_start = temp.begin();
    auto it_end = std::find(temp.begin(), temp.end(), end);

    // Check whether a occurs before b
    if (it_start < it_end)
    {
        path.assign(it_start, it_end);
    }
    else
    {
        path.assign(it_end, it_start);
    }

    return path;
}

// returns is path between begin() and end() is clear e.g. no ChessPiece between them two
bool MoveGenerator::lineOfSight(const std::vector<BoardPosition>& path) const
{
    return std::all_of(path.begin(), path.end(), [&](const BoardPosition& pos) {
        return chessboard->getPieceAtBoardPos(pos) == nullptr;
    });
}

// returns all possible moves for given piece
std::vector<BoardPosition> MoveGenerator::getPossibleMoves(const ChessPiece& piece)
{
    switch(piece.getType())
    {
        case PieceType::PAWN:
        {
            std::vector<BoardPosition> possiblemoves;
            if(chessboard->getBottomPiecesColor() == piece.getColor())
            {
                possiblemoves = getValidMoves(piece.getBoardpositon(), PieceCheck::BotPawn);
                // checking for pawn capture
                for(const auto& move: targets[PieceCheck::BotPawnCapt][piece.getBoardpositon()])
                {
                    ChessPiece* piece = chessboard->getPieceAtBoardPos(move);
                    if(piece != nullptr && piece->getColor() != chessboard->getCurrentPlayerColor())
                        possiblemoves.push_back(move);
                }
            }
            else
            {
                possiblemoves = getValidMoves(piece.getBoardpositon(), PieceCheck::TopPawn);
                // checking for pawn capture
                for(const auto& move: targets[PieceCheck::TopPawnCapt][piece.getBoardpositon()])
                {
                    ChessPiece* piece = chessboard->getPieceAtBoardPos(move);
                    if(piece != nullptr && piece->getColor() != chessboard->getCurrentPlayerColor())
                        possiblemoves.push_back(move);
                }
            }
            return possiblemoves;
        }break;
        case PieceType::KNIGHT:
        {
            return getValidMoves(piece.getBoardpositon(), PieceCheck::Knight);
        }break;
        case PieceType::BISHOP:
        {
            return getValidMoves(piece.getBoardpositon(), PieceCheck::Bishop);
        }break;
        case PieceType::ROOK:
        {
            return getValidMoves(piece.getBoardpositon(), PieceCheck::Rook);
        }break;
        case PieceType::QUEEN:
        {
            return getValidMoves(piece.getBoardpositon(), PieceCheck::Queen);
        }break;
        case PieceType::KING:
        {
            std::vector<BoardPosition> possiblemoves;
            possiblemoves = getValidMoves(piece.getBoardpositon(), PieceCheck::King);

            // Check for Castling
            std::vector<BoardPosition> KingCastleMoves = getKingCastleMoves();
            if(!KingCastleMoves.empty())
            {
                possiblemoves.insert(possiblemoves.end(), KingCastleMoves.begin(),KingCastleMoves.end());
            }

            return possiblemoves;
        }break;
        default:
        {
            std::vector<BoardPosition> invalid_piece = {{0,0}};
            return invalid_piece;
        }
    }
}


// returns valid moves for every piece
//
// checks in std::map targets wheter move is legal
// and then returns legal moves
std::vector<BoardPosition> MoveGenerator::getValidMoves(BoardPosition pos, PieceCheck piececheck)
{
    // ensures that every move doesn't leads to capturing allie piece
    auto getLegalMoves = [&]() -> std::vector<BoardPosition>
    {
        std::vector <BoardPosition> score;
        for(const auto& move: targets[piececheck][pos])
        {
            ChessPiece* piece = chessboard->getPieceAtBoardPos(move);
            if(piece == nullptr)
                score.push_back(move);
            else
            {
                if(piece->getColor() != chessboard->getCurrentPlayerColor())
                    score.push_back(move);
            }
        }
        return score;
    };

    auto getClearDiagPath = [&]() -> std::vector<BoardPosition>
    {
        std::vector<BoardPosition> score;

        std::vector<std::vector<BoardPosition>> allPaths = {
            targets[PieceCheck::Up_Right][pos],
            targets[PieceCheck::Up_Left][pos],
            targets[PieceCheck::Down_Right][pos],
            targets[PieceCheck::Down_Left][pos]
        };

        for(const auto& path: allPaths)
        {
            for(const auto& move: path)
            {
                ChessPiece* piece = chessboard->getPieceAtBoardPos(move);
                if(piece == nullptr)
                    score.push_back(move);
                else
                {
                    if(piece->getColor() != chessboard->getCurrentPlayerColor())
                        score.push_back(move);
                    break;
                }
            }
        }
        return score;
    };

    auto getClearVertPath = [&]() -> std::vector<BoardPosition>
    {
        std::vector<BoardPosition> score;

        std::vector<std::vector<BoardPosition>> allPaths = {
            targets[PieceCheck::Up][pos],
            targets[PieceCheck::Down][pos],
            targets[PieceCheck::Left][pos],
            targets[PieceCheck::Right][pos]
        };

        for(const auto& path: allPaths)
        {
            for(const auto& move: path)
            {
                ChessPiece* piece = chessboard->getPieceAtBoardPos(move);
                if(piece == nullptr)
                    score.push_back(move);
                else
                {
                    if(piece->getColor() != chessboard->getCurrentPlayerColor())
                        score.push_back(move);
                    break;
                }
            }
        }
        return score;
    };
// ----------------------------------------------//
    std::vector<BoardPosition> ValidMoves;

    switch(piececheck)
    {
        case PieceCheck::BotPawn:
        {
            for(auto const& move: targets[PieceCheck::BotPawn][pos])
            {
                if(chessboard->getPieceAtBoardPos(move) == nullptr)
                    ValidMoves.push_back(move);
                else
                    return ValidMoves;
            }
        }break;
        case PieceCheck::TopPawn:
        {
            for(auto const& move: targets[PieceCheck::TopPawn][pos])
            {
                if(chessboard->getPieceAtBoardPos(move) == nullptr)
                    ValidMoves.push_back(move);
                else
                    return ValidMoves;
            }
        }break;
        case PieceCheck::Knight:
        case PieceCheck::King:
        {
            return getLegalMoves();
        }
        break;
        case PieceCheck::Bishop:
        {
            return getClearDiagPath();
        }break;
        case PieceCheck::Rook:
        {
            return getClearVertPath();
        }break;
        case PieceCheck::Queen:
        {
            ValidMoves = getClearDiagPath();
            std::vector<BoardPosition> VertPath = getClearVertPath();
            ValidMoves.insert(ValidMoves.end(), VertPath.begin(),VertPath.end());
        }break;
    }
    return ValidMoves;
}

/* Returns Castle moves for current King.
    1. Neither the king nor the rook has previously moved.
    2. There are no pieces between the king and the rook.
    3. The king is not currently in check.
    4. The king does not pass through or finish on a square that is attacked by an enemy piece
*/
std::vector<BoardPosition> MoveGenerator::getKingCastleMoves()
{
    const ChessPiece& CurrentKing = *chessboard->getKing(chessboard->getCurrentPlayerColor());
    std::vector<BoardPosition> castlingmoves;

    auto isLineAttacked = [&](std::vector<BoardPosition> LineToCheck) -> bool
    {
        for(const auto& box :LineToCheck)
        {
            if(isChessBoxAttacked(box) == true)
                return true;
        }
        return false;
    };

    if(CurrentKing.isFirstMove == true)
    {
        const ChessPiece* LeftRook = chessboard->getPieceAtBoardPos(BoardPosition(0, CurrentKing.getBoardpositon().y));
        const ChessPiece* RightRook = chessboard->getPieceAtBoardPos(BoardPosition(7, CurrentKing.getBoardpositon().y));
        GameState temp = GLOB::CurrentGameState;
        // left castling requirement
        if (LeftRook != nullptr)
        {
            std::vector<BoardPosition> PathBetweenRookKing = getPathBetween(CurrentKing.getBoardpositon(), LeftRook->getBoardpositon());
            if(LeftRook->getType() == PieceType::ROOK &&
                LeftRook->isFirstMove == true &&
                lineOfSight(PathBetweenRookKing) == true &&
                GLOB::CurrentGameState != GameState::InCheck &&
                isLineAttacked(PathBetweenRookKing) == false)
            {
                castlingmoves.push_back(BoardPosition{CurrentKing.getBoardpositon().x - 2, CurrentKing.getBoardpositon().y});
            }
        }
        // Right castling requirement
        if (RightRook != nullptr)
        {
            std::vector<BoardPosition> PathBetweenRookKing = getPathBetween(CurrentKing.getBoardpositon(), RightRook->getBoardpositon());
            if(RightRook->getType() == PieceType::ROOK &&
               RightRook->isFirstMove == true &&
               lineOfSight(PathBetweenRookKing) == true &&
               GLOB::CurrentGameState != GameState::InCheck &&
               isLineAttacked(PathBetweenRookKing) == false)
            {
                    castlingmoves.push_back(BoardPosition{CurrentKing.getBoardpositon().x + 2, CurrentKing.getBoardpositon().y});
            }
        }
    }
    return castlingmoves;
}
