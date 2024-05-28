#ifndef SUDOKU_ITERATOR_H_
#define SUDOKU_ITERATOR_H_

int row_iterator_start(int row, int col);
int row_iterator_next(int row, int col, int index);
int row_iterator_end(int row, int col);


int col_iterator_start(int row, int col);
int col_iterator_next(int row, int col, int index);
int col_iterator_end(int row, int col);


int sq3x3_iterator_start(int row, int col);
int sq3x3_iterator_next(int row, int col, int index);
int sq3x3_iterator_end(int row, int col);


#endif