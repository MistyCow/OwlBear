#include "stdafx.h"
#include "MiniMax.h"


MiniMax::MiniMax()
{}

Move MiniMax::findBestMove(BoardState board, int depth)
{
    std::vector <Move> legalMoves = board.findLegalMoves();
    float bestEvaluation = 0.f;
    if (board.side == white)
        bestEvaluation = -99999.f;
    else bestEvaluation = 99999.f;

    Move bestMove(0, 0, illegal);

    // Exit Condition, actual evaluation
    if (depth == 0)
    {
        // Finds the best move
        for (int i = 0; i < legalMoves.size(); i++)
        {
            BoardState curBoard(board.board, legalMoves[i], board.ply, board.side);
            int curEval = curBoard.evaluate();

            if ((board.side == white && curEval > bestEvaluation) || (board.side == black && curEval < bestEvaluation))
            {
                bestEvaluation = curEval;
                bestMove = legalMoves[i];
            }
        }
        bestMove.eval = bestEvaluation;
        // Returns it
        return bestMove;
    }
    // Else, recursive call
    for (int i = 0; i < legalMoves.size(); i++)
    {
        BoardState curBoard(board.board, legalMoves[i], board.ply, board.side);
        Move curMove = findBestMove(curBoard, depth - 1);
        if ((board.side == white && curMove.eval > bestEvaluation) || (board.side == black && curMove.eval < bestEvaluation))
        {
            bestEvaluation = curMove.eval;
            bestMove = curMove;-
        }
    }
    

}