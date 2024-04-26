#include "parser/parser.h"
#include "solver/sudoku_solver_simple.h"
#include "utils/utils.h"



int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 3)
        return -1;
    struct Sudoku_Grid grid = parse_from_string(argv[1]);
    Sudoku_Grid_solve_simple_single_answer(&grid);
    // useful for speed testing
    if(argc == 2)
        print_sudoku(&grid);
    
	return 0;

}
