// OwlBear.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "definitions.h"
#include "BoardState.h"
#include <iostream>

int main()
{
    BoardState testState;
    //testState.board[21] = wQ;
    testState.board[25] = wP;
    testState.board[35] = wK;
    testState.side = white;
    std::cout << testState.findLegalMoves().size() << "\n";
    return 0;
}
