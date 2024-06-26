#ifndef SUDOKU_SOLVER_HEURISTICS_H
#define SUDOKU_SOLVER_HEURISTICS_H

#include "../sudoku-grid/sudoku_grid.h"
#include "sudoku_heuristics.h"

#define USE_MRV 1

int Sudoku_Grid_solve_heuristics_single_answer(struct Sudoku_Grid* grid, int opt);
int Sudoku_Grid_solve_heuristics_single_answer_aux(struct Sudoku_Grid* grid, int row, int col, Heuristic_Opts opts);
int find_next_idx(struct Sudoku_Grid* grid, int row, int col, int use_MRV);
void find_box_values(int* values, struct Sudoku_Grid* grid, int row, int col, int use_LCV);

#endif