#include "sudoku_solver_simple.h"

void remove_possibilities(struct Sudoku_Grid* grid, int value, int row, int col)
{
    int value_mask = 1 << value;
    for(int i = 0; i < SUDOKU_N; i++)
    {
        grid[row * SUDOKU_N + i] -= value_mask;
        grid[i * SUDOKU_N + col] -= value_mask;
    }
}
