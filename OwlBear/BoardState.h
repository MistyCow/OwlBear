#pragma once
#include "definitions.h"

struct BoardState
{
public:
    BoardState();
    BoardState(SquareState boardIn[120], int plyIn);
    BoardState(SquareState boardIn[120], Move moveIn, int oldPly, Side oldSide);

    const float pieceValues[14] = {
        0.f,1.f,3.f,3.f,5.f,9.f,999.f,
        -1.f,-3.f,-3.f,-5.f,-9.f,-999.f,0.f
    };

    SquareState board[120]; // A 10x12 board
    int ply;
    
    std::vector<Move> findPseudoLegalMoves(); // Does not check for checks on the king
    std::vector<Move> findLegalMoves();
    

    bool isKingPresent();
    bool inCheck();

    float evaluate();

    Side side;
};