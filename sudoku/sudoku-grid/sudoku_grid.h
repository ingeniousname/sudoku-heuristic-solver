#ifndef SUDOKU_GRID_H
#define SUDOKU_GRID_H

#define NULL 0
#define SUDOKU_N 9
#define SUDOKU_SIZE SUDOKU_N * SUDOKU_N

struct Sudoku_Grid
{
    int grid[SUDOKU_SIZE];
    int possibilities[SUDOKU_SIZE];
};

void Sudoku_Grid_init(struct Sudoku_Grid* grid, int* data);

#endif
