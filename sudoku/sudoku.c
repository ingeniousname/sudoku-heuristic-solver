#include "parser/parser.h"
#include "solver/sudoku_solver_simple.h"
#include "solver/sudoku_solver_heuristics.h"
#include "utils/utils.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 3)
        return -1;
    struct Sudoku_Grid grid = parse_from_string(argv[1]);
    print_sudoku(&grid);
    Sudoku_Grid_solve_simple_single_answer(&grid);
    //Sudoku_Grid_solve_heuristics_single_answer(&grid);
    // useful for speed testing
    if(argc == 2)
        print_sudoku(&grid);

    if (validate_solution(&grid))
    {
        printf("Correct solution!");
    }
    else
    {
        printf("Incorrect solution!");
    }

	return 0;

}
