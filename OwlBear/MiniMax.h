#pragma once
#include "definitions.h"
#include "BoardState.h"

class MiniMax
{
public:
    MiniMax();
    Move findBestMove(BoardState board, int depth);
};

