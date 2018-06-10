#pragma once

enum SquareState    // All the possible states of a square
{
    empty, 
    wP, wB, wN, wR, wQ, wK, 
    bP, bB, bN, bR, bQ, bK,
    illegal
};

struct Move
{
    Move(int fromIn, int toIn);
    int from;
    int to;
};

enum Side
{
    white, black
};