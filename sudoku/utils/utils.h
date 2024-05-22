#ifndef UTILS_H_
#define UTILS_H_

#include "../sudoku-grid/sudoku_grid.h"

#define CHECK_BIT(var,pos) (((var) & (1<<(pos))) >> pos)

void print_sudoku(struct Sudoku_Grid* grid);
int validate_solution(struct Sudoku_Grid* grid);

#endif
