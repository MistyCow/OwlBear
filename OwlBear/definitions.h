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
    Move(unsigned short fromIn, unsigned short toIn, SquareState capturesIn);
    unsigned short from;
    unsigned short to;
    SquareState captures;
    float eval;
};

enum Side
{
    white, black
};

