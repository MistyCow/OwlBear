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

        if ((i % 10 == 0) || (i % 10 == 9))
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
                    if ((i > 30 && i < 39) && (board[i + 20] == empty))
                    {
                        legalMoves.push_back(Move(i, i + 16));
                    }
                }

                // Captures
                if ((board[i + 9] > 6) && (board[i + 9] < 13))  // SquareState > 6 = blackSomething, 13 = sentry
                {
                    legalMoves.push_back(Move(i, i + 9));
                }

                if ((board[i + 11] > 6) && (board[i + 11] < 13))
                {
                    legalMoves.push_back(Move(i, i + 11));
                }
                continue;
            }
            // White Bishops
            if (board[i] == wB)
            {
                //Up Left
                for (int j = i - 11; j > 20; j -= 11)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] == illegal)
                    {
                        break;
                    }
                    if (board[j] > 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                //Up Right
                for (int j = i - 9; j > 20; j -= 9)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }

                    if (board[j] == illegal)
                    {
                        break;
                    }

                    if (board[j] > 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                //Down Left
                for (int j = i + 9; j < 99; j += 9)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }

                    if (board[j] == illegal)
                    {
                        break;
                    }

                    if (board[j] > 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                //Down Right
                for (int j = i + 11; j > 20; j += 11)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }

                    if (board[j] == illegal)
                    {
                        break;
                    }

                    if (board[j] > 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
            }
             
        }
    }

    return legalMoves;
}
