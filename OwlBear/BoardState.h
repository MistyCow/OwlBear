#pragma once
#include "definitions.h"

struct BoardState
{
public:
    BoardState();
    BoardState(SquareState boardIn[120], int plyIn);

    SquareState board[120]; // A 10x12 board
    int ply;

    std::vector<Move> findLegalMoves();

    Side side;
};