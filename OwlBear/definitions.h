#pragma once

enum SquareState    // All the possible states of a square
{
    empty, 
    wP, wB, wN, wR, wQ, wK, 
    bP, bB, bN, bR, bQ, bK
};

struct Move
{
    int from;
    int to;
};