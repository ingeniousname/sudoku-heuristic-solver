#include "sudoku_solver_heuristics.h"
#include "sudoku_heuristics.h"
#include "../utils/sudoku_iterator.h"

int find_MRV_idx(struct Sudoku_Grid* grid)
{
    int min_idx = -1, min_val = 10;
    for (int row = 0; row < SUDOKU_N; row++)
    {
        for (int col = 0; col < SUDOKU_N; col++)
        {
            if (grid->grid[row * SUDOKU_N + col])
                continue;
            int possibilities = grid->possibilities_row[row] & grid->possibilities_col[col] & grid->possibilities_3x3[(row / 3) * 3 + col / 3];
            int count = __popcnt(possibilities);

            if (count < min_val)
            {
                min_idx = row * SUDOKU_N + col;
                min_val = count;
            }
        }
    }
    return min_idx;
}

void apply_naked_pairs(struct Sudoku_Grid* grid, int row, int col)
{
    unsigned int cell_possibilities = grid->possibilities_cell[row * SUDOKU_N + col] >> 1;
    if (__popcnt(cell_possibilities) != 2)
        return;

    for (int i = 0; i < SUDOKU_N; ++i)
    {
        // check row
        if (i != col)
        {
            unsigned int possibilities = grid->possibilities_cell[row * SUDOKU_N + i] >> 1;
            int possibilites_count = __popcnt(possibilities);
            if (possibilites_count == 2 && possibilities == cell_possibilities)
            {
                // Found naked pair in row, eliminate other possibilities in the row
                for (int j = 0; j < SUDOKU_N; ++j)
                {
                    if (j != col && j != i && grid->grid[row * SUDOKU_N + j] == 0)
                    {
                        unsigned int other_possibilities = grid->possibilities_cell[row * SUDOKU_N + j] & (~cell_possibilities << 1);
                        grid->possibilities_cell[row * SUDOKU_N + j] = other_possibilities;
                    }
                }
            }
        }

        // check column
        if (i != row)
        {
            unsigned int possibilities = grid->possibilities_cell[i * SUDOKU_N + col] >> 1;
            int possibilites_count = __popcnt(possibilities);
            if (possibilites_count == 2 && possibilities == cell_possibilities)
            {
                // Found naked pair in column, eliminate other possibilities in the column
                for (int j = 0; j < SUDOKU_N; ++j)
                {
                    if (j != row && j != i && grid->grid[j * SUDOKU_N + col] == 0)
                    {
                        unsigned int other_possibilities = grid->possibilities_cell[j * SUDOKU_N + col] & (~cell_possibilities << 1);
                        grid->possibilities_cell[j * SUDOKU_N + col] = other_possibilities;
                    }
                }
            }
        }
    }

    // check block
    int start_row = row / 3 * 3;
    int start_col = col / 3 * 3;
    for (int i = start_col; i < start_col + 3; ++i)
    {
        for (int j = start_row; j < start_row + 3; ++j)
        {
            if (i != col && j != row)
            {
                unsigned int possibilities = grid->possibilities_cell[j * SUDOKU_N + i] >> 1;
                int possibilites_count = __popcnt(possibilities);
                if (possibilites_count == 2 && possibilities == cell_possibilities)
                {
                    for (int c = start_col; c < start_col + 3; ++c)
                    {
                        for (int r = start_row; r < start_row + 3; ++r)
                        {
                            if ((c == col && r == row) || (c == i && r == j) || grid->grid[r * SUDOKU_N + c] != 0)
                                continue;

                            unsigned int other_possibilities = grid->possibilities_cell[j * SUDOKU_N + col] & (~cell_possibilities << 1);
                            grid->possibilities_cell[r * SUDOKU_N + c] = other_possibilities;
                        }
                    }
                }
            }
        }
    }
}

void sort_LCV_values(int* values, struct Sudoku_Grid* grid, int row, int col)
{
    int value_consts[SUDOKU_N] = { 0 };

    for (int i = 0; i < SUDOKU_N; ++i)
    {
        // count row
        if (i != col)
            check_constraints(values, value_consts, grid->possibilities_cell[row * SUDOKU_N + i]);

        // count column
        if (i != row)
            check_constraints(values, value_consts, grid->possibilities_cell[i * SUDOKU_N + col]);
    }

    // count 3x3
    int start_row = row / 3 * 3;
    int start_col = col / 3 * 3;
    for (int i = start_col; i < start_col + 3; ++i)
        for (int j = start_row; j < start_row + 3; ++j)
            if (i != col && j != row)
                check_constraints(values, value_consts, grid->possibilities_cell[j * SUDOKU_N + i]);

    // sort by key (bubble sort :3)
    int i, j, temp;
    for (i = 0; values[i] > 0; ++i)
    {
        for (j = i + 1; values[j] > 0; ++j)
        {
            if (value_consts[i] > value_consts[j])
            {
                temp = value_consts[i];
                value_consts[i] = value_consts[j];
                value_consts[j] = temp;

                temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
}

void check_constraints(int* values, int* value_consts, int possibilities)
{
    int i = 0;

    while (values[i] > 0)
    {
        if (CHECK_BIT(possibilities, (values[i] - 1)))
            value_consts[i]++;
        i++;
    }
}

void apply_hidden_pairs(struct Sudoku_Grid* grid, int row, int col)
{
    int main_idx = row * SUDOKU_N + col;
    int possibilities = grid->possibilities_cell[main_idx];
    // row
    for (int idx1 = row_iterator_start(row, col); idx1 != row_iterator_end(row, col); idx1 = row_iterator_next(row, col, idx1))
    {
        // if we found possible hidden pair candidate
        if (!idx1 == main_idx && __popcnt(possibilities & grid->possibilities_cell[idx1]) == 2)
        {
            int pair = possibilities & grid->possibilities_cell[idx1];
            int is_a_hidden_pair = 1;
            for (int idx2 = row_iterator_start(row, col); idx2 != row_iterator_end(row, col); idx2 = row_iterator_next(row, col, idx2))
            {
                // we have found a cell where exists an element from a possible pair - thus it is not a hidden pair
                if (idx2 != idx1 && idx2 != main_idx && grid->possibilities_cell[idx2] & pair != 0)
                {
                    is_a_hidden_pair = 0;
                    break;
                }
            }
                
            // if it actually is a hidden pair - update possibilities
            if (is_a_hidden_pair)
            {
                grid->possibilities_cell[main_idx] = pair;
                grid->possibilities_cell[idx1] = pair;
                return;
            }
        }
    }

    // col
    for (int idx1 = col_iterator_start(row, col); idx1 != col_iterator_end(row, col); idx1 = col_iterator_next(row, col, idx1))
    {
        // if we found possible hidden pair candidate
        if (!idx1 == main_idx && __popcnt(possibilities & grid->possibilities_cell[idx1]) == 2)
        {
            int pair = possibilities & grid->possibilities_cell[idx1];
            int is_a_hidden_pair = 1;
            for (int idx2 = col_iterator_start(row, col); idx2 != col_iterator_end(row, col); idx2 = col_iterator_next(row, col, idx2))
            {
                // we have found a cell where exists an element from a possible pair - thus it is not a hidden pair
                if (idx2 != idx1 && idx2 != main_idx && grid->possibilities_cell[idx2] & pair != 0)
                {
                    is_a_hidden_pair = 0;
                    break;
                }
            }

            // if it actually is a hidden pair - update possibilities
            if (is_a_hidden_pair)
            {
                grid->possibilities_cell[main_idx] = pair;
                grid->possibilities_cell[idx1] = pair;
                return;
            }
        }
    }

    // 3x3 square
    for (int idx1 = sq3x3_iterator_start(row, col); idx1 != sq3x3_iterator_end(row, col); idx1 = sq3x3_iterator_next(row, col,idx1))
    {
        // if we found possible hidden pair candidate
        if (!idx1 == main_idx && __popcnt(possibilities & grid->possibilities_cell[idx1]) == 2)
        {
            int pair = possibilities & grid->possibilities_cell[idx1];
            int is_a_hidden_pair = 1;
            for (int idx2 = sq3x3_iterator_start(row, col); idx2 != sq3x3_iterator_end(row, col); idx2 = sq3x3_iterator_next(row, col, idx2))
            {
                // we have found a cell where exists an element from a possible pair - thus it is not a hidden pair
                if (idx2 != idx1 && idx2 != main_idx && grid->possibilities_cell[idx2] & pair != 0)
                {
                    is_a_hidden_pair = 0;
                    break;
                }
            }

            // if it actually is a hidden pair - update possibilities
            if (is_a_hidden_pair)
            {
                grid->possibilities_cell[main_idx] = pair;
                grid->possibilities_cell[idx1] = pair;
                return;
            }
        }
    }
}
