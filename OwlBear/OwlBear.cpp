// OwlBear.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "definitions.h"
#include "BoardState.h"
#include <iostream>

int main()
{
    BoardState testState;
    testState.side = white;
    for (int i = 31; i < 39; i++)
    {
        testState.board[i] = wP;
        testState.board[i + 50] = bP;
    }
    //testState.board[21] = wR;
    testState.board[22] = wN;
    testState.board[23] = wB;
    testState.board[24] = wQ;
    testState.board[25] = wK;
    testState.board[26] = wB;
    testState.board[27] = wN;
    //testState.board[28] = wR;

    testState.board[91] = bR;
    testState.board[92] = bN;
    testState.board[93] = bB;
    testState.board[94] = bQ;
    testState.board[95] = bK;
    testState.board[96] = bB;
    testState.board[97] = bN;
    testState.board[98] = bR;

    std::cout << testState.findLegalMoves().size() << "\n";
    return 0;
}
