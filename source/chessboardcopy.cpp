#include "../headers/chessboardcopy.h"
#include "../headers/globals.h"
#include "../headers/movegenerator.h"


ChessBoardCopy::ChessBoardCopy(ChessBoard& other): originalBoard(other)
{
    // copying values
    this->scene = nullptr;
    this->PlayerColor = other.PlayerColor;
    this->movemanager = other.movemanager;

    // setting movegenerator and moves to our chessboardcopy
    this->movemanager->movegenerator.setChessBoard(*this);
    this->movemanager->moves.setChessBoard(*this);

    // copying vectors of ChessPieces
    for (auto piece : other.WhitePiece)
    {
        this->WhitePiece.push_back(piece->clone());
    }
    for (auto piece : other.BlackPiece)
    {
        this->BlackPiece.push_back(piece->clone());
    }

    // copying 2d array of ChessBoxes
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            if((x + y) % 2 == 0)
                chessbox[y][x] = new ChessBox(Qt::lightGray, BoardPosition{x, y});
            else
                chessbox[y][x] = new ChessBox(Qt::darkGray, BoardPosition{x, y});
        }
    }

    // adding pieces to chessbox
    for (auto& piece : WhitePiece)
    {
        chessbox[piece->getBoardpositon().y][piece->getBoardpositon().x]->setPiece(piece);
    }
    for (auto& piece : BlackPiece)
    {
        chessbox[piece->getBoardpositon().y][piece->getBoardpositon().x]->setPiece(piece);
    }

    this->ActivePiece = this->getBoxAtBoardPosition(other.ActivePiece->getBoardpositon())->piece;
    this->WhiteKing =  this->getBoxAtBoardPosition(other.WhiteKing->getBoardpositon())->piece;
    this->BlackKing = this->getBoxAtBoardPosition(other.BlackKing->getBoardpositon())->piece;
}

ChessBoardCopy::~ChessBoardCopy()
{
    // Cleaning after ChessBoardCopy used movegenerator
    movemanager->movegenerator.setChessBoard(originalBoard);
    movemanager->moves.setChessBoard(originalBoard);

    delete boardview;

    // deleting objects
    for(int y = 0; y < 8; y++)
    {
        for(int x = 0; x < 8; x++)
        {
            delete chessbox[y][x];
        }
    }
    for (auto piece : WhitePiece)
        delete piece;
    for (auto piece : BlackPiece)
        delete piece;
}
// It's an overrided function cause it get's the curr color and uses BlackPiece vector and so on
// but the base class use opposite approach so if curr color is White it checks the WhitePiece vector
bool ChessBoardCopy::isKingInCheck() const
{
    return movemanager->movegenerator.isKingInCheck();
}

PieceColor ChessBoardCopy::getCurrentPlayerColor() const
{
    if(movemanager->moves.size() % 2 == 0 || movemanager->moves.canUndo() == false)
        return PieceColor::Black;
    else
        return PieceColor::White;
}

void ChessBoardCopy::RemoveChessPiece(ChessPiece *PieceToRemove)
{
    // removing from the ChessBox
    ChessBox* RemovePieceBox = getBoxAtBoardPosition(PieceToRemove->getBoardpositon());
    RemovePieceBox->setPiece(nullptr);

    // removing from the vector
    if(PieceToRemove->getColor() == PieceColor::White)
    {
        auto it = std::remove(WhitePiece.begin(), WhitePiece.end(), PieceToRemove);
        if (it != WhitePiece.end())
            WhitePiece.erase(it, WhitePiece.end());
    }
    else
    {
        auto it = std::remove(BlackPiece.begin(), BlackPiece.end(), PieceToRemove);
        if (it != BlackPiece.end())
            BlackPiece.erase(it, BlackPiece.end());
    }

    delete PieceToRemove;
}

void ChessBoardCopy::AddChessPiece(ChessPiece* PieceToAdd, const BoardPosition& boardposition)
{
    // adding to ChessBox
    setPieceInBoardPos(PieceToAdd, boardposition);

    // adding to vector
    if(PieceToAdd->getColor() == PieceColor::White)
        WhitePiece.push_back(PieceToAdd);
    else
        BlackPiece.push_back(PieceToAdd);
}
