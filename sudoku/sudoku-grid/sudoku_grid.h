#ifndef SUDOKU_GRID_H
#define SUDOKU_GRID_H

#define SUDOKU_N 9
#define SUDOKU_SIZE SUDOKU_N * SUDOKU_N

struct Sudoku_Grid
{
    int grid[SUDOKU_SIZE];
    int possibilities_row[SUDOKU_N];
    int possibilities_col[SUDOKU_N];
    int possibilities_3x3[SUDOKU_N];
    int possibilities_cell[SUDOKU_SIZE];
};

void Sudoku_Grid_init(struct Sudoku_Grid* grid, int* data);

#endif
