#include "stdafx.h"
#include "BoardState.h"

BoardState::BoardState()
{}

BoardState::BoardState(SquareState boardIn[], int plyIn)
{
    *board = *boardIn;
    ply = plyIn;
}