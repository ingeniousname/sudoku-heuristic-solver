#include "sudoku_solver_heuristics.h"

int find_MRV_idx(struct Sudoku_Grid* grid)
{
    int min_idx = -1, min_val = 10;
    for (int row = 0; row < SUDOKU_N; row++)
    {
        for (int col = 0; col < SUDOKU_N; col++)
        {
            if (grid->grid[row * SUDOKU_N + col])
                continue;
            int possibilities = grid->possibilities_row[row] & grid->possibilities_col[col] & grid->possibilities_3x3[(row / 3) * 3 + col / 3];
            int count = count_mask_bits(possibilities);

            if (count < min_val)
            {
                min_idx = row * SUDOKU_N + col;
                min_val = count;
            }
        }
    }
    return min_idx;
}