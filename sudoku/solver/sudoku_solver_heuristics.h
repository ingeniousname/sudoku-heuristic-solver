#ifndef SUDOKU_SOLVER_HEURISTICS_H
#define SUDOKU_SOLVER_HEURISTICS_H

#include "../sudoku-grid/sudoku_grid.h"
#define USE_MRV 1

int Sudoku_Grid_solve_heuristics_single_answer(struct Sudoku_Grid* grid);
int Sudoku_Grid_solve_heuristics_single_answer_aux(struct Sudoku_Grid* grid, int row, int col);
int find_next_idx(struct Sudoku_Grid* grid, int row, int col);

#endif