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

int Sudoku_Grid_solve_heuristics_single_answer(struct Sudoku_Grid* grid, int opt)
{
    // Opt maska bitowa z konfiguracj¹ z kolejnoœci¹ jak poni¿ej
    Heuristic_Opts h_opts;
    h_opts.use_MRV = CHECK_BIT(opt, 0);
    h_opts.use_NP = CHECK_BIT(opt, 1);
    h_opts.use_HP = CHECK_BIT(opt, 2);

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
    if(opts.use_HP)
        apply_hidden_pairs(grid, row, col);
    int possibilities = grid->possibilities_cell[row * SUDOKU_N + col] >> 1;
    int value = 1;
    while (possibilities)
    {
        if (possibilities & 1)
        {
            remove_possibilities(grid, value, row, col);
            grid->grid[row * SUDOKU_N + col] = value;
            if (Sudoku_Grid_solve_heuristics_single_answer_aux(grid, row, col, opts))
                return 1;
            grid->grid[row * SUDOKU_N + col] = 0;
            add_possibilities(grid, value, row, col);
        }
        value++;
        possibilities >>= 1;
    }
    return 0;
}