#include "sudoku_solver_simple.h"

void remove_possibilities(struct Sudoku_Grid* grid, int value, int row, int col)
{
    int value_mask = 1 << value;
    for(int i = 0; i < SUDOKU_N; i++)
    {
        grid->possibilities[row * SUDOKU_N + i] -= value_mask;
        grid->possibilities[i * SUDOKU_N + col] -= value_mask;
    }
    grid->possibilities[row * SUDOKU_N + col] += value_mask;
}

void add_possibilities(struct Sudoku_Grid* grid, int value, int row, int col)
{
    int value_mask = 1 << value;
    for(int i = 0; i < SUDOKU_N; i++)
    {
        grid->possibilities[row * SUDOKU_N + i] |= value_mask;
        grid->possibilities[i * SUDOKU_N + col] |= value_mask;
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
    
    for(int i = 1, mask = 2; i < SUDOKU_N; i++, mask <<= 1)
    {
        if((grid->possibilities[row * SUDOKU_N + col] & mask) != 0)
        {
            remove_possibilities(grid, i, row, col);
            if(Sudoku_Grid_solve_simple_single_answer_aux(grid, row, col + 1))
                return 1;
            add_possibilities(grid, i, row, col);
        }
    }
    return 0;
}
