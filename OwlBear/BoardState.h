#pragma once
#include "definitions.h"

struct BoardState
{
public:
    BoardState();
    BoardState(SquareState boardIn[120], int plyIn);
    BoardState(SquareState boardIn[120], Move moveIn, int oldPly, Side oldSide);


    SquareState board[120]; // A 10x12 board
    int ply;
    
    std::vector<Move> findPseudoLegalMoves(); // Does not check for checks on the king
    std::vector<Move> findLegalMoves();
    

    bool isKingPresent();
    bool inCheck();

    Side side;
};