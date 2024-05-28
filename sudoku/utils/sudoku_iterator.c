#include "sudoku_iterator.h"
#include "../sudoku-grid/sudoku_grid.h"

int row_iterator_start(int row, int col)
{
	return row * SUDOKU_N;
}

int row_iterator_next(int row, int col, int index)
{
	return index + 1;
}

int row_iterator_end(int row, int col)
{
	return row * SUDOKU_N + SUDOKU_N;
}

int col_iterator_start(int row, int col)
{
	return col;
}

int col_iterator_next(int row, int col, int index)
{
	return index + SUDOKU_N;
}

int col_iterator_end(int row, int col)
{
	return SUDOKU_N * SUDOKU_N + col;
}

int sq3x3_iterator_start(int row, int col)
{
	return (row / 3) * 3 * SUDOKU_N + (col / 3) * 3;
}

int sq3x3_iterator_next(int row, int col, int index)
{
	int row_start = (row / 3) * 3;
	int col_start = (col / 3) * 3;

	int curr_col = (index % SUDOKU_N) + 1;
	if (curr_col > col_start + 2)
		index += SUDOKU_N - 2;
	else index++;

	return index;
}

int sq3x3_iterator_end(int row, int col)
{
	return ((row / 3) * 3 + 1) * SUDOKU_N + (col / 3) * 3;
}
