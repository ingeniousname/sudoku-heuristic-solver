#include "sudoku_solver_simple.h"
#include "../utils/utils.h"

void remove_possibilities(struct Sudoku_Grid* grid, int value, int row, int col)
{
    int value_mask = 1 << value;
    grid->possibilities_row[row] &= ~value_mask;
    grid->possibilities_col[col] &= ~value_mask;
    grid->possibilities_3x3[(row / 3) * 3 + col / 3] &= ~value_mask;
    update_cell_possibilities(grid, row, col);
}

void add_possibilities(struct Sudoku_Grid* grid, int value, int row, int col)
{
    int value_mask = 1 << value;
    grid->possibilities_row[row] |= value_mask;
    grid->possibilities_col[col] |= value_mask;
    grid->possibilities_3x3[(row / 3) * 3 + col / 3] |= value_mask;
    update_cell_possibilities(grid, row, col);
}

void update_cell_possibilities(struct Sudoku_Grid* grid, int row, int col)
{
    for (int i = 0; i < SUDOKU_N; ++i)
    {
        grid->possibilities_cell[row * SUDOKU_N + i] = grid->possibilities_row[row] & grid->possibilities_col[i] & grid->possibilities_3x3[(row / 3) * 3 + i / 3];
        grid->possibilities_cell[i * SUDOKU_N + col] = grid->possibilities_row[i] & grid->possibilities_col[col] & grid->possibilities_3x3[(i / 3) * 3 + col / 3];
    }
}

int Sudoku_Grid_solve_simple_single_answer(struct Sudoku_Grid* grid)
{
    return Sudoku_Grid_solve_simple_single_answer_aux(grid, 0, 0);
}

int Sudoku_Grid_solve_simple_single_answer_aux(struct Sudoku_Grid* grid, int row, int col)
{
    if(col >= SUDOKU_N)
    {
        col = 0;
        row++;
    }

    if(row >= SUDOKU_N)
        return 1;

    if(grid->grid[row * SUDOKU_N + col])
        return Sudoku_Grid_solve_simple_single_answer_aux(grid, row, col + 1);

    int grid_tmp[SUDOKU_SIZE];
    apply_hidden_pairs(grid, row, col);
    apply_naked_pairs(grid, row, col);
    int possibilities = grid->possibilities_cell[row * SUDOKU_N + col] >> 1;
    int value = 1;
    while (possibilities)
    {
        if (possibilities & 1)
        {
            remove_possibilities(grid, value, row, col);
            grid->grid[row * SUDOKU_N + col] = value;
            if (Sudoku_Grid_solve_simple_single_answer_aux(grid, row, col + 1))
                return 1;
            grid->grid[row * SUDOKU_N + col] = 0;
            add_possibilities(grid, value, row, col);
        }
        value++;
        possibilities >>= 1;
    }
    return 0;
}
