#include "utils.h"
#include <stdio.h>

void print_sudoku(struct Sudoku_Grid* grid)
{
    for(int row = 0; row < SUDOKU_N; row++)
    {
        for(int col = 0; col < SUDOKU_N; col++)
            printf("%d ", grid->grid[row * SUDOKU_N + col]);
        printf("\n");
    }
    printf("\n");
}
