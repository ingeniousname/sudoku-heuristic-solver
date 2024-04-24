#ifndef SUDOKU_SOLVER_SIMPLE_H
#define SUDOKU_SOLVER_SIMPLE_H

#include "../sudoku-grid/sudoku-grid.h"

void update_possibilities(struct Sudoku_Grid* grid, int value, int row, int col);

#endif
