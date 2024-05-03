#include "parser/parser.h"
#include "solver/sudoku_solver_simple.h"
#include "solver/sudoku_solver_heuristics.h"
#include "utils/utils.h"
#include <stdio.h>
#include <stdlib.h> 
#include "utils/timer.h"

int main(int argc, char* argv[])
{
    if(argc < 2 || argc > 4)
        return -1;


    int opt = 0;
    if (argc > 2)
    {
        opt = atoi(argv[2]);
    }

    timer(1);
    struct Sudoku_Grid grid = parse_from_string(argv[1]);
    int diff = timer(0);
    printf("\Reading sudoku took %d microseconds\n", diff);

    if(argc != 4)
        print_sudoku(&grid);
    
    timer(1);
    if (opt == 0)
    {
        Sudoku_Grid_solve_simple_single_answer(&grid);
    }
    else
    {
        Sudoku_Grid_solve_heuristics_single_answer(&grid, opt);
    }
    diff = timer(0);
    printf("\Solving sudoku took %d microseconds\n", diff);

    // useful for speed testing
    if(argc != 4)
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
