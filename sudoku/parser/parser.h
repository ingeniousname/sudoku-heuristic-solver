#ifndef PARSER_H
#define PARSER_H

#include "../sudoku-grid/sudoku_grid.h"

struct Sudoku_Grid parse_from_file(const char* filename);
struct Sudoku_Grid parse_from_string(const char* buffer);

#endif
