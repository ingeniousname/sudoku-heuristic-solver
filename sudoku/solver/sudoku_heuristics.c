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

void print_sudoku2(struct Sudoku_Grid* grid)
{
    for (int row = 0; row < SUDOKU_N; row++)
    {
        for (int col = 0; col < SUDOKU_N; col++)
            printf("%d ", grid->grid[row * SUDOKU_N + col]);
        printf("\n");
    }
    printf("\n");

}

void apply_naked_pairs(struct Sudoku_Grid* grid, int row, int col)
{
    unsigned int cell_possibilities = grid->possibilities_cell[row * SUDOKU_N + col] >> 1;
    if (__popcnt(cell_possibilities) != 2)
        return;

    for (int i = 0; i < SUDOKU_N; ++i)
    {
        // check row
        if (i != col)
        {
            unsigned int possibilities = grid->possibilities_cell[row * SUDOKU_N + i] >> 1;
            int possibilites_count = __popcnt(possibilities);
            if (possibilites_count == 2 && possibilities == cell_possibilities)
            {
                // Found naked pair in row, eliminate other possibilities in the row
                for (int j = 0; j < SUDOKU_N; ++j)
                {
                    if (j != col && j != i && grid->grid[row * SUDOKU_N + j] == 0)
                    {
                        unsigned int other_possibilities = grid->possibilities_cell[row * SUDOKU_N + j] & (~cell_possibilities << 1);
                        grid->possibilities_cell[row * SUDOKU_N + j] = other_possibilities;
                    }
                }
            }
        }

        // check column
        if (i != row)
        {
            unsigned int possibilities = grid->possibilities_cell[i * SUDOKU_N + col] >> 1;
            int possibilites_count = __popcnt(possibilities);
            if (possibilites_count == 2 && possibilities == cell_possibilities)
            {
                // Found naked pair in column, eliminate other possibilities in the column
                for (int j = 0; j < SUDOKU_N; ++j)
                {
                    if (j != row && j != i && grid->grid[j * SUDOKU_N + col] == 0)
                    {
                        unsigned int other_possibilities = grid->possibilities_cell[j * SUDOKU_N + col] & (~cell_possibilities << 1);
                        grid->possibilities_cell[j * SUDOKU_N + col] = other_possibilities;
                    }
                }
            }
        }
    }

    // check block
    int start_row = row / 3 * 3;
    int start_col = col / 3 * 3;
    for (int i = start_col; i < start_col + 3; ++i)
    {
        for (int j = start_row; j < start_row + 3; ++j)
        {
            if (i != col && j != row)
            {
                unsigned int possibilities = grid->possibilities_cell[j * SUDOKU_N + i] >> 1;
                int possibilites_count = __popcnt(possibilities);
                if (possibilites_count == 2 && possibilities == cell_possibilities)
                {
                    for (int c = start_col; c < start_col + 3; ++c)
                    {
                        for (int r = start_row; r < start_row + 3; ++r)
                        {
                            if ((c == col && r == row) || (c == i && r == j) || grid->grid[r * SUDOKU_N + c] != 0)
                                continue;

                            unsigned int other_possibilities = grid->possibilities_cell[j * SUDOKU_N + col] & (~cell_possibilities << 1);
                            grid->possibilities_cell[r * SUDOKU_N + c] = other_possibilities;
                        }
                    }
                }
            }
        }
    }
}
