#ifndef SUDOKU_HEURISTICS_H
#define SUDOKU_HEURISTICS_H

#include "../sudoku-grid/sudoku_grid.h"
#include "../utils/utils.h"

typedef struct Heuristic_Opts
{
	int use_MRV;
	int use_NP;
	int use_LCV;
} Heuristic_Opts;

int find_MRV_idx(struct Sudoku_Grid* grid);
void apply_naked_pairs(struct Sudoku_Grid* grid, int row, int col);
void sort_LCV_values(int* values, struct Sudoku_Grid* grid, int row, int col);
void check_constraints(int* values, int* value_consts, int possibilities);

#endif
