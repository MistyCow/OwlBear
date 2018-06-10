#include "stdafx.h"
#include "BoardState.h"

BoardState::BoardState()
{
    for (int i = 0; i < 120; i++)
    {
        // First we set up the sentry squares
        if (i < 20 || i > 100)
        {
            board[i] = illegal;
            continue;
        }

        if ((i && 10 == 1) || (i && 10 == 0))
        {
            board[i] = illegal;
            continue;
        }
        // If none of the conditions apply, we set it as empty
        board[i] = empty;
    }
}

BoardState::BoardState(SquareState boardIn[120], int plyIn)
{
    *board = *boardIn;
    ply = plyIn;
}

std::vector<Move> BoardState::findLegalMoves()
{
    std::vector<Move> legalMoves;

    // White Moves
    if (side == white)
    {
        for (int i = 21; i < 98; i++)
        {
            // Check for sentry squares
            if (board[i] == illegal)
                continue;

            // White Pawns
            if (board[i] == wP)
            {
                // Forward movement
                if (board[i + 8] == empty)
                {
                    legalMoves.push_back(Move(i, i + 8));

                    // We can move two forward if we are on the second rank
                    if ((i % 10 == 4) && (board[i + 20] == empty))
                    {
                        legalMoves.push_back(Move(i, i + 16));
                    }
                }

                // Captures
                if ((board[i + 9] > 6) && (board[i + 9] < 13))  // SquareState > 6 = blackSomething, 13 = sentry
                {
                    legalMoves.push_back(Move(i, i + 9));
                }

                if ((board[i + 11] > 6) && (board[i + 9] < 13))
                {
                    legalMoves.push_back(Move(i, i + 11));
                }
            }

             
        }
    }

    return legalMoves;
}
