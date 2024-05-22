#ifndef SUDOKU_HEURISTICS_H
#define SUDOKU_HEURISTICS_H

#include "../sudoku-grid/sudoku_grid.h"

typedef struct Heuristic_Opts
{
	int use_MRV;
	int use_NP;
	int use_HP;
} Heuristic_Opts;

int find_MRV_idx(struct Sudoku_Grid* grid);
void apply_naked_pairs(struct Sudoku_Grid* grid, int row, int col);
void apply_hidden_pairs(struct Sudoku_Grid* grid, int row, int col);

#endif
