#include "stdafx.h"
#include "BoardState.h"

BoardState::BoardState()
{
    for (int i = 0; i < 64; i++)
    {
        board[i] = empty;
    }
}

BoardState::BoardState(SquareState boardIn[], int plyIn)
{
    *board = *boardIn;
    ply = plyIn;
}