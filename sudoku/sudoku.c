#include <stdio.h>
#include "parser/parser.h"
#include "solver/sudoku_solver_simple.h"
#include "utils/utils.h"


int main()
{
	printf("Hello cmake!\n");
    struct Sudoku_Grid grid = parse_from_file("sample_sudoku.txt");
    Sudoku_Grid_solve_simple_single_answer(&grid);
    print_sudoku(&grid);
    
	return 0;

}
