#ifndef SUDOKU_HEURISTICS_H
#define SUDOKU_HEURISTICS_H

#include "../sudoku-grid/sudoku_grid.h"

int find_MRV_idx(struct Sudoku_Grid* grid);
void apply_naked_pairs(struct Sudoku_Grid* grid, int row, int col);

#endif
