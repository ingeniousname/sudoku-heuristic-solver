#include "sudoku_solver_heuristics.h"
#include "sudoku_solver_simple.h"
#include "../utils/utils.h"

int find_next_idx(struct Sudoku_Grid* grid, int row, int col, int use_MRV)
{
    if (use_MRV)
        return find_MRV_idx(grid);

    while (grid->grid[row * SUDOKU_N + col] != 0)
    {
        col++;
        if (col >= SUDOKU_N)
        {
            col = 0;
            row++;
        }
        if (row >= SUDOKU_N)
            return -1;
    }
    return row * SUDOKU_N + col;
}

// Find array of values that fit the box
void find_box_values(int *values, struct Sudoku_Grid* grid, int row, int col, int use_LCV)
{
    int possibilities = grid->possibilities_cell[row * SUDOKU_N + col] >> 1;
    int i = 0;
    int value = 1;
    while (possibilities)
    {
        if (possibilities & 1)
            values[i++] = value;
        value++;
        possibilities >>= 1;
    }

    // Sort possible values in LCV order
    if (use_LCV)
        sort_LCV_values(values, grid, row, col);
}

int Sudoku_Grid_solve_heuristics_single_answer(struct Sudoku_Grid* grid, int opt)
{
    // Opt maska bitowa z konfiguracja w kolejnosci jak ponizej
    Heuristic_Opts h_opts;
    h_opts.use_MRV = CHECK_BIT(opt, 0);
    h_opts.use_NP = CHECK_BIT(opt, 1);
    h_opts.use_LCV = CHECK_BIT(opt, 2);

    return Sudoku_Grid_solve_heuristics_single_answer_aux(grid, 0, 0, h_opts);
}

int Sudoku_Grid_solve_heuristics_single_answer_aux(struct Sudoku_Grid* grid, int row, int col, Heuristic_Opts opts)
{
    int idx = find_next_idx(grid, row, col, opts.use_MRV);
    if (idx < 0)
        return 1;

    row = idx / SUDOKU_N, col = idx % SUDOKU_N;

    if(opts.use_NP)
        apply_naked_pairs(grid, row, col);
    int values[SUDOKU_N] = { 0 };
    int value, i = 0;
    find_box_values(values, grid, row, col, opts.use_LCV);

    // Zero value is the end of the value list
    while (values[i] > 0)
    {
        value = values[i++];
        remove_possibilities(grid, value, row, col);
        grid->grid[row * SUDOKU_N + col] = value;
        if (Sudoku_Grid_solve_heuristics_single_answer_aux(grid, row, col, opts))
            return 1;
        grid->grid[row * SUDOKU_N + col] = 0;
        add_possibilities(grid, value, row, col);
    }
    return 0;
}