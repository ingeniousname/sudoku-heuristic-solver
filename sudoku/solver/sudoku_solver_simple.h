#ifndef SUDOKU_SOLVER_SIMPLE_H
#define SUDOKU_SOLVER_SIMPLE_H

#include "../sudoku-grid/sudoku_grid.h"


void remove_possibilities(struct Sudoku_Grid* grid, int value, int row, int col);
void add_possibilities(struct Sudoku_Grid* grid, int value, int row, int col);

int Sudoku_Grid_solve_simple_single_answer(struct Sudoku_Grid* grid);
int Sudoku_Grid_solve_simple_single_answer_aux(struct Sudoku_Grid* grid, int row, int col);

#endif
