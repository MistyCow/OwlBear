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

        side = white;
        ply = 0;
    }
}

BoardState::BoardState(SquareState boardIn[120], int plyIn)
{
    std::copy(boardIn, boardIn + 120, board);
    ply = plyIn;
}

BoardState::BoardState(SquareState boardIn[120], Move moveIn, int oldPly, Side oldSide)
{
    std::copy(boardIn, boardIn + 120, board);

    board[moveIn.to] = board[moveIn.from];
    board[moveIn.from] = empty;

    ply = oldPly + 1;
    
    oldSide == white ? side = black : side = white;
}

std::vector<Move> BoardState::findPseudoLegalMoves()
{
    std::vector<Move> legalMoves;

    // White Moves
    if (side == white)
    {
        for (int i = 21; i < 99; i++)
        {
            // Check for sentry squares
            if (board[i] == illegal)
                continue;
         
            // And for empty squares
            if (board[i] == empty)
                continue;
            
            // White Pawns
            if (board[i] == wP)
            {
                // Forward movement
                if (board[i + 10] == empty)
                {
                    legalMoves.push_back(Move(i, i + 10));

                    // We can move two forward if we are on the second rank
                    if ((i > 30 && i < 39) && (board[i + 20] == empty))
                    {
                        legalMoves.push_back(Move(i, i + 20));
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
                    if (board[j] == illegal || board[j] <= 6)
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

                    if (board[j] == illegal || board[j] <= 6)
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

                    if (board[j] == illegal || board[j] <= 6)
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

                    if (board[j] == illegal || board[j] <= 6)
                    {
                        break;
                    }

                    if (board[j] > 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                continue;
            }

            // White Knights
            if (board[i] == wN)
            {
                if ((board[i - 21] == empty) || ((board[i - 21] > 6) && (board[i - 21] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 21));
                }
                if ((board[i - 19] == empty) || ((board[i - 19] > 6) && (board[i - 19] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 19));
                }
                if ((board[i - 12] == empty) || ((board[i - 12] > 6) && (board[i - 12] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 12));
                }
                if ((board[i - 8] == empty) || ((board[i - 8] > 6) && (board[i - 8] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 8));
                }
                if ((board[i + 8] == empty) || ((board[i + 8] > 6) && (board[i + 8] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 8));
                }
                if ((board[i + 12] == empty) || ((board[i + 12] > 6) && (board[i + 12] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 12));
                }
                if ((board[i + 19] == empty) || ((board[i + 19] > 6) && (board[i + 19] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 19));
                }
                if ((board[i + 21] == empty) || ((board[i + 21] > 6) && (board[i + 21] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 21));
                }
                continue;
            }
            
            // White Rook
            if (board[i] == wR)
            {
                for (int j = i - 10; j > 20; j -= 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i - 1; j > 20; j --)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 1; j < 99; j ++)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 10; j < 99; j += 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                continue;
            }

            // White Queen
            if (board[i] == wQ)
            {
                //Up Left
                for (int j = i - 11; j > 20; j -= 11)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] == illegal || board[j] <= 6)
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

                    if (board[j] == illegal || board[j] <= 6)
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

                    if (board[j] == illegal || board[j] <= 6)
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

                    if (board[j] == illegal || board[j] <= 6)
                    {
                        break;
                    }

                    if (board[j] > 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                for (int j = i - 10; j > 20; j -= 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i - 1; j > 20; j--)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 1; j < 99; j++)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 10; j < 99; j += 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] > 6 && board[j] < 13)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                continue;
            }

            // White King
            // TODO: Stop the king from walking into checks, or, if under check, avoid any moves that end with the king in check
            if (board[i] == wK)
            {
                if ((board[i - 11] == empty) || (board[i - 11] > 6 && board[i - 11] < 13))
                {
                    legalMoves.push_back(Move(i, i - 11));
                }
                if ((board[i - 10] == empty) || (board[i - 10] > 6 && board[i - 10] < 13))
                {
                    legalMoves.push_back(Move(i, i - 10));
                }
                if ((board[i - 9] == empty) || (board[i - 9] > 6 && board[i - 9] < 13))
                {
                    legalMoves.push_back(Move(i, i - 9));
                }
                if ((board[i - 1] == empty) || (board[i - 1] > 6 && board[i - 1] < 13))
                {
                    legalMoves.push_back(Move(i, i - 1));
                }
                if ((board[i + 1] == empty) || (board[i + 1] > 6 && board[i + 1] < 13))
                {
                    legalMoves.push_back(Move(i, i + 1));
                }
                if ((board[i + 9] == empty) || (board[i + 9] > 6 && board[i + 9] < 13))
                {
                    legalMoves.push_back(Move(i, i + 9));
                }
                if ((board[i + 10] == empty) || (board[i + 10] > 6 && board[i + 10] < 13))
                {
                    legalMoves.push_back(Move(i, i + 10));
                }
                if ((board[i + 11] == empty) || (board[i + 11] > 6 && board[i + 11] < 13))
                {
                    legalMoves.push_back(Move(i, i + 11));
                }
            }
        }
    }
    // Black Moves
    if (side == black)
    {
        for (int i = 21; i < 99; i++)
        {
            // Check for sentry squares
            if (board[i] == illegal)
                continue;

            // And for empty squares
            if (board[i] == empty)
                continue;

            // Black Pawns
            if (board[i] == bP)
            {
                // Forward movement
                if (board[i - 10] == empty)
                {
                    legalMoves.push_back(Move(i, i - 10));

                    // We can move two forward if we are on the second rank
                    if ((i > 80 && i < 99) && (board[i - 20] == empty))
                    {
                        legalMoves.push_back(Move(i, i - 20));
                    }
                }

                // Captures
                if ((board[i - 9] <= 6) && (board[i - 9] != empty))  // SquareState > 6 = blackSomething, 13 = sentry
                {
                    legalMoves.push_back(Move(i, i - 9));
                }

                if ((board[i - 11] <= 6) && (board[i - 11] != empty))
                {
                    legalMoves.push_back(Move(i, i - 11));
                }
                continue;
            }

            // Black Bishops
            if (board[i] == bB)
            {
                //Up Left
                for (int j = i - 11; j > 20; j -= 11)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }
                    if (board[j] <= 6)
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

                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }

                    if (board[j] <= 6)
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

                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }

                    if (board[j] <= 6)
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

                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }

                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                continue;
            }

            // Black Knights
            if (board[i] == bN)
            {
                if ((board[i - 21] == empty) || ((board[i - 21] <= 6) && (board[i - 21] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 21));
                }
                if ((board[i - 19] == empty) || ((board[i - 19] <= 6) && (board[i - 19] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 19));
                }
                if ((board[i - 12] == empty) || ((board[i - 12] <= 6) && (board[i - 12] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 12));
                }
                if ((board[i - 8] == empty) || ((board[i - 8] <= 6) && (board[i - 8] != illegal)))
                {
                    legalMoves.push_back(Move(i, i - 8));
                }
                if ((board[i + 8] == empty) || ((board[i + 8] <= 6) && (board[i + 8] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 8));
                }
                if ((board[i + 12] == empty) || ((board[i + 12] <= 6) && (board[i + 12] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 12));
                }
                if ((board[i + 19] == empty) || ((board[i + 19] <= 6) && (board[i + 19] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 19));
                }
                if ((board[i + 21] == empty) || ((board[i + 21] <= 6) && (board[i + 21] != illegal)))
                {
                    legalMoves.push_back(Move(i, i + 21));
                }
                continue;
            }

            // Black Rook
            if (board[i] == bR)
            {
                for (int j = i - 10; j > 20; j -= 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i - 1; j > 20; j--)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 1; j < 99; j++)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 10; j < 99; j += 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                continue;
            }

            // Black Queen
            if (board[i] == bQ)
            {
                // Diagonal Bishop-like movement
                // Up Left
                for (int j = i - 11; j > 20; j -= 11)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                // Up Right
                for (int j = i - 9; j > 20; j -= 9)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }

                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }

                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                // Down Left
                for (int j = i + 9; j < 99; j += 9)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }

                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }

                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                // Down Right
                for (int j = i + 11; j > 20; j += 11)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }

                    if (board[j] == illegal || board[j] > 6)
                    {
                        break;
                    }

                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                }
                // Lateral Rook-Like Movement
                for (int j = i - 10; j > 20; j -= 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i - 1; j > 20; j--)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 1; j < 99; j++)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                for (int j = i + 10; j < 99; j += 10)
                {
                    if (board[j] == empty)
                    {
                        legalMoves.push_back(Move(i, j));
                        continue;
                    }
                    if (board[j] <= 6)
                    {
                        legalMoves.push_back(Move(i, j));
                        break;
                    }
                    // Else
                    break;
                }
                continue;
            }

            // Black King
            // TODO: Stop the king from walking into checks, or, if under check, avoid any moves that end with the king in check
            if (board[i] == bK)
            {
                if ((board[i - 11] == empty) || (board[i - 11] <= 6))
                {
                    legalMoves.push_back(Move(i, i - 11));
                }
                if ((board[i - 10] == empty) || (board[i - 10] <= 6))
                {
                    legalMoves.push_back(Move(i, i - 10));
                }
                if ((board[i - 9] == empty) || (board[i - 9] <= 6))
                {
                    legalMoves.push_back(Move(i, i - 9));
                }
                if ((board[i - 1] == empty) || (board[i - 1] <= 6))
                {
                    legalMoves.push_back(Move(i, i - 1));
                }
                if ((board[i + 1] == empty) || (board[i + 1] <= 6))
                {
                    legalMoves.push_back(Move(i, i + 1));
                }
                if ((board[i + 9] == empty) || (board[i + 9] <= 6))
                {
                    legalMoves.push_back(Move(i, i + 9));
                }
                if ((board[i + 10] == empty) || (board[i + 10] <= 6))
                {
                    legalMoves.push_back(Move(i, i + 10));
                }
                if ((board[i + 11] == empty) || (board[i + 11] <= 6))
                {
                    legalMoves.push_back(Move(i, i + 11));
                }
            }
        }
    }

    return legalMoves;
}

// Prunes pseudoLegalMoves for any checks shenanigans
std::vector<Move> BoardState::findLegalMoves()
{

    std::vector<Move> pseudoLegalMoves = findPseudoLegalMoves();
    std::vector<Move> legalMoves;
    for (int i = 0; i < pseudoLegalMoves.size(); i++)
    {
        if (!BoardState(board, pseudoLegalMoves[i], ply, side).inCheck())
        {
            legalMoves.push_back(pseudoLegalMoves[i]);
        }
    }

    return legalMoves;
}

bool BoardState::isKingPresent()
{
    int offset = 0;
    if (side == black)
        offset = 6;

    for (int i = 21; i < 99; i++)
    {
        if (board[i] == wK + offset)
            return true;
    }
    return false;
}

bool BoardState::inCheck()
{
    side == white ? side = black : side = white; // We have to check possible enemy moves if we didn't do anything
    std::vector<Move> enemyMoves = findPseudoLegalMoves();
    side == white ? side = black : side = white; // After we have the moves we set the side back

    for (int i = 0; i < enemyMoves.size(); i++)
    {
        if (!BoardState(board, enemyMoves[i], ply, side).isKingPresent()) // We check if our king has been captured
            return true;
    }
    return false;
}

float BoardState::evaluate()
{
    float value = 0;

    for (int i = 21; i < 99; i++)
    {
        value += pieceValues[board[i]];
    }
    return value;
}
