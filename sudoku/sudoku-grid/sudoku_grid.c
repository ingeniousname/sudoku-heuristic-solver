#include "sudoku_grid.h"
#include <string.h>
#include "../solver/sudoku_solver_simple.h"

void Sudoku_Grid_init(struct Sudoku_Grid* grid, int* data)
{
    if(data != NULL)
    {
        memcpy(grid->grid, data, sizeof(int) * 81);
        for(int row = 0; row < SUDOKU_N; row++)
            for(int col = 0; col < SUDOKU_N; col++)
                remove_possibilities(grid, grid->grid[row * SUDOKU_N + col], row, col);
    }
    else
    {
        
        for(int row = 0; row < SUDOKU_N; row++)
            for(int col = 0; col < SUDOKU_N; col++)
            {
                grid->grid[row * SUDOKU_N + col] = 0;
                grid->possibilities[row * SUDOKU_N + col] = (1 << (SUDOKU_N + 1)) - 1;
            }
    }
}
