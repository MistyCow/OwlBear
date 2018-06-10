#pragma once
#include "definitions.h"

struct BoardState
{
public:
    BoardState();
    BoardState(SquareState boardIn[], int plyIn);

    SquareState board[64]; // An 8x8 board
    int ply;

};