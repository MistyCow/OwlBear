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
    // Perft Checking
    
    for (int i = 31; i < 39; i++)
    {
        testState.board[i] = wP;
        testState.board[i + 50] = bP;
    }
    testState.board[21] = wR;
    testState.board[22] = wN;
    testState.board[23] = wB;
    testState.board[24] = wQ;
    testState.board[25] = wK;
    testState.board[26] = wB;
    testState.board[27] = wN;
    testState.board[28] = wR;

    testState.board[91] = bR;
    testState.board[92] = bN;
    testState.board[93] = bB;
    testState.board[94] = bQ;
    testState.board[95] = bK;
    testState.board[96] = bB;
    testState.board[97] = bN;
    testState.board[98] = bR;
    
    std::vector<Move> legalMoves = testState.findLegalMoves();
    int perft = 0;
    for (int i = 0; i < legalMoves.size(); i++)
    {
        BoardState newState(testState.board, legalMoves[i], 1, white);
        std::vector<Move> newLegalMoves = newState.findLegalMoves();
        for (int j = 0; j < newLegalMoves.size(); j++)
        {
            BoardState veryNewState(newState.board, newLegalMoves[j], 2, black);
            std::vector<Move> veryNewLegalMoves = veryNewState.findLegalMoves();
            for (int k = 0; k < veryNewLegalMoves.size(); k++)
            {
                BoardState vvNewState(veryNewState.board, veryNewLegalMoves[k], 3, white);
                perft += vvNewState.findLegalMoves().size();
            }
        }
    }
    std::cout << perft << "\n";
    std::cin >> perft;
    /*
    testState.board[21] = wR;
    testState.board[26] = wR;
    testState.board[27] = wK;
    testState.board[32] = wP;
    testState.board[33] = wP;
    testState.board[35] = wQ;
    testState.board[36] = wP;
    testState.board[37] = wP;
    testState.board[38] = wP;
    testState.board[41] = wP;
    testState.board[43] = wN;
    testState.board[44] = wP;
    testState.board[46] = wN;
    testState.board[53] = wB;
    testState.board[55] = wP;
    testState.board[57] = bB;
    testState.board[63] = bB;
    testState.board[65] = bP;
    testState.board[67] = wB;
    testState.board[71] = bP;
    testState.board[73] = bN;
    testState.board[74] = bP;
    testState.board[76] = bN;
    testState.board[82] = bP;
    testState.board[83] = bP;
    testState.board[85] = bQ;
    testState.board[86] = bP;
    testState.board[87] = bP;
    testState.board[88] = bP;
    testState.board[91] = bR;
    testState.board[96] = bR;
    testState.board[97] = bK;

    std::vector<Move> legalMoves = testState.findLegalMoves();
    int perft = 0;
    for (int i = 0; i < legalMoves.size(); i++)
    {
        BoardState newState(testState.board, legalMoves[i], 1, white);
        perft += newState.findLegalMoves().size();
    }
    std::cout << perft << "\n";*/
    return 0;
}
