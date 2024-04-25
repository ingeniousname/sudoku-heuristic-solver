#include "sudoku_grid.h"
#include <string.h>
#include "../solver/sudoku_solver_simple.h"

void Sudoku_Grid_init(struct Sudoku_Grid* grid, int* data)
{
	for (int i = 0; i < SUDOKU_N; i++)
	{
		grid->possibilities_row[i] = (1 << (SUDOKU_N + 1)) - 1;
		grid->possibilities_col[i] = (1 << (SUDOKU_N + 1)) - 1;
		grid->possibilities_3x3[i] = (1 << (SUDOKU_N + 1)) - 1; 
	}
    
    if(data != NULL)
    {
        memcpy(grid->grid, data, sizeof(int) * 81);

        for(int row = 0; row < SUDOKU_N; row++)
            for(int col = 0; col < SUDOKU_N; col++)
                remove_possibilities(grid, grid->grid[row * SUDOKU_N + col], row, col);
    }
}
